#pragma once
#include <iostream>
#include <string>
#include "/public/colors.h"
using namespace std;

class Graphics { //graphics class
	public:
	Graphics() {}

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
		for (row = small_y; row <= big_y; row++) {
			for (col = small_x; col <= big_x; col++) {
				movecursor(row,col);
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
		movecursor(col,row); // Fixed the order of row and col
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
	string p = "Graphics.h did not pass all tests.";
	Graphics test;
	if (test.get_color() != "") { // Updated to check default color
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

