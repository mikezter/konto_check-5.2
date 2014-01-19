BEGIN{ extension("konto_check_awk.so","dlload") }
{ printf "%s: %d (%s)\n",$0,ret=konto_check($1,$2),retval2txt(ret) }
