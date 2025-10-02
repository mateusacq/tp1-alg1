#include <iostream>
#include <fstream>
#include <string>

#include "grafo.hpp"

int main(int argc, char* argv[]) {
    // Le arquivo de entrada
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <nome_do_arquivo>\n";
        return 1;    
    }
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "ERRO: falha ao abrir o arquivo." << std::endl;
        return 1;
    }

    // Ler o grafo
    Grafo g;
    g.leGrafo(in);

    // Dijkstra de 1 ate N (praca ao parque)
    int distancia_minima = g.CaminhoMin(1, g.getN());
    std::cout << "Parte 1: " << distancia_minima << std::endl;

    std::cout << "Parte 2: ";
    std::vector<int> ruas_candidatas = g.Parte2();
    for (auto it : ruas_candidatas) {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    std::cout << "Parte 3: ";

    return 0;
}