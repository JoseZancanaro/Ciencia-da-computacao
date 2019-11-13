//Testes foram feitos em Release x86.

#include "stdafx.h"
#include "Ordenacao_Util.h"

int main()
{
	setlocale(LC_ALL, "Portuguese");
	string controle = "Continuar";
	while (controle != "Sair") {
		system("cls");

		cout << "Alunos: José Carlos Zancanaro e Lucas Cardone." << endl
			<< "Algoritmos de Ordenação." << endl << endl;

		//Array que é utilizado.
		int array[TAM];

		//Função que sorteia os números para o array.
		sorteia(array);

		cout << "Array criado e sorteado." << endl 
			<< "Deseja ver o array inicial? " << endl
			<< " Sim ou Não? ";
		string opcao = "";
		cin >> opcao;

		if (opcao == "Sim") {
			//Função que mostra o array.
			mostrarArray(array); cout << endl;
			system("pause");
		}

		int escolha = 0;
		while (escolha < 1 || escolha > 6) {
			system("cls");
			cout << "Selecione o método de ordenação:" << endl
				<< "1 - Bubble Sort" << endl
				<< "2 - Bubble Sort Recursivo" << endl
				<< "3 - Insertion Sort" << endl
				<< "4 - Insertion Sort Recursivo" << endl
				<< "5 - Quick Sort" << endl
				<< "6 - Merge Sort" << endl << endl
				<< "Escolha: ";
			cin >> escolha;
		}
		cout << endl;
		clock_t inicio = clock();
		switch (escolha)
		{
		case 1:
			bubble_sort(array, TAM);
			break;
		case 2:
			bubble_sort_recursivo(array, TAM);
			break;
		case 3:
			insertion_sort(array, TAM);
			break;
		case 4:
			insertion_sort_recursivo(array, TAM);
			break;
		case 5:
			quick_sort(array, 0, TAM - 1);
			break;
		case 6:
			merge_sort(array, 0, TAM - 1);
			break;
		}

		clock_t final = clock();
		cout << "---------------------------------";
		long double resultado = double(final - inicio) / CLOCKS_PER_SEC;
		cout << endl << "Tempo decorrido para ordenação:" << endl << resultado
			 << " segundos " << endl << "---------------------------------" << endl << endl;
		
		string opcao1 = "";
		cout << "Deseja ver o array ordenado?" << endl
			<< "Sim ou Não? ";
		cin >> opcao1;

		if (opcao1 == "Sim") {
			cout << endl << endl;
			mostrarArray(array); cout << endl;
		}
		cout << endl << endl << "Digite Sair para fechar o programa ou digite qualquer outra coisa para repetir. ";
		cin >> controle;
	}
	return 0;
}