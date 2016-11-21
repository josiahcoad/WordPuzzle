#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"
#include <string>
#include <cmath>
#include <FL/Fl_Button.H>
#include "PlayerList.h"

#ifndef GAME_H
#define GAME_H

using namespace Graph_lib;
using namespace std;

struct game_window : public Graph_lib::Window {
      //constructor
      game_window(Point xy,
                  int w,
                  int h,
                  const string& title, 
                  PlayerList& p);
      private:
            // member variables
            PlayerList& players;
            string currentword;
            vector<string> words;
            int totalscore;
            // this vector will keep track of letters pressed
            vector<Fl_Button*> last_pressed;
            //widgets:
            Button enter_button;
            Button done_button;
            Button backspace_button;
            Button backtomenu;
            Menu matrixsize;
            Text greeting;
            Text feedbackmsg;
            Out_box currentwordbox;
            Out_box lastwordbox;
            Out_box totalscorebox;
            vector<Button*> buttonvec;
            //function members
      static void cb_enter(Address, Address);
      static void cb_backspace(Address, Address);
      static void cb_done(Address, Address);
      static void cb_back(Address, Address);
      static void cb_3x3(Address, Address);
      static void cb_4x4(Address, Address);
      static void cb_5x5(Address, Address);
      static void cb_matrixstuff(Address, Address);
      
      void readfile(string filename);
      int checkword(string word);
      bool isword(string word);
      void donepressed();
      void enterpressed();
      void backspacepressed();
      void threepressed();
      void fourpressed();
      void fivepressed();
      void quit();
      void makematrix(int size);
      void matrixpressed(Fl_Button*);
};
vector<char> getrand(int n){
      srand(time(NULL));
      vector<char> randos;
      vector<char> vowels = {'a','e','i','o','u'};
      int j=rand()%4;
      randos.push_back(vowels[j]);
      for (int i=0; i<pow(n,2)-1; i++){
            char c='a'+rand()%26;
            randos.push_back(c);
      }
      return randos;
}
void game_window::makematrix(int size){
      vector<char> newvec=getrand(size);
      int x=0;
      for (int i=1; i<=size; ++i)
      {
            for (int j=1; j<=size; ++j)
            {
                  string letter = string(1, newvec[x]);
                  buttonvec.push_back(new Button(Point(0+50*i,85+50*j),50,50,letter,cb_matrixstuff));
                  ++x;
                  attach(*buttonvec[buttonvec.size()-1]);
            }
      }
}
//constructor:
game_window::game_window(Point xy, int w, int h, const string& title, PlayerList& p):
//initialization
players(p),
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
backspace_button(
      Point(555,10),
      25, 20,
      "<<",
      cb_backspace),
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
currentwordbox(
      Point(450,10),
      100, 20,
      "Current word:"),
feedbackmsg(
      Point(480,50),
      ""),
lastwordbox(
      Point(450,250),
      100,20,
      "Last word score"),
totalscorebox(
      Point(450,300),
      100,20,
      "TOTAL SCORE")

{
      attach(enter_button);
      attach(done_button);
      attach(backspace_button);
      attach(backtomenu);
      backtomenu.hide();
      attach(greeting);
      attach(currentwordbox);
      attach(feedbackmsg);
      attach(lastwordbox);
      attach(totalscorebox);
      matrixsize.attach(new Button(Point(0,0),0,0,"3x3",cb_3x3));
      matrixsize.attach(new Button(Point(0,0),0,0,"4x4",cb_4x4));
      matrixsize.attach(new Button(Point(0,0),0,0,"5x5",cb_5x5));
      attach(matrixsize);
      readfile("dictionary.txt");
      totalscore = 0; 
}

void game_window::readfile(string filename){
      // get info from file
      ifstream is(filename);
      if (!is) error("There is no such file in the current folder.");
      
      string word;
      while (!is.eof()){
            getline(is, word);
            words.push_back(word.substr(0,word.size()-1));
      }
      is.close();
      cout << words.size() << " words successfully imported...\n";
}

void game_window::donepressed()
{
      backtomenu.show();
}
void game_window::enterpressed()
{
      int points = checkword(currentword);
      if (points == 0)  // it was not a word
            while (last_pressed.size() > 0){ // replace buttons
                  last_pressed[last_pressed.size()-1]->show();
                  last_pressed.pop_back();
            }
      else last_pressed.clear();// clear vector of buttons pressed
      totalscore += points;
      lastwordbox.put(to_string(points));
      totalscorebox.put(to_string(totalscore));
      currentword = "";
      currentwordbox.put("");

      // if points = 0;
      // feedbackmsg.show();
      // label isn't changing...
}
int game_window::checkword(string word){
      if (isword(currentword)){
            // one point per letter
            int points = currentword.size() * 1;
            return points;
      }
      return 0;
}

bool game_window::isword(string word){
      for (string w : words)
            if (word == w) return true;
      return false;
}

void game_window::backspacepressed(){
      if (last_pressed.size() <= 0) return;
      // this removes the last letter of the word
      currentword = currentword.substr(0, currentword.size()-1);
      currentwordbox.put(currentword);
      // this shows the button again
      last_pressed[last_pressed.size()-1]->show();
      // this removes the last button from the list
      last_pressed.pop_back();
}

void game_window::threepressed()
{
      matrixsize.hide();
      makematrix(3);
}
void game_window::fourpressed()
{
      matrixsize.hide();
      makematrix(4);
}
void game_window::fivepressed()
{
      matrixsize.hide();
      makematrix(5);
}

void game_window::quit() {
  string currentplayer = "Josiah Coad";
  players[currentplayer].addscore(totalscore);
  hide();                   // FLTK idiom for delete window
}
void game_window::matrixpressed(Fl_Button* button)
{
      string letter = button->label();
      last_pressed.push_back(button);
      button->hide();
      currentword += letter;
      currentwordbox.put(currentword);
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
      reference_to<game_window>(pw).enterpressed();
}
void game_window::cb_backspace(Address, Address pw){
      reference_to<game_window>(pw).backspacepressed();
}
void game_window::cb_back(Address, Address pw)
{
      reference_to<game_window>(pw).quit();
}
void game_window::cb_matrixstuff(Address flbp, Address pw)
{
      reference_to<game_window>(pw).matrixpressed((Fl_Button*)flbp);
}

#endif