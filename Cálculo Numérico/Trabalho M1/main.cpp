#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>
#include <iomanip>
#include <locale>

#include <fstream>

#include <iterativos.hpp>
#include <intervalo.hpp>

void questao01()
{
    std::ofstream bisseccao("1.a_bisseccao.csv", std::ios::out | std::ios::trunc);
    std::ofstream falsaPosicao("1.b-falsaPosicao.csv", std::ios::out | std::ios::trunc);

    /* Equação base para resolução do problema.
     *
     * g(t) = 1 - (1 + t + t²) * e^(-t)
     *                     2
     * f(t) = 1 - (1 + t + t²) * e^(-t) - g(t)
     *                     2
     */
    auto equacao = [](double t, double g) -> double {
        return (1 - (1 + t + (pow (t, 2) / 2)) * exp(-t) - g);
    };

    /* LETRA A:
     *  Primeira parte do problema, calcular t quando g(t) = 0.1
     */
    double a = 0.1;
    auto equacaoA = [equacao, a](double t) -> double {
        return (equacao(t, a));
    };

    /* Encontrar intervalos iniciais para busca de raízes.
     * Chutar valores enquanto não encontrar um intervalo que haja alteração de sinal.
     */
    Intervalo<int> intervaloA = encontrarIntervaloComRaiz<int>(0, equacaoA);
    double respostaA = resolucaoPorBisseccaoLinear(intervaloA.getInicio(), intervaloA.getFim(), equacaoA, pow(10, -5), &bisseccao);
    std::cout << "Resposta em [" << intervaloA.getInicio() << ", " << intervaloA.getFim()
              << "] = " << respostaA << std::endl;

    /* LETRA B:
     *  Segunda parte do programa, calculcar t quando g(t) = 0.9
     */
    double b = 0.9;
    auto equacaoB = [equacao, b](double t) -> double {
        return (equacao(t, b));
    };

    /* Encontrar intervalos iniciais para busca de raízes.
     * Chutar valores enquanto não encontrar um intervalo que haja alteração de sinal.
     */

    Intervalo<int> intervaloB = encontrarIntervaloComRaiz<int>(0, equacaoB);
    double respostaB = resolucaoPorFalsaPosicao(intervaloB.getInicio(), intervaloB.getFim(), equacaoB, pow(10, -5), &falsaPosicao);
    std::cout << "Resposta em [" << intervaloB.getInicio() << ", " << intervaloB.getFim()
              << "] = " << respostaB << std::endl;

    bisseccao.close();
    falsaPosicao.close();
}

void questao02()
{
    std::ofstream bisseccao("2.a_bisseccao.csv", std::ios::out | std::ios::trunc);
    std::ofstream falsaPosicao("2.b-falsaPosicao.csv", std::ios::out | std::ios::trunc);

    /* Equação para resolução do problema:
     *
     * tg(θ) = sen(α) * cos(α)
     *    2     gR - cos²(α)
     *          v²
     *
     * f(α) = sen(α) * cos(α) - tg(θ)
     *          gR - cos²(α)       2
     *          v²
     *
     * Alguns intervalos onde há troca de sinal não apresentam uma raiz real.
     *
     */
    double teta = 80,
            g = 9.81,
            r = 63710000.0,
            v = sqrt(g * r * 1.25);

    auto equacao = [=](double x) -> double {
        return ((sin(rad(x))*cos(rad(x))) / (((g*r)/pow(v,2))-pow(cos(rad(x)),2))) - tan(rad(teta/2));
    };

    /* LETRA A:
     *  Primeira parte do problema: encontrar a primeira raiz positiva de alfa (x) com
     *  o método de bissecção.
     */
    Intervalo<int> intervaloA = encontrarIntervaloComRaiz<int>(40, equacao);
    double respostaA = resolucaoPorBisseccaoLinear(intervaloA.getInicio(),intervaloA.getFim(), equacao, pow(10,-5), &bisseccao);
    std::cout << "Resposta em [" << intervaloA.getInicio() << ", " << intervaloA.getFim()
              << "] = " << respostaA << std::endl;

    /* LETRA B:
     *  Segunda parte do problema: encontrar a segunda raiz positiva de alfa (x) com
     *  o método de falsa posição.
     */
    Intervalo<int> intervaloB = encontrarIntervaloComRaiz<int>(170, equacao);
    double respostaB = resolucaoPorFalsaPosicao(intervaloB.getInicio(), intervaloB.getFim(), equacao, pow(10,-5), &falsaPosicao);
    std::cout << "Resposta em [" << intervaloB.getInicio() << ", " << intervaloB.getFim()
              << "] = " << respostaB << std::endl;

    bisseccao.close();
    falsaPosicao.close();
}

