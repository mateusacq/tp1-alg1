#include "grafo.hpp"

Grafo::Grafo() 
    : numVertices(0), numArestas(0), 
    adj(1), arestas(1) {}

Grafo::Grafo(int n, int m) 
    : numVertices(n), numArestas(m), 
    adj(n + 1), arestas(m) {}

// i = indice da aresta, util para partes 2 e 3
void Grafo::adicionaAresta(TipoV v, TipoV u, int peso, int i) {
    Aresta a, b;
    a.v = v; a.u = u; 
    a.peso = peso; a.indice = i;
    
    arestas.push_back(a);
    adj[v].push_back({u, peso});
    
    b.v = u; b.u = v; // Bidirecionado
    b.peso = peso; b.indice = i;

    arestas.push_back(b);
    adj[u].push_back({v, peso});
}

void Grafo::leGrafo(std::ifstream &in) {
    // le dimensoes
    in >> numVertices >> numArestas;

    // Redimensionamento para n + 1 pois vertices estao indexados em 1
    adj.resize(numVertices + 1);

    for (int i = 1; i <= numArestas; i++) {
        TipoV v, u;
        int peso;
        in >> v >> u >> peso;
        adicionaAresta(v, u, peso, i);
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
    for (auto it : adj[v]) {
        if (it.second == u) {
            existe = true;
        }
    }
    return existe;
}

void Grafo::Imprime() {
    std::cout << "arestas1 de g:" << std::endl;
    for (int i = 1; i <= numVertices; i++) {
        for (auto it : adj[i]) {
            std::cout << i << " "
                      << it.first << " "
                      << it.second 
                      << std::endl;
        }
    }   
}

// Vertices armazenados na ordem {peso, {vertice, indice_aresta}} para Dijkstra
using P_E = std::pair<int, TipoV>;
int Grafo::CaminhoMin(TipoV source, TipoV u) {
    // Min-Heap que coloca a aresta com menor distancia estimada no topo:
    std::priority_queue<P_E, std::vector<P_E>, std::greater<P_E>> minHeap;

    // Inicializa vetor de distancias estimadas
    int INFINITY = 2147483647; // 2^31 - 1
    std::vector<int> dist(numVertices + 1);
    for (int i = 1; i <= numVertices; i++) {
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

        for (auto const& it : adj[v]) {
            // as arestasa[v] armazena {adjacente, peso_aresta}
            TipoV u_vizinho = it.first;
            int peso_aresta = it.second;

            if (peso_atual + peso_aresta < dist[u_vizinho]) {
                minHeap.push({peso_atual + peso_aresta, u_vizinho});
                dist[u_vizinho] = peso_atual + peso_aresta; // Atualiza estimativa
            }
        }
    }

    // Se "u" estiver em uma componente conexa do grafo diferente
    // da de "source", este return retorna uma dist == INFINITY,
    // que ha de ser tratada no codigo.
    return dist[u];
}

std::vector<int> Grafo::Parte2() {
    int N = numVertices;
    std::vector<int> dist_de_1(N + 1);
    std::vector<int> dist_ate_N(N + 1);

    // Salva o caminho minimo da origem aos vertices intermediarios e deles ao destino
    for (int i = 1; i <= N; i++) {
        dist_de_1[i] = CaminhoMin(1, i);
        dist_ate_N[i] = CaminhoMin(i, N);
    }
    
    int d = dist_de_1[N];
    std::vector<int> dist_min;
    // Verifica quais fazem parte de algum caminho minimo entre 1 e N,
    // usando a propriedade dos caminhos intermediarios
    for (auto it : arestas) {
        if ((dist_de_1[it.u] + it.peso + dist_ate_N[it.v] == d) ||
            (dist_de_1[it.v] + it.peso + dist_ate_N[it.u] == d)) {
                dist_min.push_back(it.indice);
            }
    }

    // Elimina duplicatas
    int s = dist_min.size() - 1;
    for (int i = s; i > 0; i--) {
        if (dist_min[i] == dist_min[i - 1]) {
            dist_min.erase(dist_min.begin() + i);
        }
    }

    return dist_min;
}

