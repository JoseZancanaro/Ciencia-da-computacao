/***
    Esta classe representa uma IDE (Integrated Development Environment) que deve ser
 capaz de abrir arquivos de código fonte em várias linguagens diferentes. Por exemplo,
 você poderia abrir um código fonte JAVA, e em seguida abrir outro arquivo de código
 fonte PHP, e em seguida abrir um código fonte escrito em C++, etc. 
  
    Sempre que um novo arquivo de código fonte é aberto a IDE deve: 
        1) colorir o código do arquivo que está sendo aberto (syntax highlight);
        2) autocompletar o código
        3) indicar visualmente possíveis erros sintáticos encontrados no código
        
    Cada uma das funcionalidades acima é implementada de forma diferente para cada linguagem
de programação suportada pela IDE. 

    Como implementar a IDE para que novas linguagens sejam suportadas? Ou seja, 
como permitir que as 3 funcionalidades acima sejam possíveis para qualquer linguagem 
de programação suportada pela IDE?
        
    Você deve resolver este problema utilizando no mínimo os padrões de projeto
criacionais "Simple Factory" e "Abstract Factory" (o uso do padrão Singleton é opcional).
        
    Você não deve realmente implementar as funcionalidades descritas acima (completar de 
código, colorir código, etc), pois a implementação destas funcionalidades demandaria 
uma quantidade enorme de tempo.
    
    Para esta avaliação sua implementação deve APENAS SIMULAR que as ações estão sendo 
executadas pela IDE. Por exemplo, ao invés de realmente implementar o "colorimento de 
código para PHP" você deve apenas exibir uma mensagem como "Coloringo código PHP". 
    
    Observe que esta é uma avaliação sobre os padrões de projeto criacionais, portanto 
para cumprir o que se espera desta avaliação basta que você demonstre a capacidade de 
identificar e implementar a estrutura dos padrões de projeto solicitados (Simple Factory e
Abstract Factory).

DUPLA:
- Israel Efraim de Oliveira
- José Carlos Zancanaro

*/

package javaide;

import javaide.dominio.AutoCompletador;
import javaide.dominio.RecursoLinguagemFactory;
import javaide.dominio.RecursoLinguagemFactoryCreator;
import javaide.dominio.Ressaltador;
import javaide.dominio.VerificadorSintaxe;

public class IDE
{
    private static IDE instancia;
    
    private IDE()
    {
        iniciar();
    }
    
    private void iniciar()
    {
        System.out.println("Inicializando IDE.");
    }
    
    public static IDE getInstancia()
    {
        if (instancia == null)
            instancia = new IDE();
        return instancia;
    }
        
    public void abrirArquivo(String caminhoDoArquivo)
    {
        RecursoLinguagemFactory fabrica = RecursoLinguagemFactoryCreator.criar(caminhoDoArquivo);
        
        Ressaltador ressaltador = fabrica.criarRessaltador();
        VerificadorSintaxe verificador = fabrica.criarVerificadorSintaxe();
        AutoCompletador autoCompletador = fabrica.criarAutoCompletador();
        
        ressaltador.ressaltar();
        verificador.verificar();
        autoCompletador.autoCompletar();
    }
}
