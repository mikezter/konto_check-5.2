<?
function set_var($var)
{
   global $$var;

   if(isset($_REQUEST[$var]))
      $$var=$_REQUEST[$var];
   else
      $$var="";
}

   /* Übergabevariablen holen */
set_var("testkonten");
set_var("testen");

?>
<html>
<head>
<title>Konto_check Testseite</title>
<style type="text/css">
td{padding:2px 10px 2px 3px;}
</style>
</head>
<body>

<h1>Testseite für konto_check</h1>
Bitte in das folgende Textfeld die zu testenden Bankverbindungen
(BLZ/Kto, durch Blanks getrennt) eingeben.

<p><form method="post">
<textarea cols="20" rows="15" name="testkonten">
<?=$testkonten?>
</textarea>
<p><input type="submit" name="testen" value="Konten testen">
</form>

<?
if(!empty($testen) && !empty($testkonten)){

      /* Bibliothek initialisieren (mit Defaultwerten)  */
   if(($retval=lut_init())<OK && $retval!=LUT2_PARTIAL_OK)
      die('<p><font color="red">Fehler bei der Initialisierung: '
            .kto_check_retval2html($retval)."</font>");

   echo "<h2>Testergebnisse:</h2>\n<table>\n";
   $zeilen=explode("\n",$testkonten);   /* Textfeld in Zeilen aufteilen */
   foreach($zeilen as $i=>$v){
      $v=trim($v);
      if(!empty($v)){
         list($blz,$kto)=split("[ \t]+",$v);    /* Zeile aufdröseln */
         if(!empty($blz) && !empty($kto)){      /* BLZ und Konto sind notwendig */
            $retval=kto_check_blz($blz,$kto);   /* Bankverbindung testen */
            $rv_txt=kc_html($retval);           /* Rückgabewert als Klartext */
            $name=lut_name($blz,$ret);          /* Banknamen holen */
            if($ret==OK){                       /* Bank gefunden, BLZ ok */
               $plz=lut_plz($blz);              /* Postleitzahl der Bank */
               $ort=lut_ort($blz);              /* Ort der Bank */
               $info="$name</td><td>$plz $ort"; /* Bankinfo zusammenstellen */
            }
            else
               $info="";   /* Fehler in BLZ; Banknamen leer lassen */
            printf("<tr><td>$blz</td><td>$kto</td><td>$rv_txt</td><td>$info</td></tr>\n");
         }
      }
   }
   lut_free(); /* Speicher freigeben */
}
?>
</table>
</body>
</html>
