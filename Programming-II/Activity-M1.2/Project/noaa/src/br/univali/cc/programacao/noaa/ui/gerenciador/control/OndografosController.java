package br.univali.cc.programacao.noaa.ui.gerenciador.control;

import br.univali.cc.programacao.noaa.ui.gerenciador.NOAADaemon;
import br.univali.cc.programacao.noaa.ui.model.Alerta;
import br.univali.cc.programacao.noaa.model.Ondografo;
import br.univali.cc.programacao.noaa.model.RegistroMeteoceanografico;
import br.univali.cc.programacao.noaa.persistencia.GerenciadorDeBanco;
import br.univali.cc.programacao.noaa.ui.gerenciador.NOAAServico;
import de.jensd.fx.glyphs.fontawesome.FontAwesomeIconView;
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
import javafx.scene.control.TreeItem;
import javafx.scene.control.TreeView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.KeyCode;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.scene.text.TextFlow;

public class OndografosController extends AbstractNOAAController implements Initializable 
{
    /* TreeView de Ondógrafos */
    @FXML
    private TreeView<TextFlow> tree;
    private ObservableList<Ondografo> ondografos;
    private static final String COR_NODO_TEXTO = "#3B3B3B";
    private static final String COR_NODO_ID = "#d9d9db";
    
    @FXML
    private MenuItem cLimparSelecao;
    /* TreeView de Ondógrafos */
    
    /* Tabela de Registros Meteoceanográficos */
    @FXML
    private TableView<RegistroMeteoceanografico> table;
    private ObservableList<RegistroMeteoceanografico> registros;
    private FilteredList<RegistroMeteoceanografico> registrosFiltrados;
    /* Tabela de Registros Meteoceanográficos */
    
    /* Toolbar */
    @FXML
    private FontAwesomeIconView tSalvarCSV;
    @FXML
    private CheckBox tAutoAtualizar;
    /* Toolbar */

    private GerenciadorDeBanco gdb;
    
    @Override
    public void initialize(URL url, ResourceBundle rb)
    {
        try {
            gdb = new GerenciadorDeBanco();
        }
        catch (ClassNotFoundException ex) {
            Alerta.mostrar("Erro na classe JDBC", "Erro ao carregar a classe JDBC", Alert.AlertType.ERROR);
        }
        construirTreeView();
        construirTabela();
        setupServicos();
        setupEventos();
    }

    @Override
    public void ativar()
    {
        this.atualizarStatus();
        NOAADaemon.getInstancia().get("Ondógrafos").habilitar();
    }

    @Override
    public void desativar()
    {
        NOAADaemon.getInstancia().get("Ondógrafos").desabilitar();
    }
    
    private void atualizarStatus()
    {
        String status;
        if (this.registros.size() == this.registrosFiltrados.size()) {
            status = "Carregou " + this.registros.size() + " registros de " + this.tree.getRoot().getChildren().size() + " ondógrafos";
        }
        else {
            status = "Mostrando " + this.registrosFiltrados.size() + " de " + this.registros.size() + " registros";
        }
        this.main.definirStatus(status);
    }
    
    private void setupServicos()
    {
        NOAADaemon.getInstancia().add("Ondógrafos", new NOAAServico(() -> {
            this.atualizarTreeView();
            this.atualizarTabela();
            this.atualizarStatus();
        }, 0, 2500, false, () -> this.tAutoAtualizar.setSelected(true), () -> this.tAutoAtualizar.setSelected(false)));
    }
    
    private void setupEventos()
    {
        cLimparSelecao.setOnAction(e -> this.tree.getSelectionModel().clearSelection());
        
        this.table.setOnKeyPressed(e -> {
            if (e.getCode().equals(KeyCode.DELETE)) {
                if (table.getSelectionModel().getSelectedIndex() > -1) {
                    try {
                        gdb.deletarRegistroMeteoceanografico(table.getSelectionModel().getSelectedItem());
                        this.atualizarRegistros();
                        this.atualizarStatus();
                    } catch (SQLException ignore) {
                        System.out.println(ignore);
                    }
                }
            }
        });
        
        this.table.setOnMouseClicked(e -> {
            NOAADaemon.getInstancia().get("Ondógrafos").desabilitar();
        });
        
        this.tAutoAtualizar.setOnAction(e -> {
            if (tAutoAtualizar.isSelected())
                NOAADaemon.getInstancia().get("Ondógrafos").habilitar();
            else
                NOAADaemon.getInstancia().get("Ondógrafos").desabilitar();
        });
        
        this.tSalvarCSV.setOnMouseClicked(e -> {});
    }
    
    private <T> TableColumn<RegistroMeteoceanografico, T> construirColuna(String cabecalho, String propriedade, double largura)
    {
        TableColumn<RegistroMeteoceanografico, T> coluna = new TableColumn<>(cabecalho);
        coluna.setMinWidth(largura);
        coluna.setCellValueFactory(new PropertyValueFactory<>(propriedade));
        return coluna;
    }
    
