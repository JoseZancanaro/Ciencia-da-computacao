package experimentobackup;

import java.util.List;
import java.util.LinkedList;
import java.io.IOException;

import experimentobackup.dominio.*;
import experimentobackup.experimento.*;
import experimentobackup.gerador.*;
import java.io.BufferedInputStream;
import java.io.FileInputStream;

/**
 * @author Israel Efraim de Oliveira,
 * @author José Carlos Zancanaro. 
 */
public class Inicializador {
    public static void main(String[] args) throws IOException, Exception
    {
        // Caminho onde as amostras estão ou serão geradas
        String caminho = "./amostras/entrada";
        
        // Quantidade de amostras, lembrando que a primeira terá tamanho 2^0 e a última 2^n
        int qtdAmostras = 6;
        
        // Criar lista de amostras
        List<Amostra> amostras = new LinkedList<>();
        for (int i = 0; i <= qtdAmostras; i++) {
            amostras.add(new Amostra(String.format("%s/f%dmb.txt", caminho, (int)Math.pow(2, i)), (int)Math.pow(2, i)));
        }
        
        // Gerar, se necessário
        // Caso não queira gerar, apenas comente o bloco abaixo.
        GeradorDeArquivo gda = new GeradorDeArquivo(new GeradorDeCaractereAleatorio());
        for (Amostra amostra : amostras) {
            gda.gerar(amostra.getArquivo(), 1024 * 1024 * amostra.getTamanho());
        }
                
        // Realizar testes
        TestadorCopiador tc = new TestadorCopiador("./amostras/saida", amostras, 8, 3); // 8 cópias, descartar os 3 primeiros resultados
        tc.testar("Sem Buffer", new Copiador());
        tc.testar("Com Buffer", new CopiadorBuffer());
        
        // Exportar testes para csv
        tc.exportarTodos();
    }
}