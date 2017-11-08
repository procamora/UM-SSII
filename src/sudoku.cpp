/* ------------------------- PROBLEMA DE LAS N REINAS ----------------------- */
#include <ga/GASimpleGA.h> //  Algoritmo Genetico simple
#include <ga/GA1DArrayGenome.h> // Genoma --> array de enteros (dim. 1) alelos
#include <iostream>
#include <fstream>
using namespace std;

float fitnes(GAGenome &); // Funcion objetivo --> al final
float fitnes2(GAGenome& g);
GABoolean termina(GAGeneticAlgorithm &); // Funcion de terminacion --> al final
void leerSudoku(struct plantilla *S, const char *nombreF);
void imprimirSudoku(struct plantilla *S);
void inicioSudoku(GAGenome& g);
int cruceSudoku(const GAGenome& p1, const GAGenome & p2, GAGenome* c1, GAGenome* c2);
bool checkColumna(int col[], int * check, int tam);
int mutacionSudoku(GAGenome& g, float pmut);

struct plantilla {
    int tam;
    int *fijo;
};

int main(int argc, char **argv) {
    struct plantilla *plantillaSudoku = new plantilla;

    //1 “Fichero con el caso”
    //2 “Tamaño de la población”
    //3 “Operador de Selección”
    //4 “Probabilidad de cruce”
    //5 “Probabilidad de mutación”.
    // Declaramos variables para los parametros del GA y las inicializamos
    const char *nombreF = argv[1];
    int popsize = atoi(argv[2]);
    const char *selectorString = argv[3];
    int ngen = 12000; //atoi(argv[3]);
    float pcross = atof(argv[4]);
    float pmut = atof(argv[5]);

    leerSudoku(plantillaSudoku, nombreF);

    cout << "Sudoku de tamaño: " << plantillaSudoku->tam << "x" << plantillaSudoku->tam << endl;
    cout << "Parametros:\t - Tamano poblacion: " << popsize << endl;
    cout << "\t\t - Numero de generaciones: " << ngen << endl;
    cout << "\t\t - Probabilidad cruce: " << pcross << endl;
    cout << "\t\t - Probabilidad mutacion: " << pmut << endl;
    cout << endl;

    imprimirSudoku(plantillaSudoku);

    // Conjunto enumerado de alelos --> valores posibles de cada gen del genoma
    GAAlleleSet<int> alelos;
    for (int i = 0; i < plantillaSudoku->tam; i++)
        alelos.add(i);

    // Creamos el genoma y definimos operadores de inicio, cruce y mutación
    GA1DArrayAlleleGenome<int> genome(plantillaSudoku->tam * plantillaSudoku->tam, alelos, fitnes2, plantillaSudoku);
    genome.initializer(::inicioSudoku);
    genome.crossover(::cruceSudoku);
    genome.mutator(::mutacionSudoku);

    // Creamos el algoritmo genetico
    GASimpleGA ga(genome);

    // Inicializamos - minimizar funcion objetivo, tamaño poblacion, nº generaciones,
    // pr. cruce y pr. mutacion, selección y le indicamos que evolucione.

    ga.minimaxi(-1);
    ga.populationSize(popsize);
    ga.nGenerations(ngen);
    ga.pCrossover(pcross);
    ga.pMutation(pmut);
    //seleccionamos el selector
    if (strcmp(selectorString, "GARouletteWheelSelector") == 0) {
        GARouletteWheelSelector selector;
        ga.selector(selector);
    } else {
        GATournamentSelector selector;
        ga.selector(selector);
    }
    ga.terminator(::termina);
    ga.evolve(1);

    // Imprimimos el mejor individuo que encuentra el GA y su valor fitness

    cout << "El GA encuentra la solucion ( " << ga.statistics().bestIndividual() << ")" << endl;
    cout << "con valor fitness " << ga.statistics().minEver() << endl;
}

// Funcion objetivo.

float fitnes2(GAGenome& g) {
    GA1DArrayAlleleGenome<int> & genome = (GA1DArrayAlleleGenome<int> &) g;

    float jaques = 0;
    int c, f;

    // jaques de misma fila
    for (int i = 0; i < genome.length(); i++)
        for (int j = i + 1; j < genome.length(); j++)
            if (genome.gene(i) == genome.gene(j))
                jaques++;

    return jaques;
}

