package imobiliaria;

import imobiliaria.imovel.Imovel;

public class ValorImovel 
{
    private Imovel imovel;
    private double preco;

    public ValorImovel(Imovel imovel, double preco)
    {
        this.imovel = imovel;
        this.preco = preco;
    }

    public double getPreco()
    {
        return preco;
    }   
    
    public Imovel getImovel()
    {
        return imovel;
    }
}