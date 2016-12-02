/*
 HNR CSCE 121-200, Fall 2016, Final Project
 Author: Megan Grahmann, Clare Lamers, Josiah Coad
 CODE DESCRIPTION: this is the main program for the project
*/

#include "game.h"
#include "highscore.h"
#include "mainmenu.h"
#include "info.h"
#include "PlayerList.h"

// global string that tracks next window
// gets passed by reference to windows for
// them to modify based on buttons presssed
string nextwindow="main";


//function enter_main changes the window to the main window
int enter_main(PlayerList& players){
  Main_window win(Point(100,100),600,400,"Word Puzzle", nextwindow, players);
  return gui_main();
}


//function enter_info changes the window to the info window
int enter_info(PlayerList& players){
  Info_window win(Point(100,100),600,400,"Word Puzzle", players);
  nextwindow = "game";
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
   Game_window win(Point(100,100),600,400,"game window", players);
   nextwindow = "main";
   return gui_main();
}


int main(){
  PlayerList players("players.txt"); //input file name
  //calls the functions to change the window screens
  while (nextwindow != "quit"){
    if      (nextwindow == "main")      enter_main(players);
    else if (nextwindow == "info")      enter_info(players);
    else if (nextwindow == "highscore") enter_highscore(players);
    else if (nextwindow == "game")      enter_game(players);
  }
}