#include "std_lib_facilities_4.h"
#include "Player.h"

// use to make a string out a vector of ints
// only used by the next overrider
ostream& operator<<(ostream& os, vector<int> vi){
	for (int i : vi) os << i << " ";
	return os;
}

// use to cout player info or write data back to file
ostream& operator<<(ostream& os, vector<Player> players){
	for (int i = 0; i < players.size(); ++i){
		os << players[i].get_name() << "\n";
		os << players[i].get_picturepath() << "\n";
		os << players[i].get_scores();
		// only adds new line if this player isnt the last player
		os << (i == (players.size() - 1) ? "" : "\n");
	}
	return os;
}

struct PlayersList{
	// constructor reads data from file
	PlayersList(string import_filename){
		datafile = import_filename; // used later for writing back to the file
		readfile(import_filename); 
	}
	~PlayersList(){
		writefile();
	}


	/*-------------------------------------------------------------------------------*/
	/* To Read Files */
	// makes a vector of ints from a space seperated string
	// used to get a player's scores from a line in the file
	vector<int> mk_vector(const string& scores_s){
	   vector<int> scores;
		istringstream scores_ss(scores_s);
		int score;
		while (scores_ss >> score){
			scores.push_back(score);
		}
		return scores;
	}


	void readfile(string filename){
		// get info from file
		ifstream is(filename);
		if (!is) error("There is no such file in the current folder.");
		
		string name, picturepath, scores_s;
		cout << "......Imported Players......\n";
		while (!is.eof()){
			getline(is, name);
			getline(is, picturepath);
			getline(is, scores_s);
			vector<int> scores = mk_vector(scores_s);
			players.push_back(Player(name, picturepath, scores));
		}

		is.close();
		// cout the imported players' names
		for (Player p : players) cout << p.get_name() << "\n";
	}

	/*-------------------------------------------------------------------------------*/
	/* To Write to Files */

	void writefile(){
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
	Player& operator[](string name){
		for (int i = 0; i < players.size(); ++i)
			if (name == players[i].get_name()) return players[i];
		error("Not found by that name.");
	}

	bool exists(string name){
		for (Player p : players)
			if (name == p.get_name()) return true;
		return false;
	}

	// could maybe be a better method of getting the highscore...
	Player get_highest_scorer(){
		int highscore = 0;
		for (Player p : players){
			for (int score : p.get_scores()){
				if (score > highscore) highest_scorer = p;
			}
		}
		if (highscore > 0) return highest_scorer;
		error("There is no highscore.");
	}

	void add(string name, string picturepath){
		if (exists(name)) error(name + " already added.");
		Player p(name, picturepath, {}); // player starts out with no scores
		players.push_back(p);
	}

	private:
	string datafile;
	Player highest_scorer;
	vector<Player> players;
};