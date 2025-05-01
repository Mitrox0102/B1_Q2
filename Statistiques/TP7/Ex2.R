data=read.table("Scout.txt",header=T)
attach(data)

#1
boxplot(Temps~Age)
#on voit que le temps dehors augmente avec la catégorie d'age

#2
#le para de position utilisé est la médiane
#le parametre de dispersion est EIQ
#le para de dissymétrie est Yule Kendall

#on crée des vecteurs en fonction de la cat d'age
temps_age1=Temps[Age==1]
temps_age2=Temps[Age==2]
temps_age3=Temps[Age==3]

#mediane
median(temps_age1)

#eiq
quantile(temps_age1,0.75)-quantile(temps_age1,0.25)

#Yule Kendall (Q3 + Q1-2*mediane)/(Q3-Q1)
(quantile(temps_age1,0.75)+quantile(temps_age1,0.25)-2*median(temps_age1))/(quantile(temps_age1, 0.75)-quantile(temps_age1,0.25))

#la dispersion est plus ou moins la meme pour tous les groupes
#la mediane augmente en fonction du groupe
#dissymetrie à droite pour age 1, a gauche pour age 2 et 
#symetrie pour age 3

#3
#cf dans le cours

#4
#oui le temps passé dehors depend de l'age, on voit par exemple
#dans les boxplot que la mediane, augment en fonction de l'age
#meme constat dans le point 2
#dans le point 3, on voit que la plus grande partie de la variance
#est explique par la variance entre les groupes
#ca veut dire que c'est le fait d'appartenir a des groupes differents
#qui fait varier le plus (donc influence du groupe d'age)
#les deux variables sont donc dependantes