#include <iostream>
#include <string>
#include <vector>

#include "Song.h"

class Playlist{
	private:
		/*struct Song{
			string songTitle;
			string artistName;
			int position;
		}*/
		
		vector<Song*> song_list;
		double length;
	
	public:
		Playlist();
		
		Playlist(const Playlist& p);
		
		~Playlist();

		bool addSong(const string title, const string artist);
		
		string returnTitle(const int n);
		
		string returnArtist(const int n);
		
		bool eraseSong(const int n);
		
		bool playSong(const int n);
		
		void print();
		
		void destroy();
};