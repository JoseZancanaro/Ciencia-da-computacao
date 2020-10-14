package cryptowarrior.core.filesystem;

// CryptoWarrior
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.IOException;
import java.util.List;

public abstract class FileSystemPart
{
    protected String path;
    
    public abstract void add(FileSystemPart fsp);
    
    public abstract void remove(FileSystemPart fsp);
    
    public abstract void transverse();
    
    public abstract ByteStream getByteStream() throws IOException;
    
    public abstract List<FileSystemPart> getChildren();
    
    public String getPath()
    {
        return this.path;
    }
}
