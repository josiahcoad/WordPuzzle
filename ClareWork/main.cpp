#include "game.h"
#include "highscore.h"
#include "megan_project.h"
#include "PlayerList.h"

string nextwindow="main";


int enter_game(){
   game_window win(Point(100,100),600,400,"game window", nextwindow);
   nextwindow = "main";
   return gui_main();
}

int enter_highscore(){
	Highscore_window win(Point(100,100),600,400,"High score!");
  nextwindow = "main";
	return gui_main();	
}

int enter_main(){
  Main_window win(Point(100,100),600,400,"Word Puzzle", nextwindow);
  return gui_main();
}


int main(){
  // PlayersList players("players.txt");
  // players["Josiah Coad"];
  while (nextwindow != "quit"){
    if      (nextwindow == "main")      enter_main();
    else if (nextwindow == "highscore") enter_highscore();
    else if (nextwindow == "game")      enter_game();
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