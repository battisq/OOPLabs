#include "Hierarchy.h"
#include <string>
#include <stdexcept>

using namespace std;

namespace Mathematics
{
#pragma region Base

	Base::Base() : rows(0), cols(0), array(NULL) {}

	Base::Base(int _rows, int _cols, const double *_array)
	{
		if (_rows < 0 || _cols < 0)
			throw length_error("Неприемлемый размер объекта\n");

		rows = _rows;
		cols = _cols;
		array = rows * cols ? new double[rows * cols] : NULL;

		if (_array)
			for (int i = 0; i < rows * cols; i++)
				array[i] = _array[i];
		else
			for (int i = 0; i < rows * cols; i++)
				array[i] = 0;
	}

	Base::Base(const Base &_a) : Base(_a.rows, _a.cols, _a.array) {}

	Base::Base(Base &&_a) : Base()
	{
		operator = (move(_a));
	}

	Base::~Base()
	{
		if (array != NULL)
			delete[] array;
	}

	bool Base::checkSum(const Base &_a) const
	{
		return rows == _a.rows && cols == _a.cols;
	}

	bool Base::checkMul(const Base &_a) const
	{
		return cols == _a.rows;
	}

	bool Base::checkSum(const Base & _a, const Base & _b)
	{
		return _a.rows == _b.rows && _a.cols == _b.cols;;
	}

	bool Base::checkMul(const Base & _a, const Base & _b)
	{
		return _a.cols == _b.rows;
	}

	double Base::maxEl(void) const
	{
		if (!cols && !rows)
			throw logic_error("Max элемент объекта не может быть определён. Объект не инициализирован\n");

		double max = array[0];

		for (int i = 1; i < rows * cols; i++)
			if (array[i] > max)
				max = array[i];

		return max;
	}

	double Base::minEl(void) const
	{
		if (!cols && !rows)
			throw logic_error("Min элемент объекта не может быть определён. Объект не инициализирован\n");

		double min = array[0];

		for (int i = 1; i < rows * cols; i++)
			if (array[i] < min)
				min = array[i];

		return min;
	}

	Base & Base::operator = (const Base &_a)
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

	Base & Base::operator = (Base && _a)
	{
		swap(cols, _a.cols);
		swap(rows, _a.rows);
		swap(array, _a.array);

		return *this;
	}

	Base & Base::operator += (const Base &_a)
	{
		if (!checkSum(_a))
		{
			if (!_a.cols*_a.rows)
				throw logic_error("Сложение невозможно. Объект не инициализирован\n");
			else if (!cols*rows)
				throw logic_error("Сложение невозможно. Объект не инициализирован\n");
			else
				throw logic_error("Сложение невозможно. Размер объектов не соответствует условию суммы\n");
		}

		for (int i = 0; i < rows*cols; i++)
			array[i] += _a.array[i];

		return *this;
	}

	Base & Base::operator -= (const Base &_a)
	{
		if (!checkSum(_a))
		{
			if (!_a.cols*_a.rows)
				throw logic_error("Разность невозможна. Объект не инициализирован\n");
			else if (!cols*rows)
				throw logic_error("Разность невозможна. Объект не инициализирован\n");
			else
				throw logic_error("Разность невозможна. Размер объектов не соответствует условию разности\n");
		}

		for (int i = 0; i < rows*cols; i++)
			array[i] -= _a.array[i];

		return *this;
	}

	Base & Base::operator *= (const Base &_a)
	{
		if (!checkMul(_a))
		{
			if (!_a.cols*_a.rows)
				throw logic_error("Умножение невозможно. Объект не инициализирован\n");
			else if (!cols*rows || !array)
				throw logic_error("Умножение невозможно. Объект не инициализирован\n");
			else
				throw logic_error("Умножение невозможно. Размер объектов не соответствует условию умножения\n");
		}

		Base newArray(rows, _a.cols);

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < _a.cols; j++)
				for (int k = 0; k < cols; k++)
					newArray.array[i * _a.cols + j] += this->array[i * cols + k] * _a.array[k * _a.cols + j];

		*this = move(newArray);

		return *this;
	}

	Base & Base::operator *= (double _number)
	{
		for (int i = 0; i < rows*cols; i++)
			array[i] *= _number;

		return *this;
	}

	bool Base::getRank(const Base &_a) const
	{
		return _a.cols > 1 && _a.rows > 1;
	}

#pragma endregion

