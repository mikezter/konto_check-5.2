<?
# dies ist ein kleines Testprogramm für die diversen Funktionen der
# konto_check-Bibliothek (PHP-Version). Aufruf am besten per Kommandozeile, da
# keine HTML-Formatierung gemacht wird.

$lutfile="blz.lut";

function test_kto($blz,$kto)
{
   $ret=kto_check_blz($blz,$kto);
   $ret1=kto_check_retval2txt_short($ret);
   $ret2=kto_check_retval2txt($ret);
   printf("Test von %8s/%10s -> %3d (%s / %s)\n",$blz,$kto,$ret,$ret1,$ret2);
   return 0;
}

function anzahl_filialen($blz)
{
   $cnt=lut_filialen($blz);
   $ret=$cnt>0?"OK":kto_check_retval2txt($cnt);
   printf("Filialen von %s: %d -> %s\n",$blz,$cnt,$ret);
}

function test_iban2bic($iban)
{
   $bic=iban2bic($iban,$ret,$blz,$kto);
   echo "iban2bic(\"$iban\"):\nBIC: $bic\nret: $ret (".kc_txt($ret).")\nblz: $blz\nkto: $kto\n\n";
}

function test_iban_check($iban)
{
   $ret=iban_check($iban,$ret_kto);
   echo "iban_check(\"$iban\"): $ret (".kc_txt($ret).")\nret (konto_test): $ret_kto (".kc_txt($ret_kto).")\n\n";
}

function test_ipi_gen($zweck)
{
   $ipi=ipi_gen($zweck,$ret,$papier);
   echo "ipi_gen(\"$zweck\"): $ret (".kc_txt($ret).")\nipi:    $ipi\nPapier: $papier\n\n";
}

function test_ipi_check($zweck)
{
   $ret=ipi_check($zweck);
   echo "ipi_check(\"$zweck\"): $ret (".kc_txt($ret).")\n";
}

   /* zunächst für einige Tests mit Level 0 initialisieren (d.h. nur BLZ und
    * Prüfziffermethode). Später wird die Initialisierung noch erweitert (mit
    * Level 9, d.h. der komplette Datensatz)
    */
$ret=lut_init($lutfile,0,0,$lut_name);
$ret1=kto_check_retval2txt_short($ret);
$ret2=kto_check_retval2txt($ret);
printf("init mit Level 0: %d -> %s/%s\nLUT-Datei: Soll: $lutfile / benutzt: $lut_name\n\n",$ret,$ret1,$ret2);

printf("Tests von BLZ/Kto Kombinationen:\n");
test_kto("35050000","0200029908");
test_kto("67050505","37619663");
test_kto("60010071","267474702");
test_kto("7212007","5724414");
test_kto("72120078","572441");

echo "\nTest lut_name (Fehler, da Block noch nicht geladen)";
$blz=72120078;
echo "lut_name($blz): ".lut_name($blz,$ret)." -> $ret\n";

echo "\nTest Anzahl Filialen:\n";
anzahl_filialen("10020890");
anzahl_filialen("55090500");
anzahl_filialen("55090501");
anzahl_filialen("5509050");

echo "\nTest lut_multiple() (alle Werte zu einer BLZ holen;"
      . "\ndie Initialisierung ist hier allerdins nur mit Level 0 (nicht alle Blocks) gemacht):\n";
$ret=lut_multiple("10020890",0,$cnt,$name,$name_kurz,$plz,$ort,$pan,$bic,$pz);
echo "ret: $ret (".kc_txt($ret).")\ncnt: $cnt\nname: $name\nname_kurz: $name_kurz\nplz: $plz\nort: $ort\npan: $pan\nbic: $bic\npz: $pz\n";

echo "\nTest lut_multiple() mit Filiale:\n";
$ret=lut_multiple("10020890",3,$cnt,$name,$name_kurz,$plz,$ort,$pan,$bic,$pz);
echo "ret: $ret (".kc_txt($ret).")\ncnt: $cnt\nname: $name\nname_kurz: $name_kurz\nplz: $plz\nort: $ort\npan: $pan\nbic: $bic\npz: $pz\n";


   /* nun wird nochmal initialisiert (mit Level 9); dabei werden alle (vorhandenen!) Daten der
    * BLZ-Datei geladen (die Datei muß nicht komplett sein; die Datei blz.lut2 ist es z.B. nicht).
    */
$ret=lut_init($lutfile,9,0,$lut_name);
$ret1=kto_check_retval2txt_short($ret);
$ret2=kto_check_retval2txt($ret);
printf("init mit Level 9 (inkrementell, komplett): %d -> %s/%s\nLUT-Datei: Soll: $lutfile / benutzt: $lut_name\n\n",$ret,$ret1,$ret2);

echo "lut_info zu den geladenen Blocks:\n";
$info=lut_info("",$info1,$valid1,$info2,$valid2);
$v1=kc_txt($valid1);
$v2=kc_txt($valid2);
$sep1="-----------------------------------------------------------------";
$sep2="=================================================================";
echo "$sep2\nvalid1: $valid1 ($v1)\n$sep1\ninfo1:\n$info1$sep2\nvalid2: $valid2 ($v2)\n$sep1\ninfo2:\n$sep1\n$info2$sep2\n";

echo "\nlut_info() von $lutfile:\n";
$info=lut_info($lutfile,$info1,$valid1,$info2,$valid2,$info3,$slots);
$v1=kc_txt($valid1);
$v2=kc_txt($valid2);
echo "$sep2\nvalid1: $valid1 ($v1)\n$sep1\ninfo1:\n$info1$sep2\nvalid2: $valid2 ($v2)\n$sep1\ninfo2:\n$info2$sep2\n$info3\n$sep2\n";
foreach($slots as $i=>$v)echo "$v\n";
echo "$sep2\n";

echo "\nTest lut_multiple() mit Filiale (nochmal, nach inkrementellem init()):\n";
$ret=lut_multiple("10020890",3,$cnt,$name,$name_kurz,$plz,$ort,$pan,$bic,$pz);
echo "ret: $ret (".kc_txt($ret).")\ncnt: $cnt\nname: $name\nname_kurz: $name_kurz\nplz: $plz\nort: $ort\npan: $pan\nbic: $bic\npz: $pz\n";

echo "\nTest lut_multiple() mit Filialoffset zu groß:\n";
$ret=lut_multiple("10020890",10,$cnt,$name,$name_kurz,$plz,$ort,$pan,$bic,$pz);
echo "ret: $ret (".kc_txt($ret).")\ncnt: $cnt\nname: $name\nname_kurz: $name_kurz\nplz: $plz\nort: $ort\npan: $pan\nbic: $bic\npz: $pz\n";

echo "\niban2bic:\n";
test_iban2bic("DE40 5485 1440 0020 0000 30");
test_iban2bic("DE92 5509 0500 0100 1617 11");
test_iban2bic("DE93 5456 0320 0002 3430 02");

echo "\niban_check:\n";
test_iban_check("DE40 5485 1440 0020 0000 30");
test_iban_check("DE92 5509 0500 0100 1617 11");
test_iban_check("DE93 5456 0320 0002 3430 02");

test_ipi_gen("ajaaeural435q43");
test_ipi_gen("ajaaeur843843384al435q43");
test_ipi_gen("ajaaeural435q4#ö3");

test_ipi_check("42000AJAAEURAL435Q43");
test_ipi_check("42000AJAAEURAL435Q41");

$ret=lut_cleanup();  /* noch Speicher aufräumen (wäre zu Hause auch mal angebracht ;-))) */
?>
