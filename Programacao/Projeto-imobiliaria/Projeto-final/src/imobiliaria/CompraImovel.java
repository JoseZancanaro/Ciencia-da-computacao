package imobiliaria;
import imobiliaria.imovel.Imovel;
import java.util.Date;

public class CompraImovel 
{
    private Imovel imovel;
    private Date dataCompra;
    private Cliente cliente;
    private double preco;

    public CompraImovel(Imovel imovel, Date dataCompra, Cliente cliente, double preco)
    {
        this.imovel = imovel;
        this.dataCompra = dataCompra;
        this.cliente = cliente;
        this.preco = preco;
    }
    
    public Imovel getImovel() 
    {
        return imovel;
    }

    public Date getDataCompra() 
    {
        return dataCompra;
    }

    public Cliente getCliente()
    {
        return cliente;
    }

    public double getPreco()
    {
        return preco;
    }      
    
    public String detalhesCompra()
    {
        return String.format("Imovel: %s, Preço: %.2f, cliente: %s, Data da compra: %s", 
                this.getImovel().getTipo(), this.getPreco(), this.getCliente().toString(), this.getDataCompra().toString());
    }
}