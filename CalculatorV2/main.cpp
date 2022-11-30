#include <iostream>
#include <cstring>
#include <stack>
#include <math.h>
#include <graphics.h>
#include <winbgim.h>
#include "printnum.h"
#include "conv.h"
#include "calculate.h"

using namespace std;

char input[256], *ptr;
int Operator = 0, previous = 0, intermediate = 0;
int CNT;
string number;
bool zero, foundNumber = false;

stack < codification > StackNr; // stiva pentru numere
stack < codification > StackOp; // stiva pentru opeartii
codification item;

////////////////////////////////////////////////////////////
///FUNCTII PENTRU CONVERTIREA INPUTULUI PENTRU PRELUCRARE///
////////////////////////////////////////////////////////////

void WordsToNumbers()
{
    ///Luam inputul cuvant cu cuvant si le ignoram pe cele inutile
    ptr = strtok(input, sep);
    while (ptr)
    {
        /// pentru cazul in care semnul intrebarii este legat de ultimul numar
        if (ptr[strlen(ptr) - 1] == '?')
            ptr[strlen(ptr) - 1] = '\0';
        extractOnlyTheUsefulWords(ptr);
        ptr = strtok(NULL, sep);
    }
    /// inseram in vectorul cu codificari fiecare input modificatul
    ptr = strtok(inputModified, sep);
    while (ptr)
    {
        if (isNumber(ptr))
            {
                if (strstr (ptr,"zero"))
                    zero = true;
                foundNumber = true;
                million(ptr, Operator, previous, intermediate);
            }
            else
            {
                if (strstr(ptr, "+")) { vectorCOD[i] = '+'; i++; }
                if (strstr(ptr, "-")) { vectorCOD[i] = '-'; i++; }
                if (strstr(ptr, "*")) { vectorCOD[i] = '*'; i++; }
                if (strstr(ptr, "/")) { vectorCOD[i] = '/'; i++; }
                if (strstr(ptr, ","))
                    if (foundNumber) { vectorCOD[i] = 'n'; i++; }
                //if (strstr(ptr, "?")) /// inainte trebuia sa fie spatiu intre numar si semnul intrebarii
                    //if (foundNumber) { vectorCOD[i] = 'n'; i++; }
                if (strstr(ptr, "plus"))
                {
                    if (foundNumber)
                    {
                        vectorCOD[i] = 'n'; i++;
                        vectorCOD[i] = '+'; i++;
                    }
                }
                if (strstr(ptr, "minus"))
                {
                    if (foundNumber)
                    {
                        vectorCOD[i] = 'n'; i++;
                        vectorCOD[i] = '-'; i++;
                    }
                }
                if (strstr(ptr, "ori"))
                {
                    if (foundNumber)
                    {
                        vectorCOD[i] = 'n'; i++;
                        vectorCOD[i] = '*'; i++;
                    }
                }
                if (strstr(ptr, "impartit"))
                {
                    if (foundNumber)
                    {
                        vectorCOD[i] = 'n'; i++;
                        vectorCOD[i] = '/'; i++;
                    }
                }
                if (strstr(ptr, "cu"))
                {
                    if (foundNumber) { vectorCOD[i] = 'n'; i++; }
                }
                //VerificareParanteza=false;
                foundNumber = false;
                if (previous != 0)
                    Operator += previous;
                if (intermediate != 0)
                    Operator += intermediate;
                if (Operator != 0 || zero)
                {
                    zero = false;
                    Numbers[CNT] = Operator;
                    CNT++;
                    Operator = 0;
                    previous = 0;
                    intermediate = 0;
                }
            }
            ptr = strtok(NULL, sep);
    }
    if (foundNumber) { vectorCOD[i] = 'n'; i++; } /// addeed: mereu o sa fie un numar la urma
    if (previous != 0)
        Operator += previous;
    if (intermediate != 0)
        Operator += intermediate;
    if (Operator != 0 || zero)
    {
        zero = false;
        Numbers[CNT] = Operator;
        CNT++;
        Operator = 0;
        previous = 0;
        intermediate = 0;
    }
}

/////////////////////////////////////////////////////
/// FUNCTII PENTRU CALCULAREA INPUTULUI CONVERTIT ///
/////////////////////////////////////////////////////

