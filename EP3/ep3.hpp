#ifndef _EP3_H
#define _EP3_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <regex>

using namespace std;

class Alphabet 
{
    set<char> symbols; 

    void setAlphabet (string);
    void printAlpha ();

    public:
        Alphabet():
        symbols() {};
        
        Alphabet (string allSymbols) 
            { setAlphabet (allSymbols); 
                printAlpha (); }
        
        ~Alphabet() 
            { symbols.clear(); }
        
        bool isAlpha (char c) {
            if (symbols.find (c) != symbols.end())
                return true;
            else 
                return false; 
        }

        char getSymbol (int position) {
            if ((int)symbols.size() <= position)
                return 0;
            
            return *next (symbols.begin(), position);
        }
};

void Alphabet::setAlphabet (string allSymbols)
{
    regex alphaSensitive ("[a-zA-Z]");
    regex numbers ("[0-9]");

    string aux;
    for (unsigned int i = 0; i < allSymbols.size(); i++){
        aux = allSymbols[i];
        // check for groups
        if (aux == "-")
            for (char k = allSymbols[i-1]; k <= allSymbols[i+1]; k++)
                symbols.insert (k);
        // check for joker
        else if (aux == "."){
            for (char k = 'a'; k <= 'z'; k++)
                symbols.insert (k);
            for (char k = 'A'; k <= 'Z'; k++)
                symbols.insert (k);
            for (char k = '0'; k <= '9'; k++)
                symbols.insert (k);
        }
        
        else if (regex_match (aux, alphaSensitive) || regex_match (aux, numbers))
            symbols.insert (allSymbols[i]);
        
        // check for "∧" operator
        else if (aux == "^"){
            string complement = "";
            while (allSymbols[i] != ']')
                complement += allSymbols[i++];
            
            for (char k = 'a'; k <= 'z'; k++)
                if (complement.find (k) == complement.npos)
                    symbols.insert (k);
            for (char k = 'A'; k <= 'Z'; k++)
                if (complement.find (k) == complement.npos)
                    symbols.insert (k);
            for (char k = '0'; k <= '9'; k++)
                if (complement.find (k) == complement.npos)
                    symbols.insert (k);
        }
    }
}

void Alphabet::printAlpha ()
{
    int count = 0;
    cout << "******** ALFABETO ********\n";
    char symb;
    for (int i = 0; (symb = getSymbol (i)) != 0; i++){
        if (count >= 10){
            cout << "\n";
            count = 0;
        }
        cout << symb << " ";
        count++;
    }
    if (count != 10)
        cout << "\n";
    cout << "************************\n";
}

class Transition
{
    char symbol;
    int nextState; 

    public:
        Transition();
        
        Transition (char c, int next): 
        symbol (c), nextState (next) {};

        char getSymbol()
            { return symbol; }
        int getNextState()
            { return nextState; }
        void ChangeNextState (int n)
            { nextState = n; }
};

class State 
{
    vector<Transition> transitions;


    public:
    int ID; 
        State();
        
        State (int id): 
        transitions(), ID (id) {};

        ~State(){ 
            transitions.clear();
            ID = -1;
        }

        void setNextState (char s, int next)
            { transitions.push_back (Transition (s, next)); } 
        
        void setNextState (char s, State *next)
            { transitions.push_back (Transition (s, next->ID)); } 
        
        vector<int>* isTransition (char);
};

vector<int>* State::isTransition (char c)
{
    vector<int> *next = new vector<int>;

    for (unsigned int i = 0; i != transitions.size(); i++)
        if (transitions[i].getSymbol() == c || transitions[i].getSymbol() == 0)
            next->push_back (transitions[i].getNextState());

    if (next->size() != 0)
        return next;
    else
        return nullptr;
}

class NFA
{
    vector<State*> Q;
    string expression;
    Alphabet sigma;
    State *q0, *qf;


    void setJoker (int);

    public:
        NFA():
        q0 (nullptr), qf (nullptr) {};

        NFA (string expr){
            expression = expr;
            q0 = new State (0);
            qf = q0;
            Q.push_back (q0);
            sigma = Alphabet (expr);
        }
        
        ~NFA(){ 
            q0 = qf = nullptr;
            Q.clear();
        }

        void readRE (string, unsigned int);  
        bool checkWord (string, int, int); 
};

