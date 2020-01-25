#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
#include <vector>
#include <regex>
#include <chrono>

using namespace std;

#include "struktury.h"
#include "funkcje.h"

/* Funkcja porówująca dzień następnie godzinę początkową i końcową */
bool mniejsza(const Zajecia & pLewy, const Zajecia & pPrawy)
{
    if(pLewy.DzienZajec < pPrawy.DzienZajec)
        return true;
    else if(pLewy.DzienZajec > pPrawy.DzienZajec)
        return false;
    else // dni takie same, porownujemy godziny
    {
        if(pLewy.PoczatekZajec.Godzina < pPrawy.PoczatekZajec.Godzina)
            return true;
        else if(pLewy.PoczatekZajec.Godzina > pPrawy.PoczatekZajec.Godzina)
            return false;
        else // godziny poczatkowe takie same, porownujemy minuty
        {
            if(pLewy.PoczatekZajec.Minuta < pPrawy.PoczatekZajec.Minuta)
                return true;
            else if(pLewy.PoczatekZajec.Minuta > pPrawy.PoczatekZajec.Minuta)
                return false;
            else // minuty takie same, porownujemy godziny konca zajec
            {
                if(pLewy.KoniecZajec.Godzina < pPrawy.KoniecZajec.Godzina)
                  return true;
                else if(pLewy.KoniecZajec.Godzina > pPrawy.KoniecZajec.Godzina)
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

/* Funkcja konwertująca enum na string */
string enumNaString(Dzien DzienZajec){
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

/* Funkcja konwertująca string na enum */
Dzien stringNaEnum(string& dzien){
    if(dzien == "pn") return pn;
    else if (dzien == "wt") return wt;
    else if (dzien == "sr") return sr;
    else if (dzien == "cz") return cz;
    else if (dzien == "pt") return pt;
    else if (dzien == "sb") return sb;
    else return nd;
}

/* Funkcja zwracajaca wskaznik na szukanego prowadzacego */
Prowadzacy* znajdzProwadzacegoRekurencyjnie (Prowadzacy* pGlowaListyProwadzacych, string nazwisko){
    //jeśli istnieje
    if (pGlowaListyProwadzacych)
    {
        //jeśli znaleźliśmy prowadzącego zwrócić wskaźnik
        if (pGlowaListyProwadzacych->NazwiskoProwadzacego == nazwisko)
            return pGlowaListyProwadzacych;
        //jeśli nie znaleźlismy szukaj dalej
        else
            return znajdzProwadzacegoRekurencyjnie(pGlowaListyProwadzacych->pNastepnyProwadzacy, nazwisko);
    }
    //nie ma takiego prowadzacego i zwraca nullptr
    else
        return nullptr;
}

/* Funkcja dodajaca prowadzacego na koniec listy jednokierunkowej */
Prowadzacy* dodajProwadzacegoNaKoniecListy (Prowadzacy*& pGlowaListyProwadzacych, string nazwisko)
{
    //jeśli nie ma listy to ją utwórz
    if(not pGlowaListyProwadzacych)
        return pGlowaListyProwadzacych = new Prowadzacy {nazwisko, nullptr, nullptr };
    //dodaj rekurencyjnie na koniec listy
    else
        return dodajProwadzacegoNaKoniecListy(pGlowaListyProwadzacych->pNastepnyProwadzacy, nazwisko);
}

/* Funkcja dodająca zajęcia do drzewa binarnego */
void DodajZajeciaProwadzacemu (Zajecia*& pKorzen, Czas& PoczatekZajec, Czas& KoniecZajec, Dzien& DzienZajec, string& grupa, string& przedmiot)
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
          if (mniejsza (*pNowy, *p))  
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

/* Funkcja wypisujaca posortowane zajecia prowadzacego*/
//inorder traversal
void wypiszZajeciaProwadzacego(Zajecia* pKorzen, ofstream& strumien){
    //jesli istnieje
    if (pKorzen)
    {
	   wypiszZajeciaProwadzacego(pKorzen->pLewy, strumien);
       strumien<<setw(2)<<setfill('0')<<pKorzen->PoczatekZajec.Godzina<<
            ":"<<setw(2)<<setfill('0')<<pKorzen->PoczatekZajec.Minuta<<
            "-"<<setw(2)<<setfill('0')<<pKorzen->KoniecZajec.Godzina<<
            ":"<<setw(2)<<setfill('0')<<pKorzen->KoniecZajec.Minuta<<
            " "<<enumNaString(pKorzen->DzienZajec)<<
            " "<<pKorzen->Grupa<<
            " "<<pKorzen->Przedmiot<<endl;
        wypiszZajeciaProwadzacego(pKorzen->pPrawy, strumien);
    }
}
/* Funkcja wypisująca zajęcia każdego prowadzącego */
void wypiszWszystkieZajecia(Prowadzacy*& pGlowaListyProwadzacych){
    //jeśli istnieje
    if(pGlowaListyProwadzacych)
    {
	string wyjscie = "../pliki/" + pGlowaListyProwadzacych->NazwiskoProwadzacego + ".txt";
	ofstream plik(wyjscie);
        wypiszZajeciaProwadzacego(pGlowaListyProwadzacych->pKorzenListyZajec, plik);
        auto p = pGlowaListyProwadzacych->pNastepnyProwadzacy;
        wypiszWszystkieZajecia(p);
    }
}	

/* funkcja usuwajaca drzewo zajec */
void usunDrzewo(Zajecia*& pKorzen){
    //jesli korzen istnieje
    if (pKorzen)
        {
            //usun drzewo rekurencyjnie
            usunDrzewo(pKorzen->pLewy);
            usunDrzewo(pKorzen->pPrawy);
            //usun korzen i wskaznik na korzen
            delete pKorzen;
            pKorzen = nullptr;
        }
}

//usun drzewo-> wskaznik na nastepnego prowadzacego-> usun poprzedniego i wskaznik
//potem rekurencja
/* funkcja usuwajaca liste i wszystkie drzewa */
void usunWszystko(Prowadzacy*& pGlowaListyProwadzacych){
    //jesli prowadzacy istnieje
    if (pGlowaListyProwadzacych)
    {
        usunDrzewo(pGlowaListyProwadzacych->pKorzenListyZajec);
        //przechodzimy do nastepnego prowadzacego;     
        auto p = pGlowaListyProwadzacych->pNastepnyProwadzacy;
        delete pGlowaListyProwadzacych;
        pGlowaListyProwadzacych = nullptr;
        //krok rekurencyjny przechodzacy do nastepnego prowadzacego
        usunWszystko(p);
    }
}
/* Funkcja tworząca element listy o takim samym nazwisku a następnie przypisuje mu zajęcia */
void wczytajZajeciaProwadzacemu(Prowadzacy*& pGlowaListyProwadzacych, string nazwisko, Czas PoczatekZajec, Czas KoniecZajec, Dzien DzienZajec, string grupa, string przedmiot){
    Prowadzacy* p = znajdzProwadzacegoRekurencyjnie(pGlowaListyProwadzacych, nazwisko);
        if (not p)
        p = dodajProwadzacegoNaKoniecListy(pGlowaListyProwadzacych, nazwisko);
    DodajZajeciaProwadzacemu(p->pKorzenListyZajec, PoczatekZajec, KoniecZajec, DzienZajec, grupa, przedmiot);
}

/* Funkcja odczytująca elementy z pliku a następnie wczytująca je do dynamicznej struktury */
bool odczytajZPliku(Prowadzacy*& pGlowaListyProwadzacych, string& nazwaPlikuWejsciowego){
    ifstream plik;
    string linia = "";
	plik.open("../pliki/" + nazwaPlikuWejsciowego);
	
		if (!plik.good()) //sprawdzenie czy plik moze byc otwarty 
		{
			plik.close();
            return false;
		}
		else
		{
    		Czas PoczatekZajec {0,0};
            Czas KoniecZajec {0,0};
            string DzienZajec = "";
            string grupa = "";
            string nazwisko = "";
            string przedmiot = "";
    		char znak = 0;
    			
    		while (plik >> PoczatekZajec.Godzina >> znak >> PoczatekZajec.Minuta >> znak >> KoniecZajec.Godzina >> znak >> KoniecZajec.Minuta >> DzienZajec >> grupa >> nazwisko >> przedmiot)
    			wczytajZajeciaProwadzacemu(pGlowaListyProwadzacych, nazwisko, PoczatekZajec, KoniecZajec, stringNaEnum(DzienZajec), grupa, przedmiot);
    			
		}
		plik.close(); 
       		return true;
}

/* Generuj losowe liczby z danego przedzialu */
int Silnik(size_t min, size_t max){
    std::default_random_engine silnik;
    silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<size_t> rozklad (min,max);
    return rozklad(silnik);
}

/* Generuj plik do posortowania */
void generujPlik(int ile, string& nazwaPlikuWyjsciowego){
    string wyjscie = "../pliki/" + nazwaPlikuWyjsciowego + ".txt";
    ofstream plik(wyjscie);
    vector<string> Nazwiska = {"Nowak", "Kowalski", "Lewandowski", "Karolak"};
    //vector<string> Nazwiska = {"Nowak", "Kowalski", "Lewandowski", "Zielinski", "Wojcik", "Kowalczyk", "Kaminska", "Lewandowska", "Dabrowska", "Zielinska"};
    vector<string> Przedmioty = {"Programowanie", "Java", "Fizyka", "Matematyka", "Historia", "Przyroda", "Geografia", "AMiAL", "TUC"};
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

/* Sprawdz czy plik jest poprawny, jesli nie to wypisz zle linie */
// if nr.linii > x 
//    break?

bool sprawdzPlik(string& nazwaPlikuWejsciowego){
    string wejscie = "../pliki/" + nazwaPlikuWejsciowego;
    ifstream plik(wejscie);
    string linia;
    bool poprawnedane=false;
    regex kod("^(\\s*|[ \\t]*([01]\\d|2[0-3]):([0-5]\\d)-([01]\\d|2[0-3]):([0-5]\\d)[ \\t]+(pn|wt|sr|cz|pt|sb|nd)[ \\t]+(gr[1-9])[ \\t]+([A-Z][a-z]*)[ \\t]+([A-Z]([a-z]|[A-Z])*)\\s*)$");
    smatch porownaj;

    if(!plik.good())
        plik.close();
    else
    {
        poprawnedane=true;
        for(int numerLinii = 1; getline(plik, linia); numerLinii++)
            {
                if(!regex_match(linia,porownaj,kod))
                {
                    cout<<"Niepoprawna linia "<<numerLinii<<":"<<endl<<linia<<endl;
                    poprawnedane= false; 
                }
            }
        plik.close();
    }  
    return poprawnedane;
}

/* Wywołanie instrukcji */
void instrukcja()
{
    cout
    <<"PLAN"<<endl
    <<"Program uruchamiany z linii polecen"<<endl
    <<"-h sluzy do wywolania instrukcji"<<endl
    <<"-g /nazwapliku/ /ilosc/       sluzy do wygenerowania pliku z prowadzacymi"<<endl
    <<"-i /nazwapliku/.rozszerzenie  sluzy do uruchomienia programu"<<endl
    <<"Program zapisuje posortowane zajecia w pliku dla kazdego prowadzacego"<<endl;
}

//1 = ok; 2= -h; 3= zle argumenty; 4= za duzo arg; 5=generuj plik
/* Pobierz argumenty z konsolki */
int pobierzArgumenty(int argc, char* argv[], string& nazwaPlikuWejsciowego, int& ile)
{
    int ok = 0;
    if (argc <= 4)
    {
        for (int i = 1; i < argc; i++)
        {
            if (string(argv[i]) == string("-h"))
            {
                return 2;
            }
            if (string(argv[i]) == string("-i"))
            {
                nazwaPlikuWejsciowego = string(argv[i + 1]);
                ok=1;
            }
            if (string(argv[i]) == string("-g"))
            {
                nazwaPlikuWejsciowego = string(argv[i + 1]);
                ile = strtol(argv[i+2], NULL, 10);
                ok=5;
            }
        }
        if(ok == 1 or ok == 5)  
        	return ok;
        else 
            return 3;
    }
    else
        return 4;
} 
