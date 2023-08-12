/**
    @file GUI.cpp
    @brief This program implements GUI.h. 
    @author Armin Farhang
    @author Brandon Luu
    @date 09/23/2023
*/

#include "GUI.h"
using namespace std;

    

    
GUI::GUI (int width, int height, const std::string& title, const std::string& style): 
    black(0, 0, 0), 
    offwhite(212, 212, 212), 
    greywhite(120, 120, 120),
    songtext("Welcome to Binyl!", monstFontItal, 50),
    artisttext("", chakBold, 30),
    albumtext("Tap a Binyl card to start queuing!", monstFontReg, 20),
    next1text(" -", ChakReg, 30),
    next1usertext("", ChakReg, 30),
    next2text(" -", ChakReg, 30),
    next2usertext("", ChakReg, 30),
    next3text(" -", ChakReg, 30),
    next3usertext("", ChakReg, 30),
    next4text(" -", ChakReg, 30),
    next4usertext("", ChakReg, 30),
    currsong()
    {
        
        
        
        //setting resolution and window type ----------------------------
        if (style =="F" || style == "f"){ //if style = "f" then GUI is fullscreen
            window.create(sf::VideoMode(width, height), title, sf::Style::Fullscreen);
        }
        else{  //else GUI is windowed
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
            std::cerr << "Failed to load default cover image!" << std::endl;
            
            
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

        
        songtext.setPosition(1043, 183);
        artisttext.setPosition(1045, 265);
        albumtext.setPosition(1048, 309);
        
        next1text.setPosition(1057, 452);
        next1usertext.setPosition(1581, 452);
        next1text.setFillColor(offwhite);
        next1usertext.setFillColor(greywhite);
      
        next2text.setPosition(1057, 506);
        next2usertext.setPosition(1548, 506);
        next2text.setFillColor(offwhite);
        next2usertext.setFillColor(greywhite);

        next3text.setPosition(1057, 560);
        next3usertext.setPosition(1428, 560);
        next3text.setFillColor(offwhite);
        next3usertext.setFillColor(greywhite);

        next4text.setPosition(1057, 615);
        next4usertext.setPosition(1428, 615);
        next4text.setFillColor(offwhite);
        next4usertext.setFillColor(greywhite);
    }

    // Reset the GUI to be empty on everything
    void GUI::setEmpty() {
        coversprite.setScale(1, 1);
        setNext("", "", "", 1);
        setNext("", "", "", 2);
        setNext("", "", "", 3);
        setNext("", "", "", 4);
        songtext.setString("Welcome to Binyl!");
        artisttext.setString("Tap a Binyl card to start queuing!");
        albumtext.setString("");
    }
    
    void GUI::setCurrentSong(std::string newartist, std::string newsong, std::string newalbum, std::string coverlink) {
        Curl coverdl(coverlink);
        coverdl.execute();

        cover.loadFromMemory(coverdl.result(), coverdl.size());
        coversprite.setTexture(cover);
        coversprite.setScale(sf::Vector2f((float)(685.0f / cover.getSize().x), (float)(685.0f / cover.getSize().y)));

        songtext.setString(newsong);
        artisttext.setString(newartist);
        albumtext.setString(newalbum);

        //////////resume here////////////////
        // downloadCover(artlink,"" );s
        // cover = sf::Texture ();
        // texture.loadFromMemory(myrequest.result(), myrequest.size());
        // coversprite.setTexture()
    }

    void GUI::setCurrentSong(Song newsong) {
        currsong = newsong;

        Curl coverdl(currsong.getCoverArt());
        coverdl.execute();
        cover.loadFromMemory((void*)coverdl.result(), coverdl.size());
        
        coversprite.setScale((float)685/640, (float)685/640);

        cout << coversprite.getScale().x << endl;

        songtext.setString(currsong.getName());
        artisttext.setString(currsong.getArtist());
        albumtext.setString(currsong.getAlbum());
    }

    void GUI::setNext(vector<Song> next4) {
        // Reset everything first
        setNext("", "", "", 1);
        setNext("", "", "", 2);
        setNext("", "", "", 3);
        setNext("", "", "", 4);

        if (!next4.empty()){
            int amt = next4.size();
            if (amt >= 4) amt = 4;
            for (int i =0; i != amt; i++){
                setNext(next4[i].getArtist(), next4[i].getName(), next4[i].getUser().getUsername(), i+1);
            }
        }
    }

    
    
    void GUI::setNext(std::string newartist, std::string newsong, std::string username, int numnext){
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

            next1text.setString(printstring);
            next1usertext.setString(username);
        }
        else if (numnext == 2){
            if (printstring.length()>30){
            printstring = printstring.substr(0,30);
            printstring += "...";
            }
            
            next2text.setString(printstring);
            next2usertext.setString(username);      
        }
        else if (numnext == 3){
            if (printstring.length()>25){
            printstring = printstring.substr(0,25);
            printstring += "...";
            }
            next3text.setString(printstring);
            next3usertext.setString(username);
            
        }
        else if (numnext == 4){
            if (printstring.length()>22){
            printstring = printstring.substr(0,22);
            printstring += "...";
            }
            next4text.setString(printstring);
            next4usertext.setString(username);
            
        }
        else {
            std::cerr << "Wrong number specified for upnext!" << std::endl;
            return;
        }

    }


    void GUI::setNext(Song song, int numnext){
        std::string newartist = song.getArtist();
        std::string newsong = song.getName();
        string username = song.getUser().getUsername();
        //std::string type = song.getType();

        std::string printstring ="";
        printstring = newartist + " - " + newsong;

        if (numnext == 1){
            if (printstring.length()>33){
                printstring = printstring.substr(0,33);
                printstring += "...";
            }

            next1text.setString(printstring);
            next1usertext.setString(username);
        }
        else if (numnext == 2){
            if (printstring.length()>30){
            printstring = printstring.substr(0,30);
            printstring += "...";
            }
            
            next2text.setString(printstring);
            next2usertext.setString(username);      
        }
        else if (numnext == 3){
            if (printstring.length()>25){
            printstring = printstring.substr(0,25);
            printstring += "...";
            }
            next3text.setString(printstring);
            next3usertext.setString(username);
            
        }
        else if (numnext == 4){
            if (printstring.length()>22){
            printstring = printstring.substr(0,22);
            printstring += "...";
            }
            next4text.setString(printstring);
            next4usertext.setString(username);
            
        }
        else {
            std::cerr << "Wrong number specified for upnext!" << std::endl;
            return;
        }

    }

    void GUI::changeElement(sf::Sprite& background, sf::Texture& texture, const std::string& filename) {
        if (!texture.loadFromFile(filename)) {
            std::cerr << "Failed to load background file: " << filename << std::endl;
            return;
        }
        background.setTexture(texture);
    }
    // void changeElement(sf::Sprite& background, sf::Texture& texture, std::string& filename) {
    //     if (!texture.loadFromMemory(myrequest.result(), myrequest.size())) {
    //         std::cerr << "Failed to load background file: " << filename << std::endl;
    //         return;
    //     }
    //     background.setTexture(texture);
    // }

    void GUI::setPauseScreen(){
        bckgrndsprite.setTexture(pause_bckgrnd);
        pausesprite.setColor(opacityfull);
        if (vistimer.getElapsedTime().asSeconds() > 3) {
            pausesprite.setColor(opacitynone);
            vistimer.restart();
            pausecounter = 2;
        }
        
        
    }
    
    void GUI::setPlayScreen(){
        bckgrndsprite.setTexture(bckgrnd);
        playsprite.setColor(opacityfull);
        if (vistimer.getElapsedTime().asSeconds() > 3) {
            playsprite.setColor(opacitynone);
            vistimer.restart();
            resumecounter = 2;
        }
        
        
    }

    void GUI::flashNextLogo(){
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

    void GUI::flashPrevLogo(){
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



    void GUI::runScreen(){

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
        // sf::Text next1usertext("album", ChakReg, 30);
        // next1text.setPosition(1057, 452);
        // next1usertext.setPosition(1631, 452);
        // next1text.setFillColor(offwhite);
        // next1usertext.setFillColor(greywhite);

        // sf::Text next2text("Drake - Hot Line Bling", ChakReg, 30);
        // sf::Text next2usertext("single", ChakReg, 30);
        // next2text.setPosition(1057, 506);
        // next2usertext.setPosition(1578, 506);
        // next2text.setFillColor(offwhite);
        // next2usertext.setFillColor(greywhite);

        // sf::Text next3text("Spotify Lofi Stud...", ChakReg, 30);
        // sf::Text next3usertext("playlist", ChakReg, 30);
        // next3text.setPosition(1057, 560);
        // next3usertext.setPosition(1500, 560);
        // next3text.setFillColor(offwhite);
        // next3usertext.setFillColor(greywhite);

        // sf::Text next4text("Parcels - Vol.1", ChakReg, 30);
        // sf::Text next4usertext("playlist", ChakReg, 30);
        // next4text.setPosition(1057, 615);
        // next4usertext.setPosition(1448, 615);
        // next4text.setFillColor(offwhite);
        // next4usertext.setFillColor(greywhite);





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
            
            /*
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
            */
            

            

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
            window.draw(next1usertext);
            window.draw(next2text);
            window.draw(next2usertext);
            window.draw(next3text);
            window.draw(next3usertext);
            window.draw(next4text);
            window.draw(next4usertext);
            


            // float time = timer.getElapsedTime().asSeconds();
            


            window.display();

        }
    }





// request myrequest("https://i.scdn.co/image/ab67616d0000b273c18cc9d6fcea1478b1257678");
//     myrequest.execute();

//     RenderWindow window(VideoMode(600, 600), "SFML works!");
//     Texture texture;
//     texture.loadFromMemory(myrequest.result(), myrequest.size());
