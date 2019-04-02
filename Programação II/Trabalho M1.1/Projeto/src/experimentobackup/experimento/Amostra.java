package experimentobackup.experimento;

public class Amostra
{
    private String arquivo;
    private int tamanho;

    public Amostra(String arquivo, int tamanho)
    {
        this.arquivo = arquivo;
        this.tamanho = tamanho;
    }

    public String getArquivo()
    {
        return arquivo;
    }
    
    public int getTamanho()
    {
        return tamanho;
    }
}
