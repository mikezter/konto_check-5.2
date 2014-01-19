<?
/* Dies ist ein kleines Testskript, um das PHP-API der konto_check Bibliothek zu zeigen.
 * geschrieben März 2008, M. Plugge
 * kleine Änderungen Januar 2009 M.P.
 * Umstellung auf das neue API Februar 2009 M.P.
 * Suchfunktionen und Beschreibung der Prüfziffermethoden hinzugefügt August/September 2009
 */

      ##########################################################################################
      ##########################################################################################
      ###  Achtung: Dieses Skript sollte nur mit der Version 2.99 oder höher der konto_check ###
      ###  Bibliothek benutzt werden, da bei 2.98 u.U. PHP-Abstürze vorkommen können (durch  ###
      ###  nicht freigegebenen Speicher). Auch die Suchfunktionen sind erst ab Version 2.99  ###
      #### implementiert.                                                                    ###
      ##########################################################################################
      ##########################################################################################

   /* get_var(): Request-Variable holen, dabei Sonderzeichen maskieren */
function get_var($var)
{
   global $$var;

   if(isset($_REQUEST[$var]))
      $$var=trim(htmlspecialchars($_REQUEST[$var]));
   else
      $$var="";
}

   /* get_var1(): Request-Variable holen für Query-String */
function get_var1($var)
{

   if(isset($_REQUEST[$var]))
      return $_REQUEST[$var];
   else
      return "";
}

   /* get_var_bool(): boolsche Request-Variable holen */
function get_var_bool($var)
{
   $vc="${var}_chk";
   global $$var,$$vc;

   if(isset($_REQUEST[$var])){
      $$var=1;
      $$vc=" checked";
   }
   else
      $$var=0;
}

function head_link($i,$extra,$name)
{
   global $ausgabe;

   if(!$i)
      echo <<<HTML
   <td class="nchk"><a href="$extra">$name</a></td>

HTML;
   else if($ausgabe==$i)
      echo "   <td class=\"chk\">$name</td>\n";
   else
      echo <<<HTML
   <td class="nchk"><a href="?ausgabe=$i$extra">$name</a></td>

HTML;
}

   /* blz_link(): Link für die Detailinfos zu Bankleitzahlen zusammenstellen;
    * dabei sollen die Übergabevariablen erhalten bleiben.
    */
function blz_link($blz)
{
   global $detail,$hauptstellen;

   if($detail){
      $target="";
      $d="&detail=${_REQUEST['detail']}";
   }
   else{
      $target=" target=\"_blank\"";
      $d="";
   }
   if($hauptstellen)
      $hs="&hauptstellen=1";
   else
      $hs="";

   return "<a href=\"?blz3=$blz&suchen8=1"
      ."&ausgabe=".get_var1('ausgabe')
      ."&blz1=".get_var1('blz1')
      ."&blz2=".get_var1('blz2')
      ."&name=".get_var1('name')
      ."&name_kurz=".get_var1('name_kurz')
      ."&plz1=".get_var1('plz1')
      ."&plz2=".get_var1('plz2')
      ."&ort=".get_var1('ort')
      ."&pz1=".get_var1('pz1')
      ."&pz2=".get_var1('pz2')
      ."&bic1=".get_var1('bic1')
      ."&pz1=".get_var1('pz1')
      ."&pz2=".get_var1('pz2')
      ."$hs$d\" title=\"Detailinfos zur BLZ $blz\"$target>$blz</a>";
}


   /* Skriptvariablen holen */
get_var("methode");
get_var("kto1");
get_var("blz");
get_var("kto");
get_var("iban");
get_var("zweck");
get_var("blz1");
get_var("blz2");
get_var("blz3");
get_var("bic1");
get_var("pz1");
get_var("pz2");
get_var("plz1");
get_var("plz2");
get_var("name");
get_var("name_kurz");
get_var("ort");
get_var("ausgabe");
get_var("liste");
get_var("tabelle");
get_var_bool("iban_test");
get_var_bool("iban2bic");
get_var_bool("methode_test");
get_var_bool("kto_test");
get_var_bool("zweck_test");
get_var_bool("zweck_gen");
get_var_bool("dump");
get_var_bool("info");
get_var_bool("suchen1");
get_var_bool("suchen2");
get_var_bool("suchen3");
get_var_bool("suchen4");
get_var_bool("suchen5");
get_var_bool("suchen6");
get_var_bool("suchen7");
get_var_bool("suchen8");
get_var_bool("methode_txt");
get_var_bool("hauptstellen");
get_var_bool("kc_info");
get_var_bool("version");
get_var_bool("methode_liste");
get_var_bool("detail");

