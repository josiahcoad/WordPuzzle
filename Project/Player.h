#include "std_lib_facilities_4.h"

#ifndef PLAYER_H
#define PLAYER_H

struct Player{
	Player(){} // allows an empty initialization of this class
	Player(string name,
	 		 string picture,
	 		 vector<int> scores){
		this -> name = name;
		this -> picture = picture;
		this -> scores = scores;
		topscore = 0;
		set_topscore();
	}
	// convenience functions 
	void set_name(string name){ this -> name = name; }
	void set_picture(string picture){ this -> picture = picture; }
	string get_name() { return name; }
	string get_picturepath() { return (picfolder + picture); }
	string get_picture() { return picture; }
	int get_topscore() { return topscore; }
	vector<int> get_scores() { return scores; }

	// profile picture folder
	string picfolder = "./profile_pics/";

	// used to add a score to a player
	void addscore(const int& score){
		if (score > topscore) topscore = score;
		scores.push_back(score);
	}

	private:
	void set_topscore(){
		for (int s : scores)
			if (s > topscore)
				topscore = s;
	}

	string name, picture;
	int topscore;
	vector<int> scores;
};

#endif