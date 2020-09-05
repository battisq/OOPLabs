#pragma once

namespace Math
{

	class Vectorr
	{
	public:

		explicit Vectorr(double newX = 0.0, double newY = 0.0, double newZ = 0.0);
		Vectorr(const Vectorr &newVVec);
		~Vectorr();

		double getX(void) const;
		double getY(void) const;
		double getZ(void) const;

		int getId(void) const;

		void printVVec(void) const;

		void setX(double newX);
		void setY(double newY);
		void setZ(double newZ);
		void setAll(double newX, double newY, double newZ);

		double moduleVVec(void) const;

		Vectorr &copyVVec(const Vectorr &source);
		Vectorr &copyTo(Vectorr &source) const;
		Vectorr &mulOnScal(double coeff);
		Vectorr &normVVec(void);

		friend Vectorr add(const Vectorr &a, const Vectorr &b);
		friend Vectorr sub(const Vectorr &a, const Vectorr &b);
		friend Vectorr mul(const Vectorr &a, const Vectorr &b);

		friend double scalMulVVec(const Vectorr &a, const Vectorr &b);

		friend double cos(const Vectorr &a, const Vectorr &b);
		friend double sin(const Vectorr &a, const Vectorr &b);
		friend double angle(const Vectorr &a, const Vectorr &b);

	private:
		double x, y, z;
		int id;
		static int ID;

		void exception(int id) const;
	};
};