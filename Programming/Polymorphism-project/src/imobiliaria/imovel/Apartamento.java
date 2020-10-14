package imobiliaria.imovel;

import imobiliaria.imovel.Imovel;

public class Apartamento extends Imovel
{
    private int numeroDoAndar;
    private double area;
    private int qtdComodos;
    private boolean contemSacada;

    public Apartamento(int numeroDoAndar, double area, int qtdComodos, boolean contemSacada, int codigo) 
    {
        super(codigo);
        this.numeroDoAndar = numeroDoAndar;
        this.area = area;
        this.qtdComodos = qtdComodos;
        this.contemSacada = contemSacada;
    }

    public int getNumeroDoAndar() 
    {
        return numeroDoAndar;
    }
    
    public double getArea()
    {
        return area;
    }

    public int getQtdComodos()
    {
        return qtdComodos;
    }

    public boolean getContemSacada() 
    {
        return contemSacada;
    }
    
    public String mostrarDetalhes()
    {
        return String.format("Tipo: Apartamento, Número do andar: %d, Quantidade de cômodos: %d, Contém sacada: %b, Área: %.2f ",
                                this.getNumeroDoAndar(), this.getQtdComodos(), this.getContemSacada(), this.getArea());
    }
    
     public String getTipo()
    {
        return "Apartamento";
    }   
}