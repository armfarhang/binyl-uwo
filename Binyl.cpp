/*
    program.cpp
    Brandon Luu
    09/23/2023

    Binyl: Spotify RFID Music Player
    Tap your card to add songs, change playback, and more!

    The main program. Interfaces with all the classes.
*/

// TODO: Convert modules into singletons

#include <iostream>
using namespace std;

#include <string>
#include <thread>
#include <unistd.h>

#include "SpotifyService.h"
#include "RFIDModule/RFIDModule.h"
#include "GUI.h"
#include "User.h"
#include "Song.h"

#include "json.hpp"
using json = nlohmann::json;

// Declare threads in main beforehand
void guiThreadFunction(GUI* gui);
void rfidThreadFunction(RFIDModule *rfid, SpotifyService *spotify, GUI *gui, vector<Song> *queue);
void processSongThreadFunction(SpotifyService *spotify, GUI *gui, vector<Song> *queue);

/**
    Entry point for the program.
    @param argc Argument count.
    @param argv Should contain the Spotify token obtained from the authorization URL as the first argument.
*/
int main(int argc, char* argv[]) {
  // Check user sudo, if not then exit
  if (geteuid() != 0) {
    cout << "Binyl must be run as root (sudo)." << endl;
    return -1;
  }

  // Check and parse arguments
  if (argc < 2) {
    cout << "\nBinyl: Spotify RFID Music Player\n\nSpotify code missing\nVisit this site and login to get a new code.\n"
    "Copy the 'code' value within the URL and run the program using:\n"
    "\t./program [code]\n"
    "\t./program [access token] 1\n" << endl;
    cout << "https://accounts.spotify.com/authorize?response_type=code&scope=user-read-playback-state user-modify-playback-state&client_id=8692d0967e7d4bd4bf898c2c98b9e64b&redirect_uri=https://www.blank.org/\n" << endl;
    return -1;
  }
  
  string code = string(argv[1]);
  int access = 0;
  if (argc == 3) access = stoi(argv[2]);

  cout << "\nBinyl: Spotify RFID Music Player\n\nTap your card to add songs, change playback, and more!\n" << endl;

  // Create classes
  SpotifyService spotify(code, access);
  RFIDModule rfid;
  GUI gui(1920, 1080, "Binyl", "w");
  vector<Song> queue;

  // Create needed threads: GUI, RFID reader, Song processor
  thread guiThread(guiThreadFunction, &gui);
  thread rfidThread(rfidThreadFunction, &rfid, &spotify, &gui, &queue);
  thread processSongThread(processSongThreadFunction, &spotify, &gui, &queue);

  /*
  thread screenThread(graphicstest);
  while (true);
  */

  //pid_t screenFork = fork();
  //if (screenFork == 0) execl("test_fb_graphics", NULL);

  while (true);

  return 0;
}

