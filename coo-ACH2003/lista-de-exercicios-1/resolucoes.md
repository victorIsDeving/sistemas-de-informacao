## Resoluções da lista de exercício

### Ex 1
#### Explique como cada um dos recursos abaixo disponíveis na linguagem Java possibilitam a criação de um código com melhor qualidade:  
- **Possibilidade de criação de pacotes** 
Pacotes podem agrupar classes de funcionalidades similares ou relacionadas. Isso pode ser muito útil quando temos mais de um desenvolvedor trabalhando em um projeto, onde um usará classes que foram criadas pelo outro. O uso de pacotes previne que ocorra um erro pela criação de classes com o mesmo nome feitas por desenvolvedores diferentes. Essa é a ideia principal de utilizar um pacote com Java, mas tem outras vantagens que ajudam a fazer o código como um todo ter uma qualidade melhor:
    - *Facilita a busca e a localização de classes específicas* 
    - *Implementa o encapsulamento de dados*
    - *Fornece a possibilidade de controle de acesso de acordo com níveis de pacotes*
    - *Reuso de classes em pacotes de outros programas*

- **Mecanismo para tratamento de exceções** 
Uma exceção é para o tratamento de erros, é uma forma de preparar o sistema para lidar com uma situação estranha ou inesperada ((http://web.mit.edu/java_v1.0.2/www/tutorial/java/exceptions/definition.html)[link]). O uso de exceções tem as seguintes vantagens para o desenvolvimento:
    - *"Separa" o tratamento de erros do código principal do programa*. Pelo sistema de `try` e `catch` das exceptions, é possível deixar claro o que é o fluxo principal que resolve um problema e o que é o código que trata os possiveis erros que podem ocorrer no fluxo principal
    - *Propagar erros para "cima"*. Num caso em que temos métodos encadeados, um chamando o outro, com o uso de exceções é possível focalizar qual dos métodos nós queremos que trate o erro. Se o erro ocorrer no terceiro método encadeado na chamada, podemos tratar o erro no primeiro método
    - *Agrupamento e diferenciação dos erros*. Isso permite tratamento de erros de uma forma genérica, assim podemos generalizar casos parecidos, e também tratar erros de forma específica, criando um foco especial em casos de erro importantes

- **Tipos genéricos**
Os tipos genéricos dão maior estabilidade para o código, permite a detecção de bugs no momento da compilação ((https://www.javatpoint.com/generics-in-java)[link]).
    - *Controle do tipo armazenado*. Podemos especificar o tipo de dado que queremos armazenar, evitando qualquer surpresa de tratar um dado que não correspode ao tipo que esperávamos encontrar.
    - *Não precisamos usar um type cast ao recuperar um dado*. Como controlamos os tipos de dado na entrada do armazenamento, não tem necessidade de um controle para a saída de dados armazenados.
    - *Verificação de erros no compilamento*. Previne erros que poderiam acontecer na execução do programa, esses erros agora vão aparecer durante o compilamento (o melhor momento para um programa apresentar erros)

### Ex 2
#### Considere o cenário em que uma classe qualquer define um atributo de instância, e é esperado que os “clientes/usuários” que manipulam instâncias desta classe sejam capazes tanto de obter o valor atual do atributo, quanto de alterá-lo. Por que, mesmo neste caso, é recomendável proteger o atributo, tornando-o privado, e definir getters e setters para o atributo em questão?  
Tornar um atributo privado faz com que apenas a classe que declara esse atributo tenha o poder de fazer modificações nele. Isso facilita muito a implementação de mudanças, é o _encapsulamento_ dos membros de uma classe. O uso de métodos `get`e `set` é a forma pela qual iremos acessar ou mudar o valor do atributo fora dessa classe. 
Essa forma de implementação em que os atributos são privados e os métodos são públicos (_interface da classe_, como nos comunicamos com os objetos dessa classe) é muito comum, dessa forma, se tivermos que fazer alguma alteração com relação ao atributo privado não precisamos ir em todos os lugares do código em que esse atributo foi utilizado para adaptar, basta alterarmos os métodos `get` e `set`.

> PROGRAMANDO VOLTADO À INTERFACE, E NÃO À IMPLEMENTAÇÃO  
> É sempre bom programar pensando na interface da sua classe, em como seus usuários estarão utilizando-a, e não somente em como ela funcionará.  
> A implementação em si, o conteúdo dos métodos, não tem tanta importância para o usuário dessa classe, pois ele só precisa saber o que cada método pretende fazer, e não como ele o faz, porque isso pode mudar com o tempo.  
> Essa frase vem do livro Design Patterns, de Eric Gamma et al., que é cultuado no meio da orientação a objetos.  

### Ex 3
#### Explique como composição pode ser usada como uma alternativa à herança  
Herança é uma forma de extender atributos e métodos de uma determinada classe para outra, criando uma relação de mãe e filha entre as classes (também chamado de superclasse e subclasse). Assim quando criar um objeto da classe filha, todos os atributos da classe mãe será replicada. É muito usada para criar especificações de classes, objetos que, essencialmente, terão os mesmos atributos que outros, mas que precisam de alguns atributos a mais para completar sua função. A herança também funciona com os métodos, que podem ser usados pela classe filha, além de também ser possível declarar um novo método com o mesmo nome caso essa função deva ter uma execução diferente para a classe filha. É, basicamente, uma técnica de reutilização de código.  
Composição ((https://www.geeksforgeeks.org/composition-in-java/#:~:text=The%20composition%20is%20a%20design,that%20refers%20to%20other%20objects.)[Composition]) é uma forma de criar múltiplas "heranças" entre classes. Não é uma herança, é um relacionamento entre classes ((https://www.geeksforgeeks.org/what-is-has-a-relation-in-java/)[Has-A-Relation]), é criada uma variável que instancia que se referencia à outro objeto.  
A composição pode ser usada como uma alternativa à herança quando uma classe precisa ser uma extensão de duas ou mais classes, além de dar a opção de mudar os objetos membros em run time, para alterar dinamicamente o comportamento do programa.  

### Ex 4
#### Suponha que você esteja trabalhando na implementação de uma certa classe, e você precise disponibilizar a informação de quantas instâncias desta classe foram criadas desde o momento em que o programa iniciou sua execução, até o instante atual. Qual seria uma boa forma de implementar tal funcionalidade?  
Usando um construtor de classe. Com o um construtor nós vamos criar uma "rotina" de inicialização da classe que estamos monitorando, podemos criar um atributo contadore colocar nessa rotina de inicialização um incremento nesse atributo contador.  
Esse atributo contador pode ser um do tipo *static*, assim ele não será um atributo de cada objeto criado a partir da classe, mas um atributo da própria classe. Para recuperar esse atributo, podemos criar um `getter` que pega esse valor, ao invés de usar `this.contador` ele usa o próprio nome da classe para recuperar esse valor.  

    class Conta {
        private static int totalDeContas;
        //...
        Conta() {
            Conta.totalDeContas = Conta.totalDeContas + 1;
        }
        public int getTotalDeContas() {
            return Conta.totalDeContas; //nome da variável para recuperar o atributo *static*
        }
    }

    Conta c = new Conta();
    int total = c.getTotalDeContas();

### Ex 5
#### Você está trabalhando com um projeto Java que possui os seguintes pacotes: **projeto** (do qual faz parte o programa principal Ex5.java), **projeto.mat** (ao qual pertencem as classes *Circulo*, *Triangulo* e *Retangulo*) e **projeto.graficos** (ao qual pertencem as classes *Poligono*, *Reta*, *Circulo*). Por que o código Ex5.java (o código fonte para esta e outras questões encontram-se a partir da página 5 deste documento) não compila? Como fazer para corrigi-lo?  
Código Ex5.java:  
    package projeto;
    import projeto.mat.*;
    import projeto.graficos.*;
    public class Ex5 {
        public static void main(String [] args){
            Triangulo triangulo = new Triangulo();
            Retangulo retangulo = new Retangulo();
            Circulo circulo = new Circulo();
            Poligono poligono = new Poligono();
            Reta reta = new Reta();
        }
    }
Devido à ambiguidade em relação ao mesmo nome de classe em pacotes diferentes, a compilação é barrada, visto que o compilador não tem a instrução de qual classe `Círculo` utilizar. Para corrigir, é necessário especificar a classe `Círculo` que deseja ser utilizada. Um dos meios para isso é especificar no `import`, ao invés de importar todas as classes do pacote com `.*`.
### Ex 6
#### Descreva as diversas maneiras de se utilizar, dentro do seu código, uma classe que pertence a um pacote diferente do pacote atual (isto é, aquele ao qual pertence a classe “usuária”). Escreva um trecho de código para ilustrar cada maneira.  
Uma maneira é especificar antes da chamada da classe em qual pacote está a classe que gostaríamos de usar. Com o código do exercício anterior, por exemplo  
    package projeto;
    import projeto.mat.*;
    import projeto.graficos.*;
    public class Ex5 {
        public static void main(String [] args){
            Triangulo triangulo = new Triangulo();
            Retangulo retangulo = new Retangulo();
            Circulo circulo = new projeto.mat.Circulo(); //ou new projeto.graficos.Circulo()
            Poligono poligono = new Poligono();
            Reta reta = new Reta();
        }
    }


### Ex 7
#### Quais as saídas geradas pelo programa Ex7.java, para os seguintes pares de números digitados como entrada pelo usuário: “20 16”, “8 8”, “23 9.5” “10 20”?  
Código Ex7.java  
    import java.util.*;
    public class Ex7 {
        public static void metodo(){
            try {
                int a, b, c;
                Scanner scanner = new Scanner(System.in);
                System.out.print("Entre com dois numeros: ");
                a = scanner.nextInt();
                b = scanner.nextInt();
                if(a - b < 0) return;
                c = a / (a - b);
                System.out.println("Resultado = " + c);
            } catch(ArithmeticException e) {
                System.out.println("Divisao por zero!");
            } finally {
                System.out.println("Finally.");
            }
        }

        public static void main(String [] args){
            System.out.println("Ex8: inicio.");
            metodo();
            System.out.println("Ex8: fim.");
        }
    }

Com `20 16` a saída é `5` e `Finally.` 
Com `8 8` a saída é `Divisão por zero!` e `Finally.` 
Com `23 9.5` a saída é apenas `Finally.`, junto com uma `InputMismatchException`, gerada no `try` e que não foi tratada com `catch` 
Com `10 20` a saída também é apenas `Finally.`, mas sem um erro, ela sai do `try` sem nenhuma exceção 

### Ex 8
#### Qual a utilidade de um bloco `finally`?  
O bloco `finally` é uma terceira cláusula dos blocos `try`e `catch`. Ele vai indicar o que deve ser feito após o término ou do bloco `try` ou de um bloco `catch` qualquer.  
É um recurso interessante para rodar um bloco de código sempre, independente do que acontecer nos blocos `try` e `catch` anteriores, mesmo surgindo uma exceção que não é tratada o bloco `finally`vai rodar.

### Ex 9
#### Para que servem as instruções `throw` e `throws` relacionadas ao mecanismo para tratamento de exceções presente na linguagem Java?  
A palavra `throw` lança uma `Exception`, já a palavra `throws` indica a possibilidade de um método lançar uma `Exception`. O `throws` obriga que o tratamento da exceção seja feito fora do método que lança a exceção.

### Ex 10
#### Que característica uma classe deve ter para que suas instâncias possam ser lançadas?  


### Ex 11
#### Quais as diferenças que existem entre as exceções verificadas e não verificadas?
As exceções verificadas são as que o compilador obriga quem chama o método ou construtor a tratar a exceção.  
As não verificadas o compilador não força quem chamou o método/construtor a tratar a `Exception`.
