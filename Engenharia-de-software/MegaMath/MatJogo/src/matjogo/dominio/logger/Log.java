package matjogo.dominio.logger;

import javafx.scene.image.Image;

public class Log
{
    private final String title;
    private final String type;
    private final String description;
    private final Object arg;

    public Log(String title, String description)
    {
        this.title = title;
        this.type = "";
        this.description = description;
        this.arg = null;
    }
    
    public Log(String title, String type, String description, Object arg)
    {
        this.title = title;
        this.type = type;
        this.description = description;
        this.arg = arg;
    }

    public String getTitle()
    {
        return title;
    }

    public String getType()
    {
        return type;
    }

    public String getDescription()
    {
        return description;
    }

    public Object getArg()
    {
        return arg;
    }
    
    public static Log criar(String titulo, String tipo, String descricao, Object arg)
    {
        switch (tipo) {
            case "fx-dado":
                return new Log(titulo, tipo, descricao, new Image("/matjogo/view/assets/img/feedback/dado.png"));
            case "fx-armadilha":
                return new Log(titulo, tipo, descricao, new Image("/matjogo/view/assets/img/feedback/erro.png"));
            case "fx-error":
                return new Log(titulo, tipo, descricao, new Image("/matjogo/view/assets/img/feedback/erro.png"));
            case "fx-endgame":
                return new Log(titulo, tipo, descricao, new Image("/matjogo/view/assets/img/feedback/winner.png"));
            default:
                return new Log(titulo, tipo, descricao, arg);
        }
    }
}
