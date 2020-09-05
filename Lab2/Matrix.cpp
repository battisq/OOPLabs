#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

namespace Mathematics
{
	int Matrix::countId = 0;   

	Matrix::Matrix() : rows(0), cols(0), array(NULL)
	{
		id = ++countId;
		std::cout << "Конструктор матрицы " << id << std::endl;
	}

	Matrix::Matrix(int _rank, const double *_matrix) : Matrix(_rank, _rank, _matrix) {}

	Matrix::Matrix(int _rows, int _cols, const double *_matrix)
	{
		if (_rows < 0 || _cols < 0)
			throw std::length_error("Непреемлимый размер матрицы " + std::to_string(id) + "\n");

		rows = _rows;
		cols = _cols;
		array = rows * cols ? new double[rows * cols] : NULL;
		
		if (_matrix)
			for (int i = 0; i < rows * cols; i++)
				array[i] = _matrix[i];
		else
			for (int i = 0; i < rows * cols; i++)
				array[i] = 0;

		id = ++countId;
		std::cout << "Конструктор матрицы " << id << std::endl;
	}

	Matrix::Matrix(int _rows, int _cols, double _el, ...) : Matrix(_rows, _cols, &_el) {}

	Matrix::Matrix(int _rank, double(*_function)(int, int)) : Matrix(_rank, _rank, _function) {}

