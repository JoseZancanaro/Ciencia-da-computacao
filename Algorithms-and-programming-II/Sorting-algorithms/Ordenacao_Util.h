#pragma once
#ifndef Ordenacao_Util.h

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>    
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <vector>

//TAM, define o tamanho das posições dos arrays.
#define TAM 50000

using namespace std;

void mostrarArray(int array[]);
void sorteia(int array[]);

void bubble_sort(int array[], int tamanhoVetor);
void bubble_sort_recursivo(int array[], int tamanhoVetor);

void insertion_sort(int array[], int tamanhoVetor);
void insertion_sort_recursivo(int array[], int tamanhoVetor);

void troca(int* a, int* b);
int fracao(int array[], int low, int high);
void quick_sort(int array[], int low, int high);

void merge_sort(int array[], int inicio, int fim);
void merge(int array[], int inicio, int metade, int fim);

#endif 
