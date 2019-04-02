package cryptowarrior.core.engine.nullcipher;

// CryptoWarrior
import cryptowarrior.core.engine.CryptoEngineFactory;
import cryptowarrior.core.engine.IDecryptor;
import cryptowarrior.core.engine.IEncryptor;

public class NullCipherFactory implements CryptoEngineFactory
{
    @Override
    public IEncryptor createEncryptor()
    {
        return new NullCipherEncryptor();
    }

    @Override
    public IDecryptor createDecryptor()
    {
        return new NullCipherDecryptor();
    }
    
    public String getName()
    {
        return "Nullable ";
    }
}
