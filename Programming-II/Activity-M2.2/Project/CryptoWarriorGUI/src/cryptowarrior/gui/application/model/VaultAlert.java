package cryptowarrior.gui.application.model;

// CryptoWarrior
import cryptowarrior.gui.application.Configuration;

// JavaUtils
import java.util.Optional;

// JavaFX
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.image.Image;
import javafx.stage.Stage;

public class VaultAlert
{
    private static final String ICONE = Configuration.IMG_LOGO;
    
    private VaultAlert() {} // Do not instantiate this!
            
    public static Optional<ButtonType> show(String title, String description, Alert.AlertType type)
    {
        Alert alert = new Alert(type);
        ((Stage)alert.getDialogPane().getScene().getWindow()).getIcons().add(new Image(VaultAlert.ICONE));
        alert.getDialogPane().setPrefSize(400, 200);
        alert.setTitle(title);
        alert.setContentText(description);
        return alert.showAndWait();
    }
}
