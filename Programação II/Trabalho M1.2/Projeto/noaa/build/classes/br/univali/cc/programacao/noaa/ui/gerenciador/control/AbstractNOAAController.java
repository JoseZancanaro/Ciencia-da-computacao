package br.univali.cc.programacao.noaa.ui.gerenciador.control;

public abstract class AbstractNOAAController
{
    protected AplicacaoNOAAController main;
    
    protected void setAplicacaoNOAA(AplicacaoNOAAController main)
    {
        this.main = main;
    }
    
    public abstract void ativar();
    public abstract void desativar();
}
