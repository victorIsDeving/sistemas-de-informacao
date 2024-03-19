get_dataset <- function(){
  colunas_desejadas <- c(
    'TP_PRESENCA_CH',
    'IN_TREINEIRO',
    'SG_UF_RESIDENCIA',
    'TP_ESCOLA',
    'Q001',
    'Q002',
    'Q006'
  )
  
  
  dataset <- data.table::fread(input='C:/Users/vmonteiro/Desktop/regressao-logistica/MICRODADOS_ENEM_2019.csv',
                               integer64='character',
                               skip=0,  #Ler do inicio
                               nrow=-1, #Ler todos os registros
                               select = colunas_desejadas,
                               na.strings = "",
                               showProgress = TRUE,
                               encoding = 'UTF-8'
  )
  nrow(dataset)
  
  dataset$IN_TREINEIRO <- factor(dataset$IN_TREINEIRO, levels = c(1,0),  labels=c('Sim','Nao'))
  
  dataset$Regiao <- factor(dataset$SG_UF_RESIDENCIA, 
    levels = c("AC","AL","AP","AM","BA","CE","DF","ES","GO","MA","MT","MS","MG","PA","PB","PR","PE","PI","RJ","RN","RS","RO","RR","SC","SP","SE","TO"),
    labels = c("Norte","Nordeste","Norte","Norte","Nordeste","Nordeste","Centro-Oeste","Sudeste","Centro-Oeste","Nordeste","Centro-Oeste","Centro-Oeste",
      "Sudeste","Norte","Nordeste","Sul","Nordeste","Nordeste","Sudeste","Nordeste","Sul","Norte","Norte","Sul","Sudeste","Nordeste","Centro-Oeste"))
  
  dataset$TP_PRESENCA_CH <- factor(dataset$TP_PRESENCA_CH, levels = c(0,1,2),
                                   labels=c('Faltou à prova',
                                            'Presente na prova',
                                            'Presente na prova'))
  
  dataset$TP_ESCOLA <- factor(dataset$TP_ESCOLA, levels = c(1,2,3,4),
                              labels=c('Nao respondeu',
                                       'Publica',
                                       'Privada',
                                       'Exterior'))
  
  dataset$Q001 <- factor(dataset$Q001, levels = c('A','B','C','D','E','F','G','H'),
                         labels=c('Nunca Completou Ensino Medio',
                                  'Nunca Completou Ensino Medio',
                                  'Nunca Completou Ensino Medio',
                                  'Nunca Completou Ensino Medio',
                                  'Completou o Ensino Medio',
                                  'Completou o Ensino Medio',
                                  'Completou o Ensino Medio','Nao sei'))
  
  dataset$Q002 <- factor(dataset$Q002, levels = c('A','B','C','D','E','F','G','H'),
                        labels=c('Nunca Completou Ensino Medio',
                                 'Nunca Completou Ensino Medio',
                                 'Nunca Completou Ensino Medio',
                                 'Nunca Completou Ensino Medio',
                                 'Completou o Ensino Medio',
                                 'Completou o Ensino Medio',
                                 'Completou o Ensino Medio','Nao sei'))
  
  dataset$Q006 <- factor(dataset$Q006,levels =  c('A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q'),
                         labels=c('Menos de R$ 3.000,00',
                                  'Menos de R$ 3.000,00',
                                  'Menos de R$ 3.000,00',
                                  'Menos de R$ 3.000,00',
                                  'Menos de R$ 3.000,00',
                                  'Menos de R$ 3.000,00',
                                  'Mais de R$ 3.000,00',
                                  'Mais de R$ 3.000,00',
                                  'Mais de R$ 3.000,00',
                                  'Mais de R$ 3.000,00',
                                  'Mais de R$ 3.000,00',
                                  'Mais de R$ 3.000,00',
                                  'Mais de R$ 3.000,00',
                                  'Mais de R$ 3.000,00',
                                  'Mais de R$ 3.000,00',
                                  'Mais de R$ 3.000,00',
                                  'Mais de R$ 3.000,00'))
  
  setnames(dataset, 'TP_PRESENCA_CH', 'PRESENCA_HUMANAS')
  
  setnames(dataset, 'IN_TREINEIRO', 'Treineiro')
  setnames(dataset, 'SG_UF_RESIDENCIA', 'UF_Residencia')
  setnames(dataset, 'TP_ESCOLA', 'Tipo_Escola')
  setnames(dataset, 'Q001', 'Escolaridade_pai')
  setnames(dataset, 'Q002', 'Escolaridade_mae')
  setnames(dataset, 'Q006', 'Renda_familiar')
  
  return(dataset)
}