package experimentobackup.gerador;

import java.util.Random;

public class GeradorDeCaractereAleatorio implements IGeradorDeCaractere
{
    private Random rng;

    public GeradorDeCaractereAleatorio()
    {
        this.rng = new Random();
    }
    
    public int proximo()
    {
        return rng.nextInt(256);
    }
}