if(empty($blz2) || $blz2<$blz1)$blz2=$blz1;
if(empty($pz2) || $pz2<$pz1)$pz2=$pz1;
if(empty($plz2) || $plz2<$plz1)$plz2=$plz1;

$ausgabe=intval($ausgabe);
if($ausgabe<1)
   $ausgabe=1;
else if($ausgabe>4)
   $ausgabe=4;

$suchen=$suchenx=0;
if($suchen1 && !empty($name))$suchen=1;
if($suchen2 && !empty($name_kurz))$suchen=2;
if($suchen3 && !empty($ort))$suchen=3;
if($suchen4 && !empty($bic1))$suchen=4;
if($suchen5 && !empty($plz1))$suchen=5;
if($suchen6 && !empty($blz1))$suchen=6;
if($suchen7 && !empty($pz1))$suchen=7;
if($suchen8 && !empty($blz3))$suchenx=8;

$b1=$b2=$b3=$b4="nchk";
switch($ausgabe){
   case 1: $b1="chk"; break;
   case 2: $b2="chk"; break;
   case 3: $b3="chk"; break;
   case 4: $b4="chk"; break;
}

echo <<<HTML
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
   <title>konto_check Testseite</title>
   <meta http-equiv="content-type" content="text/html; charset=ISO-8859-1">
   <meta name="description" content="Testseite für die PHP-Version von konto_check">
   <meta name="author" content="Michael Plugge">
   <link rel="stylesheet" type="text/css" href="formate.css" />
</head>
<body bgcolor="#f0f0f0">

<center>
<h1><em>Konto_check</em></h1>
<h2>C/PHP/Perl-Library zur Prüfzifferberechnung von Kontonummern</h2>
</center>

<center><p><table border cellpadding="3"><tr>

HTML;
   head_link(0,"konto_check.php","Hauptseite");
   head_link(1,"","Einzeltest");
   head_link(2,"","Listentest");
   head_link(3,"","Suche nach Banken");
   head_link(4,"&kc_info=1","Infos");
echo "</tr></table></center>\n";
switch($ausgabe){

   case 1:
      #######################################
      ####    Startseite / Einzeltest     ###
      #######################################

      echo <<<HTML
<h1>Testseite für <em>konto_check</em> (PHP-Version)</h1>
<p>Auf dieser Seite können Sie Kontonummern mit Hilfe der <em>konto_check</em>
library testen. Falls bei einer Prüfziffermethode eine bestimmte Untermethode
getestet werden soll, ist diese als Ziffer oder Buchstabe an die Methode
anzuhängen, z.B. 903 (oder 90c) für Methode 90c.

<p>Den kompletten PHP-Quellcode dieses Skriptes können Sie mit dem Button
"Quellcode dieses Skriptes anzeigen" im Unterpunkt &lt;Infos&gt; im Broser
ansehen. Diese Seite ersetzt die alte HTML/CGI-Seite; die Funktionalität und
Benutzerfreundlichkeit wurde aufgrund der Umstellung auf PHP &ndash; das für
Webseiten natürlich besser geeignet ist als&nbsp;C&nbsp;:-)&nbsp;&ndash; stark
erweitert.

<form method="get">
<h2>Einzeltest von Kontonummern etc.</h2>
<input type="checkbox" name="methode_txt"$methode_txt_chk> Text der Prüfzifferberechnungsmethoden ausgeben<br>
<input type="checkbox" name="detail"$detail_chk> Details zur Bank anzeigen
<p><table cellspacing=12>
<tr>
   <td>PZ/Kto.:</td><td><input type="text" value="$methode" name="methode" size="12" maxlength="3">
   <input type="text" value="$kto1" name="kto1" size="12" maxlength="10"></td>
   <td colspan="2"><input type=submit name="methode_test" value="Kontonummer prüfen"></td>
</tr>
<tr>
   <td>BLZ/Kto.:</td>
   <td><input type="text" value="$blz" name="blz" size="12" maxlength="8">
   <input type="text" value="$kto" name="kto" size="12" maxlength="10"></td>
   <td colspan="2"><input type=submit name="kto_test" value="Kontonummer prüfen"></td>
