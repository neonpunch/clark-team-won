#pragma once
#include <iostream>
#include <string>
#include "/public/colors.h"
using namespace std;

class Graphics { //graphics class
	string color = "";
	public:
	Graphics() {}

	Graphics(string new_color) {  //constructor
		color = new_color;
	}
	string get_color() {  //getter
		return color;
	}
	void set_color(string new_color) {  //setter
		color = new_color;
	}
	// rectangle, an oval, a polygon, and a line methods
	void drawRectangle(int small_x, int big_x, int small_y, int big_y, int r, int g, int b) {
		if ((small_x > big_x) || (small_y > big_y)) {
		cout << RED << "BAD INPUT";
		resetcolor();
		cout << endl;
		exit(0);
		}
		resetcolor();
		setbgcolor(r,g,b);
		int row;
		int col;
		for (row = small_x; row <= big_x; row++) {
			for (col = small_y; col <= big_y; col++) {
				movecursor(col,row);
				cout << " ";
				}
		}
		cout.flush();
		resetcolor();
		cout << endl;
	}

		//return 0; //stub
	void drawPoint(int row, int col, int r, int g, int b) {
		resetcolor();
		setbgcolor(r,g,b);
		movecursor(col,row);
		cout << " ";
		cout.flush();
		resetcolor();


		//This should be in drawPoint in Graphics.h
		/*
		   show_cursor(false);
		   movecursor(y, x);
		// setbgcolor(,,);
		// setcolor(,,);
		cout << pSymbol;
		cout.flush();
		//reset.color();
		usleep(1'000'000/FPS);
		lifetime--;
		clearscreen();
		*/
	}
	double makepolygon() {
		return 0; //stub
	}
	double makeoval() {
		return 0; //stub
	}
};
inline string testGraphics() { //test to make sure everthing works
	bool result = true;
	string p = "Graphics.h passed all tests!";
	Graphics test("red");
	if (test.get_color() != "red") {
		result = false;
	}
	test.set_color("blue");
	if (test.get_color() != "blue") {
		result = false;
	}
	/*	if (test.drawPoint() != 0) {
		result = false;
		} */
	if (test.makeoval() != 0) {
		result = false;
	}
/*	if (test.makerectangle() != 0) {
		result = false;
	} */
	if (test.makepolygon() != 0) {
		result = false;
	}
	if (result != false) {
		p = "Graphics.h passed all tests!";
	}
	return p;
}

