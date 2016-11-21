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


int main()
{
	Image pic(Point(100,50),word_header);
pic.resize(400,200); //this will resize the image with width 400 and height 200
win.attach(pic); //draw the image with size 400x200
}