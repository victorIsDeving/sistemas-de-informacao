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
