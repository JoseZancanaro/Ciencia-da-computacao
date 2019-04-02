package fuzzy.model.servidor;

import fuzzy.model.servidor.listener.ServidorListener;
import fuzzy.model.servidor.listener.ServidorListenerAdapter;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import javax.net.ServerSocketFactory;

public class ServidorFuzzy implements Runnable
{
    private final int porta;
    
    private ServidorListener listener = new ServidorListenerAdapter();
    
    public ServidorFuzzy(int porta)
    {
        this.porta = porta;
    }
    
    public void listen() throws IOException
    {
        ServerSocket server = ServerSocketFactory.getDefault().createServerSocket(porta);
        
        while (true) {
            Socket s = server.accept();
            listener.inicio(s);
            try {
                new Thread(new GerenciadorConexao(s)).start();
            } catch (IOException ex) {
                listener.excecao(ex);
                listener.fim(s);
            }
        }
    }
    
    @Override
    public void run()
    {
        try {
            this.listen();
        } catch (IOException ex) {}
    }
    
    public void setListener(ServidorListener listener)
    {
        this.listener = listener;
    }
    
    public static void main(String[] args) throws Exception
    {
        ServidorFuzzy sf = new ServidorFuzzy(2048);
        sf.setListener(new ConsoleServidorListener());
        sf.listen();
    }
}
