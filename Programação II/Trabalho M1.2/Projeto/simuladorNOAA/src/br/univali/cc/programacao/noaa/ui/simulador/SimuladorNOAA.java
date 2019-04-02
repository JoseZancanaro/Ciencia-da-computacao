package br.univali.cc.programacao.noaa.ui.simulador;

import java.io.IOException;
import javafx.application.Application;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

public class SimuladorNOAA extends Application 
{
    
    public void setup(Stage primaryStage)
    {
        try {
            primaryStage.setTitle(NOAAConfig.TITULO);
            primaryStage.getIcons().add(new Image(NOAAConfig.ICONE_SISTEMA));
            FXMLLoader loader = new FXMLLoader(getClass().getResource(NOAAConfig.CAMINHO_VIEW + "SimuladorNOAAView.fxml"));
            Parent raiz = loader.load();
            Scene scene = new Scene(raiz, NOAAConfig.DIMENSAO.getWidth(), NOAAConfig.DIMENSAO.getHeight());
            primaryStage.setScene(scene);
            primaryStage.show();
        }
        catch(IOException ex){
            System.out.println(ex);
        }
    }
    
    @Override
    public void start(Stage primaryStage) 
    { 
        setup(primaryStage);
    }
    
    public static void main(String[] args) 
    {
        launch(args);
    }
}
