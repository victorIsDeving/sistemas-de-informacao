public class FibRecursivoTeste {
    public static void main( String[] args ) {     
        System.out.println("\nDesafio\nFibonacci usando um metodo recursivo");
        
        Fibonacci fibonacci = new Fibonacci();
        for (int i = 1; i <= 6; i++) {
            int resultado = fibonacci.calculaFibonacci(i);
            System.out.print(resultado+" ");
        }
    }
}
