#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<iostream>
using namespace std;
void wczytaj_zasady();									    //funkcja wypisuje zasady gry
int kontynuacja();                                          //zapis i wybor gry
template <typename L>
L wczytaj_liczbe(L min, L max);                             //szablon funkcji wczytujacej liczbe z przedzialu
class kolkokrzyzyk {
protected:
	char plansza[15][15] = { NULL };                        //plansza
public:
	kolkokrzyzyk();                                         //konstruktor domyslny
	virtual void ruch(int pom) {};                          //ruch osoby
	void rysujplansze();                                    //rysowanie planszy
	int sprawdz_czy_wygrales();                             //sprawdzenie czy osoba x wygrala
	int sprawdz_remis();                                    //sprawdzenie remisu
	void zapisz_gre(int pomz);                              //zapisanie gry
	int wczytaj_gre();                                      //wczytanie gry
};

//klasa gry dwuosobowej
class gracz :public kolkokrzyzyk {
protected:
	char p1;                                               //gracz 1
	char p2;                                               //gracz 2
public:
	gracz();                                               //konstruktor domyslny
	virtual void ruch(int pom);                            //gracz wybiera swoj ruch
};

//klasa gry z komputerem
class komputer : public kolkokrzyzyk {
protected:
	char p1;                                               //gracz 1
	char com;                                              //gracz komputer
public:
	komputer();                                            //konstruktor domyslny
	virtual void ruch(int pom);                            //ruch gracza
};