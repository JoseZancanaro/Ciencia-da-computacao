#include <iostream>
#include "FilaGenerica.hpp"

using namespace std;

/* Exercício em aula
 * Simulação de supermercado
 * - n filas (usuário ou constante)
 * - 10 clientes chegam por unidade de tempo (10 mil u.t)
 * - 2 dos clientes levam 1 u.t para serem atendidos
 * - 3 dos clientes levam 2 u.t para serem atendidos
 * - 5 dos clientes levam 3 u.t para serem atendidos
 *
 * -> Crie um programa que simule as filas e os atendimentos  .
 * Ao final, responda a média de clientes que esperam por fila. ()
 */

// Cliente e unidade de tempo
const int unidadeTamanho = 10000;
struct Cliente {
    int tempo;
};

// Função que define o tempo de cada cliente,  {1,1,2,2,2,3,3,3,3,3}
void chegadaDeClientes(Fila<Cliente> caixas[], int quantidadeCaixa)
{
    for (int i = 0; i < 10; i++) {										// Cria 10 clientes
        Cliente cliente;

        if (i < 2)														// Dois clientes com tempo 1
            cliente.tempo = 1;
        else if (i > 1 && i < 5)										// Tres clientes com tempo 2
            cliente.tempo = 2;
        else                                                            // Cinco clientes com tempo 3
            cliente.tempo = 3;

        // Encontrar a melhor fila e atribuir o cliente nela
        int melhorFila = 0,
            menor = caixas[0].quantidade;
        for (int j = 1; j < quantidadeCaixa; j++) {
            if (caixas[j].quantidade < menor) {
                menor = caixas[j].quantidade;
                melhorFila = j;
            }
        }
        enfileirar(caixas[melhorFila], cliente);
    }
}

// Função de atender clientes
void atenderClientes(Fila<Cliente> caixas[], int quantidadeCaixa)
{
    //Cliente é atendido e quando seu tempo zerar, cliente é retirado
    for (int j = 0; j < quantidadeCaixa; j++) {
        if (caixas[j].quantidade > 0) {
            caixas[j].inicio->dado.tempo--;
            if (caixas[j].inicio->dado.tempo == 0)
                desenfileirar(caixas[j]);
        }
    }
}

// Funcão para contar clientes
int contarClientes(Fila<Cliente> caixas[], int quantidadeCaixa) {
    int contagem = 0;
    for (int i = 0; i < quantidadeCaixa; i++)
        contagem += caixas[i].quantidade;
    return contagem;
}

// Simulação de um Super Mercado
int simularSuperMercado()
{
    int quantidadeCaixa;
    std::cout << "Informe a quantidade de caixas: ";
    std::cin >> quantidadeCaixa;										// Quantidade de caixas escolhidas;

    Fila <Cliente> *caixas = new Fila <Cliente>[quantidadeCaixa];		// Aloca na memória caixas de acordo com a quantidade escolhida

    for (int i = 0; i < quantidadeCaixa; i++)							// Inicializar todos os caixas
        inicializarFila(caixas[i]);

    double somaMedias = 0.0;
    double somaAtendimento = 0.0;

    for (int ut = 0; ut < unidadeTamanho; ut++) {
        chegadaDeClientes(caixas, quantidadeCaixa);
        int antes = contarClientes(caixas, quantidadeCaixa);
        atenderClientes(caixas, quantidadeCaixa);
        int depois = contarClientes(caixas, quantidadeCaixa);
        somaMedias += static_cast<double>(depois) / static_cast<double>(quantidadeCaixa);
        somaAtendimento += static_cast<double>(antes - depois);
    }

    std::cout << "Média de espera por fila = " << somaMedias / unidadeTamanho << std::endl;
    std::cout << "Média de pessoas (" << somaAtendimento << ") "
              << "atendidas por caixa (" << static_cast<double>(quantidadeCaixa) << "): "
              << somaAtendimento / static_cast<double>(quantidadeCaixa);

    return 0;
}

int main()
{
    simularSuperMercado();

    cin.ignore();
    cin.get();
    return 0;
}
