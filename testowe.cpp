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
};

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
//zrobić warunki dla godzin
// lewo = pKorzen->pLewy
// if (PoczatekZajec > lewo->PoczatekZajec)
// lewo->pLewy
// else lewo->pPrawy i to samo dla drugiej strony?
Zajecia* DodajZajeciaProwadzacemu (Zajecia *pKorzen, Godzina PoczatekZajec, Godzina KoniecZajec, Dzien DzienZajec, string Grupa, string przedmiot){
  if (not pKorzen)
  {
    Zajecia * temp = new Zajecia;
    temp->PoczatekZajec = PoczatekZajec;
    temp->DzienZajec = DzienZajec;
    temp->pLewy = temp->pPrawy = nullptr;
    return temp;
  }
  if(DzienZajec > (pKorzen->DzienZajec))
    {
      pKorzen->pPrawy = DodajZajeciaProwadzacemu(pKorzen->pPrawy, PoczatekZajec, KoniecZajec, DzienZajec, Grupa, przedmiot);
    }
  else if (DzienZajec <= (pKorzen->DzienZajec))
    {
      pKorzen->pLewy = DodajZajeciaProwadzacemu(pKorzen->pLewy, PoczatekZajec, KoniecZajec, DzienZajec, Grupa, przedmiot);
    }
  return pKorzen;
}

void DodajProwadzacegoNaPoczatek (Prowadzacy *& pGlowaListyProwadzacych, Zajecia *& pGlowaListyZajec, string nazwisko){
  //jeśli nie istnieje to dodaj do listy
 if (not pGlowaListyProwadzacych)
     pGlowaListyProwadzacych = new Prowadzacy {nazwisko, nullptr, pGlowaListyZajec};
 //dodaj na poczatek listy tak aby byl tylko jeden prowadzacy przedmioty
else if (ZnajdzProwadzacegoRekurencyjnie(pGlowaListyProwadzacych, nazwisko) == nullptr)
        pGlowaListyProwadzacych = new Prowadzacy {nazwisko, pGlowaListyProwadzacych, pGlowaListyZajec};
}

/** wypisz posortowane drzewo zajec wg. dnia i godziny */
//poprawic wypisywanie
void WypiszZajeciaProwadzacego(Zajecia * pKorzen){
    if (not pKorzen)
    {
        return;
    }
    WypiszZajeciaProwadzacego(pKorzen->pLewy);
      cout<<pKorzen-><<" ";
    WypiszZajeciaProwadzacego(pKorzen->pPrawy);
  
}

void UsunWszystko(){

}

void Wczytaj (){

}

int main()
{
    return 0;
}
