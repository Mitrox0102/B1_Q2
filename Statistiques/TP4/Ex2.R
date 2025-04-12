##Liste 4

data=read.table("car-data.txt",header=T)
attach(data)

puissance4=Horsepower[Doors=="four"]
puissance2=Horsepower[Doors=="two"]

##Ex2
##1

h=hist(puissance4,freq=F,breaks=c(50,65,80,95,110,125,145,165,185),
     main="Historgamme unitaire puissance voitures 4 portes", 
     ylab="Fréquances ajustées", xlab="Puissance")
#on va ajouter le polygone des fréquances
#on va calculer les x et les y des points qu'on veut ajouter au graphique
?hist
h$density #nous donne la hauteur des colonnes
plot(h) #dessine l'histo
x1=seq(47.5,187.5,5)
y1=c(0,rep(h$density,c(3,3,3,3,3,4,4,4)),0)
lines(x1,y1,col="red",type="o",lwd=2)

##2
#on dessine la courbe cumulative
plot(ecdf(puissance4))

#on calcule les x et les y des points necessaires pour dessiner l'ogive
x2=c(50,65,80,95,110,125,145,165,185)
y2=c(0,0.06,0.29,0.55,0.69,0.84,0.87,0.96,1)

#on dessine l'ogive
lines(x2,y2,col="red",type="o",lwd=2)