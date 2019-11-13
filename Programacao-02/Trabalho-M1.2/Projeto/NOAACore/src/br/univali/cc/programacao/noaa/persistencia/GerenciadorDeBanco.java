package br.univali.cc.programacao.noaa.persistencia;

import br.univali.cc.programacao.noaa.model.CategoriaEvento;
import br.univali.cc.programacao.noaa.model.EventoClimatico;
import br.univali.cc.programacao.noaa.model.Ondografo;
import br.univali.cc.programacao.noaa.model.RegistroAtmosferico;
import br.univali.cc.programacao.noaa.model.RegistroMeteoceanografico;
import br.univali.cc.programacao.noaa.model.Satelite;
import br.univali.cc.programacao.noaa.model.SituacaoEvento;
import br.univali.cc.programacao.noaa.model.TipoEvento;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class GerenciadorDeBanco
{
    private static final String URL = "jdbc:mysql://localhost/noaa";
    private static final String USUARIO = "root";
    private static final String SENHA = "";

    public GerenciadorDeBanco() throws ClassNotFoundException
    {
        Class.forName("com.mysql.jdbc.Driver");
    }
    
    private Connection getConnection() throws SQLException
    {
        return DriverManager.getConnection(URL, USUARIO, SENHA);
    }
    
    /* MÉTODOS: ONDÓGRAFO */
    
    public void inserirOndografo(Ondografo ondografo) throws SQLException
    {
        Connection conexao = this.getConnection();
        
        PreparedStatement comando = conexao.prepareStatement
        (
            "INSERT INTO ondografos (nome, latitude, longitude, bateria, data_lancamento) VALUES (?, ?, ?, ?, ?)"
        );
        comando.setString(1, ondografo.getNome());
        comando.setDouble(2, ondografo.getLatitude());
        comando.setDouble(3, ondografo.getLongitude());
        comando.setDouble(4, ondografo.getBateria());
        comando.setTimestamp(5, Timestamp.valueOf(ondografo.getDataLancamento()));
        comando.execute();
        
        conexao.close();
    }
    
    public boolean atualizarOndografo(Ondografo ondografo) throws SQLException
    {
        Connection conexao = this.getConnection();
        
        PreparedStatement comando = conexao.prepareStatement
        (
            "UPDATE ondografos SET nome = ?, latitude = ?, longitude = ?, bateria = ?, data_lancamento = ? " +
            "WHERE ondografos.id = ?"
        );
        
        comando.setString(1, ondografo.getNome());
        comando.setDouble(2, ondografo.getLatitude());
        comando.setDouble(3, ondografo.getLongitude());
        comando.setDouble(4, ondografo.getBateria());
        comando.setTimestamp(5, Timestamp.valueOf(ondografo.getDataLancamento()));
        comando.setInt(6, ondografo.getId());
        
        boolean atualizou = comando.executeUpdate() > 0;
        
        conexao.close();
        
        return atualizou;
    }
   
    public boolean deletarOndografo(Ondografo ondografo) throws SQLException
    {
        Connection conexao = this.getConnection();

        PreparedStatement comando = conexao.prepareStatement
        (
            "DELETE FROM ondografos WHERE ondografos.id = ?"
        );

        comando.setInt(1, ondografo.getId());

        boolean deletou = comando.executeUpdate() > 0;

        conexao.close();

        return deletou;
    }
    
    public List<Ondografo> consultarOndografos(String filtro) throws SQLException
    {
        List<Ondografo> lista = new ArrayList<>();
        
        Connection conexao = this.getConnection();
        
        Statement comando = conexao.createStatement();
        ResultSet rs = comando.executeQuery("SELECT * FROM ondografos ");
        while(rs.next()) {
            lista.add(new Ondografo(rs.getInt("id"), rs.getString("nome"), rs.getDouble("latitude"), rs.getDouble("Longitude"),
                                    rs.getDouble("bateria"), rs.getTimestamp("data_lancamento").toLocalDateTime()));
        }
        
        conexao.close();
            
        return lista;
    }
    
    public List<Ondografo> consultarOndografos() throws SQLException
    {
        return this.consultarOndografos("");
    }
    
    /* MÉTODOS: ONDÓGRAFO */
    
    /* MÉTODOS: SATÉLITE*/
    
    public void inserirSatelite(Satelite satelite) throws SQLException
    {
        Connection conexao = this.getConnection();
        
        PreparedStatement comando = conexao.prepareStatement
        (
            "INSERT INTO satelites (nome, latitude, longitude, angulo, bateria, data_lancamento) VALUES (?, ?, ?, ?, ?, ?)"
        );
        comando.setString(1, satelite.getNome());
        comando.setDouble(2, satelite.getLatitude());
        comando.setDouble(3, satelite.getLongitude());
        comando.setDouble(4, satelite.getAngulo());
        comando.setDouble(5, satelite.getBateria());
        comando.setTimestamp(6, Timestamp.valueOf(satelite.getDataLancamento()));
        comando.execute();
        
        conexao.close();
    }
    
    public boolean atualizarSatelite(Satelite satelite) throws SQLException
    {
        Connection conexao = this.getConnection();
        
        PreparedStatement comando = conexao.prepareStatement
        (
            "UPDATE satelites SET nome = ?, latitude = ?, longitude = ?, angulo = ?, bateria = ?, data_lancamento = ? " +
            "WHERE satelites.id = ?"
        );
        
        comando.setString(1, satelite.getNome());
        comando.setDouble(2, satelite.getLatitude());
        comando.setDouble(3, satelite.getLongitude());
        comando.setDouble(4, satelite.getAngulo());
        comando.setDouble(5, satelite.getBateria());
        comando.setTimestamp(6, Timestamp.valueOf(satelite.getDataLancamento()));
        comando.setInt(7, satelite.getId());
        
        boolean atualizou = comando.executeUpdate() > 0;
        
        conexao.close();
        
        return atualizou;
    }
    
    public boolean deletarSatelite(Satelite satelite) throws SQLException
    {
        Connection conexao = this.getConnection();

        PreparedStatement comando = conexao.prepareStatement
        (
            "DELETE FROM satelites WHERE satelites.id = ?"
        );

        comando.setInt(1, satelite.getId());

        boolean deletou = comando.executeUpdate() > 0;

        conexao.close();

        return deletou;
    }
    
    public List<Satelite> consultarSatelite(String filtro) throws SQLException
    {
        List<Satelite> lista = new ArrayList<>();
        
        Connection conexao = this.getConnection();
        
        Statement comando = conexao.createStatement();
        ResultSet rs = comando.executeQuery("SELECT * FROM satelites ");
        while(rs.next()) {
            lista.add(new Satelite(rs.getInt("id"), rs.getString("nome"), rs.getDouble("latitude"), rs.getDouble("Longitude"),
                                   rs.getDouble("angulo"), rs.getDouble("bateria"), rs.getTimestamp("data_lancamento").toLocalDateTime()));
        }
        
        conexao.close();
            
        return lista;
    }
    
    public List<Satelite> consultarSatelite() throws SQLException
    {
        return this.consultarSatelite("");
    }
    
    /* MÉTODOS: SATÉLITE*/
    
    /* MÉTODOS: REGISTRO METEOCEANOGRÁFICOS */
    
    public void inserirRegistroMeteoceanografico(RegistroMeteoceanografico registro) throws SQLException
    {
        Connection conexao = this.getConnection();
        
        PreparedStatement comando = conexao.prepareStatement
        (
            "INSERT INTO registrosMeteoceanograficos (id_ondografo, temperatura, umidade, pressao, altura, corrente, direcao_corrente, vento, direcao_vento, bateria, data) " +
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
        );
        comando.setInt(1, registro.getIdOndografo());
        comando.setDouble(2, registro.getTemperatura());
        comando.setDouble(3, registro.getUmidade());
        comando.setDouble(4, registro.getPressao());
        comando.setDouble(5, registro.getAltura());
        comando.setDouble(6, registro.getCorrente());
        comando.setDouble(7, registro.getDirecaoCorrente());
        comando.setDouble(8, registro.getVento());
        comando.setDouble(9, registro.getDirecaoVento());
        comando.setDouble(10, registro.getBateria());
        comando.setTimestamp(11, Timestamp.valueOf(registro.getData()));
        comando.execute();
        
        conexao.close();
    }
    
    public boolean deletarRegistroMeteoceanografico(RegistroMeteoceanografico registro) throws SQLException
    {
        Connection conexao = this.getConnection();
        
        PreparedStatement comando = conexao.prepareStatement
        (
            "DELETE FROM registrosMeteoceanograficos WHERE registrosMeteoceanograficos.id = ?"
        );
        comando.setInt(1, registro.getId());
        
        boolean deletou = comando.executeUpdate() > 0;
        
        conexao.close();
        
        return deletou;
    }
    
    public List<RegistroMeteoceanografico> consultarRegistrosMeteoceanograficos(String filtro) throws SQLException
    {
        List<RegistroMeteoceanografico> lista = new ArrayList<>();
        
        Connection conexao = this.getConnection();
        
        Statement comando = conexao.createStatement();
        ResultSet rs = comando.executeQuery("SELECT * FROM registrosMeteoceanograficos " + filtro);
        
        while(rs.next()){
            lista.add(new RegistroMeteoceanografico(rs.getInt("id"), rs.getInt("id_ondografo"), rs.getDouble("temperatura"), rs.getDouble("umidade"),
                        rs.getDouble("pressao"), rs.getDouble("altura"), rs.getDouble("corrente"), rs.getDouble("direcao_corrente"), rs.getDouble("vento"),
                        rs.getDouble("direcao_vento"), rs.getDouble("bateria"), rs.getTimestamp("data").toLocalDateTime()));
        }
        
        conexao.close();
        
        return lista;
    }
    
    public List<RegistroMeteoceanografico> consultarRegistrosMeteoceanograficos() throws SQLException
    {
        return this.consultarRegistrosMeteoceanograficos("");
    }
    
    public List<RegistroMeteoceanografico> consultarRegistrosMeteoceanograficosDec(String filtro) throws SQLException
    {
        return this.consultarRegistrosMeteoceanograficos(filtro + " ORDER BY data DESC");
    }
    
    public List<RegistroMeteoceanografico> consultarRegistrosMeteoceanograficosDec() throws SQLException
    {
        return this.consultarRegistrosMeteoceanograficos("ORDER BY data DESC");
    }
    
    /* MÉTODOS: REGISTRO METEOCEANOGRÁFICOS */
    
    /* MÉTODOS: REGISTRO ATMOSFÉRICO */
    
    public void inserirRegistroAtmosferico(RegistroAtmosferico registro) throws SQLException
    {
        Connection conexao = this.getConnection();
        
        PreparedStatement comando = conexao.prepareStatement
        (
            "INSERT INTO registrosAtmosfericos (id_satelite, temperatura, pressao, densidade, vento, direcao_vento, bateria, data) " +
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?)"
        );
        comando.setInt(1, registro.getIdSatelite());
        comando.setDouble(2, registro.getTemperatura());
        comando.setDouble(3, registro.getPressao());
        comando.setDouble(4, registro.getDensidade());
        comando.setDouble(5, registro.getVento());
        comando.setDouble(6, registro.getDirecaoVento());
        comando.setDouble(7, registro.getBateria());
        comando.setTimestamp(8, Timestamp.valueOf(registro.getData()));
        comando.execute();
        
        conexao.close();
    }
    
    public boolean deletarRegistroAtmosferico(RegistroAtmosferico registro) throws SQLException
    {
        Connection conexao = this.getConnection();
        
        PreparedStatement comando = conexao.prepareStatement
        (
            "DELETE FROM registrosAtmosfericos WHERE registrosAtmosfericos.id = ?"
        );
        comando.setInt(1, registro.getId());
        
        boolean deletou = comando.executeUpdate() > 0;
        
        conexao.close();
        
        return deletou;
    }
    
    public List<RegistroAtmosferico> consultarRegistrosAtmosfericos(String filtro) throws SQLException
    {
        List<RegistroAtmosferico> lista = new ArrayList<>();
        
        Connection conexao = this.getConnection();
        
        Statement comando = conexao.createStatement();
        ResultSet rs = comando.executeQuery("SELECT * FROM registrosAtmosfericos " + filtro);
        
        while(rs.next()){
            lista.add(new RegistroAtmosferico(rs.getInt("id"), rs.getInt("id_satelite"), rs.getDouble("temperatura"), rs.getDouble("pressao"),
                        rs.getDouble("densidade"), rs.getDouble("vento"), rs.getDouble("direcao_vento"), 
                        rs.getDouble("bateria"), rs.getTimestamp("data").toLocalDateTime()));
        }
        
        conexao.close();
        
        return lista;
    }
    
    public List<RegistroAtmosferico> consultarRegistrosAtmosfericos() throws SQLException
    {
        return this.consultarRegistrosAtmosfericos("");
    }
    
    public List<RegistroAtmosferico> consultarRegistrosAtmosfericosDec(String filtro) throws SQLException
    {
        return this.consultarRegistrosAtmosfericos(filtro + " ORDER BY data DESC");
    }
    
    public List<RegistroAtmosferico> consultarRegistrosAtmosfericosDec() throws SQLException
    {
        return this.consultarRegistrosAtmosfericos("ORDER BY data DESC");
    }
    
    /* MÉTODOS: REGISTRO ATMOSFÉRICO */

    /* MÉTODOS: EVENTO CLIMÁTICO */
    
    public void inserirEventoClimatico(EventoClimatico evento) throws SQLException
    {
        Connection conexao = this.getConnection();
        
        PreparedStatement comando = conexao.prepareStatement
        (
            "INSERT INTO eventosClimaticos (tipo, latitude, longitude, descricao, data_inicio, data_fim, situacao, categoria) VALUES (?, ?, ?, ?, ?, ?, ?, ?)"
        );
        comando.setString(1, evento.getTipo().toString());
        comando.setDouble(2, evento.getLatitude());
        comando.setDouble(3, evento.getLongitude());
        comando.setString(4, evento.getDescricao());
        comando.setTimestamp(5, Timestamp.valueOf(evento.getDataInicio()));
        comando.setTimestamp(6, (evento.getDataFim() == null ? null : Timestamp.valueOf(evento.getDataFim())));
        comando.setString(7, evento.getSituacao().toString());
        comando.setString(8, evento.getCategoria().toString());
        comando.execute();
        
        conexao.close();
    }
    
    public boolean atualizarEventoClimatico(EventoClimatico evento) throws SQLException
    {
        Connection conexao = this.getConnection();
        
        PreparedStatement comando = conexao.prepareStatement
        (
            "UPDATE eventosClimaticos SET tipo = ?, latitude = ?, longitude = ?, descricao = ?, data_inicio = ?, data_fim = ?, situacao = ?, categoria = ? " +
            "WHERE eventosClimaticos.id = ?"
        );
        
        comando.setString(1, evento.getTipo().toString());
        comando.setDouble(2, evento.getLatitude());
        comando.setDouble(3, evento.getLongitude());
        comando.setString(4, evento.getDescricao());
        comando.setTimestamp(5, Timestamp.valueOf(evento.getDataInicio()));
        comando.setTimestamp(6, (evento.getDataFim() == null ? null : Timestamp.valueOf(evento.getDataFim())));
        comando.setString(7, evento.getSituacao().toString());
        comando.setString(8, evento.getCategoria().toString());
        comando.setInt(9, evento.getId());
        
        boolean atualizou = comando.executeUpdate() > 0;
        
        conexao.close();
        
        return atualizou;
    }
    
    public boolean deletarEventoClimatico(EventoClimatico evento) throws SQLException
    {
        Connection conexao = this.getConnection();

        PreparedStatement comando = conexao.prepareStatement
        (
            "DELETE FROM eventosClimaticos WHERE eventosClimaticos.id = ?"
        );

        comando.setInt(1, evento.getId());

        boolean deletou = comando.executeUpdate() > 0;

        conexao.close();

        return deletou;
    }
    
    public List<EventoClimatico> consultarEventosClimaticos(String filtro) throws SQLException
    {
        List<EventoClimatico> lista = new ArrayList<>();
        
        Connection conexao = this.getConnection();
        
        Statement comando = conexao.createStatement();
        ResultSet rs = comando.executeQuery("SELECT * FROM eventosClimaticos " + filtro);
        
        while(rs.next()){
            Timestamp tfim = rs.getTimestamp("data_fim");
            LocalDateTime fim = tfim == null ? null : tfim.toLocalDateTime();
            lista.add(new EventoClimatico(rs.getInt("id"), TipoEvento.valueOf(rs.getString("tipo")), rs.getDouble("latitude"), rs.getDouble("longitude"),
                        rs.getString("descricao"), rs.getTimestamp("data_inicio").toLocalDateTime(), fim,
                        SituacaoEvento.valueOf(rs.getString("situacao")), CategoriaEvento.valueOf(rs.getString("categoria"))));
        }
        
        conexao.close();
        
        return lista;
    }
    
    public List<EventoClimatico> consultarEventosClimaticos() throws SQLException
    {
        return this.consultarEventosClimaticos("");
    }
    
    /* MÉTODOS: EVENTO CLIMÁTICO */
}