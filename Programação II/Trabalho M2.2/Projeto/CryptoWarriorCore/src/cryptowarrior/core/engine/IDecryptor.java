package cryptowarrior.core.engine;

// CryptoWarrior
import cryptowarrior.core.filesystem.FileSystemPart;
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.IOException;

public abstract class IDecryptor extends FileCipher
{
    public abstract ByteStream run(ByteStream bs) throws IOException;
    
    public abstract void decryptFile(FileSystemPart fsp) throws IOException;
    
    public void decrypt(FileSystemPart fsp) throws IOException
    {
        if (fsp.getChildren() == null) {
            this.decryptFile(fsp);
        }
        else {
            for (FileSystemPart cFsp : fsp.getChildren()) {
                this.decrypt(cFsp);
            }
        }
    }
}