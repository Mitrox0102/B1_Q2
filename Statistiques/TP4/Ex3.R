##Ex3
##1
boxplot(Horsepower~Doors,names=c("4 portes","2 portes"))
#Le q1 et la médiane sont presque égaux
#pour les voitures à deux portes le troisième quartile est plus grand
#étalement à droite un peu plus grand pour les voitures à deux portes

##2
#on peut faire le polygone pour les voitures à deux portes et
#à quatre portes sur le même graphique

#on dessine le plygone pour les voiture à 4 portes

plot(x1,y1,col="red",type="o")

#on va ajouter celui des voitures à deux portes
#on calcule les x et y des points à ajouter sur ke graphique

h2=hist(puissance2,freq=F)

h2$density
h2$breaks
h2$counts

#Toutes les colonnes ont la même longueur, donc on doit juste
#mettre un point au centre de chaque colonne
x3=seq(30,290,20)
x3
y3=c(0,h2$density,0)

#On trace le polygone de puissance 2
lines(x3,y3,col="blue",type="o")
#attention il sort du graphique de base

legend("topright",legend=c("4 portes","2 portes"),col=c("red","blue"),lty=1)

##on peut aussi faire les deux ogives sur le meme graphique
plot(x2,y2,col="red",type="o")

#on veut ajouter l'ogive des voitures à deux portes
#on doit calculer le x et le y des points à ajouter

x4=h2$breaks

#on calcule les ordonnées
#on calcule les fréquences des classes
freq2=h2$counts/sum(h2$counts)

#on calcule les freq cumulees
cumsum(freq2)

y4=c(0,cumsum(freq2)) #le premier à toujours une fréquance 0

lines(x4,y4,col="blue",type="o")
#attention elle sort du graphique

##3
#calculer les coefficients de fisher

#F=m3/s^3
#pour les voitures 4 portes
m3=mean((puissance4-mean(puissance4))^3)
s=sd(puissance4)*sqrt(111/112) #ecart biaisé (on mult par racine n-1/n)

F4=m3/s^3
F4

#on fait pareil pour les 2 portes
m3=mean((puissance2-mean(puissance2))^3)
s=sd(puissance2)*sqrt(84/85) #ecart biaisé (on mult par racine n-1/n)

F2=m3/s^3
F2

#ils sont positifs, ce qui signifie une dissymétrie à gauche

#coefficient de yule kendall
#YK=(Q1+Q3-2*Médiane)/(Q3-Q1)=((Q3-Médiane)-(Médiane-Q1))/(Q3-Q1)
#donne une info sur la disposition de la médiane et des quartiles

YK4=(quantile(puissance4,0.25)+quantile(puissance4,0.75)-2*median(puissance4))/(quantile(puissance4,0.75)-quantile(puissance4,0.25))
YK4
YK2=(quantile(puissance2,0.25)+quantile(puissance2,0.75)-2*median(puissance2))/(quantile(puissance2,0.75)-quantile(puissance2,0.25))
YK2

#ils sont tous les deux proches de 0
#ca signifie que la médiane est à meme distance des deux quartiles

##4
#coefficient ed pearson (applatissement) P=m4/s^4
m4=mean((puissance4-mean(puissance4))^4)
s=sd(puissance4)*sqrt(111/112)

P4=m4/s^4
P4
#il faut le comparer à la valeur 3, ici c'est supérieur
#une distribution normale à un coefficeint de pearson = 3
#il y a donc plus de masse dans les queues de la distribution que
#par rapport à une distribution normale