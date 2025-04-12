import math
import pygame
import sys

# Constantes

BLEUCLAIR = (127, 191, 255)
ROUGE = (255, 0, 0)
NOIR = (0, 0, 0)
k = 8.9876 * 10**9
rayon = 10
largeur_trait = 4

# Paramètres

objets = []
dimensions_fenetre = (1600, 900)  # en pixels
images_par_seconde = 25


mobile_x, mobile_y = 0, 0
mobile_vx, mobile_vy = 0, 0
mobile_charge = 0
masse_mobile = 1e-10
mobile_est_present = False


t0 = 0
temps_maintenant = 0

# Initialisation

pygame.init()

fenetre = pygame.display.set_mode(dimensions_fenetre)
pygame.display.set_caption("Programme 3")

horloge = pygame.time.Clock()
couleur_fond = BLEUCLAIR

#Fonctions ajoutées

def ajouter_objet(x, y, q) :
    objets.append((x, y, q))


def retirer_objet(x1, y1):
    for(x,y,q) in objets:
        ecart = math.sqrt((x1 - x)**2 + (y1 - y)**2)
        if (ecart < 10):
            objets.remove((x,y,q))
            return

def ajouter_charge(position, button):
    x, y = position
    if button == 1:
        ajouter_objet(x, y, 10**-7)
        print("Ajoute")
    elif button == 3:
        ajouter_objet(x, y, -10**-7)
        print("Ajoute")
    elif button == 2:
        retirer_objet(x, y)
        print("Retire")

def calculer_champ(x2, y2):
    global mobile_est_present, mobile_vx, mobile_vy
    Ex, Ey = 0, 0
    for (x, y, q) in objets :
        r = math.sqrt((x2 - x)**2 + (y2 - y)**2)
        if r < 20 :
            mobile_est_present = False
            Ex, Ey = 0, 0
            mobile_vx, mobile_vy = 0, 0
        else :
            E = k * q / r**2

            Ex += E * (x2 - x) / r
            Ey += E * (y2 - y) / r
    return (Ex, Ey)

def dessiner_mobile():
    if mobile_est_present == True:
        if(mobile_charge < 0):
            pygame.draw.circle(fenetre, NOIR, (mobile_x, mobile_y), rayon, largeur_trait)
        else:
            pygame.draw.circle(fenetre, ROUGE, (mobile_x,mobile_y),rayon, largeur_trait)
    

def mettre_a_jour_mobile(t):
    global mobile_x, mobile_y, mobile_vx, mobile_vy, mobile_est_present
    Ex, Ey = calculer_champ(mobile_x, mobile_y)
    if Ex is None or Ey is None:
        mobile_est_present = False
        Ex, Ey = 0, 0
        return
    
    fx = mobile_charge * Ex
    fy = mobile_charge * Ey

    ax = fx / masse_mobile
    ay = fy / masse_mobile

    mobile_vx += ax * t
    mobile_vy += ay * t

    mobile_x += mobile_vx * t
    mobile_y += mobile_vy * t

    if mobile_x < 0 or mobile_x > dimensions_fenetre[0] or mobile_y < 0 or mobile_y > dimensions_fenetre[1]:
        mobile_est_present = False
    
    return

def calculer_energie_potentielle(x, y, charge):

    E = 0
    for (x1, y1, q) in objets:
        r = math.sqrt((x - x1)**2 + (y - y1)**2)
        if r < 20:
            return 0

        E += k * q * charge / r
    return E

def calculer_energie_cinetique(vx, vy, masse):
    v = math.sqrt(vx**2 + vy**2)
    return ((masse * v**2)/2)

def calculer_potentiel(x, y):
    V = 0
    for (x1, y1, q) in objets:
        r = math.sqrt((x - x1)**2 + (y - y1)**2)
        if r < 20:
            return 0
        else:
            V += k * q / r
    return V


def tableau(x,y):

    energie_cinetique = calculer_energie_cinetique(mobile_vx, mobile_vy, masse_mobile)
    energie_potentielle = calculer_energie_potentielle(mobile_x, mobile_y, mobile_charge)

    energie_tot = energie_potentielle + energie_cinetique


    police  = pygame.font.SysFont("monospace", 16)


    Ec = "Energie cinétique : {0:.2f} µJ".format(energie_cinetique*(10**6)) 
    affichage_Ec = police.render(Ec, True, NOIR)
    fenetre.blit(affichage_Ec, (x, y))

    Ep = "Energie potentielle : {0:.2f} µJ".format(energie_potentielle*(10**6)) 
    affichage_Ep = police.render(Ep, True, NOIR)
    fenetre.blit(affichage_Ep, (x, y + 15))

    Et = "Energie totale : {0:.2f} µJ".format(energie_tot*(10**6)) 
    affichage_Et = police.render(Et, True, NOIR)
    fenetre.blit(affichage_Et, (x, y + 30))


    Ps = "Potentiel souris : {0:.2f} V".format(potentiel_souris) 
    affichage_Ps = police.render(Ps, True, NOIR)
    fenetre.blit(affichage_Ps, (x, y+50))

# Boucle principale

while True:
    for evenement in pygame.event.get():
        if evenement.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        elif evenement.type == pygame.MOUSEBUTTONDOWN:
            ajouter_charge(evenement.pos, evenement.button)
        elif evenement.type == pygame.KEYDOWN:
            if evenement.key == pygame.K_p:
                mobile_est_present = True
                mobile_x, mobile_y = pygame.mouse.get_pos()
                mobile_charge = 10**-7
                mobile_vx, mobile_vy = 0, 0
            elif evenement.key == pygame.K_n:
                mobile_est_present = True
                mobile_x, mobile_y = pygame.mouse.get_pos()
                mobile_charge = -10**-7
                mobile_vx, mobile_vy = 0, 0

    fenetre.fill(couleur_fond)
    for (x, y, q) in objets :
        if q < 0 :
            pygame.draw.circle(fenetre, NOIR , (x, y), rayon)
        else :
            pygame.draw.circle(fenetre, ROUGE , (x, y), rayon)


    dessiner_mobile()
    temps_maintenant = pygame.time.get_ticks()
    t = (temps_maintenant - t0)/1000
    t0 = temps_maintenant

    mettre_a_jour_mobile(t)

    potentiel_souris = calculer_potentiel(pygame.mouse.get_pos()[0], pygame.mouse.get_pos()[1])

    tableau(20, 20)

    pygame.display.flip()
    horloge.tick(images_par_seconde)