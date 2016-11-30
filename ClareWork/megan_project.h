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

    //constructor
    Main_window(Point xy,             // top lefthand corner
                  int w,                // width
                  int h,                // height
                  const string& title, // label
                  string& nw,
                  PlayerList& p);

private:
	//data members
	string& nextwindow;
	PlayerList& players;

	//widgets:
	Button enter_info_page_button;
	Button view_high_score_button;
    Button quit_button;                // end program
	Image header;
	Image info_header;
	
	In_box user_name;
	In_box profile_image;
	Button enter_game_button;
	
	Button back_main_button;
	Button finish_game_button;

//-----------------------------------------------	
    // actions invoked by callbacks:
	
	//transtions the window to the info page
	void enter_info_page_pressed() {
		hide_main_menu();
		show_info_page();
	}
	
	//hides the buttons and headers on the main menu
	void hide_main_menu() {
		enter_info_page_button.hide();
		quit_button.hide();
		view_high_score_button.hide();
		detach(header);
	}
	
	//attaches the headers and buttons for the information page
	void show_info_page() {
		attach(user_name);
		attach(profile_image);
		attach(enter_game_button);
		info_header.resize(x_max(), 200);
		attach(info_header); // too big...
	}

	//changes the window to the game screen
	//attaches the name and image to window
	void  enter_game() {
		string name_input = user_name.get_string();
		players.current.set_name(name_input);
		string image_input = profile_image.get_string();
		if (image_input == "")
			if (!players.exists(name_input))
				players.current.set_picture(players.missing_pic);
			else
				players.current.set_picture(players[name_input].get_picturepath());
		else
			players.current.set_picture(image_input);
		nextwindow = "game";
		hide();
	}
	
	//functions that transitions the windows to shows the high scores while hiding high scores
	void view_high_score_pressed() {
		hide_main_menu();
		show_high_score_page();
	}
	
	//changes the window to highscore
	void show_high_score_page() {
		nextwindow = "highscore";
		hide();
	}
	
	//hides tje buttons and boxes on the info page
	void hide_info_page() {
		enter_game_button.hide();
		user_name.hide();
		profile_image.hide();
		detach(info_header);
	}
		
	//transition that hides the game screen while showing the menu screen
	void finish_game_pressed() {
		hide_game_screen();
		show_main_menu();
	}
	
	//hides the buttons the game screen
	void hide_game_screen() {
		//hide clare's part
		finish_game_button.hide();
	}
	
	//transition that calls the functions to show the main menu while hiding the high scores
	void back_to_main_menu_pressed() {
		show_main_menu();
		hide_high_scores_page();
	}
	
	//attaches the headers and buttons the main menu page
	void show_main_menu() {
		header.resize(x_max(), 200);
		attach(header);
		enter_info_page_button.show();
		quit_button.show();
		view_high_score_button.show();
	}
	
	//hides the buttons the high scores page
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
                Point(225, 220),       // location of button
                150, 20,               // dimensions of button
                "New Game",            // label of button
                cb_enter_info_page),   // callback function for button
// initialize quit button
        quit_button(
                Point(225, 340),       // location of button
                150, 20,               // dimensions of button
                "Quit",                 // label of button
                cb_quit),               // callback function for button
//initialize the view high score button
	   view_high_score_button(
                Point(225, 280),       // location of button
                150, 20,               // dimensions of button
                "View highest score",    // label of button
                cb_view_high_score),    // callback function for button				
// initialize the inbox
        user_name(
                Point(225, 220),       // location of box
                150, 20,               // dimensions of box
                "User Name:"),         // label of box
// initialize the profile picture inbox
        profile_image(
                Point(225, 280),       // location of box
                150, 20,               // dimensions of box
                "Profile image:"),     // label of box
		enter_game_button(
                Point(225, 340),      // location of button
                150, 20,              // dimensions of button
                "Start Game",         // label of button
                cb_enter_game),       // callback function for button
		back_main_button(
				Point(225,380),       //location of box
				150,20,               //dimensions of box
				"Back to Main Menu",   //label of button
				cb_back_main),        //callback function for button
		finish_game_button(
				Point(225,380),       //location of box
				150,20,               //dimensions of box
				"Back to Main Menu",    //label of button
				cb_finish_game),        //callback function for button
		header(
				Point(0,0),              //location of image on window
				"word_header.jpg"),      //file name of image
		info_header
			(
			Point(0,0),                   //location of image on window
			"enter_user_header.jpg")      //file name of window
			

// body of constructor follows
{
    // attach buttons and boxes to window
    attach(enter_info_page_button);
	attach(view_high_score_button);
    attach(quit_button);
    header.resize(x_max(), 200);
	attach(header);
    //  attach(xy_out);
    //  xy_out.put("no point");        // output to out box
}

// -----------------------------------------------
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

//--------------------------------------------

// what to do when quit button is pressed
void Main_window::quit() {
	nextwindow = "quit";
   hide();                   // FLTK idiom for delete window
}

#endif