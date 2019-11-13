package cryptowarrior.core.engine.rot13;

// CryptoWarrior
import cryptowarrior.core.engine.IDecryptor;
import cryptowarrior.core.engine.nullcipher.NullCipherDecryptor;
import cryptowarrior.core.engine.rot.OrdinaryRotationAlgorithm;
import cryptowarrior.core.filesystem.FileSystemPart;
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.IOException;

public class Rot13Decryptor extends IDecryptor
{
    IDecryptor innerDecryptor;
    OrdinaryRotationAlgorithm rot;

    public Rot13Decryptor()
    {
        this.rot = new OrdinaryRotationAlgorithm(13);
        this.innerDecryptor = new NullCipherDecryptor();
    }

    public Rot13Decryptor(IDecryptor innerDecryptor)
    {
        this.rot = new OrdinaryRotationAlgorithm(13);
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
    
    private ByteStream runDecryption (ByteStream bs) throws IOException
    {
        return rot.decrypt(bs);
    }
}
