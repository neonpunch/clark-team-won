#pragma once
#include <iostream>
#include <string>
#include "/public/colors.h"
using namespace std;

class Graphics { //graphics class
    string color;
public:
    Graphics() : color("") {}

    void set_color(const string& new_color) {
        color = new_color;
    }

    string get_color() const {
        return color;
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
        for (col = small_y; col <= big_y; col++) {
            for (row = small_x; row <= big_x; row++) {
                movecursor(row,col);
                cout << " ";
            }
        }
        cout.flush();
        resetcolor();
        cout << endl;
    }

    void drawPoint(int col, int row, int r, int g, int b) {
        resetcolor();
        setbgcolor(r,g,b);
        movecursor(row,col); // Fixed the order of row and col
        cout << " ";
        cout.flush();
        resetcolor();
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
    if (test.makeoval() != 0) {
        result = false;
    }
    if (test.makepolygon() != 0) {
        result = false;
    }
    if (result != false) {
        p = "Graphics.h passed all tests!";
    }
    return p;
}
