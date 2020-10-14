package cryptowarrior.core.engine.nullcipher;

// CryptoWarrior
import cryptowarrior.core.engine.IEncryptor;
import cryptowarrior.core.filesystem.FileSystemPart;
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.IOException;

public class NullCipherEncryptor extends IEncryptor
{
    @Override
    public void encryptFile(FileSystemPart fsp) {}

    @Override
    public ByteStream run(ByteStream bs) throws IOException
    {
        return bs;
    }
}
