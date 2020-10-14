package javaide.dominio;

public interface RecursoLinguagemFactory
{
    Ressaltador criarRessaltador();
    AutoCompletador criarAutoCompletador();
    VerificadorSintaxe criarVerificadorSintaxe();
}