</tr>
<tr>
   <td>IBAN: </td>
   <td><input type="text" value="$iban" name="iban" size="30" maxlength="34"></td>
   <td colspan="2"><input type=submit name="iban_test" value="IBAN prüfen">
       <input type=submit name="iban2bic" value="Kontodaten aus der IBAN bestimmen"></td>
</tr>
<tr>
   <td>Zweck: </td>
   <td><input type="text" value="$zweck" name="zweck" size="30" maxlength="30"></td>
   <td><input type=submit name="zweck_test" value="Verwendungszweck prüfen"></td>
   <td><input type=submit name="zweck_gen" value="Verwendungszweck generieren"></td>
</tr>
</table>
<input type="hidden" name="ausgabe" value="$ausgabe">
HTML;
      break;

   case 2:

      ##########################
      ####    Listentest     ###
      ##########################

      $liste2=explode("\n",$liste);
      $liste3=array();
      foreach($liste2 as $i=>$v){
         $zeile=trim($v);
         $p1=strtolower(substr($zeile,0,1));
         $p2=strtolower(substr($zeile,1,1));
         if((ord($p1)>=48 && ord($p1)<=57  || ord($p1)>=97 && ord($p1)<=ord('f'))
               && ($p2==" " || ord($p2)>=48 && ord($p2)<=57))
            $liste3[]=$zeile;
      }
      $liste_neu=implode("\n",$liste3);
      if($tabelle=="text"){
         $t1_chk="";
         $t2_chk=" checked";
      }
      else{
         $t1_chk=" checked";
         $t2_chk="";
      }
      echo <<<HTML
<h2>Listentest von Kontonummern</h2>
<form method="post">
<p><table width="100%" cellspacing="12"><tr><td valign="top"><textarea name="liste" rows="12" cols="20">
PZ/BLZ Konto

$liste_neu</textarea></td>
<td valign="top">Im nebenstehenden Feld können Sie bis zu 1000 Kontonummern eingeben,
die getestet werden sollen. Jede Zeile sollte zuerst die Bankleitzahl, dann (durch
ein Blank getrennt) die Kontonummer enthalten. Der Rest der Zeile wird ignoriert.
Zeilen, die nicht mit einer Ziffer (bzw. a oder b bei Methode a0...) beginnen, werden
übersprungen. Falls mehr als 1000 Kontonummern eingegeben werden, werden
die überzähligen ignoriert.

<p><input type="checkbox" name="methode_liste"$methode_liste_chk>Benutzte Prüfmethode ausgeben<br>
<p><input type="radio" name="tabelle" value="tabelle"$t1_chk>Ausgabe als Tabelle (langsamer Aufbau, Proportionalschrift)<br>
<input type="radio" name="tabelle" value="text" $t2_chk>Ausgabe als Text (schnellerer Aufbau)
</td>
</tr></table>

<p><input type=submit value="Liste prüfen">
<input type="hidden" name="ausgabe" value="$ausgabe">
HTML;
      break;

   case 3:

      ##########################################
      ####    Suche nach Bankleitzahlen      ###
      ##########################################

      echo <<<HTML
<h2>Suche nach Banken</h2>
<p>Auf dieser Seite können Sie Bankleitzahlen, die gewisse Kriterien erfüllen,
suchen. Bei den Feldern, die eine Texteingabe erwarten (Bankname, Ort, BIC)
kann der Text am Anfang abgekürzt werden (z.B. findet a als Ort alle Orte, die
mit a beginnen, aa findet Aachen und Aalen etc.). Bei numerischen Eingaben
(BLZ, PLZ, Prüfziffer) sind zwei Eingabefelder vorhanden, mit denen eine untere
und obere Schranke für den Suchbereich angegeben werden kann.

<p><form method="get">
<input type="checkbox" name="hauptstellen"$hauptstellen_chk> Nur die Hauptstellen ausgeben<br>
<input type="checkbox" name="detail"$detail_chk> Detailinfos im gleichen Fenster ausgeben
<table cellspacing=12>
<tr>
   <td>Bankleitzahl:</td>
   <td><input type="text" value="$blz3" name="blz3" size="8" maxlength="8"></td>
   <td></td>
   <td></td>
   <td><input type="submit" name="suchen8" value="alle Infos zu der Bank ausgeben"></td>
