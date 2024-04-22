#pragma once
#include <unordered_map>
#include <string>
#include "json-mgr.h"

class AdjMatrix {
private:
    InteractionSeverity graph[8009][8009];
    std::unordered_map<std::string, int> mapper;
    std::string reverseMapper[8009];
public:
    void addEdge(std::string from, std::string to, std::string interType);
    int getSize(){ //just amount of drugs in graph
        return 8009;
    }
    std::set<InteractionDesc> getInteractions(std::string drug);
    DrugInfo getDrugInfo(std::string drug);
};

void AdjMatrix::addEdge(std::string from, std::string to, std::string interType) {
    int index = 0;
    if (mapper.find(from) == mapper.end()) {
        mapper[from] = index++;
        reverseMapper[index] = from;
    }
    if (mapper.find(to) == mapper.end()) {
        mapper[to] = index++;
        reverseMapper[index] = to;
    }
    graph[mapper[from]][mapper[to]] = convert(interType);
}

std::set<InteractionDesc> AdjMatrix::getInteractions(std::string drug) {
    int y = mapper[drug];
    std::set<InteractionDesc> ints;
    for (int i = 0; i < getSize(); i++) {
        InteractionDesc inter = {reverseMapper[i], graph[y][i]};
        ints.insert(inter);
    }    
    return ints;
}

DrugInfo AdjMatrix::getDrugInfo(std::string drug) {
    auto ints = getInteractions(drug);
    DrugInfo di;
    di.name = drug;
    di.DrugInfo::interactions = ints;
    return di;
}
