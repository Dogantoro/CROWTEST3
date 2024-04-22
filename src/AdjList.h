#pragma once
#include "json-mgr.h"
#include <unordered_map>
#include <ctime>
#include <random>

class AdjList {
private:
    std::unordered_map<std::string, DrugInfo> graph;


public:
    void addEdge(std::string from, std::string to, std::string interType);
    int getSize() { //how many drugs are in graph
        return (int)(graph.size());
    }
    std::set<InteractionDesc> getInteractions(DrugInfo drug) {
        return drug.DrugInfo::interactions;
    }

    bool drugExists(std::string drug) {
        return graph.find(drug) != graph.end();
    }
    DrugInfo getDrugInfo(std::string drug) {
            return graph[drug];
    }

    std::string randomDrug() { //finds a random drug in the graph
        std::mt19937 randNum(std::time(nullptr));
        int index = randNum() % getSize();
        auto random = *std::next(std::begin(graph), index);
        return random.first;
    }
};

void AdjList::addEdge(std::string from, std::string to, std::string interType){
    DrugInfo fromDrug, toDrug;
    fromDrug.name = from;
    toDrug.name = to;
    if (!drugExists(from))
        graph[from] = fromDrug;
    if (!drugExists(to))
        graph[to] = toDrug;
    InteractionDesc inter1 = {to, convert(interType)};
    // not all interactions involving a certain drug are displayed without this
    InteractionDesc inter2 = {from, convert(interType)};
    graph[from].DrugInfo::interactions.insert(inter1);
    graph[to].DrugInfo::interactions.insert(inter2);
}

