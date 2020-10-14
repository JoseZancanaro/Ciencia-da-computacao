package fuzzy.model.comunicacao.deserializador;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import fuzzy.model.assets.ImagemFuzzy;
import fuzzy.model.assets.Postagem;
import fuzzy.model.assets.Usuario;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Deserializador
{
    private final JsonParser jsonParser;

    public Deserializador()
    {
        this.jsonParser = new JsonParser();
    }
    
    private ImagemFuzzy deserializarFoto(JsonArray imagem)
    {
        byte[] bytes = new byte[imagem.size()];
        
        for (int i = 0; i < imagem.size(); i++)
            bytes[i] = imagem.get(i).getAsByte();
        
        return new ImagemFuzzy(bytes);
    }
    
    public Usuario deserializarUsuario(JsonObject raiz)
    {
        Usuario usuario = new Usuario(raiz.get("id").getAsInt(), raiz.get("nome").getAsString(),
                                raiz.get("senha").getAsString(), deserializarFoto(raiz.get("foto").getAsJsonArray()));
        
        return usuario;
    }
    
    public List<Usuario> deserializarUsuarios(JsonArray lista)
    {
        List<Usuario> usuarios = new ArrayList<>();
        
        lista.forEach((u) -> {
            usuarios.add(deserializarUsuario(u.getAsJsonObject()));
        });
        
        return usuarios;
    }
    
    public List<Usuario> deserializarConsultaUsuarios(JsonObject raiz)
    {
        return deserializarUsuarios(raiz.getAsJsonObject("parametros").getAsJsonArray("lista"));
    }
    
    public List<Usuario> deserializarConsultaUsuarios(String raiz)
    {
        JsonObject objeto = jsonParser.parse(raiz).getAsJsonObject();
        return deserializarConsultaUsuarios(objeto);
    }
    
    public Postagem deserializarPostagem(JsonObject raiz)
    {
        Postagem postagem = new Postagem(raiz.get("id").getAsInt(), raiz.get("id_autor").getAsInt(), raiz.get("texto").getAsString(),
                                    deserializarFoto(raiz.get("imagem").getAsJsonArray()), LocalDateTime.parse(raiz.get("data").getAsString()));
        
        return postagem;
    }
    
    public List<Postagem> deserializarPostagens(JsonArray lista)
    {
        List<Postagem> postagens = new ArrayList<>();
        
        lista.forEach((p) -> {
            postagens.add(deserializarPostagem(p.getAsJsonObject()));
        });
        
        return postagens;
    }
    
    public List<Postagem> deserializarConsultaPostagens(JsonObject raiz)
    {
        return deserializarPostagens(raiz.getAsJsonObject("parametros").getAsJsonArray("lista"));
    }
    
    public List<Postagem> deserializarConsultaPostagens(String raiz)
    {
        JsonObject objeto = jsonParser.parse(raiz).getAsJsonObject();
        return deserializarConsultaPostagens(objeto);
    }
    
    public static Deserializador criar()
    {
        return new Deserializador();
    }
}
