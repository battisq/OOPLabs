#pragma once

#include <iostream>

namespace Mathematics
{
	class Base
	{
	protected:

		int rows;
		int cols;
		double *array;

		Base();

		Base(int _rows, int _cols, const double *_array = NULL);

		Base(const Base &_a);
		Base(Base &&_a);

		bool getRank(const Base &_a) const;

	public:
	
		virtual ~Base();

		bool checkSum(const Base &_a) const;
		bool checkMul(const Base &_a) const;

		static bool checkSum(const Base &_a, const Base &_b);
		static bool checkMul(const Base &_a, const Base &_b);

		double maxEl(void) const;
		double minEl(void) const;

		Base & operator =  (const Base &_a);
		Base & operator =  (Base &&_a);
		Base & operator += (const Base &_a);
		Base & operator -= (const Base &_a);
		Base & operator *= (const Base &_a);
		Base & operator *= (double _number);

		friend std::ostream & operator << (std::ostream &_out, const Base &_a);
		friend std::istream & operator >> (std::istream &_in, const Base &_a);

		friend Base operator + (const Base &_a, const Base &_b);
		friend Base operator - (const Base &_a, const Base &_b);
		friend Base operator * (const Base &_a, const Base &_b);
		friend Base operator * (const Base &_a, double _number);
		friend Base operator * (double _number, const Base &_b);
	};

	class Vector : public Base
	{
	private:

		int size;

	public:

		Vector();

		Vector(int _size, const double *_array = NULL);
		Vector(int _size, double _el, ...);

		Vector(const Vector &_a);
		Vector(const Base &_a);
		Vector(Vector &&_a);
		Vector(Base &&_a);

		~Vector();

		int getSize(void) const;

		Vector & transposition(void);

		double & operator[] (int _i);
		double operator[] (int _i) const;

		Vector & operator = (const Vector &_a);
		Vector & operator = (Vector &&_a);

		Vector & operator = (const Base &_a);
		Vector & operator = (Base &&_a);
		
		Vector & operator *= (const Vector &_a);
		Vector & operator *= (const Base &_a);
	};
	
	class Row
	{
	private:
		double *row;
		int cols;

	public:

		Row(int _col, double *_row);
		~Row();

		double & operator[] (int _j);
		double operator[] (int _j) const;
	};

	class Matrix : public Base
	{
	public:
		Matrix();

		explicit Matrix(int _rank, const double *_matrix = NULL);
		Matrix(int _rows, int _cols, const double *_matrix = NULL);

		Matrix(int _rows, int _cols, double _el, ...);

		Matrix(const Matrix &_a);
		Matrix(const Base &_a);
		Matrix(Matrix &&_a);
		Matrix(Base &&_a);

		~Matrix();

		int getRows(void) const;
		int getCols(void) const;

		Row operator[] (int _i);
		const Row operator[] (int _i) const;

		Matrix & operator = (const Matrix &_a);
		Matrix & operator = (Matrix &&_a);

		Matrix & operator = (const Base &_a);
		Matrix & operator = (Base &&_a);
	};

	//Matrix operator * (const Vector &_a, const Vector &_b);
	//Matrix operator * (const Vector &_a, const Matrix &_b);
	//Matrix operator * (const Matrix &_a, const Vector &_b);
	//Matrix operator * (const Matrix &_a, const Matrix &_b);
}