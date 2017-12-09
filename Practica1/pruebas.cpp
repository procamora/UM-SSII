/*
 * pruebas.cpp
 *
 *  Created on: 18 nov. 2017
 *      Author: procamora
 */

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct plantilla {
        int tam;
        int *fijo;
};

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

int calculaFilas(struct plantilla *S) {
    int contFila = 1;

    int huecosVacios = 0;
    int *t1 = new int[S->tam];

    memset(t1, 0, sizeof(int) * S->tam);

    //creamos el array de numeros
    for (int i = 0; i < S->tam; i++)
        for (int j = i + 1; j < S->tam ; j++) {
            cout << S->fijo[i] << " ";
            cout << S->fijo[j] << " ";
            t1[S->fijo[i]] = S->fijo[i];
        }

    cout << endl;
    //comprobamos las posiciones en las que no hay ningun numero y aumentamos contador ya que seran los huecos que faltan
    for (int i = 1; i <= S->tam; i++) {
        cout << t1[i] << " ";
        if (t1[i] == 0)
            huecosVacios++;
    }
    cout << endl;

    delete[] t1;
    return huecosVacios;
}

int main(int argc, char **argv) {

    struct plantilla *plantillaSudoku = new plantilla;
    const char *nombreF = "../Practica1/guion-P1/Casos/MIO_RESUELTO";
    leerSudoku(plantillaSudoku, nombreF);
    imprimirSudoku(plantillaSudoku);

    cout << "Filas: " << calculaFilas(plantillaSudoku) << endl;
//cout << "Filas: " << esLegal(plantillaSudoku) << endl;

}
