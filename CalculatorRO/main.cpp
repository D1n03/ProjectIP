#include <iostream>
#include <cstring>
#include <stack>
#include <math.h>
#include <graphics.h>
#include <winbgim.h>
#include "conv.h"
#include "calculate.h"
#include "printnum.h"
using namespace std;
char input[NMAX], * ptr;
int Operator = 0, previous = 0, intermediate = 0;
int CNT, dist;
string number;
bool foundNumber = false;
bool VerifParenthesis = false, VerifParenthesisSign = false, AfterComma = true, zero, raport = true;
stack < codification > StackNr; // stiva pentru numere
stack < codification > StackOp; // stiva pentru operatii
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
                VerifParenthesis = true;
                VerifParenthesisSign = true;
                dist = 1;
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
            if (strstr(ptr, "plus"))
            {
                if (foundNumber)
                {
                    vectorCOD[i] = 'n'; i++;
                    vectorCOD[i] = '+'; i++;
                }
                if (VerifParenthesisSign && dist == 1)
                {
                    vectorCOD[i] = '+'; i++;
                    VerifParenthesisSign = false;
                    dist = 0;
                }
                else if (dist > 2)
                {
                    dist = 0; VerifParenthesisSign = false;
                }
            }
            if (strstr(ptr, "minus"))
            {
                if (foundNumber)
                {
                    vectorCOD[i] = 'n'; i++;
                    vectorCOD[i] = '-'; i++;
                }
                if (VerifParenthesisSign && dist == 1)
                {
                    vectorCOD[i] = '-'; i++;
                    VerifParenthesisSign = false;
                    dist = 0;
                }
                else if (dist > 2)
                {
                    dist = 0;
                    VerifParenthesisSign = false;
                }
            }
            if (strstr(ptr, "ori"))
            {
                if (foundNumber)
                {
                    vectorCOD[i] = 'n'; i++;
                    vectorCOD[i] = '*'; i++;
                }
                if (VerifParenthesisSign && dist == 1)
                {
                    vectorCOD[i] = '*'; i++;
                    VerifParenthesisSign = false;
                    dist = 0;
                }
                else if (dist > 2)
                {
                    dist = 0;
                    VerifParenthesisSign = false;
                }
            }
            if (strstr(ptr, "impartit"))
            {
                if (foundNumber)
                {
                    vectorCOD[i] = 'n'; i++;
                    vectorCOD[i] = '/'; i++;
                }
                if (VerifParenthesisSign && dist == 1)
                {
                    vectorCOD[i] = '/'; i++;
                    VerifParenthesisSign = false;
                    dist = 0;
                }
                else if (dist > 2)
                {
                    dist = 0;
                    VerifParenthesisSign = false;
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
                if (VerifParenthesisSign && dist == 1)
                {
                    vectorCOD[i] = '^'; i++;
                    VerifParenthesisSign = false;
                    dist = 0;
                    goto OutOfIf; /// cand iesim din if si nu mai trecem prin conditii
                }
                else
                {
                    vectorCOD[i] = '^'; i++;
                }
            }
            OutOfIf:
            if (strstr(ptr, "cu"))
            {
                if (VerifParenthesis) goto SkipPar; /// trecem peste paranteza
                if (foundNumber)
                {
                    vectorCOD[i] = 'n'; i++;
                }
            }
            SkipPar:
            VerifParenthesis = false;
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
}
/////////////////////////////////////////////////////
/// FUNCTII PENTRU CALCULAREA INPUTULUI CONVERTIT ///
/////////////////////////////////////////////////////

