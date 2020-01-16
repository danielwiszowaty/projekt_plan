#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "struktury.h"
#include "funkcje.h"

int main()
{
    Prowadzacy * pGlowa = nullptr;
	Odczyt("plik.txt", pGlowa);
    WypiszWszystkieZajecia(pGlowa);
    UsunWszystko(pGlowa);

    return 0;
}