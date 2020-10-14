package experimentobackup.experimento;

import experimentobackup.dominio.AbstractCopiador;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public class TestadorCopiador
{
    private final String destino;
    private final List<Amostra> amostras;
    private final List<RegistroExecucao> execucoes;
    private final int copiasPorArquivo;
    private final int descartes;
    
    public TestadorCopiador (String destino, List<Amostra> amostras, int copiasPorArquivo, int descartes)
    {
        this.destino = destino;
        this.amostras = amostras;
        this.execucoes = new LinkedList<>();
        this.copiasPorArquivo = copiasPorArquivo;
        this.descartes = descartes;
    }
    
    public void testar(String identificador, AbstractCopiador copiador) throws IOException
    {
        RegistroExecucao reg = new RegistroExecucao(identificador);

        for (Amostra amostra : this.amostras) {
            long somaTempo = 0;
            for (int j = 0; j < this.copiasPorArquivo; j++) {
                long duracao = copiador.copiar(amostra.getArquivo(),
                                String.format("%s/saida%dmb.txt", destino, amostra.getTamanho()));
                if (j >= descartes)
                    somaTempo += duracao;
            }
            reg.registrar(amostra.getTamanho(), somaTempo / (copiasPorArquivo - descartes));
            System.out.println(String.format("Finalizou %d mbs: %d ms", amostra.getTamanho(), somaTempo / (copiasPorArquivo - descartes)));
        }
        
        this.execucoes.add(reg);
    }
    
    private void exportarRegistro(RegistroExecucao reg) throws IOException
    {
        File arquivo = new File(String.format("%s.csv", reg.getNome()));
        BufferedWriter bw = new BufferedWriter(new FileWriter(arquivo));
        bw.write(reg.toString());
        bw.close();
    }
    
    public void exportarRegistro(String nome) throws IOException
    {
        for (RegistroExecucao reg : this.execucoes) {
            if (reg.getNome().equals(nome)) {
                this.exportarRegistro(reg);
                break;
            }
        }
    }
    
    public void exportarTodos() throws IOException
    {
        for (RegistroExecucao reg : this.execucoes)
            this.exportarRegistro(reg);
    }
}
