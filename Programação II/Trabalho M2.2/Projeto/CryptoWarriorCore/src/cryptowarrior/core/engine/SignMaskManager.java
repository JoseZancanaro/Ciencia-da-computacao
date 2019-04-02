package cryptowarrior.core.engine;

public class SignMaskManager
{
    
    public enum Engine {
        NULL(0b0, "Null Cipher"), ROT13(0b1, "Rotation Algorithm 13"),
        CAESAR(0b10, "Caesar Cipher"), BASE64(0b100, "Base 64 Cipher"),
        FRACTIONATED_MORSE(0b1000, "Fractioned Morse Cipher");
        
        private final int value;
        private final String name;
        
        Engine(int value, String name)
        {
            this.value = value;
            this.name = name;
        }
        
        public int getValue()
        {
            return this.value;
        }
        
        public String getName()
        {
            return this.name;
        }
        
        public static Engine fromName(String name)
        {
            Engine[] engines = Engine.values();
            for (Engine e : engines) {
                if (e.getName().equals(name))
                    return e;
            }
            throw new IllegalArgumentException(name);
        }
        
    }   
    
}
