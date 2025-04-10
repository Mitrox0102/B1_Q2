# Donnees ----

cars

x1<-cars$speed
y1<-cars$speed

set.seed(189)
x2<-sample(rep(c(1,2,3,4), c(5,10,8,6)))
y2<-sample(rep(c(10,11,12), c(11,13,5)))

# Tableau de contigence ----

tableau<-table(x2,y2)
tableau
tableau<-addmargins(tableau)
tableau

# Covariance et corrélation ----

cov(x1,y1)
cor(x1,y1)

# Nuage de points ----

plot(x1,y1)
identify(x1,y1)