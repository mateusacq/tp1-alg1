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
    g.Imprime();

    // Dijkstra de 1 ate N (praca ao parque)


    return 0;
}