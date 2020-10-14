package cryptowarrior.core.engine.base64;

// CryptoWarrior
import cryptowarrior.core.engine.IEncryptor;
import cryptowarrior.core.engine.nullcipher.NullCipherEncryptor;
import cryptowarrior.core.filesystem.FileSystemPart;
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.IOException;
import java.util.Base64;

public class Base64Encrytor extends IEncryptor
{
    IEncryptor innerEncryptor;

    public Base64Encrytor()
    {
        this.innerEncryptor = new NullCipherEncryptor();
    }

    public Base64Encrytor(IEncryptor innerEncryptor)
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
    
    private ByteStream runEncryption(ByteStream bs) throws IOException
    {
        byte[] output = Base64.getEncoder().encode(bs.toByteArray());
        return new ByteStream(output);
    }
}
