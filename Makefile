# Dies ist ein minimales Makefile, um die konto_check Bibliothek unter Unix zu
# erstellen Es enthält nur einige Targets aus dem normalen Makefile, ist aber
# mehr eine quick&dirty Lösung.

BZIP2 = 0
LZO   = 0
LZMA  = 0

ifeq ($(BZIP2),1)
C_BZ2 = -DUSE_BZIP2=1
LD_BZ2 = -lbz2
else
C_BZ2 =
LD_BZ2 =
endif

ifeq ($(LZO),1)
C_LZO = -DUSE_LZO=1
else
C_LZO =
endif

ifeq ($(LZMA),1)
C_LZMA = -DUSE_LZMA=1
LD_LZMA = -llzma
else
C_LZMA =
LD_LZMA =
endif

DEBUG = -DDEBUG=1 -g
CFLAGS = -O3 -funroll-loops -Wall $(C_BZ2) $(C_LZO) $(C_LZMA)
LDFLAGS = -lz $(LD_BZ2) $(LD_LZMA)

BLZ_LEVEL   = -g37
BLZ_LEVELF  = -g39f
BLZ_FILE    = blz2_20130909.txt
BLZ_CMT     = Bankleitzahlentabelle gueltig vom  09.09.2013 bis 08.12.2013; IBAN blacklist vom 09.09.2013
GUELTIG     = 20130909-20131208
BLZ_FILE2   = blz2_20131209.txt
BLZ_CMT2    = Bankleitzahlentabelle gueltig vom 09.12.2013 bis 02.03.2014; IBAN blacklist vom 09.12.2013
GUELTIG2    = 20131209-20140302

LIB_MAJOR_VERSION = 3
LIB_MINOR_VERSION = 5
LIB_PATCHLEVEL    = 2
LIB_VERSION = $(LIB_MAJOR_VERSION).$(LIB_MINOR_VERSION).$(LIB_PATCHLEVEL)

all: konto_check konto_check_mini lut test

test: konto_check testkonten
	./konto_check testkonten.txt testkonten.out

testkonten:
	touch testkonten.txt

konto_check.o: konto_check.c
	$(CC) $(CFLAGS) -c konto_check.c -o konto_check.o

konto_check: konto_check.o main.c
	$(CC) $(CFLAGS) $(LDFLAGS) konto_check.o main.c -o konto_check

konto_check_mini: konto_check.o konto_check_mini.c
	$(CC) $(CFLAGS) $(LDFLAGS) konto_check.o konto_check_mini.c -o konto_check_mini

lut: lut2 lut2f

lut2: blz.lut2
blz.lut2: konto_check
	./konto_check $(BLZ_LEVEL) $(BLZ_FILE) -i "$(BLZ_CMT)" -N iban.blacklist -G$(GUELTIG) blz.lut2
	./konto_check $(BLZ_LEVEL) $(BLZ_FILE2) -i "$(BLZ_CMT2)" -G$(GUELTIG2) -2 blz.lut2

lut20: konto_check
	./konto_check -g39f $(BLZ_FILE) -i "$(BLZ_CMT)" -G$(GUELTIG) blz.lut2 -Z0
	@ echo "`ls -lh blz.lut2` (`head blz.lut2 | grep Kompression`)"
lut21: konto_check
	./konto_check -g39f $(BLZ_FILE) -i "$(BLZ_CMT)" -G$(GUELTIG) blz.lut2 -Z1
	@ echo "`ls -lh blz.lut2` (`head blz.lut2 | grep Kompression`)"
lut22: konto_check
	./konto_check -g39f $(BLZ_FILE) -i "$(BLZ_CMT)" -G$(GUELTIG) blz.lut2 -Z2
	@ echo "`ls -lh blz.lut2` (`head blz.lut2 | grep Kompression`)"
lut23: konto_check
	./konto_check -g39f $(BLZ_FILE) -i "$(BLZ_CMT)" -G$(GUELTIG) blz.lut2 -Z3
	@ echo "`ls -lh blz.lut2` (`head blz.lut2 | grep Kompression`)"
lut24: konto_check
	./konto_check -g39f $(BLZ_FILE) -i "$(BLZ_CMT)" -G$(GUELTIG) blz.lut2 -Z4
	@ echo "`ls -lh blz.lut2` (`head blz.lut2 | grep Kompression`)"

lut2f: blz.lut2f
blz.lut2f: konto_check
	./konto_check $(BLZ_LEVELF) $(BLZ_FILE) -i "$(BLZ_CMT)" -N iban.blacklist.2013-09 -G$(GUELTIG) blz.lut2f
	./konto_check $(BLZ_LEVELF) $(BLZ_FILE2) -i "$(BLZ_CMT2)" -N iban.blacklist.2013-12 -G$(GUELTIG2) -2 blz.lut2f

lut2x: blz.lut2fx
blz.lut2fx: konto_check
	./konto_check $(BLZ_LEVELF) $(BLZ_FILE).neu -i "$(BLZ_CMT)" -N iban.blacklist -G$(GUELTIG) blz.lut2f
	./konto_check $(BLZ_LEVELF) $(BLZ_FILE2).neu -i "$(BLZ_CMT2)" -G$(GUELTIG2) -2 blz.lut2f

lib: libkonto_check.so.$(LIB_VERSION)
libkonto_check.so.$(LIB_VERSION): konto_check.c konto_check.h
	gcc -fPIC -c $(CFLAGS) konto_check.c
	gcc -shared -Wl,-soname,libkonto_check.so.$(LIB_VERSION) -o libkonto_check.so.$(LIB_VERSION) konto_check.o -lc -s

install: lib #you must be root to do this
	cp libkonto_check.so.$(LIB_VERSION) /usr/local/lib
	ln -sf /usr/local/lib/libkonto_check.so.$(LIB_VERSION) /usr/local/lib/libkonto_check.so.$(LIB_MAJOR_VERSION)
	ln -sf /usr/local/lib/libkonto_check.so.$(LIB_MAJOR_VERSION) /usr/local/lib/libkonto_check.so
	ln -sf /usr/local/lib/libkonto_check.so.$(LIB_MAJOR_VERSION) /usr/lib/libkonto_check.so
	ldconfig

clean:
	- rm -f *.bck *.o *.obj testkonten.out konto_check konto_check_mini

distclean:
	- rm -f konto_check konto_check.exe konto_check_dll.exe konto_check.dll libkonto_check.so.* blz.lut blz.lut2 blz.lut2f

