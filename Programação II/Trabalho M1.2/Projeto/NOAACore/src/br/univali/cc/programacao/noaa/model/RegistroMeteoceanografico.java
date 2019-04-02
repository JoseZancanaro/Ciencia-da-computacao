package br.univali.cc.programacao.noaa.model;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.time.LocalDateTime;

public class RegistroMeteoceanografico
{
    private int id;
    private int idOndografo;
    private double temperatura;
    private double umidade;
    private double pressao;
    private double altura;
    private double corrente;
    private double direcaoCorrente;
    private double vento;
    private double direcaoVento;
    private double bateria;
    private LocalDateTime data;

    public RegistroMeteoceanografico(int idOndografo, double temperatura, double umidade, double pressao, double altura, double corrente,
                double direcaoCorrente, double vento, double direcaoVento, double bateria, LocalDateTime data)
    {
        this.idOndografo = idOndografo;
        this.temperatura = this.aproximar(temperatura);
        this.umidade = this.aproximar(umidade);
        this.pressao = this.aproximar(pressao);
        this.altura = this.aproximar(altura);
        this.corrente = this.aproximar(corrente);
        this.direcaoCorrente = this.aproximar(direcaoCorrente);
        this.vento = this.aproximar(vento);
        this.direcaoVento = this.aproximar(direcaoVento);
        this.bateria = bateria;
        this.data = data;
    }
    
    public RegistroMeteoceanografico(int id, int idOndografo, double temperatura, double umidade, double pressao, double altura, double corrente,
                double direcaoCorrente, double vento, double direcaoVento, double bateria, LocalDateTime data)
    {
        this.id = id;
        this.idOndografo = idOndografo;
        this.temperatura = this.aproximar(temperatura);
        this.umidade = this.aproximar(umidade);
        this.pressao = this.aproximar(pressao);
        this.altura = this.aproximar(altura);
        this.corrente = this.aproximar(corrente);
        this.direcaoCorrente = this.aproximar(direcaoCorrente);
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
    
    public int getIdOndografo()
    {
        return idOndografo;
    }

    public double getTemperatura()
    {
        return temperatura;
    }

    public double getUmidade()
    {
        return umidade;
    }

    public double getPressao()
    {
        return pressao;
    }

    public double getAltura()
    {
        return altura;
    }

    public double getCorrente()
    {
        return corrente;
    }

    public double getDirecaoCorrente()
    {
        return direcaoCorrente;
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
        return String.format("RegistroMeteoceanografico[%d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %s]", 
                this.getId(), this.getIdOndografo(), this.getTemperatura(), this.getUmidade(), this.getPressao(), this.getAltura(),
                this.getCorrente(), this.getDirecaoCorrente(), this.getVento(), this.getDirecaoVento(), this.getBateria(),
                this.getData().toString());
    }
}