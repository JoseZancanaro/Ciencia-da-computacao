package cryptowarrior.core.engine.fractionatedmorse;

import cryptowarrior.core.stream.ByteStream;
import java.util.List;

public class MorseCode
{
    private static String[] keys = {"a",  "b",  "c",  "d",  "e",  "f",  "g",  "h",  "i",  "j",  "k",  "l",  "m",
                                    "n",  "o",  "p",  "q",  "r",  "s",  "t",  "u",  "v",  "w",  "x",  "y",  "z", 
                                    ".",  ",",  ":",  "\"",  "'",  "!",  "?",  "@",  "-",  ";",  "(",  ")",  "=",
                                    "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "0"};
    
    private static String[] contents = {".-",  "-...",  "-.-.",  "-..",  ".",  "..-.",  "--.",  "....",  "..",  ".---",
                                        "-.-",  ".-..",  "--",  "-.",  "---",  ".--.",  "--.-",  ".-.",  "...",  "-", 
                                        "..-",  "...-",  ".--",  "-..-",  "-.--",  "--..",  ".-.-.-",  "--..--",  "---...",
                                        ".-..-.",  ".----.",  "-.-.--",  "..--..",  ".--.-.",  "-....-",  "-.-.-.", 
                                        "-.--.",  "-.--.-",  "-...-",  ".----",  "..---",  "...--",  "....-",  ".....", 
                                        "-....",  "--...",  "---..",  "----.",  "-----"};
    
    public static String getMorseEquivalent(String key)
    {
        int i;
        for (i = 0; i < keys.length; i++)
            if (keys[i].equals(key)) break;
        
        return (i == keys.length ? key : contents[i]);
    }
    
    public static String getAlphaNumericalEquivalent(String morse)
    {
        int i;
        for (i = 0; i < contents.length; i++)
            if (contents[i].equals(morse)) break;
        
        return (i == contents.length ? morse : keys[i]);
    }
    
    private static void copyStringToByteStream(ByteStream bs, String s)
    {
        for (int i = 0; i < s.length(); i++)
            bs.append(s.charAt(i));
    }
    
    public static ByteStream toMorse(ByteStream bs)
    {
        ByteStream output = new ByteStream();
        
        List<Integer> bsList = bs.getList();
        
        for (Integer i : bsList) {
            char c = (char) i.intValue();
            if (c != ' ') {
                String equivalent = getMorseEquivalent(String.valueOf(c));
                MorseCode.copyStringToByteStream(output, equivalent);
            }
            output.append('x');
        }
        
        return output;
    }
    
    public static ByteStream fromMorse(ByteStream bs)
    {
        ByteStream output = new ByteStream();
        
        List<Integer> bsList = bs.getList();
        
        int countX = 0;
        
        for (int i = 0; i < bsList.size(); i++) {
            StringBuilder sb = new StringBuilder();
            
            boolean appendedOnce = false;
            
            char c;
            while (i < bsList.size() && ((c = (char) bsList.get(i).intValue()) != 'x')) {
                sb.append(c);
                i++;
                appendedOnce = true;
            }
            
            if (appendedOnce) {
                String equivalent = MorseCode.getAlphaNumericalEquivalent(sb.toString());
                MorseCode.copyStringToByteStream(output, equivalent);
                countX = 0;
            }
            
            if (++countX == 2) {
                output.append(' ');
                countX = 0;
            }
        }
        
        return output;
    }
    
}
