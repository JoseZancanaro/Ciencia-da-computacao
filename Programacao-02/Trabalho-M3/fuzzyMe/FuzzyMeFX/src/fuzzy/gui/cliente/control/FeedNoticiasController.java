package fuzzy.gui.cliente.control;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXProgressBar;
import com.jfoenix.controls.JFXTextArea;
import fuzzy.gui.cliente.model.Alerta;
import fuzzy.model.assets.ImagemFuzzy;
import fuzzy.model.assets.Postagem;
import fuzzy.model.assets.RedeFuzzy;
import fuzzy.model.assets.Usuario;
import fuzzy.model.cliente.ClienteFuzzy;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.time.LocalDateTime;
import java.util.Optional;
import java.util.ResourceBundle;
import java.util.Timer;
import java.util.TimerTask;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.FileChooser;

public class FeedNoticiasController implements Initializable
{
    /* FXML */
    @FXML
    private BorderPane root;
    
    @FXML
    private VBox postagens;
    
    @FXML
    private JFXButton btAnexar;
    
    @FXML
    private JFXButton btPublicar;
    
    @FXML
    private JFXTextArea tTexto;
    
    @FXML
    private Text tImagemAtual;
    
    @FXML
    private JFXProgressBar progresso;
    
    /* CADASTRO */
    private ImagemFuzzy imagemAtual;
    
    /* SERVIÇO DE REDE */
    private Usuario autenticado;
    private ClienteFuzzy socket;
    private RedeFuzzy rede;

    public FeedNoticiasController(Usuario autenticado)
    {
        try {
            this.autenticado = autenticado;
            this.socket = new ClienteFuzzy("localhost", 2048);
        } catch (Exception ex) {
            Alerta.show("Erro fatal", "Não foi possível inicializar um socket de comunicação.", Alert.AlertType.ERROR);
        }
    }

    @Override
    public void initialize(URL url, ResourceBundle rb)
    {
        this.btAnexar.setOnAction((e) -> {
            FileChooser fc = new FileChooser();
            fc.setTitle("Escolha uma imagem");
            File arquivo = fc.showOpenDialog(root.getScene().getWindow());
            if (arquivo != null) {
                try {
                    this.tImagemAtual.setText(arquivo.getName());
                    this.tImagemAtual.setVisible(true);
                    this.imagemAtual = new ImagemFuzzy(arquivo);
                } catch (IOException ignore) {}
            }
        });
        
        this.btPublicar.setOnAction((e) -> {
            this.solicitarCadastro();
        });
        
        Timer temporizador = new Timer(true);
        temporizador.scheduleAtFixedRate(new TimerTask()
        {
            @Override
            public void run()
            {
                atualizarRede();
            }
        }, 0, 3000);
    }
    
    private void inicializar(RedeFuzzy rede)
    {
        Platform.runLater(()-> {
            this.postagens.getChildren().clear();
            rede.getPostagens().forEach((p) -> {
                this.insereSeValido(rede.quemPostou(p), p);
            });
        });
        this.rede = rede;
    }
    
    private void atualizar(RedeFuzzy atualizada)
    {
        atualizada.getPostagens().stream().forEach((p) -> {
            if (!rede.getPostagens().stream().anyMatch((a) -> a.getId() == p.getId())) {
                insereSeValido(atualizada.quemPostou(p), p);
            }
        });
        this.rede = atualizada;
    }
    
    private void insereSeValido(Optional<Usuario> usuario, Postagem postagem)
    {
        if (usuario.isPresent()) {
            Platform.runLater(() -> {
                this.postagens.getChildren().add(0, new Publicacao(usuario.get(), postagem));
            });
        }
    }
    
    private void solicitarCadastro()
    {
        if (this.imagemAtual != null && !this.tTexto.getText().isEmpty()) {
            this.enviarPostagem(autenticado, new Postagem(autenticado.getId(), 
                                            this.tTexto.getText(), imagemAtual, LocalDateTime.now()));
            this.imagemAtual = null;
            this.tImagemAtual.setText("");
            this.tImagemAtual.setVisible(false);
            this.tTexto.clear();
        }
    }
    
    private void enviarPostagem(Usuario autenticado, Postagem p)
    {
        new Thread(() -> {
            try {
                boolean inseriu = socket.inserirPostagem(p);
                if (inseriu) {
                    this.atualizarRede();
                }
            } catch (IOException ex) {
                Alerta.show("Erro ao inserir postagem", ex.getMessage(), Alert.AlertType.ERROR);
            }
        }).start();
    }
    
    private void atualizarRede()
    {
        new Thread(() -> {
            try {
                progresso.setVisible(true);
                RedeFuzzy atualizados = socket.getRedeFuzzy();
                if (this.rede == null)
                    this.inicializar(atualizados);
                else
                    this.atualizar(atualizados);
                progresso.setVisible(false);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }).start();
    }
}
