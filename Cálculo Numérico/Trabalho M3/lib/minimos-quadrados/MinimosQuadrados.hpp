#ifndef MINIMOSQUADRADOS_HPP
#define MINIMOSQUADRADOS_HPP

#include "../AlgoritmoNumerico.hpp"

double produtoEscalar(const Linha &x, const Linha &y)
{
    double acc = 0.0;
    for (natural i = 0; i < x.size(); i++)
        acc += x[i] * y[i];
    return acc;
}

Matriz construirProdutosEscalares(Matriz potencias, const unsigned long &grau)
{
    Matriz produtosEscalares(grau + 1, Linha(grau + 2));

    for (natural i = 0; i < produtosEscalares.size(); i++) {
        for (natural j = 0; j < produtosEscalares.front().size(); j++) {
            if (i > j) { // já calculou o produto escalar
                produtosEscalares[i][j] = produtosEscalares[j][i];
            }
            else { // não calculou, calcular.
                produtosEscalares[i][j] = produtoEscalar(potencias[i], potencias[j]);
            }
        }
    }

    return produtosEscalares;
}

Solucao minimosQuadradosGenerico(Matriz potencias, const unsigned long &grau)
{
    Matriz produtosEscalares = construirProdutosEscalares(potencias, grau);
    return eliminacaoGaussianaComPivoteamento(produtosEscalares);
}

Matriz construirPotencias(const std::vector<Ponto> &pontos, const unsigned long &grau)
{
    Matriz potencias(grau + 2, Linha(pontos.size()));

    // preencher potencias (x elevado de 0 até o grau)
    for (natural i = 0; i < potencias.size() - 1; i++) {
        for (natural j = 0; j < pontos.size(); j++)
            potencias[i][j] = std::pow(pontos[j].x, i);
    }
    // preencher funcao
    for (natural i = 0; i < pontos.size(); i++)
        potencias.back().at(i) = pontos[i].y;

    return potencias;
}

Solucao minimosQuadradosSimples(const std::vector<Ponto> &pontos, const unsigned long &grau)
{
    return minimosQuadradosGenerico(construirPotencias(pontos, grau), grau);
}

Solucao aproximacaoExponencial(const std::vector<Ponto> &pontos)
{
    std::vector<Ponto> lnY {pontos};

    std::for_each(lnY.begin(), lnY.end(), [](Ponto &p) {
        p.y = std::log(p.y);
    });

    // solução de tamanho 2
    Solucao solucao = minimosQuadradosGenerico(construirPotencias(lnY, 1), 1);

    std::for_each(solucao.begin(), solucao.end(), [](double &x){
        x = std::exp(x);
    });

    return solucao;
}

Solucao aproximacaoExponencialNatural(const std::vector<Ponto> &pontos)
{
    std::vector<Ponto> lnY {pontos};

    std::for_each(lnY.begin(), lnY.end(), [](Ponto &p) {
        p.y = std::log(p.y);
    });

    // solução de tamanho 2
    Solucao solucao = minimosQuadradosGenerico(construirPotencias(lnY, 1), 1);

    solucao.front() = std::exp(solucao.front());

    return solucao;
}


#endif // MINIMOSQUADRADOS_HPP
