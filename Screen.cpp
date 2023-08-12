/**
 * @file Screen.cpp
 * This will be overwritten once we're done stress testing GUI.cpp
*/

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include "Controls.h"

class Screen {    
    
    private:
    sf::RenderWindow window;
    sf::Texture cover, bckgrnd, pause_bckgrnd, next, prev, pause, play;
    sf:: Sprite coversprite, bckgrndsprite, pause_bckgrndsprite, nextsprite, prevsprite, pausesprite, playsprite;
    std::string artist = "The Weeknd";
    std::string song = "False Alarm";
    std::string album = "STARBOY";
    //defining fonts and colors---------------------------------
    sf::Font ChakReg, chakBold, monstFontItal, monstFontReg;
    sf::Color black;
    sf::Color offwhite;
    sf::Color greywhite;
    sf::Color opacitynone;
    sf::Color opacityfull;
    

    sf::Text artisttext, albumtext, songtext,
    next1text, next2text, next3text, next4text,
    next1typetext, next2typetext, next3typetext, next4typetext;

    Controls& controls = Controls::getInstance();
    sf::Clock vistimer, nexttimer, prevtimer;

    int pausecounter = 0;
    int resumecounter = 0;
    int nextcounter = 0;
    int prevcounter = 0;
   

    
    


    public:


    Screen (int width, int height, const std::string& title, const std::string& style): 
    black(0, 0, 0), 
    offwhite(212, 212, 212), 
    greywhite(120, 120, 120),
    artisttext(artist, monstFontItal, 60),
    albumtext(album, monstFontReg, 20),
    songtext(song, chakBold, 30),
    next1text("", ChakReg, 30),
    next1typetext("", ChakReg, 30),
    next2text("", ChakReg, 30),
    next2typetext("", ChakReg, 30),
    next3text("", ChakReg, 30),
    next3typetext("", ChakReg, 30),
    next4text("", ChakReg, 30),
    next4typetext("", ChakReg, 30)
    {
        
        
        
        //setting resolution and window type ----------------------------
        if (style =="F" || style == "f"){
            window.create(sf::VideoMode(width, height), title, sf::Style::Fullscreen);
        }
        else{
            window.create(sf::VideoMode::getDesktopMode(), title);
        }


        //loading textures with error checking ---------------------------
        if (!bckgrnd.loadFromFile("assets/gradient-background.png")){
            std::cerr << "Failed to load background image!" << std::endl;
            
        }
        if (!pause_bckgrnd.loadFromFile("assets/pause-background.png")){
            std::cerr << "Failed to load pause background image!" << std::endl;
            
        }
        if (!cover.loadFromFile("assets/cover.png")){
            std::cerr << "Failed to load cover album image!" << std::endl;
            
            
        }
        if (!next.loadFromFile("assets/next.png")){
            std::cerr << "Failed to load cover album image!" << std::endl;
            
        }
        if (!prev.loadFromFile("assets/prev.png")){
            std::cerr << "Failed to load cover album image!" << std::endl;
            
        }
        if (!pause.loadFromFile("assets/pause.png")){
            std::cerr << "Failed to load cover album image!" << std::endl;
            
        }
        if (!play.loadFromFile("assets/play.png")){
            std::cerr << "Failed to load cover album image!" << std::endl;
            
        }
        //setting sprites -----------------------------------------
        bckgrndsprite.setTexture(bckgrnd);
        pause_bckgrndsprite.setTexture(pause_bckgrnd);
        coversprite.setTexture(cover);
        nextsprite.setTexture(next);
        prevsprite.setTexture(prev);
        pausesprite.setTexture(pause);
        playsprite.setTexture(play);
        //setting opacity of next, play. pause, prev ---------------
        opacitynone = nextsprite.getColor();
        opacityfull = opacitynone;
        opacitynone.a = 0;
        opacityfull.a = 255;

        nextsprite.setColor(opacitynone);
        prevsprite.setColor(opacitynone);
        playsprite.setColor(opacitynone);
        pausesprite.setColor(opacitynone);

        // setting the position of control logos -------------------
        nextsprite.setPosition(1618, 181);
        prevsprite.setPosition(1618, 181);
        playsprite.setPosition(1038, 89);
        pausesprite.setPosition(1038, 101);




        //fitting backgrounds to full scale ------------------------
        bckgrndsprite.setScale(
            float(window.getSize().x) / bckgrndsprite.getLocalBounds().width,
            float(window.getSize().y) / bckgrndsprite.getLocalBounds().height
        );
        pause_bckgrndsprite.setScale(
            float(window.getSize().x) / pause_bckgrndsprite.getLocalBounds().width,
            float(window.getSize().y) / pause_bckgrndsprite.getLocalBounds().height
        );

        // loading fonts ---------------------------------
        if (!ChakReg.loadFromFile("fonts/ChakraPetch/ChakraPetch-Regular.ttf") ||
                !chakBold.loadFromFile("fonts/ChakraPetch/ChakraPetch-SemiBoldItalic.ttf") ||
                !monstFontItal.loadFromFile("fonts/Montserrat/Montserrat-Italic.ttf") ||
                !monstFontReg.loadFromFile("fonts/Montserrat/Montserrat-Regular.ttf")            
                ){ // load font files
            std::cerr << "Failed to load font file!" << std::endl;
            
        }

        
        artisttext.setPosition(1043, 178);
        albumtext.setPosition(1048, 309);
        songtext.setPosition(1045, 265);

        
        next1text.setPosition(1057, 452);
        next1typetext.setPosition(1631, 452);
        next1text.setFillColor(offwhite);
        next1typetext.setFillColor(greywhite);

      
        next2text.setPosition(1057, 506);
        next2typetext.setPosition(1578, 506);
        next2text.setFillColor(offwhite);
        next2typetext.setFillColor(greywhite);

   
        next3text.setPosition(1057, 560);
        next3typetext.setPosition(1500, 560);
        next3text.setFillColor(offwhite);
        next3typetext.setFillColor(greywhite);


        next4text.setPosition(1057, 615);
        next4typetext.setPosition(1448, 615);
        next4text.setFillColor(offwhite);
        next4typetext.setFillColor(greywhite);

        

        
    }
    
