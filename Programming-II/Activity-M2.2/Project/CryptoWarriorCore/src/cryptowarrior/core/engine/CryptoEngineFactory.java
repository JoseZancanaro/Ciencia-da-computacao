package cryptowarrior.core.engine;

public interface CryptoEngineFactory
{
    String getName();
    IEncryptor createEncryptor();
    IDecryptor createDecryptor();
}
