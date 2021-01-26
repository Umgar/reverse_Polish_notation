#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

class opera{
    int priorytet;
    char znak;
public:
    opera(int p, char z)
    {
        priorytet = p;
        znak = z;
    }
    char sprawdzZnak()
    {
        return znak;
    }
    int sprawdzPriorytet()
    {
        return priorytet;
    }

};

opera operatory[7] = {
        opera(0, '('),
        opera(0, ')'),
        opera(1, '-'),
        opera(1, '+'),
        opera(2, '*'),
        opera(2, '/'),
        opera(3, '^')
    };

double Stod(vector<char> we, int &i)
{
    double liczba =0;
    double poPrzecinku =0;
    int przesuniecie =0;
    bool kropka = false;
    while(((we[i] >= '0' && we[i] <= '9') || we[i] == '.') && we.size() > i)
    {
        if(!kropka && we[i] != '.')
        {
            liczba *= 10;
            liczba += we[i]-'0';
        }
        if(kropka && we[i] != '.')
        {
            poPrzecinku *= 10;
            poPrzecinku += we[i]-'0';
            przesuniecie++;
        }
        if(we[i] == '.')
            kropka = true;
        i++;
    }
    liczba += poPrzecinku/pow(10, przesuniecie);
    return liczba;
}

void oslugaStosuONP(vector<opera> &stos, vector<char> &wyjscie,opera znak)
{
    if(znak.sprawdzZnak() == '(')
        stos.push_back(znak);
    else if(znak.sprawdzZnak() == ')')
    {
        int i = stos.size()-1;
        while(stos[i].sprawdzZnak() != '(' && i>0){
            wyjscie.push_back(stos[i].sprawdzZnak());
            wyjscie.push_back(' ');
            stos.pop_back();
            i--;
        }
        stos.pop_back();
    }
    else{
       stos.push_back(znak);
       for(int i=stos.size()-2; i>-1; i--)
       {
           if (stos[i].sprawdzZnak() == '(')
                return;
           else if(stos[i].sprawdzPriorytet() >= znak.sprawdzPriorytet())
           {
               wyjscie.push_back(stos[i].sprawdzZnak());
                wyjscie.push_back(' ');
               stos.erase(stos.begin() + i);
           }
       }
    }
}

vector<char> stworzONP(string wejscie)
{
    vector<opera> stos;
    vector<char> wyjscie;
    int i, j, z;
    for(i=0;i<wejscie.size(); i++)
    {
        if((wejscie[i]>='0' && wejscie[i]<='9') || wejscie[i] == '.')
            {
                wyjscie.push_back(wejscie[i]);
                if(!((wejscie[i+1]>='0' && wejscie[i+1]<='9') || wejscie[i+1] =='.'))
                    wyjscie.push_back(' ');
            }


        else if(wejscie[i]!= ' ' || wejscie[i] != '.')
        {
            for(j=0;j<7;j++)
            {
                if(operatory[j].sprawdzZnak() == wejscie[i])
                {
                    oslugaStosuONP(stos, wyjscie, operatory[j]);
                    break;
                }
            }
        }
        else if (wejscie[i]=='=') break;
    }
    for(i = stos.size()-1;i>-1;i--)
    {
        wyjscie.push_back(stos[i].sprawdzZnak());
        wyjscie.push_back(' ');
        stos.pop_back();
    }
    return wyjscie;
}

double wyrazenieONP(char znak, double a, double b)
    {
        double wartosc;
        switch(znak)
        {
            case '-': wartosc = b-a; break;
            case '+': wartosc = b+a; break;
            case '*': wartosc = b*a; break;
            case '/': wartosc = b/a; break;
            case '^': wartosc = pow(b, a); break;
            default: cout << endl << "Pojawil sie jakis problem: " << znak << endl; break;
        }
        return wartosc;
    }



double obliczenieONP(vector<char> ONP)
{
    vector<double> stos;
    double a, b;
    double liczba;
    int i, j;
    for(i=0; i<ONP.size(); i++)
    {
        if(ONP[i]-'0'>=0 && ONP[i]-'0'<=9)
        {
            liczba = Stod(ONP, i);
            stos.push_back(liczba);
        }
        else if(ONP[i] != ' ' && ONP[i] != '.'){
            for(j=2; j<7; j++)
            {
                if(operatory[j].sprawdzZnak() == ONP[i]);
                    {
                        a = stos[stos.size()-1];
                        stos.pop_back();
                        b = stos[stos.size()-1];
                        stos.pop_back();
                        liczba = wyrazenieONP(ONP[i], a, b);
                        stos.push_back(liczba);
                        break;
                    }
            }
        }
    }
    return stos[0];
}

int main()
{

    string we = "1.5 * 2";
    cout << "Podaj wyrazenie: " << endl;
    getline(cin, we);

    vector<char> ONP = stworzONP(we);

    cout << "Odwrotna notacja polska: ";
    for(int i=0; i<ONP.size(); i++)
        cout << ONP[i];
    double wartosc = obliczenieONP(ONP);
    cout << "\nWartosc: " << wartosc << endl << endl << endl;
    system("Pause");
    return 0;
}