float fitnes(GAGenome& g) {
    GA1DArrayAlleleGenome<int> & genome = (GA1DArrayAlleleGenome<int> &) g;
    return 69;

    float jaques = 0;
    int c, f;

    // jaques de misma fila
    for (int i = 0; i < genome.length(); i++)
        for (int j = i + 1; j < genome.length(); j++)
            if (genome.gene(i) == genome.gene(j))
                jaques++;

    // jaques en diagonal
    for (int en_est = 0; en_est < genome.length(); en_est++) {
        // diagonal derecha abajo
        c = en_est + 1;
        f = genome.gene(en_est) + 1;
        while ((c < genome.length()) && (f < genome.length())) {
            if (genome.gene(c) == f)
                jaques++;
            c++;
            f++;
        }

        // diagonal derecha arriba
        c = en_est + 1;
        f = genome.gene(en_est) - 1;
        while ((c < genome.length()) && (f >= 0)) {
            if (genome.gene(c) == f)
                jaques++;
            c++;
            f--;
        }
    }

    return jaques;
}

// Funcion de terminacion
GABoolean termina(GAGeneticAlgorithm & ga) {

    if ((ga.statistics().minEver() == 0) || (ga.statistics().generation() == ga.nGenerations()))
        return gaTrue;
    else
        return gaFalse;
}

void leerSudoku(struct plantilla *S, const char *nombreF) {

    ifstream f(nombreF);
    if (!f.is_open()) {
        cerr << "Fichero: " << nombreF << " no ha podido ser abierto" << endl;
        cout << "Terminando programa..." << endl;
        exit(0);
    }

    f >> S->tam;
    S->fijo = new int[S->tam * S->tam];
    for (int i = 0; i < S->tam * S->tam; i++)
        f >> S->fijo[i];
    f.close();
}

void imprimirSudoku(struct plantilla *S) {
    int contFila = 1;

    cout << "++++++++++++++++++++++" << endl;
    for (int i = 0; i < S->tam * S->tam; i++)
        if (contFila < S->tam) {
            cout << S->fijo[i] << " ";
            contFila++;
        } else {
            cout << S->fijo[i] << endl;
            contFila = 1;
        }
    cout << "---------------------" << endl;
}

void inicioSudoku(GAGenome& g) {
    GA1DArrayAlleleGenome<int> & genome = (GA1DArrayAlleleGenome<int> &) g;

    struct plantilla * plantilla1;	// = new plantilla;
    plantilla1 = (struct plantilla *) genome.userData();

    int aux[plantilla1->tam];

    for (int f = 0; f < plantilla1->tam; f++) {
        for (int j = 0; j < plantilla1->tam; j++)
            aux[j] = 0;

        for (int j = 1; j <= plantilla1->tam; j++) {
            int v = GARandomInt(0, plantilla1->tam - 1);
            while (aux[v] != 0)
                v = (v + 1) % plantilla1->tam;
            aux[v] = j;
        }

        int i = 0;
        while (i < plantilla1->tam) {
            while ((plantilla1->fijo[(f * plantilla1->tam) + i] == 0) && (i < plantilla1->tam))
                i++;

            if (i < plantilla1->tam) {
                bool encontrado = false;
                for (int j = 0; (j < plantilla1->tam) && (!encontrado); j++)
                    if (aux[j] == plantilla1->fijo[(f * plantilla1->tam) + i]) {
                        encontrado = true;
                        aux[j] = aux[i];
                    }
                aux[i] = plantilla1->fijo[(f * plantilla1->tam) + i];
            }
            i++;
        }

        for (int c = 0; c < plantilla1->tam; c++)
            genome.gene((f * plantilla1->tam) + c, aux[c]);
    }
}

