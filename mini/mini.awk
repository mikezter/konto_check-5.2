# Mini-Programm f�r AWK (gro�e Variante mit Bankinfo, f�r gepatchten AWK)
{
   if($1 && $2){              # Test nur, falls BLZ und Konto angegeben sind
      ret=konto_check($1,$2)  # testen
      if(bank_valid($1)>0)    # bei g�ltiger BLZ Infos holen
         bank_info=", Bank: " bank_name($1) ", " bank_plz($1) " " bank_ort($1)
      else 
         bank_info=""
      print $0 ": " ret " (" retval2txt(ret) ")" bank_info
   }
}
