package fuzzy.model.servidor.persistencia;

import fuzzy.model.assets.ImagemFuzzy;
import fuzzy.model.assets.Postagem;
import fuzzy.model.assets.Usuario;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;

public class GerenciadorDeBanco
{
    private static final String URL = "jdbc:mysql://localhost/fuzzy";
    private static final String USUARIO = "root";
    private static final String SENHA = "";
    
    private static GerenciadorDeBanco instancia = null;
    
    private GerenciadorDeBanco() throws ClassNotFoundException
    {
        Class.forName("org.mariadb.jdbc.Driver");
    }
    
    public static GerenciadorDeBanco getInstancia() throws ClassNotFoundException
    {
        if (instancia == null)
            instancia = new GerenciadorDeBanco();
        return instancia;
    }
    
    private Connection getConexao() throws SQLException
    {
        return DriverManager.getConnection(URL, USUARIO, SENHA);
    }
    
    public List<Usuario> getUsuarios(String filtro) throws SQLException
    {
        List<Usuario> usuarios = new ArrayList<>();
        try (Connection conexao = this.getConexao()) {
            Statement comando = conexao.createStatement();
            ResultSet rs = comando.executeQuery("SELECT * FROM fuzzy.usuarios " + filtro + ";");
            while (rs.next()) {
                usuarios.add(new Usuario(rs.getInt("id"), rs.getString("nome"), 
                                new ImagemFuzzy(rs.getBlob("foto").getBinaryStream())));
            }
        }
        
        return usuarios;
    }
    
    public List<Usuario> getUsuarios() throws SQLException
    {
        return this.getUsuarios("");
    }
    
    public List<Postagem> getPostagens(String filtro) throws SQLException
    {
        List<Postagem> postagens = new ArrayList<>();
        try (Connection conexao = this.getConexao()) {
            Statement comando = conexao.createStatement();
            ResultSet rs = comando.executeQuery("SELECT * FROM fuzzy.posts " + filtro + ";");
            while (rs.next()) {
                postagens.add(new Postagem(rs.getInt("id"), rs.getInt("id_autor"), rs.getString("texto"),
                                new ImagemFuzzy(rs.getBlob("imagem").getBinaryStream()), rs.getTimestamp("data").toLocalDateTime()));
            }
        }
        return postagens;
    }
    
    public List<Postagem> getPostagens() throws SQLException
    {
        return this.getPostagens("");
    }
    
    public boolean inserirUsuario(Usuario usuario) throws SQLException
    {
        boolean inseriu;
        
        try (Connection conexao = this.getConexao()) {
            PreparedStatement comando = conexao.prepareStatement("INSERT INTO fuzzy.usuarios (nome, senha, foto) VALUES (?, ?, ?);");
            comando.setString(1, usuario.getNome());
            comando.setString(2, usuario.getSenha());
            comando.setBlob(3, usuario.getFoto().getInputStream());
            
            inseriu = comando.executeUpdate() > 0;
        }
        
        return inseriu;
    }
    
    public boolean inserirPostagem(Postagem postagem) throws SQLException
    {
        boolean inseriu;
        
        try (Connection conexao = this.getConexao()) {
            PreparedStatement comando = conexao.prepareStatement("INSERT INTO fuzzy.posts (id_autor, texto, imagem, data) VALUES (?, ?, ?, ?);");
            comando.setInt(1, postagem.getIdAutor());
            comando.setString(2, postagem.getTexto());
            comando.setBlob(3, postagem.getImagem().getInputStream());
            comando.setTimestamp(4, Timestamp.valueOf(postagem.getData()));
            
            inseriu = comando.executeUpdate() > 0;
        }
        
        return inseriu;
    }
    
    public boolean removerUsuario(Usuario usuario) throws SQLException
    {
        boolean removeu;
        
        try (Connection conexao = this.getConexao()) {
            PreparedStatement comando = conexao.prepareStatement("DELETE FROM fuzzy.usuarios WHERE fuzzy.usuarios.id = ?;");
            comando.setInt(1, usuario.getId());
            
            removeu = comando.executeUpdate() > 0;
        }
        
        return removeu;
    }
    
    public boolean removerPostagem(Postagem postagem) throws SQLException
    {
        boolean removeu;
        
        try (Connection conexao = this.getConexao()) {
            PreparedStatement comando = conexao.prepareStatement("DELETE FROM fuzzy.posts WHERE fuzzy.posts.id = ?;");
            comando.setInt(1, postagem.getId());
            
            removeu = comando.executeUpdate() > 0;
        }
        
        return removeu;
    }
}
