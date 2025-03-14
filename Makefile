CC = gcc
CFLAGS = -Wall -g

# Fichiers sources
SRCS_H = biblioH.c entreeSortieH.c
SRCS_LC = biblioLC.c entreeSortieLC.c

# Objets
OBJS_H = $(SRCS_H:.c=.o)
OBJS_LC = $(SRCS_LC:.c=.o)

# Exécutables
EXEC_BIBLIO = gestion_biblioH
EXEC_TEMPS = gestion_temps

# Compilation principale (menu interactif)
$(EXEC_BIBLIO): main.o $(OBJS_H) $(OBJS_LC)
	$(CC) $(CFLAGS) -o $(EXEC_BIBLIO) main.o $(OBJS_H) $(OBJS_LC)

# Compilation pour tester les temps
$(EXEC_TEMPS): main_test_temps.o $(OBJS_H) $(OBJS_LC)
	$(CC) $(CFLAGS) -o $(EXEC_TEMPS) main_test_temps.o $(OBJS_H) $(OBJS_LC)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


all: $(EXEC_BIBLIO) $(EXEC_TEMPS)

clean:
	rm -f *.o $(EXEC_BIBLIO) $(EXEC_TEMPS)
