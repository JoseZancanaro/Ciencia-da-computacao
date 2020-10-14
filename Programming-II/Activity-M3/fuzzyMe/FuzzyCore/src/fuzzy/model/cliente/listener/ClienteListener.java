package fuzzy.model.cliente.listener;

public interface ClienteListener
{
    void usuarioAutenticado();
    void usuarioInserido();
    void postagemInserida();
    void usuarioRemovido();
    void postagemRemovida();
}