</tr>
<tr>
   <td>Bankleitzahl (Bereich):</td>
   <td><input type="text" value="$blz1" name="blz1" size="8" maxlength="8"></td>
   <td>bis</td>
   <td><input type="text" value="$blz2" name="blz2" size="8" maxlength="8"></td>
   <td><input type="submit" name="suchen6" value="Banken suchen"></td>
</tr>
<tr>
   <td>Bankname:</td>
   <td colspan="3"><input type="text" value="$name" name="name" size="30" maxlength="34"></td>
   <td><input type="submit" name="suchen1" value="Banken suchen"></td>
</tr>
<tr>
   <td>Bankname (Kurzform):</td>
   <td colspan="3"><input type="text" value="$name_kurz" name="name_kurz" size="30" maxlength="34"></td>
   <td><input type="submit" name="suchen2" value="Banken suchen"></td>
</tr>
<tr>
   <td>Postleitzahl:</td>
   <td><input type="text" value="$plz1" name="plz1" size="8" maxlength="8"></td>
   <td>bis</td>
   <td><input type="text" value="$plz2" name="plz2" size="8" maxlength="8"></td>
   <td><input type="submit" name="suchen5" value="Banken suchen"></td>
</tr>
<tr>
   <td>Ort:</td>
   <td colspan="3"><input type="text" value="$ort" name="ort" size="30" maxlength="34"></td>
   <td><input type="submit" name="suchen3" value="Banken suchen"></td>
</tr>
<tr>
   <td>BIC:</td>
   <td colspan="3"><input type="text" value="$bic1" name="bic1" size="30" maxlength="30"></td>
   <td><input type="submit" name="suchen4" value="Banken suchen"></td>
</tr>
<tr>
   <td>Prüfziffer:</td>
   <td><input type="text" value="$pz1" name="pz1" size="3" maxlength="3"></td>
   <td>bis</td>
   <td><input type="text" value="$pz2" name="pz2" size="3" maxlength="3"></td>
   <td><input type="submit" name="suchen7" value="Banken suchen"></td>
</tr>
</table>
<input type="hidden" name="ausgabe" value="$ausgabe">
HTML;
      break;

   case 4:

      ######################
      ####    Infos      ###
      ######################

      echo <<<HTML
<h2>Infos</h2>
<p>Hier gibt es einige Infos zur Version der <em>konto_check</em> Bibliothek und der verwendeten
Datendatei blz.lut. Außerdem können Sie auch den kompletten Quellcode des Skriptes ansehen.

<p><form method="get">
<input type="submit" name="dump" value="Quellcode dieses Skriptes anzeigen">
<input type="submit" name="info" value="Infos zur LUT-Datei anzeigen">
<input type="submit" name="version" value="Versionsinfo anzeigen">
<input type="hidden" name="ausgabe" value="$ausgabe">
HTML;
      break;
}

echo "</form>\n";

########################################################################################
###                   Skript ausgeben                                                ###
########################################################################################

if($dump){  /* Das Skript ausgeben */
   $name=$_SERVER["SCRIPT_FILENAME"];  /* Skriptnamen holen */
   echo "<p><center><hr width=80%></center>\n",
      "<h2>Quellcode dieses Skriptes</h2>\n";
   show_source($name);
   echo "</body>\n</html>\n";
   exit(0);
}

########################################################################################
###                   Infos zur Bibliothek                                           ###
########################################################################################

if($version || $kc_info)
   echo "<p><hr width=\"80%\" align=\"center\">\n<h2>Info zur <em>konto_check</em> Version:</h2>\n".
         get_kto_check_version();

lut_init("",9); /* Bibliosthek initialisieren (Defaultdatei, aber alle Felder) */
if($info || $kc_info){   /* Infos zur LUT-Datei ausgeben */
   $ret=lut_info("/etc/blz.lut",$info1,$valid1,$info2,$valid2,$info3,$slots);
   $valid1_html=kto_check_retval2txt_short($valid1)." / ".kto_check_retval2html($valid1);
   $valid2_html=kto_check_retval2txt_short($valid2)." / ".kto_check_retval2html($valid2);
   if($ret==OK){
      if(!$kc_info)echo "<p><hr width=\"80%\" align=\"center\">\n";
      echo <<<HTML
<h2>Info zur LUT-Datei /etc/blz.lut</h2>
<table>
<tr><td>Datensatz1: </td><td align="right"> $valid1  </td><td>($valid1_html)</td></tr>
<tr><td>Datensatz2: </td><td align="right"> $valid2 </td><td>($valid2_html)</td></tr>
</table>
<pre>
<p>$info1
<hr width="30%" align="left">
$info2
</pre>
<h2>Interna der LUT-Datei:</h2>
<pre>
<p>$info3

HTML;
      foreach($slots as $idx=>$value)echo $value,"\n";
      echo "</pre>\n<p>";
   }
   lut_init("",9);    /* die LUT-Datei laden, und dann Infos über die Blocks ausgeben */
   $ret=lut_info("",$info,$valid); /* Aufruf mit leerem Dateinamen: Info zu geladenen Blocks */
   $valid_html=kto_check_retval2html($valid);
   if($ret==OK){
      echo <<<HTML

<h2>Info zu in den Speicher geladenen Blocks:</h2>
Gültigkeit: $valid ($valid_html)
<pre>
<p>$info
</pre>
HTML;
   }
}

