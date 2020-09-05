#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <math.h>
#include "..\Lab4\Polynom.h"

using std::cout;
using std::endl;

namespace Mathematics
{

#pragma region temp

	template<class Type> class TFraction
	{
	private:
		Type numerator;
		Type denominator;

		static int countId;
		int id;

		void reduce(void)
		{
			Type div = nod(numerator, denominator);

			numerator /= div;
			denominator /= div;
		}

	public:

		explicit TFraction(Type _numerator = 0, Type _denominator = 1)
		{
			if (!_denominator)
				throw std::invalid_argument("Знаменатель дроби " + std::to_string(id) + " не должен быть равен 0. Деление на ноль\n");

			numerator = _numerator;
			denominator = _denominator;

			if (denominator < 0)
			{
				denominator *= -1;
				numerator *= -1;
			}

			reduce();

			id = ++countId;
			cout << "Конструктор дроби (Размер типа " << sizeof(Type) << " байт) " << id << endl;

		}

		TFraction(const TFraction<Type> & _a) : TFraction(_a.numerator, _a.denominator) {}

		~TFraction()
		{
			cout << "Деструктор дроби " << id << endl;
		}

		std::pair<Type, TFraction<Type>> inProper(void)
		{
			Type div = nod(numerator, denominator);

			return std::pair<Type, TFraction<Type>> {div, TFraction<Type>(numerator % div, denominator)};
		}

		TFraction<Type> & inImproper(int _integerPart)
		{
			*this += _integerPart;

			return *this;
		}

		Type getNumerator(void) const
		{
			return numerator;
		}

		Type getDenominator(void) const
		{
			return denominator;
		}

		int getId(void) const
		{
			return id;
		}

		int getCountId(void)
		{
			return countId;
		}

		TFraction<Type> & operator = (const TFraction<Type> & _a)
		{
			numerator = _a.numerator;
			denominator = _a.denominator;

			return *this;
		}

		TFraction<Type> & operator = (int _number)
		{
			numerator = _number;
			denominator = 1;

			return *this;
		}

		TFraction<Type> & operator += (const TFraction<Type> &_a)
		{
			Type newDen = nok(denominator, _a.denominator);

			numerator = numerator * newDen / denominator + _a.numerator * newDen / _a.denominator;
			denominator = newDen;

			reduce();

			return *this;
		}

		TFraction<Type> & operator += (int _number)
		{
			numerator += _number * denominator;

			return *this;
		}

		TFraction<Type> & operator -= (const TFraction<Type> &_a)
		{
			Type newDen = nok(denominator, _a.denominator);

			numerator = numerator * newDen / denominator - _a.numerator * newDen / _a.denominator;
			denominator = newDen;

			reduce();

			return *this;
		}

		TFraction<Type> & operator -= (int _number)
		{
			numerator -= _number * denominator;

			return *this;
		}

		TFraction<Type> & operator *= (const TFraction<Type> &_a)
		{
			numerator *= _a.numerator;
			denominator *= _a.denominator;

			reduce();

			return *this;
		}

		TFraction<Type> & operator *= (int _number)
		{
			numerator *= _number;

			return *this;
		}

		TFraction<Type> & operator /= (const TFraction<Type> &_a)
		{
			numerator *= _a.denominator;
			denominator *= _a.numerator;

			reduce();

			return *this;
		}

		TFraction<Type> & operator /= (int _number)
		{
			denominator *= _number;

			return *this;
		}
	
		friend TFraction<Type> operator + (const TFraction<Type> &_a, const TFraction<Type> & _b)
		{
			TFraction<Type> c(_a);

			return c += _b;
		}

		friend TFraction<Type> operator + (const TFraction<Type> & _a, int _number)
		{
			TFraction<Type> c(_a);

			return c += _number;
		}

		friend TFraction<Type> operator + (int _number, const TFraction<Type> & _b)
		{
			TFraction<Type> c(_b);

			return c += _number;
		}

		friend TFraction<Type> operator - (const TFraction<Type> &_a, const TFraction<Type> & _b)
		{
			TFraction<Type> c(_a);

			return c -= _b;
		}

		friend TFraction<Type> operator - (const TFraction<Type> & _a, int _number)
		{
			TFraction<Type> c(_a);

			return c -= _number;
		}

		friend TFraction<Type> operator - (int _number, const TFraction<Type> & _b)
		{
			TFraction<Type> c(-_b.numerator, _b.denominator);

			return c += _number;
		}

		friend TFraction<Type> operator * (const TFraction<Type> &_a, const TFraction<Type> & _b)
		{
			TFraction<Type> c(_a);

			return c *= _b;
		}

		friend TFraction<Type> operator * (const TFraction<Type> & _a, int _number)
		{
			TFraction<Type> c(_a);

			return c *= _number;
		}

		friend TFraction<Type> operator * (int _number, const TFraction<Type> & _b)
		{
			TFraction<Type> c(_b);

			return c *= _number;
		}

		friend TFraction<Type> operator / (const TFraction<Type> &_a, const TFraction<Type> & _b)
		{
			TFraction<Type> c(_a);

			return c /= _b;
		}

		friend TFraction<Type> operator / (const TFraction<Type> & _a, int _number)
		{
			TFraction<Type> c(_a);

			return c /= _number;
		}

		friend TFraction<Type> operator / (int _number, const TFraction<Type> & _b)
		{
			TFraction<Type> c(_b.denominator, _b.numerator);

			return c *= _number;
		}

		friend std::ostream & operator << (std::ostream & _out, const TFraction<Type> &_a)
		{
			std::streamsize width = _out.width(), precition = _out.precision();

			_out.width(width);
			_out.precision(precition);
			_out << _a.numerator << "/" << _a.denominator;

			return _out;
		}

		Type nok(Type _firstEl, Type _secondEl)
		{
			return (_firstEl*_secondEl / nod(_firstEl, _secondEl));
		}

		Type nod(Type _firstEl, Type _secondEl)
		{
			if (_firstEl < 0)
				_firstEl *= -1;

			if (_secondEl < 0)
				_secondEl *= -1;

			for (int i = _firstEl; i > 0; i--)
			{
				if (_firstEl % i == 0 && _secondEl % i == 0)
				{
					return i;
				}
			}

			return 1;
		}

	};

