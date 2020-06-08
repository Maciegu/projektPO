#include <iostream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include "klasy_dekl.h"
using namespace std;

int main() {
	printf("===========================\n");
	printf("GRA W KOLKO I KRZYZYK\n");
	printf("===========================\n\n\n");
	wczytaj_zasady();                          //wywolanie funkcji wczytujacej zasady
	srand(time(NULL));
	while (1) {
		kolkokrzyzyk* gra;
		printf("\n\n\nMenu gry.");
		printf("\n1.Wczytaj zapis gry");
		printf("\n2.Nowa gra");
		printf("\n3.Gra z komputerem");
		printf("\n4.Zakoncz gre");
		printf("\n\nWybierz numer: ");
		int wybor = wczytaj_liczbe(1, 4);
		int wczytanie = 0;                    //zmienna do wczytania gry
		if (wybor == 1) { 
			kolkokrzyzyk trzy;
			wybor = trzy.wczytaj_gre();
			wczytanie = 1;
		}
		if (wybor == 2) {                     //tryb offline dwuosobowy
			gracz off;
			gra = &off;
			int kolejGracza = 0;              //zmienna do roztrzygania kogo kolej ruchu
			if (wczytanie == 1) {
				gra->wczytaj_gre();	          //funkcja wczytujaca zapis gry
			}
			while (1) {
				if (kolejGracza % 2 == 0) {	 //kolej gracza X
					system("cls");
					printf("Gra dwuuosobowa\n");
					printf("Kolej gracza 'X'\n\n");
					gra->rysujplansze();
					gra->ruch(1);
					system("cls");
					printf("Gra dwuosobowa\n");
					printf("Kolej gracza 'X'\n\n");
					gra->rysujplansze();
					if (gra->sprawdz_czy_wygrales() == 1) {//sprawdzamy czy X wygral
						kontynuacja();
						break;
					}
					if (gra->sprawdz_czy_wygrales() == 2) {//sprawdzamy czy przez ruch X wygral O
						kontynuacja();
						break;
					}
				}
				else {						               //kolej gracza 'O'
					system("cls");
					printf("Gra dwuuosobowa\n");
					printf("Kolej gracza 'O'\n\n");
					gra->rysujplansze();
					gra->ruch(1);
					system("cls");
					printf("Gra dwuosobowa\n");
					printf("Kolej gracza 'O'\n\n");
					gra->rysujplansze();
					if (gra->sprawdz_czy_wygrales() == 2) {//sprawdzamy wygrana
						kontynuacja();
						break;
					}
					if (gra->sprawdz_czy_wygrales() == 1) {//sprawdzamy czy przez ruch O wygral X
						kontynuacja();
						break;
					}
					gra->zapisz_gre(wybor);	               //zapis gry
					if (gra->sprawdz_remis() == 1) {
						printf("Remis\n");
						if (remove("ZapisGry.txt") != 0) {//w przypadku remis zapis zostaje usuniety
							perror("Nie mozna usunac zapisu gry.");
							exit(0);
						}
						printf("\nWcisnij enter zeby przejsc do wyboru trybu gry\n");
						char wyb;
						wyb = getchar();
						break;
					}
				}
				kolejGracza++;                          //zwiekszamy indeks by kolejna osoba mogla wykonac ruch
			}
			system("cls");
			continue;
		}
		if (wybor == 3) {                               //gra z komputerem
			komputer komp;
			gra = &komp;
			int kolejGracza = 0;
			if (wczytanie == 1) {
				gra->wczytaj_gre();                     //wczytujemy gre
			}
			while (1) {
				if (kolejGracza % 2 == 0) {             //kolej gracza X
					system("cls");
					printf("Gra z komputerem\n");
					printf("Kolej gracza 'X'\n\n");
					gra->rysujplansze();                //pokazanie aktualnej planszy
					gra->ruch(1);
					system("cls");
					printf("Gra z komputerem\n");
					printf("Kolej gracza 'X'\n\n");
					gra->rysujplansze();
					if (gra->sprawdz_czy_wygrales() == 1) {//sprawdzamy wygrana
						kontynuacja();
						break;
					}
					if (gra->sprawdz_czy_wygrales() == 2) {//sprawdzamy czy przez ruch X wygral O
						kontynuacja();
						break;
					}
				}
				else {                                     //kolej gracza 'O'
					system("cls");
					printf("Gra z komputerem\n");
					printf("Kolej komputera 'O'\n\n");
					gra->rysujplansze();
					gra->ruch(2);
					system("cls");
					printf("Gra z komputerem\n");
					printf("Kolej komputera 'O'\n\n");
					gra->rysujplansze();
					if (gra->sprawdz_czy_wygrales() == 2) {//sprawdzamy tak jak wczesniej
						kontynuacja();
						break;
					}
					if (gra->sprawdz_czy_wygrales() == 1) {
						kontynuacja();
						break;
					}
					gra->zapisz_gre(wybor);
					if (gra->sprawdz_remis() == 1) {
						printf("Remis\n");
						if (remove("ZapisGry.txt") != 0) {
							perror("Nie mozna usunac zapisu gry.");
							exit(0);
						}
						printf("\nWcisnij \"ENTER\" aby przejsc do wyboru trybu\n");
						char wyb;
						wyb = getchar();
						break;
					}
				}
				kolejGracza++;
			}
			system("cls");
			continue;
		}
		if (wybor == 4) {
			printf("\nKoniec gry.\n");
			return 0;
		}
	}
}