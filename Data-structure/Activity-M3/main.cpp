#include <iostream>

#include "heap.hpp"

const int Heap_Size = 32;

int main () {
    HeapBinario<int, Heap_Size> heap;
    inicializarHeap (heap);
    
    for (int i = 0; i < Heap_Size; i++)
        inserirEmHeap (heap, i, i * i);

    removerEmHeap (heap);

    return 0;
}