class MeuPrograma {
    public static void main(String[] args) {
        System.out.println("Meu primeiro programa Java!\nQuebra de linha em Java!");
        System.out.println("Segunda linha em Java!");
        System.out.println("Troquei o nome do arquivo e compilou com o nome antigo");
        
        /* Comentário
        multilinhas */
        //comentário de uma linha
        int idade = 27;
        System.out.println("\nVariavel idade: " + idade);
        
        boolean valor = true;
        System.out.println("Variavel valor: " + valor);
        
        System.out.println("\nTeste da estrutura if com as variaveis idade e valor:");
        if ( valor && idade >= 18 ) {
            System.out.println("    valor=true e idade>=18\n");
        } else {
            System.out.println("    valor!=true ou idade<18\n");
        }
        
        
        System.out.println("\nTeste de loop while:");
        int i = 0;
        while (i<5) {
            System.out.println("    "+i);
            i++;
        }

        System.out.println("\nTeste de loop for:");
        for ( int j = 4; j>=0; j-- ) {
            System.out.println("    "+j);
        }

    }
}