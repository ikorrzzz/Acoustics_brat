#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include <sstream>
#include <vector>
#include"reader.h"




DVectors getVectorsDataAndPos()
{
	std::string path = "sphere_4k.obj";// имя файла
	//std::string path = "sphere_7k.obj";
	
	std::vector<std::vector<double>>Points;// вектор хранящий значения точек
	std::vector<std::vector<int>>PosPoints;//вектор хранящий значения позиций
	

	int lineNumber = 0;// Номер строки

	DataPoints Point;
	NameAndLength Zagolovok;
	DataFrame PosPoint;

	std::ifstream file(path);
	int End_Size_Point = 1;
	int End_Size_Frame = 1;
	if (!file.is_open()) //Проверка что файл открылся
	{
		std::cout << "Error file is not open" <<std:: endl;
		
	}
	std::string line;// Строка которая будет идти по нашему файлу

	// Запишем значение точек в двумерный массив
	 

	//Читаем файл построчно

	while (std::getline(file, line)) {

		std::stringstream ss(line);
		/*stringstream, позволяет связать поток ввода-вывода со строкой в памяти.
		Всё, что выводится в такой поток,
		добавляется в конец строки; всё, что считыватся из потока — извлекается из начала строки*/
		
		//Записываем размер первой таблицы значения точек
		if (lineNumber == 0) {
			ss >> Zagolovok.Name >> Zagolovok.Len;// имя и длинна
			End_Size_Point = Zagolovok.Len;// указываем номер последней строки значений точки 
		
		}
		if (lineNumber != 0 && lineNumber<= End_Size_Point)//Здесь производим проверку если наша строка не нулевая или меньше 3522 поско
		{
			std::vector <double>DopVector;
			//Записываем рез-ты значения 
			ss >> Point.x >> Point.y >> Point.z;// выписываем из файла значение точки
			
			DopVector.push_back(Point.x);
			DopVector.push_back(Point.y);
			DopVector.push_back(Point.z);
			Points.push_back(DopVector);// Записываем значения в отдельный вектор
		}
		if(lineNumber== End_Size_Point+1)// Здесь производим переход к значениям Фреймов Заголовок
		{
			ss >> Zagolovok.Name >> Zagolovok.Len;
			End_Size_Frame = Zagolovok.Len;
		}
		if (lineNumber >= End_Size_Point + 2 && lineNumber <= End_Size_Point + 1 + End_Size_Frame)
		{// по аналогии, выписываем значения Фреймов
			//cout << lineNumber + 1 << endl;
			std::vector <int>DopVector;
			//Записываем рез-ты значения 
			ss >> PosPoint.A >> PosPoint.B >> PosPoint.C;

			DopVector.push_back(PosPoint.A);
			DopVector.push_back(PosPoint.B);
			DopVector.push_back(PosPoint.C);
			PosPoints.push_back(DopVector);
			//cout << PosPoint.SizeA << " " << PosPoint.SizeB << " " << PosPoint.SizeC << endl;
		}
		lineNumber++;
	}

	file.close(); // Закрываем файл
	

	DVectors dvectors;
	dvectors.XYZ = Points;
	dvectors.ABC = PosPoints;
	return dvectors;
}


