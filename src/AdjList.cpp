#include "AdjList.h"

void AdjList::addEdge(std::string from, std::string to, std::string interType){
    DrugInfo drug1, drug2;
    drug1.name = from;
    drug2.name = to;
    graph[from] = drug1;
    graph[to] = drug2;
    InteractionDesc inter1 = {to, convert(interType)};
    InteractionDesc inter2 = {from, convert(interType)};
    graph[from].push_back(inter1);
    graph[to].push_back(inter2);
}
