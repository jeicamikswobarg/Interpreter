# Interpreter
Treść zadania

Język skryptowy do Mario
Język skryptowy do Mario. Po wielu trudach Twoja implemenatcja gry Mario jest skończona. Jednak nie jesteś do końca zadowolony - w grze brakuje możliwości zawansowanego ustawiania parametrów. Okazuje się, że rozwiązanie tego problemu kryje się w językach skryptowych.
Jako ambitny student wydziału ETI postanowiłeś napisać swój własny język skryptowy.
Język ten będzie zawierał zmienne odpowiadające w języku C zmiennym typu int. Wszystkie zmienne są globalne i nie trzeba ich deklarować. Każda zmienna może mieć wartość będącą liczbą całkowitą (odpowiadającą typowi int) lub wartość specjalną Nul. Watrość Nul jest domyślną wartością zmiennej. Zmienne są reprezentowane jako ciąg liter alfabetu łacińskiego, wielkość liter ma znaczenie.
Operatory arytmetyczne dwuargumentowe = == < > <= >= + - / * % i operator arytmetyczny jednoargumentowy - działają jak w języku C. Jeśli któryś z argumentów ma wartość Nul, to wynikiem operacji jest także Nul. W języku występują także operatory logiczne koniunkcji &, alternatywy | i negacji !. Wartości logicznej fałsz odpowiada wartość Nul, a wartości logicznej prawda jakakolwiek inna wartość. Operatory logiczne jako prawdę zwracają wartość 0.
Wszystkie operatory dwuargumentowe oprócz = są lewostronnie domknięte. Kolejność priorytetów operatorów, od najmniejszego priorytetu, to: 
= | & (!= ==) (< > <= >=) (+ -) (/ * %) (! -u)
operatory o tym samym priorytecie zostały zgrupowane nawiasem; -u to operator jednoargumentowy.
Instrukcja warunkowa będzie realizowana przez operator ?. Instukcja pętli będzie realizowana jako while przy użyciu operatora @.
?(warunek) {kod}
@(warunek) {kod}
W opisanych instrukcjach muszą występować nawiasy okrągłe i klamrowe.
Jednocześnie chcemy stworzyć ograniczenie na liczbę wykonywanych instrukcji. Realizacją tego zadania będzie licznik wykonanych operacji. Każde wykonanie operatora i każde sprawdzenie warunku w instrukcji warunkowej i w pętli powoduje inkrementację tego licznika.

przykładowe wejscie:

10

a b c d 
3
a = 3
b = 2
c = 1


wyjscie:

3
a 3
b 2
c 1
d Nul

Objaśnienie wejscia:

10 - limit ilosci operacji
a b c d - zmienne
3 - ilosc lini pod spodem

Objasnienie wyjscia:

3 - liczba wykonanych operacji
wypisanie - zmienna, wartosc 
