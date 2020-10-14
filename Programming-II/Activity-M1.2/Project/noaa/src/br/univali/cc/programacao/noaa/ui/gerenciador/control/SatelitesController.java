package br.univali.cc.programacao.noaa.ui.gerenciador.control;

import br.univali.cc.programacao.noaa.model.RegistroAtmosferico;
import br.univali.cc.programacao.noaa.model.Satelite;
import br.univali.cc.programacao.noaa.persistencia.GerenciadorDeBanco;
import br.univali.cc.programacao.noaa.ui.gerenciador.NOAADaemon;
import br.univali.cc.programacao.noaa.ui.gerenciador.NOAAServico;
import br.univali.cc.programacao.noaa.ui.model.Alerta;
import java.net.URL;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.ResourceBundle;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.transformation.FilteredList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.CheckBox;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.KeyCode;

public class SatelitesController extends AbstractNOAAController implements Initializable
{
    @FXML
    private TableView<Satelite> tabelaSatelites;
    private ObservableList<Satelite> satelites;
    
    @FXML
    private MenuItem cLimparSelecao;
    
    @FXML
    private TableView<RegistroAtmosferico> tabelaRegistros;
    private ObservableList<RegistroAtmosferico> registros;
    private FilteredList<RegistroAtmosferico> registrosFiltrados;
    
    @FXML
    private CheckBox tAutoAtualizar;
    
    private GerenciadorDeBanco gdb;
    
    @Override
    public void initialize(URL location, ResourceBundle resources)
    {
        try {
            this.gdb = new GerenciadorDeBanco();
        }
        catch (ClassNotFoundException ex) {
            Alerta.mostrar("Driver JDBC não encontrado.", "Não foi possível inicializar o driver JDBC.", Alert.AlertType.ERROR);
        }
        construirTabelaSatelites();
        construirTabelaRegistros();
        setupServicos();
        setupEventos();
    }
    
    private void setupServicos()
    {
        this.tAutoAtualizar.setSelected(true);
        NOAADaemon.getInstancia().add("Satélites", new NOAAServico(() -> {
            this.atualizarSatelites();
            this.atualizarRegistrosAtmosfericos();
            this.atualizarStatus();
        }, 0, 2500, false));
    }
    
    private void setupEventos()
    {
        cLimparSelecao.setOnAction(e -> this.tabelaSatelites.getSelectionModel().clearSelection());
        
        tabelaRegistros.setOnMouseClicked(e -> {
            NOAADaemon.getInstancia().get("Satélites").desabilitar();
            tAutoAtualizar.setSelected(false);
        });
        
        tabelaRegistros.setOnKeyPressed(e -> {
            if (e.getCode() == KeyCode.DELETE) {
                try {
                    gdb.deletarRegistroAtmosferico(tabelaRegistros.getSelectionModel().getSelectedItem());
                    atualizarRegistrosAtmosfericos();
                }
                catch (NullPointerException ex) {
                    Alerta.mostrar("Seleção vazia", "Não há o que ser deletado.", Alert.AlertType.WARNING);
                }
                catch (SQLException ex) {
                    Alerta.mostrar("Erro ao deletar registro Atmosférico", ex.getMessage(), Alert.AlertType.ERROR);
                }
            }
        });
        
        tAutoAtualizar.setOnAction(e -> {
            if (tAutoAtualizar.isSelected())
                NOAADaemon.getInstancia().get("Satélites").habilitar();
            else
                NOAADaemon.getInstancia().get("Satélites").desabilitar();
        });
    }
    
