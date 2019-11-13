package fuzzy.gui.cliente.control;

import fuzzy.model.assets.Postagem;
import fuzzy.model.assets.Usuario;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;
import javafx.scene.shape.Circle;
import javafx.scene.text.Text;

public class Publicacao extends HBox
{
    @FXML private ImageView avatar;
    @FXML private Text nome;
    @FXML private Text data;
    @FXML private Text texto;
    @FXML private ImageView imagem;
    
    private Usuario usuario;
    private Postagem postagem;

    public Publicacao(Usuario usuario, Postagem postagem)
    {
        try {
            FXMLLoader carregador = new FXMLLoader(getClass().getResource("/fuzzy/gui/cliente/view/PublicacaoView.fxml"));
            carregador.setRoot(this);
            carregador.setController(this);
            carregador.load();
            
            this.setUsuario(usuario);
            this.setPostagem(postagem);
            this.setAvatar(new Image(usuario.getFoto().getInputStream()));
            this.setNome(usuario.getNome());
            this.setData(postagem.getData());
            this.setTexto(postagem.getTexto());
            this.setImagem(new Image(postagem.getImagem().getInputStream()));
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
    }

    private void setAvatar(Image avatar)
    {
        this.avatar.setImage(avatar);
        this.avatar.setClip(new Circle(this.avatar.getX() + 32.0, this.avatar.getY() + 32.0, 32.0));
    }

    private void setNome(String nome)
    {
        this.nome.setText(nome);
    }

    private void setData(LocalDateTime data)
    {
        this.data.setText(data.format(DateTimeFormatter.ofPattern("d MMM uuuu hh:mm")));
    }

    private void setTexto(String texto)
    {
        this.texto.setText(texto);
    }

    private void setImagem(Image imagem)
    {
        this.imagem.setImage(imagem);
    }

    private void setUsuario(Usuario usuario)
    {
        this.usuario = usuario;
    }

    private void setPostagem(Postagem postagem)
    {
        this.postagem = postagem;
    }

    public Usuario getUsuario()
    {
        return usuario;
    }

    public Postagem getPostagem()
    {
        return postagem;
    }
}
