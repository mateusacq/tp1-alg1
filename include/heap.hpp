/* ### MINHEAP QUE SERVIRA DE FILA DE PRIORIDADE PARA DIJKSTRA ### */

#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <utility> // para std::pair

// Representacao de vertice e aresta
using TipoV = int;
using TipoH = std::pair<TipoV, int>;

class Heap { 

    public:
        Heap();
        Heap(int maxsize);
        ~Heap();

        void push(TipoH x); // Adiciona
        TipoH pop(); // Remove

        // Retorna true caso o heap esteja vazio, false caso contrário.
        bool empty() const;

        // Getter da raiz
        TipoH top() const;

    private:
    // Metodos internos
        int GetAncestral(int posicao) const;
        int GetSucessorEsq(int posicao) const;
        int GetSucessorDir(int posicao) const;

        int tamanho;
        int capacidade; // Para evitar estouro de tamanho do heap
        TipoH * data;

        /* Funções necessárias para implementar o Heapify recursivo
         * Você pode apagar elas caso decida implementar o Heapify iterativo
         */
        void HeapifyPorBaixo(int posicao);
        void HeapifyPorCima(int posicao);
};

#endif