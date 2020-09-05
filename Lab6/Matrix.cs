using System;
using System.Text;
using System.Globalization;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace Mathematics
{
	class Matrix : IFormattable, ICloneable, IEnumerable, IEnumerable<double>
	{
		private double[,] _matrix;

		private static int _countId = 0;
		private int _id;

		public Matrix() : this(0, 0) { }

		public Matrix(int dimension, double[][] matrix = null) : this(dimension, dimension, matrix) { }

		public Matrix(int rows, int cols, double[][] matrix = null)
		{
			_id = ++_countId;
			Console.WriteLine($"Конструктор матрицы {_id}");

			if (rows < 0 || cols < 0)
				throw new ArgumentOutOfRangeException(string.Format($"Неприемлемый размер для создания матрицы {_id}\n"));

			_matrix = (rows * cols != 0) ? new double[rows, cols] : null;

			if (matrix != null)
				for (int i = 0; i < rows && i < matrix.Length; i++)
					for (int j = 0; j < cols && j < matrix[i].Length; j++)
						_matrix[i, j] = matrix[i][j];
		}

		public Matrix(double[,] matrix)
		{
			_id = ++_countId;
			Console.WriteLine($"Конструктор матрицы {_id}");

			if (matrix == null)
				return;

			_matrix = matrix.GetLength(0) * matrix.GetLength(1) !=0 ? new double[matrix.GetLength(0), matrix.GetLength(1)] : null;

			_matrix = (double[,])matrix.Clone();
			//for (int i = 0; i < matrix.GetLength(0); i++)
			//	for (int j = 0; j < matrix.GetLength(1); j++)
			//		_matrix[i, j] = matrix[i, j];
		}

		public Matrix(Matrix a) : this(a?._matrix)
		{
			if (a == null)
				throw new ArgumentNullException(string.Format($"Некорректная матрица {_id}\n"));
		}

        public Matrix(int dimension, Func<int, int, double> func) : this(dimension, dimension, func) { }

        public Matrix(int rows, int cols, Func<int, int, double> func) : this(rows, cols)
        {
			if (func == null)
				throw new ArgumentNullException(string.Format($"Вместо делегата получен null {_id}\n"));

			for (int i = 0; i < _matrix.GetLength(0); i++)
                for (int j = 0; j < _matrix.GetLength(1); j++)
                    _matrix[i, j] = func(i, j);
        }
        
        public Matrix(int rows, int cols, params double[] list) : this(rows, cols)
        {
			if(list == null)
				throw new ArgumentNullException(string.Format($"Вместо переменных параметров получено null {_id}\n"));

			for (int i = 0, k = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    if (k == list.Length)
                        break;

                    _matrix[i, j] = list[k++];
                }
            }
        }

        ~Matrix()
        {
            Console.WriteLine($"Деструктор матрицы {_id}");
        }

        public static bool CheckSum(Matrix a, Matrix b)
        {
            return a?.Rows == b?.Rows && a?.Cols == b?.Cols;
        }

        public static bool CheckMul(Matrix a, Matrix b)
        {
            return a?.Cols == b?.Rows;
        }	

        public static Matrix operator + (Matrix a, Matrix b)
        {
            if (!CheckSum(a, b))
            {
                if (a._matrix == null)
                    throw new NullReferenceException(string.Format($"Сложение невозможно. Матрица {a._id} не инициализирована\n"));
                else if (b._matrix == null)
                    throw new NullReferenceException(string.Format($"Сложение невозможно. Матрица {b._id} не инициализирована\n"));
                else
                    throw new InvalidOperationException(string.Format($"Сложение невозможно. Размер матриц {a._id} & {b._id} не соответствует условию суммы\n"));
            }

            Matrix result = new Matrix(a);

            for (int i = 0; i < result._matrix.GetLength(0); i++)
                for (int j = 0; j < result._matrix.GetLength(1); j++)
                    result._matrix[i, j] += b._matrix[i, j];

            return result;
        }

        public static Matrix operator - (Matrix a, Matrix b)
        {
            if (!CheckSum(a, b))
            {
                if (a._matrix == null)
                    throw new NullReferenceException(string.Format($"Вычитание невозможно. Матрица {a._id} не инициализирована\n"));
                else if (b._matrix == null)
                    throw new NullReferenceException(string.Format($"Вычитание невозможно. Матрица {b._id} не инициализирована\n"));
                else
                    throw new InvalidOperationException(string.Format($"Вычитание невозможно. Размер матриц {a._id} & {b._id} не соответствует условию разности\n"));
            }

            Matrix result = new Matrix(a);

            for (int i = 0; i < result._matrix.GetLength(0); i++)
                for (int j = 0; j < result._matrix.GetLength(1); j++)
                    result._matrix[i, j] -= b._matrix[i, j];

            return result;
        }

        public static Matrix operator * (Matrix a, Matrix b)
        {
            if (!CheckMul(a, b))
            {
                if (a._matrix == null)
                    throw new NullReferenceException(string.Format($"Умножение невозможно. Матрица {a._id} не инициализирована\n"));
                else if (b._matrix == null)
                    throw new NullReferenceException(string.Format($"Умножение невозможно. Матрица {b._id} не инициализирована\n"));
                else
                    throw new InvalidOperationException(string.Format($"Умножение невозможно. Размер матриц {a._id} & {b._id} не соответствует условию произведения\n"));
            }

            Matrix newMatrix = new Matrix(a._matrix.GetLength(0), b._matrix.GetLength(1));

            for (int i = 0; i < a._matrix.GetLength(0); i++)
                for (int j = 0; j < b._matrix.GetLength(1); j++)
                    for (int k = 0; k < a._matrix.GetLength(1); k++)
                        newMatrix._matrix[i, j] += a._matrix[i, k] * b._matrix[k, j];

            return newMatrix;
        }

        public static Matrix operator * (Matrix a, double number)
        {
            if (a._matrix == null)
                throw new NullReferenceException(string.Format($"Умножение невозможно. Матрица {a._id} не инициализирована\n"));

            Matrix newMatrix = new Matrix(a);

            for (int i = 0; i < a._matrix.GetLength(0); i++)
                for (int j = 0; j < a._matrix.GetLength(1); j++)
                    newMatrix._matrix[i, j] *= number;

            return newMatrix;
        }

		public static Matrix operator * (double number, Matrix a)
		{
			if (a._matrix == null)
				throw new NullReferenceException(string.Format($"Умножение невозможно. Матрица {a._id} не инициализирована\n"));

			Matrix newMatrix = new Matrix(a);

			for (int i = 0; i < a._matrix.GetLength(0); i++)
				for (int j = 0; j < a._matrix.GetLength(1); j++)
					newMatrix._matrix[i, j] *= number;

			return newMatrix;
		}

		public double this[int i, int j]
        {
            get
            {
                if (i < 0 || i >= _matrix.GetLength(0))
                    throw new IndexOutOfRangeException(string.Format($"Неверный индекс строки для матрицы {_id}\n"));

                if (j < 0 || j >= _matrix.GetLength(1))
                    throw new IndexOutOfRangeException(string.Format($"Неверный индекс столбца для матрицы {_id}\n"));

                return _matrix[i, j];
            }

            set
            {
                if (_matrix[i, j] != value)
                    _matrix[i, j] = value;
            }
        }

        public int Rows 
        {
            get
            {
				if (_matrix == null)
					return 0;

				return _matrix.GetLength(0);
            }
        } 

        public int Cols
        {
            get
            {
				if (_matrix == null)
					return 0;

                return _matrix.GetLength(1);
            }
        }

        public override string ToString()
        {
            return ToString("G", CultureInfo.CurrentCulture);
		}

		/// <summary>
		/// Вид форматной строки: {index[:formatString][,alignment]}
		/// </summary>
		public string ToString(string _format)
        {
            return ToString(_format, CultureInfo.CurrentCulture);
        }

		/// <summary>
		/// Вид форматной строки: {index[:formatString][,alignment]}
		/// </summary>
		public string ToString(string _format, IFormatProvider _provider)
        {
			if (_matrix == null)
				return "null";

			_provider = _provider ?? CultureInfo.CurrentCulture;

			string width = "0";

			if (string.IsNullOrEmpty(_format))
				_format = "{0:G} ";
			else if (_format.IndexOf(',') != -1)
			{
				int index = _format.IndexOf(',');

				width = _format.Substring(index + 1);
				_format = string.Format("{{0,{0}:{1}}}", width, _format.Substring(0, index));

				if (width == "" || _format == "")
					throw new FormatException(string.Format("Неверный формат для печати матрицы {0}", _id));
			}
			else
			{
				width = char.IsLetter(_format[0]) || _format[0] == '0' ? "12" : _format;
				_format = string.Format(char.IsLetter(_format[0]) || _format[0] == '0' ? "{{0:{0}}} " : "{{0,{0}}}", _format);
			}

			StringBuilder str = new StringBuilder(Convert.ToInt32(width) * _matrix.Length + 2 * _matrix.GetLength(0));

			for (int i = 0; i < _matrix.GetLength(0); i++)
			{
				for (int j = 0; j < _matrix.GetLength(1); j++)
					str.AppendFormat(_format, _matrix[i, j]);

				str.AppendFormat("\n");
			}

			return str.ToString();
		}

		object ICloneable.Clone()
        {
            return Clone();
        }

        public Matrix Clone()
        {
            Matrix clone = new Matrix(this);

            return clone;
        }

        public IEnumerator GetEnumerator()
        {
            return _matrix.GetEnumerator();
        }

        IEnumerator<double> IEnumerable<double>.GetEnumerator()
        {
           return _matrix.Cast<double>().GetEnumerator();
        }
    }
}
