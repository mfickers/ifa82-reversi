#game.h

**struct board**
// Spielbrett
**timer** // Zeitvariable
// Zählt die Spielzeit mit
**turn_counter** // int
// Zählt die Spielzüge mit
**turn**
// Wer ist grade dran
**last_turn_pass**
// Wurde letzten Zug gepasst

**function init()**
// Spiel in den Anfangszustand setzen.
**function set_marker(coord, player)** // coord bspw [3][4]
// Wird von io aufgerufen, setzt Abarbeitung des Zuges in Gang
// Setzt last_turn_pass auf false
**function validate_turn(coord, player)**
// Prüft den Zug auf Güligkeit
// 1. War der Spieler am Zug
// 2. Ist das Feld auf dem Spielbrett
// 3. Ist das Feld frei
// 4. Ist das Feld verfügbar nach den Regeln
**function process_turn(coord, player)**
// Arbeitet Zug ab, dreht alle Spielsteine um
// Ruft after_turn auf
**function after_turn()**
// Spieler an der Reihe wechselt
// Anzahl Spielzüge erhöhen
// Prüfen ob das Spielbrett voll ist (<64 Steine), sonst game_over
// Prüfen ob Spieler an der Reihe einen gültigen Zug machen Kann
// -> process_turn
// -> process_pass
**function pass(player)**
// Spieler passt. Setzt last_turn_pass auf true
// Wenn last_turn_pass schon true ist, ist das Spiel vorbei
// ruft after_turn auf
**function can_put_marker(player)**
// Kann ein Spieler einen güligen Zug machen

#board.h

**struct field [8][8]**

**function init()**
// Setzt das Brett in den Anfangszustand
**function count_points(player)**
// Wieviele Punkte hat ein Spieler
**function count_markers()**
// Wieviele Steine sind auf dem Brett
**function is_field_valid(player)**
// Kann der Spieler hier einen Stein setzen?
**function is_field_empty()**
// Ist auf diesem Feld schon ein Stein
**function set_marker(coord)**
// Setzt einen Stein einer Farbe, überschreibt zur Not alten Wert

#io.h

**function render_board(board)** // Koordinaten an den Reihen und Spalten
// Zeigt das Spielbrett auf der Kommandozeile an
**function render_time(timer)**
// Zeigt den Timer auf der Kommandozeile an
**function render_turn(player)** // "Spieler 1 ist an der Reihe"
// Zeigt auf der Kommandozeile an wer an der Reihe ist.
**function render_pass(player)** // "Spieler 1 muss passen."
// Wenn kein gültiger Zug machbar ist.
**function render_score()**
// Zeigt den Spielstand auf der Kommandozeile an
**function prompt_turn()**  // Zug oder passen, dumm weiterreichen
// Fragt nach einem Input vom Spieler an der Reihe
**function invalid_move()**
// Zeigt eine Fehlermeldung aufgrund eines ungültigen Zuges
**function game_over()**
// Gibt den Endstand aus und beendet das Programm