void questao03()
{
    std::ofstream newton("3.a_newton.csv", std::ios::out | std::ios::trunc);
    std::ofstream secantes("3.b-secantes.csv", std::ios::out | std::ios::trunc);

    /* Equação para resolução do problema:
     *
     * [(1.49)³ * D^5 * S ^ (3/2)] * y^5 - 4 * Q³*y² - 4 * Q³ * D * y - q³ * D² = 0
     *    E
     *
     */
    auto equacao = [](double y, double d, double s, double e, double q) {
        return ((pow(1.49 / e, 3) * pow(d, 5) * pow(s, 3/2)) * pow(y, 5) - (4 * pow(q, 3) * pow(y, 2)) - (4 * pow(q, 3) * d * y) - (pow(q, 3) * pow(d, 2)));
    };

    /* Derivada da equação:
     *
     * 5 * [(1.49)³ * D^5 * S ^ (3/2)] * y^4 - 8 * Q³ * y - 4 * Q³ * D = 0
     *        E
     *
     */
    auto derivada = [](double y, double d, double s, double e, double q) {
        return (5 * (pow(1.49 / e, 3) * pow(d, 5) * pow(s, 3/2)) * pow(y, 4) - 8 * pow(q, 3) * y - 4 * pow(q, 3) * d);
    };

    /* LETRA A:
     * Encontrar a profundidade do canal y na estação A (D = 20.0, E = 0.0001, S = 0.030, Q = 133.0)
     * utilizando o método de Newton.
     */
    auto equacaoA = [equacao](double y) {
        return (equacao(y, 20.0, 0.0001, 0.030, 133.0));
    };

    auto derivadaA = [derivada](double y) {
        return (derivada(y, 20.0, 0.0001, 0.030, 133.0));
    };

    /* Encontrar intervalos iniciais para busca de raízes.
     * Chutar valores enquanto não encontrar um intervalo que haja alteração de sinal.
     */
    Intervalo<int> intervaloA = encontrarIntervaloComRaiz<int>(0, equacaoA);
    double respostaA = resolucaoPorNewton((intervaloA.getInicio() + intervaloA.getFim()) / 2, equacaoA, derivadaA, pow(10,-5), &newton);
    std::cout << "Resposta em [" << intervaloA.getInicio() << ", " << intervaloA.getFim()
              << "] = " << respostaA << std::endl;

    /* LETRA B:
     * Encontrar a profundidade do canal y na estação B (D = 21.5, E = 0.0001, S = 0.030, Q = 122.3)
     * utilizando o método das Secantes.
     */
    auto equacaoB = [equacao](double y) {
        return (equacao(y, 21.5, 0.0001, 0.030, 122.3));
    };

    /* Encontrar intervalos iniciais para busca de raízes.
     * Chutar valores enquanto não encontrar um intervalo que haja alteração de sinal.
     */
    Intervalo<int> intervaloB = encontrarIntervaloComRaiz<int>(0, equacaoB);
    double respostaB = resolucaoPorSecante(intervaloB.getInicio(), intervaloB.getFim(), equacaoB, pow (10, -12.5), &secantes);
    std::cout << "Resposta em [" << intervaloB.getInicio() << ", " << intervaloB.getFim()
              << "] = " << respostaB << std::endl;

    newton.close();
    secantes.close();
}

void questao04()
{
    std::ofstream newton("4.a_newton.csv", std::ios::out | std::ios::trunc);
    std::ofstream secantes("4.b-secantes.csv", std::ios::out | std::ios::trunc);

    /* Equação base para resolução do problema.
     *
     * f(x) = 37.104740 + 3.15122 * t - (2 * t²)
     *                                       2
     *
     */
    auto equacao = [](double t) {
        return (37.104740 + 3.15122 * t - (2 * pow (t, 2) / 2));
    };

    /* Derivada da função inicial
     *
     * f'(x) = 3.15122 - 2 * t
     *
     */
    auto derivada = [](double t) {
        return (3.15122 - 2 * t);
    };

    /* LETRA A:
     * Descobrir a raiz positiva utilizando o método de Newton.
     */
    Intervalo<int> intervaloA = encontrarIntervaloComRaiz<int>(0, equacao);
    double respostaA = resolucaoPorNewton((intervaloA.getInicio() + intervaloA.getFim()) / 2, equacao, derivada, pow(10, -5), &newton);
    std::cout << "Resposta em [" << intervaloA.getInicio() << ", " << intervaloA.getFim()
              << "] = " << respostaA << std::endl;

    /* LETRA B:
     * Descobrir a raiz negativa utilizando o método das Secantes.
     */
    Intervalo<int> intervaloB = encontrarIntervaloComRaiz<int>(0, equacao, -1);
    double respostaB = resolucaoPorSecante(intervaloB.getInicio(), intervaloB.getFim(), equacao, pow(10, -5), &secantes);
    std::cout << "Resposta em [" << intervaloB.getInicio() << ", " << intervaloB.getFim()
              << "] = " << respostaB << std::endl;

    newton.close();
    secantes.close();
}

