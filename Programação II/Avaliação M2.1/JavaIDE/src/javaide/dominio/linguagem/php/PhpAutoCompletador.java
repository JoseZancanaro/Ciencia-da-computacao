package javaide.dominio.linguagem.php;

import javaide.dominio.AutoCompletador;

public class PhpAutoCompletador implements AutoCompletador
{
    @Override
    public void autoCompletar()
    {
        System.out.println("Estou autocompletando em PHP.");
    }
}