    private void construirTabela()
    {
        construirModeloTabela();
        TableColumn<RegistroMeteoceanografico, Integer> idOndografo = construirColuna("Ondógrafo", "idOndografo", 15);
        TableColumn<RegistroMeteoceanografico, Integer> id = construirColuna("Id", "id", 10);
        TableColumn<RegistroMeteoceanografico, Double> temperatura = construirColuna("Temperatura em °C", "temperatura", 50);
        TableColumn<RegistroMeteoceanografico, Double> umidade = construirColuna("Umidade em %", "umidade", 50);
        TableColumn<RegistroMeteoceanografico, Double> pressao = construirColuna("Pressão em hPa", "pressao", 50);
        TableColumn<RegistroMeteoceanografico, Double> altura = construirColuna("Altura em metros", "altura", 50);
        TableColumn<RegistroMeteoceanografico, Double> corrente = construirColuna("Corrente em m/s", "corrente", 50);
        TableColumn<RegistroMeteoceanografico, Double> dirCorrente = construirColuna("° Direção Corrente", "direcaoCorrente", 50);
        TableColumn<RegistroMeteoceanografico, Double> vento = construirColuna("Vento em m/s", "vento", 50);
        TableColumn<RegistroMeteoceanografico, Double> dirVento = construirColuna("° Direção Vento", "direcaoVento", 50);
        TableColumn<RegistroMeteoceanografico, Double> bateria = construirColuna("Bateria em %", "bateria", 50);
        TableColumn<RegistroMeteoceanografico, LocalDateTime> data = construirColuna("Data", "data", 75);
        table.getColumns().addAll(idOndografo, id, temperatura, umidade, pressao, altura, corrente, dirCorrente, vento, dirVento, bateria, data);
    }
    
    private void construirModeloTabela()
    {
        registros = FXCollections.observableArrayList();
        atualizarRegistros();
        
        registrosFiltrados = new FilteredList<>(registros);
        
        tree.getSelectionModel().selectedItemProperty().addListener((obs, antigo, novo) -> {
            if (novo == null || novo.getValue().getChildren().size() == 1) {
                registrosFiltrados.setPredicate(s -> true);
            }
            else {
                registrosFiltrados.setPredicate(s -> {
                    String texto = ((Text)novo.getValue().getChildren().get(1)).getText();
                    return Integer.parseInt(texto.substring(texto.indexOf("#") + 1)) == s.getIdOndografo();
                });
            }
            this.atualizarStatus();
        });
        
        table.setItems(registrosFiltrados);
    }
            
    private void atualizarRegistros()
    {
        try {
            registros.clear();
            gdb.consultarRegistrosMeteoceanograficosDec().stream().forEach(reg -> registros.add(reg));
        } catch (SQLException ex) {
            Alerta.mostrar("Erro ao consultar os registros meteoceanográficos.",
                    "Descrição do erro: " + ex.getMessage(), Alert.AlertType.ERROR);
        }
    }

    private void construirTreeView()
    {
        Text texto = new Text("Ondógrafos");
        texto.setFill(Color.web(COR_NODO_TEXTO));
        TreeItem<TextFlow> raiz = new TreeItem<>(new TextFlow(texto));
        tree.setRoot(raiz);
    }
    
    private TreeItem<TextFlow> construirNodoOndografo(Ondografo ondografo)
    {
        Text nome = new Text(ondografo.getNome());
        nome.setFill(Color.web(COR_NODO_TEXTO));
        
        Text id = new Text(" #" + ondografo.getId());
        id.setFill(Color.web(COR_NODO_ID));
        
        TreeItem<TextFlow> item = new TreeItem<>(new TextFlow(nome, id));
        item.setExpanded(true);
        return item;
    }
    
    public void atualizarTreeView()
    {
        // Pegar texto do nodo selecionado, caso haja algum
        String textoSelecionado = null;
        if (this.tree.getSelectionModel().getSelectedIndex() > 0)
            textoSelecionado = ((Text) this.tree.getSelectionModel().getSelectedItem().getValue().getChildren().get(1)).getText();
        
        // Limpar nodos de ondógrafos
        this.tree.getRoot().getChildren().clear();
        
        try {
            // Consultar nodos e inserir no root
            gdb.consultarOndografos().stream().forEach(o -> this.tree.getRoot().getChildren().add(construirNodoOndografo(o)));
            
            // Selecionar o antigo nodo, caso houvesse
            if (textoSelecionado != null) {
                for (TreeItem<TextFlow> item : this.tree.getRoot().getChildren()) {
                    if (item.getValue().getChildren().size() > 1) {
                        if (((Text)item.getValue().getChildren().get(1)).getText().equals(textoSelecionado)) {
                            this.tree.getSelectionModel().select(item);
                            break;
                        }
                    }
                }
            }
            
            this.tree.getRoot().setExpanded(true);
        }
        catch (SQLException ex) {
            Alerta.mostrar("Erro ao atualizar lista de ondógrafos", "Descrição do erro: "
                    + ex.getMessage(), Alert.AlertType.ERROR);
        }
    }
    
    public void atualizarTabela()
    {
        this.atualizarRegistros();
    }
}
