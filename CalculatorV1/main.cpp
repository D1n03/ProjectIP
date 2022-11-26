#include <iostream>
#include <cstring>
#include <stack>
#include <math.h>

using namespace std;

/// struct in care codificam operatiile
struct codification
{
    char type; /// 0 -> nr, + -> adunare, - -> minus
    int value; /// 0 -> operatii, valoare pt numere
};

char input[256], inputModified[256] = "", *ptr, vectorCOD[101] = "";
char FinalAns[256], sep[] = " ";
int Numbers[101], cnt1, cnt2, HowManyZeros, Operator = 0, previous = 0, intermediate = 0, i, j;
int CNT;
string number;
bool ans = true, zero, foundNumber = false;

stack < codification > StackNr; // stiva pentru numere
stack < codification > StackOp; // stiva pentru opeartii
codification item;

////////////////////////////////////////////////////////////
///FUNCTII PENTRU CONVERTIREA INPUTULUI PENTRU PRELUCRARE///
////////////////////////////////////////////////////////////

/// functie de tip bool deoarece dorim sa returnam false cand apare o eroare
bool CalculateInStack(stack < codification > & StackNr, stack < codification > & StackOp, codification & item)
{
    double Nr1, Nr2, Rez;
    Nr1 = StackNr.top().value; //luam numarul din varful stivei
    StackNr.pop();
    switch(StackOp.top().type) // luam operatia din varful stivei
    {
    case '+' : // adunare
        Nr2 = StackNr.top().value;
        StackNr.pop();
        Rez = Nr1 + Nr2;
        item.type = '0';
        item.value = Rez;
        StackNr.push(item); // inseram rezultatul inapoi in stiva
        StackOp.pop();
        break;

    case '-' : // scadere
        Nr2 = StackNr.top().value;
        StackNr.pop();
        Rez = Nr2 - Nr1;
        item.type = '0';
        item.value = Rez;
        StackNr.push(item);
        StackOp.pop();
        break;

    case '*' : // inmultire
        Nr2 = StackNr.top().value;
        StackNr.pop();
        Rez = Nr1 * Nr2;
        item.type = '0';
        item.value = Rez;
        StackNr.push(item);
        StackOp.pop();
        break;

    case '/' : // impartire
        Nr2 = StackNr.top().value;
        if (Nr1 == 0)
        {
            cout << "Impartirea la 0 nu este posibila!" << "\n";
            return false;
        }
        else{
            StackNr.pop();
            Rez = (Nr2 / Nr1);
            item.type = '0';
            item.value = Rez;
            StackNr.push(item);
            StackOp.pop();
            break;
            }
    default:
        cout << "Eroare!" << "\n";
        return false;
        break;
    }
    return true;
}

void digits(char *ptr, int &Operator, int &previous)
{
    if (strcmp(ptr,"unu") == 0)
        previous += 1;

    if (strcmp(ptr,"doi") == 0)
        previous += 2;

    if (strcmp(ptr,"doua") == 0)
        previous += 2;

    if (strcmp(ptr,"trei") == 0)
        previous += 3;

    if (strcmp(ptr,"patru") == 0)
        previous += 4;

    if (strcmp(ptr,"cinci") == 0)
        previous += 5;

    if (strcmp(ptr,"sase") == 0)
        previous += 6;

    if (strcmp(ptr,"sapte") == 0)
        previous += 7;

    if (strcmp(ptr,"opt") == 0)
        previous += 8;

    if (strcmp(ptr,"noua") == 0)
        previous += 9;
}

void decimal(char*ptr, int &Operator, int &previous)
{
    bool found = false;
    if (strcmp(ptr,"zece") == 0)
    {
        previous += 10;
        found = true;
    }

    if (strcmp(ptr,"unsprezece") == 0)
    {
        previous += 11;
        found = true;
    }

    if (strcmp(ptr,"doisprezece") == 0)
    {
        previous += 12;
        found = true;
    }

    if (strcmp(ptr,"treisprezece") == 0)
    {
        previous += 13;
        found = true;
    }

    if (strcmp(ptr,"paisprezece") == 0)
    {
        previous += 14;
        found = true;
    }

    if (strcmp(ptr,"cincisprezece") == 0)
    {
        previous += 15;
        found = true;
    }

    if (strcmp(ptr,"saisprezece") == 0)
    {
        previous += 16;
        found = true;
    }

    if (strcmp(ptr,"saptesprezece") == 0)
    {
        previous += 17;
        found = true;
    }

    if (strcmp(ptr,"optsprezece") == 0)
    {
        previous += 18;
        found = true;
    }

    if (strcmp(ptr,"nouasprezece") == 0)
    {
        previous += 19;
        found = true;
    }

    if (strcmp(ptr,"douazeci") == 0)
    {
        previous += 20;
        found = true;
    }

    if (strcmp(ptr,"treizeci") == 0)
    {
        previous += 30;
        found = true;
    }

    if (strcmp(ptr,"patruzeci") == 0)
    {
        previous += 40;
        found = true;
    }

    if (strcmp(ptr,"cincizeci") == 0)
    {
        previous += 50;
        found = true;
    }

    if (strcmp(ptr,"saizeci") == 0)
    {
        previous += 60;
        found = true;
    }

    if (strcmp(ptr,"saptezeci") == 0)
    {
        previous += 70;
        found = true;
    }

    if (strcmp(ptr,"optzeci") == 0)
    {
        previous += 80;
        found = true;
    }
    if (strcmp(ptr,"nouazeci") == 0)
    {
        previous += 90;
        found = true;
    }
    if (!found)
        digits(ptr,Operator,previous);
}


