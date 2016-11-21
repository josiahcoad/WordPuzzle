#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"
#include "std_lib_facilities_4.h"
using namespace Graph_lib;
using namespace std;


struct Highscore_window : public Graph_lib::Window {
  // constructor
  Highscore_window(Point xy,
             int w,
             int h,
             const string& title);

  private:
  Button main_button;
  Text t;
  Text score;
  Image ii;
  Image ij;
   static void cb_main(Address, Address pw);
};

  Highscore_window::Highscore_window(Point xy, int w, int h, const string& title):
  Window(xy,w,h,title),
  main_button(
        Point(250,350),
        100, 20,
        "MAIN MENU",
        cb_main),
t(
      Point(30,250),
      "name place holder"),
score(
      Point(200,250),
      "number"),
ii(
      Point(125,10),
      "highscore.jpg"
),
ij(
      Point(300,240),
      "missing.jpeg"
)
{
      attach(main_button);
      attach(t);
      attach(score);
      attach(ii);
      ij.resize(50,50);
      attach(ij);

}
void Highscore_window::cb_main(Address, Address pw)
{
  reference_to<game_window>(pw).hide();
}
