package fuzzy.model.servidor;

import com.google.gson.JsonObject;
import fuzzy.model.assets.Postagem;
import fuzzy.model.assets.Usuario;
import fuzzy.model.comunicacao.Protocolo;
import fuzzy.model.comunicacao.deserializador.Deserializador;
import fuzzy.model.comunicacao.serializador.Serializador;
import fuzzy.model.servidor.persistencia.GerenciadorDeBanco;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.sql.SQLException;
import java.util.List;

public class GerenciadorConexao implements Runnable
{
    private final Socket cliente;
    
    private final BufferedReader entrada;
    private final PrintWriter saida;
    
    private final Serializador serializador;
    private final Deserializador deserializador;
    
    private boolean finalizado;

    public GerenciadorConexao(Socket cliente) throws IOException
    {
        this.cliente = cliente;
        
        this.entrada = new BufferedReader(new InputStreamReader(cliente.getInputStream()));
        this.saida = new PrintWriter(cliente.getOutputStream(), true);
        
        this.serializador = Protocolo.getSerializador();
        this.deserializador = Protocolo.getDeserializador();
        
        this.finalizado = false;
    }
    
    @Override
    public void run()
    {
        while (!finalizado) {
            try {
                if (entrada.ready()) {
                    analisarSolicitacao(entrada.readLine());
                }
            } catch (NullPointerException | IOException ex) {
                this.finalizado = true;
            }
        }
    }
    
    private void analisarSolicitacao(String solicitacao)
    {
        try {
            analisarSolicitacao(serializador.regularizar(solicitacao));
        } catch (Exception ex) {
            responderComErro(ex);
        }
    }
    
    private void analisarSolicitacao(JsonObject solicitacao) throws Exception
    {
        String operacao = solicitacao.get("operacao").getAsString();
        
        if (operacao.equalsIgnoreCase("get")) {
            responderSolicitacaoGet(solicitacao);
        }
        else if (operacao.equalsIgnoreCase("set")) {
            responderSolicitacaoSet(solicitacao);
        }
        else {
            throw new UnsupportedOperationException("Get/Set são as únicas diretivas primárias de solicitação.");
        }
    }
    
    private void responderSolicitacaoGet(JsonObject solicitacao) throws Exception
    {
        JsonObject parametros = solicitacao.getAsJsonObject("parametros");
        
        String alvo = parametros.get("consulta").getAsString();
        String filtro = parametros.get("filtro").getAsString();
        
        if (filtro.equalsIgnoreCase("all"))
            filtro = "";
        
        if (alvo.equalsIgnoreCase("usuarios")) {
            responderConsultaUsuarios(filtro);
        }
        else if (alvo.equalsIgnoreCase("postagens")) {
            responderConsultaPostagens(filtro);
        }
        else {
            throw new UnsupportedOperationException("Usuarios/Postagens são as únicas diretivas de consulta.");
        }
    }
    
    private void responderConsultaUsuarios(String filtro) throws Exception
    {
        List<Usuario> usuarios = GerenciadorDeBanco.getInstancia().getUsuarios(filtro);
        
        this.saida.println(serializador.serializarRetornoConsulta("listaUsuarios",
                            usuarios.size(), serializador.serializarUsuarios(usuarios)));
    }
    
    private void responderConsultaPostagens(String filtro) throws ClassNotFoundException, SQLException
    {
        List<Postagem> postagens = GerenciadorDeBanco.getInstancia().getPostagens(filtro);
        
        this.saida.println(serializador.serializarRetornoConsulta("listaPostagens",
                            postagens.size(), serializador.serializarPostagens(postagens)));
    }
    
    private void responderSolicitacaoSet(JsonObject solicitacao) throws Exception
    {
        JsonObject parametros = solicitacao.getAsJsonObject("parametros");
        
        String tipo = parametros.get("tipo").getAsString();
        String alvo = parametros.get("alvo").getAsString();
        JsonObject valor = parametros.getAsJsonObject("valor");
        
        if (tipo.equalsIgnoreCase("insercao")) {
            responderSolicitacaoInsercao(alvo, valor);
        }
        else if (tipo.equalsIgnoreCase("remocao")) {
            responderSolicitacaoRemocao(alvo, valor);
        }
        else {
            throw new UnsupportedOperationException("Insercao/Remocao são as únicas diretivas de set.");
        }
    }
    
    private void responderSolicitacaoInsercao(String alvo, JsonObject valor) throws Exception
    {
        if (alvo.equalsIgnoreCase("usuario")) {
            responderSolicitacaoInsercaoUsuario(valor);
        }
        else if (alvo.equalsIgnoreCase("postagem")) {
            responderSolicitacaoInsercaoPostagem(valor);
        }
        else {
            throw new UnsupportedOperationException("Usuario/Postagem são as únicas diretivas de inserção.");
        }
    }
    
    private void responderSolicitacaoInsercaoUsuario(JsonObject valor) throws ClassNotFoundException, SQLException
    {
        Usuario usuario = deserializador.deserializarUsuario(valor);
        
        boolean inseriu = GerenciadorDeBanco.getInstancia().inserirUsuario(usuario);
        
        this.saida.println(serializador.serializarRetornoOperacao("insercao", "usuario", inseriu));
    }
    
    private void responderSolicitacaoInsercaoPostagem(JsonObject valor) throws ClassNotFoundException, SQLException
    {
        Postagem postagem = deserializador.deserializarPostagem(valor);
        
        boolean inseriu = GerenciadorDeBanco.getInstancia().inserirPostagem(postagem);
        
        this.saida.println(serializador.serializarRetornoOperacao("insercao", "postagem", inseriu));
    }
    
    private void responderSolicitacaoRemocao(String alvo, JsonObject valor) throws Exception
    {
        if (alvo.equalsIgnoreCase("usuario")) {
            responderSolicitacaoRemocaoUsuario(valor);
        }
        else if (alvo.equalsIgnoreCase("postagem")) {
            responderSolicitacaoRemocaoPostagem(valor);
        }
        else {
            throw new UnsupportedOperationException("Usuario/Postagem são as únicas diretivas de remoção.");
        }
    }
    
    private void responderSolicitacaoRemocaoUsuario(JsonObject valor) throws ClassNotFoundException, SQLException
    {
        Usuario usuario = deserializador.deserializarUsuario(valor);
        
        boolean removeu = GerenciadorDeBanco.getInstancia().removerUsuario(usuario);
        
        this.saida.println(serializador.serializarRetornoOperacao("remocao", "usuario", removeu));
    }
    
    private void responderSolicitacaoRemocaoPostagem(JsonObject valor) throws ClassNotFoundException, SQLException
    {
        Postagem postagem = deserializador.deserializarPostagem(valor);
        
        boolean removeu = GerenciadorDeBanco.getInstancia().removerPostagem(postagem);
        
        this.saida.println(serializador.serializarRetornoOperacao("remocao", "postagem", removeu));
    }
    
    private void responderComErro(Exception ex)
    {
        this.saida.println(serializador.serializarRetornoProblematico(ex.getMessage(), "GerenciadorConexao()"));
    }
    
    public void finalizar()
    {
        this.finalizado = true;
    }
}
