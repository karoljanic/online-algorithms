#set page(width: 210mm, height: 297mm, margin: 25mm)
#show math.equation: set text(12pt)

= Problem Page Allocation
Karol Janic
\ \ \

== Badane metody Page Allocation
Zaimplementowano algorytm Count.

== Przebieg eksperymentu
Eksperyment polegał na przeprowadzeniu symulacji alokacji stron w grafie pełnym o $64$ wierzchołkach i wagach $1$
badając różne wartości parametru tego algorytmu. Dla każdej wartości parametru przeprowadzono $1000$ powtórzeń po $65536$ zapytań.
Badano wpływ stosunku liczby zapytań typu $italic("write")$ oraz $italic("read")$ na całkowity koszt symulacji zadając różne prawdopodobieństwa tych zapytań (rozkład jednostajny) oraz wpływ parametru $D$ także zadając różne jego wartości.

Wynikiem eksperymentu był średni koszt alokacji strony w jednym zapytaniu oraz maksymalna liczba kopii strony w grafiem
w trakcie symulacji.

== Wnioski
- Początkowo, wraz ze wzrostem liczby zapytań typu $italic("write")$ do około $20%$ rośnie średni koszt alokacji strony a następnie on maleje, ponieważ początkowo większą część kosztu stanowi kosz zapytania a następnie koszt synchronizacji kopii strony w grafie.
- Wraz ze wzrostem liczby zapytań typu $italic("write")$ szybko spada liczba zasobu w grafie, ponieważ większa liczba zapytań typu $italic("write")$ powoduje częstsze synchronizacje kopii strony w grafie.

- Wzrost parametru $italic("d")$ nie wpływa znacząco na średni koszt alokacji strony. Dla jego dużych wartości średnie koszt lekko rośnie. Jednakże, wraz ze wzrostem parametru $italic("d")$ rośnie maksymalna liczba kopii strony w grafie co jest spójne z intuicją, ponieważ większa wartość parametru $italic("d")$ oznacza większą liczbę kopii strony w grafie.

== Wyniki eksperymentu
#for chart in (
    "plots/average_cost_d.png",
    "plots/average_cost_p.png",
    "plots/average_max_copies_p.png",
    "plots/average_max_copies_d.png",
    ) {
    figure(
    image(chart, width: 90%),
    )
}