/**
    @file SpotifyWebRequest.h
    @brief This header provides CURL requests with appropriate headers for any Spotify API call. It is a modified version of a libcurl example.
    @author Brandon Luu
    @date 09/23/2023
*/

#ifndef SPOTIFYWEBREQUEST_H
#define SPOTIFYWEBREQUEST_H

#include <iostream>
#include <curl/curl.h>
using namespace std;

/**
    @brief The Spotify CURL class.
*/
class SpotifyWebRequest {
    private:
        /**
            @brief A structure to hold libcurl data.
        */
        struct MemoryStruct {
            char *memory;
            size_t size = 0;
        };

        // libcurl stuff
        struct MemoryStruct data;
        struct MemoryStruct readData;
        CURL *curl_handle;
        CURLcode res;
        struct curl_slist *headerList = NULL;

        const string client = "ODY5MmQwOTY3ZTdkNGJkNGJmODk4YzJjOThiOWU2NGI6ZDM2YjBlYWIxNjdiNDE2OThlNjM3YWY3ZDZmNTllZDA="; /**< Spotify app client token. */
        const string clientID = "8692d0967e7d4bd4bf898c2c98b9e64b"; /**< Spotify app client ID. */
        const string clientSecret = "d36b0eab167b41698e637af7d6f59ed0"; /**< Spotify app client secret. */
        string access_token; /**< Access token obtained when first authenticating with the Spotify API. */
        string refresh_token; /**< Refresh token used to refresh the access token. */

        /**
            @brief libcurl write method.
        */
        static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
    
    public:
        /**
            @brief Constructor for the Spotify CURL class.
        */
        SpotifyWebRequest();

        /**
            @brief Destructor for the Spotify CURL class.
        */
        ~SpotifyWebRequest();

        /**
            @brief Authenticates the user's token and prepares the headers for an API call.
            @param code The user's authentication token.
            @param access Whether the code is already authorized or not (is it an access token?)
        */
        void init(string code, int access);

        /**
            @brief Fetches the data at the URL.
            @param url The URL.
            @param type The type of request (GET, POST, PUT).
            @return Returns whether the request was successful or not.
        */
        bool execute(string url, int type);

        /**
            @brief Get the result of the call.
            @return Returns the data.
        */
        string result();
        
        // Type of request
        // This can be an enum instead, but this works.
        int req_GET = 0;
        int req_POST = 1;
        int req_PUT = 2;
};

#endif
