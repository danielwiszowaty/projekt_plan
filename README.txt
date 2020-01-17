Opis repozytorium:
/projekt_ppk/ pliki .cpp/.h/makefile
/make_i_nvwa/ folder memory i plik makefile do sprawdzania wycieków na linuxie
/dane_do_strumienia/ dane wczytywane z pliku


Opis zadania:
W pliku zawarte są dane zajęć w następującym formacie:
<godzina rozpoczęcia>-<godzina zakończenia> <dzień> <grupa> <prowadzący> <przedmiot>
Godzina jest podana w formacie: hh:mm, dzień przyjmuje wartości: pn, wt, sr, cz, pt, sb, nd. 
Grupa, prowadzący i przedmiot to pojedyncze wyrazy. Przykładowy plik:
  
08:30-10:00 pt gr1 Kowalski Programowanie
10:15-11:45 wt gr2 Nowak Fizyka
14:34-15:43 sr gr2 Kowalski Java
07:23-19:34 cz gr1 Nowak Astronomia

W wyniku działania programu powstają pliki dla każdego prowadzącego (nazwa pliku jest tożsama z
nazwiskiem prowadzącego) zawierający plan zajęć dla prowadzącego.

Kolejne wpisu planu są posortowane chronologicznie. Przykładowy plik Kowalski.txt:

14:34-15:43 sr gr2 Java
08:30-10:00 pt gr1 Programowanie

Program uruchamiany jest z linii poleceń z wykorzystaniem następującego przełącznika:
-i plik wejściowy