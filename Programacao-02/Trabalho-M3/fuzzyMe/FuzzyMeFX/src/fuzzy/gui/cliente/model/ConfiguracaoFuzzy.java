package fuzzy.gui.cliente.model;

import fuzzy.gui.cliente.control.FeedNoticiasController;
import fuzzy.gui.cliente.control.FuzzyMeController;
import fuzzy.model.assets.Usuario;
import javafx.geometry.Dimension2D;

public class ConfiguracaoFuzzy
{
    public static final String RAIZ = "/fuzzy/gui/cliente/";
    public static final String CAMINHO_VIEW = RAIZ + "view/";
    
    public static final String TITULO = "Fuzzy.Me Social Network";
    public static final Dimension2D DIMENSAO = new Dimension2D(900, 660);
    
    public static class FuzzyMe
    {
        public static final String VIEW = ConfiguracaoFuzzy.CAMINHO_VIEW + "FuzzyMeView.fxml";
        
        public static FuzzyMeController getController(Usuario autenticado)
        {
            return new FuzzyMeController(autenticado);
        }
    }
    
    public static class Feed
    {
        public static final String VIEW = ConfiguracaoFuzzy.CAMINHO_VIEW + "FeedNoticiasView.fxml";
        
        public static FeedNoticiasController getController(Usuario autenticado)
        {
            return new FeedNoticiasController(autenticado);
        }
    }
}
