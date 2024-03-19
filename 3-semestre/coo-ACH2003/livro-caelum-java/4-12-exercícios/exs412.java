/**
 * exercícios seção 4.12 do livro -> orientação a objetos
 * rodar com
 * javac exercicio.java -> compilar
 * java exercicio -> rodar
 * usar o modelamento de conta em conta.java
*/

public class exs412 {
    public static void main( String[] args ) {
        Conta primeiraConta = new Conta();

        primeiraConta.nomeTitular = "Victor Augusto";
        primeiraConta.numeroConta = 8942937;
        primeiraConta.agencia = "0001";
        primeiraConta.saldo = 1500000;
        primeiraConta.dataAbertura = new Data();
        primeiraConta.dataAbertura.dia = 02;
        primeiraConta.dataAbertura.mes = 06;
        primeiraConta.dataAbertura.ano = 2022;
        
        //recupera os dados com o método do tipo String
        System.out.println(primeiraConta.recuperaDadosParaImpressao());
    }
}