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
		// only adds new line if this player isnt the last one
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
	// returns the index of the player searched by name
	int find(string name){
		for (int i = 0; i < players.size(); ++i){
			if (name == players[i].get_name()) return i;
		}
		return -1; // person not found
	}

	// adds a player with a name, path to their picture and an empty vector of scores
	void add(string name, string picturepath){
		if (find(name) != -1) error("Person already added.");
		Player p(name, picturepath, {}); // player starts out with no scores
		players.push_back(p);
	}

	private:
	string datafile;
	Player highest_scorer;
	vector<Player> players;
};

int main(){
	string datafile = "testfile.txt"; // stores names, picturepaths and scores
	PlayersList pl(datafile); // import this data into an instance of PlayersList
	// pl.add("newguy", "newpicture");
	return 0;
}
