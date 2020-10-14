package matjogo.dominio;

import java.util.ArrayList;
import javafx.scene.image.Image;

public class JogadoresSimpleFactory
{
    public static ArrayList<Jogador> criar()
    {
        ArrayList<Jogador> jogadores = new ArrayList<>();
        
        for (int i = 0; i < 4; i++) {
            jogadores.add(new Jogador(i + 1, "P " + (i+1), new Image("/matjogo/view/assets/img/players/Player" + i + ".png")));
        }
        
        return jogadores;
    }
}
