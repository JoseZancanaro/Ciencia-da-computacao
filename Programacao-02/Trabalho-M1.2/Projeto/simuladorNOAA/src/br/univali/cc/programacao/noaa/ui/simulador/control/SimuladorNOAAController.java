package br.univali.cc.programacao.noaa.ui.simulador.control;

import br.univali.cc.programacao.noaa.ui.simulador.NOAAConfig;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;

public class SimuladorNOAAController implements Initializable
{
    
    /* Menu Lateral */
    @FXML
    private BorderPane borderPane;
    
    @FXML
    private HBox bInicio;
    
    @FXML
    private HBox bOndografos;
    
    @FXML
    private HBox bSatelites;
    /* Menu Lateral */
    
    /* Controladores e Views */
    private BorderPane inicioView;
    
    private BorderPane ondografosView;
    
    private BorderPane satelitesView;
    /* Controladores e Views */
    
    @Override
    public void initialize(URL location, ResourceBundle resources)
    {
        try{
            setupEventos();
            carregarViews();
            definirView(inicioView);
        }
        catch(IOException ex){
            System.out.println(ex);
        }
        
    }
    
    private void setupEventos()
    {
        bInicio.setOnMouseClicked(e -> definirView(inicioView));
        
        bOndografos.setOnMouseClicked(e -> definirView(ondografosView));
        
        bSatelites.setOnMouseClicked(e -> definirView(satelitesView));
    }
    
    private void carregarViews() throws IOException
    {
        carregarInicioView();
        carregarOndografosView();
        carregarSatelitesView();
    }
    
    private void carregarInicioView() throws IOException
    {
        FXMLLoader loader = new FXMLLoader(getClass().getResource(NOAAConfig.CAMINHO_VIEW + "InicioView.fxml"));
        inicioView = loader.load();
    }
    
    private void carregarOndografosView() throws IOException
    {
        FXMLLoader loader = new FXMLLoader(getClass().getResource(NOAAConfig.CAMINHO_VIEW + "OndografosView.fxml"));
        ondografosView = loader.load();
    }
    
    private void carregarSatelitesView() throws IOException
    {
        FXMLLoader loader = new FXMLLoader(getClass().getResource(NOAAConfig.CAMINHO_VIEW + "SatelitesView.fxml"));
        satelitesView = loader.load();
    }
    
    private void definirView(BorderPane view)
    {
        borderPane.setCenter(view);
    }
}
