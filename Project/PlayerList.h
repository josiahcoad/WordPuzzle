#include "std_lib_facilities_4.h"
#include "Player.h"

#ifndef PLAYER_LIST_H
#define PLAYER_LIST_H

// use to make a string out a vector of ints
// only used by the output overrider to write a vector of ints back to the file
ostream& operator<<(ostream& os, vector<int> vi){
	for (int i : vi) os << i << " ";
	return os;
}

// use to cout player info or write data back to file
ostream& operator<<(ostream& os, vector<Player> players){
	for (int i = 0; i < players.size(); ++i){
		os << players[i].get_name() << "\n";
		os << players[i].get_picture() << "\n";
		os << players[i].get_scores();
		// only adds new line if this player isnt the last player
		os << (i == (players.size() - 1) ? "" : "\n");
	}
	return os;
}

// ostream& operator<<(ostream& os, vector<Player> players){
// 	return (operator<<(ostream& os, vector<Player> players))
// }

struct PlayerList{
	// constructor reads data from file
	PlayerList(string import_filename){
		datafile = import_filename; // used later for writing back to the file
		readfile(import_filename); 
	}
	// constructor for initializing empty
	PlayerList(){}

	~PlayerList(){
		writefile();
	}

	
	Player& operator[](string name);
	Player get_highest_scorer();
	void add(string name, int init_score, string picture);
	bool exists(string name);

	string current_name;
	Player current;
	
	// for if the user doesn't provide a picture
	string missing_pic = "missing.jpeg";

	private:
	vector<int> mk_vector(const string& scores_s);
	void readfile(string filename);
	void writefile();
	

	string datafile;
	Player highest_scorer;
	vector<Player> players;
};



/*-------------------------------------------------------------------------------*/
/* To Read Files */
// makes a vector of ints from a space seperated string
// used to get a player's scores from a line in the file
vector<int> PlayerList::mk_vector(const string& scores_s){
   vector<int> scores;
	istringstream scores_ss(scores_s);
	int score;
	while (scores_ss >> score){
		scores.push_back(score);
	}
	return scores;
}


void PlayerList::readfile(string filename){
	// get info from file
	ifstream is(filename);
	if (!is) error("There is no such file in the current folder.");
	
	string name, picture, scores_s;
	cout << "......Imported Players......\n";
	while (!is.eof()){
		getline(is, name);
		getline(is, picture);
		getline(is, scores_s);
		vector<int> scores = mk_vector(scores_s);
		players.push_back(Player(name, picture, scores));
	}

	is.close();
	// cout the imported players' names
	for (Player p : players) cout << p.get_name() << "\n";
}

/*-------------------------------------------------------------------------------*/
/* To Write to Files */

void PlayerList::writefile(){
   // write updated info back to file
	cout << "\n\n";
	cout << "......Exported Players......\n";
	cout << players;
	ofstream outFS(datafile);
	outFS << players; // use the cout overrider I wrote for a vector of players
	outFS.close();
}


/*-------------------------------------------------------------------------------*/
// adds a player with a name, path to their picture and an empty vector of scores
// returns the index of the player searched by name
Player& PlayerList::operator[](string name){
	for (int i = 0; i < players.size(); ++i)
		if (name == players[i].get_name()) return players[i];
	error("Not found by that name.");
}

bool PlayerList::exists(string name){
	for (Player p : players)
		if (name == p.get_name()) return true;
	return false;
}


Player PlayerList::get_highest_scorer(){
	int highscore = 0;
	Player highest_scorer("No Highest Scorer!", "missing.jpeg", {});
	for (Player p : players)
		if (p.get_topscore() > highscore)
			highest_scorer = p;
	return highest_scorer;
}

void PlayerList::add(string name, int init_score, string picture){
	// if (exists(name)) error(name + " already added.");
	// if (exists(name)) players[name].update_picture();
	Player p(name, picture, {init_score}); // player starts out with first score
	players.push_back(p);
	cout << name << " successfully added.\n";
}

#endif