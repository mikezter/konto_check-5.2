use Business::KontoCheck qw(kto_check_init kto_check_blz lut_name
     lut_plz lut_ort lut_cleanup %kto_retval);

($ret=kto_check_init("blz.lut2"))>0 || $ret==-38
      or die "Fehler bei der Initialisierung: $kto_retval{$ret}\n";

open(IN,@ARGV[0]) or die "Kann ".@ARGV[0]." nicht lesen: $!\n";
open(OUT,"> @ARGV[1]") or die "Kann @ARGV[1] nicht schreiben: $!\n";

while(<IN>){
   chomp;
      # eine Zeile aufdr�seln und den Variablen zuweisen
   ($valid,$blz,$kto)=/(([0-9]+)[ \t]+([0-9]+))?/;
   if($valid){
      $retval=kto_check_blz($blz,$kto);
      if($retval>0){   # OK -> Banknamen und Adresse ausgeben
         $bank_info="; ".lut_name($blz).", ".lut_plz($blz)." ".lut_ort($blz);
      }
      else{ # Fehler, leer lassen
         $bank_info="";
      }
      print OUT "$blz $kto: $kto_retval{$retval}$bank_info\n";
   }
}
lut_cleanup(); # Speicher freigeben