if($kto_test || $iban_test || $iban2bic || $zweck_gen || $zweck_test || $suchen || $suchenx || !empty($liste3))
   echo "<p>&nbsp;<p><hr width=80%>\n<h2>Ergebnis</h2>\n";

########################################################################################
###                   Einzeltest                                                     ###
########################################################################################

if($methode_test){ /* mit Prüfziffermethode testen */
   if(strlen($methode)==1)$methode="0$methode";
   $ret=kto_check_pz_dbg($methode,$kto1,0,$methode,$methode1);
   $ret_html=kto_check_retval2html($ret);
   echo "<p>&nbsp;<p><center><hr width=80%></center>\n<h2>Ergebnis</h2>\n";
   echo "Test mit der Prüfziffermethode $methode: $ret / $ret_html\n";
   echo "<p><pre>\n";
   if($methode_txt)do{

         /* Beschreibung (Kodierung ist in ISO-8859-1, daher htmlspecialchars()
          * verwenden) und nächste zu verwendende Methode holen.
          */
      $txt=htmlspecialchars(lut_methode_txt($methode1,$methode1));
      echo "$txt\n\n";
   }while($methode1>=0);
}

if($kto_test){ /* Bankverbindung testen */
   $ret=kto_check_blz_dbg($blz,$kto,$methode,$methode1);
   $ret_html=kto_check_retval2html($ret);
   echo "Test der Bankverbindung: $ret / $ret_html (mit Methode $methode)\n";
   echo "<p><pre>\n";
   if($methode_txt)do{

         /* Beschreibung (Kodierung ist in ISO-8859-1, daher htmlspecialchars()
          * verwenden) und nächste zu verwendende Methode holen.
          */
      $txt=htmlspecialchars(lut_methode_txt($methode1,$methode1));
      echo "$txt\n\n";
   }while($methode1>=0);
   echo "</pre>\n<p>\n";
}
if($kto_test && $detail || $suchenx){ /* Infos zu einer Bank ausgeben */
   if($suchenx==8)$blz=$blz3;
      /* alles in einem Rutsch holen */
   $multi=lut_multiple($blz,0,$anzahl,$name,$name_kurz,$plz,$ort,$pan,$bic,$pz,$nr,
         $aenderung,$loeschung,$nachfolge_blz);
   echo "<h3>Infos zu BLZ $blz:</h3>";
   if($multi==OK){
      echo <<<HTML
<table>
   <tr><td>BLZ:</td><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>$blz</td></tr>
   <tr><td>Bank:</td><td></td><td>$name</td></tr>
   <tr><td>Filialen:</td><td></td><td>$anzahl</td></tr>
   <tr><td>PLZ/Ort:</td><td></td><td>$plz $ort</td></tr>
   <tr><td>Kurzbezeichnung:</td><td></td><td>$name_kurz</td></tr>
   <tr><td>BIC:</td><td></td><td>$bic</td></tr>
   <tr><td>Prüfziffermethode:</td><td></td><td>$pz</td></tr>
   <tr><td>Nr.:</td><td></td><td>$nr</td></tr>
   <tr><td>Änderung:</td><td></td><td>$aenderung</td></tr>
   <tr><td>Löschung:</td><td></td><td>$loeschung</td></tr>
   <tr><td>Nachfolge-BLZ:</td><td></td><td>$nachfolge_blz</td></tr>
</table>
HTML;
      echo "<h3>PLZ und Ort der Filialen:</h3>\n<table>\n";
      for($i=1;$i<=$anzahl;$i++)
         echo "<tr><td align=\"right\"> $i. &nbsp; </td><td>",
              lut_plz($blz,$ret,$i-1)," </td><td> ",
              lut_ort($blz,$ret,$i-1),"</td></tr>";
      echo "</table>\n";
   }
   else
      echo "Rückgabewert von lut_multiple:  $multi / ",kto_check_retval2txt($multi),"\n";
}

