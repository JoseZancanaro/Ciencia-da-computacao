package br.univali.cc.programacao.noaa.ui.simulador.control;

import br.univali.cc.programacao.noaa.model.Ondografo;
import br.univali.cc.programacao.noaa.model.Satelite;
import br.univali.cc.programacao.noaa.persistencia.GerenciadorDeBanco;
import br.univali.cc.programacao.noaa.simulador.SimuladorAleatorio;
import br.univali.cc.programacao.noaa.ui.model.Alerta;
import java.net.URL;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.ResourceBundle;
import java.util.Timer;
import java.util.TimerTask;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.TextInputControl;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.KeyCode;
import javafx.util.converter.LocalDateTimeStringConverter;

public class SatelitesController implements Initializable
{
    @FXML
    private TableView<Satelite> tabela;
    
    @FXML
    private TextField tfNome;
    
    @FXML
    private TextField tfLatitude;
    
    @FXML
    private TextField tfLongitude;
    
    @FXML
    private TextField tfData;
    
    @FXML
    private Button btnCadastrar;
    
    @FXML
    private Button btnIniciar;
    
    @FXML
    private Button btnFinalizar;
    
    private Timer timer;
        
    private ObservableList<Satelite> satelites;
    
    private GerenciadorDeBanco gdb;
    
    public void initialize(URL location, ResourceBundle resources)
    {
        try {
            SimuladorAleatorio sa = new SimuladorAleatorio();
            
            this.gdb = new GerenciadorDeBanco();
            construirTabelaSatelites();
            atualizarSatelites();
            
            btnCadastrar.setOnAction(e -> {
                try {
                    LocalDateTimeStringConverter conversor = new LocalDateTimeStringConverter(DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss"), null);
                            
                    
                    gdb.inserirSatelite(new Satelite(tfNome.getText(), Double.parseDouble(tfLatitude.getText()),
                            Double.parseDouble(tfLongitude.getText()), 60.0 ,1.0 ,conversor.fromString(tfData.getText())));
                    
                    limparControleTexto(tfNome, tfLatitude, tfLongitude, tfData);
                    
                    atualizarSatelites();
                }
                catch (DateTimeParseException ex) {
                    Alerta.mostrar("Erro de formato de data.", "A data digitada não é valida. Digite-a no formato dd/MM/yyyy hh:mm:ss", Alert.AlertType.ERROR);
                } catch (Exception ex) {
                    System.out.println(ex);
                }
            });
            
            tabela.setOnKeyPressed(e -> {
                if (e.getCode() == KeyCode.DELETE) {
                    if (tabela.getSelectionModel().getSelectedIndex() > -1) {
                        try {
                            gdb.deletarSatelite(tabela.getSelectionModel().getSelectedItem());
                            atualizarSatelites();
                        }
                        catch (SQLException ignore) {}
                    }
                }
            });
            
            btnIniciar.setOnAction(e -> {
                timer = new Timer(true);
                timer.scheduleAtFixedRate(new TimerTask()
                {
                    @Override
                    public void run()
                    {
                        try {
                            sa.simularSatelites();
                            Platform.runLater(() -> atualizarSatelites());
                        }
                        catch (SQLException ignore) {
                            System.out.println(ignore);
                        }
                    }
                }, 0, 2000);
                this.btnIniciar.setDisable(true);
                this.btnFinalizar.setDisable(false);
            });
            
            btnFinalizar.setOnAction(e -> {
                timer.cancel();
                this.btnIniciar.setDisable(false);
                this.btnFinalizar.setDisable(true);
            });
            
        }
        catch (ClassNotFoundException ex) {
            Alerta.mostrar("Erro na Classe JDBC", "Não foi possível carregar a classe JDBC.", Alert.AlertType.ERROR);
        }
    }
    
    private void limparControleTexto(TextInputControl...controles)
    {
        for (TextInputControl t : controles)
            t.clear();
    }
    
    private <D, T> TableColumn<D, T> construirColuna(String cabecalho, String propriedade, double largura)
    {
        TableColumn<D, T> coluna = new TableColumn<>(cabecalho);
        coluna.setMinWidth(largura);
        coluna.setCellValueFactory(new PropertyValueFactory<>(propriedade));
        return coluna;
    }
    
    private void construirModeloTabelaSatelites()
    {
        this.satelites = FXCollections.observableArrayList();
    }
    
    private void construirTabelaSatelites()
    {
        construirModeloTabelaSatelites();
        TableColumn<Satelite, Integer> id = construirColuna("Id", "id", 15);
        TableColumn<Satelite, String> nome = construirColuna("Nome", "nome", 75);
        TableColumn<Satelite, Double> latitude = construirColuna("Latitude", "latitude", 50);
        TableColumn<Satelite, Double> longitude = construirColuna("Longitude", "longitude", 50);
        TableColumn<Satelite, Double> angulo = construirColuna("Ângulo", "angulo", 50);
        TableColumn<Satelite, Double> bateria = construirColuna("Bateria", "bateria", 50);
        TableColumn<Satelite, LocalDateTime> data = construirColuna("Data de Lançamento", "dataLancamento", 100);
        this.tabela.getColumns().addAll(id, nome, latitude, longitude, angulo, bateria, data);
        this.tabela.setItems(satelites);
    }
    
    private void atualizarSatelites()
    {
        try {
            satelites.clear();
            gdb.consultarSatelite().stream().forEach(s -> satelites.add(s));
        }
        catch (SQLException ex) {
            
        }
    }
    
}
