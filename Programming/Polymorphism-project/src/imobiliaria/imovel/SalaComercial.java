package imobiliaria.imovel;

public class SalaComercial extends Imovel 
{
        private double area;
        private boolean estaMobiliado;

    public SalaComercial(double area, boolean estaMobiliado, int codigo)
    {
        super(codigo);
        this.area = area;
        this.estaMobiliado = estaMobiliado;
    }
            
    public double getArea()
    {
        return area;
    }

    public boolean getEstaMobiliado() 
    {
        return estaMobiliado;
    }
       
    public String mostrarDetalhes()
    {
        return String.format("Tipo: Sala Comercial, Área: %.2f, contém mobília: %b",
                                this.getArea(), this.getEstaMobiliado());
    }
        
     public String getTipo()
    {
        return "Sala comercial";
    }
}