package fuzzy.gui.cliente.model;

// CryptoWarrior

// JavaUtils
import java.util.Optional;
import javafx.application.Platform;

// JavaFX
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.image.Image;
import javafx.stage.Stage;

public class Alerta
{
    // private static final String ICONE = Configuration.IMG_LOGO;
    
    private Alerta() {} // Do not instantiate this!
            
    public static void show(String title, String description, Alert.AlertType type)
    {
        Platform.runLater(() -> {
            Alert alert = new Alert(type);
            // ((Stage)alert.getDialogPane().getScene().getWindow()).getIcons().add(new Image(VaultAlert.ICONE));
            alert.getDialogPane().setPrefSize(400, 200);
            alert.setTitle(title);
            alert.setContentText(description);
            alert.showAndWait();
        });
    }
}
