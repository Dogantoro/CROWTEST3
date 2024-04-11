#pragma once
#include "json-mgr.h"
#include <unordered_map>

class AdjList {
private:
    std::unordered_map<std::string, DrugInfo> graph;


public:
    void addEdge(std::string from, std::string to, std::string interType);

};
