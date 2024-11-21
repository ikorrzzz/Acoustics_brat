#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include <sstream>
#include <vector>
#include"reader.h"




DVectors getVectorsDataAndPos()
{
	std::string path = "sphere_4k.obj";// ��� �����
	//std::string path = "sphere_7k.obj";
	
	std::vector<std::vector<double>>Points;// ������ �������� �������� �����
	std::vector<std::vector<int>>PosPoints;//������ �������� �������� �������
	

	int lineNumber = 0;// ����� ������

	DataPoints Point;
	NameAndLength Zagolovok;
	DataFrame PosPoint;

	std::ifstream file(path);
	int End_Size_Point = 1;
	int End_Size_Frame = 1;
	if (!file.is_open()) //�������� ��� ���� ��������
	{
		std::cout << "Error file is not open" <<std:: endl;
		
	}
	std::string line;// ������ ������� ����� ���� �� ������ �����

	// ������� �������� ����� � ��������� ������
	 

	//������ ���� ���������

	while (std::getline(file, line)) {

		std::stringstream ss(line);
		/*stringstream, ��������� ������� ����� �����-������ �� ������� � ������.
		��, ��� ��������� � ����� �����,
		����������� � ����� ������; ��, ��� ���������� �� ������ � ����������� �� ������ ������*/
		
		//���������� ������ ������ ������� �������� �����
		if (lineNumber == 0) {
			ss >> Zagolovok.Name >> Zagolovok.Len;// ��� � ������
			End_Size_Point = Zagolovok.Len;// ��������� ����� ��������� ������ �������� ����� 
		
		}
		if (lineNumber != 0 && lineNumber<= End_Size_Point)//����� ���������� �������� ���� ���� ������ �� ������� ��� ������ 3522 �����
		{
			std::vector <double>DopVector;
			//���������� ���-�� �������� 
			ss >> Point.x >> Point.y >> Point.z;// ���������� �� ����� �������� �����
			
			DopVector.push_back(Point.x);
			DopVector.push_back(Point.y);
			DopVector.push_back(Point.z);
			Points.push_back(DopVector);// ���������� �������� � ��������� ������
		}
		if(lineNumber== End_Size_Point+1)// ����� ���������� ������� � ��������� ������� ���������
		{
			ss >> Zagolovok.Name >> Zagolovok.Len;
			End_Size_Frame = Zagolovok.Len;
		}
		if (lineNumber >= End_Size_Point + 2 && lineNumber <= End_Size_Point + 1 + End_Size_Frame)
		{// �� ��������, ���������� �������� �������
			//cout << lineNumber + 1 << endl;
			std::vector <int>DopVector;
			//���������� ���-�� �������� 
			ss >> PosPoint.A >> PosPoint.B >> PosPoint.C;

			DopVector.push_back(PosPoint.A);
			DopVector.push_back(PosPoint.B);
			DopVector.push_back(PosPoint.C);
			PosPoints.push_back(DopVector);
			//cout << PosPoint.SizeA << " " << PosPoint.SizeB << " " << PosPoint.SizeC << endl;
		}
		lineNumber++;
	}

	file.close(); // ��������� ����
	

	DVectors dvectors;
	dvectors.XYZ = Points;
	dvectors.ABC = PosPoints;
	return dvectors;
}


