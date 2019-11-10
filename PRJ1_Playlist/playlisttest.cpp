#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Playlist.h"

using namespace std;

const int MAXLINE = 256;

int main(){
	
	Playlist play_list;
	
	string oneline;
	
	while(!cin.eof()){
		
		string ws_delim = " ";
		string sc_delim = ";";
		
		getline(cin, oneline); //Get the line from standard input
		
		//cout << "string received: " << oneline << endl;
		
		int length_of_line = oneline.length(); //Calculate the length of the line for future reference
		
		string copy;
		copy = oneline; // Make a copy of the line received so as to not change the contents of the original line received
		
		//cout << "copy: " << copy << endl; //Check to see if the strings copied well
		
		size_t pos_whitespace = copy.find(ws_delim); //Find the position of the first whitespace
		
		//cout << pos << endl; //Check to see if the position is correct
		
		string command = copy.substr(0,pos_whitespace); //Copy over the contents from the first position to the position of the whitespace
		
		copy.erase(0, pos_whitespace + ws_delim.length());
		
		//cout << "COMMAND IS: " << command << endl;
		
		/***ADDING A SONG TO THE PLAYLIST***/
		if(command.compare("i")==0){
			
			size_t pos_semicolon = copy.find(sc_delim);
			
			string song_title = copy.substr(0, pos_semicolon);
			
			copy.erase(0, pos_semicolon + sc_delim.length());
			
			//cout << song_title << endl; //Checking to see if song_title copied properly
			
			string song_artist = copy.substr(0, length_of_line);
			
			//cout << song_artist << endl; //Checking to see if song_artist copied properly
			
			if(play_list.addSong(song_title, song_artist)){
				cout << "success" << endl;
			}
			else
				cout << "can not insert " << song_title << ";" << song_artist << endl;
			
			//play_list.print();
		}
		
		/***ERASING A SONG FROM THE PLAYLIST***/
		else if(command.compare("e")==0){
			
			string pos_erase = copy.substr(0, length_of_line);
			
			stringstream erasing(pos_erase); //object from the class stringstream
			
			int position_to_erase = 0;
			erasing >> position_to_erase;
			
			//cout << "Position to erase: " << position_to_erase << endl;
			
			if(play_list.eraseSong(position_to_erase)){
				cout << "success" << endl;
			}
			else
				cout << "could not erase " << position_to_erase << endl;
			
			//play_list.print();
		}
		
		/***PLAYING A SONG FROM THE PLAYLIST***/
		else if(command.compare("p")==0){
			
			string pos_play = copy.substr(0, length_of_line);
			
			stringstream playing(pos_play);
			
			int position_to_play = 0;
			
			playing >> position_to_play;
			
			//cout << "Position to play: " << position_to_play << endl;
			
			if(play_list.playSong(position_to_play)){
				string title;
				title = play_list.returnTitle(position_to_play);
			
				string artist;
				artist = play_list.returnArtist(position_to_play);
				
				cout << "played " << position_to_play << " " << title << ";" << artist << endl;
			}
			else
				cout << "could not play " << position_to_play << endl;
			
			//play_list.print();
		}
	}
}