	Matrix::Matrix(int _rows, int _cols, double(*_function)(int, int)) : Matrix(_rows, _cols)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				array[i*cols + j] = _function(i, j);
	}

	Matrix::Matrix(const Matrix &_a) : Matrix(_a.rows, _a.cols, _a.array) {}

	Matrix::Matrix(Matrix &&_a) : Matrix()
	{
		std::swap(rows, _a.rows);
		std::swap(cols, _a.cols);
		std::swap(array, _a.array);
		//operator=(std::move(_a));
	}

	Matrix::~Matrix()
	{
		if (array != NULL)
			delete[] array;

		std::cout << "Деструктор матрицы " << id << std::endl;
	}

	bool Matrix::checkSum(const Matrix &_a) const
	{
		return rows == _a.rows && cols == _a.cols;
	}

	bool Matrix::checkSum(const Matrix &_a, const Matrix &_b)
	{
		return _a.rows == _b.rows && _a.cols == _b.cols;
	}

	bool Matrix::checkMul(const Matrix &_a) const
	{
		return cols == _a.rows;
	}

	bool Matrix::checkMul(const Matrix &_a, const Matrix &_b)
	{
		return _a.cols == _b.rows;
	}

	double Matrix::maxEl(void) const
	{
		if (!cols && !rows)
			throw std::logic_error("Max элемент матрицы " + std::to_string(id) + " не может быть определён. Матрица не инициализированна\n");

		double max = array[0];

		for (int i = 1; i < rows * cols; i++)
			if (array[i] > max)
				max = array[i];

		return max;
	}

	double Matrix::minEl(void) const
	{
		if (!cols && !rows)
			throw std::logic_error("Min элемент матрицы " + std::to_string(id) + " не может быть определён. Матрица не инициализированна\n");

		double min = array[0];

		for (int i = 1; i < rows * cols; i++)
			if (array[i] < min)
				min = array[i];

		return min;
	}

	Row Matrix::operator[](int _i)
	{
		if (_i < 0 || _i >= rows)
			throw std::out_of_range("Неверный индекс строки для матрицы " + std::to_string(id) + "\n");

		return Row(cols, array + _i * cols, id);
	}

	const Row Matrix::operator[](int _i) const
	{
		if (_i < 0 || _i >= rows)
			throw std::out_of_range("Неверный индекс строки для матрицы " + std::to_string(id) + "\n");

		return Row(cols, array + _i * cols, id);
	}

	Matrix & Matrix::operator = (const Matrix &_a)
	{
		if (rows*cols != _a.rows*_a.cols)
		{
			if (array)
				delete[] array;

			if (!_a.array)
				array = NULL;
			else
				array = new double[_a.rows * _a.cols];
		}

		rows = _a.rows;
		cols = _a.cols;

		for (int i = 0; i < rows*cols; i++)
			array[i] = _a.array[i];

		return *this;
	}

	Matrix & Matrix::operator = (Matrix && _a)
	{
		std::swap(cols, _a.cols);
		std::swap(rows, _a.rows);
		std::swap(array, _a.array);

		return *this;
	}

	Matrix & Matrix::operator = (double _number)
	{
		if (rows != 1 || cols != 1)
		{
			rows = cols = 1;

			if (array)
			{
				delete[] array;
				array = new double[1];
			}

			array[0] = _number;
		}

		return *this;
	}

	Matrix & Matrix::operator += (const Matrix &_a)
	{
		if (!checkSum(_a))
		{
			if (!_a.cols*_a.rows)
				throw std::logic_error("Сложение невозможно. Матрица " + std::to_string(_a.id) + " не инициализирована\n");
			else if (!cols*rows)
				throw std::logic_error("Сложение невозможно. Матрица " + std::to_string(id) + " не инициализирована\n");
			else
				throw std::logic_error("Сложение невозможно. Размер матриц " + std::to_string(id) + " & " + std::to_string(_a.id) + " не соответствует условию суммы\n");
		}

		for (int i = 0; i < rows*cols; i++)
			array[i] += _a.array[i];

		return *this;
	}

	Matrix & Matrix::operator -= (const Matrix &_a)
	{
		if (!checkSum(_a))
		{
			if (!_a.cols*_a.rows)
				throw std::logic_error("Разность невозможна. Матрица " + std::to_string(_a.id) + " не инициализирована\n");
			else if (!cols*rows)
				throw std::logic_error("Разность невозможна. Матрица " + std::to_string(id) + " не инициализирована\n");
			else
				throw std::logic_error("Разность невозможна. Размер матриц " + std::to_string(id) + " & " + std::to_string(_a.id) + " не соответствует условию разности\n");
		}

		for (int i = 0; i < rows*cols; i++)
			array[i] -= _a.array[i];

		return *this;
	}

	Matrix & Matrix::operator *= (const Matrix &_a)
	{
		if (!checkMul(_a))
		{
			if (!_a.cols*_a.rows)
				throw std::logic_error("Умножение невозможно. Матрица " + std::to_string(_a.id) + " не инициализирована\n");
			else if (!cols*rows || !array)
				throw std::logic_error("Умножение невозможно. Матрица " + std::to_string(id) + " не инициализирована\n");
			else
				throw std::logic_error("Умножение невозможно. Размер матриц " + std::to_string(id) + " & " + std::to_string(_a.id) + " не соответствует условию умножения\n");
		}

		Matrix newMatrix(rows, _a.cols);

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < _a.cols; j++)
				for (int k = 0; k < cols; k++)
					newMatrix.array[i * _a.cols + j] += this->array[i * cols + k] * _a.array[k * _a.cols + j];

		*this = std::move(newMatrix);

		return *this;
	}

	Matrix & Matrix::operator *= (double _number)
	{
		for (int i = 0; i < rows*cols; i++)
			array[i] *= _number;

		return *this;
	}

	int Matrix::getRows(void) const
	{
		return rows;
	}

	int Matrix::getCols(void) const
	{
		return cols;
	}

	int Matrix::getId(void) const
	{
		return id;
	}

	int Matrix::getCountId(void)
	{
		return countId;
	}

	bool operator > (const Matrix & _a, const Matrix & _b)
	{
		return _a.rows * _a.cols > _b.rows * _b.cols;
	}

	bool operator < (const Matrix & _a, const Matrix & _b)
	{
		return _a.rows * _a.cols > _b.rows * _b.cols;
	}

	std::ostream & operator << (std::ostream &_out, const Matrix &_a)
	{
		std::streamsize width = _out.width();

		for (int i = 0; i < _a.rows; i++)
		{
			for (int j = 0; j < _a.cols; j++)
			{
				_out.width(width);
				_out << _a.array[i * _a.cols + j];

				if (!width)
					std::cout << " ";
			}
			_out << "\n";
		}

		return _out;
	}

	Matrix operator + (const Matrix &_a, const Matrix &_b)
	{
		Matrix c(_a);
		
		return c += _b;
	}

	Matrix operator - (const Matrix &_a, const Matrix &_b)
	{
		Matrix c(_a);

		return c -= _b;
	}

	Matrix operator * (const Matrix &_a, const Matrix &_b)
	{
		Matrix c(_a);

		return c *= _b;
	}

	Matrix operator * (const Matrix &_a, double _number)
	{
		Matrix c(_a);

		return c *= _number;
	}

	Matrix operator * (double _number, const Matrix &_a)
	{
		Matrix c(_a);
		
		return c *= _number;
	}

	Row::Row(int _cols, double * _row, int _id) : cols(_cols), row(_row), id(_id) {}

	Row::~Row()
	{
		row = NULL;
	}

	double & Row::operator[](int _j)
	{
		if (_j < 0 || _j >= cols)
			throw std::out_of_range("Неверный индекс столбца для матрицы " + std::to_string(id) + "\n");

		return row[_j];
	}

	const double & Row::operator[](int _j) const 
	{
		if (_j < 0 || _j >= cols)
			throw std::out_of_range("Неверный индекс столбца для матрицы " + std::to_string(id) + "\n");

		return row[_j];
	}
}