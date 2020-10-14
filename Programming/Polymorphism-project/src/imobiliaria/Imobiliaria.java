package imobiliaria;
import imobiliaria.exceptions.ImobiliariaException;
import imobiliaria.imovel.Apartamento;
import imobiliaria.imovel.Casa;
import imobiliaria.imovel.Imovel;
import imobiliaria.imovel.SalaComercial;
import imobiliaria.imovel.Terreno;
import java.util.Date;
import java.util.List;
import java.util.LinkedList;

public class Imobiliaria 
{
    private List<Imovel> catalogo;
    private List<ValorImovel> compra;
    private List<ValorImovel> aluga;
    private List<CompraImovel> jaComprado;
    private List<LocacaoImovel> jaAlugado;
    private List<Cliente> clientes;
    
    private String nome;
    
    public Imobiliaria(String nome) 
    {
        this.nome = nome;
        this.catalogo = new LinkedList<>();
        this.compra = new LinkedList<>();
        this.aluga = new LinkedList<>();
        this.jaComprado = new LinkedList<>();
        this.jaAlugado = new LinkedList<>();
        this.clientes = new LinkedList<>();
    }
    
    public List<Imovel> getCatalogo() 
    {
        return catalogo;
    }

    public List<CompraImovel> getJaComprado() 
    {
        return jaComprado;
    }
   
    public List<ValorImovel> getCompra() 
    {
        return compra;
    }

    public List<LocacaoImovel> getJaAlugado() 
    {
        return jaAlugado;
    }

    public List<ValorImovel> getAluga() 
    {
        return aluga;
    }
    
    public String getNome() 
    {
        return nome;
    }
    
     private Imovel getImovel(int codigo)
    {
        for(Imovel imovel : catalogo){
            if(imovel.getCodigo() == codigo){
                return imovel;
            }
        }
        return null;
    }
    
    public void cadastrarEmCatalogo(Imovel imovel) throws ImobiliariaException
    {
        if(existeEmCatalogo(imovel.getCodigo())){
            throw new ImobiliariaException("ERRO: Não é possível cadastrar 2 imóveis com o mesmo número de matrícula.");
        }
        catalogo.add(imovel);
    }
     
    public void cadastrarEmClientes(Cliente cliente) throws ImobiliariaException
    {
        if(existeCliente(cliente.getCpf())){
            throw new ImobiliariaException("ERRO: Não é possível cadastrar clientes com o mesmo CPF.");
        }
        clientes.add(cliente);
    }
    
    public void cadastrarParaLocacao(int codigo, double precoImovel) throws ImobiliariaException
    {
        if(existeEmLocacao(codigo)){
            throw new ImobiliariaException("ERRO: Não é possível colocar um mesmo imóvel para alugar se o mesmo já tiver locação ativa.");
        }
        
        if(!existeEmCatalogo(codigo)){
            throw new ImobiliariaException("ERRO: Imóvel não existe em catálogo. ");
        }
        
       aluga.add(new ValorImovel(getImovel(codigo), precoImovel)); 
    }
    
    public void cadastrarParaCompra(int codigo, double preco) throws ImobiliariaException
    {
        if (existeEmVenda(codigo)) {
            throw new ImobiliariaException("ERRO: Não é possível colocar um mesmo imóvel para vender se o mesmo já tiver uma venda ativa.");
        }
        
        if(!existeEmCatalogo(codigo)){
            throw new ImobiliariaException("ERRO: Imóvel não existe em catálogo.");
        }
        compra.add(new ValorImovel(getImovel(codigo), preco));
    }
    
    private Cliente getClientePorCpf(String cpf)
    {
        for(Cliente cliente : clientes){
            if(cliente.getCpf().equals(cpf)){
                return cliente;
            }
        }
        return null;
    }
    
    private Cliente getCliente(int codigo)
    {
        for(Cliente cliente:clientes){
            if(cliente.getNumeroCadastro() == codigo){
                return cliente;
            }
        }
        return null;
    }
    
