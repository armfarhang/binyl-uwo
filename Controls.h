/**
    @file Contents.h
    @brief This header provides basic controls functionality for pausing and playing songs.
    @author Armin Farhang
    @author Brandon Luu
    @date 03/14/2023
*/
#ifndef CONTROLS_H
#define CONTROLS_H

class Controls {
private:
    /**
     * @brief Indicator of play status.
     * True for paused, false for playing.
    */
    bool paused = false;
    /**
     * @brief Indicator of queue mode.
     * True means we're in queue mode, false means the opposite.
    */
    bool queue_mod;
    /**
     * @brief Time remaining on the current song in seconds.
    */
    int timeLeft = 0;
    /**
     * Constructor for an instance of Controls.
    */
    Controls();

public:
    /**
     * Method to initialize and return a single Controls instance.
     * @return A pointer to the requested Controls instance.
    */
    static Controls& getInstance();
    /**
     * Method to return the current pause status.
     * @return True if the song is paused, false otherwise.
    */
    bool isPause();
    /**
     * Method to return the current queue mode.
     * @return True if we're in queue mode, false otherwise.
    */
    bool isQueMode();
    /**
     * Method to set the pause status of Controls.
     * @param pause The desired pause status (true for pause, false for play).
    */
    void setPause(bool pause);
    /**
     * Method to turn queue mode on and off in Controls.
     * @param mode The desired queue mode (true for queue mode, false for non-queue mode).
    */
    void setQueMode(bool mode);
    /**
     * Method to get the time left in the current song.
     * @return The time left of the current song in seconds.
    */
    int getTimeLeft();
    /**
     * Method to set the time of the current song.
     * @param time The desired time stamp in seconds. 
    */
    void setTimeLeft(int time);


    /**
     * idk what this does lmao 
    */
    Controls(const Controls&) = delete;
    /**
     * idk what this does lmao 
    */
    Controls& operator=(const Controls&) = delete;
};

#endif // CONTROLS_H
