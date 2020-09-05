#include "Fraction.h"
#include <iostream>
#include <string>

using namespace std;

namespace Mathematics
{
	void Fraction::reduce(void)
	{
		if (!denominator)
			throw invalid_argument("Знаменатель дроби не должен быть равен 0. Деление на ноль\n");

		if (denominator < 0)
		{
			denominator = -denominator;
			numerator = -numerator;
		}

		int div = nod(numerator, denominator);

		numerator /= div;
		denominator /= div;

		if (!numerator)
			denominator = 1;
	}

	Fraction::Fraction(int _numerator, int _denominator)
	{
		numerator = _numerator;
		denominator = _denominator;

		reduce();
	}

	pair<int, Fraction> Fraction::toProper(void)
	{
		return pair<int, Fraction> {numerator / denominator, Fraction(numerator % denominator, denominator)};
	}

	Fraction & Fraction::toImproper(int _integerPart)
	{
		*this += _integerPart;

		return *this;
	}

	int Fraction::getNumerator(void) const
	{
		return numerator;
	}

	int Fraction::getDenominator(void) const
	{
		return denominator;
	}

	Fraction & Fraction::operator += (const Fraction &_a)
	{
		__int64 newDen = nok(denominator, _a.denominator);

		numerator = (int)(numerator * (newDen / denominator) + _a.numerator * (newDen / _a.denominator));
		denominator = (int)newDen;

		reduce();

		return *this;
	}
	
	Fraction & Fraction::operator -= (const Fraction &_a)
	{
		__int64 newDen = nok(denominator, _a.denominator);

		numerator = (int)(numerator * (newDen / denominator) - _a.numerator * (newDen / _a.denominator));
		denominator = (int)newDen;

		reduce();

		return *this;
	}
	
	Fraction & Fraction::operator *= (const Fraction &_a)
	{
		numerator *= _a.numerator;
		denominator *= _a.denominator;

		reduce();

		return *this;
	}

	Fraction & Fraction::operator /= (const Fraction &_a)
	{
		numerator *= _a.denominator;
		denominator *= _a.numerator;

		reduce();

		return *this;
	}

	bool operator == (const Fraction &_a, const Fraction & _b)
	{
		return _a.numerator == _b.numerator && _a.denominator == _b.denominator;
	}

	bool operator != (const Fraction & _a, const Fraction & _b)
	{
		return !(_a == _b);
	}

	bool operator!(const Fraction & _a)
	{
		return !(_a.numerator);
	}

	bool operator > (const Fraction &_a, const Fraction & _b)
	{
		return (__int64)_a.numerator * (__int64)_b.denominator > (__int64)_a.denominator * (__int64)_b.numerator;
	}

	bool operator >= (const Fraction &_a, const Fraction & _b)
	{
		return _a == _b || _a > _b;
	}

	bool operator < (const Fraction &_a, const Fraction & _b)
	{
		return (__int64)_a.numerator *(__int64)_b.denominator < (__int64)_a.denominator * (__int64)_b.numerator;
	}

	bool operator <= (const Fraction &_a, const Fraction & _b)
	{
		return _a == _b || _a < _b;
	}

	Fraction operator + (const Fraction &_a, const Fraction & _b)
	{
		Fraction c(_a);

		return c += _b;
	}

	Fraction operator - (const Fraction &_a, const Fraction & _b)
	{
		Fraction c(_a);

		return c -= _b;
	}

	Fraction operator * (const Fraction &_a, const Fraction & _b)
	{
		Fraction c(_a);

		return c *= _b;
	}

	Fraction operator / (const Fraction &_a, const Fraction & _b)
	{
		Fraction c(_a);

		return c /= _b;
	}

	ostream & operator << (ostream & _out, const Fraction &_a)
	{

		if (_a.denominator == 1)
			_out << _a.numerator;
		else
			_out << _a.numerator << "/" << _a.denominator;

		return _out;
	}

	int nok(int _firstEl, int _secondEl)
	{
		return (_firstEl * _secondEl / nod(_firstEl, _secondEl));
	}

	int nod(int _firstEl, int _secondEl)
	{
		if (_firstEl < 0)
			_firstEl = -_firstEl;

		if (_secondEl < 0)
			_secondEl = -_secondEl;

		for (int i = _firstEl; i > 0; i--)
		{
			if (_firstEl % i == 0 && _secondEl % i == 0)
			{
				return i;
			}
		}

		return 1;
	}

}
