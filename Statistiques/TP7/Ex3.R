data=read.table("Scout.txt",header=T)
attach(data)

#1
#on fait une table de contingence
addmargins(table(Age,Sexe))

#dans  les distributions marginales, on doit mettre les colonnes des
#effectifs et des frequences car variable qualitative

#2
#on a des variables qualitative, on fait donc un barplot ou
#un graphique en sections

barplot(c(0.37,0.27,0.34))
barplot(c(1/3,1/3,1/3))
#attention que pour comparer les garcons et les filles
#etant donne qu'o n'a pas le meme nombre d'individus, il faut faire
#un barplot avec des frequances et pas les effectifs

#3

#On voit que dans le graphique des garcons les barres different
#legerement de taille
#cependant, la difference est minime et peut etre du au faible
#nombre d'individus.
#on n'a pas assez d'elements pour conclure à un lien entre les deux