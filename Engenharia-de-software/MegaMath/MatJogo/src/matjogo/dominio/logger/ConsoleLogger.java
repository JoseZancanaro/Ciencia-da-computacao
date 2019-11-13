package matjogo.dominio.logger;

public class ConsoleLogger implements Logger
{
    @Override
    public void log(Log log)
    {
        System.out.println(String.format("%s: %s", log.getTitle(), log.getDescription()));
    }
}
