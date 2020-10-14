package javaide.dominio.linguagem.php;

import javaide.dominio.VerificadorSintaxe;

public class PhpVerificadorSintaxe implements VerificadorSintaxe
{
    @Override
    public void verificar()
    {
        System.out.println("Estou verificando sintaxe em PHP.");
    }
}
