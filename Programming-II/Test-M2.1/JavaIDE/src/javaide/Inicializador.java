package javaide;

/**
 * 
 * @author Israel Efraim de Oliveira
 * @author José Carlos Zancanaro
 */
public class Inicializador
{
    static void testar(String caminhoDoArquivo)
    {
        IDE ide = IDE.getInstancia();
        
        System.out.println("Testar Arquivo: " + caminhoDoArquivo);
        ide.abrirArquivo(caminhoDoArquivo);
        System.out.println("-- Fim Simulação --");
    }
    
    public static void main(String[] args)
    {
        testar("teste.cpp");
        testar("main.java");
        testar("index.php");
        testar("interpolacao.hs");
    }
}
