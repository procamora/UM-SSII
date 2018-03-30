/*
 * sbr.cpp
 *
 *  Created on: 23 dic. 2017
 *      Author: procamora
 */

#include "sbr.hpp"

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
    configuration->sizeAttributes = stoi(line);

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
    cout << "sizeAttributes: " << configuration->sizeAttributes << endl;

    for (Attributes attr : configuration->attributes) {
        cout << "\t " << attr.name << " "; //FIXME CAMBIAR
        if (attr.isNum)
            cout << CONF_NUM;
        else {
            cout << CONF_NOMINAL << " {";
            for (auto n : attr.nominal)
                cout << n << ","; //FIXME La ultima pone , imnecesaria, solo el visual
        }
        cout << "}" << endl;
    }

    cout << "objetive: " << configuration->objetive << endl;
    cout << "sizePriority: " << configuration->sizePriority << endl;

    for (auto pri : configuration->priority)
        cout << "\t " << pri << endl;

    cout << "################## FIN CONFIGURACION #################" << endl;
}

/**
 * Metodo para parsear las precondiciones en la regla
 */
void parserRulePreconditionAux(string line, vector<Condition> *precondition) {
    smatch match;
    regex regex(REGEX_RULES_PRECONDITION);

    while (regex_search(line, match, regex)) {
        if (match.size() == 2) {
            Condition condition;
            vector<string> splitPrecondition = explode(match[1], ' ');
            condition.name = splitPrecondition[0];
            condition.operador = splitPrecondition[1];
            condition.state = splitPrecondition[2];
            precondition->push_back(condition);
        }
        line = match.suffix().str();
    }
}

/**
 * Metodo para parsear una regla
 */
void parserRule(string line, vector<Rule> *listBC) {
    Rule rule;
    vector<Condition> precondition;
    Condition condition;
    regex regex(REGEX_RULES);
    smatch match;

    if (regex_search(line, match, regex) && match.size() == 4) {
        rule.index = stoi(match[1].str());
        parserRulePreconditionAux(match[2].str(), &precondition);
        condition.name = match[3].str();
        rule.precondition = precondition;
        rule.consequence = condition;
        rule.priority = configuration->priority[rule.index - 1];
        rule.use = false;
        listBC->push_back(rule);
    } else
        cerr << "NOT Match found!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" << line << endl;
}

