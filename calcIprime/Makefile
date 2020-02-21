CC= gcc
OBJ =  jt_arbre/jt_Iprime.o jt_lib/jt_aleatoire.o jt_lib/jt_direction.o jt_lib/jt_fichier.o jt_lib/jt_os.o jt_lib/jt_string.o jt_lib/utilitaire.o AnalyserArbre.o jt_arbre/jt_CalcDesequilibreArbre.o jt_arbre/jt_arbre.o jt_coalescence/jt_coalescence.o jt_arbre/jt_shao.o jt_arbre/MeanFeuilleMin.o jt_arbre/MeanMeanNoeud.o
LINKOBJ =  jt_arbre/jt_Iprime.o jt_lib/jt_aleatoire.o jt_lib/jt_direction.o jt_lib/jt_fichier.o jt_lib/jt_os.o jt_lib/jt_string.o jt_lib/utilitaire.o AnalyserArbre.o jt_arbre/jt_CalcDesequilibreArbre.o jt_arbre/jt_arbre.o jt_coalescence/jt_coalescence.o jt_arbre/jt_shao.o jt_arbre/MeanFeuilleMin.o jt_arbre/MeanMeanNoeud.o
LIBS = -lm
BIN = CalcIPrimeV2.exe
CFLAGS = -Wall -std=gnu99

RM = rm -f
.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)


jt_arbre/jt_Iprime.o: jt_arbre/jt_Iprime.c
	$(CC) -c jt_arbre/jt_Iprime.c -o jt_arbre/jt_Iprime.o $(CFLAGS) 
jt_lib/jt_aleatoire.o: jt_lib/jt_aleatoire.c
	$(CC) -c jt_lib/jt_aleatoire.c -o jt_lib/jt_aleatoire.o $(CFLAGS) 
jt_lib/jt_direction.o: jt_lib/jt_direction.c
	$(CC) -c jt_lib/jt_direction.c -o jt_lib/jt_direction.o $(CFLAGS) 
jt_lib/jt_fichier.o: jt_lib/jt_fichier.c
	$(CC) -c jt_lib/jt_fichier.c -o jt_lib/jt_fichier.o $(CFLAGS) 
jt_lib/jt_os.o: jt_lib/jt_os.c
	$(CC) -c jt_lib/jt_os.c -o jt_lib/jt_os.o $(CFLAGS) 
jt_lib/jt_string.o: jt_lib/jt_string.c
	$(CC) -c jt_lib/jt_string.c -o jt_lib/jt_string.o $(CFLAGS) 
jt_lib/utilitaire.o: jt_lib/utilitaire.c
	$(CC) -c jt_lib/utilitaire.c -o jt_lib/utilitaire.o $(CFLAGS) 
AnalyserArbre.o: AnalyserArbre.c
	$(CC) -c AnalyserArbre.c -o AnalyserArbre.o $(CFLAGS) 
jt_arbre/jt_CalcDesequilibreArbre.o: jt_arbre/jt_CalcDesequilibreArbre.c
	$(CC) -c jt_arbre/jt_CalcDesequilibreArbre.c -o jt_arbre/jt_CalcDesequilibreArbre.o $(CFLAGS) 
jt_arbre/jt_arbre.o: jt_arbre/jt_arbre.c
	$(CC) -c jt_arbre/jt_arbre.c -o jt_arbre/jt_arbre.o $(CFLAGS) 
jt_coalescence/jt_coalescence.o: jt_coalescence/jt_coalescence.c
	$(CC) -c jt_coalescence/jt_coalescence.c -o jt_coalescence/jt_coalescence.o $(CFLAGS) 
jt_arbre/jt_shao.o: jt_arbre/jt_shao.c
	$(CC) -c jt_arbre/jt_shao.c -o jt_arbre/jt_shao.o $(CFLAGS) 
jt_arbre/MeanFeuilleMin.o: jt_arbre/MeanFeuilleMin.c
	$(CC) -c jt_arbre/MeanFeuilleMin.c -o jt_arbre/MeanFeuilleMin.o $(CFLAGS) 
jt_arbre/MeanMeanNoeud.o: jt_arbre/MeanMeanNoeud.c
	$(CC) -c jt_arbre/MeanMeanNoeud.c -o jt_arbre/MeanMeanNoeud.o $(CFLAGS) 
