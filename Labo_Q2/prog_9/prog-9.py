import pygame
import math
import sys

# Constantes

BLEUCLAIR = (127, 191, 255)
ROUGE = (255, 0, 0)
BLEU = (0, 0, 255)
GRIS = (128, 128, 128)
NOIR = (0, 0, 0)

dimensions_fenetre = (800, 600)
centre_x = dimensions_fenetre[0] // 2
centre_y = dimensions_fenetre[1] // 2
images_par_seconde = 25

# Paramètres physiques

K = 1000   # nombre de spires
R = 0.02   # rayon du rotor (m)
L = 0.06   # longueur d’un brin conducteur (m)
B = 0.5    # champ magnétique (T)
J = 1.0    # moment d’inertie
c = 0.2    # coefficient de frottement
Rm = 10    # résistance du moteur (ohm)

# Variables du moteur

angle_moteur = 0 # angle du rotor (rad)
vitesse_moteur = 0 # vitesse du rotor (rad/s)
courant_moteur = 0 # courant du moteur (A)
tension_moteur = 0 # tension du moteur (V)
courant_enroulement = 0 # courant dans les spires (A)
circuit_est_ouvert = True
compteur = 0

# Temps

temps_maintenant = 0

# Initialisation Pygame

pygame.init()
fenetre = pygame.display.set_mode(dimensions_fenetre)
pygame.display.set_caption("Programme 9")
horloge = pygame.time.Clock()
couleur_fond = BLEUCLAIR

pygame.key.set_repeat(10, 10)

temps_precedent = pygame.time.get_ticks()

def mettre_a_jour_moteur(t):
   global angle_moteur, vitesse_moteur, courant_moteur, courant_enroulement, tension_moteur

   angle_mod = math.fmod(angle_moteur, 2 * math.pi)
   if angle_mod < 0:
      angle_mod += 2 * math.pi

   # Force électromotrice

   E = 2 * K * R * L * B * vitesse_moteur * math.cos(angle_moteur)
   if math.pi / 2 <= angle_mod <= 3 * math.pi / 2:
      E = -E

   if circuit_est_ouvert:
      tension_moteur = E
      courant_moteur = 0
   else:
      tension_moteur = 10
      courant_moteur = (10 - E) / Rm


   if 0 <= angle_mod <= math.pi / 2 or 3 * math.pi / 2 < angle_mod < 2 * math.pi:
      courant_enroulement = courant_moteur 
   else:
      courant_enroulement = -courant_moteur

   # Couple électromagnétique + frottement

   couple = 2 * K * R * L * courant_enroulement * B * math.cos(angle_moteur)
   
   couple -= c * vitesse_moteur

   
   acceleration = couple / J
   vitesse_moteur += acceleration * t
   angle_moteur += vitesse_moteur * t


def dessiner_stator():
   largeur_rectangle = 300
   hauteur_rectangle = 200
   x = centre_x - largeur_rectangle // 2
   y = centre_y - hauteur_rectangle // 2

   pygame.draw.rect(fenetre, ROUGE, (x, y, largeur_rectangle // 2, hauteur_rectangle))
   pygame.draw.rect(fenetre, BLEU, (x + largeur_rectangle // 2, y, largeur_rectangle // 2, hauteur_rectangle))

def dessiner_rotor():
   pygame.draw.circle(fenetre, BLEUCLAIR, (centre_x, centre_y), 110)
   pygame.draw.circle(fenetre, GRIS, (centre_x, centre_y), 95)

   x_rond = centre_x + 70 * math.cos(angle_moteur)
   y_rond = centre_y + 70 * math.sin(angle_moteur)
   pygame.draw.circle(fenetre, NOIR, (int(x_rond), int(y_rond)), 10)

def afficher_tableau_de_bord(x, y):
   police = pygame.font.SysFont("monospace", 16)

   texte1 = "Courant : {0:.2f} A".format(courant_moteur)
   texte2 = "Tension : {0:.2f} V".format(tension_moteur)
   etat = "Fermé" if not circuit_est_ouvert else "Ouvert"
   texte3 = "Circuit : " + etat


   fenetre.blit(police.render(texte1, True, NOIR), (x, y))
   fenetre.blit(police.render(texte2, True, NOIR), (x, y + 20))
   fenetre.blit(police.render(texte3, True, NOIR), (x, y + 40))

# Boucle principale

while True:
   fenetre.fill(couleur_fond)

   dessiner_stator()
   dessiner_rotor()

   for event in pygame.event.get():
      if event.type == pygame.QUIT:
         pygame.quit()
         sys.exit()
      elif event.type == pygame.KEYDOWN:
         if event.key == pygame.K_SPACE:
            compteur = 5

   if compteur > 0:
      circuit_est_ouvert = False
      compteur -= 1
   else:
      circuit_est_ouvert = True

   temps_maintenant = pygame.time.get_ticks()
   dt = (temps_maintenant - temps_precedent) / 1000
   temps_precedent = temps_maintenant

   mettre_a_jour_moteur(dt)
   afficher_tableau_de_bord(20, 20)

   pygame.display.flip()
   horloge.tick(images_par_seconde)
