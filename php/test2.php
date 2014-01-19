<?
/* Dies ist ein kleines Testskript, um das PHP-API der konto_check Bibliothek zu zeigen.
 * geschrieben März 2008, M. Plugge
 */

   /* Skriptvariablen holen */
if(isset($_REQUEST["methode"]))$methode=$_REQUEST["methode"];
if(isset($_REQUEST["kto1"]))$kto1=$_REQUEST["kto1"];
if(isset($_REQUEST["blz"]))$blz=$_REQUEST["blz"];
if(isset($_REQUEST["kto"]))$kto=$_REQUEST["kto"];
if(isset($_REQUEST["iban"]))$iban=$_REQUEST["iban"];
if(isset($_REQUEST["zweck"]))$zweck=$_REQUEST["zweck"];
if(isset($_REQUEST["iban_test"]))
   $iban_test=$_REQUEST["iban_test"];
else 
   $iban_test=0;
if(isset($_REQUEST["iban2bic"]))
   $iban2bic=$_REQUEST["iban2bic"]; 
else 
   $iban2bic=0;
if(isset($_REQUEST["methode_test"]))
   $methode_test=$_REQUEST["methode_test"]; 
else 
   $methode_test=0;
if(isset($_REQUEST["kto_test"]))
   $kto_test=$_REQUEST["kto_test"]; 
else 
   $kto_test=0;
if(isset($_REQUEST["zweck_test"]))
   $zweck_test=$_REQUEST["zweck_test"];
else 
   $zweck_test=0;
if(isset($_REQUEST["zweck_gen"]))
   $zweck_gen=$_REQUEST["zweck_gen"]; 
else 
   $zweck_gen=0;
if(isset($_REQUEST["dump"]))
   $dump=$_REQUEST["dump"]; 
else 
   $dump=0;
if(isset($_REQUEST["info"]))
   $info=$_REQUEST["info"]; 
else 
   $info=0;
?>
<html><head><title>konto_check (PHP-Version)</title></head>
<body bgcolor="#f0f0f0">
<h1>Testseite für die PHP-Version von konto_check</h1>
Dies ist eine kleine Testseite für die PHP-Version von konto_check. Es werden
nur wenige Funktionen benutzt; ein etwas ausführlicheres Testskript findet sich
in der Quellcode-Distribution unter php/test.php (als Kommandozeilenversion).

<p>Den Quellcode dieses Skriptes können Sie mit dem Button am Ende direkt im
Broser ansehen.

<form method="get">
<h2>Test von Kontonummern etc.</h2>
<table cellspacing=12>
<tr>
   <td>PZ/Kto.:</td><td><input type="text" value="<?=$methode?>" name="methode" size="12" maxlength="3">
   &nbsp;&nbsp;<input type="text" value="<?=$kto1?>" name="kto1" size="12" maxlength="10"></td>
   <td colspan="2"><input type=submit name="methode_test" value="Kontonummer prüfen"></td>
</tr>
<tr>
   <td>BLZ/Kto.:</td>
   <td><input type="text" value="<?=$blz?>" name="blz" size="12" maxlength="8">
   &nbsp;&nbsp;<input type="text" value="<?=$kto?>" name="kto" size="12" maxlength="10"></td>
   <td colspan="2"><input type=submit name="kto_test" value="Kontonummer prüfen"></td>
</tr>
<tr>
   <td>IBAN: </td>
   <td><input type="text" value="<?=$iban?>" name="iban" size="30" maxlength="34"></td>
   <td colspan="2"><input type=submit name="iban_test" value="IBAN prüfen">
                   &nbsp;&nbsp;<input type=submit name="iban2bic" value="BIC etc. aus dem IBAN bestimmen"></td>
</tr>
<tr>
   <td>Zweck: </td>
   <td><input type="text" value="<?=$zweck?>" name="zweck" size="30" maxlength="30"></td>
   <td><input type=submit name="zweck_test" value="Verwendungszweck prüfen"></td>
   <td><input type=submit name="zweck_gen" value="Verwendungszweck generieren"></td>
