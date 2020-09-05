using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Mathematics;

namespace Lab7
{
	class Program
	{
		static void Main()
		{
			try
			{
				Vector v = new Vector(4, 2, 5, 9, 6), v1 = new Vector(4, 8, 4, 3, 7);

				Console.WriteLine(v);

				v1.Transposition();
				Console.WriteLine(v1);

				Console.WriteLine(v1 * 8);

				Matrix m = new Vector(3, 5, 6, 7), m1 = new Vector(3, 1, 2, 3, 4);

				Console.WriteLine(Matrix.CheckSum(m, m1));
				Console.WriteLine(v1.Max());

			}

			catch(Exception ex)
			{
				Console.WriteLine(ex);
			}
			//Base b = new Matrix(m);
			//m = (Matrix)b.Clone();
			//m *= 1;

			//NotImplementedException
			//mt.Clone();
			//Vector v = new Vector(4, 2, 5, 9, 6), v1 = new Vector();
			//v += v1;
			//Vector[] vm = new Vector[4] { new Vector(v), new Vector(v1), new Vector(v), new Vector(v1) };
			//
			//foreach(var elvec in vm)
			//{
			//	Console.WriteLine(elvec);
			//}
			//IEnumerator<double> num = v._data.Cast<double>().GetEnumerator();
			//
			//foreach (double el in v)
			//	Console.WriteLine(el);
			//Matrix m = new Matrix(2, 2), m1 = new Matrix(m);
			//v += v1;
			//
			//v.Transposition();
			//Console.WriteLine(Base.CheckMul (m, m1));

			Console.ReadKey();
		}
	}
}
