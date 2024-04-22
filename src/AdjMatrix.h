#pragma once
#include <unordered_map>
#include <string>
#include "json-mgr.h"
#include <ctime>

class AdjMatrix {
private:
    // the x and y coords are different drugs and the overall coordinate is the interaction between the drugs
    InteractionSeverity graph[8009][8009];
    // to keep track of the index of a drug
    std::unordered_map<std::string, int> mapper;
    // to easily access a drug by index
    std::string reverseMapper[8009];
public:
    void addEdge(std::string from, std::string to, std::string interType);
    int getSize(){ //just amount of drugs in graph
        return 8009;
    }
    
    std::set<InteractionDesc> getInteractions(std::string drug);
    DrugInfo getDrugInfo(std::string drug);
    std::string randomDrug() { //finds a random drug in the graph
        std::mt19937 randNum(std::time(nullptr));
        int index = randNum() % getSize();
        return reverseMapper[index];
    }
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
