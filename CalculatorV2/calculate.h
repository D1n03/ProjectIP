#include <iostream>
using namespace std;
char vectorCOD[101] = "";
int cnt1, cnt2, i, j, Numbers[101], HowManyZeros;
bool ans = true;
int getPriority(char current)  //functia returneaza prioritatea operatiei: 1 pt adunare si scadere, 2 pt inmultire si impartire, etc.
{
    if (current== 's' || current == 'c' || current == 't' || current == 'g' || current == 'l') 
        return 4;
    if (current == '^')
        return 3;
    if (current == '*' || current == '/')
        return 2;
    if (current == '+' || current == '-')
        return 1;
    else return 0;
}
double calculate()
{
    double nr = -1, res_divison;
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
            if (vectorCOD[cnt1] == 'n')
            {
                nr = Numbers[cnt2];
                cnt1++;
                cnt2++;
                OutOfSum:  // iesirea din suma 
                while (vectorCOD[cnt1] == 'n')
                {
                    nr += Numbers[cnt2];
                    cnt1++;
                    cnt2++;
                }
            }
            //return nr;
            if (vectorCOD[cnt1] == '(')
            {
                if (nr == -1 && first)
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
            if (vectorCOD[cnt1] == 'n')
            {
                nr = Numbers[cnt2];
                cnt1++;
                cnt2++;
                OutOfDif:
                while (vectorCOD[cnt1] == 'n')
                {
                    nr -= Numbers[cnt2];
                    cnt1++;
                    cnt2++;
                }
            }
            //return nr;
            if (vectorCOD[cnt1] == '(')
            {
                if (nr == -1 && first)
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
            if (vectorCOD[cnt1] == 'n')
            {
                nr = Numbers[cnt2];
                cnt1++;
                cnt2++;
                OutOfProd:
                while (vectorCOD[cnt1] == 'n')
                {
                    nr *= Numbers[cnt2];
                    cnt1++;
                    cnt2++;
                }
            }
            //return nr;
            if (vectorCOD[cnt1] == '(')
            {
                if (nr == -1 && first)
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
            if (vectorCOD[cnt1] == 'n')
            {
                nr = Numbers[cnt2];
                cnt1++;
                cnt2++;
                OutOfDiv:
                while (vectorCOD[cnt1] == 'n')
                {
                    if (Numbers[cnt2] == 0 && HowManyZeros == 0)
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
            //return nr;
            if (vectorCOD[cnt1] == '(')
            {
                if (nr == -1 && first)
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
                    cout << "Nu este posibila impartirea la 0";
                    ans = false;
                    HowManyZeros++;
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
            if (vectorCOD[cnt1] == 'n')
            {
                nr = Numbers[cnt2];
                cnt1++;
                cnt2++;
            OutOfPow:
                while (vectorCOD[cnt1] == 'n')
                {
                    nr = pow(nr, Numbers[cnt2]);
                    cnt1++;
                    cnt2++;
                }
                //  return nr;
            }
            if (vectorCOD[cnt1] == '(')
            {
                if (nr == -1 && first)
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