/**
    Begins reading from the RFID reader and sends commands to the Spotify API.
    @param spotify The Spotify API service object.
    @param queue The song queue.
    @param rfid The RFID module service.
*/
void rfidThreadFunction(RFIDModule *rfid, SpotifyService *spotify, GUI *gui, vector<Song> *queue) {
  Controls& controls = Controls::getInstance();

  cout << "Card reader started!\n" << endl;
  while (true) {
    // get card type and check to see if valid
    string type = rfid->get(8);

    if (type == "track") {
      // Combine IDs as they are stored on two blocks
      string id1 = rfid->get(9);
      string id2 = rfid->get(10);
      string id = id1 + id2;

      string cardOwner = rfid->get(12);
      // Get song info (for use later...)
      json songjson = json::parse(spotify->getSong(id));

      // Stop if there is an error while queuing
      if (!songjson["error"].is_null()) {
        string error = songjson["error"]["message"];
        cout << "Error while queuing song: " << error << endl;
        break;
      }

      // Printing json object directly adds quotes around strings, this avoids that
      string songID = songjson["id"];
      string songName = songjson["name"];
      int songDuration = songjson["duration_ms"];
      string albumName = songjson["album"]["name"];
      string artistName = songjson["artists"][0]["name"];
      string albumArt = songjson["album"]["images"][0]["url"];
      
      // Create user and song, then queue
      User newUser(cardOwner);
      Song newSong(newUser, songID, songName, songDuration, albumName, artistName, albumArt);
      queue->push_back(newSong);

      cout << "[" << cardOwner << ": Queue Song] " << artistName << " - " << songName << endl;
    }

    // There is a limit where it can only get 100 songs at once
    // but we can use the offset flag to get around it
    else if (type == "playlist") {
      // Combine IDs as they are stored on two blocks
      string id1 = rfid->get(9);
      string id2 = rfid->get(10);
      string id = id1 + id2;

      string cardOwner = rfid->get(12);

      // Loop until we reach the end of the playlist
      int offset = 0;
      while (true) {
        json playlistjson = json::parse(spotify->getPlaylist(id, offset));

        // Stop if there is an error while getting playlist
        if (!playlistjson["error"].is_null()) {
          string error = playlistjson["error"]["message"];
          cout << "Error while queuing playlist: " << error << endl;
          break;
        }

        // Get songs in playlist
        json items = playlistjson["tracks"]["items"];
        int count = 0;
        for (count; count != items.size(); count++) {
          string songID = items[count]["track"]["id"];

          json songjson = json::parse(spotify->getSong(songID));

          // Get data
          string songName = songjson["name"];
          int songDuration = songjson["duration_ms"];
          string albumName = songjson["album"]["name"];
          string artistName = songjson["artists"][0]["name"];
          string albumArt = songjson["album"]["images"][0]["url"];
          
          // Create user and song, then queue
          User newUser(cardOwner);
          Song newSong(newUser, songID, songName, songDuration, albumName, artistName, albumArt);
          queue->push_back(newSong);
        }

        // If the "next" field is defined, then continue getting the next set of 100 songs
        if (!playlistjson["tracks"]["next"].is_null()) offset += 100;
        else {
          // Printing json object directly adds quotes around strings, this avoids that
          string displayName = playlistjson["owner"]["display_name"];
          string playlistName = playlistjson["name"];
          cout << "[" << cardOwner << ": Queue Playlist] " << displayName << " - " << playlistName << " [" << playlistjson["tracks"]["total"] << " song(s)]" << endl;
          break;
        }
      }
    }

    // There is a limit where it can only get 50 songs at once
    // but we can use the offset flag to get around it
    else if (type == "album") {
      // Combine IDs as they are stored on two blocks
      string id1 = rfid->get(9);
      string id2 = rfid->get(10);
      string id = id1 + id2;

      string cardOwner = rfid->get(12);

      // Loop until we reach the end of the playlist
      int offset = 0;
      while (true) {
        json albumjson = json::parse(spotify->getAlbum(id, offset));

        // Stop if there is an error while getting playlist
        if (!albumjson["error"].is_null()) {
        string error = albumjson["error"]["message"];
        cout << "Error while queuing album: " << error << endl;
        break;
      }

        // Get songs in album
        json items = albumjson["tracks"]["items"];
        string albumName = albumjson["name"];
        string artistName = albumjson["artists"][0]["name"];
        string albumArt = albumjson["images"][0]["url"];

        int count = 0;
        for (count; count != items.size(); count++) {
          string songID = items[count]["id"];
          string songName = items[count]["name"];
          int songDuration = items[count]["duration_ms"];

          // Get user and song, then queue
          User newUser(cardOwner);
          Song newSong(newUser, songID, songName, songDuration, albumName, artistName, albumArt);
          queue->push_back(newSong);
        }

        // If the "next" field is defined, then continue getting the next set of 50 songs
        if (!albumjson["tracks"]["next"].is_null()) offset += 50;
        else {
          cout << "[" << cardOwner << ": Queue Album] " << artistName << " - " << albumName << " [" << albumjson["tracks"]["total"] << " song(s)]" << endl;
          break;
        }
      }
    }
    // Toggle between pause and play
    else if (type == "toggleplay") {
      // Set to play
      if (controls.isPause()) {
        cout << "Changing playback to playing..." << endl;
        controls.setPause(false);
        spotify->play();
        gui->setPlayScreen();
      }
      else {
        cout << "Changing playback to paused..." << endl;
        spotify->pause();
        controls.setPause(true);
        gui->setPauseScreen();
      }
    }
    // Skip to the next song
    else if (type == "skipnext") {
      cout << "Skipping to next song..." << endl;
      // Set time left to 0 and set GUI
      controls.setTimeLeft(0);
      gui->flashNextLogo();
    }
    else {
      cout << "Invalid card!" << endl;
    }

    // Delay for next card
    printf("\nNext card reading in 3 seconds...\n");
    sleep(3);
  }
}

/**
    Begins processing songs in the queue to be played.
    @param spotify The Spotify API service object.
    @param gui The GUI object.
    @param queue A vector of Songs.
*/
void processSongThreadFunction(SpotifyService *spotify, GUI *gui, vector<Song> *queue) {
  Controls& controls = Controls::getInstance();
  int prevQueueSize = 0;

  while (true) {
    // Song still playing, decrement time and continue
    if (controls.getTimeLeft() > 0) {
      if (!controls.isPause()) controls.setTimeLeft(controls.getTimeLeft() - 1000);

      // Update GUI if queue size changed
      if (prevQueueSize != queue->size()) {
        // Get next 4 songs
        vector<Song> four;
        for (int i = 0; i != 4; i++) {
          // Prevent out of bounds if i is larger than queue
          if (i == queue->size()) break;
          four.push_back(queue->at(i));
        }

        gui->setNext(four);

        prevQueueSize = queue->size();
      }
    }
    else if (queue->size() > 0) {
      // Dequeue a song and play it
      Song song = queue->front();
      queue->erase(queue->begin());

      // Queue up the song and set time left
      spotify->queue(song.getID());
      // Delay for queuing and then play
      sleep(1);
      spotify->skipNext();
      sleep(1);
      spotify->play();
      controls.setTimeLeft(song.getDuration());

      // Update GUI
      gui->setCurrentSong(song);
    }
    else gui->setEmpty();

    // Wait one second and loop
    sleep(1);
  }
}

/**
    Begins running the GUI.
    @param gui The GUI object.
*/
void guiThreadFunction(GUI *gui) {
  gui->runScreen();

  // If the GUI has exited, exit the program
  return 0;
}