</tr>
</table>

<p><input type=submit name="dump" value="Quellcode dieses Skriptes anzeigen">
<input type=submit name="info" value="Infos zur LUT-Datei anzeigen">

<?
if($dump){  /* Das Skript ausgeben */
   echo "<p>&nbsp;<p><center><hr width=80%></center>\n<h2>Quellcode dieses Skriptes:</h2>\n<pre>\n";
   $name=$_SERVER["SCRIPT_FILENAME"];  /* Skriptnamen holen */
   passthru("cat $name | perl -pe '"   /* nun das Skript ausgeben, mit leichter Syntaxhervorhebung durch Perl */

            /* dieser Perl-Einzeiler poliert die Ausgabe für HTML etwas auf; kein richtiges Prettyprinting,
             * nur ein paar farbliche Markierungen. Die Strings für Kommentare mußten unterbrochen werden,
             * damit die Kommentarmarkierungen nicht die Hervorhebungen durcheinanderbringen.
             * Mit lex könnte man natürlich besser und komfortabler machen...
             */
         ."s/&/&amp;/g; s/</&lt;/g; s/>/&gt;/g; "  /* grundlegende Sachen: [&<>] ersetzen durch HTML Entities */
         ."s+/\*+<em><font color=\"blue\">/"."*+g; s+\*"."/+*"."/</font></em>+g; "  /* Kommentare kursiv */
         ."s+&lt;EOD+\&lt;EOD<font color=\"orange\">+g; s+^EOD;+</font>EOD;+g; "    /* heredoc strings orange */
         ."s/&lt;\?/<font color=\"green\">&lt;?/g;  s+\?&gt;+?&gt;</font>+g;  '");  /* PHP grün */
   echo "</pre>";
}
else if($info){   /* Infos zur LUT-Datei ausgeben */
   $ret=lut_info("/etc/blz.lut",$info1,$valid1,$info2,$valid2);
   if($ret==OK){
      echo "<p>&nbsp;<p><center><hr width=80%></center>\n<h2>Info zur LUT-Datei:</h2>\n";
      echo "Datensatz1: $valid1<br>\n";
      echo "Datensatz2: $valid2<br>\n";
      if($valid1!=LUT2_BLOCK_NOT_IN_FILE)echo "<pre>",$info1,"</pre>\n";
      if($valid2!=LUT2_BLOCK_NOT_IN_FILE)echo "<hr width=80%><pre>",$info2,"</pre>\n";
   }
   lut_init();    /* die LUT-Datei laden, und dann Infos über die Blocks ausgeben */
   $ret=lut_info("",$info1,$valid1); /* Aufruf ohne Dateinamen => Ausgabe von geladenen Blocks */
   if($ret==OK){
      echo "<center><hr width=80%></center>\n<h2>Info zu in den Speicher geladenen Blocks:</h2>\n";
      if($valid1!=LUT2_BLOCK_NOT_IN_FILE)echo "<pre>",$info1,"</pre>\n";
      echo "\n</pre>\n";
   }
}
else if($kto_test || $iban_test || $iban2bic || $zweck_gen || $zweck_test){
   echo "<p>&nbsp;<p><center><hr width=80%></center>\n<h2>Ergebnis</h2>\n";
   lut_init(); /* Bibliosthek initialisieren (komplett mit Defaultwerten) */
}

if($methode_test){ /* mit Prüfziffermethode testen */
   $ret=kto_check_pz($methode,$kto1);
   echo "<p>&nbsp;<p><center><hr width=80%></center>\n<h2>Ergebnis</h2>\n";
   printf("Test mit der Prüfziffermethode $methode: %d / %s\n<p>",$ret,kto_check_retval2html($ret));
}

