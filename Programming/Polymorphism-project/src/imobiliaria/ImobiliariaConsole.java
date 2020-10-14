package imobiliaria;
import imobiliaria.exceptions.ImobiliariaException;
import imobiliaria.imovel.Apartamento;
import imobiliaria.imovel.Casa;
import imobiliaria.imovel.Imovel;
import imobiliaria.imovel.SalaComercial;
import imobiliaria.imovel.Terreno;
import java.text.ParseException;
import java.util.Calendar;
import java.util.Date;
import java.util.Scanner;
import java.text.SimpleDateFormat;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Nas etapas de pedir algo para um usuário, utilizei em algumas funções uma instrução "cin.nextLine();"
 * para não dar erro de leitura.
 */

public class ImobiliariaConsole{
    
    // Constantes para escolha de opções do menu.
    private static final int OPCAO_CADASTRO_IMOVEL = 1;  
    private static final int OPCAO_IMOVEL_PARA_LOCACAO = 2;
    private static final int OPCAO_IMOVEL_PARA_VENDA = 3;
    private static final int OPCAO_VENDER_IMOVEL = 4;
    private static final int OPCAO_ALUGAR_IMOVEL = 5;
    private static final int OPCAO_LISTAR_IMOVEL = 6;
    private static final int OPCAO_CADASTRAR_CLIENTE = 7;
    private static final int OPCAO_EXCLUIR_IMOVEL = 8;
    private static final int OPCAO_EXCLUIR_CLIENTE = 9;
    
    private Scanner cin;
    private Imobiliaria imobiliaria;

    public ImobiliariaConsole()
    {
        cin = new Scanner(System.in);
        imobiliaria = new Imobiliaria("Zancanaro");
        preCadastroImoveis();
        preCadastroClientes();
    }
    
    private void preCadastroImoveis()
    {
        // Cadastro de oito imovéis, dois de cada tipo, para facilitar em testes.
        try{
            imobiliaria.cadastrarEmCatalogo(new Casa("Cinza", 5, 190.0, 1));
            imobiliaria.cadastrarEmCatalogo(new Casa("Branca", 7, 210.0, 2));
            imobiliaria.cadastrarEmCatalogo(new Apartamento(2, 59.0, 4, true, 3));
            imobiliaria.cadastrarEmCatalogo(new Apartamento(5, 90.0, 4, false, 4));
            imobiliaria.cadastrarEmCatalogo(new Terreno(250.0, "Limpo", 5));
            imobiliaria.cadastrarEmCatalogo(new Terreno(299.0, "Sujo", 6));
            imobiliaria.cadastrarEmCatalogo(new SalaComercial(25.0, false, 7));
            imobiliaria.cadastrarEmCatalogo(new SalaComercial(35.0, true, 8));
        } catch(ImobiliariaException e){
            System.out.println("Erro em teste, deu ruim.");
        }
        
    }
    
    private void preCadastroClientes()
    {
        // Cadastro de cinco clientes.
        try{
            imobiliaria.cadastrarEmClientes(new Cliente("Jose", "167765", 19, 1));
            imobiliaria.cadastrarEmClientes(new Cliente("Israel", "121273", 18, 2));
            imobiliaria.cadastrarEmClientes(new Cliente("Allan", "473976", 19, 3));
            imobiliaria.cadastrarEmClientes(new Cliente("Carlos", "546789", 30, 4));
            imobiliaria.cadastrarEmClientes(new Cliente("Geraldo", "867098", 28, 5));
        }catch(ImobiliariaException e){
            System.out.println("Erro em teste, deu ruim novamente. ");
        }
    }
    
    public void exibirEscolhas()
    {
        System.out.println("|-----------------------------------|");
        System.out.println("|-----ESCOLHA UMA OPÇÃO DESEJADA----|");
        System.out.println("|-----------------------------------|");
        System.out.println("| 1  -> Cadastro de Imóvel          |");
        System.out.println("| 2  -> Colocar Imóvel para Locação |");
        System.out.println("| 3  -> Colocar Imóvel para Venda   |");
        System.out.println("| 4  -> Vender Imóvel               |");
        System.out.println("| 5  -> Alugar Imóvel               |");
        System.out.println("| 6  -> Listagem de Imóveis         |");
        System.out.println("| 7  -> Cadastrar cliente           |");
        System.out.println("| 8  -> Excluir imóvel              |");
        System.out.println("| 9  -> Excluir cliente             |");
        System.out.println("| 10 -> Sair do programa            |");
        System.out.println("|-----------------------------------|");
    }
    
