
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

#include "struktury.h"
#include "funkcje.h"

/** */
bool Mniejsza(const Zajecia & pLewy, const Zajecia & pPrawy)
{
    if(pLewy.DzienZajec < pPrawy.DzienZajec)
        return true;
    else if(pLewy.DzienZajec > pPrawy.DzienZajec)
        return false;
    else // dni takie same, porownujemy godziny
    {
        if(pLewy.PoczatekZajec.Godzinka < pPrawy.PoczatekZajec.Godzinka)
            return true;
        else if(pLewy.PoczatekZajec.Godzinka > pPrawy.PoczatekZajec.Godzinka)
            return false;
        else // godziny takie same, porownujemy minuty
        {
            if(pLewy.PoczatekZajec.Minuta < pPrawy.PoczatekZajec.Minuta)
                return true;
            else 
                return false;
        }
    }
}

/** funkcja wypisujaca enum jako string */
string WypiszDzien(Dzien DzienZajec){
    switch(DzienZajec)
    {
        case pn: return "pn"; break;
        case wt: return "wt"; break;
        case sr: return "sr"; break;
        case cz: return "cz"; break;
        case pt: return "pt"; break;
        case sb: return "sb"; break;
        case nd: return "nd"; break;
        default: return ""; break;
    }
}

Dzien Konwersja(string& dzionek){
    if(dzionek == "pn") return pn;
    else if (dzionek == "wt") return wt;
    else if (dzionek == "sr") return sr;
    else if (dzionek == "cz") return cz;
    else if (dzionek == "pt") return pt;
    else if (dzionek == "sb") return sb;
    else if (dzionek == "nd") return nd;
    //end of non void function
    //else return 
}

/** funkcja zwracajaca wskaznik na szukanego prowadzacego */
Prowadzacy* ZnajdzProwadzacegoRekurencyjnie (Prowadzacy* pGlowaListyProwadzacych, string nazwisko){
    //jeśli istnieje
    if (pGlowaListyProwadzacych)
    {
        //jeśli znaleźliśmy prowadzącego zwrócić wskaźnik
        if (pGlowaListyProwadzacych->NazwiskoProwadzacego == nazwisko)
            return pGlowaListyProwadzacych;
        //jeśli nie znaleźlismy szukaj dalej
        else
            return ZnajdzProwadzacegoRekurencyjnie(pGlowaListyProwadzacych->pNastepnyProwadzacy, nazwisko);
    }
    //nie ma takiego prowadzacego i zwraca nullptr
    else
        return nullptr;
}

/** funkcja dodajaca prowadzacego na koniec listy jednokierunkowej */
Prowadzacy* DodajProwadzacegoNaKoniecListy (Prowadzacy*& pGlowaListyProwadzacych, string nazwisko)
{
    if(not pGlowaListyProwadzacych)
        return pGlowaListyProwadzacych = new Prowadzacy {nazwisko, nullptr, nullptr };
    else
        return DodajProwadzacegoNaKoniecListy(pGlowaListyProwadzacych->pNastepnyProwadzacy, nazwisko);
}

/** funkcja ktora dodaje posortowane zajecia */
void DodajZajeciaProwadzacemu (Zajecia*& pKorzen, Godzina& PoczatekZajec, Godzina& KoniecZajec, Dzien& DzienZajec, string& grupa, string& przedmiot)
{
    auto pNowy = new Zajecia {PoczatekZajec, KoniecZajec, DzienZajec, grupa, przedmiot, nullptr, nullptr};
    
    if(not pKorzen)
        pKorzen = pNowy;
    else
    {
      auto p = pKorzen;
      while(true)
      {
          if (Mniejsza (*pNowy, *p))  // nowy jest mniejszy od p
        {
          if(p->pLewy)
            p = p->pLewy;
          else
          {
            p->pLewy = pNowy;
            return;
          }
        }
        else
        {
          if(p->pPrawy)
            p = p->pPrawy;
          else
          {
            p->pPrawy = pNowy;
            return;
          }
        }
      }
   }
}

