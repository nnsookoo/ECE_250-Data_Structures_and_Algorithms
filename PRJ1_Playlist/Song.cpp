#include "Song.h"

using namespace std;

Song::Song(){
}

Song::Song(const string& Title, const string& Artist, const int number){
	songTitle = Title;
	artistName = Artist;
	position = number;
}

Song::~Song(){
	songTitle = " ";
	artistName = " ";
	position = 0;
}

void Song::setSongTitle(const string& Title){
	songTitle = Title;
}

void Song::setArtistName(const string& Artist){
	artistName = Artist;
}