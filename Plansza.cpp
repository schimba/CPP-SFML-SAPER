
#include<time.h>
#include "Plansza.h"
using namespace std;
Plansza::Plansza() {
    int x=100;
    int y=100;
};





void Plansza::deployMines(bool random, int miny) { // Funkcja ustawiająca miny parametr random jeszcze z poprzedniej wersji
    if (!random)
        minka();
    else losuj_pozycje(miny);

};

void Plansza::losuj_pozycje(int miny) { //Losowanie pozycji miny
    time_t t;
    int poz_x, poz_y;
    int ilosc = miny;

    srand((unsigned)time(&t));

    while (ilosc>0)
    {
        poz_x = rand()% wartx();
        poz_y = rand()% warty();

        ominowanie(poz_x,poz_y); //oddanie do ominowania losowej wartosci
        ilosc--;

    }
};

void Plansza::minka() { //funkcja ustawiająca miny po przekątnej, obecnie niedostępna z poziomu programu
    for(int i=0; i<warty();i++)
    {
        for(int j=0;j<wartx();j++)
            if(i==0){
                Tablica[i][j].StanMina(true); //ustawiam mine
            }
            else if(i==j)
            {
                Tablica[i][j].StanMina(true); //ustawiam mine
            }
    }
};

bool Plansza::ominowanie(int poz_x, int poz_y) { // LOSUJ POZYCJE część dalsza

    if (!Tablica[poz_x][poz_y].StanMiny()) {
        Tablica[poz_x][poz_y].StanMina(true); //ustawiam mine
    }
    else {

        while (Tablica[poz_x][poz_y].StanMiny()) { //jeżeli na pozycji jest już mina -> losowanie nowej pozycji
            poz_x = rand() % wartx();
            poz_y = rand() % warty();
        }
        Tablica[poz_x][poz_y].StanMina(true);   //ustawiam mine
    }
    return true;

}

bool Plansza::hasMine(int a, int b) { //Czy pole ma mine?
    if( a>wartx() || b>warty()|| a<0 || b<0)
        return false;
    return Tablica[a][b].StanMiny();
}

void Plansza::rozmiarplanszy(int a, int b) {//Modyfikator rozmianru planszy
    x=a;
    y=b;
}

int Plansza::wartx() const { //zwraca wartość X
    return x;
}

int Plansza::warty() const { //zwraca wartość Y
    return y;
}

int Plansza::countMines(int a, int b) { // Zliczenie min naokoło pola
    int ilosc = 0;
    for (int i = (a - 1); i <= (a + 1); i++) {
        for (int j = (b - 1); j <= (b + 1); j++) {
            if (hasMine(i, j)) {
                //cout << "\n Wykryto mine! "<<endl;
                ilosc++;
            }
        }
    }
    return ilosc;
}

int Plansza::display2(int a,int b) { //fkcja zwracająca wartości do tekstury w zależności od stanu pola
    if (Tablica[a][b].StanOdkrytej() && hasMine(a, b)) {
        return 9;
    }
    if (!Tablica[a][b].StanOdkrytej() && !Tablica[a][b].StanFlagi()) {
        return 10;
    }

    if (!Tablica[a][b].StanOdkrytej() && Tablica[a][b].StanFlagi()){
        return 11;
    }
    if (Tablica[a][b].StanOdkrytej() && !hasMine(a, b))
    {
        return countMines(a,b);
    }
}
int Plansza::displayKKK(int a,int b) { //fkcja zwracająca wartości do tekstury w zależności od stanu pola
    if (Tablica[a][b].StanOdkrytej() && hasMine(a, b) && Tablica[a][b].StanFlagi()) {
        return 12;
    }
    if (Tablica[a][b].StanOdkrytej() && hasMine(a, b) && !Tablica[a][b].StanFlagi()) {
        return 9;
    }
    if (!Tablica[a][b].StanOdkrytej() && !Tablica[a][b].StanFlagi()) {
        return 10;
    }

    if (!Tablica[a][b].StanOdkrytej() && Tablica[a][b].StanFlagi()){
        return 13;
    }
    if (Tablica[a][b].StanOdkrytej() && !hasMine(a, b))
    {
        return countMines(a,b);
    }
}

bool Plansza::czyRuch() { //Czy jest jeszcze możliwy ruch do zrobienia?
    for (int a = 0; a < x; a++) {
        for (int b = 0; b < y; b++) {
            if(!Tablica[a][b].StanOdkrytej() && !Tablica[a][b].StanMiny())
                return true;
        }
    }
    return false;
}
bool Plansza::czyRuchZrobiono() { //Czy ruch już został zrobiony
    for (int a = 0; a < x; a++) {
        for (int b = 0; b < y; b++) {
            if(Tablica[a][b].StanOdkrytej())
                return true;
        }
    }
    return false;
}

