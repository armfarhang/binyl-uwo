/**
    @file GUITest.cpp
    @brief This program implements GUITest.h. 
    @author Brandon Luu
    @date 09/23/2023
*/

#include "GUI.h"

#include <SFML/Graphics.hpp>

#include <iostream>
using namespace std;

#include "Curl.h"
#include <vector>

using namespace sf;

void GUI::Run() {
    // Begin data retrieval using request object
    window.create(VideoMode(600, 600), "GUI with Image Thread");

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
}

void GUI::setName(string name) {
    window.setTitle(name);
}

void GUI::setImage(string url) {
    Curl myrequest(url);
    myrequest.execute();
    texture.loadFromMemory(myrequest.result(), myrequest.size());
    sprite.setTexture(texture);
}
