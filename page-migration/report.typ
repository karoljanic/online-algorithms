#set page(width: 210mm, height: 297mm, margin: 25mm)
#show math.equation: set text(12pt)

= Problem Page Migration
Karol Janic
\ \ \

== Badane metody Page Migration
Zaimplementowano następujące metody Page Migration:
- Move to Min
- Coin Flip

== Przebieg eksperymentu
Eksperyment polegał na przeprowadzeniu symulacji migracji stron w dwóch grafach:
- torusie 3D o wymiarach $4 times 4 times 4$ z krawędziami wagi $1$
- hiperkostce o wymiarach $2 times 2 times 2 times 2 times 2 times 2$ z krawędziami wagi $1$
badając różne parametry wyżej wymienionych algorytmów. Dla każdej metody i grafu przeprowadzono $100$ powtórzeń po $65536$ zapytań. W każdym zapytaniu losowano wierzchołek docelowy z następującymi rozkładami:
- rozkład jednostajny ($PP[X=i] = 1/64$)
#v(0.05em)
- rozkład harmoniczny ($PP[X=i] = 1/(i H^((1))_64)$)
#v(0.05em)
- rozkład dwuharmoniczny ($PP[X=i] = 1/(i^2 H^((2))_64)$)

Wynikiem eksperymentu był średni koszt migracji strony w jednym zapytaniu.

== Wnioski
- Zmiana parametru $d$ w algorytmie Coin Flip nie wpływa na wynik eksperymentu. W przypadku algorytmu Move to Min wzrost parametru $d$ powoduje zmniejszenie średniego kosztu migracji strony dla wyboru wierzchołka docelowego z rozkładu harmonicznego lub dwuharmonicznego.

- Strategia Coin Flip osiąga znacząco lepsze wyniki niż Move to Min w przypadku wyboru wierzchołka docelowego z rozkładu jednostajnego. W przypadku wyboru wierzchołka docelowego z rozkładu harmonicznego lub dwuharmonicznego Move to Min osiąga znacząco lepsze wyniki.

- Pomimo równej średniej($3$) i maksymalnej($6$) odległości między wierzchołkami w hiperkostce i torusie 3D średnie koszty migracji strony w hiperkostce są mniejsze niż w torusie 3D. Jest to spowodowane większą liczbą krawędzi między bliskimi wierzchołkami w hiperkostce, co pozwala na szybsze znalezienie wierzchołka docelowego w przypadku niejednostajnych rozkładów.

- Najlepsze wyniki osiągnięto dla rozkładu dwuharmonicznego, co jest zgodne z intuicją, że w przypadku migracji stron lepiej jest wybierać wierzchołki docelowe bliskie siebie. Najgorsze wyniki osiągnięto dla rozkładu jednostajnego, co jest spowodowane tym, że w przypadku tego rozkładu wierzchołki docelowe są odległe od siebie, co powoduje większy koszt migracji strony.

== Wyniki eksperymentu
#for chart in (
    "plots/cost_per_strategy_coin-flip.png",
    "plots/cost_per_strategy_move-to-min.png", 
    "plots/cost_per_distribution_uniform.png",
    "plots/cost_per_distribution_harmonic.png",
    "plots/cost_per_distribution_biharmonic.png"
    ) {
    figure(
    image(chart, width: 95%),
    )
}