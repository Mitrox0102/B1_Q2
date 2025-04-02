# ------------------------------------------------------------------------
# Laboratoires de programmation mathématique et physique 2
# ------------------------------------------------------------------------
#
# Programme : 7 segments.
#
# ------------------------------------------------------------------------

import math
import pygame
import sys
import numpy as np
import datetime as dt  # Import pour obtenir l'heure actuelle

### Constante(s)

NOIR = (0, 0, 0)
GRIS = (200, 200, 200)
ROUGE = (255, 0, 0)

### Variables Globales

valeur_memorisee = 0
precedant = 0
couleur_cercle = 0
num_afficheur = 0
latence_mat = np.zeros((6, 7), dtype=int)
valeurs_horloge = np.zeros(6, dtype=int)  # Vecteur pour stocker les digits de l'horloge

def dessiner_arduino(sortie_arduino, sortie_CD4511, sortie_CD4028, sortie_bouton):
   fenetre.blit(image_arduino, pos_arduino)
   fenetre.blit(image_CD4511, pos_CD4511)
   fenetre.blit(image_bouton, pos_bouton)
   fenetre.blit(image_CD4028, pos_CD4028)


   for j in range(0, 2):
      if j == 0:
            off_ard = 285
            off_cd = 15
            pos_carte = pos_CD4511
            r = range(0, 4)

      if j == 1:
            off_ard = 194
            off_cd = 91
            pos_carte = pos_CD4028
            r = range(4, 8)

      for i in r:
            if sortie_arduino[i] == 0:
               couleur = NOIR
            else:
               couleur = ROUGE

            pygame.draw.line(fenetre, couleur, (pos_arduino[0] + 280, pos_arduino[1] + off_ard),
                           (pos_carte[0] + 7, pos_carte[1] + off_cd), 5)
            off_ard = off_ard + 14
            off_cd = off_cd + 19



   off_cd = 15
   off_aff = 5
   i = 0
   for i in range(0, 7):
      if sortie_CD4511[i] == 0:
            couleur = NOIR
      else:
            couleur = ROUGE
      pygame.draw.line(fenetre, couleur, (pos_afficheur[0] + 591, pos_afficheur[1] + off_aff),
                        (pos_CD4511[0] + 102, pos_CD4511[1] + off_cd), 5)
      off_aff = off_aff + 19
      off_cd = off_cd + 19


   if sortie_bouton == 0:
      couleur = NOIR
   else:
      couleur = ROUGE
   pygame.draw.line(fenetre, couleur, (pos_arduino[0] + 279, pos_arduino[1] + 353),
                        (pos_bouton[0] + 13, pos_bouton[1] + 13), 5)

   i = 0
   off_cd = (102, 111)
   off_aff = 44
   for i in range(0, 6):
      if sortie_CD4028[i] == 0:
            couleur = NOIR
      else:
            couleur = ROUGE
      pygame.draw.line(fenetre, couleur, (pos_CD4028[0] + off_cd[0], pos_CD4028[1] + off_cd[1]),
                        (pos_afficheur[0] + off_aff, pos_CD4028[1] + off_cd[1]), 5)

      pygame.draw.line(fenetre, couleur, (pos_afficheur[0] + off_aff, pos_afficheur[1]),
                        (pos_afficheur[0] + off_aff, pos_CD4028[1] + off_cd[1] - 2), 5)
      off_cd = (off_cd[0], off_cd[1] - 20)
      off_aff = off_aff + 101



def dessiner_afficheur(sortie_CD4511, sortie_CD4028):
   global latence_mat
   positions_barres = [[32, 14], [89, 20], [87, 88], [28, 150],
                        [17, 88], [19, 20], [30, 82]]

   for j in range(6):
      fenetre.blit(image_afficheur_s, (pos_afficheur[0] + j*101, pos_afficheur[1]))
      if sortie_CD4028[j] == 1:
         latence_mat[j] = sortie_CD4511

      for i, barre in enumerate(positions_barres):
         if latence_mat[j][i] == 0:
            continue
         x_b = j*101 + pos_afficheur[0] + int(round(barre[0]*(image_afficheur_s.get_width()/133)))
         y_b = pos_afficheur[1] + int(round(barre[1]*(image_afficheur_s.get_height()/192)))
         if i in [0, 3, 6]:
            fenetre.blit(barre_horizontale_s, (x_b, y_b))
         else:
            fenetre.blit(barre_verticale_s, (x_b, y_b))

def composant_CD4511(entree):
   print(f"Entrée : {entree}")
   decimale = sum(entree[3 - i] * (2**i) for i in range(4))
   tdv = np.array([
      [0, 0, 1, 0, 1, 1, 1], #(H)
      [1, 0, 0, 1, 1, 1, 1], #(E)
      [0, 0, 0, 1, 1, 1, 0], #(L)
      [0, 0, 1, 1, 1, 0, 1], #(O)
      [0, 1, 1, 1, 1, 1, 1], #(W)
      [0, 0, 0, 0, 1, 0, 1], #(R)
      [0, 1, 1, 1, 1, 0, 1], #(D)
      [0, 0, 0, 0, 0, 0, 0]  #Espace
   ])
   return np.array(tdv[decimale])

