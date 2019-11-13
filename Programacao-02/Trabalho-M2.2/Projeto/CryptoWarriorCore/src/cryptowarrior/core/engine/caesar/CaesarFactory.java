package cryptowarrior.core.engine.caesar;

// CryptoWarrior
import cryptowarrior.core.engine.CryptoEngineFactory;
import cryptowarrior.core.engine.IDecryptor;
import cryptowarrior.core.engine.IEncryptor;
import cryptowarrior.core.engine.nullcipher.NullCipherFactory;

public class CaesarFactory implements CryptoEngineFactory
{
    CryptoEngineFactory innerFactory;

    public CaesarFactory()
    {
        this.innerFactory = new NullCipherFactory();
    }

    public CaesarFactory(CryptoEngineFactory innerFactory)
    {
        this.innerFactory = innerFactory;
    }
    
    @Override
    public IEncryptor createEncryptor()
    {
        IEncryptor innerEncryptor = innerFactory.createEncryptor();
        return new CaesarEncryptor(innerEncryptor);
    }

    @Override
    public IDecryptor createDecryptor()
    {
        IDecryptor innerDecryptor = innerFactory.createDecryptor();
        return new CaesarDecryptor(innerDecryptor);
    }
    
    @Override
    public String getName()
    {
        return this.innerFactory.getName() + "-> Caesar ";
    }
}
