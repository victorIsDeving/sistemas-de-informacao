regressao_logistica <- function(variavel_dependente, variaveis_independentes, data){
  formula <- as.formula(paste(variavel_dependente, "~", reduce(variaveis_independentes, paste, sep = " + ")))
  print(formula)
  mod <- glm(formula, family = binomial(link = 'logit'), data = data)
  
  cat('\n--------------------------------\n')
  print('Resumo do modelo')
  cat('\n--------------------------------\n')
  
  print(summary(mod))
  
  cat('\n--------------------------------\n')
  print('Vendo categorias de referencia')
  cat('\n--------------------------------\n')
  
  print(variavel_dependente)
  print(levels(data[[variavel_dependente]]))
  
  for (i in seq_along(variaveis_independentes)) {
    cat('\n')
    print(variaveis_independentes[i])
    print(levels(data[[variaveis_independentes[i]]]))
  }
  
  cat('\n--------------------------------\n')
  print('Resumo dos residuos padronizados')
  cat('\n--------------------------------\n')
  
  print(summary(stdres(mod)))
  
  if(length(variaveis_independentes) > 1){
    cat('\n--------------------------------\n')
    print('Analise de multicolinearidaded')
    print('Se acima de 10 existe multicoliearidade')
    cat('\n--------------------------------\n')
    
    print(vif(mod))
  }
  
  cat('\n--------------------------------\n')
  print('Overall Effects')
  print('Caso o Pr(>Chisq) < 0.05 então aquela variavel é um previsor estatisticamente relevante ')
  cat('\n--------------------------------\n')
  
  print(Anova(mod, type='II', test='Wald'))
  
  cat('\n--------------------------------\n')
  print('Calculo de Odds Ratio')
  print('Usando log-likelihood')
  cat('\n--------------------------------\n')
  
  print(exp(cbind(OR = coef(mod), confint.default(mod))))
  
  cat('\n--------------------------------\n')
  print('Calculo do Pseudo R2')
  print('Usando NagelKerke')
  cat('\n--------------------------------\n')
  
  PseudoR2(mod, which = "Nagelkerke")
  
}