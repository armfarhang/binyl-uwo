/**
    @file maintest.cpp 
    @brief This program provides testing of our GUI 
    @author Armin Farhang
    @date 03/14/2023
*/

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>

// to run:
// g++ test1.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// ps -u afarhan3

/**
 * Main method from which our tests will be run.
 * @return A status code for main.
 */
int main()
{
    //render the window
    // sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "My Full Screen Window", sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(1920,1080), "My Full Screen Window", sf::Style::Fullscreen);
    // sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Fullscreen Background");

    // set textures
    sf::Texture cover, coverShadow, bckgrnd, lPlant, lPlantDs, rPlant, line, upnextBars;
    if (!cover.loadFromFile("assets/cover.png") ||
        !coverShadow.loadFromFile("assets/cover-shadow.png") ||
        !bckgrnd.loadFromFile("assets/gradient-background.png") ||
        !lPlant.loadFromFile("assets/left-plant.png") ||
        !rPlant.loadFromFile("assets/right-plant.png") ||
        !line.loadFromFile("assets/line.png") ||
        !upnextBars.loadFromFile("assets/upnext.png") ||
        !lPlantDs.loadFromFile("assets/left-plant-ds.png"))
         // load image file
    {
        std::cerr << "Failed to load image file!" << std::endl;
        return -1;
    }

    // set the background and adjust it to fit the window
    sf::Sprite bckgrndsprite(bckgrnd);
    // bckgrndsprite.setPosition(0, 0);
    // bckgrndsprite.setPosition(window.getSize().x/2 - bckgrndsprite.getGlobalBounds().width/2, 
    //                           window.getSize().y/2 - bckgrndsprite.getGlobalBounds().height/2
    // );
    
    bckgrndsprite.setScale(
        float(window.getSize().x) / bckgrndsprite.getLocalBounds().width,
        float(window.getSize().y) / bckgrndsprite.getLocalBounds().height
    );
    // render the album art 
    sf::Sprite coversprite(cover);
    coversprite.setPosition(192, 101);

    //render the shadow on the cover
    sf::Sprite coverShadowsprite(coverShadow);
    coverShadowsprite.setPosition(192, 20);

    //render the plant
    sf::Sprite lPlantsprite(lPlant);
    lPlantsprite.setPosition(0, 478);

    sf::Sprite lPlantDssprite(lPlantDs);
    lPlantDssprite.setPosition(0, 455);

    sf::Sprite rPlantsprite(rPlant);
    rPlantsprite.setPosition(442, 653);

    //render a line dividing the artist name from the song names
    sf::Sprite linesprite(line);
    linesprite.setPosition(1053, 253);

    //render the up next section of the GUI
    sf::Sprite upnextBarssprite(upnextBars);
    upnextBarssprite.setPosition(1038, 448);




    sf::Vector2u bckgrndSize = bckgrnd.getSize();
    // sf::Vector2u coverSize = cover.getSize();
    // sf::Vector2u coverShadowSize = coverShadow.getSize();
    // sf::Vector2u lPlantSize = lPlant.getSize();
    // sf::Vector2u lPlantDsSize = lPlantDs.getSize();
    // sf::Vector2u rPlantSize = rPlant.getSize();
    // sf::Vector2u lineSize = line.getSize();
    // sf::Vector2u upnextBarsSize = upnextBars.getSize();
    
    
    // //  sf::Vector2u maxSize = {std::max(bgSize.x, std::max(midSize.x, fgSize.x)),
    // //                         std::max(bgSize.y, std::max(midSize.y, fgSize.y))};


    // // Set the size of the window to match the largest texture
    // sf::Vector2u maxSize = {std::max(bckgrndSize.x, std::max(coverSize.x, std::max(coverShadowSize.x, std::max(lPlantSize.x, std::max(lPlantDsSize.x, std::max(rPlantSize.x, std::max(lineSize.x, upnextBarsSize.x))))))),
    //                         std::max(bckgrndSize.y, std::max(coverSize.y, std::max(coverShadowSize.y, std::max(lPlantSize.y, std::max(lPlantDsSize.y, std::max(rPlantSize.y, std::max(lineSize.y, upnextBarsSize.y)))))))};
    // window.setSize(sf::Vector2u(maxSize.x, maxSize.y));


    window.setSize(bckgrndSize);
    
    // import attributes like fonts, colors, etc.
////////////////////////////////////////////////////////////////////////////////
    sf::Font ChakReg, chakBold, monstFontItal, monstFontReg;
    sf::Color black(0, 0, 0);
    sf::Color offwhite(212, 212, 212);
    sf::Color greywhite(120, 120, 120);



    if (!ChakReg.loadFromFile("fonts/ChakraPetch/ChakraPetch-Regular.ttf") ||
            !chakBold.loadFromFile("fonts/ChakraPetch/ChakraPetch-SemiBoldItalic.ttf") ||
            !monstFontItal.loadFromFile("fonts/Montserrat/Montserrat-Italic.ttf") ||
            !monstFontReg.loadFromFile("fonts/Montserrat/Montserrat-Regular.ttf")            
            ){ // load font files
        std::cerr << "Failed to load font file!" << std::endl;
        return -1;
    }
    
    // string artist("The Weeknd");
    // string song("False Alarm");
    // string album("STARBOY");


    // set default song values to test rendering
    sf::Text artisttext("The Weeknd", monstFontItal, 60);
    artisttext.setPosition(1043, 178);

    sf::Text albumtext("STARBOY", monstFontReg, 20);
    albumtext.setPosition(1048, 309);

    sf::Text songtext("False Alarm", chakBold, 30);
    songtext.setPosition(1045, 265);

    sf::Text nexttext("Up Next", ChakReg, 30);
    nexttext.setPosition(1053, 401);
    nexttext.setFillColor(black);


    sf::Text next1text("Lana Del Rey - NFR", ChakReg, 30);
    sf::Text next1typetext("album", ChakReg, 30);
    next1text.setPosition(1057, 452);
    next1typetext.setPosition(1631, 452);
    next1text.setFillColor(offwhite);
    next1typetext.setFillColor(greywhite);

    sf::Text next2text("Drake - Hot Line Bling", ChakReg, 30);
    sf::Text next2typetext("single", ChakReg, 30);
    next2text.setPosition(1057, 506);
    next2typetext.setPosition(1578, 506);
    next2text.setFillColor(offwhite);
    next2typetext.setFillColor(greywhite);

    sf::Text next3text("Spotify Lofi Stud...", ChakReg, 30);
    sf::Text next3typetext("playlist", ChakReg, 30);
    next3text.setPosition(1057, 560);
    next3typetext.setPosition(1500, 560);
    next3text.setFillColor(offwhite);
    next3typetext.setFillColor(greywhite);

    sf::Text next4text("Parcels - Vol.1", ChakReg, 30);
    sf::Text next4typetext("playlist", ChakReg, 30);
    next4text.setPosition(1057, 615);
    next4typetext.setPosition(1448, 615);
    next4text.setFillColor(offwhite);
    next4typetext.setFillColor(greywhite);





    // string artist("The Weeknd");
    // string song("False Alarm");
    // string album("STARBOY");

    // draw everything in the GUI
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(bckgrndsprite);
        window.draw(coverShadowsprite);
        window.draw(coversprite);
        window.draw(lPlantDssprite);
        window.draw(lPlantsprite);
        
        window.draw(rPlantsprite);
        window.draw(linesprite);
        window.draw(upnextBarssprite);
        

        window.draw(artisttext);
        window.draw(albumtext);
        window.draw(songtext);
        window.draw(nexttext);
        window.draw(next1text);
        window.draw(next1typetext);
        window.draw(next2text);
        window.draw(next2typetext);
        window.draw(next3text);
        window.draw(next3typetext);
        window.draw(next4text);
        window.draw(next4typetext);

        window.display();

        // std::this_thread::sleep_for(std::chrono::minutes(3)); // wait for 3 minutes
    }

    return 0;
}
