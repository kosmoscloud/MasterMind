#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <tchar.h>
#include <malloc.h>

#include "funkcje.h"
#include "typedef.h"

extern rank ranking[11];
extern FILE* p;
extern int r;
extern errno_t blad;

//funkcja pozwalająca przemieszczać kursor(bufor) po oknie konsoli
void SHIFT(int x, int y, int czy_x, int czy_y) {	
	CONSOLE_SCREEN_BUFFER_INFO csbi; HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &csbi);
	SetConsoleCursorPosition(handle, (COORD) { (czy_x * csbi.dwCursorPosition.X) + x, (czy_y * csbi.dwCursorPosition.Y) + y });
} 
//argumenty czy_x oraz czy_y są traktowane jako zmienne logiczne
//dla 1 zmiana jest relatywna, a dla 0 zmiana jest niezależna względem aktualnego położenia bufora

//funkcja pomocnicza dla funkcji qsort
int POROWNAJ(const void* a, const void* b) { 
	const rank* oa = a; const rank* ob = b;

	return (oa->punkty > ob->punkty) - (oa->punkty < ob->punkty);
}
//pozwala ona na sortowanie struktury poprzez jeden z jej elementow

//funkcja sortująca oraz przesuwająca wszystkie wyrazy tablicy struktur o 1
void SORTUJ() {
	qsort(ranking, r, sizeof(rank), POROWNAJ);

	for (int i = r - 1; i >= 0; --i) {
		ranking[i + 1] = ranking[i];
	}
}
//pozycja ranking[0] służy za bufor dla funkcji sortującej

//funkcja wypisująca elementy rankingu
void WYSWIETL() {

	if (r == 0) {
		SHIFT(35, 11, 0, 0);
		wprintf(L"    Brak rekordów do wyświetlenia.                                   ");
		for (int i = 1; i < 10; ++i) {
			SHIFT(35, 11 + i, 0, 0); w("                                                                        ");
		}
	}
	else {
		for (int i = 1; i <= r; ++i) {
			SHIFT(35, 11 + i, 0, 0);
			wprintf(L"%d. %s", i, ranking[i].imie); SHIFT(65, 0, 0, 1); wprintf(L"punkty: % d", ranking[i].punkty);
		}
	}
}
//w przypadku braku rekordów informuje o tym fakcie użytkownika

//funkcja pozwalająca na zresetowanie rankingu
void SKASUJ() {
	fclose(p);
	fopen_s(&p, "ranking.rnk", "w");
	if (!blad && p != NULL) {
		fclose(p);
	}
	for (int i = 0; i < 11; ++i) {
		ranking[i] = (rank){(wchar_t)0, 0};
	}
	r = 0;
	WYSWIETL();
}
//zeruje wszystkie elementy tablicy struktur i odświeża widok rankingu
