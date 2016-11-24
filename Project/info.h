// Author: Megan Grahmann, Josiah Coad and Clare 
// CSCE 121 Final Project

#ifndef INFO_H
#define INFO_H

#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Window.h"
#include "std_lib_facilities_4.h"
#include "PlayerList.h"


struct Info_window:Graph_lib:: Window {       // inherits from Window

    // constructor
    Info_window(Point xy,               // top lefthand corner
                  int w,                // width
                  int h,                // height
                  const string& title,  // label
                  PlayerList& p);

	private:
	// data members
	PlayerList& players;

	// widgets for Info Page
	Image info_header;
	In_box user_name;
	In_box profile_image;
	Button enter_game_button;

	// member function
	void enter_game() {
		get_input();
		hide();
	}

	// get input is defined below
	void get_input();


	// callback to enter game
	static void cb_enter_game(Address, Address pw) {
		reference_to<Info_window>(pw).enter_game(); 
	}

};

// constructor for the Info window
Info_window::Info_window(Point xy, int w, int h, const string& title, PlayerList& p) :
	// initialization - start by calling constructor of base class
	Window(xy, w, h, title),
	// players are passed by reference to track changes to the Player List
	players(p),
	// In box for inputting name
	user_name(
		Point(225, 220),
		150, 20,        
		"User Name:"),  
	// In box for inputting the user picture name
	profile_image(
		Point(225, 280),
		150, 20,        
		"Profile image:"),
	// Banner picture
	info_header(
		Point(0,0),
		"infopage.jpg"),
	// Button for entering the Game Page
	enter_game_button(
		Point(225, 340),  
		150, 20,          
		"Start Game",     
		cb_enter_game)  
	// Body of constructor... attaches objects for Info Page
	{
		attach(user_name);
		attach(profile_image);
		attach(enter_game_button);
		info_header.resize(x_max(), 200);
		attach(info_header); 
	}


// this was too long to include in the class 
// it handles setting the current player's picture and name
// it will add the player if needed or if they already exist,
// it will get their info.
void Info_window::get_input(){
	string name_input = user_name.get_string();
	if (name_input=="") name_input = "John Smith";
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
	// if no player exists...
	else if (!players.exists(name_input)) {
		// if no picture was inputted...
		if (image_input == ""){
			// add a player with a "missing pic"
			players.add(name_input, {}, players.missing_pic);
			players.current.set_picture(players.missing_pic);
		}
		// if a picture was inputted...
		else {
			// add a player with the inputted picture
			players.add(name_input, {}, image_input);
			players.current.set_picture(image_input);
		}
	}
}

#endif

