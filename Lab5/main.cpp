#include "TMatrix.h"
#include "TPolynom.h"
#include "TFraction.h"
#include "stdafx.h"

using namespace Mathematics;
using namespace std;

int main(void)
{
	setlocale(LC_ALL, "Rus");

	/*

	Matrix av(2, 2, 1.0, 2.0, 3.0, 4.0), bv(2, 2, 5.0, 6.0, 7.0, 8.0), a1v(2, 2, 1.0, 2.0, 3.0, 4.0), b1v(2, 2, 5.0, 6.0, 7.0, 8.0);
	TMatrix<Matrix> cv(2, 2);//, a, b, a1, b1);

	TMatrix<double> a(2, 2, 1.0, 2.0, 3.0, 4.0), b(2, 2, 5.0, 6.0, 7.0, 8.0), a1(2, 2, 1.0, 2.0, 3.0, 4.0), b1(2, 2, 5.0, 6.0, 7.0, 8.0);
	TMatrix<TMatrix<double>> c(2, 2);//, a, b, a1, b1);
	//cout << (c += c1);

	c[0][0] = a;
	c[0][1] = a1;
	c[1][0] = b;
	c[1][1] = b1;
	cout.width(4);
	cout <<  c;

	//Fraction fr1(2, 7), fr2(1, 8), fr3(7, 14), fr4(1, 3);
	//TMatrix<Fraction> tmfr(2, 2, fr1, fr2, fr3, fr4), tmfr2(2, 2, fr1, fr2, fr3, fr4);

	//cout << tmfr + tmfr2;

	//Fraction *a = new Fraction[3];


	//TPolynom<double> a(3, 1.0, 0.0, 8.0, 6.0), b(1, 8.0, 9.0);
	
	//Fraction c1(2, 7), c2(3, 8), c3(3, 88), c4(4, 9);
	//Fraction f1(2, 96), f2(1, 2), f3(7, 9), f4(44, 93);

	//TPolynom<Fraction> af(3, c1, c2, c3, c4), ah(3, f1, f2, f3, f4);

	//cout.width(5);
	//cout << (af % ah);

	//Polynom tt(5, 0.0, 5.0, 0.0, -4.0, 1.0, 1.0), pp(3, 2.0, -2.0, -1.0, 2.0);

	//cout << tt << endl;
	//cout << pp << endl;
	//cout << nod(tt, pp);

	//Polynom aa(3, 1.0, 0.0, 8.0, 6.0), bb(2, 99.0, 668.0, 8.0);
	//TFraction<Polynom> dd(aa, bb);

	//cout << nod(bb, aa) << endl;
	//cout << (dd * bb) << endl;

	//Polynom fx(5, -3.0, -4.0, -1.0, 3.0, 1.0), gx(3, -3.0, 2.0, 10.0, 3.0);

	//cout << nod(fx, gx);
	//cout << nok(fx, gx);

	//cout << nod(-5, 15);

	//TPolynom<int> df(0, 7), gh(0, 5);
	*/

	TMatrix<double> q[4] = { TMatrix<double>(2, 2, 1.0, 2.0, 3.0, 4.0), TMatrix<double>(2, 2, 1.0, 2.0, 3.0, 4.0), TMatrix<double>(2, 2, 1.0, 2.0, 3.0, 4.0), TMatrix<double>(2, 2, 1.0, 2.0, 3.0, 4.0) };
	TMatrix<TMatrix<double>> m1(2, 2, q);
	TMatrix<TMatrix<double>> m2(2, 2, q);

	//cout << m1 << endl << m2 << endl;
	//cout << m1 * m2 << endl;
	cout << m1.minEl();
	
	//TMatrix<Matrix> tm1(2, 2, Matrix(2, 2, 1.0, 1.0, 1.0, 1.0), Matrix(2, 2, 2.0, 2.0, 2.0, 2.0), Matrix(2, 2, 3.0, 3.0, 3.0, 3.0), Matrix(2, 2, 4.0, 4.0, 4.0, 4.0)), tm2(tm1);

	//cout << tm1 << endl << tm2 << endl;
	

	system("pause");

	return 0;
}