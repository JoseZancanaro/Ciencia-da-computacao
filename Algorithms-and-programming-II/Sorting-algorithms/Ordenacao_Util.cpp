#include "stdafx.h"
#include "Ordenacao_Util.h"

//Funções visual e sorteio.
void mostrarArray(int array[])
{
	for (int i = 0; i < TAM; i++) {
		cout << array[i] << (i == TAM - 1 ? "" : " - ");
	}
	cout << endl;
}
void sorteia(int array[])
{
	srand(time(NULL));

	for (int i = 0; i < TAM; i++) {
		array[i] = rand() % 1000; //Utilizamos sorteio de no máximo 999.
	}
}

//Bubble Sort
void bubble_sort(int array[], int tamanhoVetor)
{
	int auxiliar = 0;

	for (int x = 0; x < tamanhoVetor; x++) {
		for (int indice = 0; indice < tamanhoVetor - x - 1; indice++) {
			if (array[indice] > array[indice + 1]) {

				auxiliar = array[indice];
				array[indice] = array[indice + 1];
				array[indice + 1] = auxiliar;
			}
		}
	}
}
void bubble_sort_recursivo(int array[], int tamanhoVetor)
{
	if (tamanhoVetor == 1)
		return;

	for (int i = 0; i < tamanhoVetor - 1; i++)
		if (array[i] > array[i + 1])
			swap(array[i], array[i + 1]);

	bubble_sort_recursivo(array, tamanhoVetor - 1);
}

//Insertion Sort
void insertion_sort(int array[], int tamanhoVetor)
{
	int posicao, key, posicaoAnterior;
	for (posicao = 1; posicao < tamanhoVetor; posicao++)
	{
		key = array[posicao];
		posicaoAnterior = posicao - 1;

		while (posicaoAnterior >= 0 && array[posicaoAnterior] > key)
		{
			array[posicaoAnterior + 1] = array[posicaoAnterior];
			posicaoAnterior--;
		}
		array[posicaoAnterior + 1] = key;
	}
}
void insertion_sort_recursivo(int array[], int tamanhoVetor)
{
	if (tamanhoVetor <= 1)
		return;

	insertion_sort_recursivo(array, tamanhoVetor - 1);

	int ultimo = array[tamanhoVetor - 1];
	int aux = tamanhoVetor - 2;

	while (aux >= 0 && array[aux] > ultimo)
	{
		array[aux + 1] = array[aux];
		aux--;
	}
	array[aux + 1] = ultimo;
}

//Quick Sort
void troca(int* a, int* b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}
int fracao(int array[], int low, int high)
{
	int pivot = array[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (array[j] <= pivot)
		{
			i++;
			troca(&array[i], &array[j]);
		}
	}
	troca(&array[i + 1], &array[high]);
	return (i + 1);
}
void quick_sort(int array[], int low, int high)
{

	if (low < high)
	{
		int meio = fracao(array, low, high);

		quick_sort(array, low, meio - 1);
		quick_sort(array, meio + 1, high);
	}
}

//Merge Sort
void merge(int array[], int inicio, int metade, int fim)
{
	int i, j, k;
	int n1 = metade - inicio + 1;
	int n2 = fim - metade;
	vector<int> L;
	vector<int> R;
	for (i = 0; i < n1; i++)
		L.push_back(array[inicio + i]);
	for (j = 0; j < n2; j++)
		R.push_back(array[metade + 1 + j]);
	i = 0;
	j = 0;
	k = inicio;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			array[k] = L[i];
			i++;
		}
		else
		{
			array[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		array[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		array[k] = R[j];
		j++;
		k++;
	}
}
void merge_sort(int array[], int inicio, int fim)
{
	if (inicio < fim)
	{
		int metade = inicio + (fim - inicio) / 2;
		merge_sort(array, inicio, metade);
		merge_sort(array, metade + 1, fim);
		merge(array, inicio, metade, fim);
	}
}