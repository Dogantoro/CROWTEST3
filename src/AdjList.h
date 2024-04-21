#pragma once
#include "json-mgr.h"
#include <unordered_map>
#include <cctype>

class AdjList {
private:
    std::unordered_map<std::string, DrugInfo> graph;


public:
    void addEdge(std::string from, std::string to, std::string interType);
    int getSize() {
        return (int)(graph.size());
    }
    std::vector<InteractionDesc> getInteractions(DrugInfo drug) {
        return drug.DrugInfo::interactions;
    }

    bool ifDrug(std::string drug) {
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
};

void AdjList::addEdge(std::string from, std::string to, std::string interType){
    DrugInfo drug1, drug2;
    drug1.name = from;
    drug2.name = to;
    graph[from] = drug1;
    graph[to] = drug2;
    InteractionDesc inter1 = {to, convert(interType)};
    InteractionDesc inter2 = {from, convert(interType)};
    graph[from].DrugInfo::interactions.push_back(inter1);
    graph[to].DrugInfo::interactions.push_back(inter2);
}

