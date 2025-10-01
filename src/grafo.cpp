#include "grafo.hpp"

Grafo::Grafo() 
    : numVertices(0), numArestas(0), arestas(1) {}

Grafo::Grafo(int n, int m) 
    : numVertices(n), numArestas(m), arestas(n + 1) {}

void Grafo::adicionaAresta(TipoV v, TipoV u, int peso) {
    arestas[v].push_back({u, peso});
    arestas[u].push_back({v, peso});
}

void Grafo::leGrafo(std::ifstream &in) {
    // le dimensoes
    in >> numVertices >> numArestas;

    // Redimensionamento para n + 1 pois vertices estao indexados em 1
    arestas.resize(numVertices + 1);

    for (int i = 1; i <= numArestas; i++) {
        TipoV v, u;
        int peso;
        in >> v >> u >> peso;
        adicionaAresta(v, u, peso);
    }
}

int Grafo::getN() {
    return numVertices;
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
                      << it.first << " "
                      << it.second 
                      << std::endl;
        }
    }   
}

// Vertices armazenados na ordem peso, vertice para Dijkstra
using P_E = std::pair<int, TipoV>;
int Grafo::CaminhoMin(TipoV source, TipoV u) {
    // Min-Heap que coloca a aresta com menor distancia estimada no topo:
    std::priority_queue<P_E, std::vector<P_E>, std::greater<P_E>> minHeap;

    // Inicializa vetores
    int INFINITY = 2147483647; // 2^31 - 1
    int VERTICE_INVALIDO = -1;
    std::vector<TipoV> pai(numVertices + 1);
    std::vector<int> dist(numVertices + 1);
    for (int i = 1; i <= numVertices; i++) {
        pai[i] = VERTICE_INVALIDO;
        dist[i] = INFINITY;
    }

    // Vertice de origem:
    minHeap.push({0, source});
    dist[source] = 0;

    while (!minHeap.empty()) {
        // Salva dados da aresta de menor distancia conhecida:
        int peso_atual = minHeap.top().first;
        TipoV v = minHeap.top().second;
        
        minHeap.pop();
        // Ignora copiasa de v com peso obsoleto no minHeap
        if (peso_atual > dist[v]) {
            continue;
        }

        // Encontramos a distancia ate u quando vale:
        if (v == u) {
            return dist[u];
        }

        for (auto const& it : arestas[v]) {
            // as arestasa[v] armazena {adjacente, peso_aresta}
            TipoV u_vizinho = it.first;
            int peso_aresta = it.second;

            if (peso_atual + peso_aresta < dist[u_vizinho]) {
                minHeap.push({peso_atual + peso_aresta, u_vizinho});
                dist[u_vizinho] = peso_atual + peso_aresta; // Atualiza estimativa
                pai[u_vizinho] = v; // Salva vertice previo
            }
        }
    }

    // Se "u" estiver em uma componente conexa do grafo diferente
    // da de "source", este return retorna uma dist == INFINITY,
    // que ha de ser tratada no codigo.
    return dist[u];
}