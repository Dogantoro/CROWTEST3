#pragma once
#include <fstream> 
#include <iostream> 
#include <string>
#include<boost/tokenizer.hpp>
#include <boost/progress.hpp>
#include "AdjList.h"
#include "AdjMatrix.h"

// loads database info into an adjacency list and adjacency graph
void processCSVs(AdjList* listGraph, AdjMatrix* matrixGraph) {
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
        boost::tokenizer<boost::escaped_list_separator<char>> token(temp);

        getline(inFile, temp);  // remove first csv line with column labels

        // gets each value and adds corresponding edges (ignoring database drug ids)
        while (getline(inFile, temp)) {
            token.assign(temp.begin(), temp.end());
            auto it = token.begin();
            it++;
            drug1 = *it;
            it++;
            it++;
            drug2 = *it;
            it++;
            interLevel = *it;
            listGraph->addEdge(drug1, drug2, interLevel);
            matrixGraph->addEdge(drug1, drug2, interLevel);
        }
        ++progress;
        inFile.close();
    }
}
