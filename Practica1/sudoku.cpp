/*
 * sudoku.cpp
 *
 *      Author: procamora
 */

#include "sudoku.hpp"

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
    float pcross = atof(argv[4]);
    float pmut = atof(argv[5]);

    leerSudoku(plantillaSudoku, nombreF);

    cout << "Sudoku de tamaño: " << plantillaSudoku->tam << "x" << plantillaSudoku->tam << endl;
    cout << "Parametros:\t - Tamano poblacion: " << popsize << endl;
    cout << "\t\t - Numero de generaciones: " << TAM_POBLACION << endl;
    cout << "\t\t - Probabilidad cruce: " << pcross << endl;
    cout << "\t\t - Probabilidad mutacion: " << pmut << endl;
    cout << endl;

    imprimirSudoku(plantillaSudoku);

    // Conjunto enumerado de alelos --> valores posibles de cada gen del genoma
    GAAlleleSet<int> alelos;
    for (int i = 1; i <= plantillaSudoku->tam; i++)
        alelos.add(i);

    // Creamos el genoma y definimos operadores de inicio, cruce y mutación
    GA1DArrayAlleleGenome<int> genome(plantillaSudoku->tam * plantillaSudoku->tam, alelos, fitness, plantillaSudoku);
    genome.initializer(::inicioSudoku);
    genome.crossover(::cruceSudoku);
    genome.mutator(::mutacionSudoku);

    // Creamos el algoritmo genetico
    GASimpleGA ga(genome);

    // Inicializamos - minimizar funcion objetivo, tamaño poblacion, nº generaciones,
    // pr. cruce y pr. mutacion, selección y le indicamos que evolucione.

    ga.minimaxi(-1);  // el objetivo del algoritmo genético consiste en minimizar
    ga.populationSize(popsize);
    ga.nGenerations(TAM_POBLACION);
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
    cout << "fitness: " << ga.statistics().minEver() << endl;
}

// Funcion objetivo.
float fitness(GAGenome& g) {
    GA1DArrayAlleleGenome<int> & genome = (GA1DArrayAlleleGenome<int> &) g;

    float jaques = 0;
    int c, f;
    int huecosVacios = 0;
    int tamSudoku = sqrt(genome.length());
    int *arrayElementos = new int[tamSudoku];

    //coincidencias misma filas
    for (int i = 0; i < tamSudoku; i++) {
        memset(arrayElementos, 0, sizeof(int) * tamSudoku);
        calculaFilas(g, i * tamSudoku, arrayElementos);
        huecosVacios += compruebaHuecosVacios(arrayElementos, tamSudoku);
    }

    //coincidencias misma columna
    for (int i = 0; i < tamSudoku; i++) {
        memset(arrayElementos, 0, sizeof(int) * tamSudoku);
        calculaColumnas(g, i, arrayElementos);
        huecosVacios += compruebaHuecosVacios(arrayElementos, tamSudoku);
    }

    //coincidencias misma subcuadricula 3x3
    for (int i = 0; i < tamSudoku; i++) {
        memset(arrayElementos, 0, sizeof(int) * tamSudoku);
        calculaSubBloque(g, i, arrayElementos);
        huecosVacios += compruebaHuecosVacios(arrayElementos, tamSudoku);
    }

    delete[] arrayElementos;
    return huecosVacios;
}

/**
 * Metodo que comprueba la cantidad de huecos que tiene el array con un 0
 */
int compruebaHuecosVacios(int *array, int tamSudoku) {
    int huecosVacios = 0;
    for (int i = 1; i <= tamSudoku; i++)
        if (array[i] == 0)
            huecosVacios++;

    return huecosVacios;
}

/**
 * Metodo para comprobar una fila, recibe el inicio de la fila y la recorre añadiendo al array
 * pasado por referencia los valores que encuentra para su posterior tratamiento
 */
void calculaFilas(GAGenome& g, int inicioFila, int *arrayElementos) {
    GA1DArrayAlleleGenome<int> & genome = (GA1DArrayAlleleGenome<int> &) g;

    int tamSudoku = sqrt(genome.length());
    int finFila = inicioFila + tamSudoku;
    for (int i = inicioFila; i < finFila; i++)
        arrayElementos[genome.gene(i)] = genome.gene(i);
}

/**
 * Metodo para comprobar una fila, recibe el inicio de la columna y va calculando los saltos que
 * tiene que dar para recorrer la columna completa añadiendo al array pasado por referencia los .
 * valores que encuentra para su posterior tratamiento
 */
void calculaColumnas(GAGenome& g, int inicioColumna, int *arrayElementos) {
    GA1DArrayAlleleGenome<int> & genome = (GA1DArrayAlleleGenome<int> &) g;

    int tamSudoku = sqrt(genome.length());
    int finFila = inicioColumna + (tamSudoku * (tamSudoku - 1));
    for (int i = 0; i < tamSudoku; i++) {
        arrayElementos[genome.gene(inicioColumna)] = genome.gene(inicioColumna);
        inicioColumna += tamSudoku;
    }
}

/**
 * Metodo encargado de comprobar las submatrices del sudoku, recibe el numero de la submatriz y
 * obtiene cual es el indice donde empieza con lo que va añadiendo al array pasado por referencia
 * los valores que encuentra para su posterior tratamiento
 */
void calculaSubBloque(GAGenome& g, int bloque, int *arrayElementos) {
    GA1DArrayAlleleGenome<int> & genome = (GA1DArrayAlleleGenome<int> &) g;

    int inicioFila = getInicioFilaBloque[bloque];
    int tamSudoku = sqrt(genome.length());

    int filas = 0;
    int finFila = inicioFila + sqrt(tamSudoku);
    while (filas != sqrt(tamSudoku)) {
        for (int i = inicioFila; i < finFila; i++)
            arrayElementos[genome.gene(i)] = genome.gene(i);

        inicioFila += tamSudoku;
        finFila = inicioFila + sqrt(tamSudoku);
        filas++;
    }
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

    struct plantilla * plantilla1;
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
    GA1DArrayAlleleGenome<int> & m = (GA1DArrayAlleleGenome<int> &) p1;
    GA1DArrayAlleleGenome<int> & p = (GA1DArrayAlleleGenome<int> &) p2;

    struct plantilla * plantilla1 = (struct plantilla *) m.userData();
    int n = 0;

    int punto1 = GARandomInt(0, m.length());
    while ((punto1 % plantilla1->tam) != 0)
        punto1++;
    int punto2 = m.length() - punto1;

    if (c1) {
        GA1DArrayGenome<int> & h1 = (GA1DArrayGenome<int> &) *c1;
        h1.copy(m, 0, 0, punto1);
        h1.copy(p, punto1, punto1, punto2);
        n++;
    }

    if (c2) {
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

