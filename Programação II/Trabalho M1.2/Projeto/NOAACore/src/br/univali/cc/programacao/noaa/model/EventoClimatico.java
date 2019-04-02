package br.univali.cc.programacao.noaa.model;

import java.time.LocalDateTime;

public class EventoClimatico
{
    private int id;
    private TipoEvento tipo;
    private double latitude;
    private double longitude;
    private String descricao;
    private LocalDateTime dataInicio;
    private LocalDateTime dataFim;
    private SituacaoEvento situacao;
    private CategoriaEvento categoria;

    public EventoClimatico(int id, TipoEvento tipo, double latitude, double longitude, String descricao, LocalDateTime dataInicio, LocalDateTime dataFim, SituacaoEvento situacao, CategoriaEvento categoria)
    {
        this.id = id;
        this.tipo = tipo;
        this.latitude = latitude;
        this.longitude = longitude;
        this.descricao = descricao;
        this.dataInicio = dataInicio;
        this.dataFim = dataFim;
        this.situacao = situacao;
        this.categoria = categoria;
    }
    
    public EventoClimatico(TipoEvento tipo, double latitude, double longitude, String descricao, LocalDateTime dataInicio, LocalDateTime dataFim, SituacaoEvento situacao, CategoriaEvento categoria)
    {
        this.id = id;
        this.tipo = tipo;
        this.latitude = latitude;
        this.longitude = longitude;
        this.descricao = descricao;
        this.dataInicio = dataInicio;
        this.dataFim = dataFim;
        this.situacao = situacao;
        this.categoria = categoria;
    }

    public int getId()
    {
        return id;
    }
    
    public TipoEvento getTipo()
    {
        return tipo;
    }
    
    public double getLatitude()
    {
        return latitude;
    }
    
    public double getLongitude()
    {
        return longitude;
    }
    
    public String getDescricao()
    {
        return descricao;
    }
    
    public LocalDateTime getDataInicio()
    {
        return dataInicio;
    }
    
    public LocalDateTime getDataFim()
    {
        return dataFim;
    }
    
    public SituacaoEvento getSituacao()
    {
        return situacao;
    }
    
    public CategoriaEvento getCategoria()
    {
        return categoria;
    }
    
    public void setId(int id)
    {
        this.id = id;
    }

    public void setTipo(TipoEvento tipo)
    {
        this.tipo = tipo;
    }

    public void setLatitude(double latitude)
    {
        this.latitude = latitude;
    }

    public void setLongitude(double longitude)
    {
        this.longitude = longitude;
    }

    public void setDescricao(String descricao)
    {
        this.descricao = descricao;
    }

    public void setDataInicio(LocalDateTime dataInicio)
    {
        this.dataInicio = dataInicio;
    }

    public void setDataFim(LocalDateTime dataFim)
    {
        this.dataFim = dataFim;
    }

    public void setSituacao(SituacaoEvento situacao)
    {
        this.situacao = situacao;
    }

    public void setCategoria(CategoriaEvento categoria)
    {
        this.categoria = categoria;
    }
    
    @Override
    public String toString()
    {
        return String.format("EventoClimatico[%d,%s,%f,%f,%s,%s,%s,%s,%s]",
                this.getId(), this.getTipo(), this.getLatitude(), this.getLongitude(), this.getDescricao(),
                this.getDataInicio(), this.getDataFim(), this.getSituacao(), this.getCategoria());
    }
}
