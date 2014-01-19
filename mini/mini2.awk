# Mini-Programm für AWK (kleine Variante, für AWK mit der Modulversion von konto_check)
BEGIN{ extension("/usr/local/lib/konto_check_awk.so","dlload") }
{ printf "%s: %d (%s)\n",$0,ret=konto_check($1,$2),retval2txt(ret) }
