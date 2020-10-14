package javaide.dominio.linguagem.java;

import javaide.dominio.AutoCompletador;
import javaide.dominio.RecursoLinguagemFactory;
import javaide.dominio.Ressaltador;
import javaide.dominio.VerificadorSintaxe;

public class JavaRecursoLinguagemFactory implements RecursoLinguagemFactory
{
    @Override
    public Ressaltador criarRessaltador()
    {
        return new JavaRessaltador();
    }

    @Override
    public AutoCompletador criarAutoCompletador()
    {
        return new JavaAutoCompletador();
    }

    @Override
    public VerificadorSintaxe criarVerificadorSintaxe()
    {
        return new JavaVerificadorSintaxe();
    }
}
