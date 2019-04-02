#ifndef HEAP_H
#define HEAP_H

/**
 * Nodos para o heap binário.
 */
template <typename T>
struct ElementoHeap {
    int chave;
    T dado;
};

/**
 * Estrutura de heap binário. 
 * Pode ser utilizado para mínimo ou máximo. As funções desta biblioteca tratam o heap máximo.
 */
template <typename T, int MAX>
struct HeapBinario {
    ElementoHeap<T> elementos[MAX];
    unsigned int quantidade;
};

/**
 * @brief inicializarHeap Inicializa o heap binário passado por parâmetro, determinando
 * sua quantidade inicial como 0 elementos.
 * @param heap Heap binário passado por referência.
 * @returns void Alteração é feita por referência.
 */
template <typename T, int MAX>
void inicializarHeap (HeapBinario<T, MAX> &heap) {
    heap.quantidade = 0;
}

/**
 * @brief trocar Realiza a troca de valores de duas variáveis quaisquer, desde que sejam
 * do mesmo tipo.
 * @param esquerda Primeira variável para ter seu dado trocado.
 * @param direita Segunda variável para ter seu dado trocado.
 * @returns void Realiza a troca dos valores por referência.
 */
template <typename T>
void trocar (T &esquerda, T &direita) {
    T aux = esquerda;
    esquerda = direita;
    direita = aux;
}

/**
 * @brief ascendente Calcula o nodo ascendente de um índice dentro de um heap, através 
 * de seu índice.
 * @param indice Índice para calcular o ascendente.
 * @returns unsigned int Índice do nodo pai do índice passado por parâmetro.
 */
unsigned int ascendente (unsigned int indice) {
    return (indice - 1) / 2;
}

/**
 * @brief descendenteEsquerdo Calcula o nodo descendente esquerdo de um índice num heap 
 * binário.
 * @param indice Índice para calcular o descendente esquerdo.
 * @returns unsigned int Índice do descendente imediato esquerdo.
 */
unsigned int descendenteEsquerdo (unsigned int indice) {
    return (2 * indice + 1);
}

/**
 * @brief descendenteDireito Calcula o nodo descendente direito de um índice num heap 
 * binário.
 * @param indice Índice para calcular o descendente direito.
 * @returns unsigned int Índice do descendente imediato direito.
 */
unsigned int descendenteDireito (unsigned int indice) {
    return (2 * indice + 2);
}


/**
 * @brief subirEmHeap Sobe o elemento no índice determinado enquanto este não se tornou a raiz
 * e for maior que seus ascendentes.
 * @param heap Heap binário alvo.
 * @param indice Índice para balancear para cima.
 * @returns void Alterações são feitas por referência.
 */
template <typename T, int MAX>
void subirEmHeap (HeapBinario<T, MAX> &heap, unsigned int indice) {
    if (heap.quantidade > 0 && indice < heap.quantidade) {
        while (indice > 0 && heap.elementos[indice].chave > heap.elementos[ascendente (indice)].chave) {
            trocar (heap.elementos[indice], heap.elementos[ascendente (indice)]);
            indice = ascendente (indice);
        }
    }
}

/**
 * @brief descerEmHeap Desce o elemento no índice determinado enquanto este não se tornou uma
 * folha e é menor que seus descendentes.
 * @param heap Heap binário alvo.
 * @param indice Índice para balancear para baixo.
 * @returns void Alterações são feitas por referência.
 */
template <typename T, int MAX>
void descerEmHeap (HeapBinario<T, MAX> &heap, unsigned int indice) {
    if (heap.quantidade > 0 && indice < heap.quantidade) {
        while (descendenteEsquerdo (indice) < heap.quantidade
            && (heap.elementos[indice].chave < heap.elementos[descendenteEsquerdo (indice)].chave
            || heap.elementos[indice].chave < heap.elementos[descendenteDireito (indice)].chave))
            {
                if (heap.elementos[descendenteEsquerdo (indice)].chave > heap.elementos[descendenteDireito (indice)].chave) {
                    trocar (heap.elementos[indice], heap.elementos[descendenteEsquerdo (indice)]);
                    indice = descendenteEsquerdo (indice);
                } else {
                    trocar (heap.elementos[indice], heap.elementos[descendenteDireito (indice)]);
                    indice = descendenteDireito (indice);
                }
            }   
    }
}

