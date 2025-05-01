data=read.table("Scout.txt",header=T)
attach(data)

#1
#on commence par creer le vecteur avec "peu", "moyen" et "beaucoup"
temps2=ifelse(Temps<5,"peu",ifelse(Temps<7,"Moyen","Beaucoup"))
#Tableau de contingence
table(Age,temps2)

#2
#coefficient de correlation entre les variables
#puisque on a des classes, on doit utiliser le centre des classes

#3
#en regardant kes moyennes du temps en fonction de l'age, on
#voit que le temps passé dehors augmente en fonction de l'age

#c'est cohérent avec le fait que la correlation vaut 0.72
#ce qui signifie un lien lineaire positif entre les données
#(ca veut dire une augment, lorque l'autre augmente)

#les variables sont dependant et augmente en meme temps.