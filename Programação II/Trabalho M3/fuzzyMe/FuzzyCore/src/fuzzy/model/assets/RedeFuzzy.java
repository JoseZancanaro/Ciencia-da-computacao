package fuzzy.model.assets;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class RedeFuzzy
{
    private List<Usuario> usuarios;
    private List<Postagem> postagens;

    public RedeFuzzy(List<Usuario> usuarios, List<Postagem> postagens)
    {
        this.usuarios = usuarios;
        this.postagens = postagens;
    }

    public List<Usuario> getUsuarios()
    {
        return usuarios;
    }

    public List<Postagem> getPostagens()
    {
        return postagens;
    }
    
    public void setUsuarios(List<Usuario> usuarios)
    {
        this.usuarios = usuarios;
    }

    public void setPostagens(List<Postagem> postagens)
    {
        this.postagens = postagens;
    }
    
    public Optional<Usuario> quemPostou(Postagem postagem)
    {
        return this.usuarios.stream().filter((u) -> {
            return u.getId() == postagem.getIdAutor();
        }).findFirst();
    }
    
    public static RedeFuzzy copiar(RedeFuzzy outra)
    {
        return new RedeFuzzy(new ArrayList<>(outra.usuarios), new ArrayList<>(outra.postagens));
    }
}
