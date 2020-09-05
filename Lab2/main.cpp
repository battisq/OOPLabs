#include <iostream>
#include <iomanip>
#include <clocale>
#include <string>
#include "Matrix.h"
#include <ctime>
#include <vector>

using namespace std;
using namespace Mathematics;

double f(int i, int j)
{
	srand((unsigned int)time(NULL));
	return rand() % 200 - 100.25;
}

int main(void)
{
	setlocale(LC_ALL, "Rus");

/*
	////Matrix a(2, 2, 4.2, 4.4, 6.2, 8.8, 0.0), b(2, 2, 1.1, 11.1, 1.01, 101.0), c;

	////cout << setw(5) << a << endl;
	////cout << setw(5) << b << endl;
	////
	////a += b;
	////cout << setw(5) << a << endl;
	////
	////c = a + b;
	////
	////cout << setw(5) << c << endl;

	//double (*fo)(int, int) = &f;

	//Matrix d(3, fo);

	//cout.width(7);
	//cout.precision(2);

	//cout << d;

	double *arr = new double[4];

	for (int i = 0; i < 2; i++)
		arr[i] = i + 1;

	Matrix e(3, 2, arr);

	cout << e;


	////cout.precision(3);

	//const Matrix w(2, 2, 7.3, 7.70, 0.0, 9.9);
	//Matrix z(2, 2, 7.3, 7.70);

	////z = 4;

	//try
	//{
	//	w[0][1] = 9;
	//}

	//catch (const string err)
	//{
	//	cout << err;
	//}
	//cout <<  w;

	////e += b;

	////cout << e;
	////try
	////{
	////	cout << e[10][10];
	////}
	////catch (const string err)
	////{
	////	cout << err;
	////}
	*/

	//Matrix z(3, 2, 7.2, 8.3, 1.1, 6.6, 4.4, 9.9), x(z);

	//cout << "Z:\n" << z << endl;

	//z *= 7;

	//cout << std::fixed << "Z:\n" << z << endl;

	//Matrix x(std::move(z));
	//cout << "X:\n" << x << endl;

	//cout << "Z:\n" << z << endl;
	//cout << "X:\n" << x << endl;

	Matrix m(2, 3, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
	cout << m[1][2] << endl;

	cin.get();
	return 0;
}