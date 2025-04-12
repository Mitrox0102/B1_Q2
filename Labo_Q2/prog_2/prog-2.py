import math
import pygame
import sys

# Constantes

BLEUCLAIR = (127, 191, 255)
ROUGE = (255, 0, 0)
NOIR = (0, 0, 0)
k = 8.9876 * 10**9

# Paramètres

objets = []
dimensions_fenetre = (1600, 900)  # en pixels
images_par_seconde = 25

# Initialisation

pygame.init()

fenetre = pygame.display.set_mode(dimensions_fenetre)
pygame.display.set_caption("Programme 2")

horloge = pygame.time.Clock()
couleur_fond = BLEUCLAIR

#Fonctions du labo 2

A = 2
B = 5
C = 20

def deplacer_pol(point, distance, orientation):
    x, y = point
    x2,y2 = x + distance*math.cos(orientation),y + distance*math.sin(orientation)
    return (x2, y2)

def dessiner_vecteur(fenetre, couleur, origine, vecteur):
    distance_pp4 = math.sqrt((vecteur[1]**2 + vecteur[0]**2))
    angle = math.atan2(vecteur[1],vecteur[0])
    if distance_pp4 >= C :
        
        p4 = (vecteur[0]+origine[0],vecteur[1]+origine[1])
        p1= deplacer_pol(origine,A,angle-math.pi/2)
        p7= deplacer_pol(origine,A,angle+math.pi/2)
        p2 = deplacer_pol(p1,distance_pp4-C,angle)
        p6 = deplacer_pol(p7,distance_pp4-C,angle)
        p3 = deplacer_pol(p2,B,angle-math.pi/2)
        p5 = deplacer_pol(p6,B,angle+math.pi/2)
        polygone = [p1,p2,p3,p4,p5,p6,p7]

    else:
        
        p3 = (vecteur[0]+origine[0],vecteur[1]+origine[1])
        p1 = deplacer_pol(p3,C,angle+math.pi)
        p2 = deplacer_pol(p1,A+B,angle-math.pi/2)
        p4 = deplacer_pol(p1,A+B,angle+math.pi/2)
        polygone= [p1,p2,p3,p4]

    pygame.draw.polygon(fenetre, couleur, polygone)
    
    return 

#Fonctions ajoutées

def ajouter_objet(x, y, q) :
    objets.append((x, y, q))
    
def calculer_couleur(v) :

    if v <= 8:
        return (255, (255*v/8), 0)
    elif v <= 16:
        return ((255*(16 -v)/8), 255, (255*(v-8)/8))
    elif v <= 24:
        return (0, (255*(24-v)/8), 255)
    elif v <= 32:
        return ((255*(v-24)/8), 0, 255)
    else:
        return (255, 0, 255)


def calculer_champ(x2, y2):
    Ex, Ey = 0, 0
    for (x, y, q) in objets :
        r = math.sqrt((x2 - x)**2 + (y2 - y)**2)
        if r < 20 :
            return None
        else :
            E = k * q / r**2
            angle = math.atan2(y2-y, x2-x)
            
            Ex += E * math.cos(angle)
            Ey += E * math.sin(angle)
    return (Ex, Ey)

def dessiner_champ():
    largeur, hauteur = dimensions_fenetre[0], dimensions_fenetre[1]
    scan = 50

    for y in range(-50, hauteur + scan, scan):
        for x in range(-50, largeur + scan, scan):
            if (x, y) != (0, 0) :
                vecteur = calculer_champ(x, y)

                if vecteur != None:
                    E = math.sqrt(vecteur[0]**2 + vecteur[1]**2)
                    if E != 0 :
                        v = math.sqrt(1000*E)
                        couleur = calculer_couleur(v)
                        angle = math.atan2(vecteur[1], vecteur[0])
                        x3 = 40 * math.cos(angle)
                        y3 = 40 * math.sin(angle)
                        centre_x = x - x3/2
                        centre_y = y - y3/2
                        dessiner_vecteur(fenetre, couleur, (centre_x, centre_y), (x3, y3))

def retirer_objet(x1, y1):
    for(x,y,q) in objets:
        ecart = math.sqrt((x1 - x)**2 + (y1 - y)**2)
        if (ecart < 10):
            objets.remove((x,y,q))
            return

def ajouter(position, button):
    x, y = position
    if button == 1:
        ajouter_objet(x, y, 10**-7)
    elif button == 3:
        ajouter_objet(x, y, -10**-7)
    elif button == 2:
        retirer_objet(x, y)

# Boucle principale

while True:
    for evenement in pygame.event.get():
        if evenement.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        elif evenement.type == pygame.MOUSEBUTTONDOWN:
            ajouter(evenement.pos, evenement.button)

    fenetre.fill(couleur_fond)
    dessiner_champ()
    for (x, y, q) in objets :
        if q < 0 :
            pygame.draw.circle(fenetre, NOIR , (x, y), 10)
        else :
            pygame.draw.circle(fenetre, ROUGE , (x, y), 10)

    pygame.display.flip()
    horloge.tick(images_par_seconde)