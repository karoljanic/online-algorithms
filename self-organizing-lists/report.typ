#set page(width: 210mm, height: 297mm, margin: 25mm)
#show math.equation: set text(12pt)

= Metody samoorganizacji list jednokierunkowych
Karol Janic
\ \ \

== Badane metody samoorganizacji
Zaimplementowano następujące metody samoorganizacji list jednokierunkowych:
- brak samoorganizacji
- move to front
- transpose
- frequency count

== Opis eksperymentu
Eksperyment polegał na przeprowadzeniu wyszukiwań elementów w liście o długości 100 elementów. Wyszukiwane elementy były wybierane losowe z kilku rozkładów prawdopodobieństwa:

- rozkład jednostajny ($PP[X=i] = 1/100$)
#v(0.05em)
- rozkład geometryczny ($PP[X=i] = 1/2^i$)
#v(0.05em)
- rozkład harmoniczny ($PP[X=i] = 1/(i H^((1))_100)$)
#v(0.05em)
- rozkład dwuharmoniczny ($PP[X=i] = 1/(i^2 H^((2))_100)$)

Dla każdej metody i rozkładu przeprowadzono po 100 eksperymentów. Wynikiem eksperymentu był koszt wyszukiwania, czyli liczba porównań elementów listy z wyszukiwanym elementem. 

W przypadku braku znalezienia elementu w liście, zostawał on dodany na jej koniec.

== Wyniki eksperymentu
#for chart in ("plots/uniform.png", "plots/geometric.png", "plots/harmonic.png", "plots/biharmonic.png") {
    figure(
    image(chart, width: 90%),
    )
}

== Wnioski
- W przypadku rozkładu jednostajnego metoda nie wpływa na średni koszt wyszukiwania.  \ Oscyluje on wokół wartości oczekiwanej - 50.

- W przypadku pozostałych rozkładów, czym rozkład bardzie skoncentrowany jest wokół wartości początkowych, tym mniejszy jest średni koszt wyszukiwania.

- Metoda frequency count osiąga najlepsze wyniki dla badanych rozkładów pomimo, że nie jesteśmy w stanie znaleźć jej wspłółczynnika konkurencyjności jako stałej.

- Metoda move to front i brak samoorganizacji osiągają najgorsze wyniki dla badanych rozkładów pomimo, że teoretycznie jest to optymalny deterministyczny algorytm on-line.

- Metoda transpose osiąga wyniki pomiedzy metodą move to front i frequency count.
