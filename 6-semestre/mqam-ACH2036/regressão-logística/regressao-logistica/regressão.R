if(!require(data.table)){install.packages('data.table')}
if(!require(pacman)) install.packages("pacman")
install.packages("pander")
install.packages("knitr")
library(pander)
library(knitr)
library(pacman)

pacman::p_load(dplyr, psych, car, MASS, DescTools, QuantPsyc, ggplot2)
pacman::p_load(dplyr, ggplot2, car, rstatix, lmtest, ggpubr)

source('C:/Users/vmonteiro/Desktop/regressao-logistica/functions/regressao_logistica.R')
source('C:/Users/vmonteiro/Desktop/regressao-logistica/functions/get_dataset.R')

dataset <- get_dataset()

head(dataset)

regressao_logistica('PRESENCA_HUMANAS', c('Treineiro'), dataset)
dataset$Regiao <- relevel(dataset$Regiao, ref = 'Sudeste')
regressao_logistica('PRESENCA_HUMANAS', c('Regiao'), dataset)
dataset$Tipo_Escola <- relevel(dataset$Tipo_Escola, ref = 'Publica')
regressao_logistica('PRESENCA_HUMANAS', c('Tipo_Escola'), dataset)
regressao_logistica('PRESENCA_HUMANAS', c('Escolaridade_pai'), dataset)
regressao_logistica('PRESENCA_HUMANAS', c('Escolaridade_mae'), dataset)
regressao_logistica('PRESENCA_HUMANAS', c('Renda_familiar'), dataset)

regressao_logistica('PRESENCA_HUMANAS', c('Treineiro', 'Regiao', 'Tipo_Escola', 'Escolaridade_pai', 'Escolaridade_mae', 'Renda_familiar'), dataset)
