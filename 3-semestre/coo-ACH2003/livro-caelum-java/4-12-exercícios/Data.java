/**
 * exercícios seção 4.12 do livro -> orientação a objetos
 * rodar com
 * javac Data.java -> compilar
 * java exercicio -> rodar
 * modelamento de uma data para usar no modelo de conta, no atributo data de abertura
*/
public class Data {
    int dia;
    int mes;
    int ano;

    String formatar() {
        String dataFormatada = this.dia + "/" + this.mes + "/" + this.ano;
        return dataFormatada;
    }
}
