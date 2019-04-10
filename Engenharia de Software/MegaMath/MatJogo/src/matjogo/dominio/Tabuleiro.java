package matjogo.dominio;

import java.util.ArrayList;
import java.util.function.Consumer;
import matjogo.dominio.logger.Log;
import matjogo.dominio.logger.LoggerPadrao;

public class Tabuleiro
{
    // Principal aspecto do Jogo
    private final ArrayList<Posicao> trilha;
    private final ArrayList<Jogador> jogadores;
    private final Consumer<Jogador> onAtualizarJogador;
    
    // Posições
    private Posicao largada;
    private Posicao chegada;
    
    // Ponteiro para lembrar o jogador de respectiva rodada
    private Jogador jogadorAtual;
    
    // Memórias de estado
    private int rodada;
    private int atual;

    public Tabuleiro(ArrayList<Posicao> trilha, ArrayList<Jogador> jogadores, Consumer<Jogador> onAtualizarJogador)
    {
        this.trilha = trilha;
        this.jogadores = jogadores;
        this.onAtualizarJogador = onAtualizarJogador;
        
        // Definir situação da trilha
        this.setLargada(this.getTrilha().stream().findFirst().get());
        this.setChegada(this.getTrilha().get(this.getTrilha().size() - 1));
        
        // Definir tabuleiro atual dos jogadores.
        this.getJogadores().forEach((j) -> {
            this.getLargada().adicionarJogador(j);
            j.setPosicaoAtual(largada);
            j.setTabuleiro(this);
            
            LoggerPadrao.get().log(new Log("Jogador adicionado!", "fx",  "O nome dele é " + j.getNome() + ".", j.getAvatar()));
        });
        this.setJogadorAtual(jogadores.stream().findFirst().get());
        
        // Definir situação do jogo
        this.rodada = 0;
        this.atual = 0;
    }
    
    public void proximaRodada()
    {
        this.setJogadorAtual(++this.atual);
    }
    
    public void efetuarMovimento()
    {
        if (this.getChegada().getJogadores().size() == this.getJogadores().size()) {
            LoggerPadrao.get().log(
                    Log.criar("Fim de jogo", "fx-endgame",
                            String.format("O jogador %s venceu!!!", this.getChegada().getJogadores().stream().findFirst().get().getNome()), null));
        }
        else {
            this.jogadorAtual.moverPara(
                    this.getPosicao(this.getJogadorAtual().getPosicaoAtual().getId()
                                     + this.getJogadorAtual().realizarMovimento())
            );
            this.proximaRodada();
        }
       
    }
    
    public Posicao getPosicao(int id)
    {
        id = id < 0 ? 0 : (id >= this.getTrilha().size() ? this.getTrilha().size() - 1: id);
        return this.getTrilha().get(id);
    }
    
    public void desenhar()
    {
        trilha.forEach((p) -> {
            p.desenhar();
        });
    }

    public ArrayList<Posicao> getTrilha()
    {
        return this.trilha;
    }

    public ArrayList<Jogador> getJogadores()
    {
        return this.jogadores;
    }

    public Jogador getJogadorAtual()
    {
        return this.jogadorAtual;
    }
    
    public void setJogadorAtual(int id)
    {
        this.atual = id % this.getJogadores().size();
        this.setJogadorAtual(this.getJogadores().get(this.atual));
    }
    
    public void setJogadorAtual(Jogador jogadorAtual)
    {
        this.jogadorAtual = jogadorAtual;
        this.onAtualizarJogador.accept(jogadorAtual);
    }

    public int getRodada()
    {
        return this.rodada;
    }

    public int getAtual()
    {
        return this.atual;
    }

    public Posicao getLargada()
    {
        return largada;
    }

    private void setLargada(Posicao largada)
    {
        this.largada = largada;
    }

    public Posicao getChegada()
    {
        return chegada;
    }

    private void setChegada(Posicao chegada)
    {
        this.chegada = chegada;
    }
}
