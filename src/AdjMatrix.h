#pragma once
#include <map>
#include "json-mgr.h"

class AdjMatrix {
private:
    std::string** graph;
    std::map<std::string, int> mapper;
public:
    AdjMatrix(int num) {
    graph = new bool*[num];
    for (int i = 0; i < num; i++) {
      graph[i] = new bool[num];
      for (int j = 0; j < num; j++)
        graph[i][j] = NULL;
  }
    }
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
