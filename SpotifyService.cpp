/*
    SpotifyService.cpp
    Brandon Luu
    09/23/2023

    This class provides the functionality to the SpotifyService.h header methods.
*/

#include <iostream>
using namespace std;

#include "SpotifyService.h"

// Constructor for the Spotify API class
SpotifyService::SpotifyService(string code, int access) {
    spotify.init(code, access);
}

// Get info about playing song
string SpotifyService::getPlaying() {
    spotify.execute("https://api.spotify.com/v1/me/player/currently-playing", spotify.req_GET);
    return spotify.result();
}

// Get JSON about a song
string SpotifyService::getSong(string id) {
    spotify.execute("https://api.spotify.com/v1/tracks/" + id, spotify.req_GET);
    return spotify.result();
}

// Get JSON about a playlist
string SpotifyService::getPlaylist(string id, int offset = 0) {
    spotify.execute("https://api.spotify.com/v1/playlists/" + id + "?offset=" + to_string(offset), spotify.req_GET);
    return spotify.result();
}

// Get JSON about an album
string SpotifyService::getAlbum(string id, int offset = 0) {
    spotify.execute("https://api.spotify.com/v1/albums/" + id + "?offset=" + to_string(offset), spotify.req_GET);
    return spotify.result();
}

// Set the volume
void SpotifyService::setVolume(int volume) {
    spotify.execute("https://api.spotify.com/v1/me/player/volume?volume_percent=" + to_string(volume), spotify.req_PUT);
}

// Start playing music
void SpotifyService::play() {
    spotify.execute("https://api.spotify.com/v1/me/player/play", spotify.req_PUT);
}

// Pause the music
void SpotifyService::pause() {
    spotify.execute("https://api.spotify.com/v1/me/player/pause", spotify.req_PUT);
}

// Skip to the next song
void SpotifyService::skipNext() {
    spotify.execute("https://api.spotify.com/v1/me/player/next", spotify.req_POST);
}

// Skip to the previous song
void SpotifyService::skipPrevious() {
    spotify.execute("https://api.spotify.com/v1/me/player/previous", spotify.req_POST);
}

// Add a song to the queue
void SpotifyService::queue(string url) {
    spotify.execute("https://api.spotify.com/v1/me/player/queue?uri=spotify:track:" + url, spotify.req_POST);
}