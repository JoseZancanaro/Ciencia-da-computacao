package javaide.dominio.linguagem.php;

import javaide.dominio.Ressaltador;

public class PhpRessaltador implements Ressaltador
{
    @Override
    public void ressaltar()
    {
        System.out.println("Estou ressaltando em PHP.");
    }
}
