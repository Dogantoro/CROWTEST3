#pragma once
#include <unordered_map>
#include <string>
#include <set>
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
    int index;
public:
    AdjMatrix() {
        for (int i = 0; i < 8009; i++) {
            for (int j = 0; j < 8009; j++) {
                graph[i][j] = InteractionSeverity::NONE;
            }
        }
        index = 0;
    }
    void addEdge(std::string from, std::string to, std::string interType);
    int getSize() {  // number of drugs in graph
        return 8009;
    }
    std::set<InteractionDesc> getInteractions(std::string drug);
    DrugInfo getDrugInfo(std::string drug);
    std::string randomDrug() {  // finds a random drug in the graph
        std::mt19937 randNum(std::time(nullptr));
        int index = randNum() % getSize();
        return reverseMapper[index];
    }
};

void AdjMatrix::addEdge(std::string from, std::string to, std::string interType) {
    from = convertName(from);
    to = convertName(to);
    if (mapper.find(from) == mapper.end()) {
        mapper[from] = ++index;
        reverseMapper[index] = from;
    }
    if (mapper.find(to) == mapper.end()) {
        mapper[to] = ++index;
        reverseMapper[index] = to;
    }
    graph[mapper[from]][mapper[to]] = convert(interType);
    graph[mapper[to]][mapper[from]] = convert(interType);
}

std::set<InteractionDesc> AdjMatrix::getInteractions(std::string drug) {
    int y = mapper[drug];
    std::set<InteractionDesc> ints;
    for (int i = 0; i < getSize(); i++) {
        InteractionDesc inter = {reverseMapper[i], graph[y][i]};
        if (inter.severity != InteractionSeverity::NONE)
            ints.insert(inter);
    }
    return ints;
}

DrugInfo AdjMatrix::getDrugInfo(std::string drug) {
    auto ints = getInteractions(drug);
    DrugInfo di;
    di.name = convertName(drug);
    di.DrugInfo::interactions = ints;
    return di;
}
