using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Mathematics;

namespace Lab6
{
    class Program
    {
		static void Main(string[] args)
        {

			Matrix a = new Matrix(2, 2, (x, y) => x * y);
			Matrix c = a.Clone(), b = new Matrix(c);
			Console.WriteLine(a);
			//Console.WriteLine("{0:##.####}", 5643453.965131651);
			//Console.WriteLine("{0:f2, 8}", a);
			//Console.WriteLine("{0:5}", a);
			//Console.WriteLine("{0:14:000000.00000}", a);
			//Console.WriteLine("{0}", a);

			Console.ReadKey();
        }
    }
}
