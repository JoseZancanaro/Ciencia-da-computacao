package fuzzy.model.assets;

import java.time.LocalDateTime;

public class Postagem
{
    private final int id;
    private final int idAutor;
    private final String texto;
    private final ImagemFuzzy imagem;
    private final LocalDateTime data;

    public Postagem(int id, int idAutor, String texto, ImagemFuzzy imagem, LocalDateTime data)
    {
        this.id = id;
        this.idAutor = idAutor;
        this.texto = texto;
        this.imagem = imagem;
        this.data = data;
    }
    
    public Postagem(int idAutor, String texto, ImagemFuzzy imagem, LocalDateTime data)
    {
        this.id = 0;
        this.idAutor = idAutor;
        this.texto = texto;
        this.imagem = imagem;
        this.data = data;
    }

    public int getId()
    {
        return id;
    }

    public int getIdAutor()
    {
        return idAutor;
    }

    public String getTexto()
    {
        return texto;
    }

    public ImagemFuzzy getImagem()
    {
        return imagem;
    }

    public LocalDateTime getData()
    {
        return data;
    }
    
    public boolean equals(Postagem outra)
    {
        return this.getId() == outra.getId();
    }
}
