package matjogo.dominio.control;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;
import static javafx.scene.layout.Region.USE_PREF_SIZE;
import matjogo.dominio.logger.Log;

public final class FXLog extends HBox
{
    @FXML private ImageView ivLog;
    @FXML private Label lTitulo;
    @FXML private Label lDescricao;
    
    public FXLog(Log log)
    {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/matjogo/view/LogView.fxml"));
            loader.setRoot(this);
            loader.setController(this);
            loader.load();

            
            this.setImagemLog((Image) log.getArg());
            this.setTitulo(log.getTitle());
            this.setDescricao(log.getDescription());
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public void setImagemLog(Image image)
    {
        this.ivLog.setImage(image);
        this.ivLog.setFitWidth(USE_PREF_SIZE);
    }

    public void setTitulo(String titulo)
    {
        this.lTitulo.setText(titulo);
    }

    public void setDescricao(String descricao)
    {
        this.lDescricao.setText(descricao);
    }
}