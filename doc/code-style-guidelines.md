# Code Style Guidelines

## Allgemein

* Einrückung vier Leerzeichen

## Funktionen

```c
function _render_game(struct Board board)
{
    printf("Hallo");
}
```
* Funktionsbezeichnung im camel_case
* Private Funktionen durch Unterstrich kennzeichnen
* Kein Leerzeichen vor oder nach den Klammern
* Geschweifte Klammern in eigenen Zeilen.

## Verzweigungen

```c
if (is_empty(coord)) {
    do_something();
} else {
    do_something_else();
}
```
* Leerzeichen nach dem if
* Geschweifte Klammer in der Zeile der Verzweigung
* Prüfung auf true oder false findet implizit statt

## Schleifen
```c
for (int i = 0; i < 10; i++) {
    printf("%\n", i);
}
```

* Leerzeichen nach dem for/while
* Geschweifte Klammer in der Zeile der Schleifen
* Leerzeichen nur nach den Semikolons.

## Konstanten

```c
#define BOARD_LENGTH 8

const int MAX_MARKERS = 64;
```

* UPPER_CASE mit Unterstrichen

## Variablen

```c
int turn_counter = 0; // Turn count

/**
 * The Board containing all fields
 */
struct Board {
    int turn_counter = 0;
}
```

* camel_case
* Deklaration immer mit Default-Wert
* Jede Variable in einer eigenen Zeile
* Structs werden großgeschrieben

## Kommentare

```c
/**
 * Processes turn
 */
function turn() {}
```

* Zwei Sternchen in der ersten Zeile, danach maximal eins
* Jede Funktion und Klasse muss einen Kommentar haben
* Englisch
