package fuzzy.model.cliente;

import com.google.gson.JsonObject;
import fuzzy.model.assets.ImagemFuzzy;
import fuzzy.model.assets.Postagem;
import fuzzy.model.assets.RedeFuzzy;
import fuzzy.model.assets.Usuario;
import fuzzy.model.cliente.listener.ClienteListener;
import fuzzy.model.cliente.listener.ClienteListenerAdapter;
import fuzzy.model.comunicacao.Protocolo;
import fuzzy.model.comunicacao.deserializador.Deserializador;
import fuzzy.model.comunicacao.serializador.Serializador;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.rmi.UnexpectedException;
import java.time.LocalDateTime;
import java.util.List;

public class ClienteFuzzy
{
    private final Socket servidor;
    
    private final BufferedReader entrada;
    private final PrintWriter saida;
    
    private final Serializador serializador;
    private final Deserializador deserializador;
    
    private ClienteListener listener = new ClienteListenerAdapter();

    public ClienteFuzzy(Socket servidor) throws Exception
    {
        this.servidor = servidor;
        this.entrada = new BufferedReader(new InputStreamReader(servidor.getInputStream()));
        this.saida = new PrintWriter(servidor.getOutputStream(), true);
        this.serializador = Protocolo.getSerializador();
        this.deserializador = Protocolo.getDeserializador();
    }

    public ClienteFuzzy(String hospedeiro, int porta) throws Exception
    {
        this.servidor = new Socket(hospedeiro, porta);
        this.entrada = new BufferedReader(new InputStreamReader(servidor.getInputStream()));
        this.saida = new PrintWriter(servidor.getOutputStream(), true);
        this.serializador = Protocolo.getSerializador();
        this.deserializador = Protocolo.getDeserializador();
    }
    
    public List<Usuario> solicitarUsuarios() throws IOException
    {
        String solicitacao = serializador.serializarConsulta("usuarios", "all").toString();
        
        this.saida.println(solicitacao);
        this.aguardarResposta();
        
        JsonObject raiz = serializador.regularizar(entrada.readLine());
        
        this.verificarErro(raiz);
        
        return deserializador.deserializarConsultaUsuarios(raiz);
    }
    
    public List<Postagem> solicitarPostagens() throws IOException
    {
        String solicitacao = serializador.serializarConsulta("postagens", "all").toString();
        
        this.saida.println(solicitacao);
        this.aguardarResposta();
        
        JsonObject raiz = serializador.regularizar(entrada.readLine());
        
        this.verificarErro(raiz);
        
        return deserializador.deserializarConsultaPostagens(raiz);
    }
    
    public boolean inserirUsuario(Usuario usuario) throws IOException
    {
        String solicitacao = serializador.serializarInsercao("usuario", serializador.serializarUsuario(usuario)).toString();
        
        this.saida.println(solicitacao);
        this.aguardarResposta();
        
        JsonObject raiz = serializador.regularizar(entrada.readLine());
        
        this.verificarErro(raiz);
        
        listener.usuarioInserido();
        
        return raiz.getAsJsonObject("parametros").get("realizou").getAsBoolean();
    }
    
    public boolean inserirPostagem(Postagem postagem) throws IOException
    {
        String solicitacao = serializador.serializarInsercao("postagem", serializador.serializarPostagem(postagem)).toString();
        
        this.saida.println(solicitacao);
        this.aguardarResposta();
        
        JsonObject raiz = serializador.regularizar(entrada.readLine());
        
        this.verificarErro(raiz);
        
        listener.postagemInserida();
        
        return raiz.getAsJsonObject("parametros").get("realizou").getAsBoolean();
    }
    
    public boolean removerUsuario(Usuario usuario) throws IOException
    {
        String solicitacao = serializador.serializarRemocao("usuario", serializador.serializarUsuario(usuario)).toString();
        
        this.saida.println(solicitacao);
        this.aguardarResposta();
        
        JsonObject raiz = serializador.regularizar(entrada.readLine());
        
        this.verificarErro(raiz);
        
        listener.usuarioRemovido();
        
        return raiz.getAsJsonObject("parametros").get("realizou").getAsBoolean();
    }
    
    public boolean removerPostagem(Postagem postagem) throws IOException
    {
        String solicitacao = serializador.serializarRemocao("postagem", serializador.serializarPostagem(postagem)).toString();
        
        this.saida.println(solicitacao);
        this.aguardarResposta();
        
        JsonObject raiz = serializador.regularizar(entrada.readLine());
        
        this.verificarErro(raiz);
        
        listener.postagemRemovida();
        
        return raiz.getAsJsonObject("parametros").get("realizou").getAsBoolean();
    }
    
    private void verificarErro(JsonObject raiz) throws UnexpectedException
    {
        if (raiz.get("retorno").getAsString().equalsIgnoreCase("erro")) {
            System.out.println(raiz.toString());
            throw new UnexpectedException(raiz.getAsJsonObject("parametros").get("mensagem").getAsString());
        }
    }
    
    public void setListener(ClienteListener listener)
    {
        this.listener = listener;
    }
    
    public RedeFuzzy getRedeFuzzy() throws IOException
    {
        return new RedeFuzzy(this.solicitarUsuarios(), this.solicitarPostagens());
    }
    
    private void aguardarResposta() throws IOException
    {
        while (!entrada.ready()) {} // o.O
    }
    
    public static void main(String[] args) throws Exception
    {
        ClienteFuzzy sf = new ClienteFuzzy("localhost", 2048);
        
        Usuario is = new Usuario(1, "Israel Efraim", new ImagemFuzzy("/home/efraim/Downloads/pp2.jpg"));
        Usuario ze = new Usuario(2, "José Zancanaro", new ImagemFuzzy("/home/efraim/Downloads/pp.jpg"));
        
        // Postagem postagemIs = new Postagem(1, "Cara, to com fome e sono!", new ImagemFuzzy("/home/efraim/Downloads/pp2.jpg"), LocalDateTime.now());
        Postagem postagemZe = new Postagem(2, "Cara, to lagando.", new ImagemFuzzy("/home/efraim/Documents/CC/fuzzy.me/FuzzyMeFX/src/fuzzy/gui/cliente/view/assets/image/pp4.png"), LocalDateTime.now());
        
        // System.out.println(sf.inserirPostagem(postagemIs));
        System.out.println(sf.inserirPostagem(postagemZe));
    }
    
}
