#pragma once
#define w(s) wprintf(L##s); //makro ułatwiające zapis wprintf
							//(niestety działające tylko w przypadku braku konieczności drukowania zmiennych

//definicja struktury rankingu
typedef struct {
	wchar_t imie[20];
	int punkty;
} rank;