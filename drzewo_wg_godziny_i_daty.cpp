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
Zajecia* DodajZajeciaProwadzacemu (Zajecia* pKorzen, Godzina PoczatekZajec, Godzina KoniecZajec, Dzien DzienZajec, string grupa, string przedmiot){
  if (not pKorzen)
  {
    Zajecia * temp = new Zajecia;
    temp->PoczatekZajec.Godzinka = PoczatekZajec.Godzinka;
    temp->PoczatekZajec.Minuta = PoczatekZajec.Minuta;
    temp->DzienZajec = DzienZajec;
    temp->KoniecZajec.Godzinka = KoniecZajec.Godzinka;
    temp->KoniecZajec.Minuta = KoniecZajec.Minuta;
    temp->Grupa = grupa;
    temp->Przedmiot = przedmiot;
    //temp->dla wszystkich?
    temp->pLewy = temp->pPrawy = nullptr;
    return temp;
  }
  auto Prawo = pKorzen->pPrawy;
  auto Lewo = pKorzen->pLewy;
  //posortowac wg. minut
  if(DzienZajec > (pKorzen->DzienZajec))
    {
        if(PoczatekZajec.Godzinka and PoczatekZajec.Minuta > (pKorzen->PoczatekZajec.Godzinka and pKorzen->PoczatekZajec.Minuta))
        {
            Prawo->pPrawy = DodajZajeciaProwadzacemu(Prawo->pPrawy, PoczatekZajec, KoniecZajec, DzienZajec, grupa, przedmiot);
        }
        else
            Prawo->pLewy = DodajZajeciaProwadzacemu(Prawo->pLewy, PoczatekZajec, KoniecZajec, DzienZajec, grupa, przedmiot);
    }
  else if (DzienZajec <= (pKorzen->DzienZajec))
    {
      if(PoczatekZajec.Godzinka and PoczatekZajec.Minuta <= (pKorzen->PoczatekZajec.Godzinka and pKorzen->PoczatekZajec.Minuta))
      {
          Lewo->pLewy = DodajZajeciaProwadzacemu(Lewo->pLewy, PoczatekZajec, KoniecZajec, DzienZajec, grupa, przedmiot);
      }
      else
          Lewo->pPrawy = DodajZajeciaProwadzacemu(Lewo->pPrawy, PoczatekZajec, KoniecZajec, DzienZajec, grupa, przedmiot);
    }
  return pKorzen;
}

void DodajProwadzacegoNaPoczatek (Prowadzacy *& pGlowaListyProwadzacych, Zajecia *& pGlowaListyZajec, string nazwisko){
  //jeśli nie istnieje to dodaj do listy
 if (not pGlowaListyProwadzacych)
     pGlowaListyProwadzacych = new Prowadzacy {nazwisko, nullptr, pGlowaListyZajec};
 //dodaj na poczatek listy tak aby byl tylko jeden o takim samym nazwisku prowadzacy przedmioty
else if (ZnajdzProwadzacegoRekurencyjnie(pGlowaListyProwadzacych, nazwisko) == nullptr)
        pGlowaListyProwadzacych = new Prowadzacy {nazwisko, pGlowaListyProwadzacych, pGlowaListyZajec};
}

/** wypisz posortowane drzewo zajec wg. dnia i godziny dla każdego prowadzącego*/
//inorder traversal
//poprawic wypisywanie
void WypiszZajeciaProwadzacego(Zajecia* pKorzen){
    if (not pKorzen)
    {
        return;
    }
    WypiszZajeciaProwadzacego(pKorzen->pLewy);
      cout<<pKorzen;
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
