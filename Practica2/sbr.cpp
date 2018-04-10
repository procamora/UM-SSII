/*
 * sbr.cpp
 *
 *  Created on: 23 dic. 2017
 *      Author: procamora
 */

#include "sbr.hpp"

/**
 * Metodo para convertir un string en un int, en linux no es necesario pero parece que en windows con mingw si
 * https://www.reddit.com/r/cpp_questions/comments/2s7y35/gcc_492_stoi_not_a_member/
 */
int stoiMia(const std::string& s) {
    istringstream str(s);
    int i;
    str >> i;
    return i;
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
 * Metodo para cargar en memoria la configuracion
 */
void readFileConfiguration(const char *pathFile) {
    ifstream file(pathFile);
    if (!file.is_open()) {
        cerr << "Fichero: " << pathFile << " no ha podido ser abierto" << endl;
        cout << "Terminando programa..." << endl;
        exit(0);
    }

    vector<Attributes> attributes;
    string line;

    getline(file, line);  //ATRIBUTOS
    getline(file, line);
    configuration->sizeAttributes = stoiMia(line);

    for (int i = 0; i < configuration->sizeAttributes; i++) {
        getline(file, line);
        vector<string> splitAttributes = explode(line, ' ');
        Attributes attrib;
        attrib.name = splitAttributes[0];
        if (splitAttributes[1].compare(CONF_NUM) == 0)
            attrib.isNum = true;
        else {
            attrib.isNum = false;
            //Eliminanos los corchetes FIXME intentar ponerlo con regex
            string substrNominal = splitAttributes[2].substr(1, splitAttributes[2].size() - 2);
            vector<string> splitAttributes = explode(substrNominal, ',');
            attrib.nominal = splitAttributes;
        }
        attributes.push_back(attrib);
    }

    configuration->attributes = attributes;

    getline(file, line);  //OBJETIVO
    getline(file, line);
    configuration->objetive = line;

    getline(file, line);  //PRIORIDADES-REGLAS
    getline(file, line);
    configuration->sizePriority = stoiMia(line);

    vector<int> priority;

    for (int i = 0; i < configuration->sizePriority; i++) {
        getline(file, line);
        priority.push_back(stoiMia(line));
    }

    configuration->priority = priority;
    file.close();
}

/**
 * Metodo para imprimir la configuracion del sistema
 */
void printConfiguration(ofstream *myfile) {

    *myfile << "################# INICIO CONFIGURACION #################" << endl;
    *myfile << "sizeAttributes: " << configuration->sizeAttributes << endl;

    for (Attributes attr : configuration->attributes) {
        *myfile << "\t " << attr.name << " ";
        if (attr.isNum)
            *myfile << CONF_NUM;
        else {
            *myfile << CONF_NOMINAL << " {";
            for (string n : attr.nominal)
                *myfile << n << ","; //FIXME La ultima pone , imnecesaria, solo el visual
            *myfile << "}";
        }
        *myfile << endl;
    }

    *myfile << "objetive: " << configuration->objetive << endl;
    *myfile << "sizePriority: " << configuration->sizePriority << endl;

    for (int pri : configuration->priority)
        *myfile << "\t " << pri << endl;

    *myfile << "################## FIN CONFIGURACION #################" << endl;

}

/**
 * Metodo para parsear las precondiciones en la regla y consecuencias
 */
void parserRuleConditionAux(string line, vector<Condition> *precondition) {
    smatch match;
    regex regex(REGEX_RULES_PRECONDITION);

    while (regex_search(line, match, regex)) {
        if (match.size() == 2) {
            vector<string> splitPrecondition = explode(match[1], ' ');
            precondition->push_back( { splitPrecondition[0], splitPrecondition[1], splitPrecondition[2] });
        }
        line = match.suffix().str();
    }
}

/**
 * Metodo para parsear una regla y guardarla en memoria
 */
void parserRule(string line, vector<Rule> *listBC) {
    Rule rule;
    vector<Condition> precondition;
    vector<Condition> consequence; //Solo es 1 pero lo hago como vector para reutilizar parserRulePreconditionAux
    regex regex(REGEX_RULES);
    smatch match;

    if (regex_search(line, match, regex) && match.size() == 4) {
        rule.index = stoiMia(match[1].str());
        parserRuleConditionAux(match[2].str(), &precondition); //Precondiciones
        parserRuleConditionAux(match[3].str(), &consequence);
        if (consequence.size() != 1)
            cout << "La consecuencia en la regla" << line << " ha fallado" << endl;
        rule.precondition = precondition;
        rule.consequence = {consequence.front().name, consequence.front().operador, consequence.front().state};
        rule.priority = configuration->priority[rule.index - 1];
        rule.use = false;
        listBC->push_back(rule);
    } else
        cerr << "NOT Match found!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" << line << endl;
}

/**
 * Metodo que ordena el vector con la base de conocimiento segun el criterio, primero ordena por prioridad descendente,
 * en caso de empate de prioridad ordena por numero de regla ascendente
 */
void sortBC(vector<Rule> *listBC) {
    sort(listBC->begin(), listBC->end(), [ ]( const Rule& r1, const Rule& r2 ) {
        if( r1.priority == r2.priority) {
            return r1.index < r2.index;
        }
        return r1.priority > r2.priority;
    });
}

/**
 * Metodo para cargar en memoria la Base de Conocimiento
 */
void readFileBC(const char *pathFile, vector<Rule> *listBC) {
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
    int numLines = stoiMia(line);

    for (int i = 0; i < numLines; i++) {
        getline(file, line);
        parserRule(line, listBC);
    }
    file.close();

    sortBC(listBC);
}

/**
 * Metodo auxiliar para imprimir las condiciones de la Base de Conocimiento
 */
void printConditions(vector<Condition> precondition, ofstream *myfile) {
    unsigned int cont = 0;
    for (Condition condition : precondition) {
        *myfile << condition.name << " " << condition.operador << " " << condition.state;
        cont++;
        if (cont != precondition.size())
            *myfile << " && ";
        else
            *myfile << " ";
    }
}

/**
 * Metodo para imprimir una regla con un formato visible
 */
void printRule(Rule rule, ofstream *myfile) {
    *myfile << "R" << rule.index << ": IF ";
    printConditions(rule.precondition, myfile);
    *myfile << "THEN " << rule.consequence.name << " " << rule.consequence.operador << " " << rule.consequence.state;
    *myfile << "; Priority: " << rule.priority;
    string uso = rule.use == true ? "True" : "False";
    *myfile << " ; Use: " << uso << endl;
}

/**
 * Metodo para imprimir la Base de Conocimiento
 */
void printBC(vector<Rule> listBC, ofstream *myfile) {
    *myfile << "################## INICIO BC #################" << endl;
    for (Rule rule : listBC)
        printRule(rule, myfile);
    *myfile << "################### FIN BC ##################" << endl;
}

/**
 * Metodo para cargar en memoria la Base de Conocimiento
 */
void readFileBH(const char *pathFile, vector<Condition> *listBH) {
    ifstream file(pathFile);
    if (!file.is_open()) {
        cerr << "Fichero: " << pathFile << " no ha podido ser abierto" << endl;
        cout << "Terminando programa..." << endl;
        exit(0);
    }

    string line;
    getline(file, line); // numero de hechos que hay
    int numLines = stoiMia(line);

    for (int i = 0; i < numLines; i++) {
        getline(file, line);
        parserRuleConditionAux(line, listBH);
    }

}

/**
 * Metodo para imprimir la Base de Hechos
 */
void printBH(vector<Condition> listBH, ofstream *myfile) {
    *myfile << "################## INICIO BH #################" << endl;
    printConditions(listBH, myfile);
    *myfile << endl;
    *myfile << "################### FIN BH ##################" << endl;
}

/**
 * Metodo que imprime el vector de reglas que han sido usadas
 */
void printMark(vector<Rule> listMark, ofstream *myfile) {
    *myfile << "El orden seguido ha sido: " << endl;
    for (int i = 0; i < int(listMark.size()); i++) {
        *myfile << "\t" << i + 1 << ": ";
        //listMark[i].use = true; //al pasarle una copia antes de la modificacion
        printRule(listMark[i], myfile);
    }
}

/***
 * Compara un par de numeros segun el operador indicado
 * https://stackoverflow.com/questions/24716453/convert-string-to-operator
 */
bool conditionalState(string op, Condition conditionRuleBC, Condition conditionBH) {
    if (op.compare("=") == 0) {
        return stoiMia(conditionBH.state) == stoiMia(conditionRuleBC.state);
    } else if (op.compare("<") == 0)
        return stoiMia(conditionBH.state) < stoiMia(conditionRuleBC.state);
    else if (op.compare(">") == 0)
        return stoiMia(conditionBH.state) > stoiMia(conditionRuleBC.state);
    else if (op.compare("<=") == 0)
        return stoiMia(conditionBH.state) <= stoiMia(conditionRuleBC.state);
    else if (op.compare(">=") == 0)
        return stoiMia(conditionBH.state) >= stoiMia(conditionRuleBC.state);
    return false;
}

/**
 * Metodo para obtener la configuracion de una condicion, para saber tengo que hacer una comparacion numerica o nominal
 * https://stackoverflow.com/questions/22972265/c-return-null-struct-from-function?noredirect=1&lq=1
 */
Attributes getAttributes(Condition c1) {
    for (Attributes attr : configuration->attributes)
        if (c1.name.compare(attr.name) == 0)
            return attr;
    throw runtime_error("getAttributes no ha encontrado la condicion necesaria");
}

/**
 * Compara si 2 condiciones son iguales
 */
bool isConditionEquals(Condition conditionRuleBC, Condition conditionBH) {
    bool equals = true;
    if (!conditionRuleBC.name.compare(conditionBH.name) == 0)
        return false;

    Attributes attr = getAttributes(conditionRuleBC);
    if (attr.isNum) {  //Es numero
        bool boolNum = conditionalState(conditionRuleBC.operador, conditionRuleBC, conditionBH);
        return boolNum;
    } else { //Es nominal
        if (!conditionRuleBC.operador.compare(conditionBH.operador) == 0)
            equals = false;
        if (!conditionRuleBC.state.compare(conditionBH.state) == 0)
            equals = false;
    }
    return equals;
}

/**
 * Para una condicion de una regla de la BC comprueba si estan todas las condiciones en la BH
 */
bool isConditionInBH(Condition condition, vector<Condition> listBH) {
    for (Condition conditionBH : listBH)
        if (isConditionEquals(condition, conditionBH))
            return true;
    return false;
}

/**
 * Metodo que extrae la primera regla, se usa inicialmente aunque la regla no se vaya a usar
 */
vector<Rule> extraeCualquierRegla(vector<Rule> listBC) {
    vector<Rule> r;
    r.push_back(listBC.front());
    return r;
}

/**
 * Extrae TODAS las reglas ordenadas por prioridad que no ha sido usada y que
 * se pueden ejecutar en este momento
 */
vector<Rule> equiparar(vector<Rule> listBC, vector<Condition> listBH) {
    vector<Rule> conflict;

    for (Rule rule : listBC)
        if (!rule.use) {
            bool valid = true;
            for (Condition condition : rule.precondition) {
                if (!isConditionInBH(condition, listBH))
                    valid = false;
            }
            if (valid)
                conflict.push_back(rule);
        }
    return conflict;
}

/**
 * Retorna True si hemos encontrado la meta, False en caso contrario
 */
bool contenida(string meta, vector<Condition> listBH) {
    for (Condition condition : listBH)
        if (condition.name.compare(meta) == 0)
            return true;
    return false;
}

/**
 * Retorna true si encuentra alguna regla que aun no ha sido usada en el conjucto conflicto
 */
bool noVacia(vector<Rule> conjuntoConflicto) {
    for (Rule rule : conjuntoConflicto)
        if (!rule.use)
            return true;
    return false;
}

/**
 * Resuelve la primera regla del conjunto conflicto, retornando la primera regla del vector,
 * ya que es un vector ordenado
 */
Rule resolver(vector<Rule> &conjuntoConflicto) {
    return conjuntoConflicto.front();
}

/**
 * Actualiza la Base de Hechos con el nuevo valor sacado
 */
void aplicar(Rule r, vector<Condition> *listBH) {
    listBH->push_back( { r.consequence.name, r.consequence.operador, r.consequence.state });
}

/**
 * Actualiza la Base de Conocimiento marcando como utilizado la regla para no volver a ejecutarse
 */
Rule actualizar(Rule r, vector<Rule> &listBC) {
    for (int i = 0; i < int(listBC.size()); i++)
        if (listBC[i].index == r.index) {
            listBC[i].use = true;
            return listBC[i];
        }
    throw runtime_error("actualizar no ha actualizado la regla");
}

//FIXME BORRAR
void printConditions(vector<Condition> precondition) {
    unsigned int cont = 0;
    for (Condition condition : precondition) {
        cout << condition.name << " " << condition.operador << " " << condition.state;
        cont++;
        if (cont != precondition.size())
            cout << " && ";
        else
            cout << " ";
    }
}
/**
 * Motor de Inferencia con encaminamiento hacia delante
 */
bool motorInferencia(vector<Rule> *listBC, vector<Condition> *listBH, vector<Rule> *listMark) {
    vector<Rule> conjuntoConflicto = extraeCualquierRegla(*listBC);

    while (!contenida(configuration->objetive, *listBH) && noVacia(conjuntoConflicto)) {
        conjuntoConflicto = equiparar(*listBC, *listBH);

        for (auto rule : conjuntoConflicto) {
            cout << "R" << rule.index << ": IF ";
            printConditions(rule.precondition);
            cout << "THEN " << rule.consequence.name << " " << rule.consequence.operador << " " << rule.consequence.state;
            cout << "; Priority: " << rule.priority;
            string uso = rule.use == true ? "True" : "False";
            cout << " ; Use: " << uso << endl;
        }
        cout<<endl;

        if (noVacia(conjuntoConflicto)) {
            Rule r = resolver(conjuntoConflicto);
            aplicar(r, listBH);
            r = actualizar(r, *listBC);
            listMark->push_back(r);
        }
    }
    if (contenida(configuration->objetive, *listBH))
        return true;
    else
        return false;

}

int main(int argc, char **argv) {

    const char *bc = argv[1];
    const char *conf = argv[2];
    const char *bh = argv[3];

    vector<Rule> listBC;     // Base de Conociminto
    vector<Rule> listMark;   // Base de Conociminto de reglas marcadas ordenadas
    vector<Condition> listBH; // Base de Hechos

    ofstream myfile;
    myfile.open(SALIDA_1);
    readFileConfiguration(conf);
    //printConfiguration(&myfile);
    readFileBC(bc, &listBC);
    printBC(listBC, &myfile);

    myfile << "########## INICIO ATRIBUTO OBJETIVO ##########" << endl;
    myfile << "Objetivo -> " << configuration->objetive << endl;
    myfile << "########### FIN ATRIBUTO OBJETIVO ###########" << endl;

    readFileBH(bh, &listBH);
    printBH(listBH, &myfile);

    bool result = motorInferencia(&listBC, &listBH, &listMark);
    printMark(listMark, &myfile);
    myfile.close();

    myfile.open(SALIDA_2);
    printBC(listBC, &myfile);
    printBH(listBH, &myfile);

    Rule r = listMark.back();

    if (result) {
        cout << "EXITO!!" << endl;
        myfile << "El resultado objetivo es: " << r.consequence.name << " " << r.consequence.operador << " " << r.consequence.state << endl;
    } else {
        cout << "FRACASO :(" << endl;
        myfile << "El resultado objetivo no ha podido ser encontrado" << endl;
    }

    myfile.close();

    return 0;
}

