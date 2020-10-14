package cryptowarrior.core.engine;

// CryptoWarrior
import cryptowarrior.core.filesystem.FileSystemPart;
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.IOException;

public abstract class IEncryptor extends FileCipher
{    
    public abstract ByteStream run(ByteStream bs) throws IOException;
    
    public abstract void encryptFile(FileSystemPart fsp) throws IOException;
    
    public void encrypt(FileSystemPart fsp) throws IOException
    {
        if (fsp.getChildren() == null) {
            this.encryptFile(fsp);
        }
        else {
            for (FileSystemPart cFsp : fsp.getChildren()) {
                this.encrypt(cFsp);
            }
        }
    }
}
