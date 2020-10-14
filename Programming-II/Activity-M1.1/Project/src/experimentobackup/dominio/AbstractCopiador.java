package experimentobackup.dominio;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public abstract class AbstractCopiador
{
    protected long copiar (InputStream is, OutputStream os) throws FileNotFoundException, IOException {
        int byteLido;
        
        // Registrar momento de início da cópia
        long inicio = System.currentTimeMillis();
        
        // Copiar enquanto há conteúdo
        while ((byteLido = is.read()) != -1)
            os.write(byteLido);
        
        // Registrar fim de cópia
        long fim = System.currentTimeMillis();
        
        return (fim - inicio);
    }
    public abstract long copiar (String entrada, String saida) throws FileNotFoundException, IOException;
}