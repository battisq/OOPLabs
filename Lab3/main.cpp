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


	//cout << "Введите вектор:" << endl;
	//cin >> a;

	//cout << "Введите вектор:" << endl;
	//cin >> a;

	//Vector c(a);
	//c.transposition();

	//cout << "Вектор-столбец на вектор-строку\n" << (c *= a) << endl << endl;
	cout << "Вектор-строку на вектор-столбец\n" << (c *= a) << endl;

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