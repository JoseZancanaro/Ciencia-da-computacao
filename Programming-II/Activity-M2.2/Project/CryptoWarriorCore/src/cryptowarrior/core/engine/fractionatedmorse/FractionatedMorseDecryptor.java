package cryptowarrior.core.engine.fractionatedmorse;

// CryptoWarrior
import cryptowarrior.core.engine.IDecryptor;
import cryptowarrior.core.engine.nullcipher.NullCipherDecryptor;
import cryptowarrior.core.filesystem.FileSystemPart;
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.IOException;

public class FractionatedMorseDecryptor extends IDecryptor
{
    IDecryptor innerDecryptor;

    public FractionatedMorseDecryptor()
    {
        this.innerDecryptor = new NullCipherDecryptor();
    }

    public FractionatedMorseDecryptor(IDecryptor innerDecryptor)
    {
        this.innerDecryptor = innerDecryptor;
    }

    @Override
    public void decryptFile(FileSystemPart fsp) throws IOException
    {
        ByteStream bs = this.run(fsp.getByteStream());
        this.writeByteStream(fsp, bs);
    }

    @Override
    public ByteStream run(ByteStream bs) throws IOException
    {
        bs = this.runDecryption(bs);
        return innerDecryptor.run(bs);
    }
    
    public ByteStream runDecryption(ByteStream bs) throws IOException
    {
        return MorseCode.fromMorse(bs);
    }
}