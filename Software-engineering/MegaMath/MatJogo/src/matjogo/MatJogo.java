/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package matjogo;

import com.jfoenix.controls.JFXButton;
import java.io.IOException;
import java.util.ArrayList;
import javafx.application.Application;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import matjogo.dominio.Jogador;
import matjogo.dominio.JogadoresSimpleFactory;
import matjogo.dominio.Posicao;
import matjogo.dominio.Tabuleiro;
import matjogo.dominio.TrilhaSimplesFactory;
import matjogo.dominio.control.FXLog;
import matjogo.dominio.logger.Log;
import matjogo.dominio.logger.LoggerPadrao;

public class MatJogo extends Application {
    
    @FXML
    private Parent parent;
    
    @FXML
    private Canvas canvas;
    private GraphicsContext gc;
    
    private double gcInicioY;
    private double gcTamanhoBase;
    private double gcTamanhoLado;
    
    @FXML
    private VBox feed;
    
    @FXML
    private ImageView ivJogador;
    
    @FXML
    private Text tJogador;
    
    @FXML
    private JFXButton btJogar;
    
    // Jogo
    private Tabuleiro tabuleiro;
    private ArrayList<Jogador> jogadores;
    
    // Chamada somente após inicialização da UI!
    public void loadJogo()
    {
        ArrayList<Posicao> trilha = TrilhaSimplesFactory.criar(
                50, this.gcInicioY, this.gcTamanhoBase, this.gcTamanhoLado, 4, 4, 3, gc);
        
        this.jogadores = JogadoresSimpleFactory.criar();
        
        this.tabuleiro = new Tabuleiro(trilha, jogadores, (Jogador j) -> {
            this.ivJogador.setImage(j.getAvatar());
            this.tJogador.setText(j.getNome());
        });
        
        this.btJogar.setOnAction((e) -> {
            this.tabuleiro.efetuarMovimento();
        });
        
        this.tabuleiro.desenhar();
    }
    
    public void loadComponentes() throws IOException
    {
        // Carregar view
        FXMLLoader loaderBot = new FXMLLoader(getClass().getResource("/matjogo/view/MainView.fxml"));
        loaderBot.setController(this);
        this.parent = loaderBot.load(); // componentes carregados
            
        // Definir componentes auxiliares
        this.gc = canvas.getGraphicsContext2D();
        
        // Definir limites gráficos do canvas
        this.gcInicioY = canvas.getHeight() * 0.175;
        this.gcTamanhoBase = canvas.getWidth() * 0.0833333333;
        this.gcTamanhoLado = canvas.getHeight() * 0.125;
    }
    
    public void loadUI(Stage primaryStage) throws IOException
    {
        this.loadComponentes();
        Scene scene = new Scene(parent, 1200, 690);
        primaryStage.setTitle("MegaMath!");
        primaryStage.getIcons().add(new Image("/matjogo/view/assets/img/logo.png"));
        primaryStage.setScene(scene);
    }
    
    public void load(Stage primaryStage) throws IOException
    {
        LoggerPadrao.set((Log log) -> {
            this.feed.getChildren().add(0, new FXLog(log));
        });
        
        this.loadUI(primaryStage);
        this.loadJogo();
    }
    
    @Override
    public void start(Stage primaryStage)
    {
        try {
            this.load(primaryStage);
            primaryStage.show();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public static void main(String[] args)
    {
        launch(args);
    }
}
