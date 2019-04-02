package br.univali.cc.programacao.noaa.model;

import java.time.LocalDateTime;

public final class Satelite
{
    private int id;
    private String nome;
    private double latitude;
    private double longitude;
    private double angulo;
    private double bateria;
    private LocalDateTime dataLancamento;
    
    public Satelite(String nome, double latitude, double longitude, double angulo, double bateria, LocalDateTime dataLancamento)
    {
        this.setNome(nome);
        this.setLatitude(latitude);
        this.setLongitude(longitude);
        this.setAngulo(angulo);
        this.setBateria(bateria);
        this.setDataLancamento(dataLancamento);
    }
    
    public Satelite(int id, String nome, double latitude, double longitude, double angulo, double bateria, LocalDateTime dataLancamento)
    {
        this.id = id;
        this.setNome(nome);
        this.setLatitude(latitude);
        this.setLongitude(longitude);
        this.setAngulo(angulo);
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
    
     public double getAngulo()
    {
        return angulo;
    }
      
    public LocalDateTime getDataLancamento()
    {
        return this.dataLancamento;
    }
    
     public double getBateria()
    {
        return this.bateria;
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
    
    public void setAngulo(double angulo)
    {
        this.angulo = angulo;
    }
    
    public void setDataLancamento(LocalDateTime dataLancamento)
    {
        this.dataLancamento = dataLancamento;
    }
    
    public void setBateria(double bateria)
    {
        this.bateria = bateria;
    }
    
    @Override
    public String toString()
    {
        return String.format("Satelite[%d,%s,%f,%f,%f,%f,%s]", this.getId(), this.getNome(), this.getLatitude(),
                                this.getLongitude(), this.getAngulo(), this.getBateria(),  this.getDataLancamento().toString());
    }
}
