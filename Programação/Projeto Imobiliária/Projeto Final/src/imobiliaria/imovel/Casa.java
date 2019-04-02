package imobiliaria.imovel;

import imobiliaria.imovel.Imovel;

public class Casa extends Imovel 
{
    private String cor;
    private int qtdComodos;
    private double areaCasa;

    public Casa(String cor, int qtdComodos, double areaCasa, int codigo)
    {
        super(codigo);
        this.cor = cor;
        this.qtdComodos = qtdComodos;
        this.areaCasa = areaCasa;
    }
   
    public String getCor() 
    {
        return cor;
    }

    public int getQtdComodos() 
    {
        return qtdComodos;
    }

    public double getAreaCasa() 
    {
        return areaCasa;
    }
    
    public String mostrarDetalhes()
    {
        return String.format("Tipo: Casa, Cor: %s, Quantidade de cômodos: %d, Área: %.2f",
                                this.getCor(), this.getQtdComodos(), this.getAreaCasa());
    }
    
    public String getTipo()
    {
        return "Casa";
    }
}