void sortBC(vector<Rule> *listBC) {
    //Ordenamos segun criterio
    sort(listBC->begin(), listBC->end(), [ ]( const auto& lhs, const auto& rhs ) {
        if( lhs.priority == rhs.priority) {
            return lhs.index < rhs.index;
        }
        return lhs.priority > rhs.priority;
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
    int numLines = stoi(line);

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

void printRule(Rule rule) {
    cout << "R" << rule.index << ": IF ";
    printConditions(rule.precondition);
    cout << "THEN " << rule.consequence.name << " " << rule.consequence.operador << rule.consequence.state;
    cout << "; Priority: " << rule.priority;
    string uso = rule.use == true ? "True" : "False";
    cout << " ; Use: " << uso << endl;
}

/**
 * Metodo para imprimir la Base de Conocimiento
 */
void printBC(vector<Rule> listBC) {
    cout << "################## INICIO BC #################" << endl;
    for (Rule rule : listBC) {
        printRule(rule);
    }
    cout << "################### FIN BC ##################" << endl;
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
    int numLines = stoi(line);

    for (int i = 0; i < numLines; i++) {
        getline(file, line);
        parserRulePreconditionAux(line, listBH);
    }

    file.close();
}

/**
 * Metodo para imprimir la Base de Hechos
 */
void printBH(vector<Condition> listBH) {
    cout << "################## INICIO BH #################" << endl;
    printConditions(listBH);
    cout << endl;
    cout << "################### FIN BH ##################" << endl;
}

void printMark(vector<Rule> listMark) {
    cout << "El orden seguido ha sido: " << endl;
    for (int i = 0; i < int(listMark.size()); i++) {
        cout << i << ": ";
        printRule(listMark[i]);
    }
}
/***
 * Compara un numero segun el operador
 * https://stackoverflow.com/questions/24716453/convert-string-to-operator
 */
bool conditionalState(string op, Condition conditionRuleBC, Condition conditionBH) {
//cout << "BC:" << conditionRuleBC.name << " " << conditionRuleBC.operador << " " << conditionRuleBC.state << endl;
//cout << "BH:" << conditionBH.name << " " << conditionBH.operador << " " << conditionBH.state << endl;
    if (op.compare("=") == 0) {
        return stoi(conditionBH.state) == stoi(conditionRuleBC.state);
    } else if (op.compare("<") == 0)
        return stoi(conditionBH.state) < stoi(conditionRuleBC.state);
    else if (op.compare(">") == 0)
        return stoi(conditionBH.state) > stoi(conditionRuleBC.state);
    else if (op.compare("<=") == 0)
        return stoi(conditionBH.state) <= stoi(conditionRuleBC.state);
    else if (op.compare(">=") == 0)
        return stoi(conditionBH.state) >= stoi(conditionRuleBC.state);
    return false;
}

/**
 * Metodo para obtener la configuracion de una condicion
 * https://stackoverflow.com/questions/22972265/c-return-null-struct-from-function?noredirect=1&lq=1
 */
Attributes getAttributes(Condition c1) {
    for (Attributes attr : configuration->attributes)
        if (c1.name.compare(attr.name) == 0)
            return attr;
    throw runtime_error("getAttributes no ha encontrado la condicion necesaria"); // FIXME CAMBIAR O DEJAR?
}

/**
 * Compara si 2 condiciones son iguales
 */
bool isConditionEquals(Condition conditionRuleBC, Condition conditionBH) {
    bool equals = true;
    if (!conditionRuleBC.name.compare(conditionBH.name) == 0)
        return false;

    Attributes attr = getAttributes(conditionRuleBC);
//cout << "Is num: " << attr.isNum << endl;
//cout << endl;
    if (attr.isNum) {  //Es numero
        bool boolNum = conditionalState(conditionRuleBC.operador, conditionRuleBC, conditionBH);
        // cout << boolNum << endl;
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
    for (Condition conditionBH : listBH) {
        //cout << "analizo: " << conditionBH.name << endl;
        if (isConditionEquals(condition, conditionBH)) {
            // cout << "acierta: " << conditionBH.name << endl;
            return true;
        }
        //cout << "falla: " << conditionBH.name << endl;
    }
    return false;
}

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
        } else
            cout << "La regla esta en uso: " << rule.priority << endl;
    return conflict;
}

/**
 * Retorna True si hemos encontrado la meta, False en caso contrario
 */
bool contenida(string meta, vector<Condition> listBH) {
    for (Condition condition : listBH)
        if (condition.name.compare(meta))
            return true;
    return false;
}

/**
 * Retorna true si encuentra alguna regla que aun no ha sido usada
 */
bool noVacia(vector<Rule> listBC) {
//FIXME creo que esta regla esta mal, ya que no tiene en cuenta que puede haber reglas
//no usadas pero que no se puedan usar
    for (Rule rule : listBC)
        if (!rule.use)
            return true;
    return false;
}

/**
 * Resuelve la primera regla del conjunto conflicto ya que es un vector ordenado primero por prioridad y luego por numero de regla
 */
Rule resolver(vector<Rule> &conjuntoConflicto) {
//&conjuntoConflicto[0].use = true;
//return &conjuntoConflicto[0];
//conjuntoConflicto->front().use = true;
    return conjuntoConflicto.front();
}
/**
 * Actualiza la Base de Hechos con el nuevo valor sacado
 */
void aplicar(Rule r, vector<Condition> &listBH) {
    cout << "Actualizada: " << r.consequence.name << r.consequence.operador << r.consequence.state << endl;
    listBH.push_back(r.consequence);
}

/**
 * Actualiza la Base de Conocimiento marcando como utilizado la regla para no volver a ejecutarse
 */
void actualizar(Rule r, vector<Rule> &listBC) {
    for (int i = 0; i < int(listBC.size()); i++) {
        if (listBC[i].index == r.index) {
            cout << "ac: " << listBC[i].index << endl;
            listBC[i].use = true;
            return;
        }
    }
//listBH->push_back(r.consequence);
}

void motorInferencia(vector<Rule> listBC, vector<Condition> listBH, vector<Rule> listMark) {
    vector<Rule> conjuntoConflicto = extraeCualquierRegla(listBC);

    while (!contenida(configuration->objetive, listBH) && noVacia(listBC)) {
        conjuntoConflicto = equiparar(listBC, listBH);
        if (noVacia(listBC)) {
            Rule r = resolver(conjuntoConflicto);
            aplicar(r, listBH);
            actualizar(r, listBC);
            listMark.push_back(r);
            // printBC(conjuntoConflicto);
        }
    }
    if (contenida(configuration->objetive, listBH))
        return; // "exito";
}

int main(int argc, char **argv) {

    const char *bc = argv[1];
    const char *conf = argv[2];
    const char *bh = argv[3];

    vector<Rule> listBC;     // Base de Conociminto
    vector<Rule> listMark;   // Base de Conociminto de reglas marcadas ordenadas
    vector<Condition> listBH; // Base de Hechos

    readFileConfiguration(conf);
//printConfiguration();
    readFileBC(bc, &listBC);
    printBC(listBC);
    readFileBH(bh, &listBH);
    printBH(listBH);

    motorInferencia(listBC, listBH, listMark);

    printBH(listBH);
    printBC(listBC);
    printMark(listMark);

    return 0;
}

