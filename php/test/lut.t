<?

function ok($ok,$txt)
{
   global $nok_cnt;

   if(!$ok){
      $nok_cnt++;
      echo "Fehler: $txt\n";
   }
}

$ok_cnt=$nok_cnt=0;

$ret=lut_init("blz.lut2f",9);
ok($ret==OK,"lut_init(): ".kc_txt($ret));
$p=lut_suche_pz(0,500,$ret,$blz_a);   /* alle Banken suchen (Prüfziffermethoden 0...500) */
ok($ret==OK,"lut_suche_pz(): ".kc_txt($ret));

for($cnt=0;$cnt<100;$cnt++){
   foreach($blz_a as $i=>$blz){
      $ret1=lut_multiple($blz,0,$cnt1,$name,$name_kurz,$plz,$ort,$pan,$bic,$pz,$nr,$aenderung,$loeschung,$nachfolge_blz);
      $name1=lut_name($blz);
      $name_kurz1=lut_name_kurz($blz);
      $plz1=lut_plz($blz);
      $ort1=lut_ort($blz);
      $pan1=lut_pan($blz);
      $bic1=lut_bic($blz);
      $pz1=lut_pz($blz);
      $nr1=lut_nr($blz);
      $aenderung1=lut_aenderung($blz);
      $loeschung1=lut_loeschung($blz);
      $nachfolge_blz1=lut_nachfolge_blz($blz);
      ok($name==$name1,"bei $blz, Name: $name / $name1");
      ok($name==$name1,"bei $blz, Name_kurz: $name_kurz / $name_kurz1");
      ok($plz1==$plz,"bei $blz, PLZ: $plz / $plz1");
      ok($ort1==$ort,"bei $blz, Ort: $ort / $ort1");
      ok($pan==$pan1,"bei $blz, : $pan / $pan1");
      ok($bic==$bic1,"bei $blz, : $bic / $bic1");
      ok($pz==$pz1,"bei $blz, : $pz / $pz1");
      ok($nr==$nr1,"bei $blz, : $nr / $nr1");
      ok($aenderung==$aenderung1,"bei $blz, : $aenderung / $aenderung1");
      ok($loeschung==$loeschung1,"bei $blz, : $loeschung / $loeschung1");
      ok($nachfolge_blz==$nachfolge_blz1,"bei $blz, : $nachfolge_blz / $nachfolge_blz1");
      $info=lut_info("",$i,$v);
      $ok_cnt++;
   }
   echo "Durchlauf $cnt, Anzahl Tests: ok: $ok_cnt, nicht ok: $nok_cnt\n";
}
echo "Anzahl Tests: ok: $ok_cnt, nicht ok: $nok_cnt\n";
lut_free();
echo malloc_report();
?>
