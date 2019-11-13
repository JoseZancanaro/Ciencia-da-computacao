package cryptowarrior.gui.application;

// CryptoWarrior
import cryptowarrior.gui.application.control.CryptoWarriorApplicationController;

// JavaFX
import java.io.IOException;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

public class CryptoWarriorApplication extends Application
{
    public void setupWindow(Stage primaryStage) throws IOException
    {
        System.out.println(Configuration.MainWindow.VIEW);
        FXMLLoader loader = new FXMLLoader(getClass().getResource(Configuration.MainWindow.VIEW));
        loader.setController(new CryptoWarriorApplicationController());
        
        Parent parent = loader.load();
        
        Scene scene = new Scene(parent, Configuration.MainWindow.WIDTH, Configuration.MainWindow.HEIGHT);
        
        primaryStage.getIcons().add(new Image(Configuration.IMG_LOGO));
        primaryStage.setTitle(Configuration.MainWindow.TITLE);
        primaryStage.setScene(scene);
    }

    @Override
    public void start(Stage primaryStage) throws Exception
    {
        this.setupWindow(primaryStage);
        primaryStage.show();
    }
    
    public static void main(String[] args)
    {
        launch(args);
    }
    
}
