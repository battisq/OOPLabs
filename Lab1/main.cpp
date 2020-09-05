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

	printf("\n������ %d:\n", objA.getId());
	objA.printVVec();

	objB.setX(8);
	objB.setY(1);
	objB.setZ(4);

	printf("\n������ %d:\n", objB.getId());
	objB.printVVec();

	try
	{
		//printf("\n������ ������� %d = %lf\n\n", objA.getId(), objA.moduleVec());
		//printf("������ ������� %d = %lf\n\n", objB.getId(), objB.moduleVec());

		//printf("����������� ������� %d � %d:\n", objB.getId(), objA.getId());
		//objA.copyVec(objB);
		//objA.printVec();

		//printf("\n��������� ������� %d �� \"4\":\n", objB.getId());
		//objB.mulOnScal(4);
		//objB.printVec();

		objA.setAll(7, 8, 5);

		printf("\n");
		objA.printVVec();
		objA.copyTo(objB);
		objA.printVVec();

		//printf("\n������������ ������� %d:\n", objA.getId());
		//objA.normVec();

		//printf("\n%lf\n", objA.moduleVec());

		//objA.printVec();

		//printf("�������� %d � %d ��������:\n\n", objA.getId(), objB.getId());

		//Vector objC;

		//objC.copyVec(add(objA, objB));

		//printf("\n���������:\n");
		//objC.printVec();

		//printf("\n��������� %d � %d ��������:\n\n", objA.getId(), objB.getId());
		//objC.copyVec(sub(objA, objB));

		//printf("\n���������:\n");
		//objC.printVec();

		//printf("\n��������� %d � %d ��������:\n\n", objA.getId(), objB.getId());
		//objC.copyVec(mul(objA, objB));

		//printf("\n���������:\n");
		//objC.printVec();

		//printf("\n��������� ��������� %d � %d �������� = %lf\n\n", objA.getId(), objB.getId(), scalMulVec(objA, objB));
		//objA.setAll(0, 0, 0);

		//printf("������� ���� ����� %d � %d �������� = %lf\n\n", objA.getId(), objC.getId(), cos(objA, objB));

		//printf("C���� ���� ����� %d � %d �������� = %lf\n\n", objA.getId(), objB.getId(), sin(objA, objB));

		//objB.setAll(0, 0, 0);

		//printf("\n�������� ���� � �������� ����� ��������� %d � %d � ��������[�pi, pi] = %lf\n", objA.getId(), objB.getId(), angle(objA, objB));
	}

	catch (const std::string &err)
	{
		std::cout << err << std::endl;
	}

	std::cin.get();

	return 0;
}
