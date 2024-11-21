#include<vector>
#pragma once


//Структура предназначенная для считывания значений точек из файла 
struct DataPoints {

	double x;//Первое значение
	double y;//Второе значение	
	double z;//Третье значение

};
//Структура предназначенна для считывания заголовковков
struct NameAndLength {
	std::string Name;// Имя
	int Len;// длинна таблицы
};

//Структура предназначенная для считывания значений Фреймов из файла 
struct DataFrame {

	int A;//Первое значение
	int	 B;//Второе значение	
	int C;//Третье значение

};
struct DVectors {
	std::vector<std::vector<double>>XYZ;// Объявляем вектор хранящий данные x,y,z
	std::vector<std::vector<int>>ABC;// Объявляем вектор хранящий данные позиций А,В,С
};
DVectors getVectorsDataAndPos();
