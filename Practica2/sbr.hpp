/*
 * sbr.hpp
 *
 *  Created on: 23 dic. 2017
 *      Author: procamora
 */

#ifndef PRACTICA2_SBR_HPP_
#define PRACTICA2_SBR_HPP_

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct {
        int sizeAttributes;
        vector<string> attributes;
        string objetive;
        int sizePriority;
        vector<int> priority;
} Configuration;

typedef struct {
        string nombre;
        //string estado;
        //int prioridad;
        //int indexRegla;
} variable;  //FIXME llamar condition

typedef struct {
        int tipo;
        vector<variable> precondicion;
        //vector<variable> consecuencia;
        //int prioridad;
        //int indice;
        //bool usada;
} Reglas;

void leerFicheroConfiguracion(Configuration *conf, const char *file);
void imprimirFicheroConfiguracion(Configuration *conf);
void leerFicheroReglas(Reglas *rules, const char *file);
void imprimirFicheroReglas(Reglas *rules);


#endif /* PRACTICA2_SBR_HPP_ */
