#include <iostream>
#include <clocale>
#include <string>
#include "Hierarchy.h"

using namespace std;
using namespace Mathematics;

int main(void)
{
	setlocale(LC_ALL, "Rus");
	
	Vector a(4);
	Vector c(4);
	a += c;
	//Matrix d;

	//d = a * c;


	//cout << "������� ������:" << endl;
	//cin >> a;

	//cout << "������� ������:" << endl;
	//cin >> a;

	//Vector c(a);
	//c.transposition();

	//cout << "������-������� �� ������-������\n" << (c *= a) << endl << endl;
	cout << "������-������ �� ������-�������\n" << (c *= a) << endl;

	//cout << "\n" << a;
	//cout << "\n" << c;

	//cout << a * c << endl;

	//a *= c;

	//cout << c * a << endl;
	Vector v(1, 2.0);
	Matrix m(1, 1, 2.0);
	Vector v2 = v * m;
	Matrix m2 = v * m;
	cout << v2 << endl;
	cout << m2 << endl;

	system("pause > nul");
	return 0;
}