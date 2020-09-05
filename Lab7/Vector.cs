using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mathematics
{
	class Vector : Matrix, ICloneable
	{
		public Vector() : base() { }

		public Vector(int size) : base(size, 1) { }

		public Vector(double[] vector) : this(vector == null ? 0 : vector.Length)
		{
			if (vector == null)
				return;

			data = vector.Length != 0 ? new double[vector.Length, 1] : null;

			for (int i = 0; i < vector.Length; i++)
				data[i, 0] = vector[i];
		}

		public Vector(int size, params double[] list) : base(size, 1, list) { }

		public Vector(Vector source) : base(source) { }

		public Vector(Matrix source) : base(source?.Rank == 1 ? source : new Vector())
		{
			if (source.Rank > 2)
				new ArgumentException("Вектор не может перенять свойства матрицы");
		}

		public double this[int i]
		{
			get
			{
				if (i < 0 || i >= data.Length)
					throw new IndexOutOfRangeException("Неверный индекс для вектора\n");

				return data.GetLength(0) > 1 ? data[i, 0] : data[0, i];
			}

			set
			{
				if (data.GetLength(0) > 1)
				{
					if (data[i, 0] != value)
						data[i, 0] = value;
				}
				else
					if (data[0, i] != value)
						data[0, i] = value;
			}
		}

		/// <summary>
		/// Недоступная операция для вектора
		/// </summary>
		public override double this[int i, int j]
		{
			get => throw new NotImplementedException("Данная операция не поддерживается");
			set => throw new NotImplementedException("Данная операция не поддерживается");
		}

		/// <summary>
		/// Недоступная операция для вектора
		/// </summary>
		public override int Cols
			=> throw new NotImplementedException("Данная операция не поддерживается");

		/// <summary>
		/// Недоступная операция для вектора
		/// </summary>
		public override int Rows
			=> throw new NotImplementedException("Данная операция не поддерживается");

		public int Size 
			=> data == null ? 0 : data.Length;

		public bool IsColumn
			=> data?.GetLength(1) > 0 ? false : true;

		public void Transposition()
		{
			double[,] temp = new double[data.GetLength(1), data.GetLength(0)];

			for (int i = 0; i < data.GetLength(0); i++)
				for (int j = 0; j < data.GetLength(1); j++)
					temp[j, i] = data[i, j];

			data = temp;
			temp = null;
		}

		new public Vector Clone() 
			=> new Vector(this);

		public static Vector operator + (Vector a, Vector b)
		{
			Vector result = CheckSum(a, b) ? new Vector(a) : null;

			Add(a, b, result);

			return result;
		}

		public static Vector operator - (Vector a, Vector b)
		{
			Vector result = CheckSum(a, b) ? new Vector(a) : null;

			Sub(a, b, result);

			return result;
		}

		public static Vector operator * (Vector a, double number)
		{
			Vector result = new Vector(a);

			Mul(a, number, result);

			return result;
		}

		public static Vector operator * (double number, Vector b)
			=> b * number;
	}
}
