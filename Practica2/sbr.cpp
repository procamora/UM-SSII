/*
 * sbr.cpp
 *
 *  Created on: 23 dic. 2017
 *      Author: procamora
 */

#include "sbr.hpp"

/**
 * Metodo para cargar en memoria la configuracion
 */
void readFileConfiguration(const char *pathFile) {
    ifstream file(pathFile);
    if (!file.is_open()) {
        cerr << "Fichero: " << pathFile << " no ha podido ser abierto" << endl;
        cout << "Terminando programa..." << endl;
        exit(0);
    }

    vector<string> attributes;
    string line;

    getline(file, line);  //ATRIBUTOS
    getline(file, line);
    configuration->sizeAttributes = stoi(line);

    for (int i = 0; i < configuration->sizeAttributes; i++) {
        getline(file, line);
        attributes.push_back(line);
    }

    configuration->attributes = attributes;

    getline(file, line);  //OBJETIVO
    getline(file, line);
    configuration->objetive = line;

    getline(file, line);  //PRIORIDADES-REGLAS
    getline(file, line);
    configuration->sizePriority = stoi(line);

    vector<int> priority;

    for (int i = 0; i < configuration->sizePriority; i++) {
        getline(file, line);
        priority.push_back(stoi(line));
    }

    configuration->priority = priority;
    file.close();
}

/**
 * Metodo para imprimir la configuracion del sistema
 */
void printConfiguration() {
    cout << "################# INICIO CONFIGURACION #################" << endl;
    cout << "tamAtributos: " << configuration->sizeAttributes << endl;

    for (auto attr : configuration->attributes)
        cout << "\t " << attr << endl;

    cout << "objetivo: " << configuration->objetive << endl;
    cout << "sizePriority: " << configuration->sizePriority << endl;

    for (auto pri : configuration->priority)
        cout << "\t " << pri << endl;

    cout << "################## FIN CONFIGURACION #################" << endl;
}

/**
 * Metodo para cargar en memoria la Base de Conocimiento
 */
void readFileBC(const char *pathFile) {
    ifstream file(pathFile);
    if (!file.is_open()) {
        cerr << "Fichero: " << pathFile << " no ha podido ser abierto" << endl;
        cout << "Terminando programa..." << endl;
        exit(0);
    }

    vector<string> attributes;
    string line;

    getline(file, line);  //IDENTIFICACION DE FRUTAS
    getline(file, line); // numero de reglas que hay

    int numLines = stoi(line);
    for (int i = 0; i < numLines; i++) {
        getline(file, line);
        parserRule(line);
    }
    file.close();
}

/**
 * Metodo para parsear las reglas
 */
string parserRule(string line) {
    Rules rule;
    vector<Condition> precondition;
    Condition condition;
    regex rgx(REGEX_RULES);
    smatch matches;

    if (regex_search(line, matches, rgx) && matches.size() == 4) {
        rule.indice = stoi(matches[1].str());
        parserRulePreconditionAux(matches[2].str(), &precondition);
        condition.name = matches[3].str();
        rule.precondition = precondition;
        rule.consecuencia = condition;
        rule.prioridad = configuration->priority[rule.indice - 1];
        listRules.push_back(rule);
    } else
        cerr << "NOT Match found!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

    return line;
}

/**
 * Metodo para parsear las precondiciones en la regla
 */
void parserRulePreconditionAux(string line, vector<Condition> *precondition) {
    smatch match;
    regex regex("(\\w+ ..? \\w+)");

    while (regex_search(line, match, regex)) {
        if (match.size() == 2) {
            Condition c;
            vector<string> v = explode(match[1], ' ');
            c.name = v[0];
            c.operador = v[1];
            c.estado = v[2];
            precondition->push_back(c);
            //cout << match[1] << " ";
        }
        line = match.suffix().str();
    }
}

/**
 * Metodo para partir un string a partir de un delimitador
 * http://www.cplusplus.com/articles/2wA0RXSz/
 */
const vector<string> explode(const string& s, const char& c) {
    string buff { "" };
    vector<string> v;

    for (auto n : s) {
        if (n != c)
            buff += n;
        else if (n == c && buff != "") {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "")
        v.push_back(buff);

    return v;
}

/**
 * Metodo para imprimir la Base de Conocimiento
 */
void printBC() {
    cout << "################## INICIO BC #################" << endl;
    for (Rules rule : listRules) {
        cout << "R" << rule.indice << ": Si ";
        printBCAux(rule.precondition);
        cout << "Entonces " << rule.consecuencia.name << " " << rule.consecuencia.operador << rule.consecuencia.estado;
        cout << "; Prioridad: " << rule.prioridad << endl;
    }
    cout << "################### FIN BC ##################" << endl;
}

/**
 * Metodo auxiliar para imprimir las condiciones de la Base de Conocimiento
 */
void printBCAux(vector<Condition> precondition) {
    unsigned int cont = 0;
    for (Condition condition : precondition) {
        cout << condition.name << " " << condition.operador << " " << condition.estado;
        cont++;
        if (cont != precondition.size())
            cout << " && ";
        else
            cout << " ";
    }
}

int main(int argc, char **argv) {

    const char *bc = argv[1];
    const char *conf = argv[2];
    //const char *bh = argv[3];

    readFileConfiguration(conf);
    printConfiguration();
    readFileBC(bc);
    printBC();

    return 0;
}

