package imobiliaria.imovel;

public class Terreno extends Imovel
{
    private double area;
    private String estadoDoTerreno;

    public Terreno(double area, String estadoDoTerreno, int codigo)
    {
        super(codigo);
        this.area = area;
        this.estadoDoTerreno = estadoDoTerreno;
    }
    
    public double getArea()
    {
        return area;
    }
    
    public String getEstadoDoTerreno()
    {
        return estadoDoTerreno;
    }
    
    public String mostrarDetalhes()
    {
        return String.format("Tipo: Terreno, Área: %.2f, Estado atual: %s",
                                this.getArea(), this.getEstadoDoTerreno());
    }
    
     public String getTipo()
    {
        return "Terreno";
    }
}