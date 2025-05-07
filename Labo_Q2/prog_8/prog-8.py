import math
import pygame
import sys

# Constantes
BLEUCLAIR = (127, 191, 255)
ROUGE = (255, 0, 0)
NOIR = (0, 0, 0)
k = 8.9876 * 10**9  #constante de Coulomn
rayon = 10          #rayon du mobile
largeur_trait = 4   #Epaisseur du trait du cercle
taille_trace = 10000#Nombre maxiaml de pints dans la trace

# Paramètres
dimensions_fenetre = (1600, 900)  # en pixels
images_par_seconde = 25

mobile_x, mobile_y = dimensions_fenetre[0]/2, dimensions_fenetre[1]/2
mobile_vx, mobile_vy = 0, 0
mobile_charge = 1e-10
masse_mobile = 1e-10
mobile_est_present = False

champ_electrique_v = 10  # V/m
champ_magnetique = 1

mode_cyclotron = False
alpha = 0

trace = [None] * taille_trace
nb_trace = 0
prochaine_trace = 0

t0 = 0
temps_maintenant = 0
dt = 0
pas = 0.0001

# Initialisation
pygame.init()
fenetre = pygame.display.set_mode(dimensions_fenetre)
pygame.display.set_caption("Programme 8")
horloge = pygame.time.Clock()
couleur_fond = BLEUCLAIR

# Fonctions ajoutées
def calculer_champ_electrique():
   return (0, -champ_electrique_v)

def ajouter_mobile(x, y, q):
   global mobile_est_present, mobile_x, mobile_y, mobile_charge, mobile_vx, mobile_vy
   if not mobile_est_present:
      mobile_est_present = True
   mobile_x = x
   mobile_y = y
   mobile_vx = 0
   mobile_vy = 0
   mobile_charge = q

def dessiner_mobile():
   if mobile_est_present:
      couleur = ROUGE if mobile_charge > 0 else NOIR
      pygame.draw.circle(fenetre, couleur, (int(mobile_x), int(mobile_y)), rayon, largeur_trait)

def mettre_a_jour_mobile(t):
   global mobile_x, mobile_y, mobile_vx, mobile_vy
   if not mode_cyclotron:
      return
   
   e_x, e_y = calculer_champ_electrique()

   force_electrique_x = mobile_charge * e_x
   force_electrique_y = mobile_charge * e_y

   force_lorentz_x = -mobile_charge * (mobile_vy * champ_magnetique)
   force_lorentz_y = mobile_charge * (mobile_vx * champ_magnetique)

   force_x = force_electrique_x + force_lorentz_x
   force_y = force_electrique_y + force_lorentz_y

   ax = force_x / masse_mobile
   ay = force_y / masse_mobile

   mobile_vx += ax * t
   mobile_vy += ay * t

   mobile_x += mobile_vx * t
   mobile_y += mobile_vy * t

def calculer_energie_cinetique(vx, vy, m):
   return 0.5 * m * (vx**2 + vy**2)

def tableau(x, y):
   police = pygame.font.SysFont("monospace", 16)
   energie = calculer_energie_cinetique(mobile_vx, mobile_vy, masse_mobile) * 1e6
   ligne1 = "Energie cinétique : {0:.2f} µJ".format(energie)
   ligne2 = "Champ électrique : {0:.2f} V/m".format(champ_electrique_v)
   ligne3 = "Champ magnétique : {0:.2f} T".format(champ_magnetique)
   fenetre.blit(police.render(ligne1, True, NOIR), (x, y))
   fenetre.blit(police.render(ligne2, True, NOIR), (x, y + 20))
   fenetre.blit(police.render(ligne3, True, NOIR), (x, y + 40))

def initialiser_trace():
   global trace, nb_trace, prochaine_trace
   trace = [None] * taille_trace
   nb_trace = 0
   prochaine_trace = 0

def ajouter_trace():
   global trace, nb_trace, prochaine_trace
   if nb_trace < taille_trace:
      nb_trace += 1
   trace[prochaine_trace] = (int(mobile_x), int(mobile_y))
   prochaine_trace = (prochaine_trace + 1) % taille_trace

def afficher_trace():
   for i in range(nb_trace):
      index = (prochaine_trace - 1 - i) % taille_trace
      position = trace[index]
      pygame.draw.circle(fenetre, (100, 100, 100), position, 3)

def calculer_champ_cyclotron(dt):
   global alpha, champ_electrique_v
   if not mode_cyclotron:
      return
   
   T = (2 * math.pi * masse_mobile) / (mobile_charge * champ_magnetique)
   alpha += (2 * math.pi * dt) / T

   alpha = math.fmod(alpha, 2 * math.pi)
   champ_electrique_v = 10 * math.sin(alpha)

# Boucle principale
ajouter_mobile(800, 450, mobile_charge)
initialiser_trace()

temps_precedent = pygame.time.get_ticks()
dt_fixe = 0.001 / 10

while True:
   fenetre.fill(couleur_fond)
   for event in pygame.event.get():
      if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
      elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP and champ_electrique_v < 100:
               champ_electrique_v += 1
               mode_cyclotron = False
            elif event.key == pygame.K_DOWN and champ_electrique_v > -100:
               champ_electrique_v -= 1
               mode_cyclotron = False
            elif event.key == pygame.K_SPACE:
               mobile_x = dimensions_fenetre[0] // 2
               mobile_y = dimensions_fenetre[1] // 2
               mobile_vx = 0
               mobile_vy = 0
               mobile_est_present = True
               mode_cyclotron = False
               initialiser_trace()
            elif event.key == pygame.K_l and champ_magnetique < 1:
               champ_magnetique += 0.01
            elif event.key == pygame.K_m and champ_magnetique > -1:
               champ_magnetique -= 0.01
            elif event.key == pygame.K_c:
               mode_cyclotron = True

   dessiner_mobile()
   ajouter_trace()
   afficher_trace()

   temps_maintenant = pygame.time.get_ticks()
   nb_etapes = temps_maintenant - temps_precedent
   temps_precedent = temps_maintenant

   for _ in range(nb_etapes):
      for _ in range(10):
            calculer_champ_cyclotron(dt_fixe)
            mettre_a_jour_mobile(dt_fixe)

   tableau(20, 20)
   pygame.display.flip()
   horloge.tick(images_par_seconde)
