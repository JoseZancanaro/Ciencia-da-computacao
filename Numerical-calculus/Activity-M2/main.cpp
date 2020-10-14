#include "./lib/AlgoritmoNumerico.hpp"

#include <sstream>
#include <fstream>

const std::string CAMINHO = "../Relatório/Dados/";

std::string polinomioToString(Solucao solucao)
{
    std::stringstream ss;
    ss << "f(x) = ";
    for (natural i = 0; i < solucao.size(); i++) {
        if (solucao[i] != 0.0) {
            if (std::fabs(solucao[i]) == 1.0)
                ss << "x^" << i;
            else
                ss << std::fabs(solucao[i]) << " * x^" << i;
            if (i + 1 != solucao.size()) {
                if (solucao[i + 1] > 0)
                    ss << " + ";
                else
                    ss << " - ";
            }
        }
    }
    return ss.rdbuf()->str();
}

void imprimirSolucao(std::ostream &os, const Solucao &vetor)
{
    for (size_t i = 0; i < vetor.size(); i++)
        os << "x" << i << " = " << vetor[i] << std::endl;
}

void imprimirHistorico(std::ostream &os, const std::vector<std::vector<double>> &historico)
{
    if (historico.size() > 0) {
        os << "k, ";
        for (size_t i = 0; i < historico.size(); i++)
            os << i << ", ";
        os << std::endl;
        for (size_t i = 0; i < historico.front().size(); i++) {
            os << "x" << i << ", ";
            for (size_t j = 0; j < historico.size(); j++)
                os << historico[j][i] << ", ";
            os << std::endl;
        }
    }
}

void decorator(std::function<void()> questao, int num)
{
    std::cout << "--- Questão 0" << num << " -------------" << std::endl << std::endl;
    questao();
    std::cout << std::endl << "----------------------------" << std::endl << std::endl;
}

void questao01()
{
    Matriz matriz
    {
        { 2,  1,  7,  4, -3, -1,  4,  4,  7,  0,    86},
        { 4,  2,  2,  3, -2,  0,  3,  3,  4,  1,    45},
        { 3,  4,  4,  2,  1, -2,  2,  1,  9, -3,  52.5},
        { 9,  3,  5,  1,  0,  5,  6, -5, -3,  4,   108},
        { 2,  0,  7,  0, -5,  7,  1,  0,  1,  6,  66.5},
        { 1,  9,  8,  0,  3,  9,  9,  0,  0,  5,  90.5},
        { 4,  1,  9,  0,  4,  3,  7, -4,  1,  3,   139},
        { 6,  3,  1,  1,  6,  8,  3,  3,  0,  2,    61},
        { 6,  5,  0, -7,  7, -7,  6,  2, -6,  1, -43.5},
        { 1,  6,  3,  4,  8,  3, -5,  0, -6,  0,    31}
    };

    std::ofstream matrizInicial(CAMINHO + "1.MatrizInicial.csv");
    matrizInicial << matriz;
    matrizInicial.close();

    AlgoritmoGaussParcial gaussParcial(matriz);
    imprimirSolucao(std::cout, gaussParcial.escalonarCompletamente());

    std::ofstream gauss(CAMINHO + "1.PivoteamentoParcial.csv");
    gauss << gaussParcial.getMatriz();
    gauss.close();
}

