/**
    @file GUITest.h
    @brief This header provides testing for our GUI class. 
    @author Brandon Luu 
    @date 03/14/2023
*/

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

/**
 * A testing class for our GUI.
*/
class GUI {
    private:
        /**
         * @brief The window that will hold the GUI. 
        */
        RenderWindow window;
        /**
         * @brief A texture instance for testing texture rendering.
        */
        Texture texture;
        /**
         * @brief A sprite instance for testing sprite rendering. 
        */
        Sprite sprite;
    public:
        /**
         * Method to run a standard display test, like creating a window, drawing sprite and showing textures. 
        */
        void Run();
        /**
         * Method to change the name of the current window.
         * @param name The new name of the window.
        */
        void setName(string name);
        /**
         * Method to change the background image of the current window.
         * @param url The new background image of the window.
        */
        void setImage(string url);
};
