
#ifndef INC_242016_POLE_H
#define INC_242016_POLE_H
#include<iostream>

class Pole {
    bool mina;
    bool odkryta;
    bool flaga;
public:
    Pole();
    void  Info()const;
    void  StanMina(bool a);
    void  StanOdkryta(bool b);
    void  StanFlaga(bool c);
    bool  StanMiny();
    bool  StanOdkrytej();
    bool  StanFlagi();

};


#endif //INC_242016_POLE_H