if($kto_test){ /* Bankverbindung testen */
   $ret=kto_check_blz($blz,$kto);
   printf("Test der Bankverbindung: %d / %s\n<p>",$ret,kto_check_retval2html($ret));
   $multi=lut_multiple($blz,0,$cnt,$name,$name_kurz,$plz,$ort,$pan,$bic); /* alle Infos zu der Bank in einem Rutsch holen */
   echo <<<EOD
<table>
   <tr><td>Bank:</td><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>$name</td></tr>
   <tr><td>Ort:</td><td></td><td>$plz $ort</td></tr>
   <tr><td>Kurzname:</td><td></td><td>$name_kurz</td></tr>
   <tr><td>BIC:</td><td></td><td>$bic</td></tr>
</table>
EOD;
}

if($iban_test){   /* IBAN testen */
   $ret_iban=iban_check($iban);
   $ret=$ret_iban['ret'];
   $ret3=$ret_iban['ret3'];
   $retk=$ret_iban['ret_kto'];
   $retk3=$ret_iban['ret3_kto'];
   echo "Test der IBAN: $ret / $ret3<br>\n";
   echo "Test der Bankverbindung: $retk / $retk3<br>\n";
}

if($iban2bic){    /* Bankverbindung aus der IBAN bestimmen */
   $i2b=iban2bic($iban);   /* Die Funktion gibt BIC, BLZ und kto zurück */
   if($i2b['ret2']!='IBAN2BIC_ONLY_GERMAN'){
      $bic=$i2b['bic'];
      $blz=$i2b['blz'];
      $kto=$i2b['kto'];
      $name=lut_name($blz);   /* hier werden die Infos einzeln geholt */
      if($name['ret']==1){    /* BLZ ist ok, weitere Sachen holen */
         $plz=lut_plz($blz);
         $ort=lut_ort($blz);
         $name_kurz=lut_name_kurz($blz);
         $name=$name['wert'];
         $plz=$plz['wert'];
         $ort=$ort['wert'];
         $name_kurz=$name_kurz['wert'];
         echo <<<EOD
<table>
   <tr><td>BIC:</td><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>$bic</td></tr>
   <tr><td>BLZ:</td><td></td><td>$blz</td></tr>
   <tr><td>Konto:</td><td></td><td>$kto</td></tr>
   <tr><td>Bank:</td><td></td><td>$name</td></tr>
   <tr><td>Ort:</td><td></td><td>$plz $ort</td></tr>
   <tr><td>Kurzname:</td><td></td><td>$name_kurz</td></tr>
</table>
EOD;
      }
      else
         echo $name['ret3'];
   }
   else
      echo $i2b['ret3'];
}

if($zweck_gen){   /* Strukturierten Verwendungszweck (IPI)  generieren */
   $ret_ipi=ipi_gen($zweck);
   $zw=$ret_ipi['zweck_out'];
   $papier=$ret_ipi['papier'];
   $ret=$ret_ipi['ret'];
   $ret3=$ret_ipi['ret3'];
   if($ret==1)
      echo <<<EOD
<table>
   <tr><td>Strukturierter Verwendungszweck:</td><td>&nbsp;&nbsp;&nbsp;</td><td>$zw</td></tr>
   <tr><td>Papierform:</td><td></td><td>$papier</td></tr>
   <tr><td>Rückgabewert:</td><td></td><td>$ret / $ret3</td></tr>
</table>
EOD;
   else
      echo "Rückgabewert: $ret / $ret3<br>\n";
}

if($zweck_test){   /* Strukturierten Verwendungszweck (IPI) testen */
   $ret_ipi=ipi_check($zweck);
   $ret=$ret_ipi['ret'];
   $ret3=$ret_ipi['ret3'];
   echo "Test des strukturierten Verwendungszwecks: $ret / $ret3<br>\n";
}

lut_cleanup(); /* Speicher freigeben */
?>
</body>
</html>
