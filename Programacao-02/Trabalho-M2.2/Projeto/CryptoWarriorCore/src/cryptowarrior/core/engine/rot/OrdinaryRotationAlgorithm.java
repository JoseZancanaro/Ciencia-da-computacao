package cryptowarrior.core.engine.rot;

// CryptoWarrior
import cryptowarrior.core.stream.ByteStream;

// JavaUtils
import java.util.List;

public class OrdinaryRotationAlgorithm
{
    private final int offset;
    private final int backwardOffset;
    private static final String lowerAlphabet = "abcdefghijklmnopqrstuvwxyz";
    private static final String upperAlphabet = lowerAlphabet.toUpperCase();

    public OrdinaryRotationAlgorithm(int offset)
    {
        this.offset = offset;
        this.backwardOffset = 26 - offset;
    }
    
    private ByteStream run(ByteStream bs, int offset)
    {
        List<Integer> bsList = bs.getList();
        
        for (int i = 0; i < bsList.size(); i++) {
            char b = (char) bsList.get(i).intValue();
            if (lowerAlphabet.indexOf(b) >= 0)
                bsList.set(i, (int) lowerAlphabet.charAt((lowerAlphabet.indexOf(b) + offset) % 26));
            else {
                if (upperAlphabet.indexOf(b) >= 0)
                    bsList.set(i, (int) upperAlphabet.charAt((upperAlphabet.indexOf(b) + offset) % 26));
                else
                    bsList.set(i, (int) b);
            }
        }
        
        return bs;
    }
    
    public ByteStream encrypt(ByteStream bs)
    {
        return this.run(bs, this.offset);
    }
    
    public ByteStream decrypt(ByteStream bs)
    {
        return this.run(bs, backwardOffset);
    }
}
