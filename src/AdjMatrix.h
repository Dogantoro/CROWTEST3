#pragma once

class AdjMatrix {
private:
    // will prob have to make a map
    bool** graph;
    int numVertices;
public:
    AdjMatrix(int num);
    void addEdge();


};
