#include <iostream>
#include <fstream>
#include <sstream>
#include "main_header.hpp"

int getVectorsDataAndPos(DVectors &dvectors, const std::string &path ) {

    std::vector<DataPoints>Points;// вектор хранящий значения точек
    std::vector<DataFrame>PosPoints;//вектор хранящий значения позиций

    int lineNumber = 0;// Номер строки


    NameAndLength Zagolovok;


    std::ifstream file(path);
    int End_Size_Point = 1;
    int End_Size_Frame = 1;
    if (!file.is_open()) //Проверка что файл открылся
    {
        std::cout << "Error file is not open" <<std:: endl;
        return -1;

    }
    std::string line;// Строка которая будет идти по нашему файлу

    while (std::getline(file, line)) {

        std::stringstream ss(line);

        if (lineNumber == 0) {
            ss >> Zagolovok.Name >> Zagolovok.Len;// имя и длинна
            End_Size_Point = Zagolovok.Len;// указываем номер последней строки значений точки

        }
        if (lineNumber != 0 && lineNumber<= End_Size_Point)//Здесь производим проверку если наша строка не нулевая или меньше 3522 поско
        {
            DataPoints Point;
            ss >> Point.x >> Point.y >> Point.z;// выписываем из файла значение точки
            Points.push_back(Point);// Записываем значения в отдельный вектор
        }
        if(lineNumber== End_Size_Point+1)// Здесь производим переход к значениям Фреймов Заголовок
        {
            ss >> Zagolovok.Name >> Zagolovok.Len;
            End_Size_Frame = Zagolovok.Len;
        }
        if (lineNumber >= End_Size_Point + 2 && lineNumber <= End_Size_Point + 1 + End_Size_Frame)
        {
            DataFrame PosPoint;
            int A, B, C;
            ss >> A >> B >> C;
            PosPoint.A = A-1;
            PosPoint.B = B-1;
            PosPoint.C = C-1;
            PosPoints.push_back(PosPoint);
        }
        lineNumber++;
    }

    file.close(); // Закрываем файл

    dvectors.XYZ = Points;
    dvectors.ABC = PosPoints;
    return 0;
}


