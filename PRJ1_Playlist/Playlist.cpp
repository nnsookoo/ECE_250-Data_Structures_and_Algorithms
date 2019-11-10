#include <iostream>
#include <vector>
#include <string>

#include "Playlist.h"
//#include "Song.h"

Playlist::Playlist(){
	length = 0;
}

Playlist::Playlist(const Playlist &p){
	
	if(!(this->song_list.empty()))
		this->song_list.clear();
	
	this->song_list = p.song_list;
	
	double length_of_p = p.song_list.size();
	
	this->length = length_of_p;

}

Playlist::~Playlist(){
	
	destroy();
	
}

void Playlist::destroy(){
	
	if(!(this->song_list.empty())){
		for(int i = 0; i < song_list.size(); i++)
			delete song_list[i];
	
		this->length = 0;
	}
}

bool Playlist::addSong(const string title, const string artist){
	
	Song* to_add = new Song;
	
	to_add->songTitle = title;
	to_add->artistName = artist;
	
	/*cout << title << endl;
	cout << to_add->songTitle << endl;
	
	cout << artist << endl;
	cout << to_add->artistName << endl;
	*/
	
	// Check if both a title and artist is given.
	// If either isn't given, we cannot input a song
	if(title.empty() || artist.empty())
		return false;
	
	// If playlist is empty, add song to the beginning
	if(this->song_list.empty()){
		this->song_list.push_back(to_add);
		this->length = this->length + 1;
		return true;
	}
	
	else if(!(this->song_list.empty())){
		// Iterate through list to see if there is a song already existing of that name and artist
		bool found_same_song = 0;
		
		for(int i = 0; i < song_list.size(); i++){
			
			Song *to_compare = new Song;
			
			to_compare->songTitle = song_list[i]->songTitle;
			to_compare->artistName = song_list[i]->artistName;
			
			if((to_compare->songTitle == to_add->songTitle)&&(to_compare->artistName == to_add->artistName)){
				found_same_song = found_same_song||1;
				break;
			}
		}
		
		if(found_same_song == 1)
			return false;
		else{
			this->song_list.push_back(to_add);
			this->length = this->length + 1;
			return true;
		}
	}
	
}
		
bool Playlist::eraseSong(const int n){
	
	//Check if n is a negative number
	//Check if n is less than the length of the vector
	double length_of_playlist = this->song_list.size();
	
	if(n <= 0){
		return false;
	}
	
	if(n > length_of_playlist){
		return false;
	}
	
	Song* to_remove = new Song;
	
	to_remove = this->song_list[n-1];
	
	int index_to_remove = n-1;
	
	this->song_list.erase(this->song_list.begin()+index_to_remove);
	
	return true;
}
		
bool Playlist::playSong(const int n){
	
	double length_of_playlist = this->song_list.size();
	
	if(n <= 0)
		return false;
	
	if(n > length_of_playlist)
		return false;
	
	return true;
}

string Playlist::returnTitle(const int n){
	
	Song* to_return = new Song;
	
	to_return = this->song_list[n-1];
	
	string title;	
	title = to_return->songTitle;
	
	return title;
}

string Playlist::returnArtist(const int n){
	
	Song* to_return = new Song;
	
	to_return = this->song_list[n-1];
	
	string artist;
	
	artist = to_return->artistName;
	
	return artist;
}

void Playlist::print(){
	
	int length = song_list.size();
	
	int i = 0;
	
	while(i != length){
		
		Song* to_display = new Song;
		
		to_display = this->song_list[i];
		
		cout << "Song Title: " << to_display->songTitle << endl;
		cout << "Song Artist: " << to_display->artistName << endl;
	
		i++;
	}
	
	cout << endl;
	
}
