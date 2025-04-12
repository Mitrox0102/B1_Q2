##Ex3

data=read.table("Menages.txt",header=T)
attach(data)
data

##1
tableau=table(enfants,pieces)
tableau
#on ajoute les distributions marginales
addmargins(tableau)

##2
#pour le faire on calcule les moyennes des variables séparément
mean(pieces)
mean(enfants)

#idem pour la variance
var(pieces)*(534/535)
var(enfants)*(534/535)

##3
#on veut calculer le mode de chaque variable
table(enfants) #le mode est 2 avec un effectif de 213
table(pieces) #le mode est 4 avec un effectif de 178

##4
cov(enfants,pieces)

##5
cor(enfants,pieces)

##6
enfant4=enfants[pieces==4]
#donner la distribution
table(enfant4)

#calculer la moyenne
mean(enfant4)
n=sum(table(enfant4)) #nombre total de menages avec 4 pieces
var(enfant4)*((n-1)/n)