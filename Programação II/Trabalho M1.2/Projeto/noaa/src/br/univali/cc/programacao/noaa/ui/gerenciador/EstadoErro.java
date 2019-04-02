package br.univali.cc.programacao.noaa.ui.gerenciador;

public class EstadoErro
{
    private Exception ex;
    private boolean erro;

    public EstadoErro(Exception ex, boolean erro)
    {
        this.ex = ex;
        this.erro = erro;
    }

    public Exception getEx()
    {
        return ex;
    }

    public boolean isErro()
    {
        return erro;
    }
    
    public void desativar()
    {
        this.erro = false;
    }
    
    public void ativar()
    {
        this.erro = true;
    }
}
