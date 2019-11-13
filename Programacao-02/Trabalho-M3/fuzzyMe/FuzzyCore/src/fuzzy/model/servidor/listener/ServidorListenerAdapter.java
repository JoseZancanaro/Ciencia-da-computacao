package fuzzy.model.servidor.listener;

import java.net.Socket;

public class ServidorListenerAdapter implements ServidorListener
{
    @Override
    public void inicio(Socket socket) {}

    @Override
    public void fim(Socket socket) {}

    @Override
    public void excecao(Exception exception) {}
}
