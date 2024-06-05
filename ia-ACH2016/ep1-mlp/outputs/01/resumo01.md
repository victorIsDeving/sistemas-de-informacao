# Relatório do Treinamento e Teste do Modelo de Rede Neural

## Resumo
Testes só com parada antecipada
- No `test01` fiz uma mudança na forma que funciona a validação cruzada, estava parando muito cedo. 
	- A validação estava considerando o melhor erro de validação, o contador da paciência só zerava se o erro de validação fosse menor que o melhor erro de validação obtido anteriormente, acho que restringiu demais e os testes estavam parando antes época 150. 
	- Adicionei um print do contador da paciência também para ter um controle durante a execução
- No `test02` mudei a paciência para 5, 15 é muito, ajustei aprendizado, diminui o máximo de épocas para 650 e o threshold
- No `test03` refiz igual ao `test02`, ele parou antecipadamente na época 26
- No `test04` diminui as épocas para 100 pq demora muito o processamento completo, aumentei o número de perceptrons na camada escondida
- No `test05` aumentei as épocas pq o resultado não ficou bom, só para M e W que acerta algo
- 

## Parâmetros fixos
- Com parada antecipada
- Sem validação cruzada
- Com validação holdout, 80% para treinamento e 20% para teste

## Parâmetros variáveis
- Paciência variável
- Quantidade de perceptrons
- Aprendizado
- Limiar para classificação (threshold)