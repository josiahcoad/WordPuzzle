#include "game.h"
#include "highscore.h"
#include "megan_project.h"
#include "PlayerList.h"

string nextwindow="main";


int enter_main(PlayerList& players){
  Main_window win(Point(100,100),600,400,"Word Puzzle", nextwindow, players);
  return gui_main();
}

int enter_highscore(PlayerList& players){
	Highscore_window win(Point(100,100),600,400,"High score!", players);
  nextwindow = "main";
	return gui_main();	
}

int enter_game(PlayerList& players){
   game_window win(Point(100,100),600,400,"game window", players);
   nextwindow = "main";
   return gui_main();
}


int main(){
  PlayerList players("players.txt");
  while (nextwindow != "quit"){
    if      (nextwindow == "main")      enter_main(players);
    else if (nextwindow == "highscore") enter_highscore(players);
    else if (nextwindow == "game")      enter_game(players);
  }
}

/*
catch(exception& e){
 cerr<<"exception: "<<e.what()<<'\n';
 return 1;
}
catch(...){
 cerr<<"some exception\n";
 return 2;
}
}
*/