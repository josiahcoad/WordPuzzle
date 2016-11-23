#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"
#include "std_lib_facilities_4.h"
#include "PlayerList.h"
using namespace Graph_lib;
using namespace std;

#ifndef HIGHSCORE_H
#define HIGHSCORE_H

struct Highscore_window : public Graph_lib::Window {
  // constructor
  Highscore_window(Point xy,
             int w,
             int h,
             const string& title,
             PlayerList& p);


  private:
  PlayerList& players;
  Button main_button;
  Text player_name;
  Text score;
  Image highscore_banner;
  Image profile_pic;
  Image background_pic;
   static void cb_main(Address, Address pw);
};

  Highscore_window::Highscore_window(Point xy, int w, int h, const string& title, PlayerList& p):
  players(p),
  Window(xy,w,h,title),
  main_button(
        Point(250,350),
        100, 20,
        "MAIN MENU",
        cb_main),
  player_name(
        Point(70,250),
        "Congrats " + players.get_highest_scorer().get_name()),
  score(
        Point(200,300),
        "Score: " + to_string(players.get_highest_scorer().get_topscore())),
  highscore_banner(
        Point(0,0),
        "highscore.jpg"),
  background_pic(
        Point(0, 190),
        "background.jpg"),
  profile_pic(
        Point(380,270),
        players.get_highest_scorer().get_picturepath())
  {
        // not using this right now because covers up button
        // background_pic.resize(x_max(), y_max()-190);
        // attach(background_pic);
        attach(main_button);
        player_name.set_font(FL_COURIER_BOLD_ITALIC);
        player_name.set_font_size(25);
        attach(player_name);
        score.set_font_size(30);
        score.set_font(FL_HELVETICA_BOLD_ITALIC);
        attach(score);
        highscore_banner.resize(x_max(),200);
        attach(highscore_banner);
        profile_pic.resize(100,100);
        attach(profile_pic);
        

  }
  void Highscore_window::cb_main(Address, Address pw)
  {
  reference_to<game_window>(pw).hide();
}

#endif