package imobiliaria;
import imobiliaria.imovel.Imovel;
import java.util.Date;

public class LocacaoImovel
{
    private Imovel imovel;
    private Cliente inquilino;
    private double valorMensal;
    private Date dataInicio;
    private Date dataFim;

    public LocacaoImovel(Imovel imovel, Cliente inquilino, double valorMensal, Date dataInicio, Date dataFim)
    {
        this.imovel = imovel;
        this.inquilino = inquilino;
        this.valorMensal = valorMensal;
        this.dataInicio = dataInicio;
        this.dataFim = dataFim;
    }
    
    public String detalhesAluga()
    {
        return String.format("Imovel: %s, Inquilino: %s, Valor mensal: %.2f, Data de inicio: %s, Data de termino: %s",
            this.imovel.getTipo(), this.getInquilino(), this.getValorMensal(), this.getDataInicio(), this.getDataFim());            
    }
    
    public Imovel getImovel()
    {
        return imovel;
    }

    public Cliente getInquilino()
    {
        return inquilino;
    }

    public double getValorMensal() 
    {
        return valorMensal;
    }

    public Date getDataInicio()
    {
        return dataInicio;
    }

    public Date getDataFim() 
    {
        return dataFim;
    }
}