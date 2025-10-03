#include "grafo.hpp"

Grafo::Grafo() 
    : numVertices(0), numArestas(0), 
    adjacencia(1), arestas(1) {}

Grafo::Grafo(int n, int m) 
    : numVertices(n), numArestas(m), 
    adjacencia(n + 1), arestas(m) {}

// i = indice da aresta, util para partes 2 e 3
void Grafo::adicionaAresta(TipoV v, TipoV u, int peso, int i) {
    Aresta a, b;
    a.v = v; a.u = u; 
    a.peso = peso; a.indice = i;
    
    arestas.push_back(a);
    adjacencia[v].push_back({u, peso});
    
    // Grafo nao direcionado, portanto, arestas nos dois sentidos:
    b.v = u; b.u = v; 
    b.peso = peso; b.indice = i;

    arestas.push_back(b);
    adjacencia[u].push_back({v, peso});
}

void Grafo::leGrafo(std::ifstream &in) {
    // Le dimensoes
    in >> numVertices >> numArestas;

    // Redimensionamento para n + 1 pois vertices estao indexados em 1
    adjacencia.resize(numVertices + 1);

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
    for (auto it : adjacencia[v]) {
        if (it.second == u) {
            existe = true;
        }
    }
    return existe;
}

void Grafo::Imprime() {
    std::cout << "arestas1 de g:" << std::endl;
    for (int i = 1; i <= numVertices; i++) {
        for (auto it : adjacencia[i]) {
            std::cout << i << " "
                      << it.first << " "
                      << it.second 
                      << std::endl;
        }
    }   
}

// Vertices armazenados na ordem {peso, vertice} para Dijkstra
int Grafo::CaminhoMin(TipoV origem, TipoV destino) {
    // Fila de prioridade com arestas ordenadas em ordem de peso crescente
    Heap minHeap;

    // Inicializa vetor de distancias estimadas
    int INFINITY = 2147483647; // 2^31 - 1 = INT_MAX
    std::vector<int> dist(numVertices + 1);
    for (int i = 1; i <= numVertices; i++) {
        dist[i] = INFINITY;
    }

    // Vertice de origem:
    minHeap.push({0, origem});
    dist[origem] = 0;

    while (!minHeap.empty()) {
        // Analisa vertice com menor distancia estimada:
        int peso_atual = minHeap.top().first;
        TipoV v_atual = minHeap.top().second;
        
        minHeap.pop();
        // Ignora copias de v com peso obsoleto no minHeap
        if (peso_atual > dist[v_atual]) {
            continue;
        }

        // Verifica se destino foi alcancado
        if (v_atual == destino) {
            return dist[destino];
        }

        for (auto const& it : adjacencia[v_atual]) {
            // arestas[v] armazena {v_adjacente, peso_aresta}
            TipoV vizinho = it.first;
            int peso_aresta = it.second;

            if (peso_atual + peso_aresta < dist[vizinho]) {
                minHeap.push({peso_atual + peso_aresta, vizinho});
                dist[vizinho] = peso_atual + peso_aresta; // Atualiza estimativa
            }
        }
    }

    // Se "destino" estiver em uma componente conexa do grafo diferente
    // da de "source", este return retorna uma dist == INFINITY,
    // que ha de ser tratada no codigo.
    return dist[destino];
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
    std::vector<int> arestas_otimas;
    // Verifica quais fazem parte de algum caminho minimo entre 1 e N,
    // usando a propriedade dos caminhos intermediarios
    for (auto it : arestas) {
        if ((dist_de_1[it.u] + it.peso + dist_ate_N[it.v] == d) ||
            (dist_de_1[it.v] + it.peso + dist_ate_N[it.u] == d)) {
                arestas_otimas.push_back(it.indice);
            }
    }

    // Elimina duplicatas
    int s = arestas_otimas.size() - 1;
    for (int i = s; i > 0; i--) {
        if (arestas_otimas[i] == arestas_otimas[i - 1]) {
            arestas_otimas.erase(arestas_otimas.begin() + i);
        }
    }

    return arestas_otimas;
}

Aresta Grafo::removeAresta(int _indice) {
    int u, v;
    int contador_remocoes = 0;
    Aresta a_removida;

    // Atualiza o vetor de arestas
    for (auto it = arestas.begin(); it != arestas.end(); ) {
        if (it->indice == _indice) {
            u = it->u; v = it->v;
            a_removida = *it;
            it = arestas.erase(it); // Atualiza o iterador
            contador_remocoes++;

        } else { it++; }
    }
    
    // Seguranca no contador de arestas
    if (contador_remocoes == 0) {
        std::cerr << "ERRO: nenhuma aresta encontrada para o indice especificado " 
                  << _indice 
                  << std::endl;
    } else {
        // Atualiza adjacencias nas duas direcoes
        for (auto it = adjacencia[v].begin(); it != adjacencia[v].end(); ) {
            if (it->first == u) {
                it = adjacencia[v].erase(it);
                break;
            } else { it++; }
        }
        for (auto it = adjacencia[u].begin(); it != adjacencia[u].end(); ) {
            if (it->first == v) {
                it = adjacencia[u].erase(it);
                break;
            } else { it++; }
        }
        numArestas -= contador_remocoes;
    }

    return a_removida; // Se nenhuma for removida, os campos estarao zerados
}

std::vector<int> Grafo::Parte3(std::vector<int> arestas_otimas, int distancia_minima) {
    std::vector<int> arestas_criticas;

    // Verifica quais arestas obtidas na parte2 
    // reduzem o caminho de 1 a N, uma a uma
    for (int atual : arestas_otimas) {
        Aresta a = removeAresta(atual);
        if (distancia_minima != CaminhoMin(1, numVertices)) {
            arestas_criticas.push_back(atual);
        }
        adicionaAresta(a.v, a.u, a.peso, a.indice);
    }

    // Nao foram encontradas ruas criticas
    if (arestas_criticas.empty()) {
        arestas_criticas.push_back(-1);
    }

    return arestas_criticas;
}