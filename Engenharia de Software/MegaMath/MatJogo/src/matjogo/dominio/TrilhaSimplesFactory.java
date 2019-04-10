package matjogo.dominio;

import java.util.ArrayList;
import javafx.scene.canvas.GraphicsContext;

public class TrilhaSimplesFactory
{
    private static final double factor = 1.2;
    
    public static ArrayList<Posicao> criar(double x, double y, double largura, double altura, int capacidade, double margem, double borda, GraphicsContext gc)
    {
        ArrayList<Posicao> trilha = new ArrayList();
        
        PosicaoAleatoriaFactory paf = new PosicaoAleatoriaFactory(5, 0.6, 3, 0.7);
        PosicaoBlueprint p = new PosicaoBlueprint(x, y, largura, altura, capacidade, margem, borda);
        
        trilha.add(criarPosicaoFatorada(0, p, gc));
        avancarHorizontalmente(p, true);
        
        for (int i = 1; i < 3; i++) {
            trilha.add(paf.gerar(i, p, gc));
            avancarHorizontalmente(p, false);
        }
        for (int i = 3; i < 5; i++) {
            trilha.add(paf.gerar(i, p, gc));
            avancarVerticalmente(p, false);
        }
        for (int i = 5; i < 8; i++) {
            trilha.add(paf.gerar(i, p, gc));
            regredirHorizontalmente(p);
        }
        for (int i = 8; i < 10; i++) {
            trilha.add(paf.gerar(i, p, gc));
            avancarVerticalmente(p, false);
        }
        for (int i = 10; i < 15; i++) {
            trilha.add(paf.gerar(i, p, gc));
            avancarHorizontalmente(p, false);
        }
        for (int i = 15; i < 19; i++) {
            trilha.add(paf.gerar(i, p, gc));
            regredirVerticalmente(p);
        }
        for (int i = 19; i < 23; i++) {
            trilha.add(paf.gerar(i, p, gc));
            avancarHorizontalmente(p, false);
        }
        for (int i = 23; i < 25; i++) {
            trilha.add(paf.gerar(i, p, gc));
            avancarVerticalmente(p, false);
        }
        for (int i = 25; i < 27; i++) {
            trilha.add(paf.gerar(i, p, gc));
            regredirHorizontalmente(p);
        }
        for (int i = 27; i < 29; i++) {
            trilha.add(paf.gerar(i, p, gc));
            avancarVerticalmente(p, false);
        }
        for (int i = 29; i < 31; i++) {
            trilha.add(paf.gerar(i, p, gc));
            avancarHorizontalmente(p, false);
        }
        trilha.add(criarPosicaoFatorada(31, p, gc));
        return trilha;
    }
    
    public static Posicao criarPosicao(int id, PosicaoBlueprint p, GraphicsContext gc)
    {
        return new Posicao(id, p.getX(), p.getY(), p.getLargura(), p.getAltura(),
                                    p.getCapacidade(), p.getMargem(), p.getBorda(), gc);
    }
    
    public static PosicaoBlueprint avancarHorizontalmente(PosicaoBlueprint p, boolean aposInicio)
    {
        double largura = aposInicio ? p.getLargura() * factor : p.getLargura();
        p.setX(p.getX() + largura + p.getBorda());
        return p;
    }
    
    public static PosicaoBlueprint avancarVerticalmente(PosicaoBlueprint p, boolean aposInicio)
    {
        double altura = aposInicio ? p.getAltura() * (factor / 2) : p.getAltura();
        p.setY(p.getY() + altura + p.getBorda());
        return p;
    }
    
    public static PosicaoBlueprint regredirHorizontalmente(PosicaoBlueprint p)
    {
        p.setX(p.getX() - (p.getLargura() + p.getBorda()));
        return p;
    }
    
    public static PosicaoBlueprint regredirVerticalmente(PosicaoBlueprint p)
    {
        p.setY(p.getY() - (p.getAltura() + p.getBorda()));
        return p;
    }
    
    public static Posicao criarPosicaoFatorada(int id, PosicaoBlueprint p, GraphicsContext gc)
    {
        return new Posicao(id, p.getX(), p.getY() - (p.getAltura() * factor - p.getAltura()) / 2, p.getLargura() * factor, p.getAltura() * factor,
                                    p.getCapacidade(), p.getMargem(), p.getBorda(), gc);
    }
}
