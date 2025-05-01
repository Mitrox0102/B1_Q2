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

dimensions_fenetre = (1600, 900)  # en pixels
images_par_seconde = 25


mobile_x, mobile_y = dimensions_fenetre[0]/2, dimensions_fenetre[1]/2
mobile_vx, mobile_vy = 0, 0
mobile_charge = 1e-10
masse_mobile = 1e-10
mobile_est_present = False

champ_electrique_v = 10 # V/mµ
champ_magnetique = 0.1


t0 = 0
temps_maintenant = 0
dt = 0
pas = 00.0001

# Initialisation

pygame.init()

fenetre = pygame.display.set_mode(dimensions_fenetre)
pygame.display.set_caption("Programme 8")

horloge = pygame.time.Clock()
couleur_fond = BLEUCLAIR

#Fonctions ajoutées

def calculer_champ_electrique():
   return(0, -champ_electrique_v)

def dessiner_mobile():
   if mobile_est_present == True:
      pygame.draw.circle(fenetre, ROUGE, (mobile_x,mobile_y),rayon, largeur_trait)
   

def mettre_a_jour_mobile(t):
   global mobile_x, mobile_y, mobile_vx, mobile_vy, mobile_est_present

   Ex, Ey = calculer_champ_electrique()

#force de Lorentz (f = E + v x B)
   fxe = mobile_charge * Ex
   fye = mobile_charge * Ey

   #Force magnétique
   fxm = mobile_charge * (mobile_vy * champ_magnetique)
   fym = mobile_charge * (-mobile_vx * champ_magnetique)

   fx = fxe + fxm
   fy = fye + fym

   ax = fx / masse_mobile
   ay = fy / masse_mobile

   mobile_vx += ax * t
   mobile_vy += ay * t

   mobile_x += mobile_vx * t
   mobile_y += mobile_vy * t

   if mobile_x < 0 or mobile_x > dimensions_fenetre[0] or mobile_y < 0 or mobile_y > dimensions_fenetre[1]:
      mobile_est_present = False

   return

def calculer_energie_cinetique():
   v = math.sqrt(mobile_vx**2 + mobile_vy**2)
   return ((masse_mobile * v**2)/2)



def tableau(x,y):

   police  = pygame.font.SysFont("monospace", 16)


   champ = "Champ électrique : {0} V/m".format(champ_electrique_v)
   affichage_champ = police.render(champ, True, NOIR)
   fenetre.blit(affichage_champ, (x, y))
   
   
   energie_cinetique = calculer_energie_cinetique() * 1e6  # Convert to μJ
   Ec = "Energie cinétique : {0:.2f} µJ".format(energie_cinetique)
   affichage_Ec = police.render(Ec, True, NOIR)
   fenetre.blit(affichage_Ec, (x, y + 20))

# Boucle principale

while True:
   for evenement in pygame.event.get():
      if evenement.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
      elif evenement.type == pygame.KEYDOWN:
            if evenement.key == pygame.K_r:
               mobile_est_present = True
               mobile_x, mobile_y = dimensions_fenetre[0]//2, dimensions_fenetre[1]//2
               mobile_vx, mobile_vy = 0, 0

   fenetre.fill(couleur_fond)
   
   dessiner_mobile()
   temps_maintenant = pygame.time.get_ticks()
   t = (temps_maintenant - t0)/1000
   t0 = temps_maintenant
   
   dt += t
   while dt > pas:
      if mobile_est_present == True:
            mettre_a_jour_mobile(pas)
      dt -= pas
   
   tableau(20, 20)

   print(f"Position: ({mobile_x}, {mobile_y}), Vitesse: ({mobile_vx}, {mobile_vy})")
   
   pygame.display.flip()
   horloge.tick(images_par_seconde)