    void setCurrentSong(std::string newartist, std::string newsong, std::string newalbum){
        artist = newartist;
        song = newsong;
        album = newalbum;
        artisttext = sf::Text (artist, monstFontItal, 60);
        albumtext = sf::Text (album, monstFontReg, 20);
        songtext = sf::Text (song, chakBold, 30);
        artisttext.setPosition(1043, 178);
        albumtext.setPosition(1048, 309);
        songtext.setPosition(1045, 265);
        //////////resume here////////////////
        // downloadCover(artlink,"" );s
        // cover = sf::Texture ();
        // texture.loadFromMemory(myrequest.result(), myrequest.size());
        // coversprite.setTexture()


    }
    
    
    void setNext(std::string newartist, std::string newsong, std::string type, int numnext){
        std::string printstring ="";
        printstring = newartist + " - " + newsong;
        // if (printstring.length()>22){
        //     printstring = printstring.substr(0,22);
        //     printstring += "...";
        // }
        if (numnext == 1){
            if (printstring.length()>33){
            printstring = printstring.substr(0,33);
            printstring += "...";
            }
            next1text = sf::Text (printstring, ChakReg, 30);
            next1typetext = sf::Text (type, ChakReg, 30);
            next1text.setPosition(1057, 452);
            next1typetext.setPosition(1631, 452);
            next1text.setFillColor(offwhite);
            next1typetext.setFillColor(greywhite);
        }
        else if (numnext == 2){
            if (printstring.length()>30){
            printstring = printstring.substr(0,30);
            printstring += "...";
            }
            next2text = sf::Text (printstring, ChakReg, 30);
            next2typetext = sf::Text (type, ChakReg, 30);
            next2text.setPosition(1057, 506);
            next2typetext.setPosition(1578, 506);
            next2text.setFillColor(offwhite);
            next2typetext.setFillColor(greywhite);        
        }
        else if (numnext == 3){
            if (printstring.length()>25){
            printstring = printstring.substr(0,25);
            printstring += "...";
            }
            next3text = sf::Text (printstring, ChakReg, 30);
            next3typetext = sf::Text (type, ChakReg, 30);
            next3text.setPosition(1057, 560);
            next3typetext.setPosition(1500, 560);
            next3text.setFillColor(offwhite);
            next3typetext.setFillColor(greywhite);
            
        }
        else if (numnext == 4){
            if (printstring.length()>22){
            printstring = printstring.substr(0,22);
            printstring += "...";
            }
            next4text = sf::Text (printstring, ChakReg, 30);
            next4typetext = sf::Text (type, ChakReg, 30);
            next4text.setPosition(1057, 615);
            next4typetext.setPosition(1448, 615);
            next4text.setFillColor(offwhite);
            next4typetext.setFillColor(greywhite);
            
        }
        else {
            std::cerr << "Wrong number specified for upnext!" << std::endl;
            return;
        }

    }


