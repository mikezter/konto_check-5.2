Dies ist der awk-Port f�r die konto_check-Bibliothek. Zum Kompilieren mu� man
zun�chst den Quellcode von gawk holen und konfigurieren, da die Datei gawk.h
ben�tigt wird; danach sollte er sich (zumindest unter Linux) problemlos
kompilieren lassen. Die notwendigen Befehle (f�r gawk-3.1.8) sind auch im Makefile
enthalten, so da� ein einfaches make ausreichen sollte, um die Erweiterung zu
generieren.

F�r den awk-Port werden nur relativ wenige Funktionen exportiert, diese auch
teilweise mit reduzierter Parameterzahl. Die LUT-Routinen werden alle nur f�r die
Hauptstellen aufgerufen; der Test eines Kontos wird �ber die alte Funktion
kto_check() gemacht, so da� f�r den ersten Parameter wahlweise eine BLZ oder eine
Pr�fziffermethode verwendet werden kann.

Hier eine kurze �bersicht der Routinen:

   retval=lut_init(lut_name,level) : initialisiert die konto_check Bibliothek
   retval=konto_check(blz,kto)     : Test eines Kontos. blz kann eine Bankleitzahl oder Pr�fziffermethode sein
   retval=iban_check(iban)         : testet, ob eine IBAN g�ltig ist
   iban=iban_gen(blz,kto)          : generiert eine IBAN aus deutscher BLZ und Kontonummer
   ipi=ipi_gen(zweck)              : generiert einen strukturierten Verwendungszweck
   retval=ipi_check(ipi)           : testet einen strukturierten Verwendungszweck
   retval=bank_valid(blz)          : testet, ob eine BLZ g�ltig ist
   name=bank_name(blz)             : bestimmt zu einer BLZ den Namen des Instituts
   name=bank_name_kurz(blz)        : bestimmt zu einer BLZ den Kurznamen des Instituts
   ort=bank_ort(blz)               : bestimmt zu einer BLZ den Ort der Hauptstelle
   bic=bank_bic(blz)               : bestimmt zu einer BLZ den BIC (Bank Identifier Code)
   plz=bank_plz(blz)               : bestimmt zu einer BLZ die Postleitzahl der Hauptstelle
   pz=bank_pz(blz)                 : bestimmt zu einer BLZ die verwendete Pr�fzifferberechnungsmethode
   txt=retval2txt(retval)          : wandelt den numerischen R�ckgabewert in Klartext um (Kodierung ISO 8859-1)
   txt=retval2utf8(retval)         : wandelt den numerischen R�ckgabewert in Klartext um (Kodierung UTF-8)

AWK ist nat�rlich im Vergleich zu anderen Sprachen sehr kompakt; mit dem
folgenden Einzeiler wird z.B. eine Datei mit BLZ/Konto-Kombinationen getestet
und das Ergebnis (numerisch und als Klartext) in eine andere Datei geschrieben:

gawk 'BEGIN{extension("konto_check_awk.so","dlload")} {if(/^[ 0-9]+/)printf "%3d %s (%s)\n",ret=konto_check($1,$2),$0,retval2txt(ret); else print $0}' testkonten.txt > testkonten.out

-------------------------------------

Die obige Version kompilierte konto_check als externes AWK-Modul; es ist
nat�rlich auch m�glich, konto_check direkt in den Quellcode von awk zu
integrieren. Die notwendigen �nderungen (f�r gawk-3.1.8) sind in der Datei
konto_check.gawk-3.1.8.diff enthalten.

Um den Patch zu integrieren, m�ssen Sie den Quellcode von gawk-3.1.8
herunterzuladen und zu entpacken. Wechseln Sie dann in das Verzeichnis und
geben die folgenden Befehle ein (dabei wird vorausgesetzt, da� die Datei
konto_check.gawk-3.1.8.diff im selben Verzeichnis steht und die Dateien
konto_check.c und konto_check.h auch in das Verzeichnis kopiert wurden):

   patch < konto_check.gawk-3.1.8.diff
   ./configure
   make
   strip gawk  # optional
   make install

(der letzte Schritt mu� als root ausgef�hrt werden).

Der Vorteil dieser L�sung liegt darin, da� sie auf allen Systemen funktioniert;
die Modulversion machte bei mir bei einem kurzen Test unter FreeBSD Probleme.

Es ist auch m�glich, konto_check als (vorher intallierte) shared library zu
benutzen; dazu mu� die Datei Makefile.am.shared nach Makefile.am kopiert und
dann automake aufgerufen werden.

Die beiden Dateien mini.patched.awk und mini2.patched.awk sind Beispielsdateien
f�r diese Version. Das obige Beispiel reduziert sich auf die folgende Zeile:

gawk '{if(/^[ 0-9]+/)printf "%3d %s (%s)\n",ret=konto_check($1,$2),$0,retval2txt(ret); else print $0}' testkonten.txt > testkonten.out

-------------------------------------

Update f�r AWK 4.0: Das interne Aufrufinterface von AWK hat sich sehr stark
ge�ndert; die Modulversion wird nun nicht mehr unterst�tzt, nur noch die
kompilierte Variante. Da man sowieso kompilieren mu�, macht es keinen
Unterschied ob man nur das Modul kompiliert oder awk selbst.
