package experimentobackup.experimento;

import java.util.LinkedList;
import java.util.List;

public class RegistroExecucao
{
    private String nome;
    private final List<Registro> registros;

    public RegistroExecucao(String nome)
    {
        this.nome = nome;
        this.registros = new LinkedList<>();
    }
    
    public void registrar(int tamanho, long tempo)
    {
        this.registros.add(new Registro(tamanho, tempo));
    }
    
    public String getNome()
    {
        return this.nome;
    }
    
    public String toString()
    {
        StringBuilder listaRegistros = new StringBuilder("Tamanho,Tempo\r\n");
        for (Registro reg : this.registros) {
            listaRegistros.append(reg.toString()).append("\r\n");
        }
        return listaRegistros.toString();
    }
}