using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Mathematics;

namespace Lab8
{
	class Program
	{

		static void Main()
		{
			try
			{
				var mi1 = new TMatrix<int>(2, 2, 9, 5, 1, 6);
				var mi2 = new TMatrix<int>((int[,])null);
				TMatrix<int> mi3 = null;

				Console.WriteLine(TMatrix<int>.CheckSum(mi1, mi1));
				Console.WriteLine(TMatrix<int>.CheckSum(mi1, mi2));
				Console.WriteLine(TMatrix<int>.CheckSum(mi1, mi3));
				Console.WriteLine(TMatrix<int>.CheckSum(mi2, mi3));

				//string s = "int";

				//Console.WriteLine(typeof(s.GetType())).ToString());

				//Fraction f = new Fraction();

				//Console.WriteLine(f.denominator);
				//f.AutoReduce = true;
				//Fraction f = new Fraction(7, 31), f1 = new Fraction(5, 7);
				//Console.WriteLine(typeof(int).GetInterfaces().Contains(typeof(ICloneable)));
				//Fraction[,] fm = new Fraction[2, 2] { { f, f }, { f1, f1 } };
				//Console.WriteLine("{0:X}", f);
				//var fmf = new TMatrix<Fraction>(fm);
				//
				//Console.WriteLine(f<Fraction>(f, f1));


				//int[,] i = new int[2, 2] { { 71, 22 }, { 83, 4 } };
				//double[,] d = new double[2, 2] { { 7.1, 2 }, { 8.3, 4.6 } };

				//var mi = new TMatrix<int>(i);
				//var mi1 = new TMatrix<int>(2, 2, 9, 5, 1, 6);

				//Console.WriteLine(TMatrix<int>.CheckSum(null, null));
				//Console.WriteLine(null < mi1);
				//Console.WriteLine(null == null);

				//var md = new TMatrix<double>(d);
				//var md1 = new TMatrix<double>(2, 2, 9, 5, 1, 6);

				//Console.WriteLine(mi1.CompareTo(md1));

				//var mf = new TMatrix<Fraction>(2, 2, new Fraction(5, 7), new Fraction(6), new Fraction(7, 31), new Fraction(7, 1));
				//var mf1 = new TMatrix<Fraction>(2, 2, new Fraction(56, 7), new Fraction(6), new Fraction(7, 31), new Fraction(7, 1));

				//var mm = new TMatrix<TMatrix<int>>(2, 2, new TMatrix<int>(mi), new TMatrix<int>(2, 3, 9, 5, 1, 6), new TMatrix<int>(2, 2, 9, 9, 11, 6), new TMatrix<int>(2, 2, 29, 5, 81, 66));
				//var mm1 = new TMatrix<TMatrix<int>>(2, 2, new TMatrix<int>(mi1), new TMatrix<int>(2, 2, 59, 55, 51, 56), new TMatrix<int>(2, 2, 98, 89, 11, 6), new TMatrix<int>(2, 2, 2229, 55, 781, 66));

				//Console.WriteLine("{0:5}", mi);
				//Console.WriteLine("{0:5}", mi1);

				//Console.WriteLine("{0:5}", md);
				//Console.WriteLine("{0:5}", md1);

				//Console.WriteLine("{0:5}", mf);
				//Console.WriteLine("{0:5}", mf1);

				//Console.WriteLine("{0:5}", mm);
				//Console.WriteLine("{0:5}", mm1);

				//Console.WriteLine("{0:5}", mi + mi1);
				//Console.WriteLine("{0:5}", mi - mi1);
				//Console.WriteLine("{0:5}", mi * mi1);

				//Console.WriteLine("{0:15}", md + md1);
				//Console.WriteLine("{0:15}", md - md1);
				//Console.WriteLine("{0:15}", md * md1);

				//Console.WriteLine("{0:15}", mf + mf1);
				//Console.WriteLine("{0:15}", mf - mf1);
				//Console.WriteLine("{0:15}", mf * mf1);

				//Console.WriteLine("{0:15}", mm + mm1);
				//Console.WriteLine("{0:15}", mm - mm1);
				//Console.WriteLine("{0:15}", mm * mm1);

				//Console.WriteLine(mi.CompareTo(mm));

				//Console.WriteLine("{0}", mm.Max());

				//foreach (var q in md1)
				//{
				//}

			}

			catch (Exception ex)
			{
				Console.WriteLine("{0}", ex.GetType());
				Console.WriteLine("{0}", ex.Message);
				Console.WriteLine("{0}", ex.TargetSite);
			}
			//int[] t = new int[7];

			//Fraction ff = new Fraction();
			//Console.WriteLine("{0}", ff);

			//Fraction[] f = new Fraction[3] { new Fraction(5,7), new Fraction(6) , new Fraction(7,31) };
			//Console.WriteLine(f.Max());
			//double d = (double)f[0];
			//var m = new TMatrix<Fraction>(2, 2);
			//var m1 = new TMatrix<Fraction>(m);
			//TMatrix<Fraction>.CheckSum(m, m1);
			//foreach (var el in f)
			//	Console.WriteLine(el.ToString("f"));

			Console.ReadKey();
		}
	}
}
