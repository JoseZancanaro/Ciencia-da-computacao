package br.univali.cc.programacao.noaa.simulador;

import br.univali.cc.programacao.noaa.persistencia.GerenciadorDeBanco;
import br.univali.cc.programacao.noaa.model.Ondografo;
import br.univali.cc.programacao.noaa.model.RegistroAtmosferico;
import br.univali.cc.programacao.noaa.model.RegistroMeteoceanografico;
import br.univali.cc.programacao.noaa.model.Satelite;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.List;
import java.util.Random;

public final class SimuladorAleatorio
{
    private GerenciadorDeBanco gdb;
    private Random rng;
    
    public SimuladorAleatorio() throws ClassNotFoundException
    {
        this.gdb = new GerenciadorDeBanco();
        this.rng = new Random();
    }
    
    private void simularOndografo(Ondografo ondografo) throws SQLException
    {
        gdb.inserirRegistroMeteoceanografico
        (
            new RegistroMeteoceanografico(ondografo.getId(), (rng.nextInt(22) + 8) + rng.nextDouble(), 0.8 + (rng.nextDouble() * 0.2),
                                         (rng.nextInt(178) + 858) + rng.nextDouble(), rng.nextDouble() * 3, rng.nextInt(370) + rng.nextDouble(),
                                         rng.nextInt(360) + rng.nextDouble(), rng.nextInt(16) + rng.nextDouble(), rng.nextInt(360) + rng.nextDouble(),
                                         ondografo.getBateria(), LocalDateTime.now())
        );
        ondografo.setBateria(ondografo.getBateria() - 0.025);
        if (ondografo.getBateria() < 0.5) {
            ondografo.setBateria(1.0);
        }
        System.out.println(gdb.atualizarOndografo(ondografo));
    }
    
    public void simularOndografos() throws SQLException
    {
        List<Ondografo> ondografos = gdb.consultarOndografos();
        for (Ondografo k : ondografos) {
            this.simularOndografo(k);
        }
    }
    
    private void simularSatelite(Satelite satelite) throws SQLException
    {
        gdb.inserirRegistroAtmosferico
        (
            new RegistroAtmosferico(satelite.getId(), (rng.nextInt(22) + 8) + rng.nextDouble(), (rng.nextInt(178) + 858) + rng.nextDouble(),
                1.2 - rng.nextDouble(), rng.nextInt(16) + rng.nextDouble(), rng.nextInt(360) + rng.nextDouble(), satelite.getBateria(), LocalDateTime.now())
        );
        satelite.setBateria(satelite.getBateria() - 0.025);
        if (satelite.getBateria() < 0.5) {
            satelite.setBateria(1.0);
        }
        gdb.atualizarSatelite(satelite);
    }
    
    public void simularSatelites() throws SQLException
    {
        List<Satelite> satelites = gdb.consultarSatelite();
        for (Satelite k : satelites) {
            simularSatelite(k);
        }
    }
}