void matrizParaCSV(const std::vector<std::vector<double>> &matriz, std::ostream &arquivo) {
    for (unsigned long i = 0; i < matriz.size(); i++) {
        for (unsigned long j = 0; j < matriz[i].size(); j++) {
            arquivo << matriz[i][j] << ",";
        }
        arquivo << std::endl;
    }
}

void questao05()
{
    std::ofstream gauss("5-gauss.csv", std::ios::out | std::ios::trunc);

    /* Matriz inicial para resolução do problema.
     * Equivale a transposta da matriz dada no enunciado.
     */
    std::vector<std::vector<double>> vec {
        { 1, 0, 2, 3, 2, 27 },
        { 1, 1, 1, 2, 1, 23 },
        { 1, 2, 1, 1, 2, 31 },
        { 0, 1, 2, 2, 3, 31 },
        { 2, 1, 0, 1, 1, 22 },
    };

    matrizParaCSV(vec, gauss);

    /* Invocar o procedimento de eliminação Gaussiana.
     */
    std::vector<double> respostas = eliminacaoDeGauss(vec);

    gauss << std::endl;
    matrizParaCSV(vec, gauss);

    /* Exibir o resultado.
     */
    int xIndice = 1;
    std::for_each(respostas.begin(), respostas.end(), [&xIndice](double v) {
                    std::cout << "x" << xIndice++ << " = " << v << std::endl;
                  });

    /*
     * Conferir resultados apresentados:
     *
     * 4.1 + 6.0 + 2.2 + 3.3 + 5.2 = 27
     * 4.1 + 6.1 + 2.1 + 3.2 + 5.1 = 23
     * 4.1 + 6.2 + 2.1 + 3.1 + 5.2 = 31
     * 4.0 + 6.1 + 2.2 + 3.2 + 5.3 = 31
     * 4.2 + 6.1 + 2.0 + 3.1 + 5.1 = 22
     *
     */

    gauss.close();
}

void questao06()
{
    std::ofstream gauss ("6-gauss.csv", std::ios::out | std::ios::trunc);
    /* Matriz para resolução do problema proposto.
     */
    std::vector<std::vector<double>> vec {
        { -4, 1, 0, 1, 0, 0, 0, 0, 0, 0 },
        { 1, -4, 1, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 1, -4, 0, 0, 1, 0, 0, 0, 0 },
        { 1, 0, 0, -4, 1, 0, 1, 0, 0, 0 },
        { 0, 1, 0, 1, -4, 1, 0, 1, 0, 0 },
        { 0, 0, 1, 0, 1, -4, 0, 0, 1, 0 },
        { 0, 0, 0, 1, 0, 0, -4, 1, 0, -1 },
        { 0, 0, 0, 0, 1, 0, 1, -4, 1, -1 },
        { 0, 0, 0, 0, 0, 1, 0, 1, -4, -1 }
    };

    matrizParaCSV(vec, gauss);

    /* Invocar o procedimento de eliminação de Gauss.
     */
    std::vector<double> respostas = eliminacaoDeGauss(vec);

    gauss << std::endl;
    matrizParaCSV(vec, gauss);


    /* Exibir resultados.
     */
    int xIndice = 1;
    std::for_each(respostas.begin(), respostas.end(), [&xIndice](double a) {
                    std::cout << "x" << xIndice++ << " = " << a << std::endl;
                  });

    gauss.close();
}

void sinalizarQuestao(std::function<void(void)> questao, int numero)
{
    std::cout << "~~~~Questao 0" << numero << "~~~~" << std::endl;
    questao();
    std::cout << "~~~~~~~~~~~~~~~~~~" << std::endl << std::endl;
}

int somaDois (int a, int b){
    return a + b;
}

int main ()
{
    std::cout.precision(8);
    setlocale(LC_ALL, "Portuguese");
    sinalizarQuestao(questao01, 1);
    sinalizarQuestao(questao02, 2);
    sinalizarQuestao(questao03, 3);
    sinalizarQuestao(questao04, 4);
    sinalizarQuestao(questao05, 5);
    sinalizarQuestao(questao06, 6);
    return 0;
}
