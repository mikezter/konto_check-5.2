AWK_FILES = awk/00readme.txt awk/konto_check_awk.c awk/makefile awk/mini.awk awk/mini2.awk awk/testkonten.txt awk/*diff
CFLAGS = -Igawk-3.1.8/ -I. -O -fPIC -DHAVE_CONFIG_H -g
LDFLAGS = -shared -lz

default: test

test: lib
	awk -f mini.awk testkonten.txt > testkonten.out

konto_check.c: ../konto_check.c
	cp ../konto_check.c .
konto_check.h: ../konto_check.h
	cp ../konto_check.h .
gawk-3.1.8/awk.h:
	wget ftp://ftp-stud.fht-esslingen.de/pub/Mirrors/ftp.gnu.org/gawk/gawk-3.1.8.tar.gz
	tar xzf gawk-3.1.8.tar.gz
	cd gawk-3.1.8 ; ./configure

konto_check_awk.o: gawk-3.1.8/awk.h konto_check_awk.c konto_check.h
	gcc -c $(CFLAGS) konto_check_awk.c -o konto_check_awk.o

lib: konto_check_awk.so
konto_check_awk.so: konto_check_awk.o konto_check.o
	gcc $(LDFLAGS) konto_check.o konto_check_awk.o -o konto_check_awk.so

konto_check.o: konto_check.c konto_check.h
konto_check_awk.o: konto_check_awk.c konto_check.h

install: konto_check_awk.so
	cp konto_check_awk.so /usr/lib/

clean:
	rm -vf *.o
distclean: clean
	rm -vf konto_check_awk.so

zip:
	cd .. ; zip -9ur awk $(AWK_FILES)
