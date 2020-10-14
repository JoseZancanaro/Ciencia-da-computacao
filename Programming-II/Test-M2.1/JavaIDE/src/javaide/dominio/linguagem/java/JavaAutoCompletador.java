package javaide.dominio.linguagem.java;

import javaide.dominio.AutoCompletador;

public class JavaAutoCompletador implements AutoCompletador
{
    @Override
    public void autoCompletar()
    {
        System.out.println("Estou autocompletando em Java.");
    }  
}
