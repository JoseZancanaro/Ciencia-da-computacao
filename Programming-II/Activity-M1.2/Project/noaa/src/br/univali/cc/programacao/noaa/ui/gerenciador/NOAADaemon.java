package br.univali.cc.programacao.noaa.ui.gerenciador;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

/* Gerenciador de serviços de background do NOAA */
public class NOAADaemon
{
    private static NOAADaemon instancia;
    private Map<String, NOAAServico> servicos;
    
    private NOAADaemon()
    {
        this.servicos = new HashMap<>();
    }
    
    public static NOAADaemon getInstancia()
    {
        if (instancia == null)
            instancia = new NOAADaemon();
        return instancia;
    }

    public NOAAServico get(String nomeDaemon)
    {
        return this.servicos.get(nomeDaemon);
    }
    
    public void add(String nomeDaemon, NOAAServico servico)
    {
        this.servicos.put(nomeDaemon, servico);
    }
    
    public Set<Map.Entry<String, NOAAServico>> getServicos()
    {
        return this.servicos.entrySet();
    }
    
    public void fecharTudo()
    {
        this.servicos.entrySet().forEach(s -> s.getValue().desabilitar());
    }
    
}
