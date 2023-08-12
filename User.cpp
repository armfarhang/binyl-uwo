/**
    @file User.cpp
    @brief This program implements User.h. 
    @author Brandon Luu
    @date 09/23/2023
*/

#include <string>
using namespace std;

#include "User.h"

User::User() {}

User::User(string who) {
    username = who;
}

string User::getUsername() {
    return username;
}
