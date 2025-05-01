data=read.table("Scout.txt",header=T)
attach(data)

#1
#on remplace par la moyenne de dist
mean(Dist,na.rm=T) #calcule la moyenne sans les NA
#30.69

#on remplace par la mediane
median(Dist,na.rm=T) #calcule la mediane sans les NA
#31.01

#on pourra remplacer les valeurs manquantes par une de ces valeurs

#2

#regression lineaire de la dist en fonction du temps
reg3=lm(Dist~Temps)
reg3
a3=reg3$coefficients[2] #pente
b3=reg3$coefficients[1] #ordonnee origine

#on dessine les points, et on ajoute la regression
plot(Temps~Dist)
abline(reg3)

#on veut essayer d'estimer les valeurs manquantes à partir de
#la droite de regression

#quelles sont les valeurs manquantes
which(is.na(Dist))

#on aimerai estimer les distances manquantes qui correspondent
#aux observations 17, 26, 40
#pour ce faire, on utilise les temps correspondant et la
#droite de regression (a3*x+b3)
a3*Temps[c(17,26,40)]+b3
#les valeurs des distances estimées sont donc
# 21.44673 (pour l'observation 17), 46.74176 (pour la 26)
# 30.69602 (pour la 40)

#3
#la deuxieme est meiux car elle tient compte de la relation lineaire
#entre distance et temps, tandis que la premiere remplace simplement
#toutes les valeurs manquantes par la meme valeur

#4
#a
#on separe distance selon la categorie d'age
dist_age1=Dist[Age==1]
dist_age2=Dist[Age==2]
dist_age3=Dist[Age==3]

#pour la premiere technique, on calcule la moyenne des differents
#groupes
mean(dist_age1,na.rm=T)
#idem pour les autres groupes
median(dist_age1,na.rm=T)

#on remplacera donc les donnees manquantes de distance pour la moyenne
#du groupe 1, si la distance qui manque fait partie du groupe 1
#(et pareil pour les autres groupes)

#on doit donc regarder à quel groupe appartient les distances
#manquantes
Age[17] #groupe 1, on remplacera donc la moy du groupe 1
Age[26] #groupe 3, idem avec 3
Age[40] #groupe 2, idem avec 2

#b
#on doit faire une regression lin pour chaque groupe
reg_gr1=lm(dist_age1~temps_age1)
reg_gr2=lm(dist_age2~temps_age2)
reg_gr3=lm(dist_age3~temps_age3)

#on fait le graphique avec les couleurs
summary(Temps)
summary(Dist)
plot(temps_age1,dist_age1, col="red", xlim=c(3,10.5), ylim=c(4,52))
points(temps_age2, dist_age2,col="blue")
points(temps_age3, dist_age3,col="green")

abline(reg_gr1,col="red")
abline(reg_gr2,col="blue")
abline(reg_gr3,col="green")

#les données manquantes à inserer sont à calcuer avec les
#differentes regression lineaire
#pour la 17, on utilise la premiere
#pour le 26, la troisieme et pour la 40 la deuxieme

#en estimant les valeurs, on voit que le fait de separer en trois groupes
#ne change pas les valeurs lorsqu'on les estime avec les regressions
#par contre, avec les moyennes, separer en trois groupes est 
#interessant car plus precis