#include <iostream>
#include <string>
#include "pilhaGenerica.hpp"

using namespace std;

// Exercício em Aula.
// Verificar se o indice contem o char necessário (arrayFinal ou arrayInicial)
bool verificarArray(char atual, char array[])
{
    for (int i = 0; i < 3; i++) {
        if (atual == array[i])
            return true;
    }
    return false;
}

// Verificar indice
template <typename T>
int verificacaoIndice(T array[], int tamanho, T alvo)
{
    for (int i = 0; i < tamanho; i++)
        if (alvo == array[i]) return i;
    return -1;
}

// Função que verificará se a expressão tem todos os requisitos
bool verificarExpressaoMat(string textoExpressao)
{
    Pilha<char> pilha;
    inicializarPilha(pilha);
    char arrayInicio[] = { '{', '[', '(' };
    char arrayFinal[] = { '}', ']', ')' };

    for (size_t i = 0; i < textoExpressao.size(); i++) {
        char atual = textoExpressao[i];

        if (verificarArray(atual, arrayInicio)) {
            push(pilha, atual);
        }
        else if (verificarArray(atual, arrayFinal)) {
            if (pilha.quantidade == 0)
                return false;
            else {
                char aux = pilha.topo->dado;
                char fecha = arrayInicio[verificacaoIndice(arrayFinal, 3, atual)];

                if (aux == fecha)
                    pop(pilha);
                else
                    return false;
            }
        }
    }
    return pilha.quantidade == 0;
}

// Verificará se a expressão está correta
void conferirExpressaoMat()
{
    string texto;

    int i = 1;
    while (i) {
        i = 0;
        cout << "Digite sua expressão: ";
        cin >> texto;

        if (verificarExpressaoMat(texto))
            cout << "Expressão ok, tudo certo! " << std::endl << std::endl;
        else
            cout << "Expressão não correta, tente outra vez! " << std::endl << std::endl;
    }
}

int metodoProfessorExpressaoMat()
{
    Pilha<char> p;
    inicializarPilha(p);
    string texto;
    cin >> texto;
    bool correto = true;

    for (size_t i = 0; i < texto.size(); i++) {
        char atual = texto.at(i);
        if (atual == '{' || atual == '[' || atual == '(') {
            push(p, atual);
        }
        else {
            if (atual == '}' || atual == ']' || atual == ')') {
                if (p.quantidade > 0) {
                    if ((atual == '}' && p.topo->dado == '{')
                        || (atual == ']' && p.topo->dado == '[')
                        || (atual == ')' && p.topo->dado == '(')) {
                        pop(p);
                    }
                    else {
                        correto = false;
                        break;
                    }
                }
                else {
                    correto = false;
                    break;
                }
            }
        }
    }
    if (p.quantidade == 0 && correto) {
        cout << "\nCORRETO!\n";
    }
    else {
        cout << "\nERRO!!!\n";
    }
    return 0;
}

int main()
{
    conferirExpressaoMat();
    //metodoProfessorExpressaoMat();

    return 0;
}
