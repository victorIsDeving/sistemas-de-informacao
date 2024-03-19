if (!require(data.table)){install.packages('data.table')} # nolint
if (!require(pacman)) install.packages("pacman")
install.packages("pander")
install.packages("knitr")
library(pander)
library(knitr)
library(pacman)

pacman::p_load(dplyr, psych, car, MASS, DescTools, QuantPsyc, ggplot2)
pacman::p_load(dplyr, ggplot2, car, rstatix, lmtest, ggpubr)

source('C:/sistemas-informacao/mqam-ACH2036/clusters/functions/get_dataset.R') # nolint

df <- get_dataset()

dataset <- df

head(dataset)

dataset <- dataset[dataset$Regiao == 'Sul'] # nolint
dataset <- dataset[dataset$TP_ESCOLA == 'Privada'] # nolint
dataset <- dataset[dataset$IN_TREINEIRO == 0]

dataset$Regiao <- NULL
dataset$IN_TREINEIRO <- NULL
dataset$TP_ESCOLA <- NULL

head(dataset)
describe(dataset)

dataset_padronizado <- scale(dataset)

describe(dataset_padronizado)

dists <- dist(dataset_padronizado, method = 'euclidian') # nolint

par(mfrow=c(1,2)) # nolint

plot(hclust(dists, method = 'single')) # nolint
plot(hclust(dists, method = 'ward.D2')) # nolint

plot(hclust(dists, method = 'complete')) # nolint
plot(hclust(dists, method = 'average')) # nolint

plot(hclust(dists, method = 'mcquitty')) # nolint
plot(hclust(dists, method = 'centroid')) # nolint


cl <- kmeans(dataset_padronizado, 4)

plot(dataset, col = cl$cluster)

points(cl$centers, col = 1:5, pch = 8)

# sort(cl$cluster)

cl <- kmeans(dataset_padronizado, 2)

plot(dataset, col = cl$cluster)

points(cl$centers, col = 1:5, pch = 8)

# sort(cl$cluster)