package fuzzy.gui.cliente.control;

import com.jfoenix.controls.JFXButton;
import fuzzy.gui.cliente.model.ConfiguracaoFuzzy;
import fuzzy.model.assets.Postagem;
import fuzzy.model.assets.RedeFuzzy;
import fuzzy.model.assets.Usuario;
import fuzzy.model.cliente.ClienteFuzzy;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.shape.Circle;

public class FuzzyMeController implements Initializable
{
    /* FXML */
    @FXML
    private BorderPane root;
    
    @FXML
    private ImageView avatar;
    
    @FXML
    private Label nome;
    
    @FXML
    private JFXButton btSair;
    
    /* VIEWS E CONTROLADORES */
    private BorderPane feedView;
    private FeedNoticiasController feedController;
    
    /* SERVIÇO DE REDE */
    private final Usuario autenticado;

    public FuzzyMeController(Usuario autenticado)
    {
        try {
            this.autenticado = autenticado;
        } catch (Exception ex) {
            throw new RuntimeException(ex);
        }
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb)
    {
        try {
            this.demonstrarUsuario(autenticado);
            this.feedController = ConfiguracaoFuzzy.Feed.getController(autenticado);
            this.inicializarFeedView(feedController);
            
            this.btSair.setOnAction((e) -> {
                Platform.exit();
            });
            
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
    }
    
    private void demonstrarUsuario(Usuario usuario)
    {
        this.nome.setText(usuario.getNome());
        this.avatar.setImage(new Image(usuario.getFoto().getInputStream()));
        this.avatar.setClip(new Circle(this.avatar.getX() + this.avatar.getFitWidth() / 2,
                                this.avatar.getY() + this.avatar.getFitHeight() / 2, this.avatar.getFitWidth() / 2));
    }
    
    private void inicializarFeedView(FeedNoticiasController controller) throws IOException
    {
        FXMLLoader carregador = new FXMLLoader(this.getClass().getResource(ConfiguracaoFuzzy.Feed.VIEW));
        carregador.setController(controller);
        
        this.feedView = carregador.load();
        this.definirView(this.feedView);
    }
    
    private void definirView(Node view)
    {
        this.root.setCenter(view);
    }
}
