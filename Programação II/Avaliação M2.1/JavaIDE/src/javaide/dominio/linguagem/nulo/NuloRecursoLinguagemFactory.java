package javaide.dominio.linguagem.nulo;

import javaide.dominio.AutoCompletador;
import javaide.dominio.RecursoLinguagemFactory;
import javaide.dominio.Ressaltador;
import javaide.dominio.VerificadorSintaxe;

public class NuloRecursoLinguagemFactory implements RecursoLinguagemFactory
{
    @Override
    public Ressaltador criarRessaltador()
    {
        return new NuloRessaltador();
    }

    @Override
    public AutoCompletador criarAutoCompletador()
    {
        return new NuloAutoCompletador();
    }

    @Override
    public VerificadorSintaxe criarVerificadorSintaxe()
    {
        return new NuloVerificadorSintaxe();
    }
}
