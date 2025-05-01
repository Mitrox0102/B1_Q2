# Nom de l'exécutable
EXEC = five

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -g --std=c99 --pedantic -Wall -W -Wmissing-prototypes -Wextra `pkg-config --cflags gtk+-2.0`#-fsanitize=address
LDFlAGS = `pkg-config --libs gtk+-2.0` #-fsanitize=address

# Répertoires des sources
MODEL_DIR = modele
VIEW_DIR = vue
CONTROL_DIR = controle

# Fichiers sources
SRC = ./main.c \
      $(MODEL_DIR)/modele.c \
      $(VIEW_DIR)/vue.c \
      $(CONTROL_DIR)/controle.c \
		./utilis.c


# Fichiers objets
OBJ = $(SRC:.c=.o)

# Règle principale
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFlAGS)

# Compilation des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers compilés
clean:
	rm -f $(OBJ) $(EXEC)

# Nettoyage complet
mrproper: clean
	rm -f *~