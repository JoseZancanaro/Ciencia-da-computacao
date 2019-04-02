package br.univali.cc.programacao.noaa.ui.gerenciador;

import br.univali.cc.programacao.noaa.ui.model.Alerta;
import java.util.ArrayList;
import java.util.List;
import javafx.scene.control.Alert;

public class GerenciadorDeErro
{
    private static GerenciadorDeErro instancia;
    
    private List<EstadoErro> erros;
    
    private GerenciadorDeErro()
    {
        this.erros = new ArrayList<>();
    }
    
    public static GerenciadorDeErro getInstancia()
    {
        if (instancia == null)
            instancia = new GerenciadorDeErro();
        return instancia;
    }
    
    public void registrar(Exception ex, String titulo, String mensagem)
    {
        if (!erros.stream().anyMatch(e -> e.getEx().equals(e))) {
            erros.add(new EstadoErro(ex, true));
            Alerta.mostrar((titulo == null ? ex.getMessage() : mensagem),
                           (mensagem == null ? ex.getMessage() : mensagem) ,
                           Alert.AlertType.ERROR);
        }
            
    }
}
