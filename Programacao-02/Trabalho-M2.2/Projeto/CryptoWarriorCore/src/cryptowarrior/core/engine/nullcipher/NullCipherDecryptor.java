package cryptowarrior.core.engine.nullcipher;

// CryptoWarrior
import cryptowarrior.core.engine.IDecryptor;
import cryptowarrior.core.filesystem.FileSystemPart;
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.IOException;

public class NullCipherDecryptor extends IDecryptor
{
    @Override
    public void decryptFile(FileSystemPart fsp) {}

    @Override
    public ByteStream run(ByteStream bs) throws IOException 
    {
        return bs;
    }
}
