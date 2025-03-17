#include <iostream>
#include <string>
using namespace std;

class gc { //graphics class
	string color = "";
  public:
	gc(string new_color) {  //constructor
		color = new_color;
	}
	string get_color() {  //getter
		return color;
	}
	void set_color(string new_color) {  //setter
		color = new_color;
	}
// rectangle, an oval, a polygon, and a line methods
	double makerectangle() {
		return 0; //stub
	}
	double makeline() {
		return 0; //stub
	}
	double makepolygon() {
		return 0; //stub
	}
	double makeoval() {
		return 0; //stub
	}
};
string testinggc() { //test to make sure everthing works
	bool result = true;
	string p = "pass";
	gc test("red");
	if (test.get_color() != "red") {
		result = false;
	}
	test.set_color("blue");
	if (test.get_color() != "blue") {
		result = false;
	}
	if (test.makeline() != 0) {
		result = false;
	}
	if (test.makeoval() != 0) {
		result = false;
	}
	if (test.makerectangle() != 0) {
		result = false;
	}
	if (test.makepolygon() != 0) {
		result = false;
	}
	if (result != false) {
		p = "pass";
	}
	return p;
}






























