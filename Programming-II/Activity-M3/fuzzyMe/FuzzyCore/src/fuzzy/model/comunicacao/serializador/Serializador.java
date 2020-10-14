package fuzzy.model.comunicacao.serializador;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import fuzzy.model.assets.ImagemFuzzy;
import fuzzy.model.assets.Postagem;
import fuzzy.model.assets.Usuario;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;

public class Serializador
{
    private final JsonParser jsonParser;

    public Serializador()
    {
        this.jsonParser = new JsonParser();
    }
    
    private JsonArray serializarFoto(ImagemFuzzy imagem)
    {
        JsonArray raiz = new JsonArray();
        
        InputStream is = imagem.getInputStream();
        
        try {
            int byteLido;
            while ((byteLido = is.read()) != -1) {
                raiz.add(byteLido);
            }
        } catch (IOException ignore) {}
        
        return raiz;
    }
    
    public JsonObject serializarUsuario(Usuario usuario)
    {
        JsonObject raiz = new JsonObject();
        
        raiz.addProperty("id", usuario.getId());
        raiz.addProperty("nome", usuario.getNome());
        raiz.addProperty("senha", usuario.getSenha());
        raiz.add("foto", serializarFoto(usuario.getFoto()));
        
        return raiz;
    }
    
    public JsonArray serializarUsuarios(List<Usuario> usuarios)
    {
        JsonArray lista = new JsonArray();
        
        usuarios.forEach((u) -> {
            lista.add(serializarUsuario(u));
        });
        
        return lista;
    }
    
    public JsonObject serializarPostagem(Postagem postagem)
    {
        JsonObject raiz = new JsonObject();
        
        raiz.addProperty("id", postagem.getId());
        raiz.addProperty("id_autor", postagem.getIdAutor());
        raiz.addProperty("texto", postagem.getTexto());
        raiz.add("imagem", serializarFoto(postagem.getImagem()));
        raiz.addProperty("data", postagem.getData().toString());
        
        return raiz;
    }
    
    public JsonArray serializarPostagens(List<Postagem> postagens)
    {
        JsonArray lista = new JsonArray();
        
        postagens.forEach((u) -> {
            lista.add(serializarPostagem(u));
        });
        
        return lista;
    }
    
    public JsonObject serializarConsulta(String alvo, String filtro)
    {
        JsonObject raiz = new JsonObject();
        raiz.addProperty("operacao", "get");
        
        JsonObject parametros = new JsonObject();
        parametros.addProperty("consulta", alvo);
        parametros.addProperty("filtro", filtro);
        
        raiz.add("parametros", parametros);
        
        return raiz;
    }
    
    public JsonObject serializarInsercao(String alvo, JsonObject objeto)
    {
        JsonObject raiz = new JsonObject();
        raiz.addProperty("operacao", "set");
        
        JsonObject parametros = new JsonObject();
        parametros.addProperty("tipo", "insercao");
        parametros.addProperty("alvo", alvo);
        parametros.add("valor", objeto);
        
        raiz.add("parametros", parametros);
        
        return raiz;
    }
    
    public JsonObject serializarRemocao(String alvo, JsonObject objeto)
    {
        JsonObject raiz = new JsonObject();
        raiz.addProperty("operacao", "set");
        
        JsonObject parametros = new JsonObject();
        parametros.addProperty("tipo", "remocao");
        parametros.addProperty("alvo", alvo);
        parametros.add("valor", objeto);
        
        raiz.add("parametros", parametros);
        
        return raiz;
    }
    
    public JsonObject serializarRetornoConsulta(String tipo, int quantidade, JsonArray lista)
    {
        JsonObject raiz = new JsonObject();
        raiz.addProperty("retorno", tipo);
        
        JsonObject parametros = new JsonObject();
        parametros.addProperty("quantidade", quantidade);
        parametros.add("lista", lista);
        
        raiz.add("parametros", parametros);
        
        return raiz;
    }
    
    public JsonObject serializarRetornoOperacao(String operacao, String tipo, boolean estado)
    {
        JsonObject raiz = new JsonObject();
        raiz.addProperty("retorno", operacao);
        
        JsonObject parametros = new JsonObject();
        parametros.addProperty("tipo", tipo);
        parametros.addProperty("realizou", estado);
        
        raiz.add("parametros", parametros);
        
        return raiz;
    }
    
    public JsonObject serializarRetornoProblematico(String mensagem, String causa)
    {
        JsonObject raiz = new JsonObject();
        raiz.addProperty("retorno", "erro");
        
        JsonObject parametros = new JsonObject();
        parametros.addProperty("mensagem", mensagem);
        parametros.addProperty("causa", causa);
        
        raiz.add("parametros", parametros);
        
        return raiz;
    }
    
    public JsonObject regularizar(String mensagem)
    {
        return jsonParser.parse(mensagem).getAsJsonObject();
    }
    
    public static Serializador criar()
    {
        return new Serializador();
    }
}
