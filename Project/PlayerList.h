/*
 HNR CSCE 121-200, Fall 2016, Final Project
 Author: Megan Grahmann, Clare Lamers, Josiah Coad
 CODE DESCRIPTION: This code gives backend data management
 						 for the list of players.
*/

// importing needed header files
#include "std_lib_facilities_4.h"
#include "Player.h"


// import guards
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

	// destructor writes back to file
	~PlayerList(){
		writefile();
	}

	
	// public member functions defined below
	Player& operator[](string name);
	Player get_highest_scorer();
	void add(string name, int init_score, string picture);
	bool exists(string name);

	// data for the current player that is used in a session
	// set / changed when a new name is entered in the Info page
	Player current;
	
	// for if the user doesn't provide a picture
	string missing_pic = "missing.jpeg";

	private:
	// private member functions defined below
	vector<int> mk_vector(const string& scores_s);
	void readfile(string filename);
	void writefile();
	

	// name of the file where the data is stored.
	string datafile;
	// highest player used on highscore page
	Player highest_scorer;
	// the vector that stores all the players
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


// get players from a file
void PlayerList::readfile(string filename){
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

// write updated info back to file
void PlayerList::writefile(){
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

// returns boolean if the player already exists
// used in info page to see if user is returning or new
bool PlayerList::exists(string name){
	for (Player p : players)
		if (name == p.get_name()) return true;
	return false;
}


// used in the highscore page to get the highest scorer
Player PlayerList::get_highest_scorer(){
	int highscore = 0;
	Player highest_scorer("No Highest Scorer!", "missing.jpeg", {});
	for (Player p : players)
		if (p.get_topscore() > highscore){
			highest_scorer = p;
			highscore = p.get_topscore();
		}
	return highest_scorer;
}

// add a player to the vector of players
// used by info page to add if user doesn't exist
void PlayerList::add(string name, int init_score, string picture){
	Player p(name, picture, {init_score});
	players.push_back(p);
	cout << name << " successfully added.\n";
}

#endif