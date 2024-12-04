#include <iostream>
#include <fstream>
#include <sstream>
#include "main_header.hpp"

int getVectorsDataAndPos(DVectors &dvectors, const std::string &path ) {

    std::vector<DataPoints>Points;
    std::vector<DataFrame>PosPoints;

    int lineNumber = 0;


    NameAndLength Zagolovok;


    std::ifstream file(path);
    int End_Size_Point = 1;
    int End_Size_Frame = 1;
    if (!file.is_open()){
        std::cout << "Error file is not open" <<std:: endl;
        return -1;

    }
    std::string line;

    while (std::getline(file, line)) {

        std::stringstream ss(line);

        if (lineNumber == 0) {
            ss >> Zagolovok.Name >> Zagolovok.Len;
            End_Size_Point = Zagolovok.Len;

        }
        if (lineNumber != 0 && lineNumber<= End_Size_Point){
            DataPoints Point;
            ss >> Point.x >> Point.y >> Point.z;
            Points.push_back(Point);
        }
        if(lineNumber== End_Size_Point+1){
            ss >> Zagolovok.Name >> Zagolovok.Len;
            End_Size_Frame = Zagolovok.Len;
        }
        if (lineNumber >= End_Size_Point + 2 && lineNumber <= End_Size_Point + 1 + End_Size_Frame){
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

    file.close(); 

    dvectors.XYZ = Points;
    dvectors.ABC = PosPoints;
    return 0;
}


