package br.univali.cc.programacao.noaa.model;

public enum TipoEvento
{
    Trovoada("Trovoada"), Raio("Raio"), InversaoTermica("Inversão Térmica"), Furacao("Furacão"),
    Ciclone("Ciclone"), Tornado("Tornado"), Ventania("Ventania"), Nevasca("Nevasca");
    
    private String descricao = null;
    
    private TipoEvento(String nome)
    {
        this.descricao = nome;
    }
    
    public String getDescricao()
    {
        return this.descricao;
    }
}