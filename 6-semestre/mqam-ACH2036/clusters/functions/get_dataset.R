contar_correspondencias <- function(row, col1, col2) {
  string1 <- as.character(row[col1])
  string2 <- as.character(row[col2])
  return(sum(strsplit(string1, "")[[1]] == strsplit(string2, "")[[1]]))
}

get_dataset <- function() { # nolint
  colunas_desejadas <- c ( # nolint
    'SG_UF_RESIDENCIA', # nolint
    'NU_IDADE', # nolint
    'IN_TREINEIRO', # nolint
    'TP_ESCOLA', # nolint
    'NU_NOTA_CN', # nolint
    'NU_NOTA_CH', # nolint
    'NU_NOTA_LC', # nolint
    'NU_NOTA_MT', # nolint
    'NU_NOTA_REDACAO' # nolint
  )

  dataset <- data.table::fread(input='C:/sistemas-informacao/mqam-ACH2036/regressão-logística/regressao-logistica/MICRODADOS_ENEM_2019.csv',  # nolint
    integer64='character',  # nolint
    skip = 0,  #Ler do inicio
    nrow = -1, #Ler todos os registros
    select = colunas_desejadas,
    na.strings = "",
    showProgress = TRUE,
    encoding = 'UTF-8'  # nolint
  )
  nrow(dataset)

  dataset$Regiao <- factor(dataset$SG_UF_RESIDENCIA,
  levels = c("AC","AL","AP","AM","BA","CE","DF","ES","GO","MA", # nolint
            "MT","MS","MG","PA","PB","PR","PE","PI","RJ","RN", # nolint
            "RS","RO","RR","SC","SP","SE","TO"), # nolint
  labels = c("Norte","Nordeste","Norte","Norte","Nordeste", # nolint
            "Nordeste","Centro-Oeste","Sudeste","Centro-Oeste", # nolint
            "Nordeste","Centro-Oeste","Centro-Oeste","Sudeste", # nolint
            "Norte","Nordeste","Sul","Nordeste","Nordeste", # nolint
            "Sudeste","Nordeste","Sul","Norte","Norte","Sul", # nolint
            "Sudeste","Nordeste","Centro-Oeste")) # nolint

  dataset$TP_ESCOLA <- factor(dataset$TP_ESCOLA, levels = c(1, 2, 3, 4),
  labels = c('Nao respondeu','Publica','Privada','Exterior')) # nolint

  dataset <- na.omit(dataset)

  dataset$SG_UF_RESIDENCIA <- NULL
  setnames(dataset, 'NU_NOTA_CH', 'Nota Humanas') # nolint
  setnames(dataset, 'NU_NOTA_CN', 'Nota Natureza') # nolint
  setnames(dataset, 'NU_NOTA_LC', 'Nota Linguagem') # nolint
  setnames(dataset, 'NU_NOTA_MT', 'Nota Matematica') # nolint
  setnames(dataset, 'NU_IDADE', 'Idade') # nolint
  setnames(dataset, 'NU_NOTA_REDACAO', 'Nota Redacao') # nolint

  return(dataset)
}