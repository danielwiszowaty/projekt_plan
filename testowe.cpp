#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

enum class Dzien{
    pn=1, wt=2, sr=3, czw=4, pt=5, sb=6, nd=7
};

struct Godzina {
    int Godzinka;
    int Minuta;
};

/** element listy z zajeciami */
struct Zajecia{
    Godzina PoczatekZajec;
    Godzina KoniecZajec;
    Dzien DzienZajec;
    string Grupa;
    string Przedmiot;
    Zajecia* pLewy;
    Zajecia* pPrawy;
}jd;

/** element listy prowadzacych */
struct Prowadzacy{
    string NazwiskoProwadzacego;
    Prowadzacy* pNastepnyProwadzacy;
    Zajecia* pGlowaListyZajec;
};

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

/** wskaźnik na korzeń drzewa binarnego */
Zajecia* DodajZajeciaProwadzacemu (){
    return nullptr;
}

void DodajProwadzacegoNaPoczatek (Prowadzacy *& pGlowaListyProwadzacych, Zajecia *& pGlowaListyZajec, string nazwisko){          
  //jeśli nie istnieje to dodaj do listy
 if (not pGlowaListyProwadzacych)
     pGlowaListyProwadzacych = new Prowadzacy {nazwisko, nullptr, pGlowaListyZajec};
 //dodaj na poczatek listy tak aby byl tylko jeden prowadzacy przedmioty
else if (ZnajdzProwadzacegoRekurencyjnie(pGlowaListyProwadzacych, nazwisko) == nullptr)
        pGlowaListyProwadzacych = new Prowadzacy {nazwisko, pGlowaListyProwadzacych, pGlowaListyZajec};

/*        //jeśli nie istnieje i nie ma zajec element dodaj do listy element bez wskaznikow
        if (not pGlowaListyProwadzacych) //and  DodajZajeciaProwadzacemu( ) == nullptr
            pGlowaListyProwadzacych = new Prowadzacy {nazwisko, nullptr, nullptr};
            //jesli nie istnieje zaden element ale ma zajecia dodaj element ze wskaznikiem na liste zajec
            else if (not pGlowaListyProwadzacych) //and DodajZajeciaProwadzacemu( ) != nullptr
              pGlowaListyProwadzacych = new Prowadzacy {nazwisko, nullptr, pGlowaListyZajec}
              //jesli nie ma takiego prowadzacego a nie ma zajec to dodaj go na poczatek bez wskaznika na liste zajec
                else if (ZnajdzProwadzacegoRekurencyjnie(pGlowaListyProwadzacych, nazwisko) == nullptr) // and DodajZajeciaProwadzacemu( ) == nullptr 
                  pGlowaListyProwadzacych = new Prowadzacy {nazwisko, pGlowaListyProwadzacych, nullptr};
                  //jesli nie ma takiego prowadzacego a ma zajecia dodaj na poczatek ze wskaznikiem na nastepny element i na liste zajec
                  else
                    pGlowaListyProwadzacych = new Prowadzacy {nazwisko, pGlowaListyProwadzacych, pGlowaListyZajec};
*/
}

/** wypisz posortowane drzewo zajec wg. dnia i godziny */
void WypiszZajeciaProwadzacego(){

}

void Wczytaj (){

}

int main()
{
    return 0;
}
