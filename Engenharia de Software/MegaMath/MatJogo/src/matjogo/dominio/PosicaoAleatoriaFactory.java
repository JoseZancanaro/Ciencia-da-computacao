package matjogo.dominio;

import javafx.scene.canvas.GraphicsContext;

public class PosicaoAleatoriaFactory
{
    private final int proxArmadilhas;
    private final double probArmadilhas;
    private int contArmadilhas;
    private final int proxExpressoes;
    private final double probExpressoes;
    private int contExpressoes;

    public PosicaoAleatoriaFactory(int proxArmadilhas, double probArmadilhas, int proxExpressoes, double probExpressoes)
    {
        this.proxArmadilhas = proxArmadilhas;
        this.probArmadilhas = probArmadilhas;
        this.contArmadilhas = -3;
        this.proxExpressoes = proxExpressoes;
        this.probExpressoes = probExpressoes;
        this.contExpressoes = -2;
    }

    public Posicao gerar(int id, PosicaoBlueprint p, GraphicsContext gc)
    {
        if (contArmadilhas >= 0) {
            if (Math.random() <= probArmadilhas) {
                contArmadilhas = proxArmadilhas * -1;
                return new PosicaoArmadilha(id, p.getX(), p.getY(), p.getLargura(), p.getAltura(),
                                    p.getCapacidade(), p.getMargem(), p.getBorda(), gc);
            }
        }
        contArmadilhas++;
        if (contExpressoes >= 0) {
            if (Math.random() <= probExpressoes) {
                contExpressoes = proxExpressoes * -1;
                OperatorType operator = OperatorType.toOperator((int) (Math.random() * 3));
                return new PosicaoExpressao(operator, id, p.getX(), p.getY(), p.getLargura(), p.getAltura(),
                                            p.getCapacidade(), p.getMargem(), p.getBorda(), gc);
            }
        }
        contExpressoes++;
        return new Posicao(id, p.getX(), p.getY(), p.getLargura(), p.getAltura(),
                                p.getCapacidade(), p.getMargem(), p.getBorda(), gc);
    }
}