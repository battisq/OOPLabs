using System;
using System.Text;
using System.Globalization;
using System.Collections;
using System.Collections.Generic;

namespace Mathematics
{
	class Matrix : IFormattable, ICloneable, IEnumerable, IEnumerable<double>
	{
		protected double[,] data;

		public Matrix() : this(0, 0) { }

		public Matrix(int dimension) : this(dimension, dimension) { }

		public Matrix(int rows, int cols)
		{
			if (rows < 0 || cols < 0)
				throw new ArgumentOutOfRangeException("Неприемлемый размер для создания объекта\n");

			data = (rows * cols != 0) ? new double[rows, cols] : null;
		}

		public Matrix(double[,] data)
		{
			if (data == null)
				return;

			this.data = data.GetLength(0) * data.GetLength(1) != 0 ? new double[data.GetLength(0), data.GetLength(1)] : null;
			this.data = (double[,])data.Clone();
		}

		public Matrix(Matrix source) : this(source?.data)
		{
			if (source == null)
				throw new ArgumentNullException("Некорректная матрица\n");
		}

		public Matrix(int rows, int cols, params double[] list) : this(rows, cols)
		{
			if (list == null)
				throw new ArgumentNullException("Вместо переменных параметров получено null\n");

			for (int i = 0, k = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					if (k == list.Length)
						break;

					data[i, j] = list[k++];
				}
			}
		}

		public static bool CheckSum(Matrix a, Matrix b)
			=> a?.data?.GetLength(0) == b?.data?.GetLength(0) && a?.data?.GetLength(1) == b?.data?.GetLength(1);

		public static bool CheckMul(Matrix a, Matrix b)
			=> a?.data?.GetLength(1) == b?.data?.GetLength(0);

		public virtual double this[int i, int j]
		{
			get
			{
				if (i < 0 || i >= data.GetLength(0))
					throw new IndexOutOfRangeException("Неверный индекс строки для матрицы\n");

				if (j < 0 || j >= data.GetLength(1))
					throw new IndexOutOfRangeException("Неверный индекс столбца для матрицы\n");

				return data[i, j];
			}

			set
			{
				if (data[i, j] != value)
					data[i, j] = value;
			}
		}

		public virtual int Rows
			=> data == null ? 0 : data.GetLength(0);

		public virtual int Cols
			=> data == null ? 0 : data.GetLength(1);

		public virtual int Rank
			=> data?.GetLength(0) > 1 && data?.GetLength(0) > 1 ? 2 : 1;

		protected static void Add(Matrix a, Matrix b, Matrix receiver)
		{
			if (!CheckSum(a, b))
			{
				if (a?.data == null)
					throw new NullReferenceException("Сложение невозможно. Объект не инициализирован\n");
				else if (b?.data == null)
					throw new NullReferenceException("Сложение невозможно. Объект не инициализирован\n");
				else
					throw new InvalidOperationException("Сложение невозможно. Размер объекта не соответствует условию суммы\n");
			}

			for (int i = 0; i < receiver.data.GetLength(0); i++)
				for (int j = 0; j < receiver.data.GetLength(1); j++)
					receiver.data[i, j] += b.data[i, j];
		}

		protected static void Sub(Matrix a, Matrix b, Matrix receiver)
		{
			if (!CheckSum(a, b))
			{
				if (a?.data == null)
					throw new NullReferenceException("Сложение невозможно. Объект не инициализирован\n");
				else if (b?.data == null)
					throw new NullReferenceException("Сложение невозможно. Объект не инициализирован\n");
				else
					throw new InvalidOperationException("Сложение невозможно. Размер объекта не соответствует условию суммы\n");
			}

			for (int i = 0; i < receiver.data.GetLength(0); i++)
				for (int j = 0; j < receiver.data.GetLength(1); j++)
					receiver.data[i, j] -= b.data[i, j];
		}

