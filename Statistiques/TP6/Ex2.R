data=read.table("Regression.txt", header=T)
attach(data)

#Exercice 2
#1

#donnee manquante
summary(data)

#dans la variable prix median, on a 5 NA
#NA = not available

#commune ayant les donnees manquantes
Commune[is.na(Prix_median)]

#On n'a pas le prix median pour les communes
#"Ambleve" "Fauvillers" "Daverdisse" "Herbeumont" "MeixdevantVirton"

#2

?cor
cor(Prix_median,Revenu_median,use="complete.obs")

#attention on doit enlever les NA
#On a une correlation positive, relation linéaire et croissant

#3
#Droite de régression
#lm = linear model
#Prix_median~Revenu_median  ~ = en fonction de ..

reg1=lm(Prix_median~Revenu_median)
b1=reg1$coefficients[1] #ordonnee à l'origine
a1=reg1$coefficients[2] #pente

#dessin des points + droites
plot(Revenu_median, Prix_median)
abline(reg1,col="red") #rajoute la droite de reg

#la droite passe bien dans le nuage de points
#le nuage de point est croissant et la droite aussi

#4
#on veut le coeff de détermination
summary(reg1)

#La valeur qui nous interesse est le multiple R-squared
#donc 0.4765
#Il y a donc 47.5% de la variance du prix_median qui est expliqué par la regression
#lineaire

#5
#on utilise l'équ de la reg qui est a1*x+b1
#le x est le revenu median des gens de la commune

#pour la communed'Ambleve
a1*Revenu_median[Commune=="Ambleve"]+b1
#la valeur du prix median estimé par la reg est 20552.7

#pour la commune de Fauvillers
a1*Revenu_median[Commune=="Fauvillers"]+b1
#la valeur du prix median estimé par la reg est 270327.7


#6
#on va identifier les points bizarres
#on ouvre une fenetre à part

#windows() #windows
#quartz() #mac
#dev.new() #linux

plot(Revenu_median, Prix_median)
#on identifie les points

#identify(Revenu_median,Prix_median)

#les donnees identifiées sont la 22 et la 182
Commune[22] #Lasnes
Commune[182] #Attert

#7
#on refait la regression sans la 22ème observation
reg2=lm(Prix_median[-22]~Revenu_median[-22])
a2=reg2$coefficients[2] #pente
b2=reg2$coefficients[1] #ordonnee origine

#on trace la deuxieme regression
abline(reg2,col="blue")
#ajoute la legende
#la deuxieme regression à une pente plus petite que la premiere
#la droite rouge est "attirée" par le point 22, ce qui fait
#augmenter sa pente. Sans le point 22, la pente diminue.
#les regressions par les moindres carrés sont influencées par
#les données externes

#8
#comparer des residus du point 182 pour les deux regressions
# 182 est la commun de attert
reg1$residuals[182] #donne theoriquement le residu de l'observation

#sauf qu'ici, il y a des données manquantes (donc supprimees)
#les indices des donnees sont décalés

#il est plus facile de le faire à la main
#residu=vraie valeur-valeur approximée (par a1*x+b1)
#pour la premiere regression
Prix_median[Commune=="Attert"]-(a1*Revenu_median[Commune=="Attert"]+b1)
#le residu vaut -88882.21 

#pour la deuxieme regression
Prix_median[Commune=="Attert"]-(a2*Revenu_median[Commune=="Attert"]+b2)
#le residu vaut -79289.22

#les residus sont grands : ce qui est attendu puisque le point
#est loin des droites de regressions
#les residus sont négatifs : ce qui est attendu, car les droites
#surestiment la valeur du prix median pour ce point (car elle est au
#dessus du point)

#9
summary(reg2)
# les coefficients de det est Multiple R-squared:  0.529
#Il y a donc 52% de la variabilité expliquée par la deuxieme reg
#lineaire, ce qui est plus que pour la premiere (il valait 47,6%)
#donc la ceuxieme regression est plus representative