void Plansza::flag(int a, int b) {
    Tablica[a][b].StanFlaga(!Tablica[a][b].StanFlagi()); //Zmiana Stanu flagi
}

void Plansza::massreveal(int a,int b) {                         //fkcja odkrywa pobliskie oraz wywołuje siebie gdy któreś pole obok nie zawiera min obok siebie
    Tablica[a][b].StanOdkryta(true);
    for (int i = (a - 1); i <= (a + 1); i++) {
        for (int j = (b - 1); j <= (b + 1); j++) {
            if (!(i > wartx() || j > warty() || i < 0 || j < 0)) {
                //cout << "Wartosci to :" << i << j << endl;
                if (!hasMine(i, j)) {
                    if (countMines(i, j) == 0 && !Tablica[i][j].StanOdkrytej()) {
                        massreveal(i, j);
                    }
                    else if (countMines(i,j)!=0)
                        Tablica[i][j].StanOdkryta(true);
                }
            }
        }
    }
}

void Plansza::reveal(int a, int b) {    // Funkcja odkrywająca oraz sprawdzająca warunki dla możliwości
    // odkrycia(szczególnie ważne przy wcześniejszej wersji sapera podawania pola jako liczby z klawiatury
    if (!(a > wartx() || b > warty() || a < 0 || b < 0))
    {

        if (Tablica[a][b].StanFlagi())
        {
            // Pole jest oflagowane, wybierz inne pole lub zdejmij z niego flage
            return;
        }
        else {
            if (Tablica[a][b].StanMiny()) {
                Tablica[a][b].StanOdkryta(true);
                //Koniec gry :C
                return;

            } else if (!Tablica[a][b].StanMiny()) {
                if (!Tablica[a][b].StanOdkrytej()) {
                    if (countMines(a, b) == 0) {
                        massreveal(a, b);
                    } else if (countMines(a, b) != 0)
                        Tablica[a][b].StanOdkryta(true);
                } else return; //Pole juz jest odkryte...
            }
        }
    }
    else return;//  Pole nie ma w planszy ;c
}

bool Plansza::koniec() {    //Sprawdzenie warunków ukończenia gry
    for (int a = 0; a < x; a++) {
        for (int b = 0; b < y; b++) {
            if (Tablica[a][b].StanMiny() && Tablica[a][b].StanOdkrytej()) {
                // Wybuchles
                return true;
            }
        }

    }
    if (czyRuch())
        return false;
    else {

        //  Wygrales
        return true;
    }
}
void Plansza::koniecPrzegrana(int &warta, int &wartb) {    //Sprawdzenie warunków ukończenia gry
    for (int a = 0; a < x; a++) {
        for (int b = 0; b < y; b++) {
            if (Tablica[a][b].StanMiny() && Tablica[a][b].StanOdkrytej()) {
                warta=a;
                wartb=b;
            }
        }
    }
}

bool Plansza::trudnosc(float a, float b){ // Przyciski ustawienia trudności gry
    if(a>=225&&a<=575&&b>=196&&b<=284)
    {
        rozmiarplanszy(10,10);
        deployMines(true,15);
        return true;
    }
    if(a>225&&a<575&&b>333&&b<420)
    {
        rozmiarplanszy(20,15);
        deployMines(true,45);
        return true;
    }

    if(a>225&&a<575&&b>470&&b<557)
    {
        rozmiarplanszy(25,25);
        deployMines(true,100);
        return true;
    }
    return false;
}
int Plansza::barwaOkna(float a, float b){ //Zabarwienie okien przy przejeżdżaniu przez nie.
    if(a>=225&&a<=575&&b>=196&&b<=284)
    {
        return 1;
    }
    if(a>225&&a<575&&b>333&&b<420)
    {
        return 2;
    }

    if(a>225&&a<575&&b>470&&b<557)
    {
        return 3;
    }
    return -1;
}



void Plansza::revealAllMines() { // Funkcja odkrywająca wszystkie miny, potrzebna do pokazania ostatniego okna
    for (int a = 0; a < x; a++) {
        for (int b = 0; b < y; b++) {
            if(Tablica[a][b].StanMiny())
                Tablica[a][b].StanOdkryta(true);
        }
    }
}

void Plansza::clearAll() {
    for (int a = 0; a < x; a++) {
        for (int b = 0; b < y; b++) {
            Tablica[a][b].StanMina(false);
            Tablica[a][b].StanOdkryta(false);
            Tablica[a][b].StanFlaga(false);
        }
    }
}







