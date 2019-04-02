package fuzzy.model.assets;

public class Usuario
{
    private final int id;
    private final String nome;
    private final String senha;
    private final ImagemFuzzy foto;
    
    public Usuario(String nome, String senha, ImagemFuzzy foto)
    {
        this.id = 0;
        this.nome = nome;
        this.senha = senha;
        this.foto = foto;
    }

    public Usuario(int id, String nome, ImagemFuzzy foto)
    {
        this.id = id;
        this.nome = nome;
        this.senha = "";
        this.foto = foto;
    }
    
    public Usuario(int id, String nome, String senha, ImagemFuzzy foto)
    {
        this.id = id;
        this.nome = nome;
        this.senha = senha;
        this.foto = foto;
    }
    
    public int getId()
    {
        return id;
    }

    public String getNome()
    {
        return this.nome;
    }

    public String getSenha()
    {
        return this.senha;
    }

    public ImagemFuzzy getFoto()
    {
        return this.foto;
    }
    
    public boolean equals(Usuario outro)
    {
        return this.getId() == outro.getId();
    }
}
