package matjogo.dominio;

import java.util.ArrayList;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;

public class Posicao 
{
    // Indice da posição na trilha
    private final int id;

    // Posição 2D
    private final double x;
    private final double y;
    
    // Dimensões
    private final double largura;
    private final double altura;
    
    // Máximo de jogadores permitidos
    private final int capacidade;
    
    // Espaço entre a borda e o desenho dos jogadores
    private final double margem;
    
    // Borda do desenho
    private final double borda;
    
    // Lista de jogadores
    private final ArrayList<Jogador> jogadores;
    
    // Canvas
    private final GraphicsContext gc;

    public Posicao(int id, double x, double y, double largura, double altura, int capacidade, double margem, double borda, GraphicsContext gc)
    {
        this.id = id;
        this.x = x;
        this.y = y;
        this.largura = largura;
        this.altura = altura;
        this.capacidade = capacidade;
        this.margem = margem;
        this.borda = borda;
        this.gc = gc;
        this.jogadores = new ArrayList(this.capacidade);
    }
    
    // José
    // Se override: Esta função É RESPONSÁVEL POR RENDERIZAR a inclusão.
    // Lembre-se de sempre chamar a função de jogador.
    public boolean adicionarJogador(Jogador jogador)
    {
        boolean adicionou = getJogadores().add(jogador);
        
        if (adicionou)
            this.desenhar();
        
        return adicionou;
    }
    
    public boolean removerJogador(Jogador jogador)
    {
        boolean removeu = getJogadores().remove(jogador);
        
        if (removeu)
            this.desenhar();
        
        return removeu;
    }
    
    protected void desenharCustomizado(Paint preenchimento, Paint borda)
    {
        // Salvar tinta atual
        Paint p = this.getGc().getFill();
        
        this.getGc().setFill(borda);
        this.getGc().fillRect(this.getX(), this.getY(),
                this.getLargura() + this.getBorda() * 2, this.getAltura() + this.getBorda() * 2);
        
        this.getGc().setFill(preenchimento);
        this.getGc().fillRect(this.getX() + this.getBorda(), this.getY() + this.getBorda(),
                this.getLargura(), this.getAltura());
        
        // Redefinir tinta
        this.getGc().setFill(p);
    }
    
            
    public void desenhar()
    {
        this.desenharCustomizado(Color.LIGHTGRAY, Color.DARKGRAY);
        this.desenharJogadores();
    }
    
    protected void desenharJogadores()
    {
        double esquerda = this.getX() + this.getBorda();
        double topo = this.getY() + this.getBorda();
        
        double largJogador = this.getLargura() * 0.4;
        double altJogador = this.getAltura() * 0.4;
        
        double x = esquerda + this.getLargura() * 0.25 - (largJogador / 2);
        double y = topo + margem;
        
        double xi = x;
        double yi = y;
        
        for (int i = 0; i < 2 && i < this.getJogadores().size(); i++) {
            this.getJogadores().get(i).desenhar(xi, yi, largJogador, altJogador, gc);
            xi += largJogador + margem;
        }
        
        xi = x;
        yi = y + altJogador + margem;
                
        for (int i = 2; i < 4 && i < this.getJogadores().size(); i++) {
            this.getJogadores().get(i).desenhar(xi, yi, largJogador, altJogador, gc);
            xi += largJogador + margem;
        }
    }

    public int getId()
    {
        return this.id;
    }

    public double getX()
    {
        return this.x;
    }

    public double getY()
    {
        return this.y;
    }

    public double getLargura()
    {
        return this.largura;
    }

    public double getAltura()
    {
        return this.altura;
    }

    public int getCapacidade()
    {
        return this.capacidade;
    }

    public double getMargem()
    {
        return this.margem;
    }
    
    public double getBorda()
    {
        return borda;
    }

    public ArrayList<Jogador> getJogadores()
    {
        return this.jogadores;
    }    

    private GraphicsContext getGc()
    {
        return gc;
    }
  
    public boolean equals(Posicao outra)
    {
        return this.getId() == outra.getId();
    }

    public String tipo()
    {
        return "Posicao normal";
    }
}