void questao02()
{
    Matriz matriz
    {
        {  4, -1,  0, -1,  0,  0,  0,  0,  0,  0, -110},
        { -1,  4, -1,  0, -1,  0,  0,  0,  0,  0,  -30},
        {  0, -1,  4,  0,  0, -1,  0,  0,  0,  0,  -40},
        { -1,  0,  0,  4, -1,  0,  0,  0,  0,  0, -110},
        {  0, -1,  0, -1,  4, -1, -1,  0,  0,  0,    0},
        {  0,  0, -1,  0, -1,  4,  0, -1,  0,  0,  -15},
        {  0,  0,  0,  0, -1,  0,  4, -1,  0,  0,  -90},
        {  0,  0,  0,  0,  0, -1, -1,  4, -1,  0,  -25},
        {  0,  0,  0,  0,  0,  0,  0, -1,  4, -1,  -55},
        {  0,  0,  0,  0,  0,  0,  0,  0, -1,  4,  -65}
    };

    std::ofstream matrizInicial(CAMINHO + "2.MatrizInicial.csv");
    matrizInicial << matriz;
    matrizInicial.close();

    std::cout << "Método :: GAUSS JACOBI" << std::endl;
    AlgoritmoGaussJacobi gaussJacobi(matriz);
    imprimirSolucao(std::cout, gaussJacobi.resolverAte(pow(10, -5)));

    std::ofstream arquivoJacobi(CAMINHO + "2.GaussJacobi.csv");
    imprimirHistorico(arquivoJacobi, gaussJacobi.getHistorico());
    arquivoJacobi.close();

    std::cout << std::endl;

    std::cout << "Método :: GAUSS SEIDEL" << std::endl;
    AlgoritmoGaussSeidel gaussSeidel(matriz);
    imprimirSolucao(std::cout, gaussSeidel.resolverAte(pow(10, -5)));

    std::ofstream arquivoSeidel(CAMINHO + "2.GaussSeidel.csv");
    imprimirHistorico(arquivoSeidel, gaussSeidel.getHistorico());
    arquivoSeidel.close();
}

void questao03()
{
    std::vector<Ponto> pontos {{1500, 35}, {1250, 25}, {1000, 15}, {750, 10}, {500, 7}};
    Solucao solucao = resolverPorSistemaLinear(pontos);
    std::cout << "Polinômio > " << polinomioToString(solucao) << std::endl;
    std::cout << "f(850) = " << resolverPolinomioInterpolado(850, solucao) << std::endl;

    std::ofstream polinomio(CAMINHO + "3.Polinomio.csv");
    polinomio << solucao << std::endl;
    polinomio << polinomioToString(solucao) << std::endl;
    polinomio << resolverPolinomioInterpolado(850, solucao);
    polinomio.close();
}

void questao04()
{
    std::vector<Ponto> pontos {{500, 2.74}, {1000, 5.48}, {1500, 7.90}, {2000, 11.0}, {2500, 13.93}, {3000, 16.43}, {3500, 20.24}, {4000, 23.52} };
    EsquemaPraticoLagrange epl = teoremaDeLagrangePratico(1730, pontos);

    std::cout << epl.esquema << std::endl;
    std::cout << "f(1730) = " << epl.resposta << std::endl;

    std::ofstream esquema(CAMINHO + "4.Esquema.csv");
    esquema << epl.esquema << std::endl;
    esquema << "Produto Diagonal = " << epl.produtoDiagonal << std::endl;
    esquema << "S = " << epl.S << std::endl;
    esquema << epl.resposta << std::endl;
    esquema.close();
}

void questao05()
{
    std::vector<Ponto> pontos {{60, 76}, {80, 95}, {100, 112}, {120, 138}, {140, 151}, {160, 170}, {180, 192}};
    Matriz matriz = tabelaDeDiferencasDivididas(pontos);

    std::cout << matriz << std::endl;
    std::cout << "f(130) = " << esquemaPraticoNewton(130, matriz) << std::endl;

    std::ofstream diferencasDivididas(CAMINHO + "5.Tabela.csv");
    diferencasDivididas << matriz << std::endl;
    diferencasDivididas << esquemaPraticoNewton(130, matriz) << std::endl;
    diferencasDivididas.close();
}

void questao06()
{
    std::vector<Ponto> pontos {{2.8, 16.44}, {3.0, 20.08}, {3.2, 24.53}, {3.4, 29.96}};
    Matriz matriz = tabelaDeDiferencasDivididas(pontos);

    std::cout << matriz << std::endl;
    std::cout << "f(3.1) = " << esquemaPraticoNewton(3.1, matriz) << std::endl;

    std::ofstream splineCubica(CAMINHO + "6.Spline.csv");
    splineCubica << matriz << std::endl;
    splineCubica << esquemaPraticoNewton(3.1, matriz);
    splineCubica.close();
}

int main()
{
    decorator(questao01, 1);
    decorator(questao02, 2);
    decorator(questao03, 3);
    decorator(questao04, 4);
    decorator(questao05, 5);
    decorator(questao06, 6);

    return 0;
}
