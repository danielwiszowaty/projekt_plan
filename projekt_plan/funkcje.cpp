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
	string wyjscie = "../pliki_txt/" + pGlowaListyProwadzacych->NazwiskoProwadzacego + ".txt";
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
void WczytajZajeciaProwadzacemu(Prowadzacy*& pGlowaListyProwadzacych, string nazwisko, Godzina PoczatekZajec, Godzina KoniecZajec, Dzien DzienZajec, string grupa, string przedmiot){
    Prowadzacy* p = ZnajdzProwadzacegoRekurencyjnie(pGlowaListyProwadzacych, nazwisko);
        if (not p)
        p = DodajProwadzacegoNaKoniecListy(pGlowaListyProwadzacych, nazwisko);
    DodajZajeciaProwadzacemu(p->pKorzenListyZajec, PoczatekZajec, KoniecZajec, DzienZajec, grupa, przedmiot);
}

/** Funkcja odczytująca elementy z pliku a następnie wczytująca je do dynamicznej struktury */
bool OdczytajZPliku(Prowadzacy*& pGlowaListyProwadzacych, const string& nazwapliku){
    ifstream plik;
	plik.open("../pliki_txt/" + nazwapliku + ".txt"); //otwieranie pliku 
	
		if (!plik.good()) //sprawdzenie czy plik moze byc otwarty 
		{
			plik.close();
            		return false;
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
			WczytajZajeciaProwadzacemu(pGlowaListyProwadzacych, nazwisko, PoczatekZajec, KoniecZajec, StringNaEnum(DzienZajec), grupa, przedmiot);
			}
		}
		plik.close(); 
       		return true;
}

int Silnik(size_t min, size_t max){
    random_device r;
    default_random_engine e1(r());
    uniform_int_distribution<size_t> uniform_dist(min,max);
    int liczba = uniform_dist(e1);
    return liczba;
}

void GenerujPlik(int ile, string& nazwapliku){
    string wyjscie = "../pliki_txt/" + nazwapliku + ".txt";
    ofstream plik(wyjscie);
    vector<string> Nazwiska = {"Nowak", "Kowalski", "Lewandowski", "Zielinski"};
    //vector<string> Nazwiska = {"Nowak", "Kowalski", "Lewandowski", "Zielinski", "Wojcik", "Kowalczyk", "Kaminska", "Lewandowska", "Dabrowska", "Zielinska"};
    vector<string> Przedmioty = {"Programowanie", "Java", "Fizyka", "Matematyka", "Historia", "Przyroda", "Geografia"};
    vector<string> Dni = {"pn", "wt", "sr", "cz", "pt", "sb", "nd"};
    string grupa = "gr";

    for (int i=0; i<ile; i++)
    {
            
           plik<<setw(2)<<setfill('0')<<Silnik(0,23)<<
            ":"<<setw(2)<<setfill('0')<<Silnik(0,59)<<
            "-"<<setw(2)<<setfill('0')<<Silnik(0,23)<<
            ":"<<setw(2)<<setfill('0')<<Silnik(0,59)<<
            " "<<Dni[Silnik(0,Dni.size()-1)]<<
            " "<<grupa<<Silnik(1,9)<<
            " "<<Nazwiska[Silnik(0,Nazwiska.size()-1)]<<
            " "<<Przedmioty[Silnik(0,Przedmioty.size()-1)]<<endl;
    }
}

bool SprawdzPlik(string& nazwapliku){
    string wejscie = "../pliki_txt/" + nazwapliku + ".txt";
    ifstream plik(wejscie);
    string linia;
    bool poprawnedane=false;
    regex kod("^([01]\\d|2[0-3]):([0-5]\\d)-([01]\\d|2[0-3]):([0-5]\\d) (pn|wt|sr|cz|pt|sb|nd) (gr[1-9]) ([A-Z][a-z]+) ([A-Z][a-z]+)$");
    smatch porownaj;

    if(!plik.good())
    {
        cout<<"Nie ma takiego pliku lub nie udalo sie go utworzyc"<<endl;
        plik.close();
    }
    else
    {
        poprawnedane=true;
        for(int numerLinii = 1; getline(plik, linia); numerLinii++)
            {
                if(!regex_search(linia,porownaj,kod))
                {
                    cout<<"Niepoprawna linia "<<numerLinii<<":"<<endl<<linia<<endl;
                    poprawnedane= false; 
                }
            }
        plik.close();
    }  
    return poprawnedane;
}

void Instrukcja()
{
    cout
    <<"PLAN"<<endl
    <<"Program uruchamiany z linii polecen"<<endl
    <<"-h sluzy do wywolania instrukcji"<<endl
    <<"-g /nazwapliku/ (bez .txt) /ilosc/ sluzy do wygenerowania pliku z prowadzacymi"<<endl
    <<"-i /nazwapliku/ (bez .txt)         sluzy do uruchomienia programu"<<endl
    <<"Program zapisuje posortowane zajecia w pliku dla kazdego prowadzacego"<<endl;
}

//1 = ok; 2= -h; 3= zle argumenty; 4= za duzo arg; 5=generuj plik
int OdczytajArgumenty(int argc, char* argv[], string& nazwapliku, int& ile)
{
    int policz=0;
    //maximum 3 argumenty
    if(argc <= 4)
    {
        for (int i=0; i<argc; i++)
        {
            //jesli pierwszy argument to -h wywolaj instrukcje
            if(string(argv[i]) == string("-h"))
            {
                return 2;
            }
            //jesli pierwszy argument to -i wykonaj operacje na pliku
            if(string(argv[i]) == string("-i"))
            {
                //jesli drugi argument istnieje i trzeci argument jest pusty
                if(argv[i+1] and argv[i+2] == nullptr)
                {
                    //nazwa pliku to drugi argument 
                    nazwapliku = string(argv[i+1]);
                    policz=1;
                }
                else 
                    //jesli nie to podano zle argumenty
                    return 3;
               
            }
            //jesli pierwszy argument to -g wygeneruj plik z prowadzacymi
            if(string(argv[i]) == string("-g"))
            {
                //jesli istnieja oba argumenty
                if(argv[i+1] and argv[i+2])
                {
                    //ilosc wierszy do wygenerowania to ostatni argument
                    ile = strtol(argv[i+2], NULL, 10);
                    //jesli ilosc jest ujemna podano zle argumenty
                    if(ile<0)
                        return 3;
                    //nazwa pliku to drugi argument, wygeneruj plik
                    else
                    {
                        nazwapliku = string(argv[i+1]);
                        return 5;
                    }
                }
                else return 3;
            }
        }
        if (policz == 1)
            return policz;
        else 
            return 3;
    }
    //podano za duzo argumentow
    else
        return 4;
}  