    public void definirEscolha()
    {
        int escolha;
        do{
            exibirEscolhas();
            escolha = cin.nextInt();
            switch(escolha)
            {
                case OPCAO_CADASTRO_IMOVEL:
                    cadastramentoDeImovel();
                break;
                case OPCAO_IMOVEL_PARA_LOCACAO:
                    imovelParaLocacao();
                break;
                case OPCAO_IMOVEL_PARA_VENDA:
                    imovelParaVenda();
                break;
                case OPCAO_VENDER_IMOVEL:
                    venderImovel();
                break;
                case OPCAO_ALUGAR_IMOVEL:
                    alugarImovel();
                break;
                case OPCAO_LISTAR_IMOVEL:
                    listarImovel();
                break;
                case OPCAO_CADASTRAR_CLIENTE:
                    cadastrarCliente();
                break;
                case OPCAO_EXCLUIR_IMOVEL:
                    excluirImovelConsole();
                break;
                case OPCAO_EXCLUIR_CLIENTE:
                    excluirCliente();
                break;
                case 10:
                    System.out.println("Saindo do programa...");;
                break;
            }
        }while(escolha != 10);
    }
    
    public void exibirOpcoesCadastro()
    {
        System.out.println("|-------------------------------------------|");
        System.out.println("|-INFORME O TIPO DE IMÓVEL A SER CADASTRADO-|");
        System.out.println("|-------------------------------------------|");
        System.out.println("| 1 - Casa                                  |");
        System.out.println("| 2 - Apartamento                           |");
        System.out.println("| 3 - Terreno                               |");
        System.out.println("| 4 - Sala Comercial                        |");
        System.out.println("| 5 - Voltar                                |");
        System.out.println("|-------------------------------------------|"); 
    }
    
    public void cadastrarCasa()
    {
        System.out.println("CADASTRO: CASA ");
        System.out.println("- Informe o código de cadastramento: ");
        int codigoImovel = cin.nextInt();
        cin.nextLine();
        System.out.println("- Informe a cor da casa: ");
        String cor = cin.nextLine();
        System.out.println("- Informe a quantidade de cômodos da casa: ");
        int qtdComodos = cin.nextInt();
        System.out.println("- Informe a área da casa: ");
        double area = cin.nextDouble();
       
        Imovel novaCasa = new Casa(cor, qtdComodos, area, codigoImovel);
        try {
            imobiliaria.cadastrarEmCatalogo(novaCasa);
        }catch(ImobiliariaException e){
            System.out.println(e.getMessage());
        }
        
    }
    
    public void cadastrarApartamento()
    {
        System.out.println("CADASTRO: APARTAMENTO ");
        System.out.println("- Informe o código de cadastramento: ");
        int codigoImovel = cin.nextInt();
        cin.nextLine();
        System.out.println(" - Informe o número do andar do apartamento: ");
        int numeroAndar = cin.nextInt();
        System.out.print("- Informe a área do apartamento: ");
        double area = cin.nextDouble();
        System.out.println("- Informe a quantidade de cômodos: ");
        int qtdComodos = cin.nextInt();
        System.out.println("- Informe se o apartamento contém sacada, true(sim) ou false(não): ");
        boolean contemSacada = cin.nextBoolean();
        
        Imovel novoApartamento = new Apartamento(numeroAndar, area, qtdComodos, contemSacada, codigoImovel);
        
        try {
            imobiliaria.cadastrarEmCatalogo(novoApartamento);
        } catch (ImobiliariaException e) {
            System.out.println(e.getMessage());
        }
    }
    
    public void cadastrarTerreno()
    {
        System.out.println("CADASTRO: TERRENO ");
        System.out.println("- Informe o código de cadastramento: ");
        int codigoImovel = cin.nextInt();
        cin.nextLine();
        System.out.println("- Informe a área do terreno: ");
        double area = cin.nextDouble();
        System.out.println("- Informe o estado atual do terreno: ");
        String estadoTerreno = cin.nextLine();
       
        Imovel novoTerreno = new Terreno(area, estadoTerreno, codigoImovel);
        try {
            imobiliaria.cadastrarEmCatalogo(novoTerreno);
        } catch (ImobiliariaException e) {
            System.out.println(e.getMessage());
        }
    }
    
    public void cadastrarSalaComercial()
    {
        System.out.println("CADASTRO: SALA COMERCIAL ");
        System.out.println("- Informe o código de cadastramento: ");
        int codigoImovel = cin.nextInt();
        cin.nextLine();
        System.out.println("- Informe a área da sala comercial: ");
        double area = cin.nextDouble();
        System.out.println("- Informe se a sala comercial está mobiliada, true(sim) ou false(não): ");
        boolean estaMobiliado = cin.nextBoolean();
       
        Imovel novaSalaComercial = new SalaComercial(area, estaMobiliado, codigoImovel);
        try {
            imobiliaria.cadastrarEmCatalogo(novaSalaComercial);
        } catch (ImobiliariaException e) {
            System.out.println(e.getMessage());
        }
    }
    
    public int cadastrarCliente()
    {
        
        System.out.println("CADASTRO DO CLIENTE: ");
        System.out.println("- Informe um número de cadastro para este cliente: ");
        int numero = cin.nextInt();
        cin.nextLine();
        System.out.println("- Infome o nome do cliente: ");
        String nome = cin.nextLine();
        System.out.println("- Informe o cpf do cliente: ");
        String cpf = cin.nextLine();
        System.out.println("- Infome a idade do cliente: ");
        int idade = cin.nextInt();
        
        Cliente novoCliente = new Cliente(nome, cpf, idade, numero);
        System.out.println("- Confira o como o cliente ficou cadastrado: ");
        System.out.println(novoCliente.toString());
        
        try{
            imobiliaria.cadastrarEmClientes(novoCliente);
        }catch(ImobiliariaException e){
            System.out.println(e.getMessage());
        }
        return numero;
    }
    
