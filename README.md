# Binyl

Vinyls digitized for Raspberry Pi.

### Authors
* Brandon Luu
* Armin Farhang
* Irfan Sharif
* Ryan Cook
* Endreas Yohannes

### Introduction
* This is a program written in C++ for the Raspberry Pi that is meant to vinyl-like funcitonality with tap cards.
* The program uses Spotify's API to store and play songs, with URLs being loaded onto RFID cards.
* To play a song, we tap the corresponding card onto an RFID module attached to a Raspberry Pi while running the program.

### Current Features
* Functional GUI
* Cards loaded with individual songs play as expected
* Multiple songs can be queued at once, with the songs that are up next being displayed in the GUI
* Users can pause, play, go to the next song and go to the previous song
* Song cards are associated with users and the user who owns the card will be displayed in the GUI

### Dependencies
* RFID-RC522 - A library for RFID support on Raspberry Pi [https://github.com/paulvha/rfid-rc522]
* BCM2835 - A library for Broadcom BCM 2835 chip support on Raspberry Pi [https://www.airspayce.com/mikem/bcm2835]
* SFML - Multimedia for C++ [https://www.sfml-dev.org]
* libssd1306 - A driver for OLED SSD1306 [https://github.com/stealthylabs/libssd1306]
* curl - For HTTP requests [https://curl.se]

### Building
* Install all the above Dependencies
* Run the makefile
```sh 
make all
```
