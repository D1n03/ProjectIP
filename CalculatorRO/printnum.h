#include <iostream>
#include <cstring>
using namespace std;
char FinalAns[NMAX] = "";
void printDigit(string s, int Start, int Final)
{
    switch (s[Final])
    {
    case '0':
        strcat(FinalAns, " zero");
        break;
    case '1':
        strcat(FinalAns, " unu");
        break;
    case '2':
        strcat(FinalAns, " doi");
        break;
    case '3':
        strcat(FinalAns, " trei");
        break;
    case '4':
        strcat(FinalAns, " patru");
        break;
    case '5':
        strcat(FinalAns, " cinci");
        break;
    case '6':
        strcat(FinalAns, " sase");
        break;
    case '7':
        strcat(FinalAns, " sapte");
        break;
    case '8':
        strcat(FinalAns, " opt");
        break;
    case '9':
        strcat(FinalAns, " noua");
        break;
    }
}
void printSpecialCase(string s, int Start, int Final)
{
    switch (s[Start])
    {
        case '0':
            strcat(FinalAns, "");
            break;
        case '1':
            strcat(FinalAns, " o");
            break;
        case '2':
            strcat(FinalAns, " doua");
            break;
        case '6':
            strcat(FinalAns, " sai");
    }
}
void printSpecialCase2(string s, int Start, int Final)
{
    switch (s[Start])
    {
    case '0':
        strcat(FinalAns, "");
        break;
    default:
        strcat(FinalAns, " si");
        printDigit(s, Start, Start);
        break;
    }
}
void printDecimal(string s, int Start, int Final)
{
    if (s[Start] == '1')
    {
        switch (s[Final])
        {
        case '0':
            strcat(FinalAns, " zece");
            break;
        case '1':
            strcat(FinalAns, " unsprezece");
            break;
        case '2':
            strcat(FinalAns, " doisprezece");
            break;
        case '3':
            strcat(FinalAns, " treisprezece");
            break;
        case '4':
            strcat(FinalAns, " paisprezece");
            break;
        case '5':
            strcat(FinalAns, " cincisprezece");
            break;
        case '6':
            strcat(FinalAns, " saisprezece");
            break;
        case '7':
            strcat(FinalAns, " saptesprezece");
            break;
        case '8':
            strcat(FinalAns, " optsprezece");
            break;
        case '9':
            strcat(FinalAns, " nouasprezece");
            break;
        }
    }
    else
    {
       switch (s[Start])
        {
        case '2':
            printSpecialCase(s, Start, Start);
            strcat(FinalAns, "zeci");
            printSpecialCase2(s, Final, Final);
            break;
        case '3':
            printDigit(s, Start, Start);
            strcat(FinalAns, "zeci");
            printSpecialCase2(s, Final, Final);
            break;
        case '4':
            printDigit(s, Start, Start);
            strcat(FinalAns, "zeci");
            printSpecialCase2(s, Final, Final);
            break;
        case '5':
            printDigit(s, Start, Start);
            strcat(FinalAns, "zeci");
            printSpecialCase2(s, Final, Final);
            break;
        case '6':
            printSpecialCase(s, Start, Start);
            strcat(FinalAns, "zeci");
            printSpecialCase2(s, Final, Final);
            break;
        case '7':
            printDigit(s, Start, Start);
            strcat(FinalAns, "zeci");
            printSpecialCase2(s, Final, Final);
            break;
        case '8':
            printDigit(s, Start, Start);
            strcat(FinalAns, "zeci");
            printSpecialCase2(s, Final, Final);
            break;
        case '9':
            printDigit(s, Start, Start);
            strcat(FinalAns, "zeci");
            printSpecialCase2(s, Final, Final);
            break;
        }
    }
}
void printHundred(string s, int Start, int Final)
{
    int nonZerosPozition = Final + 1;
    /// cautam o pozitie pe care nu se afla zero | exemplu : 103
    for (int i = Start + 1; i <= Final; ++i)
        if (s[i] != '0')
        {
            nonZerosPozition = i;
            break;
        }
    if (s[Start] == '1')
    {
        printSpecialCase(s, Start, Start);
        strcat(FinalAns," suta");
    }
    else if (s[Start] == '2')
    {
        printSpecialCase(s, Start, Start);
        strcat(FinalAns," sute");
    }
    else{
        printDigit(s, Start, Start);
        strcat(FinalAns," sute");
    }
    string newS = "";
    Start = nonZerosPozition;
    for (int i = Start; i <= Final; i++)
        newS = newS + s[i];
    int new_len = newS.size();
    switch (new_len)
    {
        case 1:
            printDigit(newS, 0, new_len - 1);
            break;
        case 2:
            printDecimal(newS, 0, new_len - 1);
            break;
    }
}
void printThousand(string s, int Start, int Final)
{
    int nonZerosPozition = Final + 1;
    /// cautam o pozitie pe care nu se afla zero | exemplu : 204021
    for (int i = Start + (Final - 2); i <= Final; ++i)
        if (s[i] != '0')
        {
            nonZerosPozition = i;
            break;
        }
    switch (Final + 1)
    {
    case 4:
        if (s[Start] == '1')
        {
            printSpecialCase(s, Start, Start);
            strcat(FinalAns," mie");
        }
        else if (s[Start] == '2')
        {
            printSpecialCase(s, Start, Start);
            strcat(FinalAns," mii");
        }
        else{
            printDigit(s, Start, Start);
            strcat(FinalAns," mii");
        }
        break;
    case 5:
        if (s[Start] == '1')
        {
            printDecimal(s, Start, Start + 1);
            strcat(FinalAns," mii");
        }
        else{
            printDecimal(s, Start, Start + 1);
            strcat(FinalAns," de mii");
        }
        break;
    case 6:
         printHundred(s, Start, Start + 2);
        if (s[Start + 1] == '1' || (s[Start + 1] == '0' && s[Start + 2] != '0'))
            strcat(FinalAns," mii");
        else
            strcat(FinalAns," de mii");
        break;
    }
    string newS = "";
    Start = nonZerosPozition;
    for (int i = Start; i <= Final; ++i)
        newS = newS + s[i];
    int new_len = newS.size();
    switch (new_len)
    {
        case 1:
            printDigit(newS, 0, new_len - 1);
            break;
        case 2:
            printDecimal(newS, 0, new_len - 1);
            break;
        case 3:
            printHundred(newS, 0, new_len - 1);
            break;
    }
}
void printMillions(string s, int Start, int Final)
{
    int nonZeroPozition = Final + 1;
    /// cautam o pozitie pe care nu se afla zero | exemplu : 106320423
    for (int i = Start + (Final - 5); i <= Final; ++i)
        if (s[i] != '0')
        {
            nonZeroPozition = i;
            break;
        }
    switch (Final + 1)
    {
    case 7:
        if (s[Start] == '1')
        {
            strcat(FinalAns," un milion");
        }
        else if (s[Start] == '2')
        {
            printSpecialCase(s, Start, Start);
            strcat(FinalAns," milioane");
        }
        else{
            printDigit(s, Start, Start);
            strcat(FinalAns, " milioane");
        }
        break;
    case 8:
        if (s[Start] == '1')
        {
            printDecimal(s, Start, Start + 1);
            strcat(FinalAns," milioane");
        }
        else{
            printDecimal(s, Start, Start + 1);
            strcat(FinalAns," de milioane");
        }
        break;
    case 9:
        printHundred(s, Start, Start + 2);
        if (s[Start + 1] == '1' || (s[Start + 1] == '0' && s[Start + 2] != '0'))
            strcat(FinalAns," milioane");
        else
            strcat(FinalAns," de milioane");
        break;
    }
    string newS = "";
    Start = nonZeroPozition;
    for (int i = Start; i <= Final; ++i)
        newS = newS + s[i];
    int new_len = newS.size();
    switch (new_len)
    {
        case 1:
            printDigit(newS, 0, new_len - 1);
            break;
        case 2:
            printDecimal(newS, 0, new_len - 1);
            break;
        case 3:
            printHundred(newS, 0, new_len - 1);
            break;
        case 4:
            printThousand(newS, 0, new_len - 1);
            break;
        case 5:
            printThousand(newS, 0, new_len - 1);
            break;
        case 6:
            printThousand(newS, 0, new_len - 1);
            break;
    }
}
//pentru afisare, luam lungimea numarului nostru de tip string si in functie de valoare, stim ce cifra avem
void printNumber(string s, int len)
{
    switch (len)
    {
        case 1:
            printDigit(s, 0, len - 1);
            break;
        case 2:
            printDecimal(s, 0, len - 1);
            break;
        case 3:
            printHundred(s, 0, len - 1);
            break;
        case 4:
            printThousand(s, 0, len - 1);
            break;
        case 5:
            printThousand(s, 0, len - 1);
            break;
        case 6:
            printThousand(s, 0, len - 1);
            break;
        case 7:
            printMillions(s, 0, len - 1);
            break;
        case 8:
            printMillions(s, 0, len - 1);
            break;
        case 9:
            printMillions(s, 0, len - 1);
            break;
    }
}

