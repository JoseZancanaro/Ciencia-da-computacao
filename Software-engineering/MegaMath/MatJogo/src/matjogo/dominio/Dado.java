package matjogo.dominio;

import java.util.Random;

public class Dado 
{
    // Intervalo de sorteio de valores
    private int min;
    private int max;
    private Random r;
    
    public Dado(int min, int max) 
    {
        this.min = min;
        this.max = max;
        this.r = new Random();
    }
      
    public int jogar()
    { 
        return r.nextInt(this.getMax() - this.getMin() + 1) + this.getMin();
    }

    public int getMin()
    {
        return this.min;
    }

    public int getMax()
    {
        return this.max;
    }
}