int cruceSudoku(const GAGenome& p1, const GAGenome & p2, GAGenome* c1, GAGenome* c2) {

//******************************************************//
//******************************************************//
// Hacer el casting correspondiente para obtener m y p  //
//******************************************************//
//******************************************************//
    GA1DArrayAlleleGenome<int> & m = (GA1DArrayAlleleGenome<int> &) p1;
    GA1DArrayAlleleGenome<int> & p = (GA1DArrayAlleleGenome<int> &) p2;

    struct plantilla * plantilla1 = (struct plantilla *) m.userData();
    int n = 0;

    int punto1 = GARandomInt(0, m.length());
    while ((punto1 % plantilla1->tam) != 0)
        punto1++;
    int punto2 = m.length() - punto1;

    if (c1) {
        //***************************************************//
        //***************************************************//
        // Hacer el casting correspondiente para obtener h1  //
        //***************************************************//
        //***************************************************//
        GA1DArrayGenome<int> & h1 = (GA1DArrayGenome<int> &) *c1;
        h1.copy(m, 0, 0, punto1);
        h1.copy(p, punto1, punto1, punto2);
        n++;
    }

    if (c2) {
        //***************************************************//
        //***************************************************//
        // Hacer el casting correspondiente para obtener h2  //
        //***************************************************//
        //***************************************************//
        GA1DArrayGenome<int> & h2 = (GA1DArrayGenome<int> &) *c2;

        h2.copy(p, 0, 0, punto1);
        h2.copy(m, punto1, punto1, punto2);
        n++;
    }

    return n;
}

bool checkColumna(int col[], int * check, int tam) {
    bool repe = false;

    for (int i = 0; i < tam; i++)
        check[i] = 0;

    for (int i = 0; i < tam; i++)
        check[col[i] - 1]++;
    for (int i = 0; i < tam; i++)
        if (check[i] > 1)
            repe = true;

    return repe;
}

int mutacionSudoku(GAGenome& g, float pmut) {

//*******************************************************//
//*******************************************************//
// Hacer el casting correspondiente para obtener genome  //
//*******************************************************//
//*******************************************************//
    GA1DArrayAlleleGenome<int> & genome = (GA1DArrayAlleleGenome<int> &) g;

    struct plantilla * plantilla1 = (struct plantilla *) genome.userData();
    int nmut = 0;
    int aux, aux1;
    int fil;
    bool fila;

    int caux[plantilla1->tam];
    int *checkC = new int[plantilla1->tam];

    if (pmut <= 0.0)
        return 0;

    for (int f = 0; f < plantilla1->tam; f++)
        for (int c = 0; c < plantilla1->tam; c++)
            if (plantilla1->fijo[(f * plantilla1->tam) + c] == 0) {
                if (GAFlipCoin(pmut)) {
                    if (GAFlipCoin(0.5))
                        fila = true;
                    else
                        fila = false;

                    if (!fila) {

                        for (int j = 0; j < plantilla1->tam; j++)
                            caux[j] = genome.gene((j * plantilla1->tam) + c);
                        if (checkColumna(caux, checkC, plantilla1->tam)) {
                            int v1 = GARandomInt(0, plantilla1->tam - 1);
                            while (checkC[v1] <= 1)
                                v1 = (v1 + 1) % plantilla1->tam;
                            v1++;
                            int v2 = GARandomInt(0, plantilla1->tam - 1);
                            while (checkC[v2] != 0)
                                v2 = (v2 + 1) % plantilla1->tam;
                            v2++;

                            bool encontrado = false;
                            for (int j = 0; j < plantilla1->tam && !encontrado; j++)
                                if ((plantilla1->fijo[j * (plantilla1->tam) + c] == 0)
                                        && (genome.gene(j * (plantilla1->tam) + c) == v1)) {
                                    encontrado = true;
                                    genome.gene((j * plantilla1->tam) + c, v2);
                                    fil = j;
                                }

                            int col = (c + 1) % plantilla1->tam;
                            while (genome.gene((fil * plantilla1->tam) + col) != v2)
                                col = (col + 1) % plantilla1->tam;
                            if (plantilla1->fijo[(fil * plantilla1->tam) + col] == 0) {
                                nmut++;
                                genome.gene((fil * plantilla1->tam) + col, v1);
                            } else {
                                genome.gene((fil * plantilla1->tam) + c, v1);
                            }
                        }
                    } else {
                        int v1 = (c + 1) % plantilla1->tam;
                        while ((plantilla1->fijo[(f * plantilla1->tam) + v1] != 0))
                            v1 = (v1 + 1) % plantilla1->tam;
                        aux = genome.gene((f * plantilla1->tam) + c);
                        genome.gene((f * plantilla1->tam) + c, genome.gene((f * plantilla1->tam) + v1));
                        genome.gene((f * plantilla1->tam) + v1, aux);
                        nmut++;
                    }
                }
            }
    return nmut;
}

