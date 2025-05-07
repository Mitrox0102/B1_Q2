# Nom de l'exécutable
EXEC = five

# Compilateur
CC = gcc

# Répertoire source principal
SOURCE_DIR = source

# Options de compilation
CFLAGS = -g --std=c99 --pedantic -Wall -W -Wmissing-prototypes -Wextra `pkg-config --cflags gtk+-2.0`#-fsanitize=address
LDFlAGS = `pkg-config --libs gtk+-2.0`

# Répertoire de documentation
DOC_DIR = doc/

# Répertoires des sources
MODEL_DIR = $(SOURCE_DIR)/modele
VIEW_DIR = $(SOURCE_DIR)/vue
CONTROL_DIR = $(SOURCE_DIR)/controle
RAPPORT_DIR = rapport


# Fichiers sources
SRC = $(SOURCE_DIR)/main.c \
		$(MODEL_DIR)/modele.c \
		$(VIEW_DIR)/vue.c \
		$(CONTROL_DIR)/controle.c \
		$(SOURCE_DIR)/utilis.c

# Fichiers objets (avec le même chemin relatif que les sources)
OBJ = $(SRC:.c=.o)

# Règle principale
all: $(EXEC)

# Compilation de l'exécutable
five:
$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFlAGS)

# Compilation des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation du dossier de documentation
doc:
	doxygen $(SOURCE_DIR)/Doxyfile

# Compilation du rapport LaTeX
rapport:
	cd $(RAPPORT_DIR) && pdflatex main.tex

# Nettoyage des fichiers compilés
clean:
	rm -f $(OBJ) $(EXEC)
	rm -rf $(DOC_DIR)
	cd $(RAPPORT_DIR) && rm -f *.aux *.log *.out *.toc *.nav *.snm *.vrb *.synctex.gz *.fdb_latexmk *.fls

# Déclarer les cibles qui ne correspondent pas à des fichiers
.PHONY: all clean doc $(EXEC) rapport