void hundred(char *ptr, int &Operator, int &previous, int &intermediate)
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
        decimal(ptr,Operator,previous);
}

void thousand(char *ptr, int &Operator, int &previous, int &intermediate)
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

void million(char *ptr, int &Operator,int &previous, int &intermediate)
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

bool isNumber(char *ptr)
{
    if (strstr(ptr,"unu") || strstr(ptr,"doi") || strstr(ptr,"trei") || strstr(ptr,"patru") || strstr(ptr,"cinci")||strstr(ptr,"sase")||strstr(ptr,"sapte")||strstr(ptr,"opt")||strstr(ptr,"noua")||
        strstr(ptr,"zero")||strstr(ptr,"doua")||strstr(ptr,"zece")||strstr(ptr,"douazeci")||strstr(ptr,"treizeci")||strstr(ptr,"patruzeci")||strstr(ptr,"cincizeci")||strstr(ptr,"saizeci")||
        strstr(ptr,"saptezeci")||strstr(ptr,"optzeci")||strstr(ptr,"nouazeci")||strstr(ptr,"sut")||strstr(ptr,"mie")||strstr(ptr,"mii")||strstr(ptr,"milion")||strstr(ptr,"milioane")||
        strstr(ptr,"unsprezece")||strstr(ptr,"doisprezece")||strstr(ptr,"treisprezece")||strstr(ptr,"paisprezece")||strstr(ptr,"cincisprezece")||strstr(ptr,"saisprezece")||
        strstr(ptr,"saptesprezece") || strstr(ptr,"optsprezece") || strstr(ptr,"nouasprezece"))
            return true;
    return false;
}

/// implementare numar in arab ca input in numar in romana
void IntegerIntoWord(char *ptr)
{
    cout << "numar";
}

void extractOnlyTheUsefulWords(char *ptr) /// inlaturam cuvintele inutile din propozitie
{
    if (strstr(ptr,"suma") || strstr(ptr,"adunat") || strstr(ptr,"adunarea") || strstr(ptr,"adunarii") || strstr(ptr,"sumei"))
        strcat(inputModified,"+");

    if (strstr(ptr,"plus") || strstr(ptr,"adunat"))
        strcat(inputModified,"plus");

    if (strstr(ptr,"scader") || strstr(ptr,"-") || strstr(ptr,"diferenta") || strstr(ptr,"diferentei"))
        strcat(inputModified,"-");

    if (strstr(ptr,"minus"))
        strcat(inputModified,"minus");

    if (strstr(ptr,"produs") || strstr(ptr,"inmultir"))
        strcat(inputModified,"*");

    if (strstr(ptr,"inmultit") || strstr(ptr,"ori"))//dupa cuvantul "inmultit" se va pune cuvantul "la"
        strcat(inputModified,"ori");

    if (strstr(ptr,"raport") || strstr(ptr,"impartirea") || strstr(ptr,"impartirei") || strstr(ptr,"impartirii"))
        strcat(inputModified,"/");

    if (strstr(ptr,"impartit"))
        strcat(inputModified,"impartit");

    if (isNumber(ptr) || strstr(ptr,"cu"))
    {
        if (strstr(ptr,","))
        {
            ptr[strlen(ptr) - 1] = NULL;
            strcat(inputModified, ptr);
            strcat(inputModified, sep);
            strcat(inputModified, ",");
            strcat(inputModified, sep);
            }
            else strcat(inputModified, ptr);
        }
    //IntegerIntoWord(ptr)
    if (strstr(ptr, "?"))
        strcat(inputModified, "?");

    strcat(inputModified, sep);
}


