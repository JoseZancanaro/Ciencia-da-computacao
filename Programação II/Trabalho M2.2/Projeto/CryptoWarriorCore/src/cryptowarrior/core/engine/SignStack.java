package cryptowarrior.core.engine;

// JavaUtils
import java.util.Stack;
import java.util.List;

public class SignStack
{
    Stack<SignMaskManager.Engine> stack;

    public SignStack()
    {
        this.stack = new Stack<>();
    }
    
    public SignMaskManager.Engine pop()
    {
        return this.stack.pop();
    }
    
    public void push(SignMaskManager.Engine engine)
    {
        this.stack.push(engine);
    }
    
    public void pushAll(SignMaskManager.Engine...engine)
    {
        for (SignMaskManager.Engine e : engine) {
            this.push(e);
        }
    }
    
    public int getSize()
    {
        return this.stack.size();
    }
    
    public static SignStack valueOf(List<String> list)
    {
        SignStack ss = new SignStack();
        
        list.forEach(s -> {
            ss.push(SignMaskManager.Engine.fromName(s));
        });
        
        return ss;
    }
}