void NFA::readRE (string RE, unsigned int itString)
{   
    if (itString > RE.size()-1)
        return;
    
    int stateCount = (int)Q.size();
    string single = "";
    single += RE[itString++];
    
    if (single == "["){
        // character range
        if (RE[itString+1] == '-'){
            string charRange = "";
            for (int i = RE[itString]; i <= RE[itString+2]; i++)
                charRange += i;
            itString += 3;
            // "0 or more" quantifier
            if (RE[itString+1] == '*'){
                for (int i = 0; i < (int)charRange.size(); i++)
                    qf->setNextState (charRange[i], qf);
                itString++;
            }
            else {
                State *novo = new State (stateCount);
                Q.push_back (novo);    
                // "one or more" quantifier
                if (RE[itString+1] == '+'){
                    for (int i = 0; i < (int)charRange.size(); i++){
                        qf->setNextState (charRange[i], qf);
                        qf->setNextState (charRange[i], stateCount);
                    }
                    itString++;
                }
                // no quantifier
                else 
                    for (int i = 0; i < (int)charRange.size(); i++)
                        qf->setNextState (charRange[i], stateCount);
            qf = novo;
            }
        }
        
        // character group
        else if (sigma.isAlpha (RE[itString])){
            string charGroup = "";
            while (RE[itString] != ']')
                charGroup += RE[itString++];
            
            // "0 or more" quantifier
            if (RE[itString+1] == '*'){
                for (int i = 0; i < (int)charGroup.size(); i++)
                    qf->setNextState (charGroup[i], qf);
                itString++;
            }
            else {
                State *novo = new State (stateCount);
                Q.push_back (novo);    
                // "one or more" quantifier
                if (RE[itString+1] == '+'){
                    for (int i = 0; i < (int)charGroup.size(); i++){
                        qf->setNextState (charGroup[i], qf);
                        qf->setNextState (charGroup[i], stateCount);
                    }
                    itString++;
                }
                // no quantifier
                else 
                    for (int i = 0; i < (int)charGroup.size(); i++)
                        qf->setNextState (charGroup[i], stateCount);
                qf = novo;
            }
        }

        // complement
        else{
            string complement = "";
            char symb;
            itString++;

            while (RE[itString] != ']')
                complement += RE[itString++];

            // complement is an char range
            size_t found = complement.find ("-");
            while (found != complement.npos){
                string complementAux = "";
                for (char c = complement[found-1]; c <= complement[found+1]; c++)
                    complementAux += c;
                complement = complementAux;
                found = complement.find ("-", found+1);
            }
           
            // "0 or more" quantifier
            if (RE[itString+1] == '*'){
                for (int i = 1; (symb = sigma.getSymbol (i)) != 0; i++)
                        if (complement.find (symb) == complement.npos)
                        qf->setNextState (symb, qf);
                    itString++;
            }
            else{
                State *novo = new State (stateCount);
                Q.push_back (novo);    

                // "one or more" quantifier
                if (RE[itString+1] == '+'){
                    for (int i = 1; (symb = sigma.getSymbol (i)) != 0; i++)
                        if (complement.find (symb) == complement.npos){
                            qf->setNextState (symb, qf);
                            qf->setNextState (symb, stateCount);
                        }
                    itString++;
                }
                // no quantifier
                else
                    for (int i = 1; (symb = sigma.getSymbol (i)) != 0; i++)
                        if (complement.find (symb) == complement.npos)
                            qf->setNextState (symb, stateCount);
                qf = novo;
           }
        } 
        readRE (RE, ++itString);
    }

    else if (single == "("){
        string multipleAlt = "";
        State *aux = nullptr;

        while (RE[itString] != ')')
            multipleAlt += RE[itString++];

        size_t found = multipleAlt.find ("(");
        
        // multiple alternative
        if (found == multipleAlt.npos){
            multipleAlt += '|';

            // "0 or more" quantifier
            if (RE[itString+1] == '*'){
                for (int i = 0; i < (int)multipleAlt.size(); i++){
                    // single char
                    if (multipleAlt[i+1] == '|')
                        qf->setNextState (multipleAlt[i++], qf);
                    // 1+ char
                    else{
                        aux = qf;
                        while (multipleAlt[i+1] != '|'){
                            State *novo = new State (stateCount);
                            Q.push_back (novo);
                            aux->setNextState (multipleAlt[i++], stateCount++);
                            aux = novo;
                        }
                        aux->setNextState (multipleAlt[i++], qf);
                    }
                }
                readRE (RE, itString+2);
            }
            else{
                State *novo = new State (stateCount);
                Q.push_back (novo);    
                // "one or more" quantifier
                if (RE[itString+1] == '+'){
                    for (int i = 0; i < (int)multipleAlt.size(); i++){
                        // single char
                        if (multipleAlt[i+1] == '|'){
                            qf->setNextState (multipleAlt[i], qf);
                            qf->setNextState (multipleAlt[i++], stateCount);
                        }
                        // 1+ char
                        else{
                            aux = qf;
                            while (multipleAlt[i+1] != '|'){
                                State *novo = new State (stateCount);
                                Q.push_back (novo);
                                aux->setNextState (multipleAlt[i++], stateCount++);
                                aux = novo;
                            }
                            aux->setNextState (multipleAlt[i], qf);
                            aux->setNextState (multipleAlt[i++], stateCount);
                        }
                    }
                    itString++;
                }
                // no quantifier
                else{
                    for (int i = 0; i < (int)multipleAlt.size(); i++){
                        // single char
                        if (multipleAlt[i+1] == '|')
                            qf->setNextState (multipleAlt[i++], stateCount);
                        // 1+ char
                        else{
                            aux = qf;
                            while (multipleAlt[i+1] != '|'){
                                State *novo = new State (stateCount);
                                Q.push_back (novo);
                                aux->setNextState (multipleAlt[i++], stateCount++);
                                aux = novo;
                            }
                            aux->setNextState (multipleAlt[i++], stateCount);
                        }
                    }
                }
                qf = novo;
                readRE (RE, ++itString);
            }
        }
        
        // 1+ parenthesis
        else{
            State* lastQf = qf;
            
            multipleAlt += RE[itString++];
            while (found != multipleAlt.npos){
                while (RE[itString] != ')')
                    multipleAlt += RE[itString++];
                found = multipleAlt.find ("(", found+1);
                readRE (multipleAlt, 0);
            }
            
            // "0 or more" quantifier
            if (RE[itString+1] == '*'){
                qf->setNextState (0, lastQf);
                qf = lastQf;
            }
            // "one or more" quantifier
            else if (RE[itString+1] == '+')
                qf->setNextState (0, lastQf);
        }
    }

    // joker
    else if (single == "."){
        // "0 or more" quantifier
        if (RE[itString] == '*'){
            setJoker (stateCount-1);
            qf = Q[stateCount-1];
            readRE (RE, ++itString);
        }
        else {
            State *novo = new State (stateCount);
            Q.push_back (novo);
            setJoker (stateCount);
            qf = novo;
            // "one or more" quantifier
            if (RE[itString] == '+'){
                setJoker (stateCount);
                readRE (RE, ++itString);
            }
            // no quantifier
            else
                readRE (RE, itString);
        }
    }
    
    // single letter 
    else {
        // "0 or more" quantifier
        if (RE[itString] == '*'){
            qf = Q[stateCount-1];
            Q[stateCount-1]->setNextState (single[0], stateCount-1);
            readRE (RE, ++itString);
        }
        else {
            State *novo = new State (stateCount);
            Q.push_back (novo);
            qf->setNextState (single[0], stateCount);
            qf = novo;
            // "one or more" quantifier
            if (RE[itString] == '+'){
                Q[stateCount]->setNextState (single[0], stateCount);
                readRE (RE, ++itString);
            }
            // no quantifier
            else
                readRE (RE, itString);
        }
    }
    q0 = Q[0];
}

bool NFA::checkWord (string word, int it, int id) 
{
    int current = id; 
    vector<int> *p;
    for (int i = it; i < (int)word.size(); i++){
        // check if the letters are part of the alphabet
        if (!sigma.isAlpha (word[i]))
            return false;

        // check the if the word matchs de RE
        p = Q[current]->isTransition (word[i]);
        if (p){
            current++;
            for (auto k = p->begin(); k != p->end(); k++)
                if (checkWord (word, i+1, *k) == true)
                    return true;
            break;
        }
        else
            return false;   
    }
    if (Q[current] == qf && it >= (int)word.size()-1)
            return true;
    
    return false; 

}

void NFA::setJoker (int stateCount)
{
    char symb;
    for (int i = 0; (symb = sigma.getSymbol (i)) != 0; i++)
        qf->setNextState (symb, stateCount);
}

#endif