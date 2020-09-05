#pragma once

#include <iostream>

namespace Mathematics
{
	class Polynom
	{
	private:

		double *coefficients;
		int degree;

		void reduce(void);

	public:

		explicit Polynom(int _degree = 0, const double *_coefficients = NULL);
		Polynom(int _degree, double _el, ...);
		Polynom(double _number);
		Polynom(const Polynom &_a);
		Polynom(Polynom &&_a);

		~Polynom();

		int getDegree(void) const;

		Polynom & operator =  (const Polynom &_a);
		Polynom & operator =  (double _number);
		Polynom & operator =  (Polynom &&_a);

		Polynom & operator += (const Polynom & _a);
		Polynom & operator -= (const Polynom & _a);
		Polynom & operator *= (const Polynom & _a);
		Polynom & operator /= (const Polynom & _a);
		Polynom & operator %= (const Polynom & _a);

		double operator () (double _number);

		friend Polynom operator + (const Polynom &_a, const Polynom &_b);
		friend Polynom operator - (const Polynom &_a, const Polynom &_b);
		friend Polynom operator * (const Polynom &_a, const Polynom &_b);
		friend Polynom operator / (const Polynom &_a, const Polynom &_b);
		friend Polynom operator % (const Polynom &_a, const Polynom &_b);

		friend std::ostream & operator << (std::ostream &_out, const Polynom &_a);
		friend std::istream & operator >> (std::istream &_out, Polynom &_a);

		double & operator[] (int _i);
		double operator[] (int _i) const;
	};
}