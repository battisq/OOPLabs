#include "Vectorr.h"
#include <iostream>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Math
{
	int Vectorr::ID = 0;

	Vectorr::Vectorr(double newX, double newY, double newZ)
	{
		setAll(newX, newY, newZ);

		id = ++ID;
		std::cout << "Конструктор вектора " << id << std::endl;
	}

	Vectorr::Vectorr(const Vectorr &newVVec)
	{
		copyVVec(newVVec);

		id = ++ID;
		std::cout << "Конструктор вектора " << id << std::endl;
	}

	Vectorr::~Vectorr()
	{
		std::cout << "Деструктор вектора " << id << std::endl;
	}

	double Vectorr::getX(void) const
	{
		return x;
	}

	double Vectorr::getY(void) const
	{
		return y;
	}

	double Vectorr::getZ(void) const
	{
		return z;
	}

	void Vectorr::printVVec(void) const
	{
		std::cout << "x = " << x << "\ty = " << y << "\tz = " << z << std::endl;
	}

	int Vectorr::getId(void) const
	{
		return id;
	}

	void Vectorr::setX(double newX)
	{
		x = newX;
	}

	void Vectorr::setY(double newY)
	{
		y = newY;
	}

	void Vectorr::setZ(double newZ)
	{
		z = newZ;
	}

	void Vectorr::setAll(double newX, double newY, double newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
	}

	double Vectorr::moduleVVec(void) const
	{
		return sqrt(x*x + y * y + z * z);
	}

	Vectorr & Vectorr::copyVVec(const Vectorr & source)
	{
		//x = source.x;
		//y = source.y;
		//z = source.z;
		source.copyTo(*this);

		return *this;
	}

	Vectorr & Vectorr::copyTo(Vectorr & source) const
	{
		source.x = x;
		source.y = y;
		source.z = z;

		return source;
	}

	Vectorr & Vectorr::mulOnScal(double coeff)
	{
		x *= coeff;
		y *= coeff;
		z *= coeff;

		return *this;
	}

	Vectorr & Vectorr::normVVec(void)
	{
		double module = moduleVVec();

		if (!module)
			exception(id);

		x /= module;
		y /= module;
		z /= module;

		return *this;
	}

	Vectorr add(const Vectorr & a, const Vectorr & b)
	{
		return Vectorr(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	Vectorr sub(const Vectorr & a, const Vectorr & b)
	{
		return Vectorr(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	Vectorr mul(const Vectorr & a, const Vectorr & b)
	{
		return Vectorr(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	double scalMulVVec(const Vectorr & a, const Vectorr & b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	double cos(const Vectorr & a, const Vectorr & b)
	{
		double aMod = a.moduleVVec(), bMod = b.moduleVVec();

		if (!aMod || !bMod)
			a.exception(aMod == 0 ? a.getId() : b.getId());

		return scalMulVVec(a, b) / (aMod * bMod);
	}

	double sin(const Vectorr & a, const Vectorr & b)
	{
		double aMod = a.moduleVVec(), bMod = b.moduleVVec();

		if (!aMod || !bMod)
			a.exception(aMod == 0 ? a.getId() : b.getId());

		return mul(a, b).moduleVVec() / (aMod * bMod);
	}

	double angle(const Vectorr & a, const Vectorr & b)
	{
		return atan2(sin(a, b), cos(a, b)) * 180 / M_PI; // 180/PI  радианы в градусы 
	}

	void Vectorr::exception(int id) const
	{
		throw "Ошибка, вектор " + std::to_string(id) + " производит деление на 0\n";
	}
};