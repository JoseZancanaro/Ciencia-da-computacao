package br.univali.cc.programacao.noaa.ui.gerenciador;

import java.util.Timer;
import java.util.TimerTask;
import javafx.application.Platform;

public class NOAAServico
{
    private Timer tarefa;
    private Runnable atividade;
    private Runnable onHabilitar;
    private Runnable onDesabilitar;
    private long atraso;
    private long periodo;
    private boolean habilitado;
    
    public NOAAServico(Runnable atividade, long atraso, long periodo, boolean habilitar, Runnable onHabilitar, Runnable onDesabilitar)
    {
        this.atividade = atividade;
        this.setAtraso(atraso);
        this.setPeriodo(periodo);
        this.setOnHabilitar(onHabilitar);
        this.setDesabilitar(onDesabilitar);
        if (habilitar)
            this.habilitar();
    }
    
    public NOAAServico(Runnable atividade, long atraso, long periodo, boolean habilitar)
    {
        this.atividade = atividade;
        this.setAtraso(atraso);
        this.setPeriodo(periodo);
        if (habilitar)
            this.habilitar();
    }
    
    public long getAtraso()
    {
        return atraso;
    }
    
    public long getPeriodo()
    {
        return periodo;
    }
    
    public Runnable getOnHabilitar()
    {
        return onHabilitar;
    }

    public Runnable getOnDesabilitar()
    {
        return onDesabilitar;
    }

    public void setAtraso(long atraso)
    {
        if (atraso >= 0)
            this.atraso = atraso;
    }

    public void setPeriodo(long periodo)
    {
        if (periodo >= 0)
            this.periodo = periodo;
    }
    
    public void setOnHabilitar(Runnable onHabilitar)
    {
        this.onHabilitar = onHabilitar;
    }
    
    public void setDesabilitar(Runnable onDesabilitar)
    {
        this.onDesabilitar = onDesabilitar;
    }

    public boolean isHabilitado()
    {
        return habilitado;
    }
    
    public void habilitar()
    {
        if (!this.isHabilitado()) {
            tarefa = new Timer();
            this.habilitado = true;
            tarefa.scheduleAtFixedRate(new TimerTask(){
                @Override
                public void run()
                {
                    Platform.runLater(atividade);
                }
            }, this.getAtraso(), this.getPeriodo());
            if (getOnHabilitar() != null)
                Platform.runLater(getOnHabilitar());
        }
    }

    public void desabilitar()
    {
        if (this.isHabilitado()) {
            this.habilitado = false;
            this.tarefa.cancel();
            if (getOnDesabilitar() != null)
                Platform.runLater(getOnDesabilitar());
        }
    }
}
