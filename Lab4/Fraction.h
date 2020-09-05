#pragma once

#include <ostream>

namespace Mathematics
{
	class Fraction
	{
	private:
		int numerator;
		int denominator;

		void reduce(void);

	public:

		Fraction(int _numerator = 0, int _denominator = 1);

		int getNumerator(void) const;
		int getDenominator(void) const;

		std::pair<int, Fraction> toProper(void);
		Fraction & toImproper(int _integerPart);

		Fraction & operator += (const Fraction &_a);
		Fraction & operator -= (const Fraction &_a);
		Fraction & operator *= (const Fraction &_a);
		Fraction & operator /= (const Fraction &_a);

		friend bool operator == (const Fraction &_a, const Fraction &_b);
		friend bool operator != (const Fraction &_a, const Fraction &_b);
		friend bool operator !  (const Fraction &_a);

		friend bool operator >	(const Fraction &_a, const Fraction &_b);
		friend bool operator >= (const Fraction &_a, const Fraction &_b);
		friend bool operator <	(const Fraction &_a, const Fraction &_b);
		friend bool operator <= (const Fraction &_a, const Fraction &_b);
		
		friend Fraction operator + (const Fraction &_a, const Fraction &_b);
		friend Fraction operator - (const Fraction &_a, const Fraction &_b);
		friend Fraction operator * (const Fraction &_a, const Fraction &_b);
		friend Fraction operator / (const Fraction &_a, const Fraction &_b);
		
		friend std::ostream & operator << (std::ostream &_out, const Fraction &_a);

	};

	int nok(int _firstEl, int _secondEl); // Наименьшее общее кратное
	int nod(int _firstEl, int _secondEl); // Наибольший общий делитель
}