    private void atualizarStatus()
    {
        String status;
        if (this.registros.size() == this.registrosFiltrados.size()) {
            status = "Carregou " + this.registros.size() + " registros atmosféricos de " + this.satelites.size() + " satélites";
        }
        else {
            status = "Mostrando " + this.registrosFiltrados.size() + " de " + this.registros.size() + " registros atmosféricos";
        }
        this.main.definirStatus(status);
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
        TableColumn<Satelite, Double> bateria = construirColuna("Bateria", "bateria", 50);
        TableColumn<Satelite, LocalDateTime> data = construirColuna("Data de Lançamento", "dataLancamento", 100);
        this.tabelaSatelites.getColumns().addAll(id, nome, latitude, longitude, bateria, data);
        this.tabelaSatelites.setItems(satelites);
    }
    
    public void atualizarSatelites()
    {
        try {
            // Pegar satélite selecionado antes de limpar
            int selecionado = -1;
            if (this.tabelaSatelites.getSelectionModel().getSelectedItem() != null)
                selecionado = this.tabelaSatelites.getSelectionModel().getSelectedItem().getId();
            
            satelites.clear();
            
            // Consultar novos satélites
            gdb.consultarSatelite().stream().forEach(s -> satelites.add(s));
            
            // Reselecionar antigo satélite
            if (selecionado > -1) {
                for (Satelite s : this.satelites) {
                    if (selecionado == s.getId()) {
                        this.tabelaSatelites.getSelectionModel().select(s);
                        break;
                    }
                }
            }
        }
        catch (SQLException ex) {
            Alerta.mostrar("Erro ao consultar satélites", ex.getMessage(), Alert.AlertType.ERROR);
        }
    }
    
    private void construirModeloRegistros()
    {
        this.registros = FXCollections.observableArrayList();
        this.registrosFiltrados = new FilteredList<>(registros);
        
        this.tabelaSatelites.getSelectionModel().selectedItemProperty().addListener((obs, antigo, novo) -> {
            if (novo != null)
                this.registrosFiltrados.setPredicate(r -> r.getIdSatelite() == novo.getId());
            else
                this.registrosFiltrados.setPredicate(r -> true);
            this.atualizarStatus();
        });
        
    }
    
    private void construirTabelaRegistros()
    {
        construirModeloRegistros();
        TableColumn<RegistroAtmosferico, Integer> id = construirColuna("Id", "id", 15);
        TableColumn<RegistroAtmosferico, Integer> idSatelite = construirColuna("Satélite", "idSatelite", 40);
        TableColumn<RegistroAtmosferico, Double> temperatura = construirColuna("Temperatura em °C", "temperatura", 50);
        TableColumn<RegistroAtmosferico, Double> pressao = construirColuna("Pressão em hPa", "pressao", 50);
        TableColumn<RegistroAtmosferico, Double> densidade = construirColuna("Densidade em kg/m³", "densidade", 50);
        TableColumn<RegistroAtmosferico, Double> vento = construirColuna("Vento em m/s", "vento", 50);
        TableColumn<RegistroAtmosferico, Double> dirVento = construirColuna("° Direção Vento", "direcaoVento", 50);
        TableColumn<RegistroAtmosferico, Double> bateria = construirColuna("Bateria em %", "bateria", 50);
        TableColumn<RegistroAtmosferico, LocalDateTime> data = construirColuna("Data", "data", 100);
        this.tabelaRegistros.getColumns().addAll(idSatelite, id, temperatura, pressao, densidade, vento, dirVento, bateria, data);
        this.tabelaRegistros.setItems(registrosFiltrados);
    }
    
    public void atualizarRegistrosAtmosfericos()
    {
        try {
            registros.clear();
            gdb.consultarRegistrosAtmosfericosDec().stream().forEach(r -> registros.add(r));
        } catch (SQLException ex) {
            Alerta.mostrar("Erro ao consultar registros atmosféricos", ex.getMessage(), Alert.AlertType.ERROR);
        }
    }

    @Override
    public void ativar()
    {
        this.atualizarStatus();
        NOAADaemon.getInstancia().get("Satélites").habilitar();
    }

    @Override
    public void desativar()
    {
        NOAADaemon.getInstancia().get("Satélites").desabilitar();
    }
}
