package cryptowarrior.core.engine;

// CryptoWarrior
import cryptowarrior.core.engine.base64.Base64Factory;
import cryptowarrior.core.engine.caesar.CaesarFactory;
import cryptowarrior.core.engine.fractionatedmorse.FractionatedMorseFactory;
import cryptowarrior.core.engine.nullcipher.NullCipherFactory;
import cryptowarrior.core.engine.rot13.Rot13Factory;

public class CryptoEngineFactoryCreator
{
    public static CryptoEngineFactory create(SignMaskManager.Engine engine, CryptoEngineFactory innerFactory)
    {
        switch (engine)
        {
            case ROT13:
                return new Rot13Factory(innerFactory);
            case CAESAR:
                return new CaesarFactory(innerFactory);
            case BASE64:
                return new Base64Factory(innerFactory);
            case FRACTIONATED_MORSE:
                return new FractionatedMorseFactory(innerFactory);
            default:
                return new NullCipherFactory();
        }
    }
    
    public static CryptoEngineFactory create(SignMaskManager.Engine engine)
    {
        return create(engine, new NullCipherFactory());
    }
    
    public static CryptoEngineFactory create(SignStack signStack)
    {
        SignMaskManager.Engine engine = signStack.pop();
        if (engine.equals(SignMaskManager.Engine.NULL) || signStack.getSize() == 0) {
            return create(engine);
        }
        else {
            return create(engine, create(signStack));
        }
    }
}
