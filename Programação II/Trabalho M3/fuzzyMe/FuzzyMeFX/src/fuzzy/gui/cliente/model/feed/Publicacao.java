package fuzzy.gui.cliente.model.feed;

import fuzzy.model.assets.Postagem;
import fuzzy.model.assets.Usuario;
import java.time.format.DateTimeFormatter;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;

public class Publicacao extends HBox
{
    private Postagem postagem;
    private Usuario autor;
    
    private ImageView imagemAutor;
    private Text nomeAutor;
    
    private Text dataPostagem;
    private Text textoPostagem;
    private ImageView imagemPostagem;

    public Publicacao(Postagem postagem, Usuario autor)
    {
        this.postagem = postagem;
        this.autor = autor;
        configurarInterior();
    }
    
    private void configurarInterior()
    {
        HBox.setHgrow(this, Priority.ALWAYS);
        
        VBox containerEsquerdo = new VBox();
        containerEsquerdo.setAlignment(Pos.TOP_CENTER);
        
        imagemAutor = new ImageView(new Image(autor.getFoto().getInputStream()));
        imagemAutor.setFitWidth(64);
        imagemAutor.setFitHeight(64);
        
        containerEsquerdo.getChildren().add(imagemAutor);
        
        VBox containerDireito = new VBox();
        HBox.setHgrow(containerDireito, Priority.ALWAYS);
        
        HBox containerCabecalho = new HBox();
        
        HBox containerTitulo = new HBox();
        nomeAutor = new Text(autor.getNome());
        nomeAutor.setFont(Font.font("System", FontWeight.BOLD, 13));
        containerTitulo.getChildren().add(nomeAutor);
        
        HBox separadorTitulo = new HBox();
        HBox.setHgrow(separadorTitulo, Priority.ALWAYS);
        
        HBox containerDataHora = new HBox();
        containerDataHora.setAlignment(Pos.CENTER_RIGHT);
        dataPostagem = new Text(postagem.getData().format(DateTimeFormatter.ofPattern("d MMM uuuu hh:mm")));
        containerDataHora.getChildren().add(dataPostagem);
        
        containerCabecalho.getChildren().addAll(containerTitulo, separadorTitulo, containerDataHora);
        
        VBox containerConteudo = new VBox();
        
        HBox containerTexto = new HBox();
        textoPostagem = new Text(postagem.getTexto());
        containerTexto.getChildren().addAll(textoPostagem);
        
        HBox containerImagem = new HBox();
        containerImagem.setAlignment(Pos.CENTER);
        imagemPostagem = new ImageView(new Image(postagem.getImagem().getInputStream()));
        imagemPostagem.setFitWidth(426);
        imagemPostagem.setFitHeight(189);
        containerImagem.getChildren().add(imagemPostagem);
        
        containerConteudo.getChildren().addAll(containerTexto, containerImagem);
        
        containerDireito.getChildren().addAll(containerCabecalho, containerConteudo);
        
        this.getChildren().addAll(containerEsquerdo, containerDireito);
        this.setPadding(new Insets(10));
    }
    
}
