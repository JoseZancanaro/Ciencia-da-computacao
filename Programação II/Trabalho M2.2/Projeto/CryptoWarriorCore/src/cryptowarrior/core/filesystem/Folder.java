package cryptowarrior.core.filesystem;

// CryptoWarrior
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Stream;

public class Folder extends FileSystemPart
{
    
    List<FileSystemPart> children;

    public Folder(String path)
    {
        if (path == null)
            throw new NullPointerException("Mentioned path is empty.");
        
        this.path = path;
        this.children = new ArrayList<>();
        
        this.findAllChildren();
    }
    
    private void findAllChildren()
    {
        Path jPath = Paths.get(this.getPath());
        
        try {
            Stream<Path> folder = Files.list(jPath);
            
            folder.forEach(p -> {
                this.add(FileSystemPartFactory.create(p.toAbsolutePath().toString()));
            });
            
        }
        catch (Exception ignore) {}
    }
    
    @Override
    public void add(FileSystemPart fsp)
    {
        children.add(fsp);
    }

    @Override
    public void remove(FileSystemPart fsp)
    {
        children.remove(fsp);
    }

    @Override
    public ByteStream getByteStream() throws IOException
    {
        return null;
    }

    @Override
    public List<FileSystemPart> getChildren()
    {
        return children;
    }

    @Override
    public void transverse()
    {
        System.out.println(this.getPath() + " " + this.getChildren().size());
        
        this.getChildren().forEach(c -> {
            c.transverse();
        });
    }
    
}
