#include <iostream>
#include <clocale>
#include "Fraction.h"
#include "Polynom.h"

using namespace std;
using namespace Mathematics;

int main(void)
{
	setlocale(LC_ALL, "Rus");

	//cout << 77 % 12 << endl;

	Fraction a(10, 5), a1(a);
	//const Fraction b(2, 3);
	//cout << a.getCountId();
	//a += b;
	cout << a << endl;

	//cout << a.getNumerator() << "/" << a.getDenominator() << endl;

	Polynom p(2, -4.0, -2.0, 1.0), w(1, 2.0, 1.0);

	//cout << p << "\n" << w << "\n";

	//cout << p + w << endl;
	//cout << p - w << endl;
	//cout << p * w << endl;
	cout << p / w << endl;
	cout << p % w << endl;

	//Fraction a(1, 3);


	//const Polynom l(2, 1.0, -11.11, 1.0);

	//cout << p << endl;

	cin.get();
	return 0;
}