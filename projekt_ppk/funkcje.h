#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#ifndef FUNKCJE_H
#define FUNKCJE_H

bool Mniejsza(const Zajecia & pLewy, const Zajecia & pPrawy);

string WypiszDzien(Dzien DzienZajec);

Dzien Konwersja(const string& dzionek);

Prowadzacy* ZnajdzProwadzacegoRekurencyjnie (Prowadzacy* pGlowaListyProwadzacych, string nazwisko);

Prowadzacy* DodajProwadzacegoNaKoniecListy (Prowadzacy*& pGlowaListyProwadzacych, string nazwisko);

void DodajZajeciaProwadzacemu (Zajecia*& pKorzen, Godzina& PoczatekZajec, Godzina& KoniecZajec, Dzien& DzienZajec, string& grupa, string& przedmiot);

void WypiszZajeciaProwadzacego(Zajecia* pKorzen);

void WypiszWszystkieZajecia(Prowadzacy*& pGlowaListyProwadzacych);

void UsunDrzewo(Zajecia*& pKorzen);

void UsunWszystko(Prowadzacy*& pGlowaListyProwadzacych);

void Wczytaj(Prowadzacy*& pGlowaListyProwadzacych, string nazwisko, Godzina PoczatekZajec, Godzina KoniecZajec, Dzien DzienZajec, string grupa, string przedmiot);

void Odczyt(const string& nazwapliku, Prowadzacy*& pGlowaListyProwadzacych);

#endif