#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#include "typedef.h"
#include "funkcje.h"

//zmienne globalne
extern rank ranking[11];
extern FILE* p;
extern errno_t blad;

//deklaracja funkcji znajdującej się pod blokiem wstępu
int GET();

//funkcja wyświetlająca ekrany: startu, rankingu, instrukcji, informacji o programie 
//oraz pozwalająca na przemieszczanie się pomiędzy tymi widokami
int START() {
	system("cls");
	SHIFT(0, 7, 0, 0);
	w("            ███╗   ███╗ █████╗ ███████╗████████╗███████╗██████╗ ███╗   ███╗██╗███╗   ██╗██████╗             \n");
	w("            ████╗ ████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗████╗ ████║██║████╗  ██║██╔══██╗            \n");
	w("            ██╔████╔██║███████║███████╗   ██║   █████╗  ██████╔╝██╔████╔██║██║██╔██╗ ██║██║  ██║            \n");
	w("            ██║╚██╔╝██║██╔══██║╚════██║   ██║   ██╔══╝  ██╔══██╗██║╚██╔╝██║██║██║╚██╗██║██║  ██║            \n");
	w("            ██║ ╚═╝ ██║██║  ██║███████║   ██║   ███████╗██║  ██║██║ ╚═╝ ██║██║██║ ╚████║██████╔╝            \n");
	w("            ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═════╝             \n");
	SHIFT(0, 2, 0, 1);  w("\033[1m");
	w("                                         START - naciśnij ENTER                                              \033[0m");
	SHIFT(0, 2, 0, 1);
	w("                                          RANKING - naciśnij r                                                 ");
	SHIFT(0, 2, 0, 1);
	w("                                           POMOC - naciśnij h                                                  ");
	SHIFT(0, 2, 0, 1);
	w("                                         INFORMACJE - naciśnij i                                               ");
	SHIFT(0, 11, 0, 1);
	w("                                         WYJŚCIE - naciśnij ESC");
	
	return GET();
	
}

