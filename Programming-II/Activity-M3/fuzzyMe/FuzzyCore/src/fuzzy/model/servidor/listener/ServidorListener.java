package fuzzy.model.servidor.listener;

import java.net.Socket;

public interface ServidorListener
{
    void inicio(Socket socket);
    void fim(Socket socket);
    void excecao(Exception exception);
}
