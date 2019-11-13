package javaide.dominio.linguagem.cpp;

import javaide.dominio.VerificadorSintaxe;

public class CppVerificadorSintaxe implements VerificadorSintaxe
{
    @Override
    public void verificar()
    {
        System.out.println("Estou verificando sintaxe de C++.");
    }
}
