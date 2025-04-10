## Test 6 ##

# Données

cars

x<-cars$speed
y<-cars$dist

# Modèle linéaire

mod<-lm(y~x)
mod

summary(mod)

plot(x,y)
abline(mod, col='red')

# Valeurs ajustées

mod$fitted

# Résidus

mod$residuals

plot(mod$residuals, type='h')
identify(mod$residuals)

plot(x,y)
abline(mod, col='red')
identify(x,y)