    public void cadastramentoDeImovel()
    {
        int escolha;
        do{
            exibirOpcoesCadastro();
            escolha = cin.nextInt();

            switch(escolha)
            {
                case 1:
                    cadastrarCasa();
                break;
                case 2:
                    cadastrarApartamento();
                break;
                case 3:
                    cadastrarTerreno();
                break;
                case 4:
                    cadastrarSalaComercial();
               break;
                case 5:
                    exibirEscolhas();
                break;
            } 
        }while(escolha != 5);
    }
    
    public void imovelParaLocacao()
    {
        System.out.println("IMÓVEL PARA LOCAÇÃO: ");
        System.out.println("- Informe o código de cadastro do imóvel: ");
        int codigo = cin.nextInt();
        System.out.println("- Informe o preço mensal de locação deste imóvel");
        double preco = cin.nextDouble();
        
        try{
            imobiliaria.cadastrarParaLocacao(codigo, preco);
        }catch(ImobiliariaException e){
            System.out.println(e.getMessage());
        }
    }
    
    public void imovelParaVenda()
    {
        System.out.println("IMÓVEL PARA VENDA: "); 
        System.out.println("- Informe o código de cadastro do imóvel");
        int codigo = cin.nextInt();
        System.out.println("- Informe o preço para compra deste imóvel: ");
        double preco = cin.nextDouble();
        
        try{
            imobiliaria.cadastrarParaCompra(codigo, preco);
        }catch(ImobiliariaException e){
            System.out.println(e.getMessage());
        }
    }
    
    public void venderImovel()
    {
        System.out.println("VENDENDO UM IMÓVEL: ");
        System.out.println("- Informe o código do imóvel a ser vendido");
        int codigo = cin.nextInt();
        
        System.out.println("- Clinte já cadastrado? true(sim) ou false(não): ");
        boolean jaCadastrado = cin.nextBoolean();
        
        int codigoCliente;
        if(jaCadastrado){
            System.out.println("- Informe o código do cliente: ");
            codigoCliente = cin.nextInt();
        }else{
            codigoCliente = cadastrarCliente();
        }
        System.out.println("- Infomre o preço de venda deste imóvel: ");
        double preco = cin.nextDouble();
        Date data =  Calendar.getInstance().getTime();
        imobiliaria.realizarVendaImovel(codigo, codigoCliente, data, preco); 
        System.out.println("- Compra finalizada, agradecemos sua preferência. ");
    }
    
    public void alugarImovel()
    {
        System.out.println("ALUGANDO UM IMÓVEL: ");
        System.out.println("- Informe o código do imóvel a ser alugado: ");
        int codigo = cin.nextInt();
       
        System.out.println("- Cliente já cadastrado? true(sim) ou false(não): ");
        boolean jaCadastrado = cin.nextBoolean();
        
        int codigoCliente;
        if(jaCadastrado){
            System.out.println("- Informe o código do cliente: ");
            codigoCliente = cin.nextInt();
        }else{
            codigoCliente = cadastrarCliente();
        }
        System.out.println("- Informe o preço de locação deste imóvel: ");
        double preco = cin.nextDouble();
        try{
            cin.nextLine();
            System.out.println("- Informe a data de Inicio da locação: ");
            Date dataIni = new SimpleDateFormat("dd/MM/yyyy", Locale.ENGLISH).parse(cin.nextLine());
            System.out.println("- Informe a data final da locação: ");
            Date dataFim = new SimpleDateFormat("dd/MM/yyyy", Locale.ENGLISH).parse(cin.nextLine());
            imobiliaria.realizarLocacaoImovel(codigo, codigoCliente, dataIni, dataFim, preco);
            System.out.println("- Locação finalizada, agradecemos sua preferência. ");
        }catch(ParseException e){
            System.out.println("ERRO: Formato de data inválido. ");
        }
    }
    
    public void listarImovel()
    {
        System.out.println("CATÁLOGO DE IMÓVEL(S):");
        for(Imovel imovel:imobiliaria.getCatalogo()){
            System.out.println(imovel.mostrarDetalhes());
        }
    }  
    
    public void excluirImovelConsole()
    {
        System.out.println("EXCLUIR UM IMÓVEL: ");
        System.out.println("- Informe o código do imóvel a ser excluído: ");
        int codigo = cin.nextInt();
        
        try{
            imobiliaria.excluirImovel(codigo);
        }catch(ImobiliariaException e){
            System.out.println(e.getMessage());
        }
    }
    
    public void excluirCliente()
    {
        System.out.println("EXCLUIR UM CLIENTE: ");
        System.out.println("- Informe o código co cliente a ser excluído: ");
        int codigo = cin.nextInt();
        
        try{
            imobiliaria.excluirCliente(codigo);
        }catch(ImobiliariaException e){
            System.out.println(e.getMessage());
        }
    }
}