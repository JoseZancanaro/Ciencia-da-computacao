package br.univali.cc.programacao.noaa.ui.gerenciador.control;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.Initializable;

public class InicioController extends AbstractNOAAController implements Initializable
{

    @Override
    public void initialize(URL location, ResourceBundle resources)
    {
        
    }
    
    private void atualizarStatus()
    {
        this.main.definirStatus("Tela inicial do NOAA.");
    }

    @Override
    public void ativar()
    {
        this.atualizarStatus();
    }

    @Override
    public void desativar()
    {
        
    }
    
}
