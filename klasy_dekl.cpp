#include <iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "klasy_dekl.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

//funkcja wypisujaca zasady z pliku
void wczytaj_zasady() {
	FILE* plik;
	if (fopen_s(&plik, "Zasady.txt", "r") != NULL) {
		perror("Nie udalo sie otworzyc pliku z zasadami.");
		exit(0);
	}
	if (plik == NULL) {
		perror("Nie mozna otworzyc pliku z zasadami.\n");
		exit(0);
	}
	char znak;
	while ((znak = getc(plik)) != EOF) {
		printf("%c", znak);
	}
}
//szablon funkcji ktora wczytuje liczbe i sprawdza poprawnosc danych
template <typename L> L wczytaj_liczbe(L min, L max) {
	L liczba;
	cin >> liczba;
	while (liczba<min || liczba>max || cin.get() != '\n') {				
		cin.clear();
		cin.ignore(1000, '\n');
		printf("Podaj poprawna liczbe: ");
		cin >> liczba;
	}
	return liczba;
}

//konstruktor domyslny
kolkokrzyzyk::kolkokrzyzyk() {
	for (int x = 1; x <= 15; x++) {
		for (int y = 1; y <= 15; y++) {
			plansza[x][y] = ' ';
		}
	}
}


//funkcja rysujaca plansze gry
void kolkokrzyzyk::rysujplansze() {
	for (int x = 0; x <= 15; x++) {
		if (x == 0) {
			printf("%4c", ' ');
		}
		else if (x != 0) {
			printf("%4d", x);
		}
	}
	printf("\n");
	for (int x = 1; x <= 16; x++) {
		printf("----");
	}
	printf("\n");
	for (int i = 1; i <= 15; i++) {
		printf("%2d%2c", i, '|');
		for (int j = 1; j <= 15; j++) {
			printf("%4c", plansza[i][j]);
		}
		printf("\n");
	}
}

//funkcja sprawdza czy grajacy wygral
int kolkokrzyzyk::sprawdz_czy_wygrales() {
	int x = 0;
	for (int i = 1; i <= 15; i++) {
		for (int j = 1; j <= 15; j++) {
			if (plansza[i][j] == 'O' && plansza[i][j + 1] == 'O' && plansza[i][j + 2] == 'O' && plansza[i][j + 3] == 'O' && plansza[i][j + 4] == 'O') {
				x = 1;
				break;
			}
			if (plansza[i][j] == 'O' && plansza[i + 1][j] == 'O' && plansza[i + 2][j] == 'O' && plansza[i + 3][j] == 'O' && plansza[i + 4][j] == 'O') {
				x = 1;
				break;
			}
			if (plansza[i][j] == 'O' && plansza[i + 1][j + 1] == 'O' && plansza[i + 2][j + 2] == 'O' && plansza[i + 3][j + 3] == 'O' && plansza[i + 4][j + 4] == 'O') {
				x = 1;
				break;
			}
			if (plansza[i][j] == 'X' && plansza[i][j + 1] == 'X' && plansza[i][j + 2] == 'X' && plansza[i][j + 3] == 'X' && plansza[i][j + 4] == 'X') {
				x = 2;
				break;
			}
			if (plansza[i][j] == 'X' && plansza[i + 1][j] == 'X' && plansza[i + 2][j] == 'X' && plansza[i + 3][j] == 'X' && plansza[i + 4][j] == 'X') {
				x = 2;
				break;
			}
			if (plansza[i][j] == 'X' && plansza[i + 1][j + 1] == 'X' && plansza[i + 2][j + 2] == 'X' && plansza[i + 3][j + 3] == 'X' && plansza[i + 4][j + 4] == 'X') {
				x = 2;
				break;
			}
		}
	}
	if (x == 1) {
		system("cls");
		printf("\n\nGRACZ Z PIONKIEM 'X' WYGRYWA GRE!!!!!!!!!!!!!!\n\n");
		rysujplansze();
		return x;
	}
	else if (x == 2) {
		system("cls");
		printf("\n\nGRACZ Z PIONKIEM 'O' WYGRYWA GRE!!!!!!!!!!!!!!\n\n");
		rysujplansze();
		return x;
	}
}

