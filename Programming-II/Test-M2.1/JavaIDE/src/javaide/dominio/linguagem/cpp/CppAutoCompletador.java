package javaide.dominio.linguagem.cpp;

import javaide.dominio.AutoCompletador;

public class CppAutoCompletador implements AutoCompletador
{
    @Override
    public void autoCompletar()
    {
        System.out.println("Estou autocompletando C++.");
    }
}
