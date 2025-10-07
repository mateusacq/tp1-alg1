#include <iostream>
#include <fstream>
#include <string>

#include "grafo.hpp"

int main() {
    // Ler o grafo
    Grafo g;
    g.leGrafo();

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
    std::vector<int> ruas_criticas = g.Parte3(ruas_candidatas, distancia_minima);
    for (auto it : ruas_criticas) {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    return 0;
}