#pragma once
#include <fstream> 
#include <iostream> 
#include <string>
#include<boost/tokenizer.hpp>
#include <boost/progress.hpp>
#include "AdjList.h"
#include "AdjMatrix.h"


void processCSVs(AdjList* graph){
    boost::progress_display progress(8);
    // holds the names of the database files
    std::string fileNames[8] = {"/templates/databases/ddinter_downloads_code_A.csv",
                                "/templates/databases/ddinter_downloads_code_B.csv",
                                "/templates/databases/ddinter_downloads_code_D.csv",
                                "/templates/databases/ddinter_downloads_code_H.csv",
                                "/templates/databases/ddinter_downloads_code_L.csv",
                                "/templates/databases/ddinter_downloads_code_P.csv",
                                "/templates/databases/ddinter_downloads_code_R.csv",
                                "/templates/databases/ddinter_downloads_code_V.csv"};

    // process each csv whose name is in the fileNames array
    for (std::string curFile : fileNames) {
        std::ifstream inFile(SOURCE_DIR + curFile);
        std::string temp, drug1, drug2, interLevel;

        getline(inFile, temp);  // remove first csv line with column labels

        // gets each value and adds corresponding edges (ignoring database drug ids)
        while (getline(inFile, temp)) {
            boost::tokenizer<boost::escaped_list_separator<char>> token(temp);
            auto it = token.begin();
            it++;
            drug1 = *it;
            it++;
            it++;
            drug2 = *it;
            it++;
            interLevel = *it;
            graph->addEdge(drug1, drug2, interLevel);
        }
        ++progress;
        inFile.close();
    }
}

void processCSVs(AdjMatrix* graph){
    boost::progress_display progress(8);
    // holds the names of the database files
    std::string fileNames[8] = {"/templates/databases/ddinter_downloads_code_A.csv",
                                "/templates/databases/ddinter_downloads_code_B.csv",
                                "/templates/databases/ddinter_downloads_code_D.csv",
                                "/templates/databases/ddinter_downloads_code_H.csv",
                                "/templates/databases/ddinter_downloads_code_L.csv",
                                "/templates/databases/ddinter_downloads_code_P.csv",
                                "/templates/databases/ddinter_downloads_code_R.csv",
                                "/templates/databases/ddinter_downloads_code_V.csv"};

    // process each csv whose name is in the fileNames array
    for (std::string curFile : fileNames) {
        std::ifstream inFile(SOURCE_DIR + curFile);
        std::string temp, drug1, drug2, interLevel;

        getline(inFile, temp);  // remove first csv line with column labels

        // gets each value and adds corresponding edges (ignoring database drug ids)
        while (getline(inFile, temp)) {
            boost::tokenizer<boost::escaped_list_separator<char>> token(temp);
            auto it = token.begin();
            it++;
            drug1 = *it;
            it++;
            it++;
            drug2 = *it;
            it++;
            interLevel = *it;
            graph->addEdge(drug1, drug2, interLevel);
        }
        ++progress;
        inFile.close();
    }
}