		protected static void Mul(Matrix a, Matrix b, Matrix receiver)
		{
			if (!CheckMul(a, b))
			{
				if (a?.data == null)
					throw new NullReferenceException("Сложение невозможно. Объект не инициализирован\n");
				else if (b?.data == null)
					throw new NullReferenceException("Сложение невозможно. Объект не инициализирован\n");
				else
					throw new InvalidOperationException("Сложение невозможно. Размер объекта не соответствует условию суммы\n");
			}

			for (int i = 0; i < a.data.GetLength(0); i++)
				for (int j = 0; j < b.data.GetLength(1); j++)
					for (int k = 0; k < a.data.GetLength(1); k++)
						receiver.data[i, j] += a.data[i, k] * b.data[k, j];
		}

		protected static void Mul(Matrix a, double number, Matrix receiver)
		{
			if (a?.data == null)
				throw new NullReferenceException("Умножение невозможно. Объект не инициализирован\n");

			for (int i = 0; i < receiver.data.GetLength(0); i++)
				for (int j = 0; j < receiver.data.GetLength(1); j++)
					receiver.data[i, j] *= number;
		}

		public static Matrix operator + (Matrix a, Matrix b)
		{
			Matrix result = CheckSum(a, b) ? new Matrix(a) : null;

			Add(a, b, result);

			return result;
		}

		public static Matrix operator - (Matrix a, Matrix b)
		{
			Matrix result = CheckSum(a, b) ? new Matrix(a) : null;

			Sub(a, b, result);

			return result;
		}

		public static Matrix operator * (Matrix a, Matrix b)
		{
			Matrix result = CheckMul(a, b) ? new Matrix(a.data.GetLength(0), b.data.GetLength(1)) : null;

			Mul(a, b, result);

			return result;
		}

		public static Matrix operator * (Matrix a, double number)
		{
			Matrix result = new Matrix(a);

			Mul(a, number, result);

			return result;
		}

		public static Matrix operator * (double number, Matrix b)
			=> b * number;

		public override string ToString()
			=> ToString("G", CultureInfo.CurrentCulture);

		/// <summary>
		/// Вид форматной строки: {index[:formatString][,alignment]}
		/// </summary>
		public string ToString(string format)
			=> ToString(format, CultureInfo.CurrentCulture);

		/// <summary>
		/// Вид форматной строки: {index[:formatString][,alignment]}
		/// </summary>
		public string ToString(string format, IFormatProvider provider)
		{
			if (data == null)
				return "null";

			provider = provider ?? CultureInfo.CurrentCulture;

			string width = "0";

			if (string.IsNullOrEmpty(format))
				format = "{0:G} ";
			else if (format.IndexOf(',') != -1)
			{
				int index = format.IndexOf(',');

				width = format.Substring(index + 1);
				format = string.Format("{{0,{0}:{1}}}", width, format.Substring(0, index));

				if (width == "" || format == "")
					throw new FormatException("Неверный формат для печати объекта");
			}
			else
			{
				width = char.IsLetter(format[0]) || format[0] == '0' ? "12" : format;
				format = string.Format(char.IsLetter(format[0]) || format[0] == '0' ? "{{0,{1}:{0}}} " : "{{0,{0}}}", format, width);
			}

			StringBuilder str = new StringBuilder(Convert.ToInt32(width) * data.Length + 2 * data.GetLength(0));

			for (int i = 0; i < data.GetLength(0); i++)
			{
				for (int j = 0; j < data.GetLength(1); j++)
					str.AppendFormat(format, data[i, j].ToString(provider));

				str.AppendFormat("\n");
			}

			return str.ToString();
		}

		object ICloneable.Clone()
			=> Clone();

		public Matrix Clone()
			=> new Matrix(this);

		public IEnumerator GetEnumerator()
			=> data.GetEnumerator();

		IEnumerator<double> IEnumerable<double>.GetEnumerator()
		{
			for (int i = 0; i < data.GetLength(0); i++)
				for (int j = 0; j < data.GetLength(1); j++)
					yield return data[i, j];
		}
	}
}