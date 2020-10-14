package fuzzy.gui.cliente.model;

import fuzzy.model.assets.ImagemFuzzy;
import fuzzy.model.assets.Usuario;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class AplicacaoFuzzy extends Application
{
    
    private void configurarStage(Stage stage) throws Exception
    {
        // teste
        Usuario autenticado = new Usuario(1, "Israel Efraim", "j", new ImagemFuzzy("/home/efraim/Documents/CC/fuzzy.me/FuzzyMeFX/src/fuzzy/gui/cliente/view/assets/image/pp2.jpg"));
        
        stage.setTitle(ConfiguracaoFuzzy.TITULO);
        
        FXMLLoader carregador = new FXMLLoader(this.getClass().getResource(ConfiguracaoFuzzy.FuzzyMe.VIEW));
        carregador.setController(ConfiguracaoFuzzy.FuzzyMe.getController(autenticado));
        Parent raiz = carregador.load();
        
        Scene scene = new Scene(raiz, ConfiguracaoFuzzy.DIMENSAO.getWidth(), ConfiguracaoFuzzy.DIMENSAO.getHeight());
        stage.setScene(scene);
    }
    
    @Override
    public void start(Stage stage) throws Exception
    {
        configurarStage(stage);
        stage.show();
    }
    
    public static void main(String[] args)
    {
        Application.launch(args);
    }
}
