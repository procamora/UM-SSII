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

/**
 * Metodo que comprueba la cantidad de huecos que tiene el array con un 0
 */
int compruebaHuecosVacios(int *t1, int tamSudoku);

/**
 * Metodo para comprobar una fila, recibe el inicio de la fila y la recorre añadiendo al array
 * pasado por referencia los valores que encuentra para su posterior tratamiento
 */
void calculaFilas(GAGenome& g, int inicioFila, int *arrayElementos);

/**
 * Metodo para comprobar una columna, recibe el inicio de la columna y va calculando los saltos que
 * tiene que dar para recorrer la columna completa añadiendo al array pasado por referencia los .
 * valores que encuentra para su posterior tratamiento
 */
void calculaColumnas(GAGenome& g, int inicioColumna, int *arrayElementos);

/**
 * Metodo encargado de comprobar las submatrices del sudoku, recibe el numero de la submatriz y
 * obtiene cual es el indice donde empieza con lo que va añadiendo al array pasado por referencia
 * los valores que encuentra para su posterior tratamiento
 */
void calculaSubBloque(GAGenome& g, int bloque, int *arrayElementos);

GABoolean termina(GAGeneticAlgorithm &);  // Funcion de terminacion --> al final

/**
 * Metodo para leer el fichero del sudoku y guardarlo en memoria
 */
void leerSudoku(struct plantilla *S, const char *nombreF);

/**
 * Metodo para imprimir el sudoku inicial que leemos del fichero
 */
void imprimirSudoku(struct plantilla *S);
/**
 * Metodo para imprimir el solucion resuelto con tabulaciones y espacios una vez que lo resuleve el algoritmo genetico
 */
void imprimirSudokuResulto(const GAGenome& g, int size);
void inicioSudoku(GAGenome& g);
int cruceSudoku(const GAGenome& p1, const GAGenome & p2, GAGenome* c1, GAGenome* c2);
bool checkColumna(int col[], int * check, int tam);
int mutacionSudoku(GAGenome& g, float pmut);
#endif /* PRACTICA1_SUDOKU_HPP_ */
