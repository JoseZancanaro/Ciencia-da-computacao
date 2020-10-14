package cryptowarrior.gui.application;

public class Configuration
{
    public static final String DEFAULT_VIEW_FOLDER = "/cryptowarrior/gui/application/view/";
    public static final String DEFAULT_ASSETS_FOLDER = DEFAULT_VIEW_FOLDER + "assets/";
    public static final String DEFAULT_IMAGE_FOLDER = DEFAULT_ASSETS_FOLDER + "image/";
    
    public static final String IMG_LOGO = DEFAULT_IMAGE_FOLDER + "logo-improved-64.png";
    
    public class MainWindow
    {
        public static final String TITLE = "Crypto Warrior";
        public static final double WIDTH = 1000.0;
        public static final double HEIGHT = 535.0;
        
        public static final String VIEW = Configuration.DEFAULT_VIEW_FOLDER + "CryptoWarriorApplicationView.fxml";
        
        public static final String CSS_SELECTED = "-fx-cursor: hand; -fx-background-color: #6B7076; " +
                                                  "-fx-border-width: 0px 0px 0px 4px; -fx-border-color: #373B3E;";
        
        public static final String CSS_NORMAL = "";
        
    }
    
    public class EncryptionScene
    {
        public static final String VIEW = Configuration.DEFAULT_VIEW_FOLDER + "CryptoWarriorEncryptionSceneView.fxml";
    }
    
    public class DecryptionScene
    {
        public static final String VIEW = Configuration.DEFAULT_VIEW_FOLDER + "CryptoWarriorDecryptionSceneView.fxml";
    }
    
    public class HomeScene
    {
        public static final String VIEW = Configuration.DEFAULT_VIEW_FOLDER + "CryptoWarriorHomeSceneView.fxml";
    }
}
