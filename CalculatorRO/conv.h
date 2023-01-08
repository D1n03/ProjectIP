#include <iostream>
#include <cstring>
#include <stack>
#include <math.h>
using namespace std;
const int NMAX = 1000;
char inputModified[NMAX] = "", sep[] = " ";
bool thousands = 0;
bool millions = 0;
/// struct in care codificam operatiile pentru al doilea tip de input
struct codification
{
    char type; /// 0 -> nr, + -> adunare, - -> minus
    double value; /// 0 -> operatii, valoare pt numere
};
//functiile sin, cos, tg, ctg, log
double Sin(double x)
{   //rotunjim valoarea sinusului
    return (round(sin(x) * 100000000) / 100000000);
}
double Cos(double x)
{   //rotunjim valoarea cosinusului
    return (round(cos(x) * 100000000) / 100000000);
}
double Tan(double x)
{   //functie pt calcului tangentei
    double a = Sin(x);
    double b = Cos(x);
    return (a / b);
}
double Cot(double x)
{   //functie pt calcului cotangentei
    double a = Cos(x);
    double b = Sin(x);
    return (a / b);
}
double Log(double x)
{   //functie pt caclului log (logaritm natural)
    return(round(log(x) * 100000000) / 100000000);
}
///calculam si in acelasi timp verificam daca toate operatiile sunt valide
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
            cout << "Argument gresit pentru tangent!\n";
            return false;
        }
        else {
            Rez = Tan(Nr1);
            item.type = '0';
            item.value = Rez;
            StackNr.push(item);
            StackOp.pop();
            break;
        }
    case 'g':  //cotangenta
        if (Sin(Nr1) == 0) {
            cout << "Argument gresit pentru cotangent!\n";
            return false;
        }
        else {
            Rez = Cot(Nr1);
            item.type = '0';
            item.value = Rez;
            StackNr.push(item);
            StackOp.pop();
            break;
        }
    case 'l':  //logaritm natural
        if (Nr1 < 1) {
            cout << "Argumentul trebuie sa fie mai mare ca 1 la logaritm natural pentru ca lucram cu numere pozitive!\n";
            return false;
        }
        else {
            Rez = Log(Nr1);
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
//calculam numarul prin verificarea cuvintelor pe care le-am extras, incepem de la milioane si scade pana la unitati
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
void IntegerIntoWord(int val, bool flag, char newNS[200])
{
    char first1[20][20] = { "zero ","unu ", "doi ", "trei ","patru ","cinci ","sase ","sapte ","opt ","noua ","zece ","unsprezece ","doisprezece ","treisprezece ","paisprezece ","cincisprezece ","saisprezece ","saptesprezece ","optsprezece ","nouasprezece " };
    char first0[20][20] = { "zero ","", "doua ", "trei ","patru ","cinci ","sase ","sapte ","opt ","noua ","zece ","unsprezece ","douasprezece ","treisprezece ","paisprezece ","cincisprezece ","saisprezece ","saptesprezece ","optsprezece ","nouasprezece " };
    char second[10][20] = { " ", "zece ", "douazeci ", "treizeci ","patruzeci ","cincizeci ","saizeci ","saptezeci ","optzeci ","nouazeci " };
    if (val >= 1000000)
    {
        if (val >= 1000000 && val < 2000000)
        {
            millions = 1;
            strcat(newNS, "un milion ");
            millions = 0;
        }
        else
        {
            millions = 1;
            IntegerIntoWord(val / 1000000, 0, newNS);
            //if ((val / 10000000) % 10 >= 2 || val / 10000000 == 10)
                //strcat(newNS, "de ");
            strcat(newNS, "milioane ");
            millions = 0;
        }
        if (val % 1000000)
        {
            IntegerIntoWord(val % 1000000, 1, newNS);
        }
    }
    else if (val >= 1000)
    {
        if (val >= 1000 && val < 2000)
        {
            thousands = 1;
            IntegerIntoWord(val / 1000, 0, newNS);
            strcat(newNS, "mie ");
            thousands = 0;
        }
        else
        {
            thousands = 1;
            IntegerIntoWord(val / 1000, 0, newNS);
            //if ((val / 10000) % 10 >= 2 || (val / 1000) % 100 == 0)
                //strcat(newNS, "de ");
            strcat(newNS, "mii ");
            thousands = 0;
        }
        if (val % 1000)
        {
            IntegerIntoWord(val % 1000, 1, newNS);
        }
    }
    else if (val >= 100)
    {
        if (val >= 100 && val < 200)
        {
            IntegerIntoWord(val / 100, 0, newNS);
            strcat(newNS, "suta ");
        }
        else
        {
            IntegerIntoWord(val / 100, 0, newNS);
            strcat(newNS, "sute ");
        }
        if (val % 100)
        {
            IntegerIntoWord(val % 100, 1, newNS);
        }
    }
    else if (val >= 20)
    {
        strcat(newNS, second[val / 10]);
        if (val % 10)
        {
            //strcat(newNS, "si ");
            IntegerIntoWord(val % 10, 1, newNS);
        }
    }
    else
    {
        if (thousands == 1 || millions == 1)
        {
            strcat(newNS, first0[val]);
        }
        else if (flag == 0)
        {
            strcat(newNS, first0[val]);
        }
        else
        {
            strcat(newNS, first1[val]);
        }
    }
    return;
}
void extractOnlyTheUsefulWords(char* ptr) //inlaturam cuvintele inutile din propozitie
{
    if (strstr(ptr, "suma") || /*strstr(ptr, "adunat") ||*/ strstr(ptr, "adunarea") || strstr(ptr, "adunarii") || strstr(ptr, "sumei") || strstr(ptr, "adunam"))
        strcat(inputModified, "+");
    if (strstr(ptr, "plus") || strstr(ptr, "adunat"))
        strcat(inputModified, "plus");
    if (strstr(ptr, "scader") || strstr(ptr, "-") || strstr(ptr, "diferenta") || strstr(ptr, "diferentei") || strstr(ptr, "scad"))
        strcat(inputModified, "-");
    if (strstr(ptr, "minus") || strstr(ptr, "scazut"))
        strcat(inputModified, "minus");
    if (strstr(ptr, "produs") || strstr(ptr, "inmultir"))
        strcat(inputModified, "*");
    if (strstr(ptr, "inmultit") || strstr(ptr, "ori"))//pentru "inmultit" vom avea "la"
        strcat(inputModified, "ori");
    if (strstr(ptr, "putere") || strstr(ptr, "la a")) //pentru "la a" ?
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
    if (strstr(ptr, "logaritm") || strstr(ptr, "log") || strstr(ptr, "logaritmul"))
        strcat(inputModified, "l");
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
        bool HasComma = false;
        if (strstr(ptr, ","))
        {
            ptr[strlen(ptr) - 1] = '\0';
            HasComma = true;
        }
        int newNumber = charToInt(ptr);
        char changedS[200] = "";
        IntegerIntoWord(newNumber, 1, changedS);
        ///cout << changedS;
        strcat(inputModified, changedS);
        if (HasComma == true)
            strcat(inputModified, ",");
    }
    //if (strstr(ptr, "?"))
        //strcat(inputModified, "?");
    strcat(inputModified, sep);
}

