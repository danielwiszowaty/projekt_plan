Opis repozytorium:
/projekt_plan/ pliki .cpp/.h/makefile
/pliki_txt/ pliki .txt wygenerowane przez program główny
/make_i_nvwa/ folder służący do sprawdzania wycieków


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

Regex: ^([01]\d|2[0-3]):([0-5]\d)-([01]\d|2[0-3]):([0-5]\d) (pn|wt|sr|cz|pt|sb|nd) (gr[1-9]) ([A-Z][a-z]+) ([A-Z][a-z]+)$

https://regex101.com/r/xNK8RV/15