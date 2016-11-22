#include "std_lib_facilities_4.h"

#ifndef PLAYER_H
#define PLAYER_H

struct Player{
	Player(){} // allows an empty initialization of this class
	Player(string name,
	 		 string picturepath,
	 		 vector<int> scores){
		this -> name = name;
		this -> picturepath = picturepath;
		this -> scores = scores;
		topscore = 0;
		set_topscore();
	}
	// convenience functions 
	void set_name(string name){ this -> name = name; }
	void set_picture(string picturepath){ this -> picturepath = picturepath; }
	string get_name() { return name; }
	string get_picturepath() { return picturepath; }
	int get_topscore() { return topscore; }
	vector<int> get_scores() { return scores; }

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

	string name, picturepath;
	int topscore;
	vector<int> scores;
};

#endif