if($iban_test && $iban){   /* IBAN testen */
   $ret=iban_check($iban,$ret1);
   $ret_html=kto_check_retval2html($ret);
   $ret1_html=kto_check_retval2html($ret1);
   echo "Test der IBAN: $ret / $ret_html<br>\n";
   echo "Test der Bankverbindung: $ret1 / $ret1_html<br>\n";
}

if($iban2bic){    /* Bankverbindung aus der IBAN bestimmen */
   $bic=iban2bic($iban,$ret,$blz,$kto);   /* Die Funktion gibt BIC, BLZ und kto zurück */
   $ret_html=kto_check_retval2html($ret);
   if($ret!=IBAN2BIC_ONLY_GERMAN){
      $name=lut_name($blz,$ret1);   /* hier werden die Infos einzeln geholt */
      $ret1_html=kto_check_retval2html($ret1);
      if($ret1==OK){    /* BLZ ist ok, weitere Sachen holen */
         $plz=lut_plz($blz);
         $ort=lut_ort($blz);
         $name_kurz=lut_name_kurz($blz);
         echo <<<HTML
<table>
   <tr><td>ret:</td><td></td><td>$ret / $ret_html</td></tr>
   <tr><td>BIC:</td><td></td><td>$bic</td></tr>
   <tr><td>BLZ:</td><td></td><td>$blz</td></tr>
   <tr><td>Konto:</td><td></td><td>$kto</td></tr>
   <tr><td>Bank:</td><td></td><td>$name</td></tr>
   <tr><td>Ort:</td><td></td><td>$plz $ort</td></tr>
   <tr><td>Kurzname: </td><td></td><td>$name_kurz</td></tr>
</table>
HTML;
      }
      else
         echo "Test Bankverbindung:$ret1_html";
   }
   else
         echo $ret_html;
}

if($zweck_test){   /* Strukturierten Verwendungszweck (IPI) testen */
   $ret=ipi_check($zweck);
   $ret_html=kto_check_retval2html($ret);
   echo "Test des strukturierten Verwendungszwecks: $ret / $ret_html<br>\n";
}

if($zweck_gen){   /* Strukturierten Verwendungszweck (IPI)  generieren */
   $out=ipi_gen($zweck,$ret,$papier);
   $ret_html=kto_check_retval2html($ret);
   if($ret==OK)
      echo <<<HTML
<table>
   <tr><td>Strukturierter Verwendungszweck:</td><td>&nbsp;&nbsp;&nbsp;</td><td>$out</td></tr>
   <tr><td>Papierform:</td><td></td><td>$papier</td></tr>
   <tr><td>Rückgabewert:</td><td></td><td>$ret / $ret_html</td></tr>
</table>
HTML;
   else
      echo "Rückgabewert: $ret / $ret_html<br>\n";
}

########################################################################################
###                   Listentest                                                     ###
########################################################################################

if(!empty($liste3)){
   if($tabelle=="tabelle")
      echo "<table cellspacing=\"5\">";
   else
      echo "<pre>";
   $cnt=0;
   foreach($liste3 as $i=>$zeile){
      if(++$cnt>1000)break;   /* Maximalzahl erreicht (1000 Konten pro Aufruf) */
      $zeile_a=split("[ \t]+",$zeile,3);
      if(count($zeile_a)>1){ /* BLZ/Konto Kombination vorhanden */
         $b=$zeile_a[0];
         $k=$zeile_a[1];
         if(strlen($b)==1){
            $ret=kto_check_pz_dbg("0$b",$k,0,$methode);
            $blz_link=sprintf("%8s",$b);
         }
         else if(strlen($b)<4){
            $ret=kto_check_pz_dbg($b,$k,0,$methode);
            $blz_link=sprintf("%8s",$b);
         }
         else{
            $ret=kto_check_blz_dbg($b,$k,$methode);
            $blz_link=blz_link($b);
         }
         $txt=kto_check_retval2html($ret);
         if($methode_liste && $ret>=0)
            $ml=" mit Methode $methode";
         else
            $ml="";
         if($tabelle=="tabelle")
            echo "<tr><td align=\"right\">$blz_link</td>"
               ."<td>&nbsp;</td><td align=\"right\">$k</td>"
               ."<td>&nbsp;</td><td>$txt$ml</td></tr>\n";
         else
            printf("%s  %010s  %s%s\n",$blz_link,$k,$txt,$ml);
      }
   }
   if($tabelle=="tabelle")
      echo "</table>";
   else
      echo "</pre>";
   echo "<p>Anzahl geprüfter Konten: $cnt\n";
}

