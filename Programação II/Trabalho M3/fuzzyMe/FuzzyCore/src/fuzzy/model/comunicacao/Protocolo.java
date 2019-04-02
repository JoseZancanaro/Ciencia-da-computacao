package fuzzy.model.comunicacao;

import fuzzy.model.comunicacao.deserializador.Deserializador;
import fuzzy.model.comunicacao.serializador.Serializador;

public class Protocolo
{
    public static Deserializador getDeserializador()
    {
        return Deserializador.criar();
    }
    
    public static Serializador getSerializador()
    {
        return Serializador.criar();
    }
}