bool IsOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return true;
    else return false;
}
int CalculateInputModified()
{
    if (IsOperator(vectorCOD[0]) && IsOperator(vectorCOD[1]))
    {
        char auxCOD[NMAX] = "";
        int p = 0, t = 2;
        auxCOD[p] = vectorCOD[0], p++;
        auxCOD[p] = '(', p++;
        auxCOD[p] = vectorCOD[1], p++;
        while (t < i)
        {
            if (vectorCOD[t] == 'n' || vectorCOD[t] == 's' || vectorCOD[t] == 'c' || vectorCOD[t] == 't' || vectorCOD[t] == 'g' || vectorCOD[t] == 'l')
            {
                while (vectorCOD[t] == 'n' || vectorCOD[t] == 's' || vectorCOD[t] == 'c' || vectorCOD[t] == 't' || vectorCOD[t] == 'g' || vectorCOD[t] == 'l')
                    auxCOD[p] = vectorCOD[t], p++, t++;
            }
            else if ((vectorCOD[t] == '+' || vectorCOD[t] == '-' || vectorCOD[t] == '*' || vectorCOD[t] == '/'))
            {
                auxCOD[p] = ')', p++;
                auxCOD[p] = '(', p++;
                auxCOD[p] = vectorCOD[t], p++, t++;
            }
        }
        auxCOD[p] = ')', p++;
        i = p;
        for (int t = 0; t < p; t++)
            vectorCOD[t] = auxCOD[t];
    }
    if (IsOperator(vectorCOD[0]))
        number = to_string(calculate());
    else {
        i = 0; j = 0;
        char current; //variabila in care se inscrie caracterul curent prelucrat
        double value; // valoarea, adica numarul in sine
        while (true)
        {
            current = vectorCOD[i]; i++; // verificam primul simbol
            if (current == '\n')
                break; // daca ajungem la finalul randului iesim din while
            if (current == ' ')  // ignoram spatiile
                continue;
            if (current == 's') { //functia sin
                item.type = 's';
                item.value = 0;
                StackOp.push(item); //operatia se insereaza in stiva cu operatii
                continue;
            }
            if (current == 'c') { //functia cos
                item.type = 'c';
                item.value = 0;
                StackOp.push(item);
                continue;
            }
            if (current == 't') { //functia tangenta
                item.type = 't';
                item.value = 0;
                StackOp.push(item);
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
///formatam pt zero
string formatZero(string s, int len)
{
    string format = "";
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] != '0')
            break;
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
string formatAfterComma(string s, int len)
{
    string formatAux = changeToInteger(s, len);
    int integerLength = formatAux.size();
    string format = "";
    for (int i = integerLength + 1; i < len; ++i)
        if (s[i] == '(')
            return format;
        else format += s[i];
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
    string NumberAfterComma = formatAfterComma(number, len);
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
            int lenNew = min(lenNumberAfterComma, 9);
            string newStr = "";
            for (int i = 0; i < lenNew; ++i)
                newStr += NumberAfterComma[i];
            printNumber(newStr, newStr.size());
            NumberAfterComma.erase(0, newStr.size());
            lenNumberAfterComma = NumberAfterComma.size();
        }
    }
}
void graphwindowINFO(int window)
{
    int x, y;
    bool click = false;
    readimagefile("Rules_and_Info.jpg", 0, 0, 800, 600);
    do{
        if(ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            x = mousex();
            y = mousey();
            if(x > 672 && x < 786 && y > 520 && y < 583)
                click = true;
        }
    }while (!click);
}
void reset()
{
    // main
    Operator = 0, previous = 0, intermediate = 0;
    CNT = 0, dist = 0;
    number.clear();
    foundNumber = false;
    VerifParenthesis = false, VerifParenthesisSign = false, AfterComma = true, zero = false, raport = true;
    // calculate
    for (int w = 0; w < NMAX; w++)
        vectorCOD[w] = 0;
    //strcpy(vectorCOD, "");
    for (int w = 0; w < NMAX; w++)
        inputModified[w] = 0;
    ///strcpy(inputModified, "");
    cnt1 = 0, cnt2 = 0, i = 0, j = 0, HowManyZeros = 0;
    for (int p = 0; p < NMAX; p++)
        Numbers[p] = 0;
    ans = true;
    // conv
    thousands = 0;
    millions = 0;
    // printnum
    FinalAns[0] = '\0';
    while (!StackNr.empty())
        StackNr.pop();
    while (!StackOp.empty())
        StackOp.pop();
}
int main()
{
    int window, x, y;
    bool click;
    window = initwindow(800, 600, "Calculator Romana");
    menu:
    readimagefile("Menu.jpg",0,0,800,600);
    do{
        if(ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            x = mousex();
            y = mousey();
            if(x > 89 && x < 296 && y > 115 && y < 190)
            {
                closegraph(window);
                click = true;
            }
            else if(x > 83 && x < 277 && y > 263 && y < 327)
            {
                graphwindowINFO(window);
                goto menu;
            }
            else if(x > 126 && x < 259 && y > 404 && y < 469)
            {
                closegraph(window);
                goto closeprogram;
            }
        }
    } while(!click);
    cout << "Pentru a iesi din program tastati: EXIT" << '\n';
    while (true)
    {
        cout << "Introduceti intrebarea: ";
        cin.getline(input, NMAX);
        if (strcmp(input, "EXIT") == 0)
            break;
        /// convertim inputul in litere mici
        for (int i = 0; i < strlen(input); i++)
            input[i] = tolower(input[i]);
        WordsToNumbers(); /// functie care converteste inputul
        CalculateInputModified(); /// functie care calculeaza inputul modificat
        NumbersToWords(); /// functie care converteste rezultatul inapoi
        /// pentru ans = true, se afiseaza rezultatul, in caz contrar, avem o eroare, cazul cu impartirea la zero etc.
        if (ans == true)
            cout << "Rezultatul: " << FinalAns << '\n';
        reset(); /// functie care reseteaza variabilele si structurile de date principale; ne permite mai multe inputuri in consola
    }
    closeprogram:
    return 0;
}
