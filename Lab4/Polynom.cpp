#include "Polynom.h"
#include <string>

using namespace std;

namespace Mathematics
{
	void Polynom::reduce(void)
	{
		int newDegree = degree;

		for (int i = degree; i >= 0; i--)
			if (coefficients[i])
				break;
			else
				newDegree--;

		if (newDegree >= 0 && newDegree != degree)
		{
			double *newCoeff = new double[newDegree + 1];

			for (int i = 0; i <= newDegree; i++)
				newCoeff[i] = coefficients[i];

			delete[] coefficients;

			coefficients = newCoeff;
			degree = newDegree;
		}
	}

	Polynom::Polynom(int _degree, const double *_coefficients)
	{
		if (_degree < 0)
			throw  invalid_argument("Степень полинома отрицательна.");

		degree = _degree;
		coefficients = new double[degree + 1];

		if (_coefficients)
		{
			for (int i = 0; i <= degree; i++)
				coefficients[i] = _coefficients[i];

			reduce();
		}
		else
			for (int i = 0; i <= degree; i++)
				coefficients[i] = 0.0;
	}

	Polynom::Polynom(int _degree, double _el, ...) : Polynom(_degree, &_el) {}

	Polynom::Polynom(double _number)
	{
		operator = (_number);
	}

	Polynom::Polynom(const Polynom & _a) : Polynom(_a.degree, _a.coefficients) {}

	Polynom::Polynom(Polynom && _a) : degree(0), coefficients(NULL)
	{
		operator = (move(_a));
	}

	Polynom::~Polynom()
	{
		if (coefficients)
			delete[] coefficients;
	}

	int Polynom::getDegree(void) const
	{
		return degree;
	}

	Polynom & Polynom::operator = (const Polynom & _a)
	{
		if (degree != _a.degree)
		{
			if (coefficients)
				delete[] coefficients;

			coefficients = new double[_a.degree + 1];
		}

		degree = _a.degree;
		
		for (int i = 0; i <= degree; i++)
			coefficients[i] = _a.coefficients[i];

		return *this;
	}

	Polynom & Polynom::operator = (double _number)
	{
		if (degree != 1)
		{
			if (coefficients)
				delete[] coefficients;

			coefficients = new double[1];
		}

		degree = 0;
		coefficients[0] = _number;

		return *this;
	}

	Polynom & Polynom::operator = (Polynom && _a)
	{
		swap(degree, _a.degree);
		swap(coefficients, _a.coefficients);

		return *this;
	}

	Polynom & Polynom::operator += (const Polynom & _a)
	{
		if (degree >= _a.degree)
		{
			for (int i = 0; i <= _a.degree; i++)
				coefficients[i] += _a.coefficients[i];
		}
		else
		{
			double *newCoeffcients = new double[_a.degree + 1];

			for (int i = 0; i <= degree; i++)
				newCoeffcients[i] = coefficients[i] + _a.coefficients[i];

			for (int i = degree; i <= _a.degree; i++)
				newCoeffcients[i] = _a.coefficients[i];

			delete[] coefficients;

			coefficients = newCoeffcients;
			degree = _a.degree;
		}

		reduce();

		return *this;
	}

	Polynom & Polynom::operator -= (const Polynom & _a)
	{
		if (degree >= _a.degree)
		{
			for (int i = 0; i <= _a.degree; i++)
				coefficients[i] -= _a.coefficients[i];
		}
		else
		{
			double *newCoeffcients = new double[_a.degree + 1];

			for (int i = 0; i <= degree; i++)
				newCoeffcients[i] = coefficients[i] - _a.coefficients[i];

			for (int i = degree; i <= _a.degree; i++)
				newCoeffcients[i] = -_a.coefficients[i];

			delete[] coefficients;

			coefficients = newCoeffcients;
			degree = _a.degree;
		}

		reduce();

		return *this;
	}

