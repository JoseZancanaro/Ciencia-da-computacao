package br.univali.cc.programacao.noaa.ui.gerenciador;

import br.univali.cc.programacao.noaa.ui.gerenciador.control.AplicacaoNOAAController;
import br.univali.cc.programacao.noaa.ui.model.Alerta;
import java.io.IOException;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.image.Image;
import javafx.stage.Stage;

/**
 * 
 * @author Israel Efraim de Oliveira
 * @author José Carlos Zancanaro
 */
public class AplicacaoNOAA extends Application
{   
    /* Controladores */
    private AplicacaoNOAAController controladorPrincipal;
    /* Controladores */
    
    /* Eventos */
    private void setupEventos(Stage stage)
    {
        stage.setOnCloseRequest(e -> NOAADaemon.getInstancia().fecharTudo()); // Daemon = serviço de background
    }
    /* Eventos */
    
    /* Inicialização */
    public void setup(Stage stage)
    {
        try {
            stage.setTitle(NOAAConfig.TITULO);
            stage.getIcons().add(new Image(NOAAConfig.ICONE_SISTEMA));
                        
            FXMLLoader loader = new FXMLLoader(getClass().getResource(NOAAConfig.CAMINHO_VIEW + "AplicacaoNOAAView.fxml"));
            controladorPrincipal = loader.getController();
            
            Parent raiz =  loader.load();
            Scene scene = new Scene(raiz, NOAAConfig.DIMENSAO.getWidth(), NOAAConfig.DIMENSAO.getHeight());
            stage.setScene(scene);
            
            setupEventos(stage);
            
            stage.show();
        }
        catch (IOException ex) {
            Alerta.mostrar("Erro irrecuperável", "Não foi possível carregar a UI base.\n" + ex.getMessage(), Alert.AlertType.ERROR);
        }
    }
    
    @Override
    public void start(Stage stage)
    {
        this.setup(stage);
    }
    /* Inicialização */

    public static void main(String[] args)
    {
        launch(args);
    }
}