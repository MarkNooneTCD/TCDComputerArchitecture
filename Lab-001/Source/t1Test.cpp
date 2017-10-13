//
// t1Test.cpp
//
// Copyright (C) 2017 jones@scss.tcd.ie
//
// 02/10/17	first version
//


#include <iostream>         // cout
#include "t1.h"             //

using namespace std;        // cout

int g = 4;

//
// check
//
void check(char *s, int v, int expected) {
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

	//
	// t1
	//
	check("g", g, 4);

	check("min(1, 2, 3)", min(1, 2, 3), 1);
	check("min(3, 1, 2)", min(3, 1, 2), 1);
	check("min(2, 3, 1)", min(2, 3, 1), 1);
	check("min(-1, -2, -3)", min(-1, -2, -3), -3);
	check("min(-3, -1, -2)", min(-3, -1, -2), -3);
	check("min(-2, -3, -1)", min(-2, -3, -1), -3);
	check("min(-1, 2, 3)", min(-1, 2, 3), -1);
	check("min(3, -1, 2)", min(3, -1, 2), -1);
	check("min(2, 3, -1)", min(2, 3, -1), -1);

	check("p(1, 2, 3)", p(1, 2, 3, 4), 1);
	check("p(5, 6, 7)", p(5, 6, 7, 4), 4);

	check("gcd(14, 21)", gcd(14, 21), 7);
	check("gcd(1406700, 164115)", gcd(1406700, 164115), 23445);

	check("modulus(78, 25)", modulus(78, 25), 3);
	check("modulus(5, 2)", modulus(5, 2), 1);

	cout << endl;
	char p;
	cin >> p;

	return 0;
}
