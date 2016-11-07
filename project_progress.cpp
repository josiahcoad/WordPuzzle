//Megan Grahmann
//CSCE 121
//Group Project
//Word Puzzle Game
//change button to Game_Button
//change Game_Window

#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include <math.h>
#include "Graph.cpp"
#include "Graph.h"
#include "GUI.cpp"
#include "GUI.h"
#include "Point.h"
#include "Window.cpp"
#include "Window.h"
#include "std_lib_facilities_4.h"
#include "Simple_window.cpp"
#include "Simple_window.h"

//using namespace Graph_lib;
//using namespace std;

//---------------------------------------------------------
// define a struct that is a window in which shapes can be
// entered via a GUI

struct Main_window :Graph_lib:: Window {       // inherits from Window

    // constructor
    Main_window(Point xy,             // top lefthand corner
                  int w,                // width
                  int h,                // height
                  const string& title); // label

private:
    // data members
//    string current_shape;
//    Color current_color;
//    Vector_ref<Shape> myshapes;

    // widgets:
//    Button next_button;        // button indicating next point is ready
	Button enter_info_page_button;
    Button quit_button;                // end program
	
	
	In_box user_name;
	In_box profie_image;
	Button enter_game_button;
	
	
//   In_box x_loc;
//    In_box y_loc;
//    Menu color_menu;       // menu of color choices for the lines
//   Button menu_button;                // button to display the color menu
//    Menu shape_menu;
//    Button shape_menu_button;
	

    // actions invoked by callbacks:
	void enter_info_page_pressed() {
		hide_main_menu();
		show_info_page();
	}
	
	void hide_main_menu() {
		enter_info_page.hide();
		quit_button.hide();
	}
	
	void show_info_page() {
		//show estetst
		
	}