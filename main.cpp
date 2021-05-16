#include <iostream>
#include "Plansza.h"
#include <SFML/Graphics.hpp>
using namespace std;


int main()
{
    int warta, wartb;
    int continiue=false;
    do{

        //===================================================================================================
        //OKNO STARTOWE
        //===================================================================================================
        sf::RenderWindow app(sf::VideoMode(800, 800), "Saper Deluxe - WITAJ W SAPERZE");
        Plansza pierwsza;
        pierwsza.clearAll();
        pierwsza.rozmiarplanszy(25,25);  //przy zamknięciu wyboru min można zoabzyć działanie
        pierwsza.deployMines(true,0);   //Zabezpieczenie przed zamknięciem okna 2 pzed wybraniem trudnosci

        //===================================================================================================
        // KSZTAuTY
        //===================================================================================================
        sf::RectangleShape appBG(sf::Vector2f(800.0f,800.0f));
        sf::RectangleShape appBG2(sf::Vector2f(800.0f,800.0f));
        sf::RectangleShape menuEasy(sf::Vector2f(350.0f,88.0f));
        sf::RectangleShape menuMild(sf::Vector2f(350.0f,88.0f));
        sf::RectangleShape menuHard(sf::Vector2f(350.0f,88.0f));
        sf::RectangleShape PoleSFML(sf::Vector2f(32.0f,32.0f));
        sf::RectangleShape Ending(sf::Vector2f(600.0f,300.0f));

        //===================================================================================================
        //TEKSTURY
        //===================================================================================================
        sf::Texture wygrana, przegrana, okienka, BG, BG2, easy, mild, hard;
        //===================================================================================================
        // WCZYT TEKSTUR
        //===================================================================================================
        okienka.loadFromFile("okienka2.png");
        wygrana.loadFromFile("wygrana.png");
        przegrana.loadFromFile("przegrana.png");
        BG.loadFromFile("saperdeluxe.png");
        BG2.loadFromFile("saperdeluxemenu.png");
        easy.loadFromFile("easy2.png");
        mild.loadFromFile("mild2.png");
        hard.loadFromFile("hard.png");
        // PRZYPIS TEKSTUR

        menuEasy.setTexture(&easy);
        menuMild.setTexture(&mild);
        menuHard.setTexture(&hard);
        PoleSFML.setTexture(&okienka);
        appBG.setTexture(&BG);
        appBG2.setTexture(&BG2);
        //POZYCJA KSZTALTOW

        menuEasy.setPosition(225,196);
        menuMild.setPosition(225,333);
        menuHard.setPosition(225,470);

        //CHARAKTERYZACJA TEKSTURY MIN

        sf::Vector2u rozmiarTekstury = okienka.getSize();
        rozmiarTekstury.x /= 14;
        //====================================================================================================
        //OKNO POWITALNE
        //====================================================================================================
        while (app.isOpen()){

            sf::Event eventG;

            while (app.pollEvent(eventG)) {

                if (eventG.type == sf::Event::Closed) {
                    continiue=false;
                    app.close();
                }
                if (eventG.type == sf::Event::MouseButtonPressed)
                    if (eventG.key.code == sf::Mouse::Left) app.close();//OKNO ZAMYKA SIE POD LEWYM I POD PRAWYM
                    else if (eventG.key.code == sf::Mouse::Right) app.close();//OKNO ZAMYKA SIE POD LEWYM I POD PRAWYM
            }
            app.draw(appBG);
            app.display();

        }
        //===================================================================================================
        // OKNO Z MENU
        //===================================================================================================
        sf::RenderWindow menu(sf::VideoMode(800, 800), "Saper Deluxe - Wybierz Trudnosc");
        if(!app.isOpen())
        {
            while (menu.isOpen()) {
                sf::Vector2i kursor2 = sf::Mouse::getPosition(menu);

                sf::Event eventMenu;
                while (menu.pollEvent(eventMenu)) {


                    if (eventMenu.type == sf::Event::Closed) {
                        continiue = false;
                        menu.close();
                    }
                    if (eventMenu.type == sf::Event::MouseButtonPressed) {
                        if (eventMenu.key.code == sf::Mouse::Left)
                            if (pierwsza.trudnosc(kursor2.x, kursor2.y)) menu.close();//SPRAWDZENIE CZY PRZYCISK WCISNIETY
                            else if (eventMenu.key.code == sf::Mouse::Right) menu.close();// ZAMKNIECIE POD PRAWYM
                    }
                }

                //#######################################
                //KOLOR PRZYCISKÓW PRZY NAJECHANIU
                //#######################################
                if(pierwsza.barwaOkna(kursor2.x,kursor2.y)>=-1){
                    switch(pierwsza.barwaOkna(kursor2.x,kursor2.y)){
                        case 1:
                            menuEasy.setFillColor(sf::Color::Green);
                            break;
                        case 2:
                            menuMild.setFillColor(sf::Color::Yellow);
                            break;
                        case 3:
                            menuHard.setFillColor(sf::Color::Red);
                            break;
                        case -1:
                            menuHard.setFillColor(sf::Color::White);
                            menuMild.setFillColor(sf::Color::White);
                            menuEasy.setFillColor(sf::Color::White);
                            break;
                    }
                }
                menu.draw(appBG2);
                menu.draw(menuEasy);
                menu.draw(menuMild);
                menu.draw(menuHard);
                menu.display();
            }
        }
        //====================================================================================================
        // OKNO Z GRA CZESC WLASCIWA
        //====================================================================================================
        if(!app.isOpen()&& !menu.isOpen()) {
            sf::RenderWindow window(sf::VideoMode(32*pierwsza.wartx(), 32*pierwsza.warty()), "Saper Deluxe - Pacz gdzie klikasz!"); //Rozmiar po ilości pól
            while (window.isOpen()) {

                //######################################
                //PRZELICZNIK POZYCJI PO KURSORZE
                //######################################
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                int pozx = pos.x / 32;
                int pozy = pos.y / 32;

                sf::Event event;
                while (window.pollEvent(event)) {

                    if (event.type == sf::Event::Closed) {
                        continiue=false;
                        window.close();
                    }
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.key.code == sf::Mouse::Left) {
                            if (pierwsza.czyRuchZrobiono()) {
                                pierwsza.reveal(pozx, pozy);
                            }                                                           // W NORMALNYM RUCHU NORMALNE ODKRYCIE MINY
                            else {
                                pierwsza.massreveal(pozx, pozy);                      //DLA ULATWIENIA W PIERWSZYM RUCHU ODKRYWA NAM POLA WOKOLO KLIKNIETEGO O ILE NIE SA MINAMI
                            }
                        }
                        else if (event.key.code == sf::Mouse::Right) {
                            pierwsza.flag(pozx, pozy);             //OFLAGOWANIE POZYCJI
                        }
                    }
                }

                window.clear();

                //*************************************************************************
                                //OTEKSTUROWANIE KONKRETNYCH POL
                //*************************************************************************
                for (int a = 0; a < pierwsza.wartx(); a++) {
                    for (int b = 0; b < pierwsza.warty(); b++) {
                        PoleSFML.setTextureRect(
                                sf::IntRect(rozmiarTekstury.x * pierwsza.display2(a, b), rozmiarTekstury.y * 0,
                                            rozmiarTekstury.x, rozmiarTekstury.y));
                        PoleSFML.setPosition(a * 32, b * 32);
                        window.draw(PoleSFML);
                    }
                }
                if (pierwsza.koniec()){         //jeżeli koniec gry
                    window.draw(PoleSFML);
                    window.close();
                }

                window.display();
            }

        }
        if (pierwsza.koniec()) {
            //===================================================================================================
            // DODATKOWE OKNO Z WERDYKTEM WYGRANA/PRZEGRANA
            //===================================================================================================
            sf::RenderWindow koniec(sf::VideoMode(600, 300), "Saper Deluxe - Koniec!");
            sf::Event event2;
            while (koniec.isOpen()) {
                sf::Event event2;
                while (koniec.pollEvent(event2)) {
                    if (event2.type == event2.Closed) {
                        continiue=false;
                        koniec.close();
                    }
                }
                if (event2.type == sf::Event::MouseButtonPressed)
                    if (event2.key.code == sf::Mouse::Left) {

                        koniec.close();
                    } else if (event2.key.code == sf::Mouse::Right) {
                        koniec.close();
                    }
                //##########################################
                // TEKSTURA W ZALEŻNOŚCI OD WERDYKTU
                //##########################################

                if (pierwsza.czyRuch()) {
                    pierwsza.koniecPrzegrana(warta,wartb); //Spisanie wartości dla błędnie wciśniętej miny
                    Ending.setTexture(&przegrana); //przegrana tekstura
                }
                else Ending.setTexture(&wygrana); //wygrana tekstura

                koniec.draw(Ending);
                koniec.display();
            }
            if(!koniec.isOpen())
            {
                //===================================================================================================
                //DODATKOWE OKNO KARYFIKUJACE POLOZENIE WSZYSTKICH MIN NA PLANSZY
                //===================================================================================================
                sf::RenderWindow window2(sf::VideoMode(32*pierwsza.wartx(), 32*pierwsza.warty()), "Saper Deluxe - Tak to wyglada.");


                pierwsza.revealAllMines();
                while (window2.isOpen()) {
                    sf::Event eventz;
                    while (window2.pollEvent(eventz)) {

                        if (eventz.type == sf::Event::Closed) {
                            window2.close();
                        }
                        if (eventz.type == sf::Event::MouseButtonPressed)
                            if (eventz.key.code == sf::Mouse::Left)  {
                                continiue=true;//główna pętla gry
                                window2.close();
                            }
                            else if (eventz.key.code == sf::Mouse::Right) {
                                continiue=false;//główna pętla gry
                                window2.close();
                            }
                    }

                    window2.clear();
                    for (int a = 0; a < pierwsza.wartx(); a++) {
                        for (int b = 0; b < pierwsza.warty(); b++) {

                            PoleSFML.setTextureRect(
                                    sf::IntRect(rozmiarTekstury.x * pierwsza.displayKKK(a, b), rozmiarTekstury.y * 0,
                                                rozmiarTekstury.x, rozmiarTekstury.y));
                            PoleSFML.setPosition(a * 32, b * 32);
                            if( a==warta && b==wartb ) //ZMIANA KOLORU WCIŚNIĘTEGO POLA
                            {
                                PoleSFML.setFillColor(sf::Color::Red);
                            }
                            else {
                                PoleSFML.setFillColor(sf::Color::White);
                            }
                            window2.draw(PoleSFML);
                        }

                    }
                    window2.display();
                }
            }
        }
    }while (continiue);
    return 0;

}
