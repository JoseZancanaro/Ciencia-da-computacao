package javaide.dominio.linguagem.php;

import javaide.dominio.AutoCompletador;
import javaide.dominio.RecursoLinguagemFactory;
import javaide.dominio.Ressaltador;
import javaide.dominio.VerificadorSintaxe;

public class PhpRecursoLinguagemFactory implements RecursoLinguagemFactory
{
    @Override
    public Ressaltador criarRessaltador()
    {
        return new PhpRessaltador();
    }

    @Override
    public AutoCompletador criarAutoCompletador()
    {
        return new PhpAutoCompletador();
    }

    @Override
    public VerificadorSintaxe criarVerificadorSintaxe()
    {
        return new PhpVerificadorSintaxe();
    }
}
