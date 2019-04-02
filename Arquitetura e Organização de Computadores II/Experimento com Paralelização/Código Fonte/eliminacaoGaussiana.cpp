#include "eliminacaoGaussiana.hpp"

/**
 * Implementação de todas as funções utilizadas para este trabalho.
 */

/* Eliminação de Gauss com pivoteamento parcial: */
std::vector<double> eliminacaoDeGaussPivoteamentoParcial(std::vector<std::vector<double>> &matriz)
{
    auto inicio = std::chrono::high_resolution_clock::now();

    // Encontrar o maior pivô disponível (em módulo).
    for (size_t pivo = 0; pivo < matriz[0].size() - 2; pivo++) {
        size_t maiorPivo = pivo;
        for (size_t i = pivo + 1; i < matriz.size(); i++) {
            if (fabs(matriz[i][pivo]) > fabs(matriz[maiorPivo][pivo])) {
                maiorPivo = i;
            }
        }
        if (pivo != maiorPivo) {
            matriz[pivo].swap(matriz[maiorPivo]);
        }

        // Zerar abaixo da diagonal principal.
        #pragma omp parallel
        {
            #pragma omp for
            for (size_t linha = pivo + 1; linha < matriz.size(); linha++) {
                double fator = matriz[linha][pivo] / matriz[pivo][pivo];
                for (size_t coluna = 0; coluna < matriz[0].size(); coluna++) {
                    matriz[linha][coluna] -= (fator) * (matriz[pivo][coluna]);
                }
            }
        }
    }

    // Zerar acima da diagonal principal.
    for (size_t pivo = matriz[0].size() - 2; pivo > 0; pivo--) {
        #pragma omp parallel
        {
            #pragma omp for
            for (size_t linha = 0; linha < pivo; linha++) {
                double fator = matriz[linha][pivo] / matriz[pivo][pivo];
                for (size_t coluna = 0; coluna < matriz[0].size(); coluna++) {
                    matriz[linha][coluna] -= (fator) * (matriz[pivo][coluna]);
                }
            }
        }
    }

    // Finalizar eliminação.
    std::vector<double> respostas;
    for (size_t i = 0; i < matriz.size(); i++) {
        matriz[i][matriz[i].size() - 1] /= matriz[i][i];
        matriz[i][i] /= matriz[i][i];
        respostas.push_back(matriz[i][matriz[i].size() - 1]);
    }

    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = fim - inicio;
    std::cout << tempo.count() << "s" << std::endl;

    return respostas;
}

/* Auxiliares: */
int aleatorioEntre(int minimo, int maximo)
{
    return (rand() - minimo) % maximo + minimo;
}

// Imprimir para CSV.
void matrizParaCSV(const std::vector<std::vector<double>> &matriz, std::string local)
{
    std::ofstream csv(local);

    for (size_t linha = 0; linha < matriz.size(); linha++) {
        for (size_t coluna = 0; coluna < matriz[linha].size(); coluna++) {
            csv << matriz[linha][coluna] << ",";
        }
        csv << std::endl;
    }

    csv.close();
}

// Ler CSV.
std::vector<std::vector<double>> lerMatrizCSV(std::string local)
{
    std::ifstream csv(local);
    std::vector<std::vector<double>> matriz;

    std::string linha;
    while (std::getline(csv, linha)) {
        std::vector<double> vec;
        std::stringstream sstream(linha);
        std::string buf;
        while (std::getline(sstream, buf, ',')) {
            vec.push_back(atoi(buf.c_str()));
        }
        matriz.push_back(vec);
    }

    csv.close();

    return matriz;
}

// Gerar coeficientes da matriz.
std::vector<int> gerarCoeficientes(size_t tamanho)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    std::vector<int> coeficientes(tamanho);

    for (size_t i = 0; i < tamanho; i++) {
        coeficientes[i] = aleatorioEntre(1, 10);
    }

    return coeficientes;
}

// Gerar matriz que será utilizada para o trabalho.
std::vector<std::vector<double>> gerarMatriz(size_t tamanho, std::vector<int> coeficientes)
{
    std::vector<std::vector<double>> matriz(tamanho, std::vector<double>(tamanho + 1));

    for (size_t linha = 0; linha < matriz.size(); linha++) {
        int soma = 0;
        for (size_t coluna = 0; coluna < matriz.size(); coluna++) {
            int valorGerado = aleatorioEntre(1, 10);
            matriz[linha][coluna] = valorGerado;
            soma += valorGerado * coeficientes[coluna];
        }
        matriz[linha][tamanho] = soma;
    }

    return matriz;
}

/* Impressão */
void imprimirMatriz(const std::vector<std::vector<double>> &matriz)
{
    for (size_t linha = 0; linha < matriz.size(); linha++) {
        for (size_t coluna = 0; coluna < matriz[linha].size(); coluna++) {
            std::cout << matriz[linha][coluna] << " | ";
        }
        std::cout << std::endl;
    }
}
