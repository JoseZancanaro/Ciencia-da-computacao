package cryptowarrior.core.filesystem;

// JavaUtils
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileSystemPartFactory
{
    public static FileSystemPart create(String path)
    {
        Path jPath = Paths.get(path);
        
        if (Files.isDirectory(jPath)) {
            return new Folder(path);
        }
        else {
            return new File(path);
        }
    }
}
