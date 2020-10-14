package br.univali.cc.programacao.noaa.ui.gerenciador.control;

import br.univali.cc.programacao.noaa.ui.gerenciador.NOAAConfig;
import br.univali.cc.programacao.noaa.persistencia.GerenciadorDeBanco;
import br.univali.cc.programacao.noaa.ui.model.Alerta;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.control.Alert;
import javafx.scene.control.Label;
import javafx.scene.control.MenuItem;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Text;

public class AplicacaoNOAAController implements Initializable
{
    /* Gerenciador de layout central */
    @FXML
    private BorderPane borderPane;
    /* Gerenciador de layout central */
    
    /* Menu Superior */
    @FXML
    private MenuItem mSobreNOAA;
    /* Menu Superior */
    
    /* Menu Lateral */
    @FXML
    private ImageView imageView;
    
    @FXML
    private HBox bInicio;
    
    @FXML
    private HBox bOndografos;
    
    @FXML
    private HBox bSatelites;
    
    @FXML
    private HBox bEventosClimaticos;
    
    @FXML
    private HBox bConfiguracoes;
    /* Menu Lateral */
    
    /* Controladores e Views*/
    private AbstractNOAAController atual;
    
    /* -- Início -- */
    private AbstractNOAAController inicioController;
    private Node inicioView;
    /* -- Início -- */
    
    /* -- Ondógrafos -- */
    private AbstractNOAAController ondografosController;
    private Node ondografosView;
    /* -- Ondógrafos -- */
    
    /* -- Satélites -- */
    private AbstractNOAAController satelitesController;
    private Node satelitesView;
    /* -- Satélites -- */
    
    /* -- Eventos Climáticos -- */
    private AbstractNOAAController eventosClimaticosController;
    private Node eventosClimaticosView;
    /* -- Eventos Climáticos -- */
    
    /* -- Configurações -- */
    private AbstractNOAAController configuracoesController;
    private Node configuracoesView;
    /* -- Configurações -- */
    /* Controladores e Views*/
    
    /* Barra de Estado */
    @FXML
    private Text status;
    /* Barra de Estado */
    
    private GerenciadorDeBanco gdb;
    
    @Override
    public void initialize(URL url, ResourceBundle rb)
    {
        atual = null;
        try {
            this.carregarViews();
            this.setupEventos();
            this.definirView(this.inicioController, this.inicioView);
        } catch (Exception ex) {
            Alerta.mostrar("Erro fatal", "Não foi estabelecer a view principal. \n" + ex.getMessage(), Alert.AlertType.ERROR);
        }
        status.setText("Aplicação NOAA completamente inicializada.");
    }

    private void carregarViews() throws IOException
    {
        this.carregarInicioView();
        this.carregarOndografosView();
        this.carregarSatelitesView();
        this.carregarEventosClimaticosView();
        this.carregarConfiguracoesView();
    }
    
    private void carregarInicioView() throws IOException
    {
        FXMLLoader loader = new FXMLLoader(getClass().getResource(NOAAConfig.CAMINHO_VIEW + "InicioView.fxml"));
        this.inicioView = loader.load();
        this.inicioController = loader.getController();
        this.inicioController.setAplicacaoNOAA(this);
    }
    
    private void carregarOndografosView() throws IOException
    {
        FXMLLoader loader = new FXMLLoader(getClass().getResource(NOAAConfig.CAMINHO_VIEW + "OndografosView.fxml"));
        this.ondografosView = loader.load();
        this.ondografosController = loader.getController();
        this.ondografosController.setAplicacaoNOAA(this);
    }
    
    private void carregarSatelitesView() throws IOException
    {
        FXMLLoader loader = new FXMLLoader(getClass().getResource(NOAAConfig.CAMINHO_VIEW + "SatelitesView.fxml"));
        this.satelitesView = loader.load();
        this.satelitesController = loader.getController();
        this.satelitesController.setAplicacaoNOAA(this);
    }
    
    private void carregarEventosClimaticosView() throws IOException
    {
        FXMLLoader loader = new FXMLLoader(getClass().getResource(NOAAConfig.CAMINHO_VIEW + "EventosClimaticosView.fxml"));
        this.eventosClimaticosView = loader.load();
        this.eventosClimaticosController = loader.getController();
        this.eventosClimaticosController.setAplicacaoNOAA(this);
    }
    
    private void carregarConfiguracoesView() throws IOException
    {
        FXMLLoader loader = new FXMLLoader(getClass().getResource(NOAAConfig.CAMINHO_VIEW + "ConfiguracoesView.fxml"));
        this.configuracoesView = loader.load();
        this.configuracoesController = loader.getController();
        this.configuracoesController.setAplicacaoNOAA(this);
    }
        
    private void setupEventos()
    {
        this.bInicio.setOnMouseClicked(e -> definirView(this.inicioController, this.inicioView));
        this.bOndografos.setOnMouseClicked(e -> definirView(this.ondografosController, this.ondografosView));
        this.bSatelites.setOnMouseClicked(e -> definirView(this.satelitesController, this.satelitesView));
        this.bEventosClimaticos.setOnMouseClicked(e -> definirView(this.eventosClimaticosController, this.eventosClimaticosView));
        this.bConfiguracoes.setOnMouseClicked(e -> definirView(this.configuracoesController, this.configuracoesView));
    }
    
    public void definirView(AbstractNOAAController controlador, Node view)
    {
        if (atual != null) {
            atual.desativar();
        }
        atual = controlador;
        controlador.ativar();
        this.borderPane.setCenter(view);
    }
    
    protected void definirStatus(String texto)
    {
        this.status.setText(texto);
    }
}
