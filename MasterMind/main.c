#include <stdio.h>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <conio.h>

#include "intro.h"
#include "funkcje.h"
#include "gra.h"
#include "typedef.h"

//zmienne globalne
rank ranking[11];
int r = 0;
FILE* p;
errno_t blad;
//kolejno: tablica struktur przechowująca dane o najlepszych wynikach graczy
//		   liczba aktualnie istniejących rekordów w rankingu
//		   wskaźnik do pliku przechowującego ranking


int main() {
	//otwarcie pliku zawierającego ranking
	blad = fopen_s(&p, "ranking.rnk", "r+");
	if (blad) {
		errno_t blad2 = fopen_s(&p, "ranking.rnk", "w");
		if (!blad2 && p != NULL) {
			w("Błąd w czytaniu rankingu. Gra nie zostanie zapisana. Czy chcesz kontynuować? (ENTER/ESC)");
			int stop = 0;
			while (!stop) {
				switch (_getch()) {
				case 27:
					return 0;
				case '\r':
					stop = 1;
					break;
				default:
					break;
				}
			}
			fclose(p);
		}
	}
	
	//wczytanie danych z pliku do tabeli struktur
	if (!blad && p != NULL) {
	for (int i = 1; i <= 10; ++i) {
			int a = fwscanf_s(p, L"%ls punkty: %d\n", ranking[i].imie, 20, &(ranking[i].punkty));
			if (a == 2) {
				r += 1;
			}
		}
	}

	//ustawienie właściwości okna gry - jego wielkości oraz tytułu
	SMALL_RECT windowSize = { 0 , 0 , 105, 30 };
	SetConsoleTitle(TEXT("Mastermind - projekt zaliczeniowy - Maciej Komosa - 2021/2022 - Programowanie Komputerów"));
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

	//instrukcja pozwalająca na stosowanie polskich znaków - zmiana z char na wchar_t
	(void)_setmode(_fileno(stdout), _O_U16TEXT);
	//(void) dla pominięcia faktu zwracania przez funkcję _setmode wartości

	//pętla gry
	int stop = 0;
	while (!stop) {
		switch (START()) {
		case 1:
			system("cls");
			int stop1 = 0;
			while (!stop1) {
				switch (GRA()) {
				case 1:
					break;
				case 0:
					stop1 = 1;
					stop = 1;
					break;
				case -1:
					stop1 = 1;
					break;
				}
			}
			break;
		case 0:
			stop = 1;
			break;

		default:
			break;
		}
	}
	//zapisanie wyników do pliku
	//zamknięcie pliku i otworzenie go w trybie do zapisu, który automatycznie usuwa wszystkie dane zawarte w pliku
	if (!blad && p != NULL) {
		fclose(p);
	}
	errno_t blad4 = fopen_s(&p, "ranking.rnk", "w");
	if (!blad4 && p != NULL) {
		for (int i = 1; i <= r; ++i) {
			fwprintf_s(p, L"%s punkty: %d\n", ranking[i].imie, ranking[i].punkty);
		}
		fclose(p);
	}
	
	return 0;
}