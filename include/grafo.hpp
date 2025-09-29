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

using TipoV = int;

class Grafo {
public:
    Grafo();
    Grafo(int n, int m);

private:
    int numArestas;
    int numVertices;
    std::vector<std::vector<TipoV>> arestas;
};

#endif