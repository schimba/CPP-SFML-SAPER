

#include "Pole.h"

using namespace std;
Pole::Pole()
{
    mina=false;
    odkryta=false;
    flaga=false;
};
void Pole::Info()const{             // Ze starej wersji, obecnie niewykorzystywania funkcja.
    cout<<mina<<odkryta<<flaga<<" "<<flush;
};
void Pole::StanMina(bool a){        //Zmiana Stanu Miny
    mina=a;
};
void Pole::StanOdkryta(bool b){     //Zmiana Stanu Odkrycia
    odkryta=b;
};
void Pole::StanFlaga(bool c){       //Zmiana Stanu Flagi
    flaga=c;
};

bool Pole::StanMiny() {             //Podanie Stanu Miny
    return mina;
};
bool Pole::StanOdkrytej() {         //Podanie Stanu Odkrycia
    return odkryta;
};
bool Pole::StanFlagi() {            //Podanie Stanu Flagi
    return flaga;
};