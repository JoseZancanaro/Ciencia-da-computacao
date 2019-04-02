package fuzzy.model.servidor;

import fuzzy.model.servidor.listener.ServidorListener;
import java.net.Socket;

public class ConsoleServidorListener implements ServidorListener
{
    @Override
    public void inicio(Socket socket)
    {
        System.out.println("Conexão iniciada para " + socket.getInetAddress());
    }

    @Override
    public void fim(Socket socket)
    {
        System.out.println("Conexão finalizada para " + socket.getInetAddress());
    }

    @Override
    public void excecao(Exception exception)
    {
        System.out.println("Exceção lançada -> " + exception.getMessage());
    }
}
