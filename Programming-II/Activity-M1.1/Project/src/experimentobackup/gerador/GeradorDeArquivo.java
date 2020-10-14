package experimentobackup.gerador;

import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.OutputStream;

public class GeradorDeArquivo
{
    private IGeradorDeCaractere gerador;
    
    public GeradorDeArquivo(IGeradorDeCaractere gerador)
    {
        this.gerador = gerador;
    }
    
    public void gerar (String nome, int tamanhoEmBytes) throws Exception
    {
        OutputStream bos = new BufferedOutputStream(new FileOutputStream(nome));
        for (int i = 0; i < tamanhoEmBytes; i++)
            bos.write(gerador.proximo());
        bos.close();
    }
}
