#pragma once
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class AdjList {
private:
    // idk what im storing so ill do strings for now (drug names pointing to drug names)
    unordered_map<string, vector<string>> graph;
public:
    void addEdge(string from, string to);
    vector<string> getAdjacent(string vertex);

};
