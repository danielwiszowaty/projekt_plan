#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "struktury.h"
#include "funkcje.h"

int main()
{
    Prowadzacy * pGlowa = nullptr;
    string kowal = "Kowalski";
    string zbych = "Zbyszek";
    string stach = "Staszek";
    Godzina GodzinaP {14,12};
    Godzina GodzinaK {18,21};
    Godzina GodzinaP1 {13,14};
    Godzina GodzinaK1 {18,21};
    Godzina GodzinaP2 {12,17};
    Godzina GodzinaK2  {18,21};
    Godzina GodzinaP3 {7,17};
    Godzina GodzinaK3  {8,14};
    string grupa = "gr2";
    string przedmiot = "amial";
    string grupa2 = "gr3";
    string przedmiot2 = "tuc";
    Dzien dzien = pt;
    Dzien dzien2 = pn;
    Dzien dzien3 = sr;

    Wczytaj(pGlowa, kowal, GodzinaP, GodzinaK, dzien, grupa, przedmiot);
    Wczytaj(pGlowa, kowal, GodzinaP2, GodzinaK2, dzien, grupa, przedmiot);
    Wczytaj(pGlowa, kowal, GodzinaP3, GodzinaK3, dzien, grupa, przedmiot);
    Wczytaj(pGlowa, zbych, GodzinaP, GodzinaK, dzien, grupa, przedmiot2);
    Wczytaj(pGlowa, kowal, GodzinaP3, GodzinaK3, dzien, grupa, przedmiot);
    Wczytaj(pGlowa, zbych, GodzinaP, GodzinaK, dzien, grupa, przedmiot2);
    Wczytaj(pGlowa, kowal, GodzinaP3, GodzinaK3, dzien, grupa, przedmiot);
    Wczytaj(pGlowa, zbych, GodzinaP, GodzinaK, dzien, grupa, przedmiot2);
    Wczytaj(pGlowa, stach, GodzinaP2, GodzinaK2, dzien, grupa, przedmiot2);
    Wczytaj(pGlowa, kowal, GodzinaP3, GodzinaK3, dzien, grupa, przedmiot);
    Wczytaj(pGlowa, zbych, GodzinaP, GodzinaK, dzien, grupa, przedmiot2);

    WypiszWszystkieZajecia(pGlowa);
    UsunWszystko(pGlowa);

    return 0;
}