########################################################################################
###                   Banken suchen                                                  ###
########################################################################################

if($suchen){
   $kct=kc_test_var();
   $hauptstellen2=0;
   switch($suchen){
      case 1:
        $result=lut_suche_namen($name,$ret,$blz1,$idx);
        break;
      case 2:
        $result=lut_suche_namen_kurz($name_kurz,$ret,$blz1,$idx);
        break;
      case 3:
        $result=lut_suche_ort($ort,$ret,$blz1,$idx);
        break;
      case 4:
        $result=lut_suche_bic($bic1,$ret,$blz1,$idx);
        break;
      case 5:
        $result=lut_suche_plz($plz1,$plz2,$ret,$blz1,$idx);
        break;
      case 6:
        $result=lut_suche_blz($blz1,$blz2,$ret,$blz1,$idx);
        $hauptstellen2=1;
        break;
      case 7:
        $result=lut_suche_pz($pz1,$pz2,$ret,$blz1,$idx);
        $hauptstellen2=1;
        break;
   }

      /* Hauptstellen zählen */
   $hs=0;
   if(!$hauptstellen2)foreach($result as $i=>$v)if(!$idx[$i])$hs++;

   if($suchen==2)
      $n_titel='<th title="Name der Bank (Kurzform)">Kurzname</th>';
   else
      $n_titel='<th title="Name der Bank (Langform)">Name</th>';

   if($hauptstellen || $hauptstellen2)
      $zw_titel='<th title="Anzahl Filialen)">Filialen</th>';
   else
      $zw_titel='<th title="Zweigstellen-Index (Hauptstelle: 0)">Index</th>';

   if(!$hauptstellen2)
      $hsx=" ($hs Hauptstellen)";
   else
      $hsx="";
   echo "<p>",count($result)," Banken gefunden$hsx<p><table cellspacing=\"7\">\n";
   echo <<<HTML
<tr align="left">
   <th title="Rückgabewert von lut_multiple()">ret</th>
   <th title="Bankleitzahl">BLZ</th>
   $zw_titel
   <th title="Prüfzifferverfahren">PZ</th>
   <th title="Bank Identifier Code">BIC</th>
   $n_titel
   <th title="Postleitzahl und Ort der Bank">PLZ und Ort</th>
</tr>

HTML;

      /* Array mit den Prüfziffermethoden aufbauen */
   $a=ord('A');
   for($i=0;$i<300;$i++)if($i<100)
      $xpz[$i]=sprintf("%02d",$i);
   else
      $xpz[$i]=sprintf("%c%d",$i/10-10+$a,$i%10);

      /* nun die gefundenen Banken ausgeben */
   foreach($result as $i=>$v){
      $index=$idx[$i];

         /* bei $hauptstellen=1 nur die Hauptstellen ausgeben (diese haben $index=0) */
      if(!$index || !$hauptstellen){
         $blz=$blz1[$i];
         $ret=kto_check_retval2txt_short(lut_multiple($blz,$index,
                  $anzahl,$name,$name_kurz,$plz,$ort,$pan,$bic,$pz));
         $pz=$xpz[$pz];
         if($suchen==2)$name=$name_kurz;  /* es wurde nach dem Kurznamen gesucht */
         if($hauptstellen || $hauptstellen2)
            $index=lut_filialen($blz); /* Anzahl Filialen */
         else
            $index++;   /* Index der Hauptstelle auf 1 (statt 0) setzen */
         $blz_link=blz_link($blz);
         echo <<<HTML
<tr>
   <td>$ret </td>
   <td>$blz_link</td>
   <td align=\"right\"> $index </td>
   <td align=\"right\"> $pz </td>
   <td> $bic </td>
   <td> $name </td>
   <td> $plz $ort </td>
</tr>
HTML;
      }
   }
   echo "</table>\n";
}
lut_cleanup(); /* Speicher freigeben */
?>
</body>
</html>
