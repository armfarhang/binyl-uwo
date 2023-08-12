/**
    @file Song.h 
    @brief This header provides a Song class representing a song. 
    @author Brandon Luu 
    @date 03/14/2023
*/

#ifndef SONG_H
#define SONG_H

#include <string>
#include "User.h"

using namespace std;

/**
 * @brief The song class.
*/
class Song {
    private:
        /**
         * @brief The user who requested the song.
        */
        User user;
        /**
         * @brief The unique ID of the song. 
        */
        string id;
        /**
         * @brief The name of the song.
        */
        string name;
        /**
         * @brief The song's associated album name.
        */
        string album;
        /**
         * @brief The song's artist's name.
        */
        string artist; 
        /**
         * @brief A link to the cover art of the song. 
        */
        string coverArt;
        /**
         * @brief The song's total duration in seconds. 
        */
        int duration;
    public:
        /**
         * A default constructor for the Song class. 
        */
        Song();
        /**
         * A full constructor for the Song class.
         * @param user The user who requested the song.
         * @param id The id of the song. 
         * @param name The name of the song. 
         * @param duration The duration of the song in seconds. 
         * @param album The song's album's name. 
         * @param artist The song's artist's name. 
         * @param coverArt A link to the cover art of the song. 
        */
        Song(User user, string id, string name, int duration, string album, string artist, string coverArt); 
        /**
         * Method to get the ID of the song. 
         * @return The ID of the song.
        */
        string getID();
        /**
         * Method to get the user who requested the song. 
         * @return The user who requested the song.
        */
        User getUser();
        /**
         * Method to get the artist who made the song. 
         * @return The song's artist.
        */
        string getArtist();
        /**
         * Method to get the name of the song. 
         * @return The name of the song.
        */
        string getName();
        /**
         * Method to get the song's album. 
         * @return The song's album's name.
        */
        string getAlbum();
        /**
         * Method to get the cover art of the song. 
         * @return The cover art of the song.
        */
        string getCoverArt();
        /**
         * Method to get the duration of the song. 
         * @return The duration of the song.
        */
        int getDuration();
};

#endif
