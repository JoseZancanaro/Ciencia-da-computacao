package javaide.dominio.linguagem.java;

import javaide.dominio.VerificadorSintaxe;

public class JavaVerificadorSintaxe implements VerificadorSintaxe
{
    @Override
    public void verificar()
    {
        System.out.println("Estou verificando sintaxe em Java.");
    }
}
