#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
namespace Mathematics
{
	template <class Type> class TPolynom
	{
	private:

		int id;
		static int countId;

		Type *coefficients;
		int degree, sizeCoeff;

		void reduce(void)
		{
			int newDegree = degree;

			for (int i = degree; i >= 0; i--)
				if (!coefficients[i])
					newDegree--; 
				else
					break;

			if (newDegree > 0)
			{
				Type *newCoeff = new Type[newDegree + 1];

				for (int i = 0; i < newDegree + 1; i++)
					newCoeff[i] = coefficients[i];

				delete[] coefficients;

				coefficients = newCoeff;
				degree = newDegree;
				sizeCoeff = newDegree + 1;
			}
		}

	public:

		explicit TPolynom(int _degree = 0, Type *_coefficients = NULL)
		{
			if (_degree < 0)
				throw  std::invalid_argument("Степень полинома " + std::to_string(id) + " отрицательна.");

			degree = _degree;
			sizeCoeff = degree + 1;
			coefficients = new Type[sizeCoeff];

			if (_coefficients)
				for (int i = 0; i < sizeCoeff; i++)
					coefficients[i] = _coefficients[i];
			else
				for (int i = 0; i < sizeCoeff; i++)
					coefficients[i] = 0;

			reduce();

			id = ++countId;
			cout << "Конструктор полинома (Размер типа " << sizeof(Type) << " байт) " << id << endl;
		}

		TPolynom(int _degree, Type _el, ...) : TPolynom(_degree, &_el) {}

		TPolynom(const TPolynom<Type> & _a) : TPolynom(_a.degree, _a.coefficients) {}

		TPolynom(TPolynom && _a) : TPolynom()
		{
			swap(degree, _a.degree);
			swap(coefficients, _a.coefficients);
			swap(sizeCoeff, _a.sizeCoeff);

			reduce();
		}

		~TPolynom()
		{
			delete[] coefficients;

			std::cout << "Деструктор матрицы (Размер типа " << sizeof(Type) << " байт) " << id << std::endl;
		}

		int getDegree(void) const
		{
			return degree;
		}

		int getId(void) const
		{
			return id;
		}

		int getCountId(void)
		{
			return countId;
		}

		TPolynom<Type> & operator = (const TPolynom<Type> & _a)
		{
			if (degree != _a.degree)
			{
				delete[] coefficients;
				coefficients = new Type[_a.sizeCoeff];
			}

			degree = _a.degree;
			sizeCoeff = _a.sizeCoeff;

			for (int i = 0; i < sizeCoeff; i++)
				coefficients[i] = _a.coefficients[i];

			return *this;
		}

		TPolynom<Type> & operator = (Type _number)
		{
			if (degree != 1)
			{
				delete[] coefficients;
				coefficients = new Type[1];
			}

			degree = 0;
			sizeCoeff = 1;
			coefficients[0] = _number;

			return *this;
		}

		TPolynom<Type> & operator = (TPolynom<Type> && _a)
		{
			std::swap(degree, _a.degree);
			std::swap(sizeCoeff, _a.sizeCoeff);
			std::swap(coefficients, _a.coefficients);

			return *this;
		}

		TPolynom<Type> & operator += (const TPolynom<Type> & _a)
		{
			if (degree >= _a.degree)
			{
				for (int i = 0; i < _a.sizeCoeff; i++)
					coefficients[i] += _a.coefficients[i];
			}
			else
			{
				Type *newCoeffcients = new Type[_a.sizeCoeff];

				for (int i = 0; i < sizeCoeff; i++)
					newCoeffcients[i] = coefficients[i] + _a.coefficients[i];

				for (int i = sizeCoeff; i < _a.sizeCoeff; i++)
					newCoeffcients[i] = _a.coefficients[i];

				delete[] coefficients;

				coefficients = newCoeffcients;
				degree = _a.degree;
				sizeCoeff = _a.sizeCoeff;
			}

			reduce();

			return *this;
		}

		TPolynom<Type> & operator -= (const TPolynom<Type> & _a)
		{
			if (degree >= _a.degree)
			{
				for (int i = 0; i < _a.sizeCoeff; i++)
					coefficients[i] -= _a.coefficients[i];
			}
			else
			{
				Type *newCoeffcients = new Type[_a.sizeCoeff];

				for (int i = 0; i < sizeCoeff; i++)
					newCoeffcients[i] = coefficients[i] - _a.coefficients[i];

				for (int i = sizeCoeff; i < _a.sizeCoeff; i++)
					newCoeffcients[i] = _a.coefficients[i];

				delete[] coefficients;

				coefficients = newCoeffcients;
				degree = _a.degree;
				sizeCoeff = _a.sizeCoeff;
			}

			reduce();

			return *this;
		}

		TPolynom<Type> & operator *= (const TPolynom<Type> & _a)
		{
			int sizeNewCoeff = sizeCoeff + _a.sizeCoeff - 1;
			Type *newCoefficients = new Type[sizeNewCoeff];

			for (int i = 0; i < sizeNewCoeff; i++)
				newCoefficients[i] = 0.0;

			for (int i = 0; i < sizeCoeff; i++)
				for (int j = 0; j < _a.sizeCoeff; j++)
					newCoefficients[i + j] += coefficients[i] * _a.coefficients[j];

			delete[] coefficients;

			coefficients = newCoefficients;
			sizeCoeff = sizeNewCoeff;
			degree = sizeCoeff - 1;

			reduce();

			return *this;
		}

		TPolynom<Type> & operator /= (const TPolynom<Type> & _a)
		{
			if (!_a.coefficients[_a.degree])
				throw std::logic_error("Деление на ноль\n");

			int newDegree = degree - _a.degree;

			if (newDegree < 0)
			{
				if (degree > 1)
				{
					delete[] coefficients;
					coefficients = new Type[1];
				}

				coefficients[0] = 0;

				return *this;
			}

			TPolynom<Type> result(newDegree);

			for (int i = 0; i < result.sizeCoeff; i++)
			{
				result.coefficients[newDegree - i] = coefficients[degree - i] / _a.coefficients[_a.degree];
			
				for (int j = 0; j < _a.sizeCoeff; j++)
				{
					coefficients[degree - j - i] -= _a.coefficients[_a.degree - j] * result.coefficients[newDegree - i];
				}
			}

			delete[] coefficients;
			coefficients = NULL;

			*this = std::move(result);

			reduce();

			return *this;
		}

		TPolynom<Type> & operator %= (const TPolynom<Type> & _a)
		{
			if (!_a.coefficients[_a.degree])
				throw std::logic_error("Деление на ноль\n");

			int newDegree = degree - _a.degree;

			for (int i = 0; i < newDegree + 1; i++)
			{
				Type element = coefficients[degree - i] / _a.coefficients[_a.degree];

				for (int j = 0; j < _a.sizeCoeff; j++)
				{
					coefficients[degree - j - i] -= _a.coefficients[_a.degree - j] * element;
				}
			}

			reduce();

			return *this;
		}

		Type operator () (Type _number)
		{
			Type result = 0.0, x = 1.0;

			for (int i = 0; i < sizeCoeff; i++)
			{
				result += coefficients[i] * x;
				x *= _number;
			}

			return result;
		}

		Type & operator[](int _i)
		{
			if (0 < _i || _i > degree)
				throw std::out_of_range("Данной степени в полиноме " + to_string(id) + " нет\n");

			return coefficients[_i];
		}

		const Type & operator[](int _i) const
		{
			if (0 < _i || _i > degree)
				throw std::out_of_range("Данной степени в полиноме " + to_string(id) + " нет\n");

			return coefficients[_i];
		}

		friend TPolynom<Type> operator + (const TPolynom<Type> &_a, const TPolynom<Type> &_b)
		{
			TPolynom<Type> c(_a);

			return c += _b;
		}

		friend TPolynom<Type> operator - (const TPolynom<Type> &_a, const TPolynom<Type> &_b)
		{
			TPolynom<Type> c(_a);

			return c -= _b;
		}

		friend TPolynom<Type> operator * (const TPolynom<Type> &_a, const TPolynom<Type> &_b)
		{
			TPolynom<Type> c(_a);

			return c *= _b;
		}

		friend TPolynom<Type> operator / (const TPolynom<Type> &_a, const TPolynom<Type> &_b)
		{
			TPolynom<Type> c(_a);

			return c /= _b;
		}

		friend TPolynom<Type> operator % (const TPolynom<Type> &_a, const TPolynom<Type> &_b)
		{
			TPolynom<Type> c(_a);

			return c %= _b;
		}

		friend std::ostream & operator << (std::ostream &_out, const TPolynom<Type> &_a)
		{
			std::streamsize width = _out.width();

			_out.width(width);

			cout << _a.coefficients[0];

			for (int i = 1; i < _a.sizeCoeff; i++)
			{
				if (!_a.coefficients[i])
					continue;

				_out << " + ";
				_out.width(width);
				_out << _a.coefficients[i];

				if (i == 1)
					_out << "x";
				else
					_out << "x^" << i;
			}

			cout << endl;

			return _out;
		}

		friend std::istream & operator >> (std::istream & _in, TPolynom<Type> & _a)
		{
			for (int i = 0; i < _a.sizeCoeff; i++)
				_in >> _a.coefficients[i];

			return _in;
		}

	};

	template<class Type> int TPolynom<Type>::countId = 0;

}