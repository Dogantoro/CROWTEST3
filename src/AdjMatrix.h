#pragma once
#include <unordered_map>
#include "json-mgr.h"

class AdjMatrix {
private:
    InteractionSeverity graph[8008][8008];
    std::unordered_map<std::string, int> mapper;
public:
    void addEdge(std::string from, std::string to, std::string interType);
    int getSize(){ //just amount of drugs in graph
        return (int)(sizeof(graph[0])/sizeof(graph[0][0]));
    }
    std::vector<InteractionSeverity> getInteractions(std::string drug);
};

void AdjMatrix::addEdge(std::string from, std::string to, std::string interType) {
    int index = 0;
    if (mapper.find(from) == mapper.end())
        mapper[from] = index++;
    if (mapper.find(to) == mapper.end())
        mapper[to] = index++;
    graph[mapper[from]][mapper[to]] = convert(interType);
}

std::vector<InteractionSeverity> AdjMatrix::getInteractions(std::string drug)
{ // need to get name of other drug but im struggling
    int y = mapper[drug];
    //auto it = mapper.begin();
    std::vector<InteractionSeverity> ints;
    for (auto i : graph[y])
        ints.push_back(i);
    return ints;
}

