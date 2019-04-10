package matjogo.dominio.logger;

public class LoggerPadrao
{
    private static Logger padrao = new LoggerNulo();
    
    public static Logger get()
    {
        return padrao;
    }
    
    public static Logger set(Logger logger)
    {
        return (LoggerPadrao.padrao = logger);
    }
}