/** funkcja wypisujaca posortowane zajecia prowadzacego*/
//inorder traversal
void WypiszZajeciaProwadzacego(Zajecia* pKorzen){
    //jesli istnieje
    if (pKorzen)
    {
        WypiszZajeciaProwadzacego(pKorzen->pLewy);
            cout<<setw(2)<<setfill('0')<<pKorzen->PoczatekZajec.Godzinka<<
            ":"<<setw(2)<<setfill('0')<<pKorzen->PoczatekZajec.Minuta<<
            "-"<<setw(2)<<setfill('0')<<pKorzen->KoniecZajec.Godzinka<<
            ":"<<setw(2)<<setfill('0')<<pKorzen->KoniecZajec.Minuta<<
            " "<<WypiszDzien(pKorzen->DzienZajec)<<
            " "<<pKorzen->Grupa<<
            " "<<pKorzen->Przedmiot<<endl;
        WypiszZajeciaProwadzacego(pKorzen->pPrawy);
    }
}

void WypiszWszystkieZajecia(Prowadzacy*& pGlowaListyProwadzacych){
    if(pGlowaListyProwadzacych)
    {
        WypiszZajeciaProwadzacego(pGlowaListyProwadzacych->pKorzenListyZajec);
        cout<<endl;
        auto p = pGlowaListyProwadzacych->pNastepnyProwadzacy;
        WypiszWszystkieZajecia(p);

    }
}

/** funkcja usuwajaca drzewo zajec */
void UsunDrzewo(Zajecia*& pKorzen){
    //jesli korzen istnieje
    if (pKorzen)
        {
            //usun drzewo rekurencyjnie
            UsunDrzewo(pKorzen->pLewy);
            UsunDrzewo(pKorzen->pPrawy);
            //usun korzen i wskaznik na korzen
            delete pKorzen;
            pKorzen = nullptr;
        }
}

//usun drzewo-> wskaznik na nastepnego prowadzacego-> usun poprzedniego i wskaznik
//potem rekurencja
/** funkcja usuwajaca liste i wszystkie drzewa */
void UsunWszystko(Prowadzacy*& pGlowaListyProwadzacych){
    //jesli prowadzacy istnieje
    if (pGlowaListyProwadzacych)
    {
        UsunDrzewo(pGlowaListyProwadzacych->pKorzenListyZajec);
        //przechodzimy do nastepnego prowadzacego;
        auto p = pGlowaListyProwadzacych->pNastepnyProwadzacy;
        delete pGlowaListyProwadzacych;
        pGlowaListyProwadzacych = nullptr;
        //krok rekurencyjny przechodzacy do nastepnego prowadzacego
        UsunWszystko(p);
    }
}

void Wczytaj(Prowadzacy*& pGlowaListyProwadzacych, string nazwisko, Godzina PoczatekZajec, Godzina KoniecZajec, Dzien DzienZajec, string grupa, string przedmiot){
    Prowadzacy* p = ZnajdzProwadzacegoRekurencyjnie(pGlowaListyProwadzacych, nazwisko);
        if (not p)
        p = DodajProwadzacegoNaKoniecListy(pGlowaListyProwadzacych, nazwisko);
    DodajZajeciaProwadzacemu(p->pKorzenListyZajec, PoczatekZajec, KoniecZajec, DzienZajec, grupa, przedmiot);
}

void Odczyt(const string& nazwapliku, Prowadzacy*& pGlowaListyProwadzacych){
    ifstream plik;
	plik.open(nazwapliku); //otwieranie pliku 
	
		if (plik.good() == false) //sprawdzenie czy plik moze byc otwarty 
		{
			plik.close();
		}
		else
		{
				Godzina PoczatekZajec {0,0};
                Godzina KoniecZajec {0,0};
                string DzienZajec = "";
                string grupa = "";
                string nazwisko = "";
                string przedmiot = "";
				char znak = 0;
                char znak1= 0;
                char znak2 = 0;
				while (!plik.eof())
				{

					plik >> PoczatekZajec.Godzinka;
					plik >> znak;
					plik >> PoczatekZajec.Minuta;
					plik >> znak1;
					plik >> KoniecZajec.Godzinka;
					plik >> znak2;
					plik >> KoniecZajec.Minuta;
					plik >> DzienZajec;
					plik >> grupa;
					plik >> nazwisko;
					plik >> przedmiot;
					
					Wczytaj(pGlowaListyProwadzacych, nazwisko, PoczatekZajec, KoniecZajec, Konwersja(DzienZajec), grupa, przedmiot);
               
				}
		}
		plik.close(); 
	}