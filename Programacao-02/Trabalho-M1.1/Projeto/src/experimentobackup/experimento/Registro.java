package experimentobackup.experimento;

public class Registro
{
    private int tamanho;
    private long tempo;

    public Registro(int tamanho, long tempo)
    {
        this.tamanho = tamanho;
        this.tempo = tempo;
    }
    
    public int getTamanho()
    {
        return tamanho;
    }

    public long getTempo()
    {
        return tempo;
    }
    
    @Override
    public String toString()
    {
        return String.format("%d,%d,", tamanho, tempo);
    }
}
