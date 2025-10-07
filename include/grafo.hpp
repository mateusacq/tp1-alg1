#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <string>
#include <fstream> // Para Grafo::leGrafo()
#include <iostream>

// Para representacao do grafo
#include <vector> 
#include <utility> // Para std::pair

#include "heap.hpp" // Para Dijkstra e caminhos minimos

using TipoV = int;

struct Aresta {
    int u, v, peso, indice;
};

class Grafo {
public:
    Grafo();
    Grafo(int n, int m);

    void leGrafo();
    void adicionaAresta(TipoV v, TipoV u, int peso, int indice);
    Aresta removeAresta(int indice);

    // Algoritmo de Dijkstra para caminho minimo entre 2 vertices
    int CaminhoMin(TipoV origem, TipoV destino);
    // Funcao para parte 2
    std::vector<int> Parte2();
    // Funcao para parte 3
    std::vector<int> Parte3(std::vector<int> arestas_otimas, int distancia_minima);

    void Imprime();

    // Getter do numero de vertices
    int getN();

private:
    int numVertices;
    int numArestas;

    // Representacoes do grafo
    std::vector<std::vector<std::pair<int, int>>> adjacencia; // adjacencia[u] = {v, peso}
    std::vector<Aresta> arestas; // Todas as ruas (arestas)

    // Metodos internos para seguranca
    bool validaVertice(TipoV v);
    bool existeAresta(TipoV v, TipoV u);
};

#endif