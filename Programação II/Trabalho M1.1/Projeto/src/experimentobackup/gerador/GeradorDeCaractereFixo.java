package experimentobackup.gerador;

public class GeradorDeCaractereFixo implements IGeradorDeCaractere
{
    private int caractere;
    
    public GeradorDeCaractereFixo(int caractereAscii)
    {
        this.setCaractere(caractereAscii);
    }
    
    public void setCaractere(int caractereAscii)
    {
        this.caractere = caractereAscii;
    }
    
    public int proximo()
    {
        return this.caractere;
    }    
}
