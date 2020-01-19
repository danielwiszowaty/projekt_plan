#include <iostream>
#include <string>

using namespace std;

#include "struktury.h"
#include "funkcje.h"

int main(int argc, char* argv[])
{
	string plik = "";
	int ilewierszy = 0;
	int wybor = pobierzArgumenty(argc, argv, plik, ilewierszy);
	switch(wybor){
		case 1:
		{
			if(sprawdzPlik(plik))
			{
				Prowadzacy* pGlowa = nullptr;
				odczytajZPliku(pGlowa, plik);
				wypiszWszystkieZajecia(pGlowa);
				usunWszystko(pGlowa);
				cout<<"Z pliku "<<plik<<" utworzono plany dla kazdego prowadzacego"<<endl;
				return 0;
			}
			else 
			{
				cout<<endl<<"Plik "<<plik<< " jest wadliwy"<<endl;
				return 0;
			}
			break;
		}
		case 2:
		{
			instrukcja();
			return 0;
			break;
		}
		case 3:
		{
			cout<<"Podano zle argumenty do programu\n"<<endl;
			instrukcja();
			return 0;
			break;
		}
		case 4:
		{
			cout<<"Podano za dużo argumentow do programu\n"<<endl;
			instrukcja();
			return 0;
			break;
		}
		case 5:
		{
			generujPlik(ilewierszy, plik);
			cout<<"Wygenerowano plik "<<plik<<".txt w folderze pliki"<<endl;
			return 0;
			break;
		}
	}
	return 0;
}