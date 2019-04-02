package cryptowarriorcore;

// CryptoWarrior
import cryptowarrior.core.engine.CryptoEngineFactory;
import cryptowarrior.core.engine.CryptoEngineFactoryCreator;
import cryptowarrior.core.engine.IDecryptor;
import cryptowarrior.core.engine.IEncryptor;
import cryptowarrior.core.engine.SignStack;
import cryptowarrior.core.filesystem.FileSystemPart;
import cryptowarrior.core.filesystem.FileSystemPartFactory;

// JavaUtils
import cryptowarrior.core.engine.SignMaskManager.Engine;
import java.util.Scanner;

public class CryptoWarriorCore
{
    
    public static void main(String[] args) throws Exception
    {
        // create FSP
        FileSystemPart fsp = FileSystemPartFactory.create("/home/efraim/Documents/CC/cryptowarrior/Area51/Pessoas/José");
        
        // make SignStack
        SignStack signStack = new SignStack();
        signStack.pushAll(Engine.ROT13, Engine.BASE64, Engine.FRACTIONATED_MORSE, Engine.ROT13, Engine.CAESAR, Engine.BASE64);
        
        // create Factory
        CryptoEngineFactory factory = CryptoEngineFactoryCreator.create(signStack);
        System.out.println(factory.getName());
        
        // encrypt
        IEncryptor enc = factory.createEncryptor();
        enc.encrypt(fsp);
        
        // await input
        Scanner scanner = new Scanner(System.in);
        scanner.nextLine();
        
        // decrypt
        IDecryptor dec = factory.createDecryptor();
        dec.decrypt(fsp);
    }
}
