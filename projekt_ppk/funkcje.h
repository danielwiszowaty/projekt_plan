#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#ifndef FUNKCJE_H
#define FUNKCJE_H

bool Mniejsza(const Zajecia & pLewy, const Zajecia & pPrawy);

string StringNaEnum(Dzien DzienZajec);

Dzien EnumNaString(const string& dzien);

Prowadzacy* ZnajdzProwadzacegoRekurencyjnie (Prowadzacy* pGlowaListyProwadzacych, string nazwisko);

Prowadzacy* DodajProwadzacegoNaKoniecListy (Prowadzacy*& pGlowaListyProwadzacych, string nazwisko);

void DodajZajeciaProwadzacemu (Zajecia*& pKorzen, Godzina& PoczatekZajec, Godzina& KoniecZajec, Dzien& DzienZajec, string& grupa, string& przedmiot);

void WypiszZajeciaProwadzacego(Zajecia* pKorzen, ofstream& strumien);

void WypiszWszystkieZajecia(Prowadzacy*& pGlowaListyProwadzacych);

void UsunDrzewo(Zajecia*& pKorzen);

void UsunWszystko(Prowadzacy*& pGlowaListyProwadzacych);

void Wczytaj(Prowadzacy*& pGlowaListyProwadzacych, string nazwisko, Godzina PoczatekZajec, Godzina KoniecZajec, Dzien DzienZajec, string grupa, string przedmiot);

bool Odczyt(const string& nazwapliku, Prowadzacy*& pGlowaListyProwadzacych);

#endif