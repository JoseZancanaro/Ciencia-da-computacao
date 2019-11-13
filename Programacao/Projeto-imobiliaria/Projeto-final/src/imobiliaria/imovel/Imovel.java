package imobiliaria.imovel;

public abstract class Imovel 
{
    private int codigo;
    abstract public String mostrarDetalhes();
    abstract public String getTipo();
    
    public int getCodigo()
    {
        return this.codigo;
    }
    
    public Imovel(int codigo) {
        this.codigo = codigo;
    }
    
}
