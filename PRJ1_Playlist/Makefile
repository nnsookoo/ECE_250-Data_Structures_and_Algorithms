all: playlisttest

playlisttest: playlisttest.cpp
	g++ -std=c++11 -o playlisttest playlisttest.cpp Playlist.h Playlist.cpp Song.h Song.cpp

clean:
	rm *.o playlisttest