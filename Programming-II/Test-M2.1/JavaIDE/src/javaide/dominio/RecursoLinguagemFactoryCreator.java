package javaide.dominio;

import javaide.dominio.linguagem.cpp.CppRecursoLinguagemFactory;
import javaide.dominio.linguagem.java.JavaRecursoLinguagemFactory;
import javaide.dominio.linguagem.nulo.NuloRecursoLinguagemFactory;
import javaide.dominio.linguagem.php.PhpRecursoLinguagemFactory;

public class RecursoLinguagemFactoryCreator
{
    public static RecursoLinguagemFactory criar(String caminhoDoArquivo)
    {
        String extensao = getExtensaoDoArquivo(caminhoDoArquivo);
        
        switch (extensao) {
            case ".cpp":
                return new CppRecursoLinguagemFactory();
            case ".java":
                return new JavaRecursoLinguagemFactory();
            case ".php":
                return new PhpRecursoLinguagemFactory();
            default:
                return new NuloRecursoLinguagemFactory();
        }
    }
    
    private static String getExtensaoDoArquivo(String caminhoDoArquivo)
    {
        int indiceDoPonto = caminhoDoArquivo.indexOf(".");
        if (indiceDoPonto > 0) {
            return caminhoDoArquivo.substring(indiceDoPonto);
        }
        return "";
    }
}
