using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mathematics
{
	class TMatrix<Type> : IFormattable, ICloneable, IEnumerable, IEnumerable<Type>, IComparable, IComparable<TMatrix<Type>>
		where Type : new()
	{
		private Type[,] data;

		public TMatrix() : this(0, 0) { }

		public TMatrix(int dimension) : this(dimension, dimension) { }

		public TMatrix(int rows, int cols)
		{
			if (rows < 0 || cols < 0)
				throw new ArgumentOutOfRangeException("Неприемлемый размер для создания объекта\n");

			data = (rows * cols != 0) ? new Type[rows, cols] : null;

			for (int i = 0; i < Rows; i++)
				for (int j = 0; j < Cols; j++)
					data[i, j] = new Type();
		}

		public TMatrix(Type[,] data)
		{
			if (data == null)
				return;

			this.data = data.GetLength(0) * data.GetLength(1) != 0 ? new Type[data.GetLength(0), data.GetLength(1)] : null;

			for (int i = 0; i < Rows; i++)
			{
				for (int j = 0; j < Cols; j++)
				{
					if (data[i, j] is ICloneable) 
						this.data[i, j] = (Type)((ICloneable)data[i, j]).Clone();
					else
						this.data[i, j] = data[i, j];
				}
			}
		}

		public TMatrix(TMatrix<Type> source) : this(source?.data)
		{
			if (source == null)
				throw new ArgumentNullException("Некорректная матрица\n");
		}

		public TMatrix(int rows, int cols, params Type[] list) : this(rows, cols)
		{
			if (list == null)
				throw new ArgumentNullException("Вместо переменных параметров получено null\n");

			for (int i = 0, k = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					if (k == list.Length)
						break;

					if (list[k] is ICloneable) 
						data[i, j] = (Type)((ICloneable)list[k++]).Clone();
					else
						data[i, j] = list[k++];
				}
			}
		}

		public static bool CheckSum(TMatrix<Type> a, TMatrix<Type> b)
			=> a == null || b == null ? false : a == b;

		public static bool CheckMul(TMatrix<Type> a, TMatrix<Type> b)
			=> a == null || b == null ? false : a.Cols == b.Rows;

		public int Rows
			=> data == null ? 0 : data.GetLength(0);

		public int Cols
			=> data == null ? 0 : data.GetLength(1);

		public Type this[int i, int j]
		{
			get
			{
				if (i < 0 || i >= Rows)
					throw new IndexOutOfRangeException("Неверный индекс строки для матрицы\n");

				if (j < 0 || j >= Cols)
					throw new IndexOutOfRangeException("Неверный индекс столбца для матрицы\n");

				return data[i, j];
			}

			set
			{
				if (((dynamic)data[i, j]).CompareTo(value))
					data[i, j] = value;
			}
		}

		public static TMatrix<Type> operator + (TMatrix<Type> a, TMatrix<Type> b)
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

			TMatrix<Type> result = new TMatrix<Type>(a);

			for (int i = 0; i < result.Rows; i++)
				for (int j = 0; j < result.Cols; j++)
					result.data[i, j] = (dynamic)result.data[i, j] + b.data[i, j];

			return result;
		}

		public static TMatrix<Type> operator - (TMatrix<Type> a, TMatrix<Type> b)
		{
			if (!CheckSum(a, b))
			{
				if (a?.data == null)
					throw new NullReferenceException("Вычитание невозможно. Объект не инициализирован\n");
				else if (b?.data == null)
					throw new NullReferenceException("Вычитание невозможно. Объект не инициализирован\n");
				else
					throw new InvalidOperationException("Вычитание невозможно. Размер объектов не соответствует условию разности\n");
			}

			TMatrix<Type> result = new TMatrix<Type>(a);

			for (int i = 0; i < result.Rows; i++)
				for (int j = 0; j < result.Cols; j++)
					result.data[i, j] = (dynamic)result.data[i, j] - b.data[i, j];

			return result;
		}

		public static TMatrix<Type> operator * (TMatrix<Type> a, TMatrix<Type> b)
		{
			if (!CheckMul(a, b))
			{
				if (a?.data == null)
					throw new NullReferenceException("Умножение невозможно. Объект не инициализирован\n");
				else if (b?.data == null)
					throw new NullReferenceException("Умножение невозможно. Объект не инициализирован\n");
				else
					throw new InvalidOperationException("Умножение невозможно. Размер объектов не соответствует условию произведения\n");
			}

			TMatrix<Type> result = new TMatrix<Type>(a.Rows, b.Cols);

			for (int i = 0; i < a.Rows; i++)
			{
				for (int j = 0; j < b.Cols; j++)
				{
					result.data[i, j] = (dynamic)a.data[i, 0] * b.data[0, j];

					for (int k = 1; k < a.Cols; k++)
						result.data[i, j] += (dynamic)a.data[i, k] * b.data[k, j];
				}
			}

			return result;
		}

		public static TMatrix<Type> operator * (TMatrix<Type> a, Type b)
		{
			if (a.data == null)
				throw new NullReferenceException("Умножение невозможно. Объект не инициализирован\n");

			TMatrix<Type> result = new TMatrix<Type>(a);

			for (int i = 0; i < result.Rows; i++)
				for (int j = 0; j < result.Cols; j++)
					result.data[i, j] = (dynamic)result.data[i, j] * b;

			return result;
		}

		public static TMatrix<Type> operator *(Type number, TMatrix<Type> b)
			=> b * number;

		public override string ToString()
			=> ToString("G", CultureInfo.CurrentCulture);

		public string ToString(IFormatProvider provider)
			=> ToString("G", provider);

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
				format = string.Format(char.IsLetter(format[0]) || format[0] == '0' ? "{{0:{0}}} " : "{{0,{0}}}", format);
			}

			StringBuilder str = new StringBuilder(Convert.ToInt32(width) * data.Length + 2 * data.GetLength(0));

			for (int i = 0; i < Rows; i++)
			{
				for (int j = 0; j < Cols; j++)
					str.AppendFormat(format, ((dynamic)data[i, j]).ToString(provider));

				str.AppendFormat("\n");
			}

			return str.ToString();
		}

		object ICloneable.Clone()
			=> Clone();

		public TMatrix<Type> Clone()
			=> new TMatrix<Type>(this);

		IEnumerator IEnumerable.GetEnumerator()
			=> data?.GetEnumerator();

		public IEnumerator<Type> GetEnumerator()
		{
			for (int i = 0; i < data.GetLength(0); i++)
				for (int j = 0; j < data.GetLength(1); j++)
					yield return data[i, j];
		}

		public static bool operator == (TMatrix<Type> left, TMatrix<Type> right)
			=> left?.Rows == right?.Rows && left?.Cols == right?.Cols;

		public static bool operator != (TMatrix<Type> left, TMatrix<Type> right)
			=> !(left == right);

		public static bool operator > (TMatrix<Type> left, TMatrix<Type> right)
			=> left?.Rows * left?.Cols > right?.Rows * right?.Cols;

		public static bool operator < (TMatrix<Type> left, TMatrix<Type> right)
			=> left?.Rows * left?.Cols < right?.Rows * right?.Cols;

		public static bool operator >= (TMatrix<Type> left, TMatrix<Type> right)
			=> left == right || left > right;

		public static bool operator <= (TMatrix<Type> left, TMatrix<Type> right)
			=> left == right || left < right;

		public override bool Equals(object obj)
			=> base.Equals(obj);

		public override int GetHashCode()
			=> base.GetHashCode();

		public int CompareTo(object obj)
		{
			if (!(obj is TMatrix<Type>))
				throw new ArgumentException("Объект не совпадает с типом (TMatrix<Type>) данного экземпляра.");

			return CompareTo((TMatrix<Type>)obj);
		}

		public int CompareTo(TMatrix<Type> other)
			=> this == other ? 0 : this > other ? 1 : -1;

	}
}
