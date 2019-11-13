package br.univali.cc.programacao.noaa.ui.gerenciador.control;

import br.univali.cc.programacao.noaa.model.CategoriaEvento;
import br.univali.cc.programacao.noaa.model.EventoClimatico;
import br.univali.cc.programacao.noaa.model.SituacaoEvento;
import br.univali.cc.programacao.noaa.model.TipoEvento;
import br.univali.cc.programacao.noaa.model.exceptions.ValorInvalidoException;
import br.univali.cc.programacao.noaa.persistencia.GerenciadorDeBanco;
import br.univali.cc.programacao.noaa.ui.gerenciador.NOAADaemon;
import br.univali.cc.programacao.noaa.ui.gerenciador.NOAAServico;
import br.univali.cc.programacao.noaa.ui.model.Alerta;
import java.net.URL;
import java.sql.SQLException;
import java.text.ParseException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.ResourceBundle;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.TextInputControl;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.KeyCode;
import javafx.util.converter.LocalDateTimeStringConverter;

public class EventosClimaticosController extends AbstractNOAAController implements Initializable
{    
    /* Tabela */
    @FXML
    private TableView<EventoClimatico> tabela;
    private ObservableList<EventoClimatico> eventos;
    /* Tabela */
    
    /* Toolbar */
    @FXML
    private CheckBox tAutoAtualizar;
    /* Toolbar */
    
    /* Cadastro */
    @FXML
    private ComboBox<TipoEvento> cTipo;
    @FXML
    private TextField cDescricao;
    @FXML
    private ComboBox<SituacaoEvento> cSituacao;
    @FXML
    private ComboBox<CategoriaEvento> cCategoria;
    @FXML
    private TextField cLatitude;
    @FXML
    private TextField cLongitude;
    @FXML
    private TextField cDataInicio;
    @FXML
    private TextField cDataFim;
    @FXML
    private Button btnCadastrar;
    @FXML
    private Button btnCancelar;
    @FXML
    private MenuItem mEditar;
    /* Cadastro */
    
    private GerenciadorDeBanco gdb;
    
    @Override
    public void initialize(URL location, ResourceBundle resources)
    {
        try {
            this.gdb = new GerenciadorDeBanco();
        } catch (ClassNotFoundException ex) {
            Alerta.mostrar("Driver JDBC não encontrado.", "Não foi possível inicializar o driver JDBC.", Alert.AlertType.ERROR);
        }
        construirTabela();
        setupControles();
        setupServicos();
        setupEventos();
    }
    
    private void setupServicos()
    {
        NOAADaemon.getInstancia().add("EventosClimáticos", new NOAAServico(() -> {
            this.atualizarTabela();
            this.atualizarStatus();
        }, 0, 5000, false, () -> tAutoAtualizar.setSelected(true), () -> tAutoAtualizar.setSelected(false)));
    }
    
    private void atualizarStatus()
    {
        String status = "Carregou " + this.eventos.size() + " eventos climáticos";
        this.main.definirStatus(status);
    }
    
