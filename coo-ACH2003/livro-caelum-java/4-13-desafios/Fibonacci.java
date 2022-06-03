public class Fibonacci {
    int calculaFibonacci(int n) {
        return (n<=2)? 1 : calculaFibonacci(n-1) + calculaFibonacci(n-2);
    }
}
