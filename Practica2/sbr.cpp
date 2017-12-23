/*
 * sbr.cpp
 *
 *  Created on: 23 dic. 2017
 *      Author: procamora
 */

#include "sbr.hpp"

void leerFicheroConfiguracion(Configuration *conf, const char *file) {
    ifstream f(file);
    if (!f.is_open()) {
        cerr << "Fichero: " << file << " no ha podido ser abierto" << endl;
        cout << "Terminando programa..." << endl;
        exit(0);
    }

    vector<string> attributes;
    string line;

    getline(f, line);  //ATRIBUTOS
    getline(f, line);
    conf->sizeAttributes = stoi(line);

    for (int i = 0; i < conf->sizeAttributes; i++) {
        getline(f, line);
        attributes.push_back(line);
    }

    conf->attributes = attributes;

    getline(f, line);  //OBJETIVO
    getline(f, line);
    conf->objetive = line;

    getline(f, line);  //PRIORIDADES-REGLAS
    getline(f, line);
    conf->sizePriority = stoi(line);

    vector<int> priority;

    for (int i = 0; i < conf->sizePriority; i++) {
        getline(f, line);
        priority.push_back(stoi(line));
    }
    conf->priority = priority;

    f.close();
}

void imprimirFicheroConfiguracion(Configuration *conf) {
    cout << "tamAtributos: " << conf->sizeAttributes << endl;

    for (std::vector<string>::iterator it = conf->attributes.begin(); it != conf->attributes.end(); ++it)
        cout << "\t " << *it << endl;
    cout << endl;

    cout << "objetivo: " << conf->objetive << endl;

    cout << "sizePriority: " << conf->sizePriority << endl;
    for (std::vector<int>::iterator it = conf->priority.begin(); it != conf->priority.end(); ++it)
        cout << "\t " << *it << endl;
    cout << endl;
}

void leerFicheroReglas(Reglas *rules, const char *file) {
    ifstream f(file);
    if (!f.is_open()) {
        cerr << "Fichero: " << file << " no ha podido ser abierto" << endl;
        cout << "Terminando programa..." << endl;
        exit(0);
    }

    vector<string> attributes;
    string line;

    getline(f, line);  //IDENTIFICACION DE FRUTAS
    getline(f, line);
    vector<int> priority;

    int numLines =  stoi(line);
    for (int i = 0; i < numLines; i++) {
        getline(f, line);
        cout << line;
        //attributes.push_back(line);
    }

    f.close();
}

void imprimirFicheroReglas(Reglas *rules) {
    cout << "tipo: " << rules->tipo << endl;

    for (std::vector<variable>::iterator it = rules->precondicion.begin(); it != rules->precondicion.end(); ++it)
       // cout << "\t " << *it << endl;
        ;
    cout << endl;
}

int main(int argc, char **argv) {

    Configuration *configuration = new Configuration;
    Reglas *rules = new Reglas;
    const char *bc = argv[1];
    const char *conf = argv[2];
    //const char *bh = argv[3];
    leerFicheroConfiguracion(configuration, conf);
    imprimirFicheroConfiguracion(configuration);
    leerFicheroReglas(rules, bc);
    imprimirFicheroReglas(rules);

    cout << "asd: " << configuration->attributes[0] << endl;

    return 0;
}

