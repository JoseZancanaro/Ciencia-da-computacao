package cryptowarrior.core.engine.fractionatedmorse;

// CryptoWarrior
import cryptowarrior.core.engine.IEncryptor;
import cryptowarrior.core.engine.nullcipher.NullCipherEncryptor;
import cryptowarrior.core.filesystem.FileSystemPart;
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.IOException;

public class FractionatedMorseEncrytor extends IEncryptor
{
    IEncryptor innerEncryptor;

    public FractionatedMorseEncrytor()
    {
        this.innerEncryptor = new NullCipherEncryptor();
    }

    public FractionatedMorseEncrytor(IEncryptor innerEncryptor)
    {
        this.innerEncryptor = innerEncryptor;
    }

    @Override
    public void encryptFile(FileSystemPart fsp) throws IOException
    {
        ByteStream bs = this.run(fsp.getByteStream());
        this.writeByteStream(fsp, bs);
    }

    @Override
    public ByteStream run(ByteStream bs) throws IOException
    {
        bs = innerEncryptor.run(bs);
        return this.runEncryption(bs);
    }
    
    public ByteStream runEncryption(ByteStream bs) throws IOException
    {
        return MorseCode.toMorse(bs);
    }
}