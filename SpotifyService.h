/**
    @file SpotifyService.h
    @brief This header provides function definitions for use in interacting with the Spotify API.
    @author Brandon Luu
    @date 09/23/2023
*/

#ifndef SPOTIFYSERVICE_H
#define SPOTIFYSERVICE_H

#include <iostream>
using namespace std;

#include "SpotifyWebRequest.h"

/**
    @brief The Spotify API service class.
*/
class SpotifyService {
    private:
        /**
          @brief A web request object for handling web requests.
        */
        SpotifyWebRequest spotify;
    public:
        /**
            @brief Constructor for the Spotify API service.
            @param code The Spotify authorization token.
            @param access Whether the auth token is already authorized (your code is actually an access token) or not.
        */
        SpotifyService(string code, int access);

        /**
            @brief Gets infomration about the currently playing song.
            @return Returns the JSON information about the currently playing song.
        */
        string getPlaying();

        /**
            @brief Gets infomration about a song.
            @param id The Spotify ID of the song (ex. The text after "track:" in spotify:track:57fqmDaokbxZ3TaB0jp39q).
            @return Returns the JSON information about a song.
        */
        string getSong(string id);

        /**
            @brief Gets infomration about a playlist.
            @param id The Spotify ID of the playlist (ex. The text after "playlist:" in spotify:playlist:28Iy9h5Xzax5dVbwmrgPxa).
            @return Returns the JSON information about a playlist.
        */
        string getPlaylist(string id, int offset);

        /**
            @brief Gets infomration about an album.
            @param id The Spotify ID of the album (ex. The text after "album:" in spotify:album:2ivNJLSx8Rbvnsvcn01Yt3).
            @return Returns the JSON information about an album.
        */
        string getAlbum(string id, int offset);

        /**
            @brief Sets the volume of the active device.
            @param volume The volume (from 0 to 100).
        */
        void setVolume(int volume);

        /**
            @brief Begin playback of the active device.
        */
        void play();

        /**
            @brief Pause playback of the active device.
        */
        void pause();

        /**
            @brief Skip to the next song in the Spotify queue.
        */
        void skipNext();

        /**
            @brief Skip to the previous song in the Spotify queue.
        */
        void skipPrevious();

        /**
            @brief Add a song to the Spotify queue.
            @param url The Spotify song's URL (ex. track:57fqmDaokbxZ3TaB0jp39q).
        */
        void queue(string url);
};

#endif
