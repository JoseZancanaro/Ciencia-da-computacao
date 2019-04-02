#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "lib/equacao-diferencial/EquacaoDiferencial.hpp"
#include "lib/minimos-quadrados/MinimosQuadrados.hpp"
#include "lib/integracao/IntegracaoNumerica.hpp"

void questao01()
{
    std::vector<Ponto> populacao {{1872, 9.9}, {1890, 14.3}, {1900, 17.4}, {1920, 30.6}, {1940, 41.2},
                                 {1950, 51.9}, {1960, 70.2}, {1970, 93.1}, {1980, 119.0}, {1991, 146.2}};

    std::cout << "Letra A : Reta" << std::endl;

    Solucao reta = minimosQuadradosSimples(populacao, 1);
    std::cout << "Solução : ";
    std::for_each(reta.begin(), reta.end(), [](double x) { std::cout << x << " ";} );

    std::vector<Ponto> estimativaPorReta {populacao};
    estimativaPorReta.push_back({2018, 0.0});
    std::for_each(estimativaPorReta.begin(), estimativaPorReta.end(), [&reta](Ponto &p) {
        p.y = resolverPolinomioInterpolado(p.x, reta);
    });

    std::cout << std::endl;

    std::for_each(estimativaPorReta.begin(), estimativaPorReta.end(), [](Ponto p) { std::cout << p.x << ":" << p.y << std::endl; });

    std::cout << std::endl;

    std::cout << "Letra B : Parábola" << std::endl;

    Solucao parabola = minimosQuadradosSimples(populacao, 2);
    std::cout << "Solução : ";
    std::for_each(parabola.begin(), parabola.end(), [](double x) { std::cout << x << " ";} );

    std::vector<Ponto> estimativaPorParabola {populacao};
    estimativaPorParabola.push_back({2018, 0.0});
    std::for_each(estimativaPorParabola.begin(), estimativaPorParabola.end(), [&parabola](Ponto &p) {
        p.y = resolverPolinomioInterpolado(p.x, parabola);
    });

    std::cout << std::endl;

    std::for_each(estimativaPorParabola.begin(), estimativaPorParabola.end(), [](Ponto p) { std::cout << p.x << ":" << p.y << std::endl; });

    std::cout << std::endl;

    std::cout << "Letra C : Exponencial" << std::endl;

    Solucao exponencial = aproximacaoExponencialNatural(populacao);
    std::cout << "Solução : ";
    std::for_each(exponencial.begin(), exponencial.end(), [](double x) { std::cout << x << " ";} );

    std::vector<Ponto> estimativaPorExponencial {populacao};
    estimativaPorExponencial.push_back({2018, 0.0});
    std::for_each(estimativaPorExponencial.begin(), estimativaPorExponencial.end(), [&exponencial](Ponto &p) {
        p.y = exponencial.front() * std::exp(exponencial.back() * p.x);
    });

    std::cout << std::endl;

    std::for_each(estimativaPorExponencial.begin(), estimativaPorExponencial.end(), [](Ponto p) { std::cout << p.x << ":" << p.y << std::endl; });

    std::cout << std::endl << std::endl;

    std::cout << "Letra D : Estimativa de População em 2018" << std::endl;
    std::cout << "Reta          : " << estimativaPorReta.back().y << std::endl;
    std::cout << "Parábola      : " << estimativaPorParabola.back().y << std::endl;
    std::cout << "Exponenciação : " << estimativaPorExponencial.back().y << std::endl;

    std::cout << std::endl;
}

void questao02()
{
    const double precisao = 10E-5;

    std::cout << "LETRA A : Regra dos Trapézios" << std::endl;

    std::function<double(double)> funcaoTrapezio = [](double x) -> double {
        return std::sin(sqrt(x));
    };

    std::ofstream trapezios("../Relatório/Dados/2.Trapezio.csv");

    double areaTrapezios = areaPorTrapezios(funcaoTrapezio, 0.0, 0.24, precisao, &trapezios);

    std::cout << "Aproximação [0.0, 0.24] = " << areaTrapezios << std::endl;

    trapezios.close();

    std::cout << std::endl;

    std::cout << "LETRA B : Regra do 1/3 de Simpson" << std::endl;

    std::function<double(double)> funcaoSimpson = [](double x) -> double {
        return std::tan(x) + std::exp(x);
    };

    std::ofstream simpson("../Relatório/Dados/2.Simpson.csv");

    double areaSimpson = areaPorSimpson(funcaoSimpson, 0.5, 1.5, precisao, &simpson);

    std::cout << "Aproximação [0.5, 1.5] = " << areaSimpson << std::endl;

    simpson.close();

}

void questao03()
{
    std::vector<double> hs {0.2, 0.1, 0.05};

    std::function<double(double, double)> diferencial = [](double x, double y) -> double {
        return y - x;
    };

    std::function<bool(Ponto)> condicao = [](Ponto ponto) -> bool {
        return ponto.x < 4.0 - 0.01;
    };

    for (double h : hs) {
        std::stringstream ss;
        ss << "../Relatório/Dados/3.Valores-" << h << ".csv";

        std::ofstream tabela(ss.rdbuf()->str());
        tabela << "x" << "," << "y" << std::endl;

        Ponto resposta = metodoDeEuler(diferencial, {0.0,2.0}, h, condicao, &tabela);
        std::cout << "Resposta para " << h << " : " << "(" << resposta.x << "," << resposta.y << ")" << std::endl;

        tabela.close();
    }


}

void decorar(std::function<void()> questao, int num)
{
    std::cout << "--- Questão " << num << " -----------------------" << std::endl;
    questao();
    std::cout << "-------------------------------------" << std::endl << std::endl;
}

int main()
{
    decorar(questao01, 1);
    decorar(questao02, 2);
    decorar(questao03, 3);
    return 0;
}
