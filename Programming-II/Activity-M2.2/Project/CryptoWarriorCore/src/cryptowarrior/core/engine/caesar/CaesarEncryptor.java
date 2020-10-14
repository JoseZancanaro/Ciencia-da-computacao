package cryptowarrior.core.engine.caesar;

// CryptoWarrior
import cryptowarrior.core.engine.IEncryptor;
import cryptowarrior.core.engine.nullcipher.NullCipherEncryptor;
import cryptowarrior.core.engine.rot.OrdinaryRotationAlgorithm;
import cryptowarrior.core.filesystem.FileSystemPart;
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.IOException;

public class CaesarEncryptor extends IEncryptor
{
    IEncryptor innerEncryptor;
    OrdinaryRotationAlgorithm rot;

    public CaesarEncryptor()
    {
        this.rot = new OrdinaryRotationAlgorithm(7);
        this.innerEncryptor = new NullCipherEncryptor();
    }

    public CaesarEncryptor(IEncryptor innerEncryptor)
    {
        this.rot = new OrdinaryRotationAlgorithm(7);
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
    
    private ByteStream runEncryption(ByteStream bs) throws IOException
    {
        return rot.encrypt(bs);
    }
}