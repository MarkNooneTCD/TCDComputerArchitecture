//
// t2Test.cpp
//
// Copyright (C) 2012 - 2017 jones@scss.tcd.ie
//
// 09/10/17	first version
//


#include <iostream>			// cout
#include <conio.h>			// _getch
#include "t2.h"	

using namespace std;		// cout
_int64 g = 4;
//
// check
//
void check(char *s, _int64 v, _int64 expected) {
	cout << s << " = " << v;
	if (v == expected) {
		cout << " OK";
	}
	else {
		cout << " ERROR: should be " << expected;
	}
	cout << endl;
}

//
// _tmain
//
int main(int argc, char* argv[]) {

	minx64(1, 2, 3);

	//
	// tutorial 2
	//
	check("g", g, 4);
	g++;
	check("g", g, 5);
	g--;
	check("g", g, 4);

	check("min(1, 2, 3)", minx64(1, 2, 3), 1);
	check("min(3, 1, 2)", minx64(3, 1, 2), 1);
	check("min(2, 3, 1)", minx64(2, 3, 1), 1);
	check("min(-1, -2, -3)", minx64(-1, -2, -3), -3);
	check("min(-3, -1, -2)", minx64(-3, -1, -2), -3);
	check("min(-2, -3, -1)", minx64(-2, -3, -1), -3);
	check("min(-1, 2, 3)", minx64(-1, 2, 3), -1);
	check("min(3, -1, 2)", minx64(3, -1, 2), -1);
	check("min(2, 3, -1)", minx64(2, 3, -1), -1);

	check("px64(0, 1, 2, 3)", px64(0, 1, 2, 3), 0);
	check("px64(5, 6, 7, 8)", px64(5, 6, 7, 8), 4);
	check("px64(3, 2, 1, 0)", px64(3, 2, 1, 0), 0);
	check("px64(8, 7, 6, 5)", px64(8, 7, 6, 5), 4);

	check("gcdx64(14, 21)", gcdx64(14, 21), 7);
	check("gcdx64(1406700, 164115)", gcdx64(1406700, 164115), 23445);

	check("qx64(1, 2, 3, 4, 5)", qx64(1, 2, 3, 4, 5), 15);
	check("qx64(-1, 2, -3, 4, -5)", qx64(-1, 2, -3, 4, -5), -3);

	//check("qns()", qns(), 0);

	//cout << endl;

	return 0;

}

// eof
