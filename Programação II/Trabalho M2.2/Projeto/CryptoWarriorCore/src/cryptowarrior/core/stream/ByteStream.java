package cryptowarrior.core.stream;

// JavaUtils
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class ByteStream
{
    private List<Integer> bytes;

    public ByteStream()
    {
        bytes = new ArrayList<>();
    }
    
    public ByteStream(byte[] bytes)
    {
        this.bytes = new ArrayList<>();
        for (byte b : bytes) {
            this.bytes.add((int) b);
        }
    }
    
    public void append(int content)
    {
        bytes.add(content);
    }
    
    public int get(int index)
    {
        return bytes.get(index);
    }
    
    public void remove(int index)
    {
        this.bytes.remove(index);
    }
    
    public void forEach(Consumer<Integer> action)
    {
        this.bytes.forEach(action);
    }
    
    public int[] toArray()
    {
        int []byteArray = new int[bytes.size()];
        
        for (int i = 0; i < bytes.size(); i++)
            byteArray[i] = bytes.get(i);
        
        return byteArray;
    }
    
    public byte[] toByteArray()
    {
        byte []byteArray = new byte[bytes.size()];
        
        for (int i = 0; i < bytes.size(); i++)
            byteArray[i] = bytes.get(i).byteValue();
        
        return byteArray;
    }
    
    public List<Integer> getList()
    {
        return bytes;
    }
    
    public static ByteStream fromInputStream(InputStream is) throws IOException
    {
        ByteStream bs = new ByteStream();
        
        int b;
        while ((b = is.read()) != -1) {
            bs.append(b);
        }
        
        return bs;
    }
}
