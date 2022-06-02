/**
 * exercícios seção 4.12 do livro -> orientação a objetos
 * rodar com
 * javac exercicio.java -> compilar
 * java exercicio -> rodar
 * usar o modelamento de conta em conta.java
*/

public class exercicio {
    public static void main( String[] args ) {
        Conta primeiraConta = new Conta();
        // //recupera os dados com o método do tipo void
        // primeiraConta.recuperaDadosParaImpressao();
        // //recupera os dados com o método do tipo String
        // System.out.println(primeiraConta.recuperaDadosParaImpressao());

        primeiraConta.nomeTitular = "Victor Augusto";
        primeiraConta.numeroConta = 8942937;
        primeiraConta.agencia = "0001";
        primeiraConta.saldo = 1500000;
        primeiraConta.dataAbertura = new Data();
        primeiraConta.dataAbertura.dia = 02;
        primeiraConta.dataAbertura.mes = 06;
        primeiraConta.dataAbertura.ano = 2022;
        
        // //recupera os dados com o método do tipo void
        // primeiraConta.recuperaDadosParaImpressao();
        
        //recupera os dados com o método do tipo String
        System.out.println(primeiraConta.recuperaDadosParaImpressao());
        
        // System.out.println("\n");
        // double rendimento = primeiraConta.calculaRendimento();
        // System.out.println("Rendimento mensal eh "+rendimento);
        
        // primeiraConta.sacar(800000);
        // primeiraConta.deposito(300000);
        
        // rendimento = primeiraConta.calculaRendimento();
        // System.out.println("Rendimento mensal eh "+rendimento);
        // System.out.println("\n");

        // System.out.println("\n\n");
        // Conta c1 = new Conta();
        // c1.nomeTitular = "Teste";
        // c1.saldo = 100;
        // Conta c2 = new Conta();
        // c2.nomeTitular = "Teste";
        // c2.saldo = 100;

        // if (c1 == c2) {
        //     System.out.println("iguais");
        // } else {
        //     System.out.println("diferentes"); //são contas diferentes
        // }
        // c2 = c1;
        // if (c1 == c2) {
        //     System.out.println("iguais"); //agora são iguais
        // } else {
        //     System.out.println("diferentes");
        // }
    }
}