int GET() {
	switch (_getch()) {
	case 27:
		SHIFT(0, 1, 0, 1);
		return 0;
		break;
	case '\r':
		return 1;
		break;
	case 'r':
		system("cls");
		SHIFT(0, 4, 0, 0);
		w("                           ██████╗  █████╗ ███╗   ██╗██╗  ██╗██╗███╗   ██╗ ██████╗                          \n");
		w("                           ██╔══██╗██╔══██╗████╗  ██║██║ ██╔╝██║████╗  ██║██╔════╝                          \n");
		w("                           ██████╔╝███████║██╔██╗ ██║█████╔╝ ██║██╔██╗ ██║██║  ███╗                         \n");
		w("                           ██╔══██╗██╔══██║██║╚██╗██║██╔═██╗ ██║██║╚██╗██║██║   ██║                         \n");
		w("                           ██║  ██║██║  ██║██║ ╚████║██║  ██╗██║██║ ╚████║╚██████╔╝                         \n");
		w("                           ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝                          \n");
		WYSWIETL();
		SHIFT(0, 29, 0, 0); w("                                 Aby zresetować ranking, wciśnij klawisz 'e'...");
		SHIFT(0, 30, 0, 0); w("                           Naciśnij klawisz ESC aby powrócić do ekranu startowego...");
		
		if (p == NULL) {
			SHIFT(0, 29, 0, 0); w("                                                                            ");
			wprintf(L"\n\n\nNie można załadować rankingu.");
			while (1) {
				char c = _getch();
				if (c == 27) {
					system("cls");
					return -1;
					break;
				}
			}
		}
	
		while (1) {
			char c = _getch();
			if (c == 27) {
				system("cls");
				return -1;
				break;
			}
			else if (c == 'e') {
				SKASUJ();
				SHIFT(0, 9, 0, 0);
				WYSWIETL();
			}
		}
		return 2;
		break;
	case 'h':
		system("cls");
		SHIFT(0, 3, 0, 1);
		w("              ███████╗ █████╗ ███████╗ █████╗ ██████╗ ██╗   ██╗     ██████╗ ██████╗ ██╗   ██╗               \n");
		w("              ╚══███╔╝██╔══██╗██╔════╝██╔══██╗██╔══██╗╚██╗ ██╔╝    ██╔════╝ ██╔══██╗╚██╗ ██╔╝               \n");
		w("                ███╔╝ ███████║███████╗███████║██║  ██║ ╚████╔╝     ██║  ███╗██████╔╝ ╚████╔╝                \n");
		w("               ███╔╝  ██╔══██║╚════██║██╔══██║██║  ██║  ╚██╔╝      ██║   ██║██╔══██╗  ╚██╔╝                 \n");
		w("              ███████╗██║  ██║███████║██║  ██║██████╔╝   ██║       ╚██████╔╝██║  ██║   ██║                  \n");
		w("              ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝    ╚═╝        ╚═════╝ ╚═╝  ╚═╝   ╚═╝                  \n");
		w("\n");
		w("             Celem gry jest odgadnięcie kodu składającego się z czterech kolorowych pinezek                 \n");
		w("          w skończonej liczbie podejść (10 - poziom łatwy, 7 - poziom średni, 5 - poziom trudny).           \n");
		w("                  Po każdej próbie komputer zwraca informację na temat celności próby                       \n");
		w("          X - dobry kolor, właściwe miejsce, > - dobry kolor, złe miejsce, O - zły kolor i miejsce          \n\n");
		w("                   Gracz zgaduje kombinację poprzez wpisywanie kolorów, odpowiednio:                            \n");
		w("\033[0;32m                                              z - zielony                                                          \n");
		w("\033[0;33m                                              ż - żółty                                                            \n");
		w("\033[0;34m                                              n - niebieski                                                        \n");
		w("\033[0;37m                                              b - biały                                                            \n");
		w("\033[0;31m                                              c - czerwony                                                         \n");
		w("\033[0;35m                                              f - fioletowy                                                        \033[0m\n");
		w("\n          Przykład: prawidłową kombinacją jest \033[0;32mO \033[0;33mO \033[0;34mO \033[0;31mO\033[0m, a gracz wprowadza kombinację (\033[0;35mf \033[0;33mż \033[0;35mf \033[0;34mn\033[0m),\n");
		w("                     Informacją zwrotną od komputera będzie w takim przypadku O X O <.                                 ");
		SHIFT(0, 6, 0, 1);
		w("                           Naciśnij klawisz ESC aby powrócić do ekranu startowego...");
		while (1) {
			char c = _getch();
			if (c == 27) {
				system("cls");
				return -1;
				break;
			}
		}
		break;
	case 'i':
		system("cls");
		SHIFT(0, 7, 0, 1);
		w("             ██████╗     ██████╗ ██████╗  ██████╗  ██████╗ ██████╗  █████╗ ███╗   ███╗██╗███████╗            \n");
		w("            ██╔═══██╗    ██╔══██╗██╔══██╗██╔═══██╗██╔════╝ ██╔══██╗██╔══██╗████╗ ████║██║██╔════╝            \n");
		w("            ██║   ██║    ██████╔╝██████╔╝██║   ██║██║  ███╗██████╔╝███████║██╔████╔██║██║█████╗              \n");
		w("            ██║   ██║    ██╔═══╝ ██╔══██╗██║   ██║██║   ██║██╔══██╗██╔══██║██║╚██╔╝██║██║██╔══╝              \n");
		w("            ╚██████╔╝    ██║     ██║  ██║╚██████╔╝╚██████╔╝██║  ██║██║  ██║██║ ╚═╝ ██║██║███████╗            \n");
		w("             ╚═════╝     ╚═╝     ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚══════╝            \n");
		w("\n");
		w("                 Program stworzony przez Macieja Komosę w ramach projektu zaliczeniowego\n");
		w("                z kursu Programowania Komputerów, IiE rok 1, rok akademicki 2021/22, WZ AGH\n");
		SHIFT(0, 30, 0, 0);
		w("                           Naciśnij klawisz ESC aby powrócić do ekranu startowego...");
		while (1) {
			char c = _getch();
			if (c == 27) {
				system("cls");
				return -1;
				break;
			}
		}
		break;
	default:
		return -1;
	}
}