#set page(width: 210mm, height: 297mm, margin: 25mm)
#show math.equation: set text(12pt)

= Problem Bin Packingu
Karol Janic
\ \ \

== Badane metody Bin Packingu
Zaimplementowano następujące metody Bin Packingu:
- Next Fit
- Random Fit
- First Fit
- Best Fit
- Worst Fit

== Opis eksperymentu
Eksperyment polegał na przeprowadzeniu symulacji pakowania przedmiotów o losowych rozmiarach do pojemników o stałej pojemności. Wymiary przedmiotów były wybierane losowo z~rozkładu jednostajnego w przedziale $[0, 1]$. Pojemność pojemników wynosiła $1$. Dla każdej metody przeprowadzono po 10000 eksperymentów. Pakowano $100$ przedmiotów w jaki sposób, że wybierano losowo ich rozmiar i liczbę kopii (między $1$ a $10$) z różnych rozkładów prawdopodobieństwa:
- rozkład jednostajny ($PP[X=i] = 1/10$)
#v(0.05em)
- rozkład geometryczny ($PP[X=i] = 1/2^i$)
#v(0.05em)
- rozkład harmoniczny ($PP[X=i] = 1/(i H^((1))_10)$)
#v(0.05em)
- rozkład dwuharmoniczny ($PP[X=i] = 1/(i^2 H^((2))_10)$)

Wynikiem eksperymentu była liczba użytych pojemników. Porównywano ją z minimalną liczbą pojemników potrzebnych do spakowania przedmiotów o danej sumie rozmiarów przedmiotów. \
Jest to dolna granica liczby niezbędnych pojemników. W ten sposób otrzymywano wsþółczynnik konkurencyjności algorytmu. 

== Wyniki eksperymentu
#for chart in ("plots/competitiveness_per_strategy.png", "plots/competitiveness_per_distribution.png") {
    figure(
    image(chart, width: 85%),
    )
}

== Wnioski
- Najlepsze wyniki uzyskano dla metod Best Fit, First Fit oraz Random Fit. Najgorsze wyniki uzyskano dla metod Next Fit co było przewidywalne, ponieważ algorytm ten nie wykorzystuje w~pełni pojemności wszystkich pojemników.

- W przypadku czterech najlepszych metod wpływ rozkładu liczby kopii przedmiotów na wyniki był mały. Najlepsze wyniki uzyskano dla rozkładu geometrycznego i dwuharmonicznego, ponieważ generowały one małą liczbę takich samych przedmiotów. Powtórzenia przedmiotów w~przypadku większych rozmiarów wymagają wielu osobnych pojemników. Rozkład jednostajny i harmoniczny genrował zróżnicowane przedmioty, co powodowało gorsze współczynniki konkurencyjności.

- W przypadku metody Next Fit wpływ rozkładu liczby kopii przedmiotów na wyniki był minimalny. 