    private LocalDateTime converterTextoParaData(String texto) throws DateTimeParseException
    {
        LocalDateTimeStringConverter conversor = new LocalDateTimeStringConverter(DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss"), null);
        return conversor.fromString(texto);
    }
    
    private double converterTextoParaLatitude(String texto) throws ParseException, ValorInvalidoException
    {
        double lat = 0.0;
        if (texto.isEmpty())
            throw new ValorInvalidoException("Latitude vazia.");
        try {
            lat = Double.parseDouble(texto);
        }
        catch (Exception ex) {
            throw new ParseException("Latitude em formato inválido.", 0);
        }
        if (lat < -90 || lat > 90)
            throw new ValorInvalidoException("Fora do alcance da latitude [-90, +90].");
        return lat;
    }
    
    private double converterTextoParaLongitude(String texto) throws ParseException, ValorInvalidoException
    {
        double lon = 0.0;
        if (texto.isEmpty())
            throw new ValorInvalidoException("Longitude vazia.");
        try {
            lon = Double.parseDouble(texto);
        }
        catch (Exception ex) {
            throw new ParseException("Longitude em formato inválido.", 0);
        }
        if (lon < -180 || lon > 180)
            throw new ValorInvalidoException("Fora do alcance da longitude [-180, +180].");
        return lon;
    }
    
    private void limparControleTexto(TextInputControl...controles)
    {
        for (TextInputControl t : controles)
            t.clear();
    }
    
    private void limparComboBox(ComboBox...controles)
    {
        for (ComboBox t : controles)
            t.getSelectionModel().clearSelection();
    }
    
    private void acaoCadastrar(ActionEvent e)
    {
        try {
            if (this.cTipo.getValue() == null || this.cSituacao.getValue() == null || this.cCategoria.getValue() == null)
                throw new ValorInvalidoException("Campos de Tipo, Situação ou Categoria não podem estar vazios.");

            if (this.cDataInicio.getText().isEmpty() || this.cDataFim.getText().isEmpty() && this.cSituacao.getValue().equals(SituacaoEvento.Finalizado))
                throw new ValorInvalidoException("Campos de Data Início não pode estar vazia e a Data Final não pode estar vazia se o evento estiver finalizado.");

            double latitude = converterTextoParaLatitude(this.cLatitude.getText());
            double longitude = converterTextoParaLongitude(this.cLongitude.getText());

            LocalDateTime inicio = converterTextoParaData(this.cDataInicio.getText());
            LocalDateTime fim = null;

            if (this.cSituacao.getValue().equals(SituacaoEvento.Finalizado)) {
                fim = converterTextoParaData(this.cDataFim.getText());
                if (!fim.isAfter(inicio))
                    throw new ValorInvalidoException("Fim do evento deve ser maior que o início.");
            }

            gdb.inserirEventoClimatico(new EventoClimatico(this.cTipo.getValue(), latitude, longitude, this.cDescricao.getText(),
                    inicio, fim, this.cSituacao.getValue(), this.cCategoria.getValue()));

            limparControleTexto(this.cDescricao, this.cLatitude, this.cLongitude, this.cDataInicio, this.cDataFim);
            limparComboBox(this.cTipo, this.cSituacao, this.cCategoria);

            atualizarTabela();

        }
        catch (DateTimeParseException ex) {
            Alerta.mostrar("Campos inválidos", "Verifique que as datas estão no formato correto.", Alert.AlertType.ERROR);
        }
        catch (ParseException ex) {
            Alerta.mostrar("Campos inválidos", "Verifique que latitude e longitude são numéricos.", Alert.AlertType.ERROR);
        }
        catch (ValorInvalidoException ex) {
            Alerta.mostrar("Campos inválidos", ex.getMessage(), Alert.AlertType.ERROR);
        }
        catch (SQLException ex) {
            Alerta.mostrar("Não foi possível conectar-se ao banco de dados.", ex.getMessage(), Alert.AlertType.ERROR);
        }
    }
    
    private void acaoAtualizar(ActionEvent e)
    {
        try {
            if (this.cTipo.getValue() == null || this.cSituacao.getValue() == null || this.cCategoria.getValue() == null)
                throw new ValorInvalidoException("Campos de Tipo, Situação ou Categoria não podem estar vazios.");

            if (this.cDataInicio.getText().isEmpty() || this.cDataFim.getText().isEmpty() && this.cSituacao.getValue().equals(SituacaoEvento.Finalizado))
                throw new ValorInvalidoException("Campos de Data Início não pode estar vazia e a Data Final não pode estar vazia se o evento estiver finalizado.");

            double latitude = converterTextoParaLatitude(this.cLatitude.getText());
            double longitude = converterTextoParaLongitude(this.cLongitude.getText());

            LocalDateTime inicio = this.tabela.getSelectionModel().getSelectedItem().getDataInicio();
            LocalDateTime fim = null;

            if (this.cSituacao.getValue().equals(SituacaoEvento.Finalizado)) {
                fim = converterTextoParaData(this.cDataFim.getText());
                if (!fim.isAfter(inicio))
                    throw new ValorInvalidoException("Fim do evento deve ser maior que o início.");
            }

            EventoClimatico evento = this.tabela.getSelectionModel().getSelectedItem();
            evento.setLatitude(latitude);
            evento.setLongitude(longitude);
            evento.setCategoria(this.cCategoria.getValue());
            evento.setDescricao(this.cDescricao.getText());
            evento.setSituacao(this.cSituacao.getValue());
            evento.setDataFim(fim);
            
            gdb.atualizarEventoClimatico(evento);

            this.acaoCancelar(e);

        }
        catch (DateTimeParseException ex) {
            Alerta.mostrar("Campos inválidos", "Verifique que as datas estão no formato correto.", Alert.AlertType.ERROR);
        }
        catch (ParseException ex) {
            Alerta.mostrar("Campos inválidos", "Verifique que latitude e longitude são numéricos.", Alert.AlertType.ERROR);
        }
        catch (ValorInvalidoException ex) {
            Alerta.mostrar("Campos inválidos", ex.getMessage(), Alert.AlertType.ERROR);
        }
        catch (SQLException ex) {
            Alerta.mostrar("Não foi possível conectar-se ao banco de dados.", ex.getMessage(), Alert.AlertType.ERROR);
        }
    }
    
    private void acaoCancelar(ActionEvent e)
    {
        limparControleTexto(this.cDescricao, this.cLatitude, this.cLongitude, this.cDataInicio, this.cDataFim);
        limparComboBox(this.cTipo, this.cSituacao, this.cCategoria);    
        atualizarTabela();
        this.cTipo.setDisable(false);
        this.cDataInicio.setDisable(false);
        this.btnCadastrar.setOnAction(this::acaoCadastrar);
        this.btnCadastrar.setText("Cadastrar");
        this.btnCancelar.setVisible(false);
    }
    
    private void setupEventos()
    {
        this.tAutoAtualizar.setOnAction(e -> {
            if (this.tAutoAtualizar.isSelected())
                NOAADaemon.getInstancia().get("EventosClimáticos").habilitar();
            else
                NOAADaemon.getInstancia().get("EventosClimáticos").desabilitar();
        });
        
        this.cSituacao.setOnAction(e -> {
            if (this.cSituacao.getValue() == SituacaoEvento.Ocorrendo) {
                this.cDataFim.setDisable(true);
            }
            else {
                this.cDataFim.setDisable(false);
            }
        });
        
        this.btnCancelar.setOnAction(this::acaoCancelar);
        
        this.btnCadastrar.setOnAction(this::acaoCadastrar);
        
        this.mEditar.setOnAction(e -> {
            if (this.tabela.getSelectionModel().getSelectedItem() != null) {
                if (!this.tabela.getSelectionModel().getSelectedItem().getSituacao().equals(SituacaoEvento.Finalizado)) {
                    this.cTipo.setValue(this.tabela.getSelectionModel().getSelectedItem().getTipo());
                    this.cDescricao.setText(this.tabela.getSelectionModel().getSelectedItem().getDescricao());
                    this.cSituacao.setValue(this.tabela.getSelectionModel().getSelectedItem().getSituacao());
                    this.cCategoria.setValue(this.tabela.getSelectionModel().getSelectedItem().getCategoria());
                    this.cLatitude.setText(String.valueOf(this.tabela.getSelectionModel().getSelectedItem().getLatitude()));
                    this.cLongitude.setText(String.valueOf(this.tabela.getSelectionModel().getSelectedItem().getLongitude()));
                    this.cDataInicio.setText(this.tabela.getSelectionModel().getSelectedItem().getDataInicio().toString().replace('T', ' '));
                    if (this.tabela.getSelectionModel().getSelectedItem().getDataFim() != null) {
                        this.cDataFim.setText(this.tabela.getSelectionModel().getSelectedItem().getDataInicio().toString().replace('T', ' '));
                    }
                    else {
                        this.cDataFim.setText("");
                    }
                    this.btnCadastrar.setOnAction(this::acaoAtualizar);
                    this.cTipo.setDisable(true);
                    this.cDataInicio.setDisable(true);
                    this.btnCancelar.setVisible(true);
                    this.btnCadastrar.setText("Atualizar");
                }
                else {
                    Alerta.mostrar("Evento Finalizado", "Não é possível alterar um evento finalizado.", Alert.AlertType.WARNING);
                }
            }
        });
        
        this.tabela.selectionModelProperty().addListener((obs, antigo, novo) -> this.acaoCancelar(null));
        
        this.tabela.setOnKeyPressed(e -> {
            if (e.getCode() == KeyCode.DELETE) {
                try {
                    gdb.deletarEventoClimatico(this.tabela.getSelectionModel().getSelectedItem());
                    atualizarTabela();
                }
                catch (NullPointerException ex) {
                    Alerta.mostrar("Seleção vazia", "Não há nada selecionado.", Alert.AlertType.ERROR);
                }
                catch (SQLException ex) {
                    Alerta.mostrar("Erro no Banco de Dados", "Não foi possível executar a operação.\n" + ex.getMessage(), Alert.AlertType.ERROR);
                }
            }
        }); 
        
        this.tabela.setOnMouseClicked(e -> NOAADaemon.getInstancia().get("EventosClimáticos").desabilitar());
    }
    
    private void setupControles()
    {
        // Tipo do Evento
        ObservableList<TipoEvento> tipos = FXCollections.observableArrayList();
        for (TipoEvento e : TipoEvento.values()) {
            tipos.add(e);
        }
        this.cTipo.setItems(tipos);
        
        // Situação do Evento
        ObservableList<SituacaoEvento> situacoes = FXCollections.observableArrayList();
        for (SituacaoEvento e : SituacaoEvento.values()) {
            situacoes.add(e);
        }
        this.cSituacao.setItems(situacoes);
        
        // Categoria do Evento
        ObservableList<CategoriaEvento> categorias = FXCollections.observableArrayList();
        for (CategoriaEvento e : CategoriaEvento.values()) {
            categorias.add(e);
        }
        this.cCategoria.setItems(categorias);
    }
    
    private <EventoClimatico, T> TableColumn<EventoClimatico, T> construirColuna(String cabecalho, String propriedade, double largura)
    {
        TableColumn<EventoClimatico, T> coluna = new TableColumn<>(cabecalho);
        coluna.setMinWidth(largura);
        coluna.setCellValueFactory(new PropertyValueFactory<>(propriedade));
        return coluna;
    }
    
    private void construirModeloTabela()
    {
        this.eventos = FXCollections.observableArrayList();
    }
    
    private void construirTabela()
    {
        construirModeloTabela();
        TableColumn<EventoClimatico, Integer> id = construirColuna("Id", "id", 10);
        TableColumn<EventoClimatico, TipoEvento> tipo = construirColuna("Tipo", "tipo", 30);
        TableColumn<EventoClimatico, Double> latitude = construirColuna("Latitude", "latitude", 30);
        TableColumn<EventoClimatico, Double> longitude = construirColuna("Longitude", "longitude", 30);
        TableColumn<EventoClimatico, String> descricao = construirColuna("Descricao", "descricao", 100);
        TableColumn<EventoClimatico, LocalDateTime> dataInicio = construirColuna("Início", "dataInicio", 75);
        TableColumn<EventoClimatico, LocalDateTime> dataFim = construirColuna("Fim", "dataFim", 75);
        TableColumn<EventoClimatico, SituacaoEvento> situacao = construirColuna("Situação", "situacao", 30);
        TableColumn<EventoClimatico, CategoriaEvento> categoria = construirColuna("Categoria", "categoria", 30);
        tabela.getColumns().addAll(id, tipo, latitude, longitude, descricao, dataInicio, dataFim, situacao, categoria);
        tabela.setItems(eventos);
        tabela.getColumns().forEach(c -> tabela.resizeColumn(c, c.getMinWidth()));
    }
    
    private void atualizarTabela()
    {
        try {
            this.eventos.clear();
            gdb.consultarEventosClimaticos().stream().forEach(e -> eventos.add(e));
        }
        catch (SQLException ex) {
            Alerta.mostrar("", "", Alert.AlertType.ERROR);
        }
    }

    @Override
    public void ativar()
    {
        this.atualizarStatus();
        NOAADaemon.getInstancia().get("EventosClimáticos").habilitar();
    }

    @Override
    public void desativar()
    {
        NOAADaemon.getInstancia().get("EventosClimáticos").desabilitar();
    }
}
