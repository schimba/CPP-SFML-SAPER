
#ifndef INC_242016_PLANSZA_H
#define INC_242016_PLANSZA_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Pole.h"


class Plansza {
    Pole Tablica[100][100];
    int x;
    int y;
public:
    void rozmiarplanszy(int a, int b);
    int wartx()const ;
    int warty()const ;
    void deployMines(bool random, int miny);
    void losuj_pozycje (int miny);
    void minka();
    bool ominowanie (int poz_x, int poz_y);
    bool hasMine(int a, int b);
    int countMines(int a, int b);
    int display2(int a, int b);
    int displayKKK(int a,int b);
    bool koniec();
    bool czyRuch();
    void reveal(int a, int b);
    void massreveal(int a, int b);
    void flag(int a,int b);
    bool trudnosc(float a, float b);
    int barwaOkna(float a, float b);
    bool czyRuchZrobiono();
    void revealAllMines();
    void koniecPrzegrana(int &warta, int &wartb);
    void clearAll();
    Plansza();


};


#endif //INC_242016_PLANSZA_H