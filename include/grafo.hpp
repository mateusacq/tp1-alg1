//---------------------------------------------------------------------
// Arquivo      : grafo.hpp
// Conteudo     : header da estrutura de dados grafo
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 25-09-2025 - arquivo criado
//---------------------------------------------------------------------

#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <string>
#include <fstream> // Para Grafo::leGrafo()
#include <iostream>

// Para representacao do grafo
#include <vector> 
#include <utility> // Para std::pair
#include <queue> // Para fila de prioridade dos vertices do grafo
#include <functional> // Para std::greater 

using TipoV = int;

struct Aresta {
    int u, v, peso, indice;
};

class Grafo {
public:
    Grafo();
    Grafo(int n, int m);

    void leGrafo(std::ifstream &in);
    void adicionaAresta(TipoV v, TipoV u, int peso, int indice);

    // Algoritmo de Dijkstra para caminho minimo entre 2 vertices
    int CaminhoMin(TipoV v, TipoV u);
    // Funcao para parte 2
    std::vector<int> Parte2();
    // Funcao para parte 3
    std::vector<int> Parte3(std::vector<int> dist_min, int caminho_min);

    void Imprime();

    int getN();

private:
    int numVertices;
    int numArestas;
    std::vector<std::vector<std::pair<int, int>>> adj; // adj[u] = {v, peso}
    std::vector<Aresta> arestas; // Todas as ruas (arestas)

    // metodos internos para seguranca
    bool validaVertice(TipoV v);
    bool existeAresta(TipoV v, TipoV u);
};

#endif