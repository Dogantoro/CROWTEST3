#pragma once
#include <map>
#include "json-mgr.h"

class AdjMatrix {
private:
    InteractionSeverity graph[8009][8009];
    std::map<std::string, int> mapper;
public:
    void addEdge(std::string from, std::string to, std::string interType);
};

void AdjMatrix::addEdge(std::string from, std::string to, std::string interType) {
    int index = 0;
    if (mapper.find(from) == mapper.end())
        mapper[from] = index++;
    if (mapper.find(to) == mapper.end())
        mapper[to] = index++;
    graph[mapper[from]][mapper[to]] = convert(interType);
}
