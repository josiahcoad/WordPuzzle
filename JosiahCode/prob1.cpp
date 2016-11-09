#include "std_lib_facilities_4.h"
#include "PlayerList.h"

int main(){
	string datafile = "testfile.txt"; // stores names, picturepaths and scores
	PlayersList pl(datafile);         // import this data into an instance of PlayersList
	pl.add("newguy", "newpicture");   // do all sorts of cool member functions on PlayerList
	pl["Josiah Coad"].addscore(25);   // or index it by name to access a player's functions
	return 0;
}

/*
error handling code
	while (true){
		try{
			PlayersList pl(datafile); // import this data into an instance of PlayersList
		}
		catch(runtime_error& e){
			cerr << e.ehat() << " - try again!"
		}
	}

*/