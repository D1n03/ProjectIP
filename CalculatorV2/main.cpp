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
char input[256], * ptr;
int Operator = 0, previous = 0, intermediate = 0;
int CNT, inceputa, distanta;
string number;
bool foundNumber = false;
bool VerifParanteza = false, VerifParantezaSemn = false, DupaVirg = true, zero, raport = true;
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
    //cout << inputModified;
    /// inseram in vectorul cu codificari fiecare input modificatul
    ptr = strtok(inputModified, sep);
    while (ptr)
    {
        if (isNumber(ptr))
        {
            if (strstr(ptr, "zero"))
                zero = true;
            foundNumber = true;
            million(ptr, Operator, previous, intermediate);
        }
        else
        {
            if (strstr(ptr, "+")) 
            { 
                vectorCOD[i] = '+'; i++; 
            }
            if (strstr(ptr, "-")) 
            { 
                vectorCOD[i] = '-'; i++; 
            }
            if (strstr(ptr, "*")) 
            { 
                vectorCOD[i] = '*'; i++; 
            }
            if (strstr(ptr, "/")) 
            { 
                vectorCOD[i] = '/'; i++; 
            }
            if (strcmp(ptr, "l") == 0)
            {
                vectorCOD[i] = 'l'; i++;
            }
            if (strcmp(ptr, "s") == 0) 
            {
                vectorCOD[i] = 's'; i++; 
            }
            if (strcmp(ptr, "c") == 0) 
            { 
                vectorCOD[i] = 'c'; i++; 
            }
            if (strcmp(ptr, "t") == 0) 
            { 
                vectorCOD[i] = 't'; i++; 
            }
            if (strcmp(ptr, "g") == 0) 
            { 
                vectorCOD[i] = 'g'; i++; 
            }
            if (strstr(ptr, "(")) 
            {
                vectorCOD[i] = '('; i++; 
            }
            if (strstr(ptr, ","))
                if (foundNumber) 
                { 
                    vectorCOD[i] = 'n'; i++; 
                }
            if (strstr(ptr, ")"))
            {
                VerifParanteza = true;
                VerifParantezaSemn = true;
                distanta = 1;
                if (foundNumber)
                {
                    vectorCOD[i] = 'n'; i++;
                    vectorCOD[i] = ')'; i++;
                }
                else 
                { 
                    vectorCOD[i] = ')'; i++; 
                }
            }
            //if (strstr(ptr, "?")) /// inainte trebuia sa fie spatiu intre numar si semnul intrebarii
                //if (foundNumber) { vectorCOD[i] = 'n'; i++; }
            ///DE MODIF DE AICI
            if (strstr(ptr, "plus"))
            {
                if (foundNumber)
                {
                    vectorCOD[i] = 'n'; i++;
                    vectorCOD[i] = '+'; i++;
                }
                if (VerifParantezaSemn && distanta == 1)
                {
                    vectorCOD[i] = '+'; i++;
                    VerifParantezaSemn = false; distanta = 0;
                }
                else if (distanta > 2)
                {
                    distanta = 0; VerifParantezaSemn = false;
                }
            }
            if (strstr(ptr, "minus"))
            {
                if (foundNumber)
                {
                    vectorCOD[i] = 'n'; i++;
                    vectorCOD[i] = '-'; i++;
                }
                if (VerifParantezaSemn && distanta == 1)
                {
                    vectorCOD[i] = '-'; i++;
                    VerifParantezaSemn = false; distanta = 0;
                }
                else if (distanta > 2)
                {
                    distanta = 0; VerifParantezaSemn = false;
                }
            }
            if (strstr(ptr, "ori"))
            {
                if (foundNumber)
                {
                    vectorCOD[i] = 'n'; i++;
                    vectorCOD[i] = '*'; i++;
                }
                if (VerifParantezaSemn && distanta == 1)
                {
                    vectorCOD[i] = '*'; i++;
                    VerifParantezaSemn = false; distanta = 0;
                }
                else if (distanta > 2)
                {
                    distanta = 0; VerifParantezaSemn = false;
                }
            }
            if (strstr(ptr, "impartit"))
            {
                if (foundNumber)
                {
                    vectorCOD[i] = 'n'; i++;
                    vectorCOD[i] = '/'; i++;
                }
                if (VerifParantezaSemn && distanta == 1)
                {
                    vectorCOD[i] = '/'; i++;
                    VerifParantezaSemn = false; distanta = 0;
                }
                else if (distanta > 2)
                {
                    distanta = 0; VerifParantezaSemn = false;
                }
            }
            if (strstr(ptr, "^"))
            {
                if (foundNumber)
                {
                    vectorCOD[i] = 'n'; i++; 
                    vectorCOD[i] = '^'; i++;
                    goto OutOfIf;
                }
                if (VerifParantezaSemn && distanta == 1)
                {
                    vectorCOD[i] = '^'; i++; VerifParantezaSemn = false; distanta = 0; goto OutOfIf; /// OutOfIf adica iesim din if si nu mai testam conditiile
                }
                else
                { 
                    vectorCOD[i] = '^'; i++;  
                }
            }
            OutOfIf:
            if (strstr(ptr, "cu"))
            {
                if (VerifParanteza) goto SkipPar; ///SkipPar adica omitem paranteza
                if (foundNumber) { vectorCOD[i] = 'n'; i++; }
            }
            SkipPar:
            VerifParanteza=false;
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
    if (foundNumber) { vectorCOD[i] = 'n'; i++; } /// added: mereu o sa fie un numar la urma
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
    //for (int k = 0; k < i; k++)
        //cout << vectorCOD[k] << " ";
}
/////////////////////////////////////////////////////
/// FUNCTII PENTRU CALCULAREA INPUTULUI CONVERTIT ///
/////////////////////////////////////////////////////
int CalculateInputModified()
{
    if (vectorCOD[0] == '+' || vectorCOD[0] == '-' || vectorCOD[0] == '*' || vectorCOD[0] == '/')
        number = to_string(calculate());
    else {
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
            if (current == 's') { //daca am citit functia sin
                item.type = 's';
                item.value = 0;
                StackOp.push(item); //operatia se insereaza in stiva cu operatii
                continue;
            }
            if (current == 'c') { //daca am citit functia cos
                item.type = 'c';
                item.value = 0;
                StackOp.push(item); //operatia se insereaza in stiva cu operatii
                continue;
            }
            if (current == 't') { //daca am citit functia tangenta
                item.type = 't';
                item.value = 0;
                StackOp.push(item); //operatia se insereaza in stiva cu operatii
                continue;
            }
            if (current == 'g') { //daca am citit functia cotangenta
                item.type = 'g';
                item.value = 0;
                StackOp.push(item); //operatia se insereaza in stiva cu operatii
                continue;
            }
            if (current == 'l')
            {
                item.type = 'l';
                item.value = 0;
                StackOp.push(item); //operatia se insereaza in stiva cu operatii
                continue;
            }
            if (current == 'n') { // daca am citit un numar
                value = Numbers[j]; j++;
                item.type = '0';
                item.value = value;
                StackNr.push(item); // numarul se insereaza in stiva cu numere
                continue;
            }
            if (current == '+' || current == '-' || current == '*' || current == '/' || current == '^') { // daca am citit o operatie
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
            if (current == '(') { //daca am citit paranteza deschisa
                item.type = current;
                item.value = 0;
                StackOp.push(item); //operatia se insereaza in stiva cu operatii
                continue;
            }
            if (current == ')') { //daca am citit paranteza inchisa
                while (StackOp.top().type != '(') {
                    if (CalculateInStack(StackNr, StackOp, item) == false) { //daca functia returneaza 'false' incetam calculul
                        system("pause");
                        return 0;
                    }
                    else continue; //daca totul e bine
                }
                StackOp.pop();
                continue;
            }
            else 
            { //daca am citit un caracter straniu
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
/// verificam sa vedem daca exista cazul cu perioada
bool verifyPeriod(string s, int len)
{
    for (int i = 0; i < len; ++i)
        if (s[i] == '(')
            return true;
    return false;
}
///formatam pt zero
string formatZero(string s, int len)
{
    string format = "";
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] != '0') break;
        else format += s[i];
    }
    return format;
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
///formatam dupa virgula
string formatDupaVirg(string s, int len)
{
    string formatAux = changeToInteger(s, len);
    int integerLength = formatAux.size();
    string format = "";
    for (int i = integerLength + 1; i < len; ++i)
        if (s[i] == '(') return format;
        else format += s[i];
    return format;
}
///formatam perioada
string formatPeriod(string s, int len)
{
    int pos = len;
    string format = "";
    for (int i = 0; i < len; ++i)
        if (s[i] == '(')
        {
            pos = i + 1;
            break;
        }
    for (int i = pos; i < len - 1; ++i)
        format += s[i];
    return format;
}
/// numere convertite in cuvinte
void NumbersToWords()
{
    if (number[0] == '-')
    {
        strcat(FinalAns, " minus");
        number.erase(0, 1);
    }
    int len = number.size() - 1;
    while (number[len] == '0' || number[len] == '.' || number[len] == ',') //se inlatura zerourile in plus de dupa virgula
    {
        if (number[len] == '.' || number[len] == ',')
        {
            number.erase(len, 1);
            goto Virg; // facem caz virgula
        }
        number.erase(len, 1);
        len--;
    }
    Virg:
    len = len + 1;
    string IntegerNumber = changeToInteger(number, len);
    string NumberAfterComma = formatDupaVirg(number, len);
    string period = formatPeriod(number, len);
    printNumber(IntegerNumber, IntegerNumber.size());
    if (!verifyInteger(number, len))
    {
        strcat(FinalAns, " virgula");
        int lenNumberAfterComma = NumberAfterComma.size();
        while (lenNumberAfterComma)
        {
            string zeros = formatZero(NumberAfterComma, NumberAfterComma.size());
            int lenZeros = zeros.size();
            while (lenZeros--)
                strcat(FinalAns, " zero");
            NumberAfterComma.erase(0, zeros.size());
            lenNumberAfterComma = NumberAfterComma.size();
            int lenNou = min(lenNumberAfterComma, 9);
            string nou = "";
            for (int i = 0; i < lenNou; ++i)
                nou += NumberAfterComma[i];
            printNumber(nou, nou.size());
            NumberAfterComma.erase(0, nou.size());
            lenNumberAfterComma = NumberAfterComma.size();
        }
        if (verifyPeriod(number, len))
        {
            strcat(FinalAns, " si");
            int lenNumberPeriod = period.size();
            while (lenNumberPeriod)
            {
                string zeros = formatZero(period, period.size());
                int lenZeros = zeros.size();
                while (lenZeros--)
                    strcat(FinalAns, " zero");
                period.erase(0, zeros.size());
                lenNumberPeriod = period.size();
                int lenNou = min(lenNumberPeriod, 9);
                string nou = "";
                for (int i = 0; i < lenNou; ++i)
                    nou += period[i];
                printNumber(nou, nou.size());
                period.erase(0, nou.size());
                lenNumberPeriod = period.size();
            }
            strcat(FinalAns, " in perioada");
        }
    }
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
cat scadem din 10 ca sa obtinem 3
cat scade, scazi
daca operatii din opeartii, neaparat paranteze suma dintre ( suma dintre ( diferenta dintre doi cu trei ), trei cu cinci ) -
*/