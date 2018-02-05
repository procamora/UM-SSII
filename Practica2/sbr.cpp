/*
 * sbr.cpp
 *
 *  Created on: 23 dic. 2017
 *      Author: procamora
 */

//http://www.cplusplus.com/articles/2wA0RXSz/
//https://stackoverflow.com/questions/29321249/regex-grouping-matches-with-c-11-regex-library
#include "sbr.hpp"

void readFileConfiguration(Configuration *conf, const char *file) {
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

void printConfiguration(Configuration *conf) {
	cout << "################# INICIO CONFIGURACION #################" << endl;
	cout << "tamAtributos: " << conf->sizeAttributes << endl;

	for (vector<string>::iterator it = conf->attributes.begin();
			it != conf->attributes.end(); it++)
		cout << "\t " << *it << endl;

	cout << "objetivo: " << conf->objetive << endl;
	cout << "sizePriority: " << conf->sizePriority << endl;
	for (vector<int>::iterator it = conf->priority.begin();
			it != conf->priority.end(); it++)
		cout << "\t " << *it << endl;
	cout << endl;
	cout << "################## FIN CONFIGURACION #################" << endl;
}

void readFileBC(const char *file) {
	ifstream f(file);
	if (!f.is_open()) {
		cerr << "Fichero: " << file << " no ha podido ser abierto" << endl;
		cout << "Terminando programa..." << endl;
		exit(0);
	}

	vector<string> attributes;
	string line;

	getline(f, line);  //IDENTIFICACION DE FRUTAS
	getline(f, line); // numero de reglas que hay

	int numLines = stoi(line);
	for (int i = 0; i < numLines; i++) {
		getline(f, line);
		//cout << line;
		parserRule(line);
		//Condition v /*= new Condition*/;
		// v.name = line;
		//precondicion.push_back(v);
	}

	//rules->precondicion = precondicion;
	f.close();
}

string parserRule(string line) {
	Rules rule;
	vector<Condition> precondition;
	Condition condition;

	regex rgx(REGEX_RULES);
	smatch matches;
	if (regex_search(line, matches, rgx) && matches.size() == 4) {

		rule.indice = stoi(matches[1].str());

		/*********************/

		parserRulePreconditionAux(matches[2].str(), &precondition);

		/********************/

		Condition c2;
		c2.name = matches[3].str();

		/*********************/

		rule.precondition = precondition;
		rule.consecuencia = c2;
		listRules.push_back(rule);

	} else
		cout
				<< "NOT Match found!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

	return line;
}

void parserRulePreconditionAux(string line, vector<Condition> *precondition) {

	smatch match;
	regex regex("(\\w+ ..? \\w+)");

	//std::cout << line << std::endl;

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
		//cout << std::endl;
		line = match.suffix().str();
	}
}

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

void printBC() {
	cout << "################## INICIO BC #################" << endl;
	//cout << "type: " << rules->type << endl;

	for (Rules rule : listRules) {
		cout << "\t R" << rule.indice << ": Si ";
		printBCAux(rule.precondition);
		cout << "Entonces " << rule.consecuencia.name << " "
				<< rule.consecuencia.operador << rule.consecuencia.estado;
		cout << "; Prioridad: " << rule.prioridad << endl;

	}

	//for (unsigned int i = 0; i < listRules->precondition.size(); i++)
	//cout << "\t " << listRules->precondition[i].name;

	cout << "################### FIN BC ##################" << endl;
}

void printBCAux(vector<Condition> precondition) {
	unsigned int cont = 0;
	for (Condition condition : precondition) {
		cout << condition.name << " " << condition.operador << " "
				<< condition.estado;
		cont++;
		if (cont != precondition.size())
			cout << " && ";
		else
			cout << " ";
	}
}

int main(int argc, char **argv) {

	Configuration *configuration = new Configuration;
	const char *bc = argv[1];
	const char *conf = argv[2];
	//const char *bh = argv[3];

	readFileConfiguration(configuration, conf);
	//printConfiguration(configuration);
	readFileBC(bc);
	printBC();

	return 0;
}

