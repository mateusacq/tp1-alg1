#include "heap.hpp"

#define MAX_TAM 1000

Heap::Heap() {
    tamanho = 0;
    capacidade = MAX_TAM;
    data = new TipoH[MAX_TAM];
}

Heap::Heap(int maxsize) {
    tamanho = 0;
    capacidade = maxsize;
    data = new TipoH[maxsize];
}

Heap::~Heap() {
    delete[] data;
}

int Heap::GetAncestral(int posicao) const {
    return (posicao - 1) / 2;
}

int Heap::GetSucessorEsq(int posicao) const {
    return 2*posicao + 1;
}

int Heap::GetSucessorDir(int posicao) const {
    return 2*posicao + 2;
}

// Garante a propriedade do MinHeap SUBINDO o elemento,
// que esta partindo de "posicao"
void Heap::HeapifyPorBaixo(int posicao) {
    int atual = posicao;

    while ( atual > 0 && data[atual] < data[GetAncestral(atual)] ) {
        int ancestral = GetAncestral(atual);

        TipoH aux = data[atual];
        data[atual] = data[ancestral];
        data[ancestral] = aux;

        atual = ancestral;
    }
}

// Garante a propriedade do MinHeap DESCENDO o elemento,
// que esta partindo de "posicao"
void Heap::HeapifyPorCima(int posicao) {
    int atual = posicao;

    while (true) {
        int esq = GetSucessorEsq(atual);
        int dir = GetSucessorDir(atual);
        int menor = atual;

        if ( (esq < tamanho) && (data[esq] < data[menor]) ) 
            menor = esq;
        if ( (dir < tamanho) && (data[dir] < data[menor]) ) 
            menor = dir;
        
        if (menor != atual) {
            TipoH aux = data[atual];
            data[atual] = data[menor];
            data[menor] = aux;

            atual = menor;
        } else {
            break;
        }
    }
}

void Heap::push(TipoH x) {
    if (tamanho >= capacidade) {
        std::cerr << "Erro: Heap cheio! Não é possível inserir mais elementos." << std::endl;
        return;
    }

    data[tamanho] = x;
    HeapifyPorBaixo(tamanho);
    tamanho++;
}

TipoH Heap::pop() {
    if (empty()) {
        std::cerr << "Erro: Heap vazio!" << std::endl;
        TipoH par_erro = {-1 ,-1};
        return par_erro;
    }

    TipoH raiz_removida = data[0];

    tamanho--;

    if (tamanho > 0) {
        data[0] = data[tamanho];
        HeapifyPorCima(0);
    }

    return raiz_removida;
}

bool Heap::empty() const {
    return tamanho == 0;
}

TipoH Heap::top() const {
    return data[0];
}