# Pacotes para analises e graficos
install.packages("dgof")
install.packages("car")
library(dgof)
library(car)

# Upload da database e resumo
database <- read.csv('./database.csv')
summary(database)

# Variavel independente
paises <- unique(database$Country)
print(paises)
sorted <- sort(table(database$Country),decreasing=T)
print(sorted)

# Grupos de paises para a ANOVA e resumo da variavel dependente escolhida, a escritos nos ultimos 30 dias
paises_interesse <- c('Brazil', 'United Kingdom', 'India', "United States", "Mexico") # top 5
# paises_interesse <- c("United States", "United Kingdom", "Canada", "India") # top 4 anglofonos
# paises_interesse <- c("India", "Indonesia", "Thailand", "South Korea", "Philippines") # top 5 asiaticos
# paises_interesse <- c("United Kingdom", "Spain", "Russia", "Ukraine", "Germany") # top 5 europeus
for(pais in paises_interesse){
  dados_filtrados <- subset(database, Country == pais)
  dados_filtrados <- na.omit(dados_filtrados)
  media <- mean(dados_filtrados$subscribers_for_last_30_days)
  cat(pais, "\n")
  cat("Media:  ", media, "\n")

  mediana <- median(dados_filtrados$subscribers_for_last_30_days)
  cat("Mediana:  ", mediana, "\n")

  variancia <- var(dados_filtrados$subscribers_for_last_30_days)
  cat("Variância:  ", variancia, "\n\n")
}

# Teste de normalidade para cada grupo da analise
for(pais in paises_interesse){
  dados_filtrados <- subset(database, Country == pais)
  dados_filtrados <- na.omit(dados_filtrados)
  print(paste("teste de normalização do ano de criação dos canais do pais", pais))
  media <- mean(dados_filtrados$subscribers_for_last_30_days)
  desvioPadrao <- sd(dados_filtrados$subscribers_for_last_30_days)
  cat("Media da distribuição -", media, "\n")
  cat("Desvio Padrão da distribuição -", desvioPadrao, "\n")
  shapiroTest <- shapiro.test(dados_filtrados$subscribers_for_last_30_days)
  ksTest <- ks.test(dados_filtrados$subscribers_for_last_30_days, pnorm, media, desvioPadrao)
  print(shapiroTest)
  print(ksTest)
}

# Teste de homoscedasticidade
subs_last_30_d<-c()
paises<-c()
for(pais in paises_interesse){
  dados_filtrados <- subset(database, Country == pais)
  dados_filtrados <- na.omit(dados_filtrados)
  subs_last_30_d <- c(subs_last_30_d, dados_filtrados$subscribers_for_last_30_days)
  paises <- c(paises, rep(pais, length(dados_filtrados$subscribers_for_last_30_days)))
}

boxplot(subs_last_30_d ~ paises)
leveneTest(y = subs_last_30_d, group = paises)

# Por fim, modelo da ANOVA para o grupo de paises escolhido
modelo_anova <- aov(subs_last_30_d ~ paises)
resultado_anova <- summary(modelo_anova)

print(resultado_anova)