//funkcja sprawdzajaca czy na planszy jest jeszcze pole-inaczej gra konczy sie remisem
int kolkokrzyzyk::sprawdz_remis() {
	for (int x = 1; x <= 15; x++) {
		for (int y = 1; y <= 15; y++) {
			if (plansza[x][y] == ' ') return 0;
		}
	}
	return 1;
}

//funkcja zapisujaca gre
void kolkokrzyzyk::zapisz_gre(int pomz) {
	FILE* plik;
	if (fopen_s(&plik, "ZapisGry.txt", "w") != NULL) {
		perror("Nie mozna otworzyc gry.");
		exit(0);
	}
	if (plik == NULL) {
		perror("Nie mozna otworzyc gry.");
		exit(0);
	}
	for (int x = 1; x <= 15; x++) {
		for (int y = 1; y <= 15; y++) {
			fprintf(plik, "%c", plansza[x][y]);
		}
	}
	fprintf(plik, "%d\n", pomz);
	fclose(plik);
}

//funkcja wczytujaca zapis gry
int kolkokrzyzyk::wczytaj_gre() {
	FILE* plik;
	int pomw;
	if (fopen_s(&plik, "ZapisGry.txt", "r") != NULL) {
		perror("Nie mozna otworzyc pliku lub nie ma zapisanej gry.");
		exit(0);
	}
	if (plik == NULL) {
		perror("Nie mozna otworzyc pliku.");
		exit(0);
	}
	for (int x = 1; x <= 15; x++) {
		for (int y = 1; y <= 15; y++) {
			fscanf_s(plik, "%c", &plansza[x][y], 1);
		}
	}
	fscanf_s(plik, "%d", &pomw);
	fclose(plik);
	return pomw;
}

//funkcja usuwa zapis w przypadku roztrzygniecia gry i pyta o ponowna gre
int kontynuacja() {
	if (1) {
		if (remove("ZapisGry.txt") != 0) {
			perror("\nNie mozna usunac zapisu gry");
			exit(0);
		}
		printf("Czy chcesz zagrac jeszcze raz?\n");
		printf("1-Tak\n2-Nie\n\nWybierz numer: ");
		int decyzja = wczytaj_liczbe(1, 3);
		if (decyzja == 1) {
			return 1;
			system("cls");
		}
		else
			exit(0);
	}
	return 0;
}

//konstruktor domyslny
gracz::gracz():kolkokrzyzyk(), p1(' '), p2(' ') {}

//funkcja stawiajaca plytke na wybranym polu
void gracz::ruch(int pom) {
	int a, b, c, d;
	int kierunek;
	if (1) {
		printf("\n\nWybierz pole podajac (a,b) i (c,d) oddzielone enterami:\n");
		a = wczytaj_liczbe(1, 15);
		b = wczytaj_liczbe(1, 15);
		c = wczytaj_liczbe((a - 1), (a + 1));
		d = wczytaj_liczbe((b - 1), (b + 1));
		while (c == a + 1 && d == b - 1 || c == a - 1 && d == b + 1 || c == a + 1 && d == b + 1 || c == a - 1 && d == b - 1) {
			printf("Blad. Nie mozesz ustawiac plytki na skos");
			d = wczytaj_liczbe((b - 1), (b + 1));

		}
		while (a == c && b == d) {
			printf("Wybrales te same wspolrzedne co (a,b). Wybierz jeszcze raz,inne,zgodnie z zasadami.");
			c = wczytaj_liczbe((a - 1), (a + 1));
			d = wczytaj_liczbe((b - 1), (b + 1));
		}
		printf("Podaj teraz jak chcesz ustawic plytke:\n1.OX\n2.XO: ");
		kierunek = wczytaj_liczbe(1, 2);
		if (kierunek == 1 ) {
			plansza[a][b] = 'O';
			plansza[c][d] = 'X';
			
		}
		else {
			plansza[a][b] = 'X';
			plansza[c][d] = 'O';
		}
	}
}

