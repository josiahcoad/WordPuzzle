#include "std_lib_facilities_4.h"

struct Player{
	Player(){} // allows an empty initialization of this class
	Player(string name, string picturepath, vector<int> scores){
		this -> name = name;
		this -> picturepath = picturepath;
		this -> scores = scores;
	}
	// convenience functions 
	string get_name() { return name; }
	string get_picturepath() { return picturepath; }
	vector<int> get_scores() { return scores; }

	// used to add a score to a player
	void addscore(const int& score){
		scores.push_back(score);
	}

	private:
	string name, picturepath;
	vector<int> scores;
};