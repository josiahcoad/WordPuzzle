/*
 HNR CSCE 121-200, Fall 2016, Final Project
 Author: Megan Grahmann, Clare Lamers, Josiah Coad
 CODE DESCRIPTION: This is the code for interfacing highscore page
*/

// import guards
#ifndef HIGHSCORE_H
#define HIGHSCORE_H


// GUI, graphics and supporting libraries
#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"
#include "std_lib_facilities_4.h"
#include "PlayerList.h"
using namespace Graph_lib;
using namespace std;


// highscore window inherits from FLTK window
struct Highscore_window : public Graph_lib::Window {
  // constructor decleration
  Highscore_window(Point xy,
                     int w,
                     int h,
                     const string& title,
                     PlayerList& p);


  private:
  // reference to list of players for the game session
  PlayerList& players;
  
  // widgets for highscore Page
  Text player_name;
  Text score;
  Image highscore_banner;
  Image profile_pic;
  Button main_button;

  // callback for enter main menu button
  static void cb_main(Address, Address pw){
    reference_to<Highscore_window>(pw).hide();
  }

};

// constructor for the Info window
Highscore_window::Highscore_window(Point xy, int w, int h, const string& title, PlayerList& p):
players(p),
Window(xy,w,h,title),
// Button for entering the Main menu
main_button(
  Point(250,350),
  100, 20,
  "MAIN MENU",
  cb_main),
// Text for displaying the highscore player
player_name(
  Point(70,250),
  "Congrats " + players.get_highest_scorer().get_name()),
// text for displaying the score
score(
  Point(200,300),
  "Score: " + to_string(players.get_highest_scorer().get_topscore())),
// picture for page title graphics
highscore_banner(
  Point(0,0),
  "highscore.jpg"),
// Button for entering the Info Page
profile_pic(
  Point(380,270),
  players.get_highest_scorer().get_picturepath())
// Body of constructor... attaches objects to window
{
  attach(main_button);

  player_name.set_font(FL_COURIER_BOLD_ITALIC);
  player_name.set_font_size(25);
  player_name.set_color(Color::dark_magenta);
  attach(player_name);
  
  score.set_font_size(30);
  score.set_font(FL_HELVETICA_BOLD_ITALIC);
  score.set_color(Color::dark_magenta);
  attach(score);
  
  highscore_banner.resize(x_max(),200);
  attach(highscore_banner);
  
  profile_pic.resize(100,100);
  attach(profile_pic);
}

#endif