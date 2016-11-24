// Author: Megan Grahmann, Josiah Coad and Clare 
// CSCE 121 Final Project

#ifndef MAINMENU_H
#define MAINMENU_H

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
    Main_window(Point xy,               // top lefthand corner
                  int w,                // width
                  int h,                // height
                  const string& title,  // label
                  string& nw,
                  PlayerList& p);

	private:
	// data members (explained in constructor)
	string& nextwindow;
	PlayerList& players;

	// widgets for Main Page
	Button enter_info_button;
	Button enter_highscore_button;
   Button quit_button;
	Image header;
	
	
	// leave this page and change nextwindow to info
	void show_info_page() {
		nextwindow = "info";
		hide();
	}

	void show_highscore() {
		nextwindow = "highscore";
		hide();
	}
	
	// quit the entire game
	void quit_game() {
		nextwindow = "quit";
	   hide(); 
	}
	
  // callback functions. defined below.
  static void cb_enter_info(Address, Address);
  static void cb_enter_highscore(Address, Address);
  static void cb_quit(Address, Address);
};

// constructor for main 
Main_window::Main_window(Point xy, int w, int h, const string& title, string& nw, PlayerList& p) :
	// initialization - start by calling constructor of base class
	Window(xy, w, h, title),
	players(p),      // players are passed by reference to track changes to the Player List
	nextwindow(nw),  // the nextwindow string is passed by reference to tell main where to go next
	// Button for entering the Info Page
	enter_info_button(
	       Point(225, 220),      // location of button
	       150, 20,              // dimensions of button
	       "New Game",           // label of button
	       cb_enter_info),       // callback function for button
	// Button for entering the highscore page
	enter_highscore_button(
	       Point(225, 280),
	       150, 20,        
	       "View highest score",
	       cb_enter_highscore),
	// Button for quiting the game
	quit_button(
	       Point(225, 340),
	       150, 20,        
	       "Quit",         
	       cb_quit),
	// Banner picture
	header(
		Point(0,0),
		"word_header.jpg")
	// Body of constructor... attaches objects to Main
	{
	   attach(enter_info_button);
		attach(enter_highscore_button);
	   attach(quit_button);
	   header.resize(x_max(), 200);
		attach(header);
	}

// ......... CALLBACKS .........

// for a button to enter the info page
void Main_window::cb_enter_info(Address, Address pw) {
    reference_to<Main_window>(pw).show_info_page();
}

// for a button to enter the high score page
void Main_window::cb_enter_highscore(Address, Address pw) {
    reference_to<Main_window>(pw).show_highscore();
}

// Main
void Main_window::cb_quit(Address, Address pw) {
    reference_to<Main_window>(pw).quit_game();
}

#endif