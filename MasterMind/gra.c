#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>

#include "typedef.h"
#include "intro.h"
#include "funkcje.h"
#define w(s) wprintf(L##s);

//definicje zmiennych opisujących stan próby
int lprob = 0;
int poziom = 0;
int pkol = 25;
int dkol = 60;
int klucz[4];
int nprob = 0;
clock_t t;
int secs;

//deklaracje funkcji zamieszczonych poniżej głównego bloku gry
wchar_t* COLOR(int t);
int PROBA(int* klucz);
int DECOLOR(wchar_t t);
void SHIFT(int x, int y, int czy_x, int czy_y);

//zmienne globalne
extern rank ranking[11];
extern int r;

int GRA() {
	srand((int)time(0));
	
	//instrukcja stworzenia kodu, który gracz będzie usiłował odgadnąć
	for (int i = 0; i < 4; ++i) {
		klucz[i] = (int)round(((float)rand() * 5 / RAND_MAX));
		//instrukcja wypisująca kod na górze ekranu
		//wprintf(L"%ls", COLOR(klucz[i]));
	}

	//menu wybierania poziomu trudności gry (opcja 'ł' dla 999 prób)
	SHIFT(35, 11, 1, 1);
	w("\033[0;1mWybierz poziom trudności:\n");
	SHIFT(35, 1, 1, 1);
	w("\033[0m0 - łatwy (10 prób)\n");
	SHIFT(35, 1, 1, 1);
	w("1 - średni(7 prób)\n");
	SHIFT(35, 1, 1, 1);
	w("2 - trudny(5 prób)");
	short int stop = 0;
	while (!stop) {
		switch (_getch()) {
		case '0':
			poziom = 0;
			nprob = 10;
			stop = 1;
			break;
		case '1':
			poziom = 1;
			nprob = 7;
			stop = 1;
			break;
		case '2':
			poziom = 2;
			nprob = 5;
			stop = 1;
			break;
		case 108:
			poziom = 3;
			nprob = 999;
			stop = 1;
			break;
		case 27:
			system("cls");
			stop = 1;
			return -1;
		default:
			nprob = 0;
			break;
		}
	}

	//odświeżenie okna oraz wypisanie oznaczeń kolorów oraz interfejsu gry
	system("cls");
	SHIFT(pkol - 12, 0, 0, 0);
	w("\033[0;32mz - zielony\033[0m, \033[0;33mż - żółty\033[0m, \033[0;34mn - niebieski\033[0m, \033[0;37mb - biały\033[0m, \033[0;31mc - czerwony\033[0m, \033[0;35m f - fioletowy\033[0m");
	SHIFT(33, 30, 0, 0);
	w("ESC by wyjść z aplikacji...");
	SHIFT(pkol, 5, 0, 0);
	w("\033[0mPRÓBY:");
	SHIFT(dkol, 5, 0, 0);
	w("TRAFIENIA:\n");

	//rozpoczęcie odliczania czasu całej gry oraz pętla odpowiadająca powtórzeniami wybranemu poziomowi trudności
	stop = 0;
	t = clock();
	for (int i = 0; i < nprob && stop == 0; ++i) {
		switch (PROBA(klucz)) {
		
		//przypadek próby trafionej - zatrzymanie zegara oraz zapisanie nazwy użytkownika
		//wzór na liczbę punktów: czas * liczba prób
		case 1:
			t = clock() - t;
			secs = (int)((double)t / CLOCKS_PER_SEC);
			SHIFT(35, 4, 0, 1); wprintf(L"Gratulacje! Liczba prób: %d!", lprob);
			SHIFT(35, 1, 0, 1);	wprintf(L"Czas od rozpoczęcia próby: %ds.", secs);
			SHIFT(35, 1, 0, 1);
			w("Podaj swoje imie: ");
			wscanf_s(L"%s", &(ranking[0].imie), 20);
			ranking[0].punkty = lprob * secs;
			if (r < 10) { r += 1; }
			
			SORTUJ();
			SHIFT(18, 1, 0, 1);

			//menu kontunuowania gry/powrotu do ekranu głównego
			w("Aby kontynuować grę, wciśnij ENTER... (Powrót do ekranu głównego - m)");
			switch (_getch()) {
			case '\r':
				system("cls");
				lprob = 0;
				return 1;
				break;
			case 'm':
				system("cls");
				lprob = 0;
				return -1;
			case 27:
				SHIFT(0, 9, 0, 1);
				return 0;
				break;
			}
			SHIFT(35, 30, 0, 0); w("                           "); SHIFT(0, 25, 0, 0);
			break;
		case -1:
			return 0;
			break;
		}
	}

	//obsłużenie przypadku, w którym gracz nie zdołał odgadnąć kodu w założonej liczbie prób
	w("\n          Liczba możliwych prób została przekroczona. Czy chcesz spróbować ponownie? (ENTER/ESC)");
	while (1) {
		switch (_getch()) {
		case '\r':
			system("cls");
			lprob = 0;
			return 1;
			break;
		case 27:
			SHIFT(0, 9, 0, 1);
			return 0;
			break;
		}
	}
}