	template<class Type> int TFraction<Type>::countId = 0;

#pragma endregion

#pragma region tempPolynom
	
	Polynom nod(const Polynom &_a, const Polynom &_b)
	{
		Polynom a, b, c;

		if (_a.getDegree() >= _b.getDegree())
		{
			a = _a;
			b = _b;
		}
		else
		{
			a = _b;
			b = _a;
		}
	
		c = a % b;

		while (c[c.getDegree()] != 0)
		{
			cout << c;

			a = b;
			b = c;
			c = a % b;

			if (c.getDegree() == 1)
				if ((c[0] * -1) / c[1] == 0)
					break;
		}

		return b;
	}

	Polynom nok(const Polynom &_a, const Polynom &_b)
	{
		return (_a * _b / nod(_a, _b));
	}

	template<> class TFraction<Polynom>
	{
	private:
		Polynom numerator;
		Polynom denominator;

		static int countId;
		int id;

		void reduce(void)
		{
			Polynom div = nod(numerator, denominator);

			numerator /= div;
			denominator /= div;
		}

	public:

		TFraction() : numerator(0, 0.0), denominator(0, 1.0)
		{
			id = ++countId;
			cout << "Конструктор полиномиальной дроби " << id << endl;
		}

		TFraction(const Polynom &_numerator) : numerator(_numerator), denominator(0, 1.0)
		{
			id = ++countId;
			cout << "Конструктор полиномиальной дроби " << id << endl;
		}

		TFraction(const Polynom & _numerator, const Polynom & _denominator)
		{
			if (!_denominator[_denominator.getDegree()] )
				throw std::invalid_argument("Знаменатель полиномиальной дроби " + std::to_string(id) + " не должен быть равен 0. Деление на ноль\n");

			numerator = _numerator;
			denominator = _denominator;

			reduce();

			id = ++countId;
			cout << "Конструктор полиномиальной дроби " << id << endl;
		}
		
		TFraction(const TFraction & _a) : TFraction(_a.numerator, _a.denominator) {}

		~TFraction()
		{
			cout << "Деструктор полиномиальной дроби " << id << endl;
		}

		std::pair<Polynom, TFraction<Polynom>> inProper(void)
		{
			Polynom div = nod(numerator, denominator);

			return std::pair<Polynom, TFraction<Polynom>> {div, TFraction<Polynom>(numerator % div, denominator)};
		}

		TFraction<Polynom> & inImproper(Polynom _integerPart)
		{
			*this += _integerPart;

			return *this;
		}

		Polynom getNumerator(void) const
		{
			return numerator;
		}

		Polynom getDenominator(void) const
		{
			return denominator;
		}

		int getId(void) const
		{
			return id;
		}

		int getCountId(void)
		{
			return countId;
		}

		TFraction<Polynom> & operator = (const TFraction<Polynom> & _a)
		{
			numerator = _a.numerator;
			denominator = _a.denominator;

			return *this;
		}

		TFraction<Polynom> & operator = (const Polynom & _a)
		{
			numerator = _a;
			denominator = Polynom(0, 1.0);

			return *this;
		}

		TFraction<Polynom> & operator += (const TFraction<Polynom> &_a)
		{
			Polynom newDen = nok(denominator, _a.denominator);

			numerator = numerator * newDen / denominator + _a.numerator * newDen / _a.denominator;
			denominator = newDen;

			reduce();

			return *this;
		}

		TFraction<Polynom> & operator += (const Polynom & _a)
		{
			numerator += _a * denominator;

			return *this;
		}

		TFraction<Polynom> & operator -= (const TFraction<Polynom> &_a)
		{
			Polynom newDen = nok(denominator, _a.denominator);

			numerator = numerator * newDen / denominator - _a.numerator * newDen / _a.denominator;
			denominator = newDen;

			reduce();

			return *this;
		}

		TFraction<Polynom> & operator -= (const Polynom & _a)
		{
			numerator -= _a * denominator;

			return *this;
		}

		TFraction<Polynom> & operator *= (const TFraction<Polynom> &_a)
		{
			numerator *= _a.numerator;
			denominator *= _a.denominator;

			reduce();

			return *this;
		}

		TFraction<Polynom> & operator *= (const Polynom & _a)
		{
			numerator *= _a;

			return *this;
		}

		TFraction<Polynom> & operator /= (const TFraction<Polynom> &_a)
		{
			numerator *= _a.denominator;
			denominator *= _a.numerator;

			reduce();

			return *this;
		}

		TFraction<Polynom> & operator /= (const Polynom & _a)
		{
			denominator *= _a;

			return *this;
		}

		friend TFraction<Polynom> operator + (const TFraction<Polynom> &_a, const TFraction<Polynom> & _b)
		{
			TFraction<Polynom> c(_a);

			return c += _b;
		}

		friend TFraction<Polynom> operator + (const TFraction<Polynom> & _a, const Polynom & _b)
		{
			TFraction<Polynom> c(_a);

			return c += _b;
		}

		friend TFraction<Polynom> operator + (const Polynom & _a, const TFraction<Polynom> & _b)
		{
			TFraction<Polynom> c(_b);

			return c += _a;
		}

		friend TFraction<Polynom> operator - (const TFraction<Polynom> &_a, const TFraction<Polynom> & _b)
		{
			TFraction<Polynom> c(_a);

			return c -= _b;
		}

		friend TFraction<Polynom> operator - (const TFraction<Polynom> & _a, const Polynom & _b)
		{
			TFraction<Polynom> c(_a);

			return c -= _b;
		}

		friend TFraction<Polynom> operator - (const Polynom & _a, const TFraction<Polynom> & _b)
		{
			TFraction<Polynom> c(_b.numerator * Polynom(0, -1.0), _b.denominator);

			return c += _a;
		}

		friend TFraction<Polynom> operator * (const TFraction<Polynom> &_a, const TFraction<Polynom> & _b)
		{
			TFraction<Polynom> c(_a);

			return c *= _b;
		}

		friend TFraction<Polynom> operator * (const TFraction<Polynom> & _a, const Polynom & _b)
		{
			TFraction<Polynom> c(_a);

			return c *= _b;
		}

		friend TFraction<Polynom> operator * (const Polynom & _a, const TFraction<Polynom> & _b)
		{
			TFraction<Polynom> c(_b);

			return c *= _b;
		}

		friend TFraction<Polynom> operator / (const TFraction<Polynom> &_a, const TFraction<Polynom> & _b)
		{
			TFraction<Polynom> c(_a);

			return c /= _b;
		}

		friend TFraction<Polynom> operator / (const TFraction<Polynom> & _a, const Polynom & _b)
		{
			TFraction<Polynom> c(_a);

			return c /= _b;
		}

		friend TFraction<Polynom> operator / (const Polynom & _a, const TFraction<Polynom> & _b)
		{
			TFraction<Polynom> c(_b.denominator, _b.numerator);

			return c *= _a;
		}

		friend std::ostream & operator << (std::ostream & _out, const TFraction<Polynom> &_a)
		{
			std::streamsize width = _out.width(), precition = _out.precision();

			_out.width(width);
			_out.precision(precition);

			_out << "(" << _a.numerator << ")/(" << _a.denominator << ")";

			return _out;
		}
	};

	int TFraction<Polynom>::countId = 0;

#pragma endregion

}