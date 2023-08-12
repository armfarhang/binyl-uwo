all: SpotifyWebRequest.o SpotifyService.o ./RFIDModule/RFIDModule.o Binyl.o
	make Curl
	make SpotifyWebRequest
	make SpotifyService
	make User
	make Song
	make Controls
	make GUI
	make Binyl
	g++ -o Binyl Curl.o SpotifyWebRequest.o SpotifyService.o ./RFIDModule/*.c ./RFIDModule/*.cpp User.o Song.o Controls.o GUI.o Binyl.o -Wno-write-strings -lcurl -lpthread -lbcm2835 -lsfml-graphics -lsfml-window -lsfml-system -std=c++11

build:
	g++ -o Binyl Curl.o SpotifyWebRequest.o SpotifyService.o ./RFIDModule/*.c ./RFIDModule/*.cpp User.o Song.o Controls.o GUI.o Binyl.o -Wno-write-strings -lcurl -lpthread -lbcm2835 -lsfml-graphics -lsfml-window -lsfml-system -std=c++11

Curl: Curl.cpp Curl.h
	g++ -c Curl.cpp

SpotifyWebRequest: SpotifyWebRequest.cpp SpotifyWebRequest.h
	g++ -c SpotifyWebRequest.cpp -Wno-write-strings

SpotifyService: SpotifyService.cpp SpotifyService.h
	g++ -c SpotifyService.cpp -Wno-write-strings

User: User.cpp User.h
	g++ -c User.cpp User.h

Song: Song.cpp Song.h
	g++ -c Song.cpp

Controls: Controls.cpp Controls.h
	g++ -c Controls.cpp

GUI: GUI.cpp GUI.h
	g++ -c GUI.cpp

Binyl: Binyl.cpp
	g++ -c Binyl.cpp -lpthread -Wno-write-strings

screen:
	g++ Screen.cpp Controls.cpp -o screen-app -lsfml-graphics -lsfml-window -lsfml-system 

testgpt:
	g++ testgpt.cpp Controls.cpp Curl.cpp Song.cpp -o testgpt-app -lsfml-graphics -lsfml-window -lsfml-system -lcurl

clean:
	rm Binyl
	rm -f *.o
	rm -f *app
	rm ./RFIDModule/*.o