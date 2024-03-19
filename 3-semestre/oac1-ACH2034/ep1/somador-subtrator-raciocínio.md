# Objetivo do circuito
> A ideia é construir um circuito que faça soma de números em sinal-magnitude

### Soma de *bits*
  A + B = S

    A | B || S | Cout1
    0   0    0   0
    1   0    1   0
    0   1    1   0
    1   1    0   1

  > Cout = *carry out*, é meio que o que sobra da soma, o que será carregado para o próximo *bit*

  Notar que o resultado em **S** é um `XOR`, enquando no **Cout** é um `AND`  
  Essa é a estrutura de um ***MEIO SOMADOR***

  O somador completo ocorre quando temos na estrutura um **Cin**, que vai somar com o resultado da soma anterior  

  A + B = Soma Parcial (Sp)
  Sp + Cin = Soma Total (St)

    Cin | Sp || St | Cout2
    0     0     0    0
    0     1     1    0
    0     1     1    0
    0     0     0    0
    1     0     1    0
    1     1     0    1
    1     1     0    1
    1     0     1    0

  Agora tem dois *carry out* sobrando, o **Cout1** da Soma Parcial e o **Cout2** da Soma Total  
  O Cout Final, **Coutf**, é uma porta `OR` de **Cout1** com o **Cout2**