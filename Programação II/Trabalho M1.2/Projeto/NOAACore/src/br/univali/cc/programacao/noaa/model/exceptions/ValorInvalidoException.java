package br.univali.cc.programacao.noaa.model.exceptions;

public class ValorInvalidoException extends Exception
{

    public ValorInvalidoException()
    {
    }

    public ValorInvalidoException(String mensagem)
    {
        super(mensagem);
    }
}