void WordsToNumbers()
{
    ///Luam inputul cuvant cu cuvant si le ignoram pe cele inutile
    ptr = strtok(input, sep);
    while (ptr)
    {
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
                if (strstr(ptr, "?"))
                    if (foundNumber) { vectorCOD[i] = 'n'; i++; }
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

int getRang(char current)  //functia returneaza prioritatea operatiei: 1 pt adunare si scadere, 2 pt inmultire si impartire, etc.
{
	if (current == '+' || current == '-')
        return 1;
	if (current == '*' || current == '/')
        return 2;
	else return 0;
}

double calculate()
{
    double nr = -1, res_divison;
    bool first = true;
    while(cnt1 < i)
    {
        if (vectorCOD[cnt1] == '+')
        {
            cnt1++;
            if (vectorCOD[cnt1] == 'n')
            {
                nr = Numbers[cnt2];
                cnt1++;
                cnt2++;
                //IesireSuma:
                while (vectorCOD[cnt1] == 'n')
                {
                    nr += Numbers[cnt2];
                    cnt1++;
                    cnt2++;
                }
            }
            return nr;
        }
        if (vectorCOD[cnt1] == '-')
        {
            cnt1++;
            if (vectorCOD[cnt1] == 'n')
            {
                nr=Numbers[cnt2];
                cnt1++;
                cnt2++;
                //IesireDiferenta:
                while (vectorCOD[cnt1] == 'n')
                {
                    nr -= Numbers[cnt2];
                    cnt1++;
                    cnt2++;
                }
            }
            return nr;
        }
        if (vectorCOD[cnt1] == '*')
        {
            cnt1++;
            if (vectorCOD[cnt1] == 'n')
            {
                nr = Numbers[cnt2];
                cnt1++;
                cnt2++;
                //IesireProdus:
                while (vectorCOD[cnt1] == 'n')
                {
                    nr *= Numbers[cnt2];
                    cnt1++;
                    cnt2++;
                }
            }
            return nr;
        }
        if (vectorCOD[cnt1] == '/')
        {
            cnt1++;
            if (vectorCOD[cnt1] == 'n')
            {
                nr = Numbers[cnt2];
                cnt1++;
                cnt2++;
                //IesireRaport:
                while (vectorCOD[cnt1]=='n')
                {
                    if (Numbers[cnt2]==0 && HowManyZeros==0)
                    {
                        cout << "Nu este posibila impartirea la 0";
                        ans = false;
                        HowManyZeros++;
                    }
                    nr /= Numbers[cnt2];
                    cnt1++;
                    cnt2++;
                    }
                }
                return nr;
            }
        }
}

int CalculateInputModified()
{
    if (vectorCOD[0] == '+' || vectorCOD[0] == '-' || vectorCOD[0] == '*' || vectorCOD[0] == '/')
    {
        number = to_string(calculate());
    }
    else{
    i = 0; j = 0;
    char current; //variabila in care se inscrie caracterul curent prelucrat
	double value; // valoarea

	while (1) {
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
			if (StackOp.size() != 0 && getRang(current) > getRang(StackOp.top().type)) { // daca stiva nu este vida, insa prioritatea operatiei curente este mai mare decat cea din varful stivei
				item.type = current;
				item.value = 0;
				StackOp.push(item); // operatia se insereaza in stiva cu operatii
				continue;
			}
			if (StackOp.size() != 0 && getRang(current) <= getRang(StackOp.top().type)) { // daca stiva nu este vida, insa prioritatea operatiei curente e mai mica sau egala cu cea din varful stivei
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

bool verifyInteger(string s, int len)
{
    for (int i = 0; i < len; ++i)
        if (s[i] == ',' || s[i] == '.')
            return false;
    return true;
}

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
    /// cautam o pozitie pe care nu se afla zero | exemplu : 100021
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
    /// cautam o pozitie pe care nu se afla zero | exemplu : 100320423
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

void NumbersToWords()
{
    /// implementare minus aici

    int len = number.size() - 1;
    string IntegerNumber = changeToInteger(number, len);
    printNumber(IntegerNumber, IntegerNumber.size());
}

int main()
{
    cout << "Introduceti intrebarea: ";
    cin.getline(input, 256);

    // convertim inputul in litere mici
    for (int i = 0; i < strlen(input); i++)
        input[i] = tolower(input[i]);

    WordsToNumbers(); /// functie care converteste inputul
    CalculateInputModified(); /// functie care calculeaza inputul modificat
    NumbersToWords(); /// functie care converteste rezultatul inapoi

    /// pentru ans = true, se afiseaza rezultatul, in caz contrar, avem o eroare
    if (ans)
        cout << "Rezultatul: " << FinalAns << "\n";

    return 0;
}
