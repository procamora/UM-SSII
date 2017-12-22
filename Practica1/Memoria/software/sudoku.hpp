#ifndef PRACTICA1_SUDOKU_HPP_
#define PRACTICA1_SUDOKU_HPP_

#include <ga/GASimpleGA.h> //  Algoritmo Genetico simple
#include <ga/GA1DArrayGenome.h> // Genoma --> array de enteros (dim. 1) alelos
#include <iostream>
#include <fstream>
#include <cmath>  //sqrt
#define TAM_POBLACION 12000

using namespace std;

struct plantilla {
        int tam;
        int *fijo;
};

/*
 * array para obtener el indice por el que empieza cada bloque de un sudoku
 */
int getInicioFilaBloque[9] = { 0, 3, 6, 27, 30, 33, 54, 57, 60 };

float fitness(GAGenome &);  // Funcion objetivo --> al final
int compruebaHuecosVacios(int *t1, int tamSudoku);
GABoolean termina(GAGeneticAlgorithm &);  // Funcion de terminacion --> al final
void leerSudoku(struct plantilla *S, const char *nombreF);
void imprimirSudoku(struct plantilla *S);
void inicioSudoku(GAGenome& g);
int cruceSudoku(const GAGenome& p1, const GAGenome & p2, GAGenome* c1, GAGenome* c2);
bool checkColumna(int col[], int * check, int tam);
int mutacionSudoku(GAGenome& g, float pmut);
void calculaFilas(GAGenome& g, int inicioFila, int *t1);
void calculaColumnas(GAGenome& g, int inicioColumna, int *t1);
void calculaSubBloque(GAGenome& g, int bloque, int *t1);
void imprimirSudokuResulto(char *solucion);

#endif /* PRACTICA1_SUDOKU_HPP_ */
