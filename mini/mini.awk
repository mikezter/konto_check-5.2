# Mini-Programm für AWK (große Variante mit Bankinfo, für gepatchten AWK)
{
   if($1 && $2){              # Test nur, falls BLZ und Konto angegeben sind
      ret=konto_check($1,$2)  # testen
      if(bank_valid($1)>0)    # bei gültiger BLZ Infos holen
         bank_info=", Bank: " bank_name($1) ", " bank_plz($1) " " bank_ort($1)
      else 
         bank_info=""
      print $0 ": " ret " (" retval2txt(ret) ")" bank_info
   }
}
