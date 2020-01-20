/** @file */

#include <string>


using namespace std;

#ifndef FUNKCJE_H
#define FUNKCJE_H

/** Funkcja porównuje datę(dzień, godzinę początkową a następnie godzinę końcową) w drzewie.
@param pLewy lewy potomek drzewa
@param pPrawy prawy potomek drzewa
@return funkcja zwraca true jeżeli porównywana data jest mniejsza
*/
bool mniejsza(const Zajecia& pLewy, const Zajecia& pPrawy);

/** Funkcja konwertuje typ wyliczeniowy na string. Służy do wypisania planów do pliku.
@param DzienZajec dzień zajęć 
@return funkcja zwraca string
*/
string stringNaEnum(Dzien DzienZajec);

/** Funkcja konwertuje string na typ wyliczeniowy. Służy do wczytania danych z pliku.
@param DzienZajec dzień zajęć 
@return funkcja zwraca typ wyliczeniowy
*/
Dzien enumNaString(const string& dzien);

/** Funkcja znajduje rekurencyjnie poszukiwany element w liście.
@param pGlowaListyProwadzacych pierwszy element listy
@param nazwisko element w liście którego poszukujemy
@return wskaźnik na znaleziony element
*/
Prowadzacy* znajdzProwadzacegoRekurencyjnie (Prowadzacy* pGlowaListyProwadzacych, string nazwisko);

/** Funkcja dodaje rekurencyjnie element na koniec listy. Funkcja alokuje pamięć.
@param pGlowaListyProwadzących pierwszy element listy
@param nazwisko element który chcemy dodać do listy
@return wskaźnik na ostatni element listy
*/
Prowadzacy* dodajProwadzacegoNaKoniecListy (Prowadzacy*& pGlowaListyProwadzacych, string nazwisko);

/** Funkcja dodaje iteracyjnie element do drzewa. Funkcja alokuje pamięć.
@param pKorzen korzen drzewa do którego dodawane są elementy
@param PoczatekZajec godzina początkowa która ma być wstawiona
@param KoniecZajec godzina końcowa która ma być wstawiona
@param grupa grupa która ma być wstawiona
@param przedmiot przedmiot który ma być wstawiony
*/
void dodajZajeciaProwadzacemu (Zajecia*& pKorzen, Godzina& PoczatekZajec, Godzina& KoniecZajec, Dzien& DzienZajec, string& grupa, string& przedmiot);

/** Funkcja wypisuje rekurencyjnie drzewo do danego strumienia.
@param pKorzen korzeń drzewa z którego elementy mają być wypisane
@param strumien strumień do którego elementy mają być wypisane
*/
void wypiszZajeciaProwadzacego(Zajecia* pKorzen, ofstream& strumien);

/** Funkcja wypisuje rekurencyjnie posortowane drzewo dla każdego elementu listu jednokierunkowej.
@param pGlowaListyProwadzacych element listy od którego ma się zacząć wypisywanie
*/
void wypiszWszystkieZajecia(Prowadzacy*& pGlowaListyProwadzacych);

/** Funkcja usuwa rekurencyjnie całe drzewo z pamięci.
@param pKorzen korzeń drzewa do usunięcia
*/
void usunDrzewo(Zajecia*& pKorzen);

/** Funkcja usuwa rekurencyjnie każde drzewo i całą listę.
@param pGlowaListyProwadzacych element listy od którego ma się zacząć usuwanie
*/
void usunWszystko(Prowadzacy*& pGlowaListyProwadzacych);

/** Funkcja tworzy unikalny element listy i do przypisanego mu drzewa dodaje zajęcia. Funkcja alokuje pamięć.
@param pGlowaListyProwadzacych pierwszy element listy
@param nazwisko nazwisko które ma być wstawione (do listy)
@param PoczatekZajec godzina początkowa która ma być wstawiona (do drzewa)
@param KoniecZajec godzina końcowa która ma być wstawiona
@param grupa grupa która ma być wstawiona
@param przedmiot przedmiot który ma być wstawiony
*/
void wczytajZajeciaProwadzacemu(Prowadzacy*& pGlowaListyProwadzacych, string nazwisko, Godzina PoczatekZajec, Godzina KoniecZajec, Dzien DzienZajec, string grupa, string przedmiot);

/** Funkcja wczytuje zajęcia z pliku do struktury
@param pGlowaListyProwadzacych element do którego dodawane są elementy
@param[in] nazwapliku odczytana przez funkcję nazwa pliku wejściowego
@return funkcja zwraca true jeśli uda się poprawnie wczytać cały plik 
*/
bool odczytajZPliku(Prowadzacy*& pGlowaListyProwadzacych, string& nazwaPlikuWejsciowego);

/** Funkcja sprawdza poprawność danych w pliku przy użyciu wyrażen regularnych.
@param[in] nazwaPlikuWejsciowego odczytana przez funkcję nazwa pliku wejściowego
@return funkcja zwraca true jeśli cały plik jest poprawny
*/
bool sprawdzPlik(string& nazwaPlikuWejsciowego);

/** Funkcja generuje liczbę z zadanego przedziału w oparciu o random_int_distribution. 
@param min minimalna liczba
@param max maksymalna liczba
@return funkcja zwraca losowa liczbę z przedziału
*/
int Silnik(size_t min, size_t max);

/** Funkcja generuje przykładowy plik do posortowowania.
@param ile ilość wierszy w docelowym pliku tekstowym
@param[out] nazwapliku odczytana przez funkcję nazwa pliku wyjściowego
*/
void generujPlik(int ile, string& nazwaPlikuWyjsciowego);

/** Funkcja wypisująca instrukcję programu
*/
void instrukcja();

/** Funkcja pobiera parametry programu i sprawdza ich poprawność.
@param argc liczba parametrów uruchomienia programu
@param argv tablica wskaźników na parametry uruchomienia programu
@param[out] nazwaPlikuWejsciowego odczytana przez funkcję nazwa pliku wyjściowego
@return funkcja zwraca liczbę kodu wyjścia
*/
int pobierzArgumenty(int argc, char* argv[], string& nazwaPlikuWejsciowego, int& ile);

#endif