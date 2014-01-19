BEGIN{ extension("./konto_check_awk.so","dlload") }

/^$/ ; /^#/                   # Leerzeile bzw. Kommentar: direkt übernehmen
/^[0-9]/{                     # Zeile mit numerischem Anfang -> BLZ/Kto.
   if($1 && $2){              # Test nur, falls BLZ und Konto angegeben sind
      ret=konto_check($1,$2)  # testen
      if(bank_valid($1)>0)    # bei gültiger BLZ Infos holen
         bank_info=", " bank_name($1) ", " bank_plz($1) " " bank_ort($1)
      else 
         bank_info=""
      print $0 ": " ret " (" retval2txt(ret) ")" bank_info
   }
}
