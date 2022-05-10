/**
 * exercícios seção 3.13 do livro -> fixação de sintaxe
 * rodar com
 * javac exercicio.java -> compilar
 * java exercicio -> rodar
*/

public class exercicio {
    public static void main( String[] args ) {
        System.out.println("\nE01\nImprimir todos os numeros de 150 a 300"); {
            // //em coluna com while
            // int i=150;
            // while( i<=300 ) {
            //     System.out.println("    "+i);
            //     i++;
            // }

            // //em coluna com for
            // int i;
            // for( i = 150; i<=300; i++ ) {
            //     System.out.println("    "+i);
            //     i++;
            // }

            // //em linha
            // System.out.print("    150");
            // int i=151;
            // while( i<=300 ) {
            //     System.out.print(", "+i);
            //     i++;
            // }
        }
            
        System.out.println("\nE02\nImprimir soma dos numeros de 1 a 1000"); {
            // //soma com for
            // int soma = 0;
            // for ( int j = 1; j <=1000; j++ ) {
            //     soma = soma+j;
            // }
            // System.out.println("    A soma de 1 a 1000 eh "+soma);

            // //soma com while
            // int soma = 0;
            // int j = 1;
            // while ( j <=1000) {
            //     soma = soma+j;
            //     j++;
            // }
            // System.out.println("    A soma de 1 a 1000 eh "+soma);
        }
        
        System.out.println("\nE03\nImprimir os multiplos de 3 entre 1 e 100"); {
            // //usando for + if
            // int multiplos;
            // for ( multiplos=1; multiplos<100; multiplos++ ) {
            //     //if completão
            //     if( multiplos%3 == 0 ) {
            //             System.out.println("    "+multiplos);
            //     }
                    
            //     //if simplificado
            //     if(multiplos%3 == 0) System.out.println("    "+multiplos);
            //     }
            // }

            // //outro jeito com for
            // int k;
            // for (k=1; k<=(100/3); k++) {
            //     System.out.println("    "+k*3);
            // }

            // //outro jeito
            // int l;
            // for (l=1; l<100; l+=3) {
            //     System.out.println("    "+l);
            // }
        }

        System.out.println("\nE04\nImprimir fatoriais de 1 a 10"); {
            // int fatorial10 = 1;
            // for (int f=1;f<=10;f++) {
            //     fatorial10 *= f;
            //     System.out.println("    "+f+"! = "+fatorial10);
            // }
        }

        System.out.println("\nE05\nImprimir fatoriais de 1 a 20,30 e 40"); {
            // System.out.println("    Fatorial 1 a 20");
            // long fatorial20 = 1; //com o tipo de dado int no 17! ele começa a dar problema
            // for (int f=1;f<=20;f++) {
            //     fatorial20 *= f;
            //     System.out.println("        "+f+"! = "+fatorial20);
            // }
            // System.out.println("    Fatorial 1 a 30");
            // long fatorial30 = 1; //a partir do 21! o tipo de dado long começa a falhar
            // for (int f=1;f<=30;f++) {
            //     fatorial30 *= f;
            //     System.out.println("        "+f+"! = "+fatorial30);
            // }
            // System.out.println("    Fatorial 1 a 40");
            // long fatorial40 = 1;
            // for (int f=1;f<=40;f++) {
            //     fatorial40 *= f;
            //     System.out.println("        "+f+"! = "+fatorial40);
            // }
        }
    
        System.out.println("\nE06\nImprimir a serie de Fibonacci ateh passar de 100"); {
            // //minha resolução
            // int fibonacci1 = 0;
            // int fibonacci2 = 1;
            // int soma = fibonacci1 + fibonacci2;
            // System.out.println("    "+fibonacci1+"\n    "+fibonacci2);
            // while ( soma <= 100 ) {
            //     System.out.println("    "+soma);
            //     fibonacci1 = fibonacci2;
            //     fibonacci2 = soma;
            //     soma = fibonacci1 + fibonacci2;
            // }
            // System.out.println("    "+soma);

            // //resposta dada no livro
            // int anterior = 0;
            // int atual = 1;
            // while (atual<100) {
            //     System.out.println(atual);
            //     int proximo = anterior + atual;
            //     anterior = atual;
            //     atual = proximo;
            // }
            // System.out.println(atual);
        }
            
        System.out.println("\nE07\nDado x, se x eh par x=x/2, se x eh impar x=3*x+1, o programa para quando x=1"); {
            // int x = 13;
            // System.out.println("    Valor inicial eh x = "+x);
            // System.out.print("    ");
            
            // while ( x!=1 ) {
            //     if ( x%2 == 0 ) {
            //         x = x/2;
            //     } else {
            //         x = 3*x + 1;
            //     }
                
            //     System.out.print(x);
            //     if (x!=1) System.out.print(" -> ");
            // }
        }
        
        System.out.println("\nE08\nImprimir uma tabela com n linhas e n*n colunas, o valor de cada casa eh linha*coluna para linha>=coluna ou vazio"); {
            // int n = 5;
            // for ( int linha = 1; linha<=n; linha++ ) {
            //     for ( int coluna = 1; coluna<=n; coluna++ ) {
            //         if ( linha>=coluna ) {
            //             if (linha*coluna<10) {
            //                 System.out.print("    0"+linha*coluna);
            //             } else {
            //                 System.out.print("    "+linha*coluna);
            //             }
            //         }
            //     }
            //     System.out.print("\n");
            // }
        }
        
        System.out.println("\nDesafio\nFibonacci do E06 com apenas duas variaveis"); {
            // //minha resolução do exercício
            // int fibonacci1 = 0;
            // int fibonacci2 = 1;
            // System.out.println("    "+fibonacci1+"\n    "+fibonacci2);
            // while ( (fibonacci1 + fibonacci2) <= 100 ) {
            //     System.out.println("    "+ (fibonacci1+fibonacci2));
            //     if ( fibonacci2>=fibonacci1 ) { //ideia para deslocar o número à esquerda para a direita
            //         fibonacci1 += fibonacci2;
            //     } else {
            //         fibonacci2 += fibonacci1;
            //     }
            // }
            // System.out.println("    "+(fibonacci1 + fibonacci2));

            // //resolução da apostila
            // int anterior = 0;
            // int atual = 1;
            // while (atual < 100) {
            //     System.out.println(atual);
            //     atual = anterior + atual;
            //     anterior = atual - anterior;
            // }
            // System.out.println(atual);
        }

    }
}
