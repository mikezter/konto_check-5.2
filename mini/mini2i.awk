# Mini-Programm für AWK (kleine Variante, für gepatchten AWK)
{ printf "%s: %d (%s)\n",$0,ret=konto_check($1,$2),retval2txt(ret) }
