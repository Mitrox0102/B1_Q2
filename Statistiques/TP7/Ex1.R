data=read.table("Scout.txt",header=T)
attach(data)

#1
#on regarde l'etentdu des obs
summary(Temps)
#elle va de 3.26 a 10.17

#pour savoir le nombre de classe, on utilise la formule de Sturge

1+(10/3)*log10(100)
#on doit prendre 8 classes(car ca vaut 7.66)
#on doit donc diviser l'intervalle [3.26,10.17] en 8 classes
#pour avoir des bornes jolies, on divise l'intervalle [3:10.5]

#comment le diviser en 8 classes ?
hist(Temps)
stem(Temps)

#on a peu de donnéess plsu grandes que 8 et plus petite que 4
#on peut rassembler les données de ]8,10,5[ et [3,5]
#(on rassemble les colonnes avec peu de données)
#pour les colonnes avec bcp de données, on les divise en deux
#c'est-a-dire les colonnes entre 5 et 8
#au final on a donc les classes ayant pour bornes
# 3, 5, 5.5, 6, 6.5, 7, 7.5, 8, 10.5

#2

h=hist(Temps,breaks=c(3, 5, 5.5, 6, 6.5, 7, 7.5, 8, 10.5))
#pour avoir les effectiffs de notre tableau
h$counts #eff
(h$counts)/100 #freq
cumsum(h$counts) #eff cumu
cumsum((h$counts)/100) #freq cum

#la hauteur des colonnes de l'histogramme unitaire est donné
#par hi = fi/ampl
#(on divise la fréquance de la classe par son amplitude)
#pour la premiere classe, l'amplitude est de 2 et la fréqu est
#de 0.23
#la hauteur de la classe sera donc 0.23/2=0.115

#3
#on ajoute le polygone
#on doit diviser toutes les colonnes en sous colonnes
#dont l'amplitude est le pgcd des amplitudes des colonnes
#les amplitudes sont 2,0.5 et 1.5, le pgcd est donc 0.5
#on doit donc diviser nos colonnes en sous col d'amplitudes de 0.5

#on calcule le x et le y des points qu'on veut ajouter
x=seq(2.75,10.75,0.5)
y=c(0,rep(h$density,c(4,1,1,1,1,1,1,5)),0)
#on trace le polygone
lines(x,y,col="red",type='o')

#c'est plus ou moins symétriqu,et c'est bimodal (2pics)
#la forme est plus ou moins en cloche

#4
mean(Temps) #6.112
median(Temps) #6.01

#pour calculer la médiane sur les donnees groupees on utilise
#l'ogive des fréquence cumulées et puis une approximation linéaire

#dans notre cas, la fréquance cumulée 0.5 correspond exactement à
#la donnee 6 dans notre tableau, donc on n'a pas besoin de le faire

#la médiane estimée sur les données groupées est 6
#la moyenne estimée est estimée à partir des centres des classes
#elle vaut 6.0375

#les valeurs exactes et les valeurs estimées sont très proches
#cela signifie que les données sont réparties uniformément dans
#les classes 

#5
#on doit d'abord calculer les quartiles
summary(Temps)
#Q1=5.082, mediane=6.010, Q3=7.082
#on dtoi calculer les valeurs pivots et les valeurs adjacentes
#valeur pivots
#a1=Q1-1.5*EIQ et a2=Q3+1.5*EIQ
eiq=7.082-5.082
a1=5.082-1.5*eiq # 2.082
a2=7.082+1.5*eiq # 10..082

#valeurs adjacentes
#x_d est la plus petite valeur qui soit plus grande que a1
#x_g est la plus grande valeur qui soit plus petite que a2

min(Temps[Temps>2.082])
max(Temps[Temps<10.082])

#la moustache de gauche va aller jusqu'à 3.26 et celle de droite
#jsuqu'à 9.24

#les valeurs extremes sont celles qui sont en dehors des moustacehs
#ici, il n'y en a pas plus petite que 3.26
#il y en a une plus grande que 9.24, qui vaut 10.17
#on devra donc rajouter un point en 10.17 en plus de la moustache

boxplot(Temps)
#la ligne du milieu de la boite est la médiane et les deux autres
#sont le premier et le troisieme
