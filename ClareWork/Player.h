#include "std_lib_facilities_4.h"

// ostream& operator<<(ostream& os, Player& p){
// 		os << p.get_name() << "\n";
// 		os << p.get_picturepath() << "\n";
// 		os << p.get_scores();
// 		// only adds new line if this player isnt the last player
// 		os << (i == (p.size() - 1) ? "" : "\n");
// 	return os;
// }

struct Player{
	Player(){} // allows an empty initialization of this class
	Player(string name,
	 		 string picturepath,
	 		 vector<int> scores){
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