package experimentobackup.dominio;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class CopiadorBuffer extends AbstractCopiador
{
    public CopiadorBuffer() 
    {
    }

    @Override
    public long copiar(String entrada, String saida) throws FileNotFoundException, IOException 
    {
        // Instanciar streams com buffer
        InputStream fis = new BufferedInputStream(new FileInputStream(entrada));
        OutputStream fos = new BufferedOutputStream(new FileOutputStream(saida));
        
        // Chamar método de cópia adquirido por herança
        long tempoDeCopia = this.copiar(fis, fos);
        
        // Fechar streams
        fis.close();
        fos.close();
        
        return tempoDeCopia;
    }
}