    public void realizarVendaImovel(int codigoImovel, int codigoCliente, Date data, double preco)
    {
        for(ValorImovel venda : compra){
            if(venda.getImovel().getCodigo() == codigoImovel){
               jaComprado.add(new CompraImovel(venda.getImovel(), data, getCliente(codigoCliente), preco));
            }
        }
    }
    
    public void realizarLocacaoImovel(int codigoImovel, int codigoCliente , Date dataIni, Date dataFim, double preco)
    {
        for(ValorImovel locacao : aluga){
            if(locacao.getImovel().getCodigo() == codigoImovel){
                jaAlugado.add(new LocacaoImovel(locacao.getImovel(), getCliente(codigoCliente), preco, dataIni, dataFim));
            }
        }
    }
    
    public boolean existeEmCatalogo(int codigo)
    {
        for(Imovel navegar:catalogo){
            if(navegar.getCodigo() == codigo){
                return true;
            }
        }
        return false;
    }
    
    public boolean existeEmVenda(int codigo)
    {
        for(ValorImovel navegar:compra){
            if(navegar.getImovel().getCodigo() == codigo){
                return true;
            }
        }
        return false;
    }
    
    public boolean existeEmLocacao(int codigo)
    {
        for(ValorImovel navegar : aluga){
            if(navegar.getImovel().getCodigo() == codigo){
                return true;
            }
        }
        return false;
    }
    
    public boolean existeCliente(String cpf)
    {
        return getClientePorCpf(cpf) != null;
    }
    
    public void excluirImovel(Imovel imovel) throws ImobiliariaException
    {
        if(jaVendido(imovel.getCodigo()) || jaAlugado(imovel.getCodigo())){
            throw new ImobiliariaException("ERRO: Não é possível excluir um imóvel que já esteja vinculado a uma venda ou locação.");
        }
        
        if(existeEmCatalogo(imovel.getCodigo())){
            throw new ImobiliariaException("ERRO: Imóvel não existe em catálogo.");
        }
        for(Imovel navegar : catalogo){
            if(navegar.equals(imovel)){
                catalogo.remove(imovel);
            }
        }
    }
    
    // Sobrecarga de função para possibilitar que um imóvel seja removido pelo seu código.
    public void excluirImovel(int codigo) throws ImobiliariaException
    {
        this.excluirImovel(getImovel(codigo));
    }

    private boolean jaVendido(int codigo)
    {
        for(ValorImovel navegar : compra){
            if(navegar.getImovel().getCodigo() == codigo){
                return true;
            }
        }
        return false;
    }
    
    private boolean jaAlugado(int codigo)
    {
        for(ValorImovel navegar : aluga){
            if(navegar.getImovel().getCodigo() == codigo){
                return true;
            }
        }
        return false;
    }
    
    private boolean clienteJaComprou(int codigo)
    {
        for(CompraImovel navegar : jaComprado){
            if(navegar.getCliente().getNumeroCadastro() == codigo){
                return true;
            }
        }
        return false;
    }
    
    private boolean clienteJaAlugou(int codigo) 
    {
        for(LocacaoImovel navegar : jaAlugado){
            if(navegar.getInquilino().getNumeroCadastro() == codigo){
                return true;
            }
        }
        return false;
    }
    
    public void excluirCliente(int codigo) throws ImobiliariaException
    {
        if(clienteJaAlugou(codigo) || clienteJaComprou(codigo)){
            throw new ImobiliariaException("ERRO: Não é possível excluir um cliente que já esteja vinculado a uma venda ou locação. ");
        }
        
        if(getCliente(codigo) == null){
            throw new ImobiliariaException("ERRO: Clinte não existe. ");
        }
        for(Cliente remover : clientes){
            if(remover.getNumeroCadastro() == codigo){
                clientes.remove(remover);
            }
        }
    }
}