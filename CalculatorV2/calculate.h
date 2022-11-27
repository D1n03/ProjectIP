#include <iostream>

using namespace std;

char vectorCOD[101] = "";
int cnt1, cnt2, i, j, Numbers[101], HowManyZeros;
bool ans = true;

int getPriority(char current)  //functia returneaza prioritatea operatiei: 1 pt adunare si scadere, 2 pt inmultire si impartire, etc.
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
