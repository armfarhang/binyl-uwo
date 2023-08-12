/**
    @file User.h
    @brief This header provides a representation of a Spotify user. 
    @author Brandon Luu
    @date 09/23/2023
*/

#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

/**
 * @brief Class representing a Spotify user.
 */
class User {
    private:
        /**
         * @brief The username of the user.
         */
        string username;
    public:
        /**
         * A default constructor for User. 
         */
        User();
        /**
         * A constructor for User.
         * @param who The username of the user.
         */
        User(string who);
        /**
         * Method to get the user's username.
         * @return The user's username. 
         */
        string getUsername();
};

#endif
