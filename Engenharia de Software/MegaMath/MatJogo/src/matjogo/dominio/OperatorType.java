package matjogo.dominio;

import java.util.function.BiFunction;

public enum OperatorType
{
    ADD(0, "+", (Double l, Double r) -> l + r),
    SUB(1, "-", (Double l, Double r) -> l - r),
    MULT(2, "*", (Double l, Double r) -> l * r),
    DIV(3, "/", (Double l, Double r) -> l / r);
    
    private final String caractere;
    private final int num;
    private final BiFunction<Double, Double, Double> fn;

    private OperatorType(int num, String caractere, BiFunction<Double, Double, Double> fn)
    {
        this.caractere = caractere;
        this.num = num;
        this.fn = fn;
    }

    public String getCaractere()
    {
        return caractere;
    }

    public int getNum()
    {
        return num;
    }

    public BiFunction<Double, Double, Double> getOperacao()
    {
        return fn;
    }

    public static OperatorType toOperator(int num)
    {
        OperatorType ot = OperatorType.ADD;
        for (OperatorType it : OperatorType.values()) {
            if (it.getNum() == num)
                return it;
        }
        return ot;
    }
}
