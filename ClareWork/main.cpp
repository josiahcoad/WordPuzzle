#include "game.h"
#include "highscore.h"
#include "megan_project.h"
#include "PlayerList.h"

string nextwindow="main";

//function enter_main changes the window to the main window
int enter_main(PlayerList& players){
  Main_window win(Point(100,100),600,400,"Word Puzzle", nextwindow, players);
  return gui_main();
}

//function enter_highscore changes the window to the high score window
int enter_highscore(PlayerList& players){
	Highscore_window win(Point(100,100),600,400,"High score!", players);
  nextwindow = "main";
	return gui_main();	
}

//function enter_game changes the window to the game window
int enter_game(PlayerList& players){
   game_window win(Point(100,100),600,400,"game window", players);
   nextwindow = "main";
   return gui_main();
}

int main(){
  PlayerList players("players.txt"); //input file
  //calls the functions to change the window screens
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