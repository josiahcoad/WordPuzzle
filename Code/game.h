/*
 HNR CSCE 121-200, Fall 2016, Final Project
 Author: Megan Grahmann, Clare Lamers, Josiah Coad
 CODE DESCRIPTION: This code is gives user interface to the game window
*/

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

struct Game_window : public Graph_lib::Window {
      //constructor
      Game_window(Point xy,
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
            Image userpicture;
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
//This function generates a vector of randomly chosen characters
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
}//This function makes a matrix of buttons using a vector of randomly generated characters
void Game_window::makematrix(int size){
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
Game_window::Game_window(Point xy, int w, int h, const string& title, PlayerList& p):
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
      "GAME ON, " + players.current.get_name()),
userpicture(
      Point(200,05),
      players.current.get_picturepath()),
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
      greeting.set_font(FL_TIMES_BOLD_ITALIC);
      greeting.set_font_size(15);
      greeting.set_color(Color::blue);
      attach(greeting);
      userpicture.resize(40,40);
      attach(userpicture);
      attach(currentwordbox);
      attach(feedbackmsg);
      attach(lastwordbox);
      attach(totalscorebox);
      // these buttons allow the user to pick bet
      matrixsize.attach(new Button(Point(0,0),0,0,"3x3",cb_3x3));
      matrixsize.attach(new Button(Point(0,0),0,0,"4x4",cb_4x4));
      matrixsize.attach(new Button(Point(0,0),0,0,"5x5",cb_5x5));
      attach(matrixsize);
      readfile("dictionary.txt");
      totalscore = 0; 
      cout << "Game Window constructed.\n";
}
//This function reads a file and make sure the file exists
void Game_window::readfile(string filename){
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

void Game_window::donepressed()
{
      backtomenu.show();
}
//This funtion is called whenever the enter button is pressed. If the word exists,
//the score is updated and the outbox is cleared. If it does not exist, the buttons
//are replaced.
void Game_window::enterpressed()
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

}
//This function gives a word a score based on its size if it exists.
int Game_window::checkword(string word){
      if (isword(currentword)){
            // one point per letter
            int points = currentword.size() * 1;
            return points;
      }
      return 0;
}
//This function compares the input word to each dictionary word. If it matches,
//the function returns true.
bool Game_window::isword(string word){
      for (string w : words)
            if (word == w) return true;
      return false;
}
//This function updates the outbox whenever backspace is pressed and replaces the
//button.
void Game_window::backspacepressed(){
      if (last_pressed.size() <= 0) return;
      // this removes the last letter of the word
      currentword = currentword.substr(0, currentword.size()-1);
      currentwordbox.put(currentword);
      // this shows the button again
      last_pressed[last_pressed.size()-1]->show();
      // this removes the last button from the list
      last_pressed.pop_back();
}
//These functions display the matrix of desired size and hides the matrix menu.

void Game_window::threepressed()
{
      matrixsize.hide();
      makematrix(3);
}
void Game_window::fourpressed()
{
      matrixsize.hide();
      makematrix(4);
}
void Game_window::fivepressed()
{
      matrixsize.hide();
      makematrix(5);
}
//This function is called whenevr the player is about to leave the game. It updates
//or creates their picture, name and score information.
void Game_window::quit()
{
      players[players.current.get_name()].addscore(totalscore);
      hide();
}
//This funciton allows the letter buttons to be aware of their label.
void Game_window::matrixpressed(Fl_Button* button)
{
      string letter = button->label();
      last_pressed.push_back(button);
      button->hide();
      currentword += letter;
      currentwordbox.put(currentword);
}
void Game_window::cb_3x3(Address, Address pw)
{
      reference_to<Game_window>(pw).threepressed();
}
void Game_window::cb_4x4(Address, Address pw)
{
      reference_to<Game_window>(pw).fourpressed();
}
void Game_window::cb_5x5(Address, Address pw)
{
      reference_to<Game_window>(pw).fivepressed();
}
void Game_window::cb_done(Address, Address pw)
{
      reference_to<Game_window>(pw).donepressed();
}
void Game_window::cb_enter(Address, Address pw)
{
      reference_to<Game_window>(pw).enterpressed();
}
void Game_window::cb_backspace(Address, Address pw){
      reference_to<Game_window>(pw).backspacepressed();
}
void Game_window::cb_back(Address, Address pw)
{
      reference_to<Game_window>(pw).quit();
}
void Game_window::cb_matrixstuff(Address flbp, Address pw)
{
      reference_to<Game_window>(pw).matrixpressed((Fl_Button*)flbp);
}

#endif