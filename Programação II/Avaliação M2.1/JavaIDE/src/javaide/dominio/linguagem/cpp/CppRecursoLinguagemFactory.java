package javaide.dominio.linguagem.cpp;

import javaide.dominio.RecursoLinguagemFactory;
import javaide.dominio.Ressaltador;
import javaide.dominio.VerificadorSintaxe;
import javaide.dominio.AutoCompletador;

public class CppRecursoLinguagemFactory implements RecursoLinguagemFactory
{
    @Override
    public Ressaltador criarRessaltador()
    {
        return new CppRessaltador();
    }
    
    @Override
    public AutoCompletador criarAutoCompletador()
    {
        return new CppAutoCompletador();
    }
    
    @Override
    public VerificadorSintaxe criarVerificadorSintaxe()
    {
        return new CppVerificadorSintaxe();
    }
}