int CalculateInputModified()
{
    if (vectorCOD[0] == '+' || vectorCOD[0] == '-' || vectorCOD[0] == '*' || vectorCOD[0] == '/')
        number = to_string(calculate());
    else{
        i = 0; j = 0;
        char current; //variabila in care se inscrie caracterul curent prelucrat
        double value; // valoarea

        while (true)
        {
            current = vectorCOD[i]; i++; // verificam primul simbol
            if (current == '\n')
                break; // daca ajungem la sfarsitul randului iesim din while
            if (current == ' ')  // ignorarea spatiilor
                continue;

            if (current == 'n') { // daca am citit un numar
                value = Numbers[j]; j++;
                item.type = '0';
                item.value = value;
                StackNr.push(item); // numarul se insereaza in stiva cu numere
                continue;
            }
            if (current == '+' || current == '-' || current == '*' || current == '/') { // daca am citit o operatie
                if (StackOp.size() == 0) { // daca stiva cu operatii este vida
                    item.type = current;
                    item.value = 0;
                    StackOp.push(item); // operatia se insereaza in stiva cu operatii
                    continue;
                }
                if (StackOp.size() != 0 && getPriority(current) > getPriority(StackOp.top().type)) { // daca stiva nu este vida, insa prioritatea operatiei curente este mai mare decat cea din varful stivei
                    item.type = current;
                    item.value = 0;
                    StackOp.push(item); // operatia se insereaza in stiva cu operatii
                    continue;
                }
                if (StackOp.size() != 0 && getPriority(current) <= getPriority(StackOp.top().type)) { // daca stiva nu este vida, insa prioritatea operatiei curente e mai mica sau egala cu cea din varful stivei
                    if (CalculateInStack(StackNr, StackOp, item) == false) { // daca funtia returneaza 'false' incetam lucrul
                        system("pause");
                        return 0;
                    }
                    item.type = current;
                    item.value = 0;
                    StackOp.push(item); // operatia se insereaza in stiva cu operatii
                    continue;
                }
            }
            else { //daca am citit un caracter straniu
                break;
            }
        }
        while (StackOp.size() != 0) //apelam functia matematica pana cand in stiva cu operatii nu raman 0 elemente
        {
            if (CalculateInStack(StackNr, StackOp, item) == false) //daca functia returneaza 'false' incetam calculul
            {
                system("pause");
                return 0;
            }
            else continue; //daca totul e bine
        }
        number = to_string(StackNr.top().value);
    }
}

////////////////////////////////////////////////////////
/// FUNCTII PENTRU CONVERTIREA DIN NUMERE IN CUVINTE ///
////////////////////////////////////////////////////////


/// verificam mai intai sa vedem daca este intreg
bool verifyInteger(string s, int len)
{
    for (int i = 0; i < len; ++i)
        if (s[i] == ',' || s[i] == '.')
            return false;
    return true;
}
/// convertim in numar intreg rezultatul
string changeToInteger(string s, int len)
{
    if (verifyInteger(s, len))
        return s;
    string format = "";
    for (int i = 0; i < len; ++i)
        if (s[i] == '.' || s[i] == ',')
            return format;
        else format += s[i];
}

void NumbersToWords()
{
    /// implementare minus mai tarziu

    int len = number.size() - 1;
    string IntegerNumber = changeToInteger(number, len);
    printNumber(IntegerNumber, IntegerNumber.size()); //printnum.h
}

int main()
{
    cout << "Introduceti intrebarea: ";
    cin.getline(input, 256);

    /// convertim inputul in litere mici
    for (int i = 0; i < strlen(input); i++)
        input[i] = tolower(input[i]);

    WordsToNumbers(); /// functie care converteste inputul
    CalculateInputModified(); /// functie care calculeaza inputul modificat
    NumbersToWords(); /// functie care converteste rezultatul inapoi

    /// pentru ans = true, se afiseaza rezultatul, in caz contrar, avem o eroare, cazul cu impartirea la zero
    if (ans == true)
        cout << "Rezultatul: " << FinalAns << "\n";

    return 0;
}

/*
TO DO:
-Implemenetare paranteze pentru ordinea opeartiilor astefel incat sa putem aplica alte functii, numere negative
-Implemenetare functii : cos, sin, tg, ctg, ^ (pow) (posibil log)
-Implementare meniu (rules, start, select language)
-Implementare calculator in limba engleza
cat scadem din 10 ca sa obtinem 3
cat scade, scazi
*/
