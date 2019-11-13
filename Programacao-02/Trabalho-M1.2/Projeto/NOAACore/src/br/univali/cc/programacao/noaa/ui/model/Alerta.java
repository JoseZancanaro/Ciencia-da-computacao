package br.univali.cc.programacao.noaa.ui.model;

// import br.univali.cc.programacao.noaa.ui.gerenciador.NOAAConfig;
import java.util.Optional;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.image.Image;
import javafx.stage.Stage;

public class Alerta
{
    private static final String ICONE = "/br/univali/cc/programacao/noaa/ui/model/image/noaa_logo.png";
    
    private Alerta() {} // Não instancia isso!
            
    public static Optional<ButtonType> mostrar(String titulo, String descricao, Alert.AlertType tipo)
    {
        Alert alerta = new Alert(tipo);
        ((Stage)alerta.getDialogPane().getScene().getWindow()).getIcons().add(new Image(Alerta.ICONE));
        alerta.getDialogPane().setPrefSize(400, 200);
        alerta.setTitle(titulo);
        alerta.setContentText(descricao);
        return alerta.showAndWait();
    }
}
