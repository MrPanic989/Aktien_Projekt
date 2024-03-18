# Aktien_Projekt
Dieses Projekt wurde in einem 2er-Team entwickelt in dem Fach "Algorithmus und Datenstrukturen"
Protokoll

Das Programm für die Verwaltung von Aktienkursen basiert auf einer Hashtabelle mit einer geeigneter Größe für 1000 Aktien. Um Kollisionen vorzubeugen, wurde die Größe des Wertebereiches auf 2003 festgelegt. 

Es gibt insgesamt drei Klassen: 
Die Klasse StockData enthält Daten über einzelne Aktieneinträge, die aus der .csv Datei für die letzten 30 gespeichert werden können. 

Die Klasse Stock enthält Informationen über die Aktien, wie den Namen, die wen und die Kürzel, sowie einen Vektor der Klasse StockData, und somit alle Werte der Aktie. 

Die dritte Klasse ist die Hashtabelle an sich. Sie enthält alle Methoden des Programmes und auch einen Vektor der Klasse Stock und somit alle benötigten Informationen zugleich. 

Damit ein neuer Eintrag hinzugefügt werden kann, wird die kuerzel der Aktie in einen Hashwert unter der Berücksichtigung der quadratischen Sondierung umgewandelt. Der Index den wir auf diese Weise berechnet haben, wird dann genutzt, um den Eintrag in der Hashtabelle zu speichern.

Es stehen folgende Methoden zur Verfügung:

HashFunction(): Generiert einen Hashwert für die Hashtabelle.
insert(): Fügt eine geeignete Aktie an ihrem richtigen Platz in der Hashtabelle hinzu.
search(): Sucht eine Aktie anhand ihren Namens und gibt den Namen, die Kürzel, die WKN und den 	aktuellsten Kurseintrag aus.
import(): Die Methode importiert die Kurswerte einer Aktie aus der CSV-Datei.
remove(): Löscht einen Eintrag aus der Hashtabelle anhand des Namens der Aktie.
plot(): Gibt die Schlusskurse der letzten 30 Tage einer gewünschten Aktie anhand des Namens in der Form einer ASCII-Grafik aus. Sie nimmt sich zur Hilfe die Funktion ASCII() welche zuerst die Differenz des höchsten und des niedrigsten Werts berechnet um nur die relevanten Daten für die Grafik zu bekommen, und liefert dann einen Vektor aus Zeichen, welche wiederum mit der Funktion getChar() gewonnen werden, zurück. 
add(): Fügt eine Aktie mit dem Namen, der Kürzel und der WKN hinzu.
save(): Speichert die Hashtabelle in einer .CSV Datei mit dem ofstream Befehl. 
getStock(): Ruft eine Aktie aus der Hashtabelle anhand des Namens auf.
getStockB(): Ruft eine Aktie aus der Hashtabelle anhand des Indizes auf. 

Aufwandsabschätzung

Für die Aufwandsschätzung müssen wir den Aufwand für das Einfügen, Suchen und Löschen eines Datensatzes in einem normalen Array, einer einfach verketteten Listein und der Hashtabelle.

Das Einfügen, Suchen und Löschen von Datensätzen in einer Hashtabelle, einem normalen Array und einer einfach verketteten Liste haben unterschiedliche Aufwände und Laufzeiten. Im Folgenden werden wir die drei Datenstrukturen vergleichen und ihre Laufzeiten betrachten.

Hashtabelle:

Einfügen: O(1) im besten Fall (wenn es keine Kollisionen gibt), O(n) im schlimmsten Fall (wenn alle Schlüssel denselben Hashwert haben)
Suchen: O(1) im besten Fall, O(n) im schlimmsten Fall (wenn alle Schlüssel denselben Hashwert haben)
Löschen: O(1) im besten Fall, O(n) im schlimmsten Fall (wenn alle Schlüssel denselben Hashwert haben)
Wie wir bereits sehen können, hängt der Aufwand vom Füllgrad ab. Wenn die Hashtabelle stark gefüllt ist, kann es zu vielen Kollisionen kommen, was die Laufzeiten verschlechtert.
Bei 1000 Aktien kann der Aufwand für das Einfügen, Suchen und Löschen eines Datensatzes in der Hashtabelle daher zwischen O(1) und O(n) liegen.


Normales Array:

Einfügen: O(n) (wenn das Array voll ist, muss ein neues Array erstellt und alle Elemente kopiert werden)
Suchen: O(n)
Löschen: O(n) (alle nachfolgenden Elemente müssen verschoben werden, um das gelöschte Element zu entfernen)
Da das Array in einer bestimmten Größe erstellt wird und nicht dynamisch erweitert werden kann, ist das Einfügen von Elementen schwieriger und aufwändiger, wenn das Array bereits voll ist. Auch das Suchen und Löschen eines Elements erfordert eine iterierende Suche durch das gesamte Array, daher lautet der Aufwand auch hier O(n).
Bei 1000 Aktien beträgt der Aufwand für alle drei Aktionen daher jeweils O(n):


Einfach verkettete Liste:

Einfügen: O(1) (wenn das neue Element am Anfang oder Ende der Liste eingefügt wird)
Suchen: O(n)
Löschen: O(n) (man muss das zu löschende Element in der Liste finden)
Das Einfügen von Elementen in eine einfach verkettete Liste ist einfach, aber das Suchen und Löschen eines Datensatzes erfordert eine sequentielle Suche durch die Liste, daher beträgt der Aufwand für beide Operationen O(n) und ist aufwändiger als in einer Hashtabelle.
Bei 1000 Aktien beträgt der Aufwand für das Einfügen O(1) und für das Suchen und Löschen jeweils O(n).

Zusammenfassend können wir sagen, dass die Hashtabelle für das Einfügen, Suchen und Löschen von Elementen am effizientesten ist, insbesondere wenn sie nicht stark gefüllt ist. Das normale Array ist für das Einfügen von Elementen am aufwändigsten, aber für das Suchen und Löschen am einfachsten. Die einfach verkettete Liste ist für das Einfügen von Elementen am einfachsten, aber für das Suchen und Löschen am aufwändigsten. Insgesamt sind die Laufzeiten für das Einfügen, Suchen und Löschen in der Hashtabelle am besten und werden in der O-Notation mit O(1) beschrieben, während die Laufzeiten für das Einfügen, Suchen und Löschen im Array und in der einfach verketteten Liste jeweils mit O(n) beschrieben werden.

