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

#include <vector> // Para representacao do grafo

typedef struct vertice { // Para representar regioes
    int dist;
    int pai;
    char cor; // b = branco, c = cinza, p = preto
};

using TipoV = int;

class Grafo {
public:
    Grafo(int n);
    Grafo(const Grafo& outro);
    Grafo& operator=(const Grafo& outro);
    ~Grafo();

    void leGrafo(std::ifstream &in);

    void adicionaAresta(TipoV v, TipoV u);
    void removeAresta(TipoV v, TipoV u);
    std::vector<TipoV> getAdj(TipoV v);
    
    int DistanciaMin(TipoV v, TipoV u);

    bool grafoVazio();
    void Imprime() const;

private:
    int numVertices; // numero de regioes 
    int numArestas; // numero de ruas 

    // lista de adjacencia (conexoes entre regioes)
    std::vector<std::vector<TipoV>> arestas; 

    // Metodos internos
    bool existeAresta(TipoV v, TipoV u) const;
    bool validaVertice(TipoV v) const;

    std::vector<TipoV> * getRota(TipoV v, TipoV u, vertice * vertices);
};

#endif