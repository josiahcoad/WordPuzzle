#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"

using namespace Graph_lib;
using namespace std;

struct game_window : public Graph_lib::Window {
      //constructor
      game_window(Point xy,
                  int w,
                  int h,
                  const string& title);
      private:
            //widgets:
            Button enter_button;
            Button done_button;
            Button backtomenu;
            Menu matrixsize;
            Text greeting;
            Out_box currentword;
            Out_box lastword;
            Out_box totalscore;
            //function members
      static void cb_enter(Address, Address);
      static void cb_done(Address, Address);
      static void cb_back(Address, Address);
      static void cb_3x3(Address, Address);
      static void cb_4x4(Address, Address);
      static void cb_5x5(Address, Address);
      void threepressed();
      void fourpressed();
      void fivepressed();
      void donepressed();
};
//constructor:
game_window::game_window(Point xy, int w, int h, const string& title):
//initialization
Window(xy,w,h,title),
enter_button(
      Point(500,100),
      70, 20,
      "ENTER",
      cb_enter),
done_button(
      Point(500,150),
      70, 20,
      "DONE",
      cb_done),
backtomenu(
      Point(450,350),
      110, 20,
      "BACK TO MENU",
      cb_back),
matrixsize(
      Point(20,75),
      70, 20,
      Menu::horizontal,
      "size"),
greeting(
      Point(10,20),
      "Hello,"),
currentword(
      Point(450,10),
      100, 20,
      "Current word:"),
lastword(
      Point(450,250),
      100,20,
      "Last word score"),
totalscore(
      Point(450,300),
      100,20,
      "TOTAL SCORE")
{
      attach(enter_button);
      attach(done_button);
      attach(backtomenu);
      backtomenu.hide();
      attach(greeting);
      attach(currentword);
      attach(lastword);
      attach(totalscore);
      matrixsize.attach(new Button(Point(0,0),0,0,"3x3",cb_3x3));
      matrixsize.attach(new Button(Point(0,0),0,0,"4x4",cb_4x4));
      matrixsize.attach(new Button(Point(0,0),0,0,"5x5",cb_5x5));
      attach(matrixsize);
}
void game_window::donepressed()
{
      backtomenu.show();
}
void game_window::threepressed()
{
      matrixsize.hide();
}
void game_window::fourpressed()
{
      matrixsize.hide();
}
void game_window::fivepressed()
{
      matrixsize.hide();
}
void game_window::cb_3x3(Address, Address pw)
{
      reference_to<game_window>(pw).threepressed();
}
void game_window::cb_4x4(Address, Address pw)
{
      reference_to<game_window>(pw).fourpressed();
}
void game_window::cb_5x5(Address, Address pw)
{
      reference_to<game_window>(pw).fivepressed();
}
void game_window::cb_done(Address, Address pw)
{
      reference_to<game_window>(pw).donepressed();
}
void game_window::cb_enter(Address, Address pw)
{

}
void game_window::cb_back(Address, Address pw)
{

}
int main(){
      try{
game_window win(Point(100,100),600,400,"game window");
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
