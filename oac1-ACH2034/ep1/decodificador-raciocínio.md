# Objetivo do EP
> Construir um conversor sinal-magnitude para complemento de 2 e aplicá-lo ao somador-subtrator para mostrar e permitir a entrada de valores em notação sinal-magnitude

A ideia é criar um circuito que possa convertar o conversor de dois em sinal-magnitude e vice versa

### Sinal Magnitude - o primeiro dígito indica o sinal
    +0 = 0000  
    +1 = 0001  
    +2 = 0010  
    +3 = 0011  
    +4 = 0100  
    +5 = 0101  
    +6 = 0110  
    +7 = 0111  
    -0 = 1000 (esse é um problema do sinal magnitude)  
    -1 = 1000  
    -2 = 1001  
    -3 = 1010  
    -4 = 1011  
    -5 = 1100  
    -6 = 1101  
    -7 = 1110  
    -8 = 1111  


### Complemento de dois
    negativos  0000 = 0  positivos
    1111 = -1            1 = 0001  
    1110 = -2            2 = 0010  
    1101 = -3            3 = 0011  
    1100 = -4            4 = 0100  
    1011 = -5            5 = 0101  
    1010 = -6            6 = 0110  
    1001 = -7            7 = 0111  
    1000 = -8            x = 1000 (os dois são iguais, não tem uma representação para de +8 para complemento de 2)  


# Uma tabela de equivalência entre SINAL MAGNITUDE e COMPLEMENTO DE DOIS 
    1. 4 entradas (E1, E2, E3 e E4), em SINAL MAGNITUDE (SM), e  
    2. 4 saídas (S1, S2, S3 e S4), em COMPLEMENTO DE DOIS (CD)  
    
        E1 E2 E3 E4 | S1 S2 S3 S4 (o raciocínio pra saída é: do lado esquerdo tenho o +1 em SM, qual o +1 em CD?)  
        0  0  0  0    0  0  0  0  
        0  0  0  1    0  0  0  1  
        0  0  1  0    0  0  1  0  
        0  0  1  1    0  0  1  1  
        0  1  0  0    0  1  0  0  
        0  1  0  1    0  1  0  1  
        0  1  1  0    0  1  1  0  
        0  1  1  1    0  1  1  1 (para os positivos não tem nenhuma alteração, são iguais em SM e CD)  
        1  0  0  0    1  0  0  0 (o -0 do SM vamos mapear para um -)  
        1  0  0  1    1  1  1  1 (notar que eles são opostos, o 1001 em SM vai pro 1111 em CD enquanto o 1111 em SM vai pro 1001 em CD)  
        1  0  1  0    1  1  1  0  
        1  0  1  1    1  1  0  1  
        1  1  0  0    1  1  0  0  
        1  1  0  1    1  0  1  1  
        1  1  1  0    1  0  1  0  
        1  1  1  1    1  0  0  1  

> a tabela é a mesma decodificando tanto SM->CD quanto CD->SM  
> logo, o circuito que converte um para o outro e o outro para um tbm é o mesmo  
> então, podemos colocar esse decodificador no começo para o converter o CD para SM, fazer a operação do somador-subtrator, e depois converter o resultado de SM para CD

Dá para construir o circuito todo através da tabela verdade, indo por `Janela -> AnáliseCombicional` e aí completando as Entradas e Saídas do sistema, como mostra a tabela das linhas 42 até 58