package imobiliaria;

public class Cliente {
    private String nome;
    private String cpf;
    private int idade;
    private int numeroCadastro;
    
    public Cliente(String nome, String cpf, int idade, int numeroCadastro) {
        this.nome = nome;
        this.cpf = cpf;
        this.idade = idade;
        this.numeroCadastro = numeroCadastro;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCpf() {
        return cpf;
    }

    public void setCpf(String cpf) {
        this.cpf = cpf;
    }

    public int getIdade() {
        return idade;
    }

    public void setIdade(int idade) {
        this.idade = idade;
    }
    
     public int getNumeroCadastro() {
        return numeroCadastro;
    }

    public void setNumeroCadastro(int numeroCadastro) {
        this.numeroCadastro = numeroCadastro;
    }
    
    public String toString()
    {
        return String.format("Nome: %s, cpf: %s, idade: %d", this.getNome(), this.getCpf(), this.getIdade());
    }
    
    
}
