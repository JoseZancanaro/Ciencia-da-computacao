package matjogo.dominio;

import java.util.Scanner;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.TextInputDialog;
import javafx.scene.paint.Color;
import matjogo.dominio.logger.Log;
import matjogo.dominio.logger.LoggerPadrao;

public class PosicaoExpressao extends Posicao
{
    private OperatorType operator;

    public PosicaoExpressao(OperatorType operator, int id, double x, double y, double largura, double altura, int capacidade, double margem, double borda, GraphicsContext gc)
    {
        super(id, x, y, largura, altura, capacidade, margem, borda, gc);
        this.operator = operator;
    }
    
    @Override
    public boolean adicionarJogador(Jogador jogador)
    {
        if (this.solicitarEntrada()) {
            boolean adicionou = this.getJogadores().add(jogador);
            
            if (adicionou)
                this.desenhar();
            
            return adicionou;
        }
        return false;
    }
    
    @Override
    public void desenhar()
    {
        this.desenharCustomizado(Color.LIGHTCYAN, Color.DARKGRAY);
        this.desenharJogadores();
    }
    
    private boolean solicitarEntrada()
    {
        try {
            Dado dado = new Dado(1, 25);
            
            double l = dado.jogar();
            double r = dado.jogar();
            
            TextInputDialog tid = new TextInputDialog("0");
            tid.setTitle("Expressão");
            tid.setContentText("Para permanecer nesta posição, responda a seguinte expressão:\n" +
                                l + this.getOperator().getCaractere() + r);
            
            double numerico = Double.parseDouble(tid.showAndWait().get());
            
            if (!(this.getOperator().getOperacao().apply(l, r) == numerico))
                throw new Exception("Errou");
            
            return true;
        }
        catch (Exception ex) {}
        
        LoggerPadrao.get().log(
                    Log.criar("Você errou, sinto muito!", "fx-error",
                            String.format("Você não foi capaz de acertar a expressão, que pena! =("), null));
        
        return false;
    }
    
    public OperatorType getOperator()
    {
        return this.operator;
    }
    
    public String tipo()
    {
        return "expression";
    }
}