/**
 * @brief inserirEmHeap Insere um dado e uma chave no último índice disponível num 
 * heap binário máximo e depois realiza seu balanceamento. A função sobe o elemento 
 * recém inserido enquanto não for a raiz e for maior que seus ascendentes, conforme 
 * sugerido por Adam Drozdek.
 * @param heap Heap binário para inserir a chave e o dado.
 * @param chave Chave para ser inserida.
 * @param dado Dado para inserção.
 * @returns bool True se inseriu. False se não inseriu (heap atingiu a quantidade máxima).
 */
template <typename T, int MAX>
bool inserirEmHeap (HeapBinario<T, MAX> &heap, int chave, T dado) {
    if (heap.quantidade < MAX) {
        heap.elementos[heap.quantidade] = { chave, dado };
        heap.quantidade++;
        subirEmHeap (heap, heap.quantidade - 1); // balancear heap
        return true;
    }
    return false; // heap cheio
}

/**
 * @brief removerEmHeap Remove a raiz do heap e posiciona o último elemento em seu lugar,
 * em seguida, balanceia o heap para que obedeça suas duas características.
 * Implementado de acordo com o pseudo-código de Drozdek, o qual sugere substituir a
 * raiz com o último elemento do heap e o abaixar no vetor enquanto não for uma folha
 * (não há mais elementos na direita) e for menor que seus descendentes (heap máximo).
 * @param heap Heap binário (template de tipo e tamanho) alvo para exclusão de raiz.
 * @returns bool True se removeu (havia pelo menos um elemento no heap: a raiz), falso se
 * não foi possível realizar remoção (heap vazio).
 */
template <typename T, int MAX>
bool removerEmHeap (HeapBinario<T, MAX> &heap) {
    if (heap.quantidade > 0) {
        heap.elementos[0] = heap.elementos[heap.quantidade - 1];
        heap.quantidade--;
        descerEmHeap (heap, 0); // balancear heap
        return true;
    }
    return false; // heap vazio
}

/**
 * @brief atualizarChave Atualiza a chave de um elemento no heap binário através de seu índice e
 * em seguida, realiza o balanceamento.
 * @param heap Heap binário para alteração.
 * @param indice Índice de troca de chave.
 * @param novaChave Chave a ser atualizada no índice desejado.
 * @returns bool True se trocou e false caso contrário (índice inválido).
 */
template <typename T, int MAX>
bool atualizarChave (HeapBinario<T, MAX> &heap, unsigned int indice, int novaChave) {
    if (indice < heap.quantidade) {
        int chaveAntiga = heap.elementos[indice].chave;
        heap.elementos[indice].chave = novaChave;
        if (novaChave > chaveAntiga) {
            subirEmHeap (heap, indice); // chave é maior, balancear para cima
        }
        else {
            descerEmHeap (heap, indice); // chave é menor, balancear para baixo
        }
        return true;
    }
    return false; // heap vazio.
}

/**
 * @brief atualizarChavePorDado Atualiza uma chave através da busca pelo seu dado num heap
 * binário.
 * @param heap Heap para realizar a modificação.
 * @param dado Dado para busca.
 * @param novaChave Chave a ser atualizada após encontro do dado.
 * @returns bool True se realizou modificação e false caso contrário (heap vazio ou dado não encontrado).
 */
template <typename T, int MAX>
bool atualizarChavePorDado (HeapBinario<T, MAX> &heap, T dado, int novaChave) {
    if (heap.quantidade > 0) {
        for (unsigned int i = 0; i < heap.quantidade; i++) {
            if (heap.elementos[i].dado == dado) {
                return atualizarChave (heap, i, novaChave);
            }
        }
        return false; // dado não encontrado
    }
    return false; // heap vazio
}

#endif // HEAP_H