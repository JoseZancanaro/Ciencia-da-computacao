package matjogo.dominio;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import matjogo.dominio.logger.Log;
import matjogo.dominio.logger.LoggerPadrao;

public class PosicaoArmadilha extends Posicao
{
    public PosicaoArmadilha(int id, double x, double y, double largura, double altura, int capacidade, double margem, double borda, GraphicsContext gc)
    {
        super(id, x, y, largura, altura, capacidade, margem, borda, gc);
    }
    
    @Override
    public boolean adicionarJogador(Jogador jogador)
    {
        if (jogador.getTabuleiro() != null) {
            Posicao armadilhado = jogador.getTabuleiro().getPosicao(this.getId() - 3);
            
            LoggerPadrao.get().log(Log.criar("Armadilha!", "fx-armadilha", jogador.getNome() + " iria para " + this.getId() + " mas foi para " + armadilhado.getId(), null));
            
            jogador.moverPara(armadilhado);
        }
        return false;
    }
    
    @Override
    public void desenhar()
    {
        this.desenharCustomizado(Color.WHITE, Color.DARKGRAY);
        this.desenharJogadores();
    }

    public String tipo()
    {
        return "trap";
    }
}
