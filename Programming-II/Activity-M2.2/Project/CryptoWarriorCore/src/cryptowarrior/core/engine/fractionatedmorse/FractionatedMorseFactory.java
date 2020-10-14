package cryptowarrior.core.engine.fractionatedmorse;

// CryptoWarrior
import cryptowarrior.core.engine.CryptoEngineFactory;
import cryptowarrior.core.engine.IDecryptor;
import cryptowarrior.core.engine.IEncryptor;
import cryptowarrior.core.engine.nullcipher.NullCipherFactory;

public class FractionatedMorseFactory implements CryptoEngineFactory
{
    CryptoEngineFactory innerFactory;

    public FractionatedMorseFactory()
    {
        this.innerFactory = new NullCipherFactory();
    }

    public FractionatedMorseFactory(CryptoEngineFactory innerFactory)
    {
        this.innerFactory = innerFactory;
    }
    
    @Override
    public IEncryptor createEncryptor()
    {
        IEncryptor innerEncryptor = innerFactory.createEncryptor();
        return new FractionatedMorseEncrytor(innerEncryptor);
    }

    @Override
    public IDecryptor createDecryptor()
    {
        IDecryptor innerDecryptor = innerFactory.createDecryptor();
        return new FractionatedMorseDecryptor(innerDecryptor);
    }
    
    @Override
    public String getName()
    {
        return this.innerFactory.getName() + "-> Fractioned Morse ";
    }
}
