package cryptowarrior.gui.application.control;

// CryptoWarrior
import cryptowarrior.core.engine.CryptoEngineFactory;
import cryptowarrior.core.engine.CryptoEngineFactoryCreator;
import cryptowarrior.core.engine.IDecryptor;
import cryptowarrior.core.engine.SignMaskManager;
import cryptowarrior.core.engine.SignStack;
import cryptowarrior.core.filesystem.FileSystemPartFactory;
import cryptowarrior.gui.application.model.VaultAlert;

// JavaUtils
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;
import java.util.List;
import java.io.IOException;


// JavaFX
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ListView;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.BorderPane;
import javafx.stage.FileChooser;

public class CryptoWarriorDecryptionSceneController implements Initializable
{
    @FXML
    private BorderPane parentNode;
    
    // Select and sumbit <File Path>
    @FXML
    private TextField tDirectory;
    
    @FXML
    private Button bFind;
    
    // Select and manage <Ciphers>
    @FXML
    private ComboBox<String> cbActualCipher;
    
    @FXML
    private Button bAddCipher;
    
    @FXML
    private ListView listCiphers;
    private ObservableList<String> ciphers;
    
    @FXML
    private MenuItem mLimpar;
    
    // Run <Cryptograph>
    @FXML
    private Button bRunDecryptography;
    
    @Override
    public void initialize(URL location, ResourceBundle resources)
    {
        setupControls();
        setupEvents();
    }
    
    private void setupControls()
    {
        addObservableListIntoListView();
        addCiphersIntoComboBox();
    }
    
    private void execute()
    {
        try {
            List<String> ciphersList = new ArrayList<>();
            this.ciphers.forEach(s -> ciphersList.add(s));

            SignStack ss = SignStack.valueOf(ciphersList);

            CryptoEngineFactory factory = CryptoEngineFactoryCreator.create(ss);
            IDecryptor decryptor = factory.createDecryptor();
            decryptor.decrypt( FileSystemPartFactory.create(this.tDirectory.getText()) );
            
            VaultAlert.show("Arquivo Decriptografado!", "O arquivo/diretório foi decriptografado com sucesso!", Alert.AlertType.INFORMATION);
        } catch (IOException ex) {
            VaultAlert.show("Erro ao decriptografar", "Erro inesperado ao decriptografar. Ciphers corretos?", Alert.AlertType.ERROR);
        } catch (Exception ex) {
            VaultAlert.show("Erro de lógica", "Algum campo foi deixado vazio ou contém valores incorretos.", Alert.AlertType.ERROR);
        }
    }
    
    private void setupEvents()
    {
        this.bAddCipher.setOnAction(e -> {
            if (!this.cbActualCipher.getSelectionModel().isEmpty()) {
                this.ciphers.add(this.cbActualCipher.getValue());
                this.cbActualCipher.getSelectionModel().clearSelection();
            }
        });
        
        this.listCiphers.setOnKeyPressed(e -> {
            if (e.getCode().equals(KeyCode.DELETE)) {
                if (!this.listCiphers.getSelectionModel().isEmpty()) {
                    this.ciphers.remove(this.listCiphers.getSelectionModel().getSelectedItem());
                }
            }
        });
        
        this.bFind.setOnAction(e -> {
            FileChooser fc = new FileChooser();
            fc.setTitle("Definir Arquivo ou Diretório para Decriptografar");
            fc.setInitialDirectory(new java.io.File(".."));
            java.io.File f = fc.showOpenDialog(parentNode.getScene().getWindow());
            if (f != null) {
                this.tDirectory.setText(f.getAbsolutePath());
            }
        });
        
        this.mLimpar.setOnAction(e -> {
            this.ciphers.clear();
        });
        
        this.bRunDecryptography.setOnAction(e -> this.execute());
    }
    
    private void addCiphersIntoComboBox()
    {
        SignMaskManager.Engine[] engines = SignMaskManager.Engine.values();
        
        ObservableList<String> cipherList = FXCollections.observableArrayList();
        
        for (SignMaskManager.Engine engine : engines)
            if (engine.getValue() > 0) cipherList.add(engine.getName());
        
        this.cbActualCipher.setItems(cipherList);
    }
    
    private void addObservableListIntoListView()
    {
        this.ciphers = FXCollections.observableArrayList();
        this.listCiphers.setItems(this.ciphers);
    }
}
