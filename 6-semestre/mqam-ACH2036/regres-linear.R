install.packages(c("pacman", 'pillar', 'psych'))
library(psych)
library(purrr)
pacman::p_load(dplyr, ggplot2, car, rstatix, lmtest, ggpubr)

url <- "https://drive.google.com/uc?export=download&id=18vg4LHNRISHvMBPRcJqIZ1dBWM8xBI07"
nome_arquivo <- "dataset.csv"
download.file(url, destfile = nome_arquivo, method = "auto")
dataset_zerado <- read.csv(nome_arquivo)

dados_usados <- c('subscribers',
                  'created_year',
                  'video_views_for_the_last_30_days', 
                  'video.views',
                  'uploads',
                  'category',
                  'subscribers_for_last_30_days'
                  )
variavel_dependente <- 'subscribers_for_last_30_days'
variaveis_independentes <- setdiff(dados_usados, variavel_dependente)

reseta_dataset <- function(dataset, dados_usados){
  dataset <- subset(dataset_zerado, select = dados_usados)
  #View(dataset)
  dataset_tratado <- subset(
    dataset, !apply(dataset, 1, function(row) any(row == 0 | is.nan(row))))

  #View(dataset_tratado)

  #dataset_tratado$crescimento <- 
    #dataset_tratado$subscribers_for_last_30_days / dataset_tratado$subscribers
  return(dataset_tratado)
}

dataset_tratado <- reseta_dataset(dataset_zerado, dados_usados)

lmSimples <- function(dataset, variavel_dependente, variavel_independente) {
  formula <- as.formula(paste(variavel_dependente, "~", variavel_independente))
  mod <- lm(formula, data = dataset)
  
  residuos_padronizados <- rstandard(mod)
  
  limite_z_score <- 2
  
  indices_outliers <- which(abs(residuos_padronizados) > limite_z_score)
  dataset_sem_outliers <- dataset[-indices_outliers, ]
  
  mod <- lm(formula, data = dataset_sem_outliers)
  titulo <- paste("Graficos do modelo linear de ", variavel_dependente, "em função de", variavel_independente)
  par(mfrow=c(2,2))
  plot(mod, main = titulo)
  
  
  dev.print(
    png, 
    file = paste(titulo, ".png"), 
    width = 800, 
    height = 600
  )
  
  par(mfrow=c(1,1))
  normalidade <- shapiro.test(mod$residuals)
  print(normalidade)
  return(dataset_sem_outliers)
}


for(variavel_independente in variaveis_independentes) {
  dataset_tratado <- lmSimples(dataset_tratado, variavel_dependente, variavel_independente)
}

formula <- as.formula(paste(variavel_dependente, "~", reduce(variaveis_independentes, paste, sep = " + ")))

mod_original <- lm(formula, data = dataset_tratado)
par(mfrow=c(2,2))
plot(mod_original, main = "Graficos do modelo completo")

residuos_padronizados <- rstandard(mod_original)
limite_z_score <- 2
indices_outliers <- which(abs(residuos_padronizados) > limite_z_score)
dataset_sem_outliers <- dataset_tratado[-indices_outliers, ]

mod_sem_outliers <- lm(formula, data = dataset_sem_outliers)

par(mfrow=c(2,2))
plot(mod_sem_outliers, main = "Graficos do modelo sem outliers")

shapiro.test(mod$residuals)
bptest(mod_sem_outliers)
vif(mod_sem_outliers)
pairs.panels(dataset_sem_outliers)
print(mod_sem_outliers)
summary(mod_sem_outliers)


AIC(mod_original, mod_sem_outliers)

dados_retirados = c('category', 'video.views', "uploads", "subscribers")
dados_novos <- setdiff(dados_usados, dados_retirados)
dataset_dados_retirados <- dataset_sem_outliers[, dados_novos]
pairs.panels(dataset_dados_retirados)
formula_nova <- as.formula(paste(variavel_dependente, "~", reduce(dados_novos, paste, sep = " + ")))
print(formula_nova)
mod_sem_var <- lm(formula_nova, data = dataset_sem_outliers)
print(mod_sem_var)
AIC(mod_sem_outliers, mod_sem_var)

