package matjogo.dominio;

public class PosicaoBlueprint
{
    private double x;
    private double y;
    private double largura;
    private double altura;
    private int capacidade;
    private double margem;
    private double borda;

    public PosicaoBlueprint(double x, double y, double largura, double altura, int capacidade, double margem, double borda)
    {
        this.x = x;
        this.y = y;
        this.largura = largura;
        this.altura = altura;
        this.capacidade = capacidade;
        this.margem = margem;
        this.borda = borda;
    }
    
    public double getX()
    {
        return x;
    }

    public void setX(double x)
    {
        this.x = x;
    }
    
    public double getY()
    {
        return y;
    }

    public void setY(double y)
    {
        this.y = y;
    }   

    public double getLargura()
    {
        return largura;
    }

    public void setLargura(double largura)
    {
        this.largura = largura;
    }

    public double getAltura()
    {
        return altura;
    }

    public void setAltura(double altura)
    {
        this.altura = altura;
    }

    public int getCapacidade()
    {
        return capacidade;
    }

    public void setCapacidade(int capacidade)
    {
        this.capacidade = capacidade;
    }

    public double getMargem()
    {
        return margem;
    }

    public void setMargem(double margem)
    {
        this.margem = margem;
    }

    public double getBorda()
    {
        return borda;
    }

    public void setBorda(double borda)
    {
        this.borda = borda;
    } 
}
