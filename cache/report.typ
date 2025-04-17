#set page(width: 210mm, height: 297mm, margin: 25mm)
#show math.equation: set text(12pt)

= Problem pagingu w cache
Karol Janic
\ \ \

== Badane algorytmy
Zaimplementowano następujące metody działania cache'u:
- first in first out
- flush when full
- least recently used
- least frequently used
- random
- random markup

== Opis eksperymentu
Eksperyment polegał na przeprowadzeniu symulacji cachu o pojemności $k$ działającej na $n$ stronach pamięci, gdzie 
$k = \{n/10, ..., n/5 \}$. Wyszukiwane strony były wybierane losowo z kilku rozkładów prawdopodobieństwa:

- rozkład jednostajny ($PP[X=i] = 1/n$)
#v(0.05em)
- rozkład geometryczny ($PP[X=i] = 1/2^n$)
#v(0.05em)
- rozkład harmoniczny ($PP[X=i] = 1/(i H^((1))_n)$)
#v(0.05em)
- rozkład dwuharmoniczny ($PP[X=i] = 1/(i^2 H^((2))_n)$)

Dla każdej metody, rozkładu przeprowadzono i liczby stron przeprowadzono po 100 eksperymentów. W każdym z nich zadano $1000n$ zapytań o strony.
Wynikiem eksperymentu był koszt działania cache'u, czyli liczba ładowań stron do pamięci szybkiej.

== Wyniki eksperymentu
#figure(
  image("plots/distribution.png", width: 120%),
)
#figure(
  image("plots/strategy.png", width: 120%),
)

== Wnioski
- W przypadku rozkładu jednostajnego najgorszy okazał się algorytm flush when full. Reszta algorytmów uzyskiwała podobne wyniki.

- W przypadku reszty rozkładów najlepszy okazał się algorytm last-frequently used. Następne były algorytmy last-recently used, random markup, random, first in first out. Najgorszy okazał się algorytm flush when full. Jest to spowodowane tym, że w skoncentrowanych rozkładach liczba różnych wybieranych stron jest mała.

- Czym rozkład jest bardziej skoncentrowany tym algorytmy działają lepiej. Najlepiej działają dla rozkładu geometrycznego.

