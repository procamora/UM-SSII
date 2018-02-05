/*
 * sbr.hpp
 *
 *  Created on: 23 dic. 2017
 *      Author: procamora
 */

#ifndef PRACTICA2_SBR_HPP_
#define PRACTICA2_SBR_HPP_

#define REGEX_RULES "R(\\d+): Si (.*) Entonces (.*)"
#define REGEX_RULES_PRECONDITION "(\\w+ ..? \\w+)"

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
    string state;
    //int prioridad;
    //int indexRegla;
} Condition;

typedef struct {
    int index;
    vector<Condition> precondition;
    Condition consequence;
    int priority;
    bool use;
} Rules;

Configuration *configuration = new Configuration; //Configuracion global
vector<Rules> listRules;	 // Lista de reglas global
vector<Condition> listBH; // Base de Hechos global

void readFileConfiguration(const char *pathFile);
void printConfiguration();
void readFileBC(const char *pathFile);
void printBC();
void printConditions(vector<Condition> precondition);
string parserRule(string line);
void parserRulePreconditionAux(string line, vector<Condition> *precondition);
const vector<string> explode(const string& s, const char& c);
void readFileBH(const char *pathFile);
void printBH();

#endif /* PRACTICA2_SBR_HPP_ */
