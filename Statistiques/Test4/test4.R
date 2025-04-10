## test 4 ##

# données

data<-iris

#variable continue
x<-iris$Petal.Length

#variable nominale
type<-iris$Species

#Dispersion

n=150

#Variance  !!Dénominateur
var(x)
var(x)*(n-1)/n

#Ecart-type !!Dénominateur
sd(x)
sqrt(var(x)*(n-1)/n)

#etendue
max(x)-min(x)

#ecart-interqartile
quantile(x)
quantile(x,0.75)-quantile(x,0.25)
IQR(x)

#Sélectionner des groupes

Setosa<-x[type=='setosa']
Versicolor<-x[type=='versicolor']
Virginica<-x[type=='virginica']

mean(Setosa)
mean(Versicolor)
mean(Virginica)

var(Setosa)*49/50
var(Versicolor)*49/50
var(Virginica)*49/50

#Boites à moustaches

boxplot(x)

boxplot(Setosa, Versicolor, Virginica)

boxplot(x~type)