    void changeElement(sf::Sprite& background, sf::Texture& texture, const std::string& filename) {
        if (!texture.loadFromFile(filename)) {
            std::cerr << "Failed to load background file: " << filename << std::endl;
            return;
        }
        background.setTexture(texture);
    }

    void setPauseScreen(){
        bckgrndsprite.setTexture(pause_bckgrnd);
        pausesprite.setColor(opacityfull);
        if (vistimer.getElapsedTime().asSeconds() > 3) {
            pausesprite.setColor(opacitynone);
            vistimer.restart();
            pausecounter = 2;
        }
        
        
    }
    
    void setPlayScreen(){
        bckgrndsprite.setTexture(bckgrnd);
        playsprite.setColor(opacityfull);
        if (vistimer.getElapsedTime().asSeconds() > 3) {
            playsprite.setColor(opacitynone);
            vistimer.restart();
            resumecounter = 2;
        }
        
        
    }

    void flashNextLogo(){
        if (nextcounter == 0){
            nexttimer.restart();
            nextsprite.setColor(opacityfull);
            nextcounter += 2;
        }
        else{
            if (nexttimer.getElapsedTime().asSeconds() > 2) {
                nextsprite.setColor(opacitynone);
                nextcounter = 0;
            }

        }
        
        
        
    }

    void flashPrevLogo(){
        if (prevcounter == 0){
            prevtimer.restart();
            prevsprite.setColor(opacityfull);
            prevcounter += 2;
        }
        else{
            if (prevtimer.getElapsedTime().asSeconds() > 2) {
                prevsprite.setColor(opacitynone);
                prevcounter = 0;
            }

        }
        
        
        
    }



