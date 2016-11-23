//Megan Grahmann
//CSCE 121
//Group Project
//Word Puzzle Game
//change button to Game_Button
//change Game_Window
#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include <math.h>
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Window.h"
#include "std_lib_facilities_4.h"
#include "PlayerList.h"

//---------------------------------------------------------
// define a struct that is a window in which shapes can be
// entered via a GUI

struct Main_window :Graph_lib:: Window {       // inherits from Window

    // constructor
    Main_window(Point xy,             // top lefthand corner
                  int w,                // width
                  int h,                // height
                  const string& title, // label
                  string& nw,
                  PlayerList& p);

private:
	// data members
	string& nextwindow;
	PlayerList& players;

	// widgets for Main Page
	Button enter_info_page_button;
	Button view_high_score_button;
   Button quit_button;
	Image header;

	// widgets for Info Page
	Image info_header;
	In_box user_name;
	In_box profile_image;
	Button enter_game_button;
	
   // actions invoked by callbacks:
	void enter_info_page_pressed() {
		hide_main_menu();
		show_info_page();
	}
	
	void hide_main_menu() {
		enter_info_page_button.hide();
		quit_button.hide();
		view_high_score_button.hide();
		detach(header);
	}
	
	void show_info_page() {
		attach(user_name);
		attach(profile_image);
		attach(enter_game_button);
		info_header.resize(x_max(), 200);
		attach(info_header); // too big...
	}

	void  enter_game() {
		string name_input = user_name.get_string();
		players.current.set_name(name_input);
		string image_input = profile_image.get_string();
		if (players.exists(name_input)){
			// if no picture was inputted but the player exists...
			if (image_input == ""){
				// then get their picture..
				string existing_pic = players[name_input].get_picture();
				// and set it as the current player's picture
				players.current.set_picture(existing_pic);
			}
			// else if they did input a picture name and they do exist...
			else {
				// set the current player's picture to the new picture
				players.current.set_picture(image_input);
				// and update the existing player's picture
				players[name_input].set_picture(image_input);
			}
		}
		else if (!players.exists(name_input))
			// if no picture was inputted...
			if (image_input == "")
				// add a player with a "missing pic"
				players.add(name_input, {}, players.missing_pic);
			// if a picture was inputted...
			else
				// add a player with the inputted picture
				players.add(name_input, {}, image_input);
		nextwindow = "game";
		hide();
	}
	
	void view_high_score_pressed() {
		hide_main_menu();
		show_high_score_page();
	}
	

	void show_high_score_page() {
		nextwindow = "highscore";
		hide();
	}
	
	void hide_info_page() {
		enter_game_button.hide();
		user_name.hide();
		profile_image.hide();
		detach(info_header);
	}
	
	void show_main_menu() {
		header.resize(x_max(), 200);
		attach(header);
		enter_info_page_button.show();
		quit_button.show();
		view_high_score_button.show();
	}
	
//	void enter_game();
    void quit();   // defined below
	
  // callback functions; declared here and defined below.
  static void cb_enter_info_page(Address, Address);
  static void cb_view_high_score(Address, Address);
  static void cb_quit(Address, Address);
  static void cb_enter_game(Address, Address);
};

// constructor:
Main_window::Main_window(Point xy, int w, int h, const string& title, string& nw, PlayerList& p) :
		  players(p),
		  nextwindow(nw),
// initialization - start by calling constructor of base class
        Window(xy, w, h, title),

// Button for entering the Info Page (on the Main Page)
        enter_info_page_button(
                Point(225, 220),      // location of button
                150, 20,              // dimensions of button
                "New Game",           // label of button
                cb_enter_info_page),  // callback function for button
// Button for entering the highscore page (on the Main Page)
	   view_high_score_button(
                Point(225, 280),
                150, 20,        
                "View highest score",
                cb_view_high_score),
// Button for quiting the game (on the Main Page)
        quit_button(
                Point(225, 340),
                150, 20,        
                "Quit",         
                cb_quit),       
// In box for inputting name (on Info Page)
        user_name(
                Point(225, 220),
                150, 20,        
                "User Name:"),  
// In box for inputting the user picture name (on the Info Page)
        profile_image(
                Point(225, 280),
                150, 20,        
                "Profile image:"),
// Button for entering the Game Page (on the Info Page)
		enter_game_button(
                Point(225, 340),  
                150, 20,          
                "Start Game",     
                cb_enter_game),   
// Banner picture (on Main Page)
		header(
				Point(0,0),
				"word_header.jpg"),
// Banner pictuer (on Info Page)
		info_header(
			Point(0,0),
			"enter_user_header.jpg")
			

// Body of constructor... attaches objects
{
   attach(enter_info_page_button);
	attach(view_high_score_button);
   attach(quit_button);
   header.resize(x_max(), 200);
	attach(header);
}

// ......... CALLBACKS .........

void Main_window::cb_enter_info_page(Address, Address pw) {
    reference_to<Main_window>(pw).enter_info_page_pressed();
}

void Main_window::cb_view_high_score(Address, Address pw) {
    reference_to<Main_window>(pw).view_high_score_pressed();
}

void Main_window::cb_quit(Address, Address pw) {
    reference_to<Main_window>(pw).quit();
}

void Main_window::cb_enter_game(Address, Address pw) {
    reference_to<Main_window>(pw).enter_game(); 
}

void Main_window::quit() {
	nextwindow = "quit";
   hide(); 
}

#endif