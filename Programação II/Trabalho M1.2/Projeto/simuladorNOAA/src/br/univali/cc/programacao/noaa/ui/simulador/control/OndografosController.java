package br.univali.cc.programacao.noaa.ui.simulador.control;

import br.univali.cc.programacao.noaa.persistencia.GerenciadorDeBanco;
import br.univali.cc.programacao.noaa.model.Ondografo;
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

public class OndografosController implements Initializable
{
    private GerenciadorDeBanco gdb;
    
    @FXML
    private TableView<Ondografo>tabela;
    ObservableList<Ondografo> ondografos;
    
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
    
    public void initialize(URL location, ResourceBundle resources)
    {
        this.ondografos = FXCollections.observableArrayList();
        
        try {
            SimuladorAleatorio sa = new SimuladorAleatorio();
            gdb = new GerenciadorDeBanco();
            construirTabela();
            atualizarTabela();
            
            btnCadastrar.setOnAction(e -> {
                try {
                    LocalDateTimeStringConverter conversor = new LocalDateTimeStringConverter(DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss"), null);
                            
                    gdb.inserirOndografo(new Ondografo(tfNome.getText(), Double.parseDouble(tfLatitude.getText()),
                            Double.parseDouble(tfLongitude.getText()), conversor.fromString(tfData.getText())));
                    
                    limparControleTexto(tfNome, tfLatitude, tfLongitude, tfData);
                    
                    atualizarTabela();
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
                            gdb.deletarOndografo(tabela.getSelectionModel().getSelectedItem());
                            Platform.runLater(() -> atualizarTabela());
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
                            sa.simularOndografos();
                            Platform.runLater(() -> atualizarTabela());
                        }
                        catch (SQLException ignore) {}
                        catch (Exception ignore) {}
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
            
        } catch (Exception ex) {
            System.out.println(ex);
        }            
    }
    
    private <T> TableColumn<Ondografo, T> construirColuna(String titulo, String propriedade, double minTamanho)
    {
        TableColumn<Ondografo, T> coluna = new TableColumn<>(titulo);
        coluna.setCellValueFactory(new PropertyValueFactory<>(propriedade));
        coluna.setMinWidth(minTamanho);
        return coluna;
    }
    
    private void limparControleTexto(TextInputControl...controles)
    {
        for (TextInputControl t : controles)
            t.clear();
    }
    
    private void construirTabela()
    {
        TableColumn<Ondografo, Integer> id = construirColuna("Id", "id", 15);
        TableColumn<Ondografo, String> nome = construirColuna("Nome", "nome", 75);
        TableColumn<Ondografo, Double> latitude = construirColuna("Latitude", "latitude", 50);
        TableColumn<Ondografo, Double> longitude = construirColuna("Longitude", "longitude", 50);
        TableColumn<Ondografo, LocalDateTime> dataLancamento = construirColuna("Data de Lançamento", "dataLancamento", 75);
        TableColumn<Ondografo, Double> bateria = construirColuna("Bateria", "bateria", 20);
        tabela.getColumns().addAll(id, nome, latitude, longitude, dataLancamento, bateria);
        tabela.setItems(ondografos);
    }
    
    private void atualizarTabela()
    {
        try {
            ondografos.clear();
            gdb.consultarOndografos().stream().forEach(o -> ondografos.add(o));
        }
        catch (Exception ignore) {}
    }
}
