#include<vector>
#pragma once


//��������� ��������������� ��� ���������� �������� ����� �� ����� 
struct DataPoints {

	double x;//������ ��������
	double y;//������ ��������	
	double z;//������ ��������

};
//��������� �������������� ��� ���������� �������������
struct NameAndLength {
	std::string Name;// ���
	int Len;// ������ �������
};

//��������� ��������������� ��� ���������� �������� ������� �� ����� 
struct DataFrame {

	int A;//������ ��������
	int	 B;//������ ��������	
	int C;//������ ��������

};
struct DVectors {
	std::vector<std::vector<double>>XYZ;// ��������� ������ �������� ������ x,y,z
	std::vector<std::vector<int>>ABC;// ��������� ������ �������� ������ ������� �,�,�
};
DVectors getVectorsDataAndPos();
