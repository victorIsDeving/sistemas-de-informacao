/**
 * exercícios seção 4.12 do livro -> orientação a objetos
 * rodar com
 * javac conta.java -> compilar
 * java exercicio -> rodar
 * modelamento de uma conta bancária
*/
public class Conta {
    String nomeTitular;
    int numeroConta;
    String agencia;
    double saldo;
    Data dataAbertura;

    boolean sacar(double valorSaque) {
        saldo -= valorSaque;
        return true;
    }

    boolean deposito(double valorDeposito) {
        saldo += valorDeposito;
        return true;
    }

    double calculaRendimento() {
        return saldo*0.1;
    }

    // void recuperaDadosParaImpressao() {
    //     System.out.println("\nNome:   "+this.nomeTitular);
    //     System.out.println("Numero da conta:   "+this.numeroConta);
    //     System.out.println("Agencia:   "+this.agencia);
    //     System.out.println("Saldo disponivel:   "+this.saldo);
    //     System.out.println("Data de abertura:   "+this.dataAbertura);
    // }

    String recuperaDadosParaImpressao() {
        String dados = "\nNome:   " + this.nomeTitular;
        dados += "\nNumero da conta:    " + this.numeroConta;
        dados += "\nAgencia:    " + this.agencia;
        dados += "\nSaldo:    " + this.saldo;
        dados += "\nData de abertura:    " + this.dataAbertura.formatar();

        return dados;
    }

}
