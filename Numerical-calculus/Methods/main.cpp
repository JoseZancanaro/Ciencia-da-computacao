#include "algoritmoNumerico.hpp"

int main()
{
    //double a = 0.0;
    //double b = 0.0;
    //double xn = 0.0;
    //double xnAnterior = 0.0;
    //double precisao = pow(10, -2);
    //double x = 0.5;
    //std::vector<Ponto> pontos {{-1,  0}, {0, -1}, {1,  0}, {2, 7}};
    //unsigned int grau = 1;
    std::vector<std::vector<double>> matriz{{ 2, 3,  4, -2},
                                            { 3, 2, -1,  4},
                                            { 5, -4,  3,  8}};



    std::function<double(double)> funcaoBisseccao = [](double n){
        return pow(n, 3.0) - (9.0 * n) + 3.0 ;
    };

    //std::cout << bisseccao(a, b, funcaoBisseccao, parada, precisao) << std::endl << std::endl;

    std::function<double(double)> funcaoFalsaPosicao = [](double n){
        return (n * log10(n) - 1);
    };

    //std::cout << falsaPosicao(a, b, funcaoFalsaPosicao, parada, precisao) << std::endl << std::endl;

    std::function<double(double)> funcaoNewton = [](double x) -> double {
        return 4 * cos(x) - exp(x);
    };

    std::function<double(double)> derivadaNewton = [](double x) -> double {
        return -4 * sin(x) - exp(x);
    };

    //std::cout << metodoDeNewton(xn, funcaoNewton, derivadaNewton, parada, precisao) << std::endl << std::endl;

    std::function<double(double)> funcaoSecantes = [](double xn){
        return (sqrt(xn)) - (5 * exp(-xn));
    };

    //std::cout << metodoDasSecantes(xn, xnAnterior,funcaoSecantes, precisao) << std::endl << std::endl;

    imprimirVector((eliminacaoDeGauss(matriz)));
    //imprimirVector(eliminacaoDeGaussPivoteamentoParcial(matriz));
    //imprimirVector(gaussJacobi(matriz, precisao));
    //imprimirVector(gaussSeidel(matriz, precisao));

    //std::cout << "Resultado de " << x << " na fórmula de Lagrange é: " << formulaDeLagrange(x, pontos) << std::endl;
    //std::cout << "Resultado do esquema prático de Lagrange de " << x << " é: " << esquemaPraticoDeLagrange(x, pontos) << std::endl;
    //std::cout << "Resultado de " << x << " no polinomio obtido pelos pontos é: " << resolverPolinomio(x, pontos) << std::endl;
    //std::cout << "Resultado de " << x << " na fórmula de Newton é: " << formulaDeNewton(x, tabelaDiferencasDivididas(pontos));
    /*std::cout << "Resultado do esquema prático de Newton de " << x << " é: "
                 << esquemaPraticoDeNewton(x, tabelaDiferencasDivididas(pontos));
    */
    //minimosQuadrados(pontos, grau);

    std::cin.get();
    return 0;
}
