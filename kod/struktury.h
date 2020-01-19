/** @file */

#include <string>  

using namespace std;

#ifndef STRUKTURY_H
#define STRUKTURY_H

/** Typ wyliczeniowy reprezentujacy dni planu zajec */
enum Dzien{
    pn, ///<
    wt, 
    sr, 
    cz, 
    pt, 
    sb, 
    nd
};
/** Struktura reprezentująca godzinę */
struct Godzina {
    int Godzinka; ///<
    int Minuta;
};

/** Węzeł drzewa poszukiwań binarnych */
struct Zajecia{
    Godzina PoczatekZajec; ///< godzina początku zajęć przechowywana w węźle
    Godzina KoniecZajec;   ///< godzina końca zajęć przechowywana w węźle
    Dzien DzienZajec;      ///< dzien przechowywany w węźle
    string Grupa;          ///< grupa przechowywana w węźle
    string Przedmiot;      ///< przedmioty przechowywany w węźle
    Zajecia* pLewy;        ///< adres lewego potomka
    Zajecia* pPrawy;       ///< adres prawego potomka
};

/** Lista jednokierunkowa*/
struct Prowadzacy{
    string NazwiskoProwadzacego;     ///< nazwisko przechowywane w liście
    Prowadzacy* pNastepnyProwadzacy; ///< adres następnego prowadzącego
    Zajecia* pKorzenListyZajec;      ///< adres węzła drzewa poszukiwań binarnych
};

#endif
