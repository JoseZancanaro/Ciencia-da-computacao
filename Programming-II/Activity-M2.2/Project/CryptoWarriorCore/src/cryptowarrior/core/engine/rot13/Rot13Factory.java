package cryptowarrior.core.engine.rot13;

// CryptoWarrior
import cryptowarrior.core.engine.CryptoEngineFactory;
import cryptowarrior.core.engine.IDecryptor;
import cryptowarrior.core.engine.IEncryptor;
import cryptowarrior.core.engine.nullcipher.NullCipherFactory;

public class Rot13Factory implements CryptoEngineFactory
{
    CryptoEngineFactory innerFactory;

    public Rot13Factory()
    {
        this.innerFactory = new NullCipherFactory();
    }

    public Rot13Factory(CryptoEngineFactory innerFactory)
    {
        this.innerFactory = innerFactory;
    }
    
    @Override
    public IEncryptor createEncryptor()
    {
        IEncryptor innerEncryptor = innerFactory.createEncryptor();
        return new Rot13Encryptor(innerEncryptor);
    }

    @Override
    public IDecryptor createDecryptor()
    {
        IDecryptor innerDecryptor = innerFactory.createDecryptor();
        return new Rot13Decryptor(innerDecryptor);
    }
    
    @Override
    public String getName()
    {
        return this.innerFactory.getName() + "-> Rot13 ";
    }
}
