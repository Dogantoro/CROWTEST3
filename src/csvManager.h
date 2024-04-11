#pragma once
#include <fstream> 
#include <iostream> 
#include <string>
#include "AdjList.h"

void processCSVs(){
    std::string fileNames[8] = {"templates/databases/ddinter_downloads_code_A.csv",
                                "templates/databases/ddinter_downloads_code_B.csv",
                                "templates/databases/ddinter_downloads_code_D.csv",
                                "templates/databases/ddinter_downloads_code_H.csv",
                                "templates/databases/ddinter_downloads_code_L.csv",
                                "templates/databases/ddinter_downloads_code_P.csv",
                                "templates/databases/ddinter_downloads_code_R.csv",
                                "templates/databases/ddinter_downloads_code_V.csv"};

    for(std::string curFile : fileNames){
        std::ifstream inFile(curFile);
        std::string temp;

        for (int i = 0; i < 4; i++){
            getline(inFile, temp, ',');
            std::cout << temp << std::endl;
        }

    }
}
