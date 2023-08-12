/**
    @file RFIDModule.h
    @brief This header provides basic CURL functionality for fetching data from a URL.
    @author Brandon Luu
    @date 09/23/2023
*/

#include <iostream>
using namespace std;

/**
    @brief The RFID module class.
*/
class RFIDModule {
    public:
        /**
            @brief The constructor for the class.
        */
        RFIDModule();

        /**
            @brief The destructor for the class.
        */
        ~RFIDModule();

        /**
            @brief Get the data stored within a MIFARE Classic block.
            @param block The block number.
            @return Returns the data as a decoded string.
        */
        string get(int block);
};