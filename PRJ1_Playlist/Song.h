#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Song { 
	public:
		string songTitle;
		string artistName;
		int position;
		Song();
		Song(const string& Title, const string& Artist, const int number);
		
		~Song();
		
		void setSongTitle(const string& Title);
		
		void setArtistName(const string& Artist);
		
};