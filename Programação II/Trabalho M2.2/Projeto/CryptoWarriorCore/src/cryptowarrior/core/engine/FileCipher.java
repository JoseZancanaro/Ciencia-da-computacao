package cryptowarrior.core.engine;

// CryptoWarrior
import cryptowarrior.core.filesystem.FileSystemPart;
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.BufferedOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

public abstract class FileCipher
{
    protected void writeByteStream(FileSystemPart fsp, ByteStream bs) throws FileNotFoundException, IOException
    {
        if (fsp.getChildren() == null) { // it's a file.
            OutputStream os = new BufferedOutputStream(new FileOutputStream(fsp.getPath()));
            
            for (Integer b : bs.getList()) {
                os.write(b);
            }
            
            os.close();
        }
        // not a file, don't write.
    }
}
