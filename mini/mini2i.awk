# Mini-Programm f�r AWK (kleine Variante, f�r gepatchten AWK)
{ printf "%s: %d (%s)\n",$0,ret=konto_check($1,$2),retval2txt(ret) }
