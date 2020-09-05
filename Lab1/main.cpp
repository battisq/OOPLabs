#include <cstdio>
#include <clocale>
#include <string>
#include <iostream>
#include "Vectorr.h"

using namespace Math;

int main(void)
{
	setlocale(LC_ALL, "Rus");

	Vectorr objA(7, 3, 5), objB;

	printf("\nВектор %d:\n", objA.getId());
	objA.printVVec();

	objB.setX(8);
	objB.setY(1);
	objB.setZ(4);

	printf("\nВектор %d:\n", objB.getId());
	objB.printVVec();

	try
	{
		//printf("\nМодуль вектора %d = %lf\n\n", objA.getId(), objA.moduleVec());
		//printf("Модуль вектора %d = %lf\n\n", objB.getId(), objB.moduleVec());

		//printf("Копирование вектора %d в %d:\n", objB.getId(), objA.getId());
		//objA.copyVec(objB);
		//objA.printVec();

		//printf("\nУмножение вектора %d на \"4\":\n", objB.getId());
		//objB.mulOnScal(4);
		//objB.printVec();

		objA.setAll(7, 8, 5);

		printf("\n");
		objA.printVVec();
		objA.copyTo(objB);
		objA.printVVec();

		//printf("\nНормирование вектора %d:\n", objA.getId());
		//objA.normVec();

		//printf("\n%lf\n", objA.moduleVec());

		//objA.printVec();

		//printf("Сложение %d и %d векторов:\n\n", objA.getId(), objB.getId());

		//Vector objC;

		//objC.copyVec(add(objA, objB));

		//printf("\nРезультат:\n");
		//objC.printVec();

		//printf("\nВычитание %d и %d векторов:\n\n", objA.getId(), objB.getId());
		//objC.copyVec(sub(objA, objB));

		//printf("\nРезультат:\n");
		//objC.printVec();

		//printf("\nУмножение %d и %d векторов:\n\n", objA.getId(), objB.getId());
		//objC.copyVec(mul(objA, objB));

		//printf("\nРезультат:\n");
		//objC.printVec();

		//printf("\nСкалярное умножение %d и %d векторов = %lf\n\n", objA.getId(), objB.getId(), scalMulVec(objA, objB));
		//objA.setAll(0, 0, 0);

		//printf("Косинус угла между %d и %d векторов = %lf\n\n", objA.getId(), objC.getId(), cos(objA, objB));

		//printf("Cинус угла между %d и %d векторов = %lf\n\n", objA.getId(), objB.getId(), sin(objA, objB));

		//objB.setAll(0, 0, 0);

		//printf("\nВеличины угла в градусах между векторами %d и %d в пределах[–pi, pi] = %lf\n", objA.getId(), objB.getId(), angle(objA, objB));
	}

	catch (const std::string &err)
	{
		std::cout << err << std::endl;
	}

	std::cin.get();

	return 0;
}
