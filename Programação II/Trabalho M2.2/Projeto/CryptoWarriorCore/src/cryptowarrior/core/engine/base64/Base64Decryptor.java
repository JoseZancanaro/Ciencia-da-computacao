package cryptowarrior.core.engine.base64;

// CryptoWarrior
import cryptowarrior.core.engine.IDecryptor;
import cryptowarrior.core.engine.nullcipher.NullCipherDecryptor;
import cryptowarrior.core.filesystem.FileSystemPart;
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.io.IOException;
import java.util.Base64;

public class Base64Decryptor extends IDecryptor
{
    IDecryptor innerDecryptor;

    public Base64Decryptor()
    {
        this.innerDecryptor = new NullCipherDecryptor();
    }

    public Base64Decryptor(IDecryptor innerDecryptor)
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
        byte[] output = Base64.getDecoder().decode(bs.toByteArray());
        return new ByteStream(output);
    }
}
