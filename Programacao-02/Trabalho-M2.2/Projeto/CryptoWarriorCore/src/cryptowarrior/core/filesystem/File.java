package cryptowarrior.core.filesystem;

// CryptoWarrior
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.List;

public class File extends FileSystemPart
{
    public File(String path) throws NullPointerException
    {
        if (path == null)
            throw new NullPointerException("Mentioned path is empty.");
        this.path = path;
    }
    
    @Override
    public void add(FileSystemPart fsp) {}

    @Override
    public void remove(FileSystemPart fsp) {}

    @Override
    public List<FileSystemPart> getChildren()
    {
        return null;
    }

    @Override
    public ByteStream getByteStream() throws IOException
    {
        return ByteStream.fromInputStream ( new BufferedInputStream(new FileInputStream(this.getPath())) );
    }

    @Override
    public void transverse()
    {
        System.out.println(this.getPath());
    }
}