#pragma region Vector

	Vector::Vector() : Base(), size(0) {}

	Vector::Vector(int _size, const double * _array) : Base(_size, 1, _array), size(_size) {}

	Vector::Vector(int _size, double _el, ...) : Vector(_size, &_el) {}

	Vector::Vector(const Vector & _a)
	{
		Vector::operator = (_a);
	}

	Vector::Vector(const Base & _a)
	{
		Vector::operator = (_a);
	}

	Vector::Vector(Vector && _a)
	{
		Vector::operator = (move(_a));
	}

	Vector::Vector(Base && _a)
	{
		Vector::operator = (move(_a));
	}

	Vector::~Vector() {}

	int Vector::getSize(void) const
	{
		return size;
	}

	Vector & Vector::transposition(void)
	{
		swap(rows, cols);

		return *this;
	}

	double & Vector::operator[](int _i)
	{
		if (_i < 0 || _i >= size)
			throw out_of_range("Неверный индекс для вектора\n");

		return array[_i];
	}

	double Vector::operator[](int _i) const
	{
		if (_i < 0 || _i >= size)
			throw out_of_range("Неверный индекс для вектора\n");

		return array[_i];
	}

	Vector & Vector::operator = (const Vector & _a)
	{
		Base::operator = (_a);
		size = _a.size;

		return *this;
	}

	Vector & Vector::operator = (Vector && _a)
	{
		Base::operator = (_a);
		swap(size, _a.size);

		return *this;
	}

	Vector & Vector::operator = (const Base & _a)
	{
		if (getRank(_a))
			throw invalid_argument("Вектор не может перенять данные матрицы\n");

		Base::operator = (_a);
		size = rows > 1 ? rows : cols;

		return *this;
	}

	Vector & Vector::operator = (Base && _a)
	{
		if (getRank(_a))
			throw invalid_argument("Обмен данными невозможен! Вектор не может обменяться данными с матрицей\n");

		Base::operator = (move(_a));
		size = rows > 1 ? rows : cols;

		return *this;
	}

	Vector & Vector::operator *= (const Vector & _a)
	{
		if (cols == 1 && _a.rows == 1)//
			throw logic_error("При умножении вектора-столбца на вектор-строку произойдёт преобразования вектора в матрицу\n");
		else
			Base::operator *= (_a);

		return *this;
	}

	Vector & Vector::operator *= (const Base & _a)
	{
		if (getRank(_a))
			throw logic_error("Умножение вектора на матрицу недопустимо. Произойдёт преобразования вектора в матрицу\n");
		//Base x = ((Base &)*this) * _a;
		//*this = move(x);

		Vector::operator *= (Vector(_a));

		return *this;
	}

#pragma endregion

#pragma region Matrix

	Row::Row(int _cols, double * _row) : cols(_cols), row(_row){}

	Row::~Row()
	{
		row = NULL;
	}

	double & Row::operator[](int _j)
	{
		if (_j < 0 || _j >= cols)
			throw out_of_range("Неверный индекс столбца для матрицы\n");

		return row[_j];
	}

	double Row::operator[](int _j) const
	{
		if (_j < 0 || _j >= cols)
			throw out_of_range("Неверный индекс столбца для матрицы\n");

		return row[_j];
	}

	Matrix::Matrix() : Base() {}

	Matrix::Matrix(int _rank, const double * _matrix) : Matrix(_rank, _rank, _matrix) {}

	Matrix::Matrix(int _rows, int _cols, const double * _matrix) : Base(_rows, _cols, _matrix) {}

	Matrix::Matrix(int _rows, int _cols, double _el, ...) : Matrix(_rows, _cols, &_el) {}

	Matrix::Matrix(const Matrix & _a) : Base(_a) {}

	Matrix::Matrix(const Base & _a) : Base(_a) {}

	Matrix::Matrix(Matrix && _a) : Base(move(_a)) {}

	Matrix::Matrix(Base && _a) : Base(move(_a)) {}

	Matrix::~Matrix() {}

	int Matrix::getRows(void) const
	{
		return rows;
	}

	int Matrix::getCols(void) const
	{
		return cols;
	}

	Row Matrix::operator[](int _i)
	{
		if (_i < 0 || _i >= rows)
			throw out_of_range("Неверный индекс строки для матрицы\n");

		return Row(cols, array + _i * cols);
	}

	const Row Matrix::operator[](int _i) const
	{
		if (_i < 0 || _i >= rows)
			throw out_of_range("Неверный индекс строки для матрицы\n");

		return Row(cols, array + _i * cols);
	}

	Matrix & Matrix::operator = (const Matrix & _a)
	{
		Base::operator = (_a);

		return *this;
	}

	Matrix & Matrix::operator = (Matrix && _a)
	{
		Base::operator = (move(_a));

		return *this;
	}

	Matrix & Matrix::operator = (const Base & _a)
	{
		Base::operator = (_a);

		return *this;
	}

	Matrix & Matrix::operator = (Base && _a)
	{
		if (!getRank(_a))
			throw invalid_argument("Обмен данными невозможен! Матрица не может обменяться данными с вектором\n");

		Base::operator = (move(_a));

		return *this;
	}

#pragma endregion

#pragma region Functions

	ostream & operator << (ostream &_out, const Base &_a)
	{
		streamsize width = _out.width();

		for (int i = 0; i < _a.rows; i++)
		{
			for (int j = 0; j < _a.cols; j++)
			{
				_out.width(width);
				_out << _a.array[i * _a.cols + j];

				if (!width)
					cout << " ";
			}
			_out << "\n";
		}

		return _out;
	}

	istream & operator >> (istream & _in, const Base & _a)
	{
		for (int i = 0; i < _a.cols*_a.rows; i++)
		{
			_in >> _a.array[i];
		}

		return _in;
	}

	Base operator + (const Base &_a, const Base &_b)
	{
		Base c(_a);

		return c += _b;
	}

	Base operator - (const Base &_a, const Base &_b)
	{
		Base c(_a);

		return c -= _b;
	}

	Base operator * (const Base &_a, const Base &_b)
	{
		Base c(_a);

		return c *= _b;
	}

	Base operator * (const Base &_a, double _number)
	{
		Base c(_a);

		return c *= _number;
	}

	Base operator * (double _number, const Base &_a)
	{
		Base c(_a);

		return c *= _number;
	}

	/*Matrix operator * (const Vector & _a, const Vector & _b)
	{
		Matrix c(_a);

		return c *= _b;
	}

	Matrix operator * (const Vector & _a, const Matrix & _b)
	{
		Matrix c(_a);

		return c *= _b;
	}

	Matrix operator * (const Matrix & _a, const Vector & _b)
	{
		Matrix c(_a);

		return c *= _b;
	}

	Matrix operator * (const Matrix & _a, const Matrix & _b)
	{
		Matrix c(_a);

		return c *= _b;
	}*/

#pragma endregion
}