	Polynom & Polynom::operator *= (const Polynom & _a)
	{
		int newDegree = degree + _a.degree;
		double *newCoefficients = new double[newDegree + 1];

		for (int i = 0; i <= newDegree; i++)
			newCoefficients[i] = 0.0;

		for (int i = 0; i <= newDegree; i++)
			for (int j = 0; j <= _a.degree; j++)
				newCoefficients[i + j] += coefficients[i] * _a.coefficients[j];

		delete[] coefficients;

		coefficients = newCoefficients;
		degree = newDegree;

		reduce();

		return *this;
	}

	Polynom & Polynom::operator /= (const Polynom & _a)
	{
		if (!_a.coefficients[_a.degree])
			throw logic_error("Деление на ноль\n");

		int newDegree = degree - _a.degree;

		if (newDegree < 0)
		{
			*this = 0.0;

			return *this;
		}

		Polynom result(newDegree);

		for (int i = 0; i <= result.degree; i++)
		{
			result.coefficients[newDegree - i] = coefficients[degree - i] / _a.coefficients[_a.degree];

			for (int j = 0; j <= _a.degree; j++)
			{
				coefficients[degree - j - i] -= _a.coefficients[_a.degree - j] * result.coefficients[newDegree - i];
			}
		}

		*this = move(result);

		reduce();

		return *this;
	}

	Polynom & Polynom::operator %= (const Polynom & _a)
	{
		if (!_a.coefficients[_a.degree])
			throw logic_error("Деление на ноль\n");

		int newDegree = degree - _a.degree;

		for (int i = 0; i < newDegree + 1; i++)
		{
			double element = coefficients[degree - i] / _a.coefficients[_a.degree];

			for (int j = 0; j <= _a.degree; j++)
			{
				coefficients[degree - j - i] -= _a.coefficients[_a.degree - j] * element;
			}
		}

		reduce();

		return *this;
	}

	double Polynom::operator () (double _number)
	{
		double result = 0.0, x = 1.0;

		for (int i = 0; i <= degree; i++)
		{
			result += coefficients[i] * x;
			x *= _number;
		}

		return result;
	}

	double & Polynom::operator[](int _i)
	{
		if (_i < 0 || degree < _i)
			throw out_of_range("Данной степени в полиноме нет\n");

		return coefficients[_i];
	}

	double Polynom::operator[](int _i) const
	{
		if (_i < 0 || degree < _i)
			throw out_of_range("Данной степени в полиноме нет\n");

		return coefficients[_i];
	}

	Polynom operator + (const Polynom &_a, const Polynom &_b)
	{
		Polynom c(_a);

		return c += _b;
	}

	Polynom operator - (const Polynom &_a, const Polynom &_b)
	{
		Polynom c(_a);

		return c -= _b;
	}

	Polynom operator * (const Polynom &_a, const Polynom &_b)
	{
		Polynom c(_a);

		return c *= _b;
	}

	Polynom operator / (const Polynom &_a, const Polynom &_b)
	{
		Polynom c(_a);

		return c /= _b;
	}

	Polynom operator % (const Polynom &_a, const Polynom &_b)
	{
		Polynom c(_a);

		return c %= _b;
	}

	ostream & operator << (ostream &_out, const Polynom &_a)
	{
		streamsize width = _out.width();

		_out.width(width);

		cout << _a.coefficients[0];

		for (int i = 1; i <= _a.degree; i++)
		{
			if (!_a.coefficients[i])
				continue;

			_out.width(width);
			_out << (_a.coefficients[i] >= 0 ? " + " : " - ");

			_out.width(width);

			if(_a.coefficients[i] != 1 && _a.coefficients[i] != -1 && _a.coefficients[i] || !i)
				_out << (_a.coefficients[i] > 0 ? _a.coefficients[i] : -_a.coefficients[i]);

			if (i == 1)
				_out << "x";
			else
				_out << "x^" << i;
		}

		return _out;
	}

	istream & operator >> (istream & _in, Polynom & _a)
	{
		for (int i = 0; i <= _a.degree; i++)
			_in >> _a.coefficients[i];

		return _in;
	}
}