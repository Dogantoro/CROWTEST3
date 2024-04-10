#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class AdjList {
private:
    // idk what im storing so ill do strings for now (drug names pointing to drug names)
    std::unordered_map<std::string, std::vector<std::string>> graph;
public:
    void addEdge(std::string from, std::string to);
    std::vector<std::string> getAdjacent(std::string vertex);

};
