package experimentobackup.dominio;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class Copiador extends AbstractCopiador
{   
    public Copiador()
    {
    }
    
    @Override
    public long copiar (String entrada, String saida) throws FileNotFoundException, IOException
    {
        // Instanciar streams sem buffer
        InputStream fis = new FileInputStream(entrada);
        OutputStream fos = new FileOutputStream(saida);
        
        // Chamar método de cópia adquirido por herança
        long tempoDeCopia = this.copiar(fis, fos);
        
        // Fechar streams
        fis.close();
        fos.close();
        
        return tempoDeCopia;
    }
}