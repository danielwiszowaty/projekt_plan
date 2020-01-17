
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

#include "struktury.h"
#include "funkcje.h"

/** Funkcja porówująca dzień następnie godzinę początkową i końcową */
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
        else // godziny poczatkowe takie same, porownujemy minuty
        {
            if(pLewy.PoczatekZajec.Minuta < pPrawy.PoczatekZajec.Minuta)
                return true;
            else if(pLewy.PoczatekZajec.Minuta > pPrawy.PoczatekZajec.Minuta)
                return false;
            else // minuty takie same, porownujemy godziny konca zajec
            {
                if(pLewy.KoniecZajec.Godzinka < pPrawy.KoniecZajec.Godzinka)
                  return true;
                else if(pLewy.KoniecZajec.Godzinka > pPrawy.KoniecZajec.Godzinka)
                  return false;
                else // godziny koncowe takie same, porownujemy minuty
                {
                    if(pLewy.KoniecZajec.Minuta < pPrawy.KoniecZajec.Minuta)
                        return true;
                    else
                        return false;
                }
            } 
        }
    }
}

/** Funkcja konwertująca enum na string */
string EnumNaString(Dzien DzienZajec){
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

/** Funkcja konwertująca string na enum */
Dzien StringNaEnum(string& dzien){
    if(dzien == "pn") return pn;
    else if (dzien == "wt") return wt;
    else if (dzien == "sr") return sr;
    else if (dzien == "cz") return cz;
    else if (dzien == "pt") return pt;
    else if (dzien == "sb") return sb;
    else return nd;
}

/** Funkcja zwracajaca wskaznik na szukanego prowadzacego */
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

/** Funkcja dodajaca prowadzacego na koniec listy jednokierunkowej */
Prowadzacy* DodajProwadzacegoNaKoniecListy (Prowadzacy*& pGlowaListyProwadzacych, string nazwisko)
{
    //jeśli nie ma listy to ją utwórz
    if(not pGlowaListyProwadzacych)
        return pGlowaListyProwadzacych = new Prowadzacy {nazwisko, nullptr, nullptr };
    //dodaj rekurencyjnie na koniec listy
    else
        return DodajProwadzacegoNaKoniecListy(pGlowaListyProwadzacych->pNastepnyProwadzacy, nazwisko);
}

/** Funkcja dodająca zajęcia do drzewa binarnego */
void DodajZajeciaProwadzacemu (Zajecia*& pKorzen, Godzina& PoczatekZajec, Godzina& KoniecZajec, Dzien& DzienZajec, string& grupa, string& przedmiot)
{
    auto pNowy = new Zajecia {PoczatekZajec, KoniecZajec, DzienZajec, grupa, przedmiot, nullptr, nullptr};
    
    //jesli nie ma to utworz nowy korzen
    if(not pKorzen)
        pKorzen = pNowy;
    else
    {
      auto p = pKorzen;
      while(true)
      {
        // nowy jest mniejszy od p
          if (Mniejsza (*pNowy, *p))  
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

/** Funkcja wypisujaca posortowane zajecia prowadzacego*/
//inorder traversal
void WypiszZajeciaProwadzacego(Zajecia* pKorzen, ofstream& strumien){
    //jesli istnieje
    if (pKorzen)
    {
		 WypiszZajeciaProwadzacego(pKorzen->pLewy, strumien);
            strumien<<setw(2)<<setfill('0')<<pKorzen->PoczatekZajec.Godzinka<<
            ":"<<setw(2)<<setfill('0')<<pKorzen->PoczatekZajec.Minuta<<
            "-"<<setw(2)<<setfill('0')<<pKorzen->KoniecZajec.Godzinka<<
            ":"<<setw(2)<<setfill('0')<<pKorzen->KoniecZajec.Minuta<<
            " "<<EnumNaString(pKorzen->DzienZajec)<<
            " "<<pKorzen->Grupa<<
            " "<<pKorzen->Przedmiot<<endl;
        WypiszZajeciaProwadzacego(pKorzen->pPrawy, strumien);
    }
}
/** Funkcja wypisująca zajęcia każdego prowadzącego */
void WypiszWszystkieZajecia(Prowadzacy*& pGlowaListyProwadzacych){
    //jeśli istnieje
    if(pGlowaListyProwadzacych)
    {
		string wyjscie = pGlowaListyProwadzacych->NazwiskoProwadzacego + ".txt";
		ofstream plik(wyjscie);
        WypiszZajeciaProwadzacego(pGlowaListyProwadzacych->pKorzenListyZajec, plik);
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
/** Funkcja tworząca element listy o takim samym nazwisku a następnie przypisuje mu zajęcia */
void Wczytaj(Prowadzacy*& pGlowaListyProwadzacych, string nazwisko, Godzina PoczatekZajec, Godzina KoniecZajec, Dzien DzienZajec, string grupa, string przedmiot){
    Prowadzacy* p = ZnajdzProwadzacegoRekurencyjnie(pGlowaListyProwadzacych, nazwisko);
        if (not p)
        p = DodajProwadzacegoNaKoniecListy(pGlowaListyProwadzacych, nazwisko);
    DodajZajeciaProwadzacemu(p->pKorzenListyZajec, PoczatekZajec, KoniecZajec, DzienZajec, grupa, przedmiot);
}
/** Funkcja odczytująca elementy z pliku a następnie wczytująca je do dynamicznej struktury */
bool Odczyt(const string& nazwapliku, Prowadzacy*& pGlowaListyProwadzacych){
    bool plikistnieje=false;
    ifstream plik;
	plik.open(nazwapliku); //otwieranie pliku 
	
		if (!plik.good()) //sprawdzenie czy plik moze byc otwarty 
		{
			plik.close();
            return plikistnieje;
		}
		else
		{
                plikistnieje = true;
				Godzina PoczatekZajec {0,0};
                Godzina KoniecZajec {0,0};
                string DzienZajec = "";
                string grupa = "";
                string nazwisko = "";
                string przedmiot = "";
				char znak = 0;
				while (!plik.eof())
				{
					plik >> PoczatekZajec.Godzinka;
					plik >> znak;
					plik >> PoczatekZajec.Minuta;
					plik >> znak;
					plik >> KoniecZajec.Godzinka;
					plik >> znak;
					plik >> KoniecZajec.Minuta;
					plik >> DzienZajec;
					plik >> grupa;
					plik >> nazwisko;
					plik >> przedmiot;
					
					Wczytaj(pGlowaListyProwadzacych, nazwisko, PoczatekZajec, KoniecZajec, StringNaEnum(DzienZajec), grupa, przedmiot);
				}
		}
		plik.close(); 
        return plikistnieje;
}