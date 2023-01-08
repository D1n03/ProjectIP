#include <iostream>
using namespace std;
char vectorCOD[NMAX] = "";
int cnt1, cnt2, i, j, Numbers[NMAX], HowManyZeros;
bool ans = true;
int getPriority(char current)  //functia returneaza prioritatea operatiei: 1 pt adunare si scadere, 2 pt inmultire si impartire, etc.
{
    if (current == 's' || current == 'c' || current == 't' || current == 'g' || current == 'l')
        return 4;
    if (current == '^')
        return 3;
    if (current == '*' || current == '/')
        return 2;
    if (current == '+' || current == '-')
        return 1;
    else return 0;
}
bool isFunction(char ch)
{
    if (ch == 's' || ch == 'c' || ch == 't' || ch == 'g' || ch == 'l')
        return true;
    else return false;
}
double calculateFunction(char op, double x)
{
    switch (op)
    {
        case 's':
            return Sin(x);
        break;
        case 'c':
            return Cos(x);
        break;
        case 't':
            return Tan(x);
        break;
        case 'g':
            return Cot(x);
        break;
        case 'l':
            return Log(x);
        break;
    }
}
//calcularea primului tip de input, de mentionat faptul ca functiile au doar un singur numar in componenta lor
double calculate()
{
    double nr = -1e9, res_divison;
    bool first = true;
    while (cnt1 < i)
    {
        if (vectorCOD[cnt1] == '(')
        {
            cnt1++;
            calculate();
        }
        if (vectorCOD[cnt1] == '+')
        {
            cnt1++;
            Funct1:
            if (isFunction(vectorCOD[cnt1]))
            {
                if (nr == -1e9)
                    nr = calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                else nr += calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                cnt1 += 2;
                cnt2++;
                if (vectorCOD[cnt1] == 'n')
                    goto OutOfSum;
                while (isFunction(vectorCOD[cnt1]))
                {
                    nr += calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                    cnt1 += 2;
                    cnt2++;
                    if (vectorCOD[cnt1] == 'n')
                        goto OutOfSum;
                }
            }
            if (vectorCOD[cnt1] == 'n')
            {
                if (nr == -1e9)
                    nr = Numbers[cnt2];
                else nr += Numbers[cnt2];
                cnt1++;
                cnt2++;
                if (isFunction(vectorCOD[cnt1]))
                    goto Funct1;
                OutOfSum:  // iesirea din suma
                while (vectorCOD[cnt1] == 'n')
                {
                    nr += Numbers[cnt2];
                    cnt1++;
                    cnt2++;
                    if (isFunction(vectorCOD[cnt1]))
                        goto Funct1;
                }
            }
            //return nr;
            if (vectorCOD[cnt1] == '(')
            {
                if (nr == -1e9 && first)
                {
                    nr = 0;
                    first = false;
                }
                cnt1++;
                nr = nr + calculate();
                goto OutOfSum;  // iesim si nu mai continuam testele
            }
            if (vectorCOD[cnt1] == ')')
            {
                cnt1++;
                return nr;
            }
            return nr;
        }
        if (vectorCOD[cnt1] == '-')
        {
            cnt1++;
            Funct2:
            if (isFunction(vectorCOD[cnt1]))
            {
                if (nr == -1e9)
                    nr = calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                else nr -= calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                cnt1 += 2;
                cnt2++;
                if (vectorCOD[cnt1] == 'n')
                    goto OutOfDif;
                while (isFunction(vectorCOD[cnt1]))
                {
                    nr -= calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                    cnt1 += 2;
                    cnt2++;
                    if (vectorCOD[cnt1] == 'n')
                        goto OutOfDif;
                }
            }
            if (vectorCOD[cnt1] == 'n')
            {
                if (nr == -1e9)
                    nr = Numbers[cnt2];
                else nr -= Numbers[cnt2];
                cnt1++;
                cnt2++;
                if (isFunction(vectorCOD[cnt1]))
                    goto Funct2;
                OutOfDif:  // iesirea din suma
                while (vectorCOD[cnt1] == 'n')
                {
                    nr -= Numbers[cnt2];
                    cnt1++;
                    cnt2++;
                    if (isFunction(vectorCOD[cnt1]))
                        goto Funct2;
                }
            }
            //return nr;
            if (vectorCOD[cnt1] == '(')
            {
                if (nr == -1e9 && first)
                {
                    cnt1++;
                    nr = calculate();
                    first = false;
                    goto FirstElemDif; // mergem direct la primul element din dif
                }
                cnt1++;
                nr = nr - calculate();
            FirstElemDif:
                goto OutOfDif; // sarim la out of dif / iesim din dif
            }
            if (vectorCOD[cnt1] == ')')
            {
                cnt1++;
                return nr;
            }
            return nr;
        }
        if (vectorCOD[cnt1] == '*')
        {
            cnt1++;
            Funct3:
            if (isFunction(vectorCOD[cnt1]))
            {
                if (nr == -1e9)
                    nr = calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                else nr *= calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                cnt1 += 2;
                cnt2++;
                if (vectorCOD[cnt1] == 'n')
                    goto OutOfProd;
                while (isFunction(vectorCOD[cnt1]))
                {
                    nr *= calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                    cnt1 += 2;
                    cnt2++;
                    if (vectorCOD[cnt1] == 'n')
                        goto OutOfProd;
                }
            }
            if (vectorCOD[cnt1] == 'n')
            {
                if (nr == -1e9)
                    nr = Numbers[cnt2];
                else nr *= Numbers[cnt2];
                cnt1++;
                cnt2++;
                if (isFunction(vectorCOD[cnt1]))
                    goto Funct3;
                OutOfProd:  // iesirea din produs
                while (vectorCOD[cnt1] == 'n')
                {
                    nr *= Numbers[cnt2];
                    cnt1++;
                    cnt2++;
                    if (isFunction(vectorCOD[cnt1]))
                        goto Funct3;
                }
            }
            //return nr;
            if (vectorCOD[cnt1] == '(')
            {
                if (nr == -1e9 && first)
                {
                    nr = 1;
                    first = false;
                }
                cnt1++;
                nr = nr * calculate();
                goto OutOfProd; // iesim din produs
            }
            if (vectorCOD[cnt1] == ')')
            {
                cnt1++;
                return nr;
            }
            return nr;
        }
        if (vectorCOD[cnt1] == '/')
        {
            cnt1++;
            Funct4:
            if (isFunction(vectorCOD[cnt1]))
            {
                if (nr == -1e9)
                    nr = calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                else
                {
                    if(calculateFunction(vectorCOD[cnt1], Numbers[cnt2]) == 0)
                    {
                        cout << "Nu este posibila impartirea la 0" << "\n";
                        ans = false;
                        HowManyZeros++;
                        break;
                    }
                    nr /= calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                }
                cnt1 += 2;
                cnt2++;
                if (vectorCOD[cnt1] == 'n')
                    goto OutOfDiv;
                while (isFunction(vectorCOD[cnt1]))
                {
                    if (calculateFunction(vectorCOD[cnt1], Numbers[cnt2]) == 0 /*&& HowManyZeros == 0*/)
                    {
                        cout << "Nu este posibila impartirea la 0" << "\n";
                        ans = false;
                        HowManyZeros++;
                        break;
                    }
                    nr /= calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                    cnt1 += 2;
                    cnt2++;
                    if (vectorCOD[cnt1] == 'n')
                        goto OutOfDiv;
                }
            }
            if (vectorCOD[cnt1] == 'n')
            {
                if (nr == -1e9)
                    nr = Numbers[cnt2];
                else {
                    if (Numbers[cnt2] == 0 && HowManyZeros == 0)
                    {
                        cout << "Nu este posibila impartirea la 0" << "\n";
                        ans = false;
                        HowManyZeros++;
                        break;
                    }
                    nr /= Numbers[cnt2];
                }
                cnt1++;
                cnt2++;
                if (isFunction(vectorCOD[cnt1]))
                    goto Funct4;
                OutOfDiv:  // iesirea din impartire
                while (vectorCOD[cnt1] == 'n')
                {
                    if (Numbers[cnt2] == 0 && HowManyZeros == 0)
                    {
                        cout << "Nu este posibila impartirea la 0" << "\n";
                        ans = false;
                        HowManyZeros++;
                        break;
                    }
                    nr /= Numbers[cnt2];
                    cnt1++;
                    cnt2++;
                    if (isFunction(vectorCOD[cnt1]))
                        goto Funct4;
                }
            }
            //return nr;
            if (vectorCOD[cnt1] == '(')
            {
                if (nr == -1e9 && first)
                {
                    cnt1++;
                    nr = calculate();
                    first = false;
                    goto FirstElemDiv; // sarim direct la primul element din impartire
                }
                cnt1++;
                res_divison = calculate();
                if (res_divison == 0 && first == false && HowManyZeros == 0)
                {
                    cout << "Nu este posibila impartirea la 0" << "\n";
                    ans = false;
                    HowManyZeros++;
                    break;
                }
                nr /= res_divison;
                res_divison = -1;
            FirstElemDiv:
                goto OutOfDiv;
            }
            if (vectorCOD[cnt1] == ')')
            {
                cnt1++;
                return nr;
            }
            return nr;
        }
        if (vectorCOD[cnt1] == '^')
        {
            cnt1++;
            Funct5:
            if (isFunction(vectorCOD[cnt1]))
            {
                if (nr == -1e9)
                    nr = calculateFunction(vectorCOD[cnt1], Numbers[cnt2]);
                else nr = pow(nr, calculateFunction(vectorCOD[cnt1], Numbers[cnt2]));
                cnt1 += 2;
                cnt2++;
                if (vectorCOD[cnt1] == 'n')
                    goto OutOfPow;
                while (isFunction(vectorCOD[cnt1]))
                {
                    nr = pow(nr, calculateFunction(vectorCOD[cnt1], Numbers[cnt2]));
                    cnt1 += 2;
                    cnt2++;
                    if (vectorCOD[cnt1] == 'n')
                        goto OutOfPow;
                }
            }
            if (vectorCOD[cnt1] == 'n')
            {
                if (nr == -1e9)
                    nr = Numbers[cnt2];
                else nr = pow(nr,Numbers[cnt2]);
                cnt1++;
                cnt2++;
                if (isFunction(vectorCOD[cnt1]))
                    goto Funct5;
                OutOfPow:  // iesirea din suma
                while (vectorCOD[cnt1] == 'n')
                {
                    nr = pow(nr, Numbers[cnt2]);
                    cnt1++;
                    cnt2++;
                    if (isFunction(vectorCOD[cnt1]))
                        goto Funct5;
                }
            }
            if (vectorCOD[cnt1] == '(')
            {
                if (nr == -1e9 && first)
                {
                    cnt1++;
                    nr = calculate();
                    first = false;
                    goto FirstElemPow;
                }
                cnt1++;
                nr = pow(nr, calculate());
            FirstElemPow:
                goto OutOfPow;
            }
            if (vectorCOD[cnt1] == ')')
            {
                cnt1++;
                return nr;
            }
            return nr;
        }
    }
}

