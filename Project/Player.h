/*
 HNR CSCE 121-200, Fall 2016, Final Project
 Author: Megan Grahmann, Clare Lamers, Josiah Coad
 CODE DESCRIPTION: This code gives backend data management
 						 for the list of players.
*/

// "lowest level" h file... encapsulated by the PlayerList
#include "std_lib_facilities_4.h"

// import guards
#ifndef PLAYER_H
#define PLAYER_H

struct Player{
	// constructor allows an empty initialization of this class
	Player(){} 
	// constructor for making a new player with player info
	Player(string name,     // player name
	 		 string picture,  // picture name incl extension
	 		 vector<int> scores) // a vector of existing scores
	// body of constructor
	{
		this -> name = name;
		this -> picture = picture;
		this -> scores = scores;
		topscore = 0;
		set_topscore(); 
	}
	
	// get/set functions for data members
	void set_name(string name){ this -> name = name; }
	void set_picture(string picture){ this -> picture = picture; }
	string get_name() { return name; }
	string get_picturepath() { return (picfolder + picture); }
	string get_picture() { return picture; }
	int get_topscore() { return topscore; }
	vector<int> get_scores() { return scores; }

	// string of profile picture folder... 
	// picture name gets concatenated to this 
	string picfolder = "./profile_pics/";

	// used to add a score to a player
	void addscore(const int& score){
		if (score > topscore) topscore = score;
		scores.push_back(score);
	}

	private:
	// sets member variable "topscore" from 
	// the players vector of existing scores
	void set_topscore(){
		for (int s : scores)
			if (s > topscore)
				topscore = s;
	}

	// private member variables accessed through get/set
	string name, picture;
	int topscore;
	vector<int> scores;
};

#endif