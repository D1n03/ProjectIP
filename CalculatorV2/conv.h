#include <iostream>
#include <cstring>
#include <stack>
#include <math.h>
using namespace std;
char inputModified[256] = "", sep[] = " ";
/// struct in care codificam operatiile
struct codification
{
    char type; /// 0 -> nr, + -> adunare, - -> minus
    double value; /// 0 -> operatii, valoare pt numere
};
//functiile sin, cos, tg, ctg
double Sin(double x) 
{   //rotunjim valoarea sinusului
    return (round(sin(x) * 100000000) / 100000000);
}
double Cos(double x) 
{   //rotunjim valoarea cosinusului
    return (round(cos(x) * 100000000) / 100000000);
}
double ctg(double x) 
{   //functie pt calcului cotangentei
    double a = Cos(x);
    double b = Sin(x);
    return (a / b);
}
double tg(double x) 
{   //functie pt calcului tangentei
    double a = Sin(x);
    double b = Cos(x);
    return (a / b);
}
/// functie de tip bool deoarece dorim sa returnam false cand apare o eroare
bool CalculateInStack(stack < codification >& StackNr, stack < codification >& StackOp, codification& item)
{
    double Nr1, Nr2, Rez;
    Nr1 = StackNr.top().value; //luam numarul din varful stivei
    StackNr.pop();
    switch (StackOp.top().type) // luam operatia din varful stivei
    {
    case '+': // adunare
        Nr2 = StackNr.top().value;
        StackNr.pop();
        Rez = Nr1 + Nr2;
        item.type = '0';
        item.value = Rez;
        StackNr.push(item); // inseram rezultatul inapoi in stiva
        StackOp.pop();
        break;
    case '-': // scadere
        Nr2 = StackNr.top().value;
        StackNr.pop();
        Rez = Nr2 - Nr1;
        item.type = '0';
        item.value = Rez;
        StackNr.push(item);
        StackOp.pop();
        break;

    case '*': // inmultire
        Nr2 = StackNr.top().value;
        StackNr.pop();
        Rez = Nr1 * Nr2;
        item.type = '0';
        item.value = Rez;
        StackNr.push(item);
        StackOp.pop();
        break;

    case '^': //ridicare la putere
        Nr2 = StackNr.top().value;
        StackNr.pop();
        Rez = pow(Nr2, Nr1);
        item.type = '0';
        item.value = Rez;
        StackNr.push(item);
        StackOp.pop();
        break;
    case '/': // impartire
        Nr2 = StackNr.top().value;
        if (Nr1 == 0)
        {
            cout << "Impartirea la 0 nu este posibila!" << "\n";
            return false;
        }
        else {
            StackNr.pop();
            Rez = (Nr2 / Nr1);
            item.type = '0';
            item.value = Rez;
            StackNr.push(item);
            StackOp.pop();
            break;
        }
    case 's':  //sinus
        Rez = Sin(Nr1);
        item.type = '0';
        item.value = Rez;
        StackNr.push(item);
        StackOp.pop();
        break;
    case 'c':  //cosinus
        Rez = Cos(Nr1);
        item.type = '0';
        item.value = Rez;
        StackNr.push(item);
        StackOp.pop();
        break;
    case 't':  //tangenta
        if (Cos(Nr1) == 0) {
            cerr << "\nArgument gresit pentru tangent!\n";
            return false;
        }
        else {
            Rez = tg(Nr1);
            item.type = '0';
            item.value = Rez;
            StackNr.push(item);
            StackOp.pop();
            break;
        }
    case 'g':  //cotangenta
        if (Sin(Nr1) == 0) {
            cerr << "\nArgument gresit pentru cotangent!\n";
            return false;
        }
        else {
            Rez = ctg(Nr1);
            item.type = '0';
            item.value = Rez;
            StackNr.push(item);
            StackOp.pop();
            break;
        }
    default:  //altfel, eroare
        cout << "Eroare!" << "\n";
        return false;
        break;
    }
    return true;
}
void digits(char* ptr, int& Operator, int& previous)
{
    if (strcmp(ptr, "unu") == 0)
        previous += 1;
    if (strcmp(ptr, "doi") == 0)
        previous += 2;
    if (strcmp(ptr, "doua") == 0)
        previous += 2;
    if (strcmp(ptr, "trei") == 0)
        previous += 3;
    if (strcmp(ptr, "patru") == 0)
        previous += 4;
    if (strcmp(ptr, "cinci") == 0)
        previous += 5;
    if (strcmp(ptr, "sase") == 0)
        previous += 6;
    if (strcmp(ptr, "sapte") == 0)
        previous += 7;
    if (strcmp(ptr, "opt") == 0)
        previous += 8;
    if (strcmp(ptr, "noua") == 0)
        previous += 9;
}
void decimal(char* ptr, int& Operator, int& previous)
{
    bool found = false;
    if (strcmp(ptr, "zece") == 0)
    {
        previous += 10;
        found = true;
    }
    if (strcmp(ptr, "unsprezece") == 0)
    {
        previous += 11;
        found = true;
    }
    if (strcmp(ptr, "doisprezece") == 0)
    {
        previous += 12;
        found = true;
    }
    if (strcmp(ptr, "treisprezece") == 0)
    {
        previous += 13;
        found = true;
    }
    if (strcmp(ptr, "paisprezece") == 0)
    {
        previous += 14;
        found = true;
    }
    if (strcmp(ptr, "cincisprezece") == 0)
    {
        previous += 15;
        found = true;
    }
    if (strcmp(ptr, "saisprezece") == 0)
    {
        previous += 16;
        found = true;
    }
    if (strcmp(ptr, "saptesprezece") == 0)
    {
        previous += 17;
        found = true;
    }
    if (strcmp(ptr, "optsprezece") == 0)
    {
        previous += 18;
        found = true;
    }
    if (strcmp(ptr, "nouasprezece") == 0)
    {
        previous += 19;
        found = true;
    }
    if (strcmp(ptr, "douazeci") == 0)
    {
        previous += 20;
        found = true;
    }

    if (strcmp(ptr, "treizeci") == 0)
    {
        previous += 30;
        found = true;
    }
    if (strcmp(ptr, "patruzeci") == 0)
    {
        previous += 40;
        found = true;
    }
    if (strcmp(ptr, "cincizeci") == 0)
    {
        previous += 50;
        found = true;
    }
    if (strcmp(ptr, "saizeci") == 0)
    {
        previous += 60;
        found = true;
    }
    if (strcmp(ptr, "saptezeci") == 0)
    {
        previous += 70;
        found = true;
    }
    if (strcmp(ptr, "optzeci") == 0)
    {
        previous += 80;
        found = true;
    }
    if (strcmp(ptr, "nouazeci") == 0)
    {
        previous += 90;
        found = true;
    }
    if (!found)
        digits(ptr, Operator, previous);
}
void hundred(char* ptr, int& Operator, int& previous, int& intermediate)
{
    bool found = false;
    if (strcmp(ptr, "suta") == 0)
    {
        intermediate = 100;
        found = true;
        previous = 0;
    }
    if (strcmp(ptr, "sute") == 0)
    {
        intermediate = previous * 100;
        found = true;
        previous = 0;
    }
    if (!found)
        decimal(ptr, Operator, previous);
}
void thousand(char* ptr, int& Operator, int& previous, int& intermediate)
{
    bool found = false;
    if (strcmp(ptr, "mie") == 0)
    {
        Operator = Operator + 1000;
        found = true;
    }
    if (strcmp(ptr, "mii") == 0 && intermediate != 0 || strcmp(ptr, "mii") == 0 && previous != 0)
    {
        if (previous != 0)
        {
            intermediate += previous;
            previous = 0;
        }
        Operator += intermediate * 1000;
        intermediate = 0;
        found = true;
    }
    if (!found)
        hundred(ptr, Operator, previous, intermediate);
}
void million(char* ptr, int& Operator, int& previous, int& intermediate)
{
    bool found = false;
    if (strcmp(ptr, "milion") == 0)
    {
        Operator += 1000000;
        found = true;
    }
    if (strcmp(ptr, "milioane") == 0 && intermediate != 0 || strcmp(ptr, "milioane") == 0 && previous != 0)
    {
        if (previous != 0)
        {
            intermediate += previous;
            previous = 0;
        }
        Operator += intermediate * 1000000;
        found = true;
        intermediate = 0;
    }
    if (!found)
        thousand(ptr, Operator, previous, intermediate);
}
bool isNumber(char* ptr)
{
    if (strstr(ptr, "unu") || strstr(ptr, "doi") || strstr(ptr, "trei") || strstr(ptr, "patru") || strstr(ptr, "cinci") || strstr(ptr, "sase") || strstr(ptr, "sapte") || strstr(ptr, "opt") || strstr(ptr, "noua") ||
        strstr(ptr, "zero") || strstr(ptr, "doua") || strstr(ptr, "zece") || strstr(ptr, "douazeci") || strstr(ptr, "treizeci") || strstr(ptr, "patruzeci") || strstr(ptr, "cincizeci") || strstr(ptr, "saizeci") ||
        strstr(ptr, "saptezeci") || strstr(ptr, "optzeci") || strstr(ptr, "nouazeci") || strstr(ptr, "sut") || strstr(ptr, "mie") || strstr(ptr, "mii") || strstr(ptr, "milion") || strstr(ptr, "milioane") ||
        strstr(ptr, "unsprezece") || strstr(ptr, "doisprezece") || strstr(ptr, "treisprezece") || strstr(ptr, "paisprezece") || strstr(ptr, "cincisprezece") || strstr(ptr, "saisprezece") ||
        strstr(ptr, "saptesprezece") || strstr(ptr, "optsprezece") || strstr(ptr, "nouasprezece"))
        return true;
    return false;
}
int charToInt(char* ptr)
{
    int num = 0;
    for (int i = 0; i < strlen(ptr); i++)
    {
        int digit = ptr[i] - '0';
        num = num * 10 + digit;
    }
    return num;

}
/// implementare numar scris normal ca input de tip char, in numar in romana
void IntegerIntoWord(int numar, char rez[200])
{
    int ok, ok1, ok2, ok3, stanga, rest;
    ok = 0;
    ok1 = 1;
    ok2 = 1;
    ok3 = 1;
    char cazuri[30][50] = { "","unu ","doua ","trei ","patru ","cinci ","sase ","sapte ","opt ","noua ","zeci ",
                      "unsprezece ","douasprezece ","treisprezece ","paisprezece ","cincisprezece ",
                      "saisprezece ","saptesprezece ","optsprezece ","nouasprezece ","douazeci ",
                      "treizeci ","patruzeci ","cincizeci ","saizeci ","saptezeci ","optzeci ","nouazeci " };
    ///caz special zero
    if (!numar)
        strcat(rez, "zero ");
    ///egal cu o suta milioane
    if (numar == 100000000)
    {
        strcat(rez, "o suta de milioane ");
        stanga = numar / 100000000;
        ok1 = 0;
    }
    if (ok1) {
        ///10 milioane
        if (numar >= 10000000)
        {
            stanga = numar / 1000000;
            if (stanga == 10)
            {
                strcat(rez, "zece milioane ");
            }
            else if (stanga > 10 && stanga < 20)
            {
                strcat(rez, cazuri[stanga]);
                strcat(rez, "milioane ");
            }
            else if (stanga == 20)
            {
                strcat(rez, cazuri[stanga]);
                strcat(rez, "de milioane ");
            }
            else if (stanga > 20)
            {
                rest = numar / 1000000;
                if (rest % 10 == 0)
                {
                    strcat(rez, cazuri[18 + rest / 10]);
                    strcat(rez, "de milioane ");
                }
                else
                {
                    strcat(rez, cazuri[18 + rest / 10]);
                    strcat(rez, "si ");
                    strcat(rez, cazuri[rest % 10]);
                    strcat(rez, "de milioane ");
                }
            }
            numar = numar - stanga * 1000000;
            ok3 = 0;
        }
        if (numar >= 1000000 && ok3)
        {
            stanga = numar / 1000000;
            if (stanga == 1)
            {
                strcat(rez, "un milion ");
            }
            else
            {
                strcat(rez, cazuri[stanga]);
                strcat(rez, "milioane ");
            }
            numar -= stanga * 1000000;
        }
        ///100 de mii
        if (numar >= 100000)
        {
            stanga = numar / 100000;
            if (numar / 10000 % 10 != 0)
            {
                if (stanga == 1)
                {
                    strcat(rez, "o suta ");
                }
                else
                {
                    strcat(rez, cazuri[stanga]);
                    strcat(rez, "sute ");
                }
            }
            else
            {
                if (stanga == 1)
                {
                    strcat(rez, "o suta de mii ");
                }
                else
                {
                    strcat(rez, cazuri[stanga]);
                    strcat(rez, "sute de mii ");
                }
            }
            numar -= stanga * 100000;
        }
        ///10 mii
        if (numar >= 10000)
        {
            stanga = numar / 1000;
            if (stanga == 10)
            {
                strcat(rez, "zece mii ");
            }
            else if (stanga > 10 && stanga < 20)
            {
                strcat(rez, cazuri[stanga]);
                strcat(rez, "mii ");
            }
            else if (stanga == 20)
            {
                strcat(rez, cazuri[stanga]);
                strcat(rez, "de mii ");
            }
            else if (stanga > 20)
            {
                rest = numar / 1000;
                if (rest % 10 == 0)
                {
                    strcat(rez, cazuri[18 + rest / 10]);
                    strcat(rez, "de mii ");
                }
                else
                {
                    strcat(rez, cazuri[18 + rest / 10]);
                    strcat(rez, "si ");
                    strcat(rez, cazuri[rest % 10]);
                    strcat(rez, "de mii ");
                }
            }
            numar -= stanga * 1000;
            ok2 = 0;
        }
        ///mii
        if (numar >= 1000 && ok2)
        {
            stanga = numar / 1000;

            if (stanga == 1)
            {
                strcat(rez, "o mie ");
            }
            else
            {
                strcat(rez, cazuri[stanga]);
                strcat(rez, "mii ");
            }
            numar -= stanga * 1000;
        }
        ///sute
        if (numar >= 100)
        {
            stanga = numar / 100;
            if (stanga == 1)
            {
                strcat(rez, "o suta ");
            }
            else
            {
                strcat(rez, cazuri[stanga]);
                strcat(rez, "sute ");
            }
            numar -= stanga * 100;
        }
        if (numar >= 20)
        {
            stanga = numar / 10;
            strcat(rez, cazuri[18 + stanga]);
            ok = 1;
            numar -= stanga * 10;
        }
        if (ok)
        {
            if (numar == 2)
                strcat(rez, "si doi ");
            else if (numar == 10)
                strcat(rez, "zece ");
            else if (numar != 0 && numar != 2 && numar != 10)
                strcat(rez, "si ");
            strcat(rez, cazuri[numar]);
        }
        if (!ok)
        {
            if (numar == 2)
                strcat(rez, "doi ");
            else if (numar == 10)
                strcat(rez, "zece ");
            else if (numar != 0 && numar != 2)
                strcat(rez, cazuri[numar]);
        }
    }
}
void extractOnlyTheUsefulWords(char* ptr) /// inlaturam cuvintele inutile din propozitie
{
    if (strstr(ptr, "suma") || strstr(ptr, "adunat") || strstr(ptr, "adunarea") || strstr(ptr, "adunarii") || strstr(ptr, "sumei"))
        strcat(inputModified, "+");
    if (strstr(ptr, "plus") || strstr(ptr, "adunat"))
        strcat(inputModified, "plus");
    if (strstr(ptr, "scader") || strstr(ptr, "-") || strstr(ptr, "diferenta") || strstr(ptr, "diferentei") || strstr(ptr, "scad"))
        strcat(inputModified, "-");
    if (strstr(ptr, "minus"))
        strcat(inputModified, "minus");
    if (strstr(ptr, "produs") || strstr(ptr, "inmultir"))
        strcat(inputModified, "*");
    if (strstr(ptr, "inmultit") || strstr(ptr, "ori"))//dupa cuvantul "inmultit" se va pune cuvantul "la"
        strcat(inputModified, "ori");
    if (strstr(ptr, "putere") || strstr(ptr, "la a")) ///pentru "la a" ?
        strcat(inputModified, "^");
    if (strstr(ptr, "raport") || strstr(ptr, "impartirea") || strstr(ptr, "impartirei") || strstr(ptr, "impartirii") || strstr(ptr, "impartim"))
        strcat(inputModified, "/");
    if (strstr(ptr, "impartit"))
        strcat(inputModified, "impartit");
    if (strstr(ptr, "sin"))
        strcat(inputModified, "s");
    if (strstr(ptr, "cos"))
        strcat(inputModified, "c");
    if (strstr(ptr, "tan"))
        strcat(inputModified, "t");
    if (strstr(ptr, "cot"))
        strcat(inputModified, "g");
    if (strstr(ptr, "("))
        strcat(inputModified, "(");
    if (strstr(ptr, ")"))
        strcat(inputModified, ")");
    if (isNumber(ptr) || strstr(ptr, "cu"))
    {
        if (strstr(ptr, ","))
        {
            ptr[strlen(ptr) - 1] = '\0';
            strcat(inputModified, ptr);
            strcat(inputModified, sep);
            strcat(inputModified, ",");
            strcat(inputModified, sep);
        }
        else strcat(inputModified, ptr);
    }
    if (ptr[0] >= '0' && ptr[0] <= '9')
    {
        int newNumber = charToInt(ptr);
        char changedS[200] = "";
        IntegerIntoWord(newNumber, changedS);
        strcat(inputModified, changedS);
    }
    //if (strstr(ptr, "?"))
        //strcat(inputModified, "?");
    strcat(inputModified, sep);
}