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

#define CONF_NUM "NU"
#define CONF_NOMINAL "Nom"

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

typedef struct {
    string name;
    bool isNum;
    vector<string> nominal;
} Attributes;

typedef struct {
    int sizeAttributes;
    vector<Attributes> attributes;
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
} Rule;

Configuration *configuration = new Configuration; //Configuracion global
vector<Rule> listBC;	 // Base de Conociminto global
vector<Condition> listBH; // Base de Hechos global

void readFileConfiguration(const char *pathFile);
void printConfiguration();
void readFileBC(const char *pathFile);
void sortBC();
void printBC();
void printConditions(vector<Condition> precondition);
void parserRule(string line);
void parserRulePreconditionAux(string line, vector<Condition> *precondition);
const vector<string> explode(const string& s, const char& c);
void readFileBH(const char *pathFile);
void printBH();
void motorInferencia();

#endif /* PRACTICA2_SBR_HPP_ */
