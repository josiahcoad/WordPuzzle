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
  Highscore_window(Point xy,
             int w,
             int h,
             const string& title);


  private:
  Button main_button;

  static void cb_main(Address, Address pw));
  };
  Highscore_window::Highscore_window(Point xy, int w, int h, const string& title):
  Window(xy,w,h,title),
  main_button(
        Point(300,200),
        70, 20,
        "MAIN MENU",
        cb_enter)
{
      attach(main_button);
      attach(new Image ii{Point{100,50},".jpg"})
}

int main() {
  // construct the GUI window

  try{
Highscore_window win(Point(100,100),600,400,"High score!");
return gui_main();
}
catch(exception& e){
 cerr<<"exception: "<<e.what()<<'\n';
 return 1;
}
catch(...){
 cerr<<"some exception\n";
 return 2;
}
}
