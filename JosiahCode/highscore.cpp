#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"
#include "std_lib_facilities_4.h"
#include "config.h"
using namespace Graph_lib;
using namespace std;


struct Highscore_window : Graph_lib::Window {
  // constructor
  Highscore_window(const string& title):
  Window(window_corner, window_w, window_h, title),
  main_button(
  Point((window_w/2.0)-100, window_h - 100), 200, 20, "MAIN MENU", cb_main)
  { attach(main_button); }
  

  private:
  Button main_button;
  int button_w = 80;

  static void cb_main(Address, Address pw){
    reference_to<Highscore_window>(pw).quit();
  }

  void quit() { hide(); } 
};

int main() {
  // construct the GUI window
  
  Highscore_window win("High Score!");
  return gui_main();  // inherited from Window; calls FLTK's run
}