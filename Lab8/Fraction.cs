using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mathematics
{
	struct Fraction : IFormattable, ICloneable, IComparable, IComparable<Fraction>
	{
		private int denominator;
		private bool autoReduce;

		private void Reduce()
		{
			if (!AutoReduce)
				return;

			if (Denominator < 0)
			{
				denominator = -Denominator;
				Numerator = -Numerator;
			}

			int div = Nod(Numerator, Denominator);
			
			Numerator /= div;
			denominator /= div;

			if (Numerator == 0)
				denominator = 1;
		}

		public Fraction(int numerator, int denominator = 1, bool autoReduce = false)
		{
			if (denominator == 0)
				throw new DivideByZeroException("Знаменатель дроби не должен быть равен 0. Деление на ноль\n");

			Numerator = numerator;
			this.denominator = denominator;
			this.autoReduce = autoReduce;

			Reduce();
		}

		public Fraction(Fraction source) : this(source.Numerator, source.Denominator) { }

		public int ToProper()
		{
			Numerator = Numerator % Denominator;

			return Numerator / Denominator;
		}

		public static Fraction operator + (Fraction a, Fraction b)
		{
			int newDen = Nok(a.Denominator, b.Denominator);
		
			return new Fraction(a.Numerator * (newDen / a.Denominator) + b.Numerator * (newDen / b.Denominator), newDen, a.AutoReduce && b.AutoReduce);
		}

		public static Fraction operator - (Fraction a, Fraction b)
		{
			int newDen = Nok(a.Denominator, b.Denominator);

			return new Fraction(a.Numerator * (newDen / a.Denominator) - b.Numerator * (newDen / b.Denominator), newDen, a.AutoReduce && b.AutoReduce);
		}

		public static Fraction operator * (Fraction a, Fraction b) 
			=> new Fraction(a.Numerator * b.Numerator, a.Denominator * b.Denominator, a.AutoReduce && b.AutoReduce);

		public static Fraction operator / (Fraction a, Fraction b) 
			=> new Fraction(a.Numerator * b.Denominator, a.Denominator * b.Numerator, a.AutoReduce && b.AutoReduce);

		public static explicit operator int(Fraction a)
			=> a.Numerator / a.Denominator;

		public static explicit operator double(Fraction a)
			=> (double)a.Numerator / a.Denominator;

		public static implicit operator Fraction(int a)
			=> new Fraction(a);

		public int Numerator { get; private set; }

		public int Denominator
		{
			get
			{
				if (denominator == 0)
					denominator = 1;

				return denominator;
			}
		}

		public bool AutoReduce
		{
			get => autoReduce;

			set
			{
				autoReduce = value;

				Reduce();
			}
		}

		public override string ToString()
			=> ToString("G", CultureInfo.CurrentCulture);

		public string ToString(string format)
			=> ToString(format, CultureInfo.CurrentCulture);

		public string ToString(IFormatProvider provider)
			=> ToString("G", provider);

		public string ToString(string format, IFormatProvider provider)
		{
			provider = provider ?? CultureInfo.CurrentCulture;

			if (string.IsNullOrEmpty(format))
				format = "G";

			switch (format.ToUpperInvariant())
			{
				case "G":
					if (Denominator == 1)
						return string.Format(provider, "{0}", Numerator);
					else
						return string.Format(provider, "{0}/{1}", Numerator, Denominator);
				default:
					throw new FormatException(string.Format($"Ошибка! Формат {format} неизвестен."));
			}
		}

		public static int Nok(int a, int b)
			=> a * b / Nod(a, b);

		public static int Nod(int a, int b)
		{
			if (a < 0)
				a = -a;

			if (b < 0)
				b = -b;

			for (int i = a; i > 0; i--)
				if (a % i == 0 && b % i == 0)
					return i;

			return 1;
		}

		object ICloneable.Clone()
			=> Clone();
		
		public Fraction Clone()
			=> new Fraction(this);

		public static bool operator == (Fraction a, Fraction b)
			=> a.Numerator == b.Numerator && a.Denominator == b.Denominator;
		
		public static bool operator != (Fraction a, Fraction b)
			=> !(a == b);

		public static bool operator > (Fraction a, Fraction b)
			=> (long)a.Numerator * b.Denominator > (long)a.Denominator * b.Numerator;

		public static bool operator < (Fraction a, Fraction b)
			=> (long)a.Numerator * b.Denominator < (long)a.Denominator * b.Numerator;

		public static bool operator >= (Fraction a, Fraction b)
			=> a == b || a > b;

		public static bool operator <= (Fraction a, Fraction b)
			=> a == b || a < b;

		public override bool Equals(object obj)
			=> base.Equals(obj);

		public override int GetHashCode()
			=> Numerator * Denominator ^ 8;

		public int CompareTo(object obj)
		{
			if (!(obj is Fraction))
				throw new ArgumentException("Объект не совпадает с типом (Fraction) данного экземпляра.");

			return CompareTo((Fraction)obj);
		}

		public int CompareTo(Fraction other)
			=> this == other ? 0 : this > other ? 1 : -1;
	} 
}

