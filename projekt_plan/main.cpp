#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
#include <vector>
#include <regex>

using namespace std;

#include "struktury.h"
#include "funkcje.h"

int main(int argc, char* argv[])
{
	string plik = "";
	int ilewierszy = 0;
	int wybor = OdczytajArgumenty(argc, argv, plik, ilewierszy);
	switch(wybor){
		case 1:
		{
			if(SprawdzPlik(plik))
			{
				Prowadzacy* pGlowa = nullptr;
				OdczytajZPliku(pGlowa, plik);
				WypiszWszystkieZajecia(pGlowa);
				UsunWszystko(pGlowa);
				cout<<"Utworzono pliki dla kazdego prowadzacego w folderze pliki_txt"<<endl;
				return 0;
			}
			return 0;
		}
		case 2:
		{
			Instrukcja();
			return 0;
		}
		case 3:
		{
			cout<<"Podano zle argumenty do programu\n"<<endl;
			Instrukcja();
			return 0;
		}
		case 4:
		{
			cout<<"Podano za dużo argumentow do programu\n"<<endl;
			Instrukcja();
			return 0;
		}
		case 5:
		{
			GenerujPlik(ilewierszy, plik);
			cout<<"Wygenerowano plik "<<plik<<" w folderze pliki_txt ktory zawiera "<<ilewierszy<<" wierszy"<<endl;
			return 0;
		}
	}
	return 0;
}
