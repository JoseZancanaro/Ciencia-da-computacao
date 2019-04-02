package fuzzy.model.assets;

import java.io.BufferedInputStream;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

public class ImagemFuzzy
{
    private final byte[] bytes;

    public ImagemFuzzy(byte[] bytes)
    {
        this.bytes = bytes;
    }

    public ImagemFuzzy(String nome) throws IOException
    {
        BufferedInputStream bs = new BufferedInputStream(new FileInputStream(nome));
        this.bytes = this.createByteArray(bs);
    }
    
    public ImagemFuzzy(File arquivo) throws IOException
    {
        this.bytes = this.createByteArray(new BufferedInputStream(new FileInputStream(arquivo)));
    }
    
    public ImagemFuzzy(InputStream is)
    {
        this.bytes = this.createByteArray(is);
    }
    
    private byte[] createByteArray(InputStream is)
    {
        byte[] byteArray = null;
        
        try {
            byteArray = new byte[is.available()];
            
            int byteLido, posicao = 0;
            while ((byteLido = is.read()) != -1)
                byteArray[posicao++] = (byte) byteLido;
        }
        catch (IOException ignore) {}
        
        
        return byteArray;
    }
    
    public byte[] getBytes()
    {
        return this.bytes;
    }
    
    public InputStream getInputStream()
    {
        return new BufferedInputStream(new ByteArrayInputStream(this.bytes));
    }
}
