#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
#include <vector>
#include <regex>
#include <chrono>

using namespace std;

#ifndef FUNKCJE_H
#define FUNKCJE_H

bool Mniejsza(const Zajecia& pLewy, const Zajecia& pPrawy);

Dzien EnumNaString(const string& dzien);

string StringNaEnum(Dzien DzienZajec);

Prowadzacy* ZnajdzProwadzacegoRekurencyjnie (Prowadzacy* pGlowaListyProwadzacych, string nazwisko);

Prowadzacy* DodajProwadzacegoNaKoniecListy (Prowadzacy*& pGlowaListyProwadzacych, string nazwisko);

void DodajZajeciaProwadzacemu (Zajecia*& pKorzen, Godzina& PoczatekZajec, Godzina& KoniecZajec, Dzien& DzienZajec, string& grupa, string& przedmiot);

void WypiszZajeciaProwadzacego(Zajecia* pKorzen, ofstream& strumien);

void WypiszWszystkieZajecia(Prowadzacy*& pGlowaListyProwadzacych);

void UsunDrzewo(Zajecia*& pKorzen);

void UsunWszystko(Prowadzacy*& pGlowaListyProwadzacych);

void WczytajZajeciaProwadzacemu(Prowadzacy*& pGlowaListyProwadzacych, string nazwisko, Godzina PoczatekZajec, Godzina KoniecZajec, Dzien DzienZajec, string grupa, string przedmiot);

bool OdczytajZPliku(Prowadzacy*& pGlowaListyProwadzacych, string& nazwapliku);

bool SprawdzPlik(string& nazwapliku);

int Silnik(size_t min, size_t max);

void GenerujPlik(int ile, string& nazwapliku);
	
void Instrukcja();

int WierszPolecen(int argc, char* argv[], string& nazwapliku, int& ile);

#endif