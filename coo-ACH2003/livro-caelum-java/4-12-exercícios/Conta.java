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

    void sacar(double valorSaque) {
        saldo -= valorSaque;
    }

    void deposito(double valorDeposito) {
        saldo += valorDeposito;
    }

    double calculaRendimento() {
        return saldo*0.1;
    }

    String recuperaDadosParaImpressao() {
        String dados = "\nNome:   " + this.nomeTitular;
        dados += "\nNumero da conta:    " + this.numeroConta;
        dados += "\nAgencia:    " + this.agencia;
        dados += "\nSaldo:    " + this.saldo;
        dados += "\nData de abertura:    " + this.dataAbertura.formatar();

        return dados;
    }

}