def composant_CD4028(entree):
   decimale = sum(entree[3 - i] * (2**i) for i in range(4))
   tdv = np.eye(7, dtype=int)

   if decimale < 7:
         return tdv[decimale]
   else:
         return np.zeros(7,dtype=int)
      

def mettre_a_jour_horloge():
   global valeurs_horloge
   message = [0, 1, 2, 2, 3, 7, 4, 3, 5, 2, 6] 
   valeurs_horloge = np.roll(message, -num_afficheur)[:6]

def sortie_memorisee():
   global valeurs_horloge, num_afficheur
   valeur = valeurs_horloge[num_afficheur]
   binaire_valeur = np.array([0, 0, 0, 0])
   binaire_afficheur = np.array([0, 0, 0, 0])
   for i in range(4):
      binaire_valeur[3 - i] = (valeur >> i) & 1
      binaire_afficheur[3 - i] = (num_afficheur >> i) & 1
   return np.concatenate((binaire_valeur, binaire_afficheur))

def gerer_click():
   pos_souris = pygame.mouse.get_pos()
   if pygame.mouse.get_pressed()[0] == 1:
      if math.sqrt((pos_souris[0] - pos_centre_bouton[0])**2 + (pos_souris[1] - pos_centre_bouton[1])**2) < rayon_bouton:
         return 1
   return 0


def connexion_bouton(sortie_bouton):
   global valeur_memorisee, precedant
   if sortie_bouton == 0:
      couleur = NOIR
   else:
      couleur = ROUGE
      if sortie_bouton == 1 and precedant == 0:
         valeur_memorisee = (valeur_memorisee + 1) % 10

   precedant = sortie_bouton  
   pygame.draw.line(fenetre, couleur, pin_arduino, pin_bouton, 5)

   return

### Paramètre(s)

dimensions_fenetre = (1100, 600)
images_par_seconde = 25

pos_arduino = (0, 70)
pos_CD4511 = (333, 340)
pos_CD4028 = (333, 128)
pos_afficheur = (500, 350)
pos_bouton = (333, 524)
pos_centre_bouton = (pos_bouton[0] + 51, pos_bouton[1] + 34)
rayon_bouton = 18
pin_arduino = (pos_arduino[0] + 279, pos_arduino[1] + 353)
pin_bouton = (pos_bouton[0] + 13, pos_bouton[1] + 13)


### Programme

# Initialisation

pygame.init()

sig_horloge = 0
pygame.time.set_timer(pygame.USEREVENT, 600)
pygame.time.set_timer(pygame.USEREVENT + 1, 400)


fenetre = pygame.display.set_mode(dimensions_fenetre)
pygame.display.set_caption("Programme 7 segments")

horloge = pygame.time.Clock()

image_afficheur_s = pygame.image.load('images/7_seg_s.png').convert_alpha(fenetre)
barre_verticale_s = pygame.image.load('images/vertical_s.png').convert_alpha(fenetre)
barre_horizontale_s = pygame.image.load('images/horizontal_s.png').convert_alpha(fenetre)
image_afficheur = pygame.image.load('images/7_seg.png').convert_alpha(fenetre)
barre_verticale = pygame.image.load('images/vertical.png').convert_alpha(fenetre)
barre_horizontale = pygame.image.load('images/horizontal.png').convert_alpha(fenetre)
image_arduino = pygame.image.load('images/arduino.png').convert_alpha(fenetre)
image_CD4511 = pygame.image.load('images/CD4511.png').convert_alpha(fenetre)
image_CD4028 = pygame.image.load('images/CD4028.png').convert_alpha(fenetre)
image_bouton = pygame.image.load('images/bouton.png').convert_alpha(fenetre)
couleur_fond = GRIS

# Boucle principale

while True:
   temps_maintenant = pygame.time.get_ticks()
   for evenement in pygame.event.get():
      if evenement.type == pygame.QUIT:
         pygame.quit()
         sys.exit()
      elif evenement.type == pygame.USEREVENT:
         sig_horloge = 1 - sig_horloge
         if sig_horloge == 1:
            couleur_cercle = ROUGE
            mettre_a_jour_horloge()
         else:
            couleur_cercle = NOIR
      elif evenement.type == pygame.USEREVENT + 1:
         num_afficheur = (num_afficheur + 1) % 6
   sortie_bouton = gerer_click()
   if sortie_bouton == 1:
      num_afficheur = (num_afficheur + 1) % len(valeurs_horloge)  # Décalage manuel
   print(f"Sortie bouton : {sortie_bouton}, Valeurs horloge : {valeurs_horloge}")
   fenetre.fill(couleur_fond)

   sortie = sortie_memorisee()
   sortie_CD4511 = composant_CD4511(sortie[:4])
   sortie_CD4028 = composant_CD4028(sortie[4:])
   dessiner_arduino(sortie, sortie_CD4511, sortie_CD4028, sortie_bouton)
   dessiner_afficheur(sortie_CD4511, sortie_CD4028)

   connexion_bouton(sortie_bouton)

   pygame.display.flip()
   horloge.tick(images_par_seconde)