package cryptowarrior.gui.application.control;

// CryptoWarrior
import cryptowarrior.gui.application.Configuration;

// JavaFX
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;

public class CryptoWarriorApplicationController implements Initializable
{
    @FXML
    private BorderPane parentNode;
    
    @FXML
    private ImageView imgLogo;
    
    // Home
    private BorderPane homeView;
    @FXML
    private HBox bSetHomeView;
    
    // Cryptography
    private BorderPane cryptographyView;
    @FXML
    private HBox bSetEncryptionView;
    
    // Decryptography
    private BorderPane decryptographyView;
    @FXML
    private HBox bSetDecryptionView;
    
    @Override
    public void initialize(URL location, ResourceBundle resources)
    {
        try {
            loadViews();
        }
        catch (IOException ex) {
            System.out.println(ex);
        }
    }
    
    private void setupScene()
    {
        this.imgLogo.setImage(new Image(Configuration.IMG_LOGO));
    }
    
    private void loadViews() throws IOException
    {
        loadHomeView();
        refreshView(homeView);
        setSelected(bSetHomeView);
        loadEncryptionView();
        loadDecryptionView();
    }
    
    private void loadHomeView() throws IOException
    {
        FXMLLoader loader = new FXMLLoader(getClass().getResource(Configuration.HomeScene.VIEW));
        loader.setController(new CryptoWarriorHomeSceneController());
        this.homeView = loader.load();
        
        this.bSetHomeView.setOnMouseClicked(e -> {
            this.refreshView(this.homeView);
            this.unselectAll();
            this.setSelected(this.bSetHomeView);
        });
    }
    
    private void loadEncryptionView() throws IOException
    {
        FXMLLoader loader = new FXMLLoader(getClass().getResource(Configuration.EncryptionScene.VIEW));
        loader.setController(new CryptoWarriorEncryptionSceneController());
        this.cryptographyView = loader.load();
        
        this.bSetEncryptionView.setOnMouseClicked(e -> {
            this.refreshView(this.cryptographyView);
            this.unselectAll();
            this.setSelected(this.bSetEncryptionView);
        });
    }
    
    private void loadDecryptionView() throws IOException
    {
        FXMLLoader loader = new FXMLLoader(getClass().getResource(Configuration.DecryptionScene.VIEW));
        loader.setController(new CryptoWarriorDecryptionSceneController());
        this.decryptographyView = loader.load();
        
        this.bSetDecryptionView.setOnMouseClicked(e -> {
            this.refreshView(this.decryptographyView);
            this.unselectAll();
            this.setSelected(this.bSetDecryptionView);
        });
    }
    
    private void refreshView(BorderPane view)
    {
        this.parentNode.setCenter(view);
    }
    
    private void setSelected(HBox hbox)
    {
        hbox.setStyle(Configuration.MainWindow.CSS_SELECTED);
    }
    
    private void unselect(HBox hbox)
    {
        hbox.setStyle(Configuration.MainWindow.CSS_NORMAL);
    }
    
    private void unselectAll()
    {
        this.unselect(this.bSetHomeView);
        this.unselect(this.bSetEncryptionView);
        this.unselect(this.bSetDecryptionView);
    }
}
