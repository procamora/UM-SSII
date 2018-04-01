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
#include <sstream> // stoi
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
} Condition;

typedef struct {
    int index;
    vector<Condition> precondition;
    Condition consequence;
    int priority;
    bool use;
} Rule;

Configuration *configuration = new Configuration; //Configuracion

#endif /* PRACTICA2_SBR_HPP_ */
