require "konto_check"

# Kodierung auf UTF-8 umstellen, initialisieren
KontoCheck::encoding 'u'
KontoCheck::init

# Ausgabedatei öffnen
out=case ARGV.size
   when 0 then raise ArgumentError, "Aufruf: ruby mini.rb eingabedatei [ausgabedatei]"
   when 1 then STDOUT
   else File.open(ARGV[1],"w")
end

# Eingabedatei zeilenweise einlesen und auswerten
File.open(ARGV[0],"r").each{ |zeile|
   zeile_arr=zeile.split
   if zeile_arr.size>=2 then 
      blz,kto=zeile_arr
      retval=KontoCheck::konto_check(blz,kto)
      if retval>0 then # ok, Name und PLZ/Ort ausgeben
         out.printf "%s %s: %s; %s, %s %s\n",blz,kto,KontoCheck::retval2txt(retval),
            KontoCheck::bank_name(blz),KontoCheck::bank_plz(blz),KontoCheck::bank_ort(blz)
      else     # Fehler
         out.printf "%s %s: %s\n",blz,kto,KontoCheck::retval2txt(retval)
      end
   end
}
KontoCheck::free  # Speicher freigeben
