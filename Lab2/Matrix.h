#pragma once

#include <ostream>

namespace Mathematics
{
	class Row
	{
	public:

		Row(int _col, double *_row, int _id);
		~Row();

		double & operator[] (int _j);
		const double & operator[] (int _j) const;

	private:
		double *row;
		int cols;
		int id;
	};

	class Matrix
	{
	private:
		int rows;
		int cols;
		double *array;

		int id;
		static int countId;

	public:

		Matrix();

		explicit Matrix(int _rank, const double *_matrix = NULL);
		Matrix(int _rows, int _cols,const double *_matrix = NULL);

		Matrix(int _rows, int _cols, double _el, ...);

		Matrix(int _rank, double(*_function)(int, int));
		Matrix(int _rows, int _cols, double(*_function)(int, int));

		Matrix(const Matrix &_a);
		Matrix(Matrix &&_a);

		~Matrix();

		bool checkSum(const Matrix &_a) const;
		bool checkMul(const Matrix &_a) const;
		static bool checkSum(const Matrix &_a, const Matrix &_b);
		static bool checkMul(const Matrix &_a, const Matrix &_b);

		double maxEl(void) const;
		double minEl(void) const;

		Row operator[] (int _i);
		const Row operator[] (int _i) const;
				
		Matrix & operator =  (const Matrix &_a);
		Matrix & operator =  (Matrix &&_a);
		Matrix & operator =  (double _number);
		Matrix & operator += (const Matrix &_a);
		Matrix & operator -= (const Matrix &_a);
		Matrix & operator *= (const Matrix &_a);
		Matrix & operator *= (double _number);

		friend bool operator > (const Matrix &_a, const Matrix &_b);
		friend bool operator < (const Matrix &_a, const Matrix &_b);

		int getRows(void) const;
		int getCols(void) const;
		int getId(void) const;
		static int getCountId(void);

		friend std::ostream & operator << (std::ostream &_out, const Matrix &_a);
	};

	Matrix operator + (const Matrix &_a, const Matrix &_b);
	Matrix operator - (const Matrix &_a, const Matrix &_b);
	Matrix operator * (const Matrix &_a, const Matrix &_b);
	Matrix operator * (const Matrix &_a, double _number);
	Matrix operator * (double _number, const Matrix &_b);
}