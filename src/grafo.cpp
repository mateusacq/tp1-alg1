#include "grafo.hpp"

Grafo::Grafo() 
    : numVertices(0), numArestas(0), arestas(0) {}

Grafo::Grafo(int n, int m) 
    : numVertices(n), numArestas(m), arestas(n) {}
