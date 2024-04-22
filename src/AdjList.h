#pragma once
#include "json-mgr.h"
#include <unordered_map>
#include <cctype>
#include <ctime>
#include <random>

class AdjList {
private:
    std::unordered_map<std::string, DrugInfo> graph;


public:
    void addEdge(std::string from, std::string to, std::string interType);
    int getSize() {
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
    // name should have first letter be capitalized and rest should not be
    void convertName(std::string &name) {
        if (name.empty())
            return;
        name[0] = std::toupper(name[0]);
        for (size_t i = 1; i < name.size(); ++i)
            name[i] = std::tolower(name[i]);
    }

    std::string randomDrug() {
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

