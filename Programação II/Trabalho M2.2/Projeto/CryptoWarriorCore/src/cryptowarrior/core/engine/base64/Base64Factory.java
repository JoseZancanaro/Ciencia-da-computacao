package cryptowarrior.core.engine.base64;

// CryptoWarrior
import cryptowarrior.core.engine.CryptoEngineFactory;
import cryptowarrior.core.engine.IDecryptor;
import cryptowarrior.core.engine.IEncryptor;
import cryptowarrior.core.engine.nullcipher.NullCipherFactory;

public class Base64Factory implements CryptoEngineFactory
{
    CryptoEngineFactory innerFactory;

    public Base64Factory()
    {
        this.innerFactory = new NullCipherFactory();
    }

    public Base64Factory(CryptoEngineFactory innerFactory)
    {
        this.innerFactory = innerFactory;
    }
    
    @Override
    public IEncryptor createEncryptor()
    {
        IEncryptor innerEncryptor = innerFactory.createEncryptor();
        return new Base64Encrytor(innerEncryptor);
    }

    @Override
    public IDecryptor createDecryptor()
    {
        IDecryptor innerDecryptor = innerFactory.createDecryptor();
        return new Base64Decryptor(innerDecryptor);
    }
    
    public String getName()
    {
        return this.innerFactory.getName() + "-> Base 64 ";
    }
}
