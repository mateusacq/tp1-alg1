#include "grafo.hpp"

// Para distancias no Dijkstra:
#define INFINITY 2147483647 // 2^31 - 1

Grafo::Grafo() 
    : numVertices(0), numArestas(0), arestas(1) {}

Grafo::Grafo(int n, int m) 
    : numVertices(n), numArestas(m), arestas(n + 1) {}

void Grafo::adicionaAresta(TipoV v, TipoV u, int peso) {
    arestas[v].push_back({peso, u});
    arestas[u].push_back({peso, v});
}

void Grafo::leGrafo(std::ifstream &in) {
    // le dimensoes
    in >> numVertices >> numArestas;

    // Redimensionamento para n + 1 pois vertices estao indexados em 1
    arestas.resize(numVertices + 1);

    for (int i = 0; i < numArestas; i++) {
        TipoV v, u;
        int peso;
        in >> v >> u >> peso;
        adicionaAresta(v, u, peso);
    }
}

bool Grafo::validaVertice(TipoV v) {
    if ((v > numVertices) || (v <= 0)) { // indexados em 1
        return false;
    }
    return true;
}

bool Grafo::existeAresta(TipoV v, TipoV u) {
    bool existe = false;
    if (!validaVertice(v) || !validaVertice(u)) {
        return existe;
    }
    for (auto it : arestas[v]) {
        if (it.second == u) {
            existe = true;
        }
    }
    return existe;
}

void Grafo::Imprime() {
    for (int i = 1; i <= numVertices; i++) {
        for (auto it : arestas[i]) {
            std::cout << i << " "
                      << it.second << " "
                      << it.first 
                      << std::endl;
        }
    }   
}

// Vertices armazenados na ordem peso, vertice para Dijkstra
using P_E = std::pair<int, TipoV>;
int Grafo::CaminhoMin(TipoV source, TipoV u) {
    std::vector<TipoV> pai;
    std::vector<bool> visitado;
    // Min-Heap que coloca a aresta com menor distancia estimada no topo:
    std::priority_queue<P_E, std::vector<P_E>, std::greater<P_E>> dist;

    for (int i = 0; i < numVertices; i++) {
        pai[i] = NULL;
        visitado[i] = false;
        dist.push({INFINITY, i});
    }
    // Vertice de origem:
    dist.push({0, source});

    while (!visitado[u]) {
        int peso_atual = dist.top().first;
        TipoV v = dist.top().second;
        visitado[v] = true;

        for (auto it : arestas[v]) {
            if ((peso_atual + it.first) < ) {
                
            }
        }
    }
}