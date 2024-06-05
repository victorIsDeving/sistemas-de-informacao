# Relat�rio do Treinamento e Teste do Modelo de Rede Neural

## Resumo
Testes s� com parada antecipada
- No `test01` fiz uma mudan�a na forma que funciona a valida��o cruzada, estava parando muito cedo. 
	- A valida��o estava considerando o melhor erro de valida��o, o contador da paci�ncia s� zerava se o erro de valida��o fosse menor que o melhor erro de valida��o obtido anteriormente, acho que restringiu demais e os testes estavam parando antes �poca 150. 
	- Adicionei um print do contador da paci�ncia tamb�m para ter um controle durante a execu��o
- No `test02` mudei a paci�ncia para 5, 15 � muito, ajustei aprendizado, diminui o m�ximo de �pocas para 650 e o threshold
- No `test03` refiz igual ao `test02`, ele parou antecipadamente na �poca 26
- No `test04` diminui as �pocas para 100 pq demora muito o processamento completo, aumentei o n�mero de perceptrons na camada escondida
- No `test05` aumentei as �pocas pq o resultado n�o ficou bom, s� para M e W que acerta algo
- 

## Par�metros fixos
- Com parada antecipada
- Sem valida��o cruzada
- Com valida��o holdout, 80% para treinamento e 20% para teste

## Par�metros vari�veis
- Paci�ncia vari�vel
- Quantidade de perceptrons
- Aprendizado
- Limiar para classifica��o (threshold)