//konstruktor domyslny
komputer::komputer() :kolkokrzyzyk(), p1(' '), com(' ') {}


//funkcja stawiajaca plytke na wybranym przez komputer miejscu
void komputer::ruch(int dec) {
	if (dec ==1) {
		int a, b, c, d;
		int kierunek;
		printf("Twoja kolej.Wybierz pole podajac (a,b) i (c,d):\n");
		a = wczytaj_liczbe(1, 15);
		b = wczytaj_liczbe(1, 15);
		c = wczytaj_liczbe((a - 1), (a + 1));
		d = wczytaj_liczbe((b - 1), (b + 1));
		while (c == a + 1 && d == b - 1 || c == a - 1 && d == b + 1 || c == a + 1 && d == b + 1 || c == a - 1 && d == b - 1) {
			printf("Blad. Nie mozesz ustawiac plytki na skos");
			d = wczytaj_liczbe((b - 1), (b + 1));
		}
		while (a == c && b == d) {
			printf("Wybrales te same wspolrzedne co (a,b). Wybierz jeszcze raz,inne,zgodnie z zasadami.");
			c = wczytaj_liczbe((a - 1), (a + 1));
			d = wczytaj_liczbe((b - 1), (b + 1));
		}
		printf("Podaj teraz jak chcesz ustawic plytke:\n1.OX\n2.XO: ");
		kierunek=wczytaj_liczbe(1,2);
		if (kierunek == 1) {
			plansza[a][b] = 'O';
			plansza[c][d] = 'X';

		}
		else {
			plansza[a][b] = 'X';
			plansza[c][d] = 'O';
		}
	}
	if (dec == 2) {
		int a, b, c, d;
		int kierunek;
		a = 1 + rand() % (15);  //losujemy wybrane miejsce dla plytki 
		b = 1 + rand() % (15);
		c = (a-1) + rand() % (3);
		d = (b-1) + rand() % (3);
		while (c == a + 1 && d == b - 1 || c == a - 1 && d == b + 1 || c == a + 1 && d == b + 1 || c == a - 1 && d == b - 1) {
			d = (b - 1) + rand() % (3);

		}
		while (a == c && b == d) {
			c = a - 1 + rand() % (3);
			d = b - 1 + rand() % (3);
			while (c == a + 1 && d == b - 1 || c == a - 1 && d == b + 1 || c == a + 1 && d == b + 1 || c == a - 1 && d == b - 1) {
				d = (b - 1) + rand() % (3);
			}
		}
		while (plansza[a][b] != ' ' && plansza[c][d]!=' ') {
			a = 1 + rand() % (15);
			b = 1 + rand() % (15);
			c = (a - 1) + rand() % (3);
			d = (b - 1) + rand() % (3);
			while (c == a + 1 && d == b - 1 || c == a - 1 && d == b + 1 || c == a + 1 && d == b + 1 || c == a - 1 && d == b - 1) {
				d = (b - 1) + rand() % (3);

			}
			while (a == c && b == d) {
				c = a - 1 + rand() % (3);
				d = b - 1 + rand() % (3);
				while (c == a + 1 && d == b - 1 || c == a - 1 && d == b + 1 || c == a + 1 && d == b + 1 || c == a - 1 && d == b - 1) {
					d = (b - 1) + rand() % (3);
				}
			}
		}
		kierunek = 1 + rand() % (2);
		if (kierunek == 1) {
			plansza[a][b] = 'O';
			plansza[c][d] = 'X';

		}
		else {
			plansza[a][b] = 'X';
			plansza[c][d] = 'O';
		}
		printf("Komputer stawia plytke na (%d,%d)(%d,%d)\n", a, b,c,d);
		printf("\nWcisnij \"ENTER\"by kontynuowac \n");
		char pom;
		pom = getchar();
	}
}