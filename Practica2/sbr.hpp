/*
 * sbr.hpp
 *
 *  Created on: 23 dic. 2017
 *      Author: procamora
 */

#ifndef PRACTICA2_SBR_HPP_
#define PRACTICA2_SBR_HPP_

#define REGEX_RULES "R(\\d+): Si (.*) Entonces (.*)"

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

typedef struct {
        int sizeAttributes;
        vector<string> attributes;
        string objetive;
        int sizePriority;
        vector<int> priority;
} Configuration;

typedef struct {
        string name;
        string operador;
        string estado;
        //int prioridad;
        //int indexRegla;
} Condition;

typedef struct {
        int indice;
        vector<Condition> precondition;
        Condition consecuencia;
        int prioridad;
        //bool usada;
} Rules;

Configuration *configuration = new Configuration;
vector<Rules> listRules;	 // Lista de reglas global


void readFileConfiguration(const char *file);
void printConfiguration();
void readFileBC(const char *file);
void printBC();
void printBCAux(vector<Condition> precondition);
string parserRule(string line);
void parserRulePreconditionAux(string line, vector<Condition> *precondition);
const vector<string> explode(const string& s, const char& c);



#endif /* PRACTICA2_SBR_HPP_ */