    void runScreen(){

        //setting textures w/ error checking------------------------
        sf::Texture coverShadow, lPlant, lPlantDs, rPlant, line, upnextBars;
        if (
            !coverShadow.loadFromFile("assets/cover-shadow.png") ||
            !lPlant.loadFromFile("assets/left-plant.png") ||
            !lPlantDs.loadFromFile("assets/left-plant-ds.png") ||
            !rPlant.loadFromFile("assets/right-plant.png") ||
            !line.loadFromFile("assets/line.png") ||
            !upnextBars.loadFromFile("assets/upnext.png"))
            // load image file
        {
            std::cerr << "Failed to load image assets!" << std::endl;
            
        }

        //setting sprites -------------------------------------
        sf::Sprite coversprite(cover);
        coversprite.setPosition(192, 101);

        sf::Sprite coverShadowsprite(coverShadow);
        coverShadowsprite.setPosition(192, 20);

        sf::Sprite lPlantsprite(lPlant);
        lPlantsprite.setPosition(0, 478);

        sf::Sprite lPlantDssprite(lPlantDs);
        lPlantDssprite.setPosition(0, 455);

        sf::Sprite rPlantsprite(rPlant);
        rPlantsprite.setPosition(442, 653);

        sf::Sprite linesprite(line);
        linesprite.setPosition(1053, 253);

        sf::Sprite upnextBarssprite(upnextBars);
        upnextBarssprite.setPosition(1038, 448);

    

        
        

        //setting static text positions ---------------------------------

        sf::Text nexttext("Up Next", ChakReg, 30);
        nexttext.setPosition(1053, 401);
        nexttext.setFillColor(black);

        // sf::Text next1text("Lana Del Rey - NFR", ChakReg, 30);
        // sf::Text next1typetext("album", ChakReg, 30);
        // next1text.setPosition(1057, 452);
        // next1typetext.setPosition(1631, 452);
        // next1text.setFillColor(offwhite);
        // next1typetext.setFillColor(greywhite);

        // sf::Text next2text("Drake - Hot Line Bling", ChakReg, 30);
        // sf::Text next2typetext("single", ChakReg, 30);
        // next2text.setPosition(1057, 506);
        // next2typetext.setPosition(1578, 506);
        // next2text.setFillColor(offwhite);
        // next2typetext.setFillColor(greywhite);

        // sf::Text next3text("Spotify Lofi Stud...", ChakReg, 30);
        // sf::Text next3typetext("playlist", ChakReg, 30);
        // next3text.setPosition(1057, 560);
        // next3typetext.setPosition(1500, 560);
        // next3text.setFillColor(offwhite);
        // next3typetext.setFillColor(greywhite);

        // sf::Text next4text("Parcels - Vol.1", ChakReg, 30);
        // sf::Text next4typetext("playlist", ChakReg, 30);
        // next4text.setPosition(1057, 615);
        // next4typetext.setPosition(1448, 615);
        // next4text.setFillColor(offwhite);
        // next4typetext.setFillColor(greywhite);





        int nextcallcounter = 0;
        int prevcallcounter = 0;
        sf::Clock timer;
        timer.restart();

        while (window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            if (controls.isPause()){
                resumecounter =0;
                if (pausecounter == 2){

                }
                else if (pausesprite.getColor() == opacityfull){
                    setPauseScreen();
                }
                
                else{
                    vistimer.restart();
                    setPauseScreen();

                }
                
                
            }
            else{
                pausecounter = 0;
                if (resumecounter == 2){

                }
                else if (playsprite.getColor() == opacityfull){
                    setPlayScreen();
                }
                
                else{
                    vistimer.restart();
                    setPlayScreen();

                }

            }

            if (nextsprite.getColor() == opacityfull){
                flashNextLogo();

            }

            if (prevsprite.getColor() == opacityfull){
                flashPrevLogo();

            }
            
            //------------Test Cases ----------------------
            if (timer.getElapsedTime().asSeconds() > 3){
                controls.setPause(true);
            }
            if (timer.getElapsedTime().asSeconds() > 12){
                controls.setPause(false);
            }
            
            if (timer.getElapsedTime().asSeconds() > 15){
                if (nextcallcounter == 0){
                    flashNextLogo();
                    nextcallcounter++;
                }
                
            }

            if (timer.getElapsedTime().asSeconds() > 20){
                if (prevcallcounter == 0){
                    flashPrevLogo();
                    prevcallcounter++;
                }
                
            }
            

            

            window.clear();
            //drawing images --------------------------------
            window.draw(bckgrndsprite);
            window.draw(nextsprite);
            window.draw(prevsprite);
            window.draw(playsprite);
            window.draw(pausesprite);

            window.draw(coverShadowsprite);
            window.draw(coversprite);
            window.draw(lPlantDssprite);
            window.draw(lPlantsprite);
            window.draw(rPlantsprite);
            window.draw(linesprite);
            window.draw(upnextBarssprite);

            //drawing texts --------------------------------
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
            


            // float time = timer.getElapsedTime().asSeconds();
            


            window.display();

        }
    }


};

int main(){
    Controls& controls = Controls::getInstance();

    sf::Clock timer;
    timer.restart();

    Screen gui (1920, 1080, "GUI window", "w");
    gui.setNext("Eminim", "83 balls", "album", 1);
    gui.setNext("50 Cent", "In the club Riding Balls", "single", 2);
    gui.setNext("Sharika", "Hip are liars", "playlist", 3);
    gui.runScreen();


    // std::this_thread::sleep_for(std::chrono::seconds(5)); 
    // gui.setPause(true);




    return 0;
}