//funkcja pojedynczej próby odgadnięcia sekwencji przez użytkownika
int PROBA(int* klucz) {
	lprob += 1;
	if (lprob <= 9) {
		SHIFT(pkol - 3, 0, 0, 1);
		wprintf(L"%d. ", lprob);
	}
	else if (lprob > 9) {
		SHIFT(pkol - 4, 0, 0, 1);
		wprintf(L"%d. ", lprob);
	}
	else {
		SHIFT(pkol - 4, 0, 0, 1);
		wprintf(L"%d. ", lprob);
	}
	
	//definicja tablic - kodu wprowadzanego przez użytkownika, trafień oraz powtórzeń koloru w sekwencji wyjściowej
	int sekw[5] = { 0, 0, 0, 0 };
	int traf[4] = { 0, 0, 0, 0 };
	int koli[6] = { 0, 0, 0, 0 };

	//instrukcja pobrania znaku od użytkownika - omijająca znaki niezdefiniowane oraz pozwalająca na cofanie decyzji
	for (int i = 0; i < 4; ++i) {
		wchar_t proba = _getwch();
		if (proba == 27) {
			SHIFT(0, 30, 0, 0);
			return -1;
		}
		else if (proba == 8) {
			i -= 1;
			CONSOLE_SCREEN_BUFFER_INFO csbi; HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(handle, &csbi);
			if (csbi.dwCursorPosition.X > pkol + 1) {
				w("\b\b \b");
				i -= 1;
			}
		}
		else {
			wprintf(L"%ls", COLOR(DECOLOR(proba)));
			if (DECOLOR(proba) != -1) {
				sekw[i] = DECOLOR(proba);
			}
			else { i -= 1; }
		}
	}

	SHIFT(dkol, 0, 0, 1);

	//algorytm szukający liczby powtórzeń koloru w kodzie tak, aby móc stwierdzić kiedy użytkownik nie trafia,
	//a kiedy znajduje pinezkę o poprawnym kolorze, ale umieszcza ją w złym miejscu
	for (int i = 0; i < 4; ++i) {
		int k = 0;
		if (koli[sekw[i]] == 0) {
			for (int j = 0; j < 4; ++j) {
				if ((sekw[i] == klucz[j])) {
					koli[sekw[i]] += 1; //liczba opisująca ilość powtórzeń kolorów z klucza w sekwencji
				}
			}
		}
	}

	//instrukcja, która dla każdego trafienia aktualizuje tablicę trafień oraz umieszcza informację
	//o trafieniu w tablicy liczby pozostałych powtórzeń kolorów w kodzie
	for (int i = 0; i < 4; ++i) {
		if (sekw[i] == klucz[i]) {
			traf[i] = 1;
			koli[sekw[i]] -= 1;
		}
	}

	//instrukcja oceniająca, czy użytkownik trafia, czy też pudłuje
	for (int i = 0; i < 4; ++i) {
		if (sekw[i] != klucz[i]) {
			if (koli[sekw[i]] != 0) {
				traf[i] = 2;
				koli[sekw[i]] -= 1;
			}
			else if (koli[sekw[i]]) {
				traf[i] = 0;
			}
		}
	}

	short int zlicz = 0;

	//instrukja wypisująca użytkownikowi informację o rezultatach jego ostatniej próby
	for (int i = 0; i < 4; ++i) {
		switch (traf[i]) {
		case 1:
			w("\033[0;32mX \033[0m");
			zlicz += 1;
			break;
		case 2:
			w("\033[0;33m< \033[0m");
			break;
		case 0:
			w("\033[0;31mO \033[0m");
			break;
		default:
			w("\033[0;37m? \033[0m");
			break;
		}
	}
	w("\n");

	//1 dla próby trafionej, 0 - dla nietrafionej
	if (zlicz == 4){
		return 1;
	}
	else {
		return 0;
	}
}

//funkcja konwertująca znaki wprowadzane przez użytkownika na kody kolorów
int DECOLOR(wchar_t t) {
	switch (t) {
	case L'z':
	case L'Z':
		return 0;
		break;
	case L'ż':
	case L'Ż':
		return 1;
		break;
	case L'n':
	case L'N':
		return 2;
		break;
	case L'b':
	case L'B':
		return 3;
		break;
	case L'c':
	case L'C':
		return 4;
		break;
	case L'f':
	case L'F':
		return 5;
		break;
	default:
		return -1;
	}
}

//funkcja przekształcająca kod koloru w kółko o podanym kolorze w formacie wchar_t
wchar_t* COLOR(int i) {
	switch (i) {
	case 0:
		return L"\033[0;32mO ";
		break;
	case 1:
		return L"\033[0;33mO ";
		break;
	case 2:
		return L"\033[0;34mO ";
		break;
	case 3:
		return L"\033[0;37mO ";
		break;
	case 4:
		return L"\033[0;31mO ";
		break;
	case 5:
		return L"\033[0;35mO ";
		break;
	default:
		return L"";
	}
}