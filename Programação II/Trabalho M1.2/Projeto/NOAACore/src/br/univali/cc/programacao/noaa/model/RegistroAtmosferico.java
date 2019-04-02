package br.univali.cc.programacao.noaa.model;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.time.LocalDateTime;

public final class RegistroAtmosferico
{
    private int id;
    private int idSatelite;
    private double temperatura;
    private double pressao;
    private double densidade;
    private double vento;
    private double direcaoVento;
    private double bateria;
    private LocalDateTime data;
    
    public RegistroAtmosferico(int idSatelite, double temperatura, double pressao, double densidade,
                               double vento, double direcaoVento, double bateria, LocalDateTime data)
    {
        this.idSatelite = idSatelite;
        this.temperatura = this.aproximar(temperatura);
        this.pressao = this.aproximar(pressao);
        this.densidade = this.aproximar(densidade);
        this.vento = this.aproximar(vento);
        this.direcaoVento = this.aproximar(direcaoVento);
        this.bateria = bateria;
        this.data = data; 
    }
    
    public RegistroAtmosferico(int id, int idSatelite, double temperatura, double pressao, double densidade,
                               double vento, double direcaoVento, double bateria, LocalDateTime data)
    {
        this.id = id;
        this.idSatelite = idSatelite;
        this.temperatura = this.aproximar(temperatura);
        this.pressao = this.aproximar(pressao);
        this.densidade = this.aproximar(densidade);
        this.vento = this.aproximar(vento);
        this.direcaoVento = this.aproximar(direcaoVento);
        this.bateria = bateria;
        this.data = data;  
    }
    
    private double aproximar(double valor, int casas)
    {
        return new BigDecimal(valor).setScale(casas, RoundingMode.HALF_UP).doubleValue();
    }
    
    private double aproximar(double valor)
    {
        return this.aproximar(valor, 3);
    }
    
    public int getId()
    {
        return id;
    }
    
    public int getIdSatelite()
    {
        return idSatelite;
    }

    public double getTemperatura()
    {
        return temperatura;
    }

    public double getPressao()
    {
        return pressao;
    }

    public double getDensidade()
    {
        return densidade;
    }

    public double getVento()
    {
        return vento;
    }

    public double getDirecaoVento()
    {
        return direcaoVento;
    }
    
    public double getBateria()
    {
        return bateria;
    }
    
    public LocalDateTime getData()
    {
        return data;
    }
    
    @Override
    public String toString()
    {
        return String.format("RegistroAtmosferico[%d, %d, %f, %f, %f, %f, %f, %f, %s]", 
                this.getId(), this.getIdSatelite(), this.getTemperatura(), this.getPressao(),this.getDensidade(),
                this.getVento(), this.getDirecaoVento(), this.getBateria(),this.getData().toString());
    }
}
