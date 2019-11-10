#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "quadtree.cpp"

using namespace std;

int main(){
	
	string oneline;
	Point c = Point(0,0);
	boundary_box bounds = boundary_box(c, 128);
	QuadTree quad(bounds);
	
	while(!cin.eof()){
		string ws_delim = " ";
		string sc_delim = ";";
		
		getline(cin, oneline); //Get the line from the standard input_iterator
		
		//cout  << "Line received: " << oneline << endl;
	
		if((oneline[0]=='s')&&(oneline[1]=='i')){
			//cout << "COMMAND IS: " << oneline << endl;
			int initial = 0;
			cout << "tree size " << quad.size(initial) << endl;
		}
		//else if(oneline.compare("print")==0){ //For some reason, this was not working properly
		else if((oneline[0]=='p')&&(oneline[1]=='r')){
			//cout << "COMMAND IS: " << oneline << endl;
			quad.print();
			cout << endl;
		}
		else if(oneline.compare("clear")==0){
			//cout << "COMMAND IS: " << oneline << endl;
			quad.clear();
			cout << "success" << endl;
		}
		else{
			int length_of_line = oneline.length(); //Calculate the length of the line
			
			//cout << "LENGTH OF LINE: " << length_of_line << endl;
			
			string copy;
			copy = oneline;
			
			//string characteristic;
			
			//cout << "copy: " << copy << endl; //Check to see if strings copied well
			
			size_t pos_whitespace = copy.find(ws_delim); //Find the position of the whitespace
			
			//cout << pos_whitespace << endl; //Check to see if the position is correct
			
			string command = copy.substr(0, pos_whitespace);
			copy.erase(0, pos_whitespace + ws_delim.length());
			
			if(command.compare("i")==0){
				//cout << "COMMAND IS: " << command << endl;
				
				size_t pos_semicolon1 = copy.find(sc_delim);
				string city_name = copy.substr(0, pos_semicolon1);
				copy.erase(0, pos_semicolon1 + sc_delim.length());
				//cout << "City Name: " << city_name << endl;
				
				size_t pos_semicolon2 = copy.find(sc_delim);
				string x_coor = copy.substr(0, pos_semicolon2);
				copy.erase(0, pos_semicolon2 + sc_delim.length());
				float x_coordinate = stof(x_coor);
				//cout << "X: " << x_coordinate << endl;
				
				size_t pos_semicolon3 = copy.find(sc_delim);
				string y_coor = copy.substr(0, pos_semicolon3);
				copy.erase(0, pos_semicolon3 + sc_delim.length());
				float y_coordinate = stof(y_coor);
				//cout << "Y: " << y_coordinate << endl;
				
				size_t pos_semicolon4 = copy.find(sc_delim);
				string pop = copy.substr(0, pos_semicolon4);
				copy.erase(0, pos_semicolon4 + sc_delim.length());
				float population = stof(pop);
				//cout << "Population: " << population << endl;
				
				size_t pos_semicolon5 = copy.find(sc_delim);
				string cost = copy.substr(0, pos_semicolon5);
				copy.erase(0, pos_semicolon5 + sc_delim.length());
				float cost_of_living = stof(cost);
				//cout << "Cost of living: " << cost_of_living << endl;
				
				//cout << copy << endl;
				float net_avg_salary = stof(copy);
				//cout << "Net Average Salary: " << net_avg_salary << endl;
				
				Node* to_insert = new Node(Point(x_coordinate, y_coordinate), city_name, population, cost_of_living, net_avg_salary);
				
				//Why is it the same as Node to_insert(Point....) then quad.insert(&to_insert)
				
				if(quad.insert(to_insert))
					cout << "success" << endl;
				else
					cout << "failure" << endl;
				
				//cout << endl;
			}
			else if(command.compare("q_max")==0){
				//cout << "COMMAND IS: " << command << endl;
				
				size_t pos_semicolon1 = copy.find(sc_delim);
				string x_coor = copy.substr(0, pos_semicolon1);
				copy.erase(0, pos_semicolon1 + sc_delim.length());
				float x_coordinate = stof(x_coor);
				//cout << "X: " << x_coordinate << endl;
				
				size_t pos_semicolon2 = copy.find(sc_delim);
				string y_coor = copy.substr(0, pos_semicolon2);
				copy.erase(0, pos_semicolon2 + sc_delim.length());
				float y_coordinate = stof(y_coor);
				//cout << "Y: " << y_coordinate << endl;
				
				Point *to_find = new Point(x_coordinate,y_coordinate);
				
				size_t pos_semicolon3 = copy.find(sc_delim);
				string direction = copy.substr(0, pos_semicolon3);
				copy.erase(0, pos_semicolon3 + sc_delim.length());
				//cout << "Direction: " << direction << endl;
				
				string characteristic = copy.substr(0,1);
				//cout << "Characteristic: " << characteristic << endl;
				
				if(characteristic == "p")
					quad.query_attribute(to_find, direction, "max", "p");
				else if(characteristic == "r")
					quad.query_attribute(to_find, direction, "max", "r");
				else if(characteristic == "s"){
					quad.query_attribute(to_find, direction, "max", "s");
				}
				//cout << endl;
			}
			else if(command.compare("q_min")==0){
				//cout << "COMMAND IS: " << command << endl;
				
				size_t pos_semicolon1 = copy.find(sc_delim);
				string x_coor = copy.substr(0, pos_semicolon1);
				copy.erase(0, pos_semicolon1 + sc_delim.length());
				float x_coordinate = stof(x_coor);
				//cout << "X: " << x_coordinate << endl;
				
				size_t pos_semicolon2 = copy.find(sc_delim);
				string y_coor = copy.substr(0, pos_semicolon2);
				copy.erase(0, pos_semicolon2 + sc_delim.length());
				float y_coordinate = stof(y_coor);
				//cout << "Y: " << y_coordinate << endl;
				
				Point *to_find = new Point(x_coordinate,y_coordinate);
				
				size_t pos_semicolon3 = copy.find(sc_delim);
				string direction = copy.substr(0, pos_semicolon3);
				copy.erase(0, pos_semicolon3 + sc_delim.length());
				//cout << "Direction: " << direction << endl;
				string characteristic = copy.substr(0,1);
				//cout << "Characteristic: " << characteristic << endl;
				
				if(characteristic == "p")
					quad.query_attribute(to_find, direction, "min", "p");
				else if(characteristic == "r")
					quad.query_attribute(to_find, direction, "min", "r");
				else if(characteristic == "s")
					quad.query_attribute(to_find, direction, "min", "s");
				
				//cout << endl;
			}
			else if(command.compare("q_total")==0){
				//cout << "COMMAND IS: " << command << endl;
				
				size_t pos_semicolon1 = copy.find(sc_delim);
				string x_coor = copy.substr(0, pos_semicolon1);
				copy.erase(0, pos_semicolon1 + sc_delim.length());
				float x_coordinate = stof(x_coor);
				//cout << "X: " << x_coordinate << endl;
				
				size_t pos_semicolon2 = copy.find(sc_delim);
				string y_coor = copy.substr(0, pos_semicolon2);
				copy.erase(0, pos_semicolon2 + sc_delim.length());
				float y_coordinate = stof(y_coor);
				//cout << "Y: " << y_coordinate << endl;
				
				Point *to_find = new Point(x_coordinate,y_coordinate);
				
				size_t pos_semicolon3 = copy.find(sc_delim);
				string direction = copy.substr(0, pos_semicolon3);
				copy.erase(0, pos_semicolon3 + sc_delim.length());
				//cout << "Direction: " << direction << endl;
				
				string characteristic = copy.substr(0,1);
				//cout << "Characteristic: " << characteristic << endl;
				
				if(characteristic.compare("p") == 0)
					quad.query_attribute(to_find, direction, "total", "p");
				else if(characteristic.compare("r") == 0)
					quad.query_attribute(to_find, direction, "total", "r");
				else if(characteristic.compare("s")==0){
					quad.query_attribute(to_find, direction, "total", "s");
				}
				
				//cout << endl;
			}
			else if(command.compare("s")==0){
				//cout << "COMMAND IS: " << command << endl;
				size_t pos_semicolon1 = copy.find(sc_delim);
				string x_coor = copy.substr(0, pos_semicolon1);
				copy.erase(0, pos_semicolon1 + sc_delim.length());
				float x_coordinate = stof(x_coor);
				//cout << "X: " << x_coordinate << endl;
				
				float y_coordinate = stof(copy);
				//cout << "Y: " << y_coordinate << endl;
				
				Point* to_search = new Point(x_coordinate,y_coordinate);
				
				if(quad.search(to_search)){
					cout << "found ";
					quad.return_cityname(to_search);
				}
				else
					cout << "not found" << endl;
				
				//cout << endl;
			}
		}
	}
	
	//return 0;
}
