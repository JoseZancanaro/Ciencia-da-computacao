package br.univali.cc.programacao.noaa.model;

import java.time.LocalDateTime;

public final class Ondografo
{
    private int id;
    private String nome;
    private double latitude;
    private double longitude;
    private double bateria;
    private LocalDateTime dataLancamento;
    
    public Ondografo(String nome, double latitude, double longitude, LocalDateTime dataLancamento)
    {
        this.setNome(nome);
        this.setLatitude(latitude);
        this.setLongitude(longitude);
        this.setDataLancamento(dataLancamento);
        this.setBateria(1.0);
    }
    
    public Ondografo(int id, String nome, double latitude, double longitude, double bateria, LocalDateTime dataLancamento)
    {
        this.id = id;
        this.setNome(nome);
        this.setLatitude(latitude);
        this.setLongitude(longitude);
        this.setBateria(bateria);
        this.setDataLancamento(dataLancamento);
    }
    
    public int getId()
    {
        return this.id;
    }
    
    public String getNome()
    {
        return this.nome;
    }

    public double getLatitude()
    {
        return this.latitude;
    }
    
    public double getLongitude()
    {
        return this.longitude;
    }
    
    public LocalDateTime getDataLancamento()
    {
        return this.dataLancamento;
    }
    
    public double getBateria()
    {
        return bateria;
    }
    
    public void setNome(String nome)
    {
        this.nome = nome;
    }
    
    public void setLatitude(double latitude)
    {
        this.latitude = latitude;
    }
    
    public void setLongitude(double longitude)
    {
        this.longitude = longitude;
    }

    public void setBateria(double bateria)
    {
        this.bateria = bateria;
    }
    
    public void setDataLancamento(LocalDateTime dataLancamento)
    {
        this.dataLancamento = dataLancamento;
    }
    
    @Override
    public String toString()
    {
        return String.format("Ondografo[%d,%s,%f,%f,%f,%s]", this.getId(), this.getNome(), this.getLatitude(),
                                this.getLongitude(), this.getBateria(), this.getDataLancamento().toString());
    }
}
