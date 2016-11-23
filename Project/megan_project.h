//Megan Grahmann
//CSCE 121
//Group Project
//Word Puzzle Game
//change button to Game_Button
//change Game_Window
#ifndef MEGAN_PROJECT_H
#define MEGAN_PROJECT_H

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
//    data members
	string& nextwindow;
	PlayerList& players;
//    string current_shape;
//    Color current_color;
//    Vector_ref<Shape> myshapes;

//    widgets:
//    Button next_button;        // button indicating next point is ready
	Button enter_info_page_button;
	Button view_high_score_button;
    Button quit_button;                // end program
	Image header;
	Image info_header;
	//TODO: add to constructor
	
	In_box user_name;
	In_box profile_image;
	Button enter_game_button;
	
	Button back_main_button;
	Button finish_game_button;
	
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
		
	void finish_game_pressed() {
		hide_game_screen();
		show_main_menu();
	}
	
	void hide_game_screen() {
		//hide clare's part
		finish_game_button.hide();
	}
	
	void back_to_main_menu_pressed() {
		show_main_menu();
		hide_high_scores_page();
	}
	
	void show_main_menu() {
		header.resize(x_max(), 200);
		attach(header);
		enter_info_page_button.show();
		quit_button.show();
		view_high_score_button.show();
	}
	
	void hide_high_scores_page() {
		//hide josiah's part
		back_main_button.hide();
		
	}
	
//	void enter_game();
    void quit();   // defined below
	
  // callback functions; declared here and defined below.
  static void cb_enter_info_page(Address, Address);
  static void cb_view_high_score(Address, Address);
  static void cb_quit(Address, Address);
  static void cb_enter_game(Address, Address);
  static void cb_back_main(Address, Address);
  static void cb_finish_game(Address, Address);
};

// ----------------------------------------------------------
// now define the parts of Main_window that were only declared
// inside the class

// constructor:

Main_window::Main_window(Point xy, int w, int h, const string& title, string& nw, PlayerList& p) :
		  players(p),
		  nextwindow(nw),
// initialization - start by calling constructor of base class
        Window(xy, w, h, title),

// initialize the enter info page button
        enter_info_page_button(
                Point(225, 220),   // location of button
                150, 20,                 // dimensions of button
                "New Game",           // label of button
                cb_enter_info_page),               // callback function for button
// initialize quit button
        quit_button(
                Point(225, 340),   // location of button
                150, 20,                 // dimensions of button
                "Quit",                 // label of button
                cb_quit),               // callback function for button
//initialize the view high score button
	   view_high_score_button(
                Point(225, 280),   // location of button
                150, 20,                   // dimensions of button
                "View highest score",           // label of button
                cb_view_high_score),               // callback function for button				
// initialize the inbox
        user_name(
                Point(225, 220),       // location of box
                150, 20,                     // dimensions of box
                "User Name:"),                 // label of box
// initialize the profile picture inbox
        profile_image(
                Point(225, 280),       // location of box
                150, 20,                     // dimensions of box
                "Profile image:"),                 // label of box
		enter_game_button(
                Point(225, 340),   // location of button
                150, 20,                   // dimensions of button
                "Start Game",           // label of button
                cb_enter_game),               // callback function for button
		back_main_button(
				Point(225,380),
				150,20,
				"Back to Main Menu",
				cb_back_main),
		finish_game_button(
				Point(225,380),
				150,20,
				"Back to Main Menu",
				cb_finish_game),
		header(
				Point(0,0),
				"word_header.jpg"),
		info_header
			(
			Point(0,0),
			"enter_user_header.jpg")
			

				
// body of constructor follows
{
    // attach buttons and boxes to window
    attach(enter_info_page_button);
	attach(view_high_score_button);
    attach(quit_button);
    header.resize(x_max(), 200);
	attach(header);
	//attach(header);

    //  attach(xy_out);
    //  xy_out.put("no point");        // output to out box
}

// ----------------------------
// callback function for button - boilerplate:
void Main_window::cb_enter_info_page(Address, Address pw) {
    reference_to<Main_window>(pw).enter_info_page_pressed();   // quit is defined next
}

void Main_window::cb_view_high_score(Address, Address pw) {
    reference_to<Main_window>(pw).view_high_score_pressed();   // quit is defined next
}

void Main_window::cb_quit(Address, Address pw) {
    reference_to<Main_window>(pw).quit();   // quit is defined next
}

void Main_window::cb_enter_game(Address, Address pw) {
    reference_to<Main_window>(pw).enter_game();   // quit is defined next
}

void Main_window::cb_back_main(Address, Address pw) {
    reference_to<Main_window>(pw).back_to_main_menu_pressed();   // quit is defined next
}

void Main_window::cb_finish_game(Address, Address pw) {
    reference_to<Main_window>(pw).finish_game_pressed();   // quit is defined next
}
//------------------------------------


//------------------------------------
// what to do when quit button is pressed
void Main_window::quit() {
	nextwindow = "quit";
   hide();                   // FLTK idiom for delete window
}

#endif