package matjogo.dominio;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;
import matjogo.dominio.logger.Log;
import matjogo.dominio.logger.LoggerPadrao;

public class Jogador 
{    
    // Identificação
    private int id;
    private String nome;
    private Image avatar;
    
    // Tabuleiro de referência
    private Tabuleiro tabuleiro;
    
    // Localização na trilha
    private Posicao posicaoAtual;
    
    // Estatística
    private int qtdJogadas;
    private int acertos;
    private int erros;
    
    // Estrutura de sorteio
    private Dado dado;

    public Jogador(int id, String nome, Image avatar) 
    {
        this.id = id;
        this.dado = new Dado(1,6);
        this.nome = nome;
        this.avatar = avatar;
    }
    
    public int realizarMovimento() 
    {
        int sorte = this.dado.jogar();
        
        LoggerPadrao.get().log(Log.criar("Sorteio", "fx-dado", String.format("%s sorteou o número %d.", this.getNome(), sorte), this.getAvatar()));
        
        return sorte;
    }
    
    public boolean moverPara(Posicao destino)
    {
        if (!this.getPosicaoAtual().equals(destino) && destino.adicionarJogador(this)) {
            
            LoggerPadrao.get().log(
                    new Log("Movimentação", "fx",
                            String.format("%s moveu de %d para %d.", this.getNome(),
                                    this.getPosicaoAtual().getId(), destino.getId()), this.getAvatar()));
            
            this.getPosicaoAtual().removerJogador(this);
            this.setPosicaoAtual(destino);
            return true;
        }
        return false;
    }
    
    public void desenhar(double x, double y, double largura, double altura, GraphicsContext gc)
    {
        gc.drawImage(this.getAvatar(), x, y, largura, altura);
    }

    public int getId()
    {
        return this.id;
    }

    public String getNome()
    {
        return this.nome;
    }

    public Posicao getPosicaoAtual()
    {
        return this.posicaoAtual;
    }
    
    public void setPosicaoAtual(Posicao posicao)
    {
        this.posicaoAtual = posicao;
    }

    public int getQtdJogadas()
    {
        return this.qtdJogadas;
    }

    public int getAcertos()
    {
        return this.acertos;
    }

    public int getErros()
    {
        return this.erros;
    }

    public Tabuleiro getTabuleiro()
    {
        return tabuleiro;
    }

    public void setTabuleiro(Tabuleiro tabuleiro)
    {
        this.tabuleiro = tabuleiro;
    }

    public Image getAvatar()
    {
        return avatar;
    }
}
