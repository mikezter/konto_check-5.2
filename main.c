/*
 * ##########################################################################
 * #  Dies ist eine kleine main() Routine für die konto_check library.      #
 * #  zum Testen deutscher Bankkonten.                                      #
 * #                                                                        #
 * #  Versionen: siehe Datei 0_history.txt                                  #
 * #                                                                        #
 * #  Copyright (C) 2002-2013 Michael Plugge <m.plugge@hs-mannheim.de>      #
 * #                                                                        #
 * #  Dieses Programm ist freie Software; Sie dürfen es unter den           #
 * #  Bedingungen der GNU Lesser General Public License, wie von der Free   #
 * #  Software Foundation veröffentlicht, weiterverteilen und/oder          #
 * #  modifizieren; entweder gemäß Version 2.1 der Lizenz oder (nach Ihrer  #
 * #  Option) jeder späteren Version.                                       #
 * #                                                                        #
 * #  Die GNU LGPL ist weniger infektiös als die normale GPL; Code, der von #
 * #  Ihnen hinzugefügt wird, unterliegt nicht der Offenlegungspflicht      #
 * #  (wie bei der normalen GPL); außerdem müssen Programme, die diese      #
 * #  Bibliothek benutzen, nicht (L)GPL lizensiert sein, sondern können     #
 * #  beliebig kommerziell verwertet werden. Die Offenlegung des Source-    #
 * #  codes bezieht sich bei der LGPL *nur* auf geänderten Bibliothekscode. #
 * #                                                                        #
 * #  Dieses Programm wird in der Hoffnung weiterverbreitet, daß es         #
 * #  nützlich sein wird, jedoch OHNE IRGENDEINE GARANTIE, auch ohne die    #
 * #  implizierte Garantie der MARKTREIFE oder der VERWENDBARKEIT FÜR       #
 * #  EINEN BESTIMMTEN ZWECK. Mehr Details finden Sie in der GNU Lesser     #
 * #  General Public License.                                               #
 * #                                                                        #
 * #  Sie sollten eine Kopie der GNU Lesser General Public License          #
 * #  zusammen mit diesem Programm erhalten haben; falls nicht,             #
 * #  schreiben Sie an die Free Software Foundation, Inc., 59 Temple        #
 * #  Place, Suite 330, Boston, MA 02111-1307, USA. Sie können sie auch     #
 * #  von                                                                   #
 * #                                                                        #
 * #       http://www.gnu.org/licenses/lgpl.html                            #
 * #                                                                        #
 * #  im Internet herunterladen. 														 #
 * ##########################################################################
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include "konto_check.h"

#define OUTPUT_BUFSIZE 2097152

   /* FILTER_MODE==1: Rückgabewer als Zahl
    * FILTER_MODE==2: Rückgabewert als Text (kurz)
    */
#define FILTER_MODE 2

enum{CHECK,FAST,GEN_LUT,LUT_DIR,DUMP_LUT,REBUILD,COPY,EXTRACT,LUT_INFO};
extern UINT4 lc[256];

/*
 * ######################################################################
 * # Einige Makros für die innere Schleife (diese sind schneller        #
 * # als die entsprechenden Funktionen der Standard-Library).           #
 * ######################################################################
 */

#define ISDIGIT(x) ((x)>='0' && (x)<='9')
#define ISXDIGIT(x) (((x)>='0' && (x)<='9') || ((x)>='a' && (x)<='z') || ((x)>='A' && (x)<='Z'))

/*
 * ######################################################################
 * # GET_VAL: Makro für Argumente von CLI-Optionen                      #
 * ######################################################################
 */

#define GET_VAL if(!*++ptr && (++i>=argc || *(ptr=argv[i])=='-')){ \
      fprintf(stderr,"Die Option -%c benötigt ein Argument, aber es wurde keines angegeben; Abbruch\n",*(argv[--i]+1)); \
      exit(4); \
   }

#define FORMAT_ERROR do{fprintf(stderr,"Formatfehler im Gültigkeitszeitraum\n" \
      "   Sollformat: JJJJMMTT-JJJJMMTT\n" \
      "   Abbruch\n"); \
   return 1; \
} while(0)

/*
 * #######################################################################
 * # ZEIT(x): Zeitmessung mit hoher Auflösung. Die Funktion gettimeofday #
 * # ist nicht bei allen Compilern definiert; notfalls muß eine andere   #
 * # Funktion benutzt werden (bei MSVC++ z.B. Time() (???) o.ä.), oder   #
 * # das Makro als Dummy definiert werden.                               #
 * #######################################################################
 */

#define ZEIT(x) gettimeofday(&tv,NULL); x=tv.tv_sec+((double)tv.tv_usec)/1.e6

#if __WIN32
#define ftruncate(fd,len) chsize(fd,len) /* testen, ob es so stimmt!!! */
#include <windows.h>
#include <sys/timeb.h>

int gettimeofday(struct timeval *tv, void *tz)
{
   int retval;
   static long long frequency,cnt;
   static time_t ct;
   long sec;
   struct _timeb tb;
   LARGE_INTEGER qpc,qpf;

   if(!frequency){
      retval=QueryPerformanceFrequency(&qpf);
      if(!retval)
         frequency= -1;
      else{
         frequency=qpf.QuadPart;
         QueryPerformanceCounter(&qpc);
         ct=time(NULL)-qpc.QuadPart/frequency;  /* for Unix compatibility */
      }
   }
   if(frequency==-1){ /* use ftime; this yields only milliseconds resolution */
      _ftime(&tb);
      tv->tv_sec=tb.time;
      tv->tv_usec=tb.millitm*1000;
   }
   else{
      QueryPerformanceCounter(&qpc);
      cnt=qpc.QuadPart; tv->tv_sec=sec=cnt/frequency+ct; cnt=(cnt-sec*frequency)*1000000; tv->tv_usec=cnt/frequency;
   }
   return 0;
}
#endif

void print_help(void)
{
   fprintf(stderr,"%s","\n"
"   konto_check: kleines Programm zum Testen von Prüfziffern bei deutschen\n"
"   Kontonummern.\n"
"\n"
"   Aufruf:\n"
"\n"
"      konto_check [optionen] [eingabedatei [ausgabedatei [3. Parameter]]]\n"
"\n"
"   Mögliche Optionen sind:\n"
"      -c    copy: LUT-Datei kopieren (mit Angabe Slots)\n"
"      -d    dir: Infos zu einer LUT-Datei anzeigen\n"
"      -f    (fast) Schneller Modus (s. Doku/Source!!!)\n"
"      -g    LUT-Datei generieren (im aktuellen Format)\n"
"      -g1   LUT-Datei (Version 1.0) generieren\n"
"      -g2   LUT-Datei (Version 1.1) generieren\n"
"      -g3x  LUT-Datei (Version 2.0) generieren (mit Angabe Slots im 3. Parameter)\n"
"            Für x kann eine Zahl zwischen 1 und 7 oder x stehen (s.u.)\n"
"      -Gd1-d2 Gültigkeitsbereich der BLZ-Datei angeben (nur zusammen mit -g3).\n"
"            Der Gültigkeitsbereich ist in der Form JJJJMMTT-JJJJMMTT anzugeben,\n"
"            z.B. -G20091207-20100307. Er wird für jeden Datensatz einzeln\n"
"            gespeichert und bei der Initialisierung getestet.\n"
"      -h    (diese) Hilfe anzeigen\n"
"      -i    Infozeile für die LUT-Datei (nur zusammen mit -g)\n"
"      -I    Infoblock(s) der LUT-Datei ausgeben (nicht für LUT 1.0/1.1)\n"
"      -l    Name der LUT-Datei angeben\n"
"      -n    Bankname und Ort ausgeben\n"
"      -Nname Verbotsliste für IBAN-Berechnung\n"
"      -r    BLZ-Datei neu generieren (als Härtetest für die LUT2-Routinen)\n"
"            Falls der 3. Parameter angegeben ist, wird als Eingabe eine LUT-Datei\n"
"            erwartet; der Parameter gibt das zu benutzende Set (1 oder 2) an.\n"
"      -s    Separator: Trennzeichen für das Testergebnis\n"
"      -v    verbose: diverse Meldungen ausgeben\n"
"      -vx level verbose debug einschalten\n"
"      -V    Versionsinfo von Library und LUT-Datei\n"
"      -x    Block mit Typ von Parameter 3 in die Ausgabedatei extrahieren\n"
"      -X[1-9] [12] Klartext-Dump der LUT-Datei. Der 3. Parameter (optional)\n"
"            gibt das auszugebende Set (1 oder 2) der LUT-Datei an.\n"
"            Ausgabefelder s.u.\n"
"      -zgzweck Prüfziffer für strukturieren IPI-Verwendungszweck erzeugen\n"
"      -ztzweck Prüfziffer für strukturieren IPI-Verwendungszweck testen\n"
"      -Z[012]  Kompressionsbibliothek für die LUT-Datei angeben (bei -g)\n"
"\n"
"\n"
"   Optionen und Dateinamen können beliebig gemischt werden.\n"
"\n"
"   Format der Eingabedatei: in jeder Zeile steht zuerst die Bankleitzahl,\n"
"   dann das zu testende Konto. Als Trennzeichen kann ein beliebiges nicht-\n"
"   alphanumerisches Zeichen auftreten. Nach der Kontonummer können noch\n"
"   weitere Daten kommen, die in die Ausgabedatei übernommen werden, jedoch\n"
"   ansonsten nicht weiter beachtet werden.\n"
"\n"
"   Alle Zeilen, in denen nicht eine Bankleitzahl und ein Konto gefunden\n"
"   wird, werden unverändert in die Ausgabedatei übernommen. Die Ausgabe-\n"
"   datei enthält die ursprüngliche Zeilen sowie (durch : oder den mit -s\n"
"   spezifizierten Separator) das Testergebnis im Klartext.\n"
"\n"
"   Mit dem Aufruf\n"
"\n"
"       konto_check -g blz.txt blz.lut -i \"Zeile mit User-Infozeile\"\n"
"\n"
"   wird die LUT-Datei blz.lut aus blz.txt generiert. Als Eingabedatei ist der\n"
"   Name der BLZ-Datei der deutschen Bundesbank (z.B. blz0203pc.txt) anzugeben,\n"
"   als Ausgabedatei der Name der zu generierenden LUT-Datei (defaultmäßig\n"
"   blz.lut). Die (User-)Infozeile muß in doppelte Hochkommas eingeschlossen\n"
"   werden, damit sie als einzelnes Kommandozeilen-Argument erscheint.\n"
"      \n"
"   Für die Option -g3 kann man angeben, welche Blocks in der erzeugten\n"
"   LUT-Datei enthalten sein sollen. Es gibt eine Reihe vordefinierter\n"
"   Varianten, sowie die Möglichkeit, beliebige LUT-Dateien aufzubauen.\n"
"   Als zusätzlicher Parameter kann beim LUT2 Dateiformat auch noch die\n"
"   Anzahl der anzulegenden Slots (3. Parameter, nach dem Ausgabenamen) \n"
"   sowie ein Gültigkeitsbereich (mittels -G) angegeben werde. Falls die\n"
"   Filialen eingebunden werden sollen, ist nach dem -g3 noch ein f anzugeben:\n"
"   -g3f7 oder -g37f. Alle vorgegebenen Varianten enthalten ID, BLZ und PZ.\n"
"\n"
"      -g30: (nur ID,BLZ,PZ)\n"
"      -g31: NAME_KURZ\n"
"      -g32: NAME_KURZ,BIC\n"
"      -g33: NAME,PLZ,ORT\n"
"      -g34: NAME,PLZ,ORT,BIC\n"
"      -g35: NAME_NAME_KURZ,PLZ,ORT,BIC\n"
"      -g36: NAME_NAME_KURZ,PLZ,ORT,BIC,NACHFOLGE_BLZ\n"
"      -g37: NAME_NAME_KURZ,PLZ,ORT,BIC,NACHFOLGE_BLZ,AENDERUNG\n"
"      -g38: NAME_NAME_KURZ,PLZ,ORT,BIC,NACHFOLGE_BLZ,AENDERUNG,LOESCHUNG\n"
"      -g39: NAME_NAME_KURZ,PLZ,ORT,BIC,NACHFOLGE_BLZ,AENDERUNG,LOESCHUNG,PAN,NR\n"
"      -gx:  wie -g3x\n"
"      -g3x: Es können die einzubindenden Blocks direkt angegeben werden (numerisch);\n"
"            -g33 entspricht z.B. -gx1,3,4,5,9\n"
"            Die einzelnen Blocks müssen durch Komma getrennt (ohne Leerzeichen)\n"
"            aufgeführt werden.\n"
"            \n"
"   Für die Option -X (Dump einer LUT-Datei) gibt es ebenfalls eine Reihe\n"
"   vordefinierter Varianten:\n"
"\n"
"      -X0: BLZ,PZ\n"
"      -X1: BLZ,PZ,NAME_KURZ\n"
"      -X2: BLZ,PZ,NAME_KURZ,BIC\n"
"      -X3: BLZ,PZ,NAME,PLZ,ORT\n"
"      -X4: BLZ,PZ,NAME,PLZ,ORT,BIC\n"
"      -X5: BLZ,PZ,NAME,NAME_KURZ,PLZ,ORT,BIC\n"
"      -X6: BLZ,PZ,NAME,NAME_KURZ,PLZ,ORT,BIC,NACHFOLGE_BLZ\n"
"      -X7: BLZ,PZ,NAME,NAME_KURZ,PLZ,ORT,BIC,NACHFOLGE_BLZ,AENDERUNG\n"
"      -X8: BLZ,PZ,NAME,NAME_KURZ,PLZ,ORT,BIC,NACHFOLGE_BLZ,AENDERUNG,LOESCHUNG\n"
"      -X9: BLZ,PZ,NAME,NAME_KURZ,PLZ,ORT,BIC,NACHFOLGE_BLZ,AENDERUNG,LOESCHUNG,PAN,NR\n"
"                \n"
"   Der zu ladende Satz kann (optional) als 3. Parameter übergeben werden:\n"
"   mit \n"
"\n"
"      ./konto_check -X3 blz.lut blz.out 2\n"
"\n"
"   wird ein Klartext-Dump des sekundären Satzes der Datei blz.lut gemacht."
#if FILTER_MODE
"\n"
"\n"
"   Falls der Eingabename weggelassen wird, arbeitet das Programm im\n"
"   Filtermodus; es wird von der Standardeingabe gelesen, die Ausgabe\n"
"   geht auf die Standardausgabe. Für die Eingabe wird Prüfmethode oder\n"
"   BLZ, dann Trennzeichen, danach das Konto erwartet; bei der Ausgabe\n"
"   wird die Prüfmethode oder BLZ, dann das Konto und danach der numerische\n"
"   Rückgabewert ausgegeben."
#endif
"\n"
"\n"
"   Copyright (C) 2002-2013 Michael Plugge <m.plugge@hs-mannheim.de>\n\n");
}

int main(int argc,char **argv)
{
   char *ptr,*ptr1,*ptr2,*opt_ptr,*inputname,*outputname,*lutname,*extra_opt,*gueltigkeit,*trennzeile,bptr[16],kptr[16];
   char  **p_name,**p_name_kurz,**p_ort,**p_bic,*p_aenderung,*p_loeschung,*name,*ort,*keine_iban_berechnung;
   int *p_blz,*p_nachfolge_blz,p_pz,*p_nr,*p_plz,*p_pan,id,id1,id2,cnt_all,*start_idx;
   char *buffer,*dbuffer,*sptr,*dptr,*eptr,*user_info,*cmd_help,blz_buffer[12],ipi_buffer[24],ipi_papier[32];
   const char *ptrc;
	int i,j,ret,cnt,verbose,zeilen,konten,out_cnt,separator,lf_error,action,incremental,*iptr,felder;
   UINT4 gen_lut,set,blocks[256];
   double t1,t2,lesen1,lesen2,schreiben,schreiben1,schreiben2;
   int in,out;
   struct stat s_buf;
   struct timeval tv;
   FILE *out_f;
   RETVAL retvals;
   int plz,filialen,ret1,zeige_namen;
   time_t t;
   struct tm *timeptr,timebuf;

#if WIN32 && 0
   cmd_help="in diesem Modus können auch Befehle (als Simulation realer Änderungen)\n"
"eingegeben werden. Momentan unterstützte Befehle (die Auswahl kann sich\n"
"ändern, sie fangen allerdings alle mit - an):\n"
"\n"
"   -bBLZ          Infos zu der Bank anzeigen\n"
"   -biidx [zw]    Infos zu der Bank mit Index idx anzeigen (Index zählt ab 1)\n"
"                  optional kann noch eine Zweigstelle angegeben werden\n"
"                  (Zahl, ab 1). Die Zweigstellen sind in der LUT-Datei\n"
"                  u.U. nach Postleitzahlen sortiert (abhängig von dem\n"
"                  Compiler-Schalter SORT_PLZ in konto_check.h) und stimmen\n"
"                  dann **nicht** mit denen der Bundesbankdatei überein.\n"
"   -Biban         IBAN -> BIC für deutsche IBANs\n"
"   -ciban         IBAN validieren\n"
"   -Cblz kto      IBAN zu BLZ und kto generieren (vorher Konto testen)\n"
"   -d             'Systemdatum' für LUT-Datei (simuliert) löschen\n"
"   -ddatum        'Systemdatum' für LUT-Datei (simuliert) setzen (Format: JJJJMMTT)\n"
"   -D             Systemdatum für LUT-Datei (simuliert und echt) anzeigen\n"
"   -E[dihsu]      Ausgabe-Kodierung festlegen\n"
"   -i[1-7]dateiname [set]  Bibliothek mit der angegebenen Datei initialisieren\n"
"                  Die Zahl gibt die zu ladenden Blocks an (wie bei -g3)\n"
"                  Der Parameter set kann weggelassen werden; dann wird das\n"
"                  aktuell gültige Set (bzw. das primäre Set, falls keines gültig ist)\n"
"                  geladen; falls er angegeben ist, sollte er 1 (für das primäre Set)\n"
"                  oder 2 (für das sekundäre Set) sein.\n"
"   -Idateiname    Infoblocks der angegebenen LUT-Datei anzeigen\n"
"   -I             Infoblock der geladenen LUT-Datei anzeigen\n"
"   -ldateiname    Verzeichnis der angegebenen LUT-Datei anzeigen\n"
"   -sname         Namens(anfang) suchen -> BLZ\n"
"   -Sort          Ort suchen -> BLZ\n"
"   -v             geladenen Datensatz auf Gültigkeit testen\n"
"   -zgzweck       Prüfziffer für strukturieren IPI-Verwendungszweck erzeugen\n"
"   -ztzweck       Prüfziffer für strukturieren IPI-Verwendungszweck testen\n"
"   -Zkompression  Kompressionsbibliothek (0 keine, 1 zlib, 2 bzlib2)\n"
"   -h             (diese) Hilfe anzeigen\n"
"   -?             dto.";
#else
   cmd_help="in diesem Modus können auch Befehle (als Simulation realer Änderungen)\n"
"eingegeben werden. Momentan unterstützte Befehle (die Auswahl kann sich\n"
"ändern, sie fangen allerdings alle mit - an):\n"
"\n"
"   -bBLZ          Infos zu der Bank anzeigen\n"
"   -biidx [zw]    Infos zu der Bank mit Index idx anzeigen (Index zählt ab 1)\n"
"                  optional kann noch eine Zweigstelle angegeben werden\n"
"                  (Zahl, ab 1). Die Zweigstellen sind in der LUT-Datei\n"
"                  u.U. nach Postleitzahlen sortiert (abhängig von dem\n"
"                  Compiler-Schalter SORT_PLZ in konto_check.h) und stimmen\n"
"                  dann **nicht** mit denen der Bundesbankdatei überein.\n"
"   -Biban         IBAN -> BIC für deutsche IBANs\n"
"   -ciban         IBAN validieren\n"
"   -Cblz kto      IBAN zu BLZ und kto generieren (vorher Konto testen)\n"
"   -d             'Systemdatum' für LUT-Datei (simuliert) löschen\n"
"   -ddatum        'Systemdatum' für LUT-Datei (simuliert) setzen (Format: JJJJMMTT)\n"
"   -D             Systemdatum für LUT-Datei (simuliert und echt) anzeigen\n"
"   -E[dihsu]      Ausgabe-Kodierung festlegen\n"
"   -i[1-7]dateiname [set]  Bibliothek mit der angegebenen Datei initialisieren\n"
"                  Die Zahl gibt die zu ladenden Blocks an (wie bei -g3)\n"
"                  Der Parameter set kann weggelassen werden; dann wird das\n"
"                  aktuell gültige Set (bzw. das primäre Set, falls keines gültig ist)\n"
"                  geladen; falls er angegeben ist, sollte er 1 (für das primäre Set)\n"
"                  oder 2 (für das sekundäre Set) sein.\n"
"   -Idateiname    Infoblocks der angegebenen LUT-Datei anzeigen\n"
"   -I             Infoblock der geladenen LUT-Datei anzeigen\n"
"   -ldateiname    Verzeichnis der angegebenen LUT-Datei anzeigen\n"
"   -sname         Namens(anfang) suchen -> BLZ\n"
"   -Sort          Ort suchen -> BLZ\n"
"   -v             geladenen Datensatz auf Gültigkeit testen\n"
"   -zgzweck       Prüfziffer für strukturieren IPI-Verwendungszweck erzeugen\n"
"   -ztzweck       Prüfziffer für strukturieren IPI-Verwendungszweck testen\n"
"   -Zkompression  Kompressionsbibliothek (0 keine, 1 zlib, 2 bzlib2)\n"
"   -h             (diese) Hilfe anzeigen\n"
"   -?             dto.";
#endif
   ZEIT(t1);
   buffer=dbuffer=NULL;
   separator=':';
   gueltigkeit=NULL;
   keine_iban_berechnung=NULL;
   trennzeile="----------------------------------------------------------------\n";
   set=zeige_namen=verbose=gen_lut=lf_error=0;
   schreiben=0.;
   action=CHECK;
   inputname=outputname=lutname=user_info=extra_opt=NULL;
   iptr=NULL;
   for(i=1;i<argc;i++){
      if(*argv[i]=='-')
         switch(*(ptr=argv[i]+1)){
            case '1':
            case '2':
               set=atoi(ptr);
               break;
            case 'c':
               action=COPY;
               break;
            case 'd':
               action=LUT_DIR;
               break;
            case 'E':
               kto_check_encoding(*(ptr+1));
               break;
            case 'e':
               verbose|=2;
               break;
            case 'f':
               action=FAST;
               break;
            case 'g':
               action=GEN_LUT;
               if(*++ptr=='x'){
                  gen_lut=3;
                  felder='x';
                  opt_ptr=ptr+1;
               }
               else if(*ptr>='1' && *ptr<='3'){
                  gen_lut= *ptr-'0';
                  if(gen_lut==3 && *++ptr){
                     if(*ptr=='f'){
                        filialen=1;
                        ptr++;
                     }
                     else
                        filialen=0;
                     felder=*ptr-'0';
                     if(*(ptr+1)=='f'){
                        filialen=1;
                        ptr++;
                     }
                  }
                  else
                     felder=0;
               }
               else{
                  gen_lut=3;
                  felder=3;
                  filialen=0;
                  ptr--;
               }
               break;

            case 'G':
               GET_VAL;
               for(j=0,ptr1=ptr;*ptr1 && j++<8;)if(!isdigit(*ptr1++))FORMAT_ERROR;
               if(*ptr1++!='-')FORMAT_ERROR;
               for(j=0;*ptr1 && j++<8;)if(!isdigit(*ptr1++))FORMAT_ERROR;
               gueltigkeit=ptr;
               break;

            case '?':
            case 'h':
               print_help();
               exit(0);
            case 'i':
               GET_VAL;
               user_info=ptr;
               break;
            case 'I':
               action=LUT_INFO;
               break;
            case 'l':
               GET_VAL;
               if(*ptr=='u' && *(ptr+1)=='t' && *(ptr+2)==0){
                  gen_lut=2;  /* Option -lut für Kompatibilität mit altem Programm */
                  action=GEN_LUT;
               }
               else
                  lutname=ptr;
               break;
            case 'n':
               zeige_namen=1;
               break;
            case 'N':
               GET_VAL;
               keine_iban_berechnung=ptr;
               break;
            case 'r':
               action=REBUILD;
               break;
            case 's':
               GET_VAL;
               if(*ptr)separator= *ptr;
               break;
            case 'v':
               if(*(ptr+1)=='x'){
                  ptr++;
                  GET_VAL;
#if VERBOSE_DEBUG>0
                  if(*ptr)set_verbose_debug(atoi(ptr));
#else
                  fprintf(stderr,"Die Option verbose_debug wurde nicht einkompiliert\n");
#endif
               }
               else
                  verbose|=1;
               break;
				case 'V':
               if((ret=get_lut_info(&ptr,lutname))!=OK){
                  fprintf(stderr,"%s\n",kto_check_retval2txt(ret));
                  return 1;
               }
               if(ptr){
                  fprintf(stderr,"%s\nInfozeile von %s: %s\n",
                     get_kto_check_version(),lutname,ptr);
                  free(ptr);
               }
               else
                  fprintf(stderr,"%s\n%s: aus Version 1.0 (ohne Infozeile)\n",
                     get_kto_check_version(),lutname);
               return(0);
            case 'x':
               action=EXTRACT;
               break;
            case 'X':
               GET_VAL;
               action=DUMP_LUT;
               if(*ptr>='0' && *ptr<='9')
                  felder=*ptr-'0';
               else
                  felder=3;
               break;
            case 'Z':
               GET_VAL;
               switch(*ptr){
                  case '0': set_default_compression(COMPRESSION_NONE); break;
                  case '1': set_default_compression(COMPRESSION_ZLIB); break;
                  case '2': set_default_compression(COMPRESSION_BZIP2); break;
                  case '3': set_default_compression(COMPRESSION_LZO); break;
                  case '4': set_default_compression(COMPRESSION_LZMA); break;
                  default: break;
               }

            default: break;
         }
      else if(!inputname)
         inputname=argv[i];
      else if(!outputname)
         outputname=argv[i];
      else if(!extra_opt)
         extra_opt=argv[i];

   }
#if !FILTER_MODE
   if(!inputname){
      print_help();
      exit(0);
   }
#endif
   if(action==LUT_INFO){
      lut_info(inputname,&ptr,&ptr1,&i,&j);
      fprintf(stderr,"%sPrimärer Datensatz:   %s\nSekundärer Datensatz: %s\n%s",
            trennzeile,kto_check_retval2txt(i),kto_check_retval2txt(j),trennzeile);
      if(ptr){
         fprintf(stderr,"%s%s",ptr,trennzeile);
         free(ptr);
      }
      if(ptr1){
         fprintf(stderr,"%s%s",ptr1,trennzeile);
         free(ptr1);
      }
      return 0;
   }
   if(action==EXTRACT){
      if(extra_opt)
         i=atoi(extra_opt);
      else
         i=0;
      if(!i){
         fprintf(stderr,"Option -x ohne Typ (letztes Argument); Abbruch\n");
         return 1;
      }
      if(!outputname)
         out_f=stdout;
      else if(!(out_f=fopen(outputname,"wb"))){
         fprintf(stderr,"%s\n",kto_check_retval2txt(FILE_WRITE_ERROR));
         return 1;
      }
      if((ret=read_lut_block(inputname,i,(UINT4*)&cnt,&ptr))!=OK){
         fprintf(stderr,"%s\n",kto_check_retval2txt(ret));
         if(out_f!=stdout)fclose(out_f);
         return 1;
      }
      fwrite(ptr,cnt,1,out_f);
      free(ptr);  /* Block-Speicher wieder freigeben */
      if(out_f!=stdout)fclose(out_f);
      return 0;
   }
   if(action==COPY){
      if(extra_opt)
         cnt=atoi(extra_opt);
      else
         cnt=0;
      ret=copy_lutfile(inputname,outputname,cnt);
      if(ret!=OK)fprintf(stderr,"copy_lut: %s\n",kto_check_retval2txt(ret));
      return 0;
   }
   if(action==REBUILD){
      if(extra_opt)
         i=atoi(extra_opt);
      else
         i=0;
      if((ret=rebuild_blzfile(inputname,outputname,i))!=OK)
         fprintf(stderr,"rebuild_blzfile: %s\n",kto_check_retval2txt(ret));
      return 0;
   }
   if(action==LUT_DIR){
      ret=lut_dir_dump(inputname,outputname);
      if(ret!=OK)fprintf(stderr,"%s\n",kto_check_retval2txt(ret));
      return 0;
   }
   if(action==DUMP_LUT){
      if(extra_opt)
         set=atoi(extra_opt);
      else
         set=0;
      if(set<0 || set>2)set=0;
      if((ret=kto_check_init_p(inputname,9,set,0))!=OK && ret!=LUT2_PARTIAL_OK && ret!=LUT1_SET_LOADED){
         fprintf(stderr,"%s\n",kto_check_retval2txt(ret));
         return 1;
      }
      ret=dump_lutfile_p(outputname,felder);
      if(ret!=OK)fprintf(stderr,"%s\n",kto_check_retval2txt(ret));
      lut_cleanup();
      return 0;
   }

   if(action==GEN_LUT){
      if(!outputname)outputname="blz.lut";
      fprintf(stderr,"Generiere die Lookup-Datei %s aus %s\n",outputname,inputname);
      if(gen_lut<3)  /* alte Routine für LUT 1.0/1.1 aufrufen */
         ret=generate_lut(inputname,outputname,user_info,gen_lut);
      else if(felder=='x'){
         for(i=0,ptr=opt_ptr;i<255 && *ptr;i++){
            blocks[i]=atoi(ptr);
            while(*ptr && *ptr!=',')ptr++;
            if(*ptr==',')ptr++;
         }
         blocks[i]=0;
         if(extra_opt)
            cnt=atoi(extra_opt);
         else
            cnt=i*2+3;
         ret=generate_lut2(inputname,outputname,user_info,gueltigkeit,blocks,cnt,3,set);
      }
      else{
         if(extra_opt)
            cnt=atoi(extra_opt);
         else
            cnt=0;
         ret=generate_lut2_p(inputname,outputname,user_info,gueltigkeit,felder,filialen,cnt,3,set);
      }
      if(ret<0){
         fprintf(stderr,"Fehler beim Generieren der LUT-Datei: \n   %s\n",
            kto_check_retval2txt(ret));
         return 4;
      }
      else{
         if(keine_iban_berechnung)lut_keine_iban_berechnung(keine_iban_berechnung,outputname,set);
         return 0;
      }
   }

   if((ret=kto_check_init_p(lutname,9,0,0))!=OK && ret!=LUT2_PARTIAL_OK && ret!=LUT1_SET_LOADED){
      printf("Initialisierung: %s / %s\n",kto_check_retval2txt_short(ret),kto_check_retval2txt(ret));
      return 1;
   }
#if FILTER_MODE
   if(!inputname && !outputname){   /* Filterbetrieb */
      buffer=malloc(1024);
      while(!feof(stdin)){
         *buffer=0;
         fgets(buffer,1024,stdin);
         if(*buffer){
#if DEBUG
            if(*buffer=='-'){ /* Kommandomodus */
               for(ptr=buffer;*ptr && *ptr!='\r' && *ptr!='\n';ptr++);
               *ptr=0;  /* \r bzw. \n am Zeilenende entfernen (stört i.A.) */

               switch(*(buffer+1)){   /* Kommando ausführen */

                  case 'b':   /* Bankinfos anzeigen (holen über lut_multiple()) */
                     if(*(buffer+2)=='i'){   /* Dateien per Index holen */
                        id=strtoul(buffer+3,NULL,10)-1;  /* Index beginnt mit 1 */
                        if(id<0)id=0;
                        for(ptr=buffer+3;!isdigit(*ptr);ptr++);   /* Leerzeichen etc. vor Index überspringen */
                        while(isdigit(*ptr))ptr++; /* erste Zahl überspringen (Index der Bank) */
                        if(*ptr){                  /* zweite Zahl -> Index der Zweigstelle */
                           while(!isdigit(*ptr))ptr++;
                           id2=strtoul(ptr,NULL,10);
                        }
                        else
                           id2=0;
                        ret=lut_multiple(NULL,&cnt,&p_blz,&p_name,&p_name_kurz,&p_plz,&p_ort,&p_pan,&p_bic,
                              &p_pz,&p_nr,&p_aenderung,&p_loeschung,&p_nachfolge_blz,NULL,&cnt_all,&start_idx);
                        if(ret!=OK && ret!=LUT2_PARTIAL_OK){
                           printf("%s\n",kto_check_retval2txt(ret));
                           continue;
                        }
                        if(id>cnt)id=cnt-1;
                        if(id==cnt-1){
                           if(start_idx[id]+id2>=cnt_all)
                              id1=cnt_all-1;
                           else
                              id1=start_idx[id]+id2;
                        }
                        else if(start_idx[id]+id2>start_idx[id+1])
                           id1=start_idx[id+1]-1;
                        else
                           id1=start_idx[id]+id2;
                        id2=id1-start_idx[id];
                        printf("Infos zu Index %d/%d (BLZ %d",id+1,id1+1,p_blz[id]);
                        if(id2)printf(",  %d. Zweigstelle",id2);
                        printf("):\n");

                           /* zunächst testen, ob die Arrays inititalisiert sind
                            * (bzw. in der LUT-Datei enthalten waren). Für
                            * numerische Arrays ist im Fehlerfall -1 als erstes
                            * Element enthalten, für char- und Stringarrays ein '~'.
                            * Der Test ist beim Zugriff über Indizes notwendig,
                            * da die Fehler-Arrays nur 256 Elemente enthalten
                            * - genug für alle üblichen Zweigstellen, aber nicht
                            * genügend für den Offset vom Start des Arrays.
                            */
                        if(**p_name!='~')p_name+=id1;
                        if(**p_name_kurz!='~')p_name_kurz+=id1;
                        if(*p_plz>=0)p_plz+=id1;
                        if(**p_ort!='~')p_ort+=id1;
                        if(*p_pan>=0)p_pan+=id1;
                        if(**p_bic!='~')p_bic+=id1;
                            /* die Prüfziffer muß direkt bestimmt werden, geht
                             * bei lut_multiple() mit Index nicht (nur bei BLZ).
                             */
                        sprintf(blz_buffer,"%d",p_blz[id]);
                        p_pz=lut_pz(blz_buffer,0,NULL);
                        if(*p_nr>=0)p_nr+=id1;
                        if(*p_aenderung!='~')p_aenderung+=id1;
                        if(*p_loeschung!='~')p_loeschung+=id1;
                        if(*p_nachfolge_blz>=0)p_nachfolge_blz+=id1;
                     }
                     else{
                        ret=lut_multiple(buffer+2,&cnt,NULL,&p_name,&p_name_kurz,&p_plz,&p_ort,&p_pan,&p_bic,
                              &p_pz,&p_nr,&p_aenderung,&p_loeschung,&p_nachfolge_blz,&id,&cnt_all,&start_idx);
                        if(ret!=OK && ret!=LUT2_PARTIAL_OK){
                           printf("%s\n",kto_check_retval2txt(ret));
                           continue;
                        }
                        printf("Infos zu BLZ %s (%d Zweigstellen, Index %d):\n",buffer+2,cnt-1,id+1);
                     }
                     printf("Name/Ort: %s, %d %s\n",*p_name,*p_plz,*p_ort);
                     printf("Kurzbezeichnung: %s\n",*p_name_kurz);
                     printf("PAN: %d, BIC: %s, Prüfzifferverf.: %c%d\n",
                           *p_pan,*p_bic,p_pz>100?p_pz/10-10+'A':p_pz/10+'0',p_pz%10);
                     printf("Lfd.Nr.: %d, Änderung: %c, Löschung: %c, Nachfolge-BLZ: %d\n",
                           *p_nr,*p_aenderung,*p_loeschung,*p_nachfolge_blz);
                     break;

                  case 'B':   /* IBAN -> BIC */
                     for(ptr1=buffer+2;isspace(*ptr1);ptr1++);
                     ptrc=iban2bic(ptr1,&ret,bptr,kptr);
                     fprintf(stderr,"iban2bic: BIC: %s (BLZ: %s, Kto: %s, return: %d/%s)\n",
                           ptrc,bptr,kptr,ret,kto_check_retval2txt(ret));
                     break;

                  case 'c':   /* IBAN validieren */
                     ret=iban_check(buffer+2,&i);
                     fprintf(stderr,"iban_check: %s (kc: %s)\n",kto_check_retval2txt(ret),kto_check_retval2txt(i));
                     break;

                  case 'C':   /* IBAN generieren */
                     for(ptr1=buffer+2;*ptr1 && !isspace(*ptr1);ptr1++);
                     if(isspace(*ptr1)){
                        *ptr1++=0;
                        fprintf(stderr,"iban von %s %s\n",buffer+2,ptr1);
                        ptr1=iban_gen(buffer+2,ptr1,&ret);
                        fprintf(stderr,"iban_gen: %s (%s)\n",ptr1,kto_check_retval2txt(ret));
                     }
                     break;

                  case 'd':   /* "Systemdatum" (Fake) setzen */
                     current_date=strtoul(buffer+2,NULL,10);
                     break;

                  case 'D':   /* Ausgabe des aktuellen Systemdatums */
                     t=time(NULL);
                     timeptr=localtime_r(&t,&timebuf);
                     fprintf(stderr,"aktuelles Systemdatum:               %u\n",
                           (timeptr->tm_year+1900)*10000+(timeptr->tm_mon+1)*100+timeptr->tm_mday);
                     fprintf(stderr,"aktuelles modifiziertes Systemdatum: %08u\n",current_date);
                     break;

                  case 'f':   /* Speicher aufräumen */
                     lut_cleanup();
                     break;

                  case 'i':   /* neu initialisieren */
                     if(*(buffer+2)=='i' || *(buffer+3)=='i')
                        incremental=1;
                     else
                        incremental=0;
                     if(*(buffer+2)=='f' || *(buffer+3)=='f')
                        filialen=1;
                     else
                        filialen=0;
                     if(*(buffer+2+incremental+filialen)>='0' && *(buffer+2+incremental+filialen)<='9')
                        for(lutname=buffer+3+incremental+filialen;isspace(*lutname);lutname++);
                     else
                        for(lutname=buffer+2+incremental+filialen;isspace(*lutname);lutname++);
                     for(ptr=lutname;*ptr && !isspace(*ptr);ptr++);
                     if(isspace(*ptr)){
                        *ptr++=0;
                        set=atoi(ptr);
                     }
                     else
                        set=0;
                     for(ptr=lutname;*ptr && *ptr!='\r' && *ptr!='\n';ptr++);
                     *ptr=0;
                     ret=kto_check_init_p(lutname,*(buffer+2+incremental)-'0',set,incremental);
                     printf("init: %s\n",kto_check_retval2txt(ret));
                     printf("geladen: ");
                     iptr=lut2_status();
                     for(i=0;i<100;i++)if(iptr[i])printf("(%d: %d), ",i,iptr[i]);
                     printf("\n");
                     break;

                  case 'I':   /* Info zu Datei oder geladenem Datensatz anzeigen */
                     ret=lut_info(buffer+2,&ptr,&ptr1,&i,&j);
                     if(*(buffer+2))   /* es wurde ein Dateiname angegeben */
                        printf("%sPrimärer Datensatz:   %s\nSekundärer Datensatz: %s\n%s",
                              trennzeile,kto_check_retval2txt(i),kto_check_retval2txt(j),trennzeile);
                     else  /* kein Dateiname, Info über aktuell geladene Daten */
                        printf("%sgeladener Datensatz: %s\n%s",
                              trennzeile,kto_check_retval2txt(i),trennzeile);
                     if(ret==OK){
                        if(ptr){
                           printf("%s%s",ptr,trennzeile);
                           free(ptr);
                        }
                        if(ptr1){
                           printf("%s%s",ptr1,trennzeile);
                           free(ptr1);
                        }
                     }
                     break;

                  case 'l':   /* Inhaltsverzeichnis einer LUT-Datei anzeigen */
                     for(ptr=buffer+2;isspace(*ptr);ptr++);
                     lut_dir_dump(ptr,NULL);
                     break;

                  case 's':   /* Suche von BLZs */
                     {
                        char **base_name,**name,**ort,**bic,*suchfeld;
                        int a1,a2,f,anzahl,*start_idx,*blz_f,*plz,*zweigstelle,*base_name_i,typ;

                        for(ptr=buffer+3;isspace(*ptr);ptr++);
                        typ=0;   /* Ergebnis ist ein String */
                        switch(*(buffer+2)){
                           case 'P':
                              suchfeld="Postleitzahl";
                              typ=2;   /* Ergebnis ist ein Integer; BLZs mit Filialen */
                              a1=atoi(ptr);
                              while(*ptr && isdigit(*ptr++));
                              if(*ptr)
                                 a2=atoi(ptr);
                              else
                                 a2=a1;
                              ret=lut_suche_plz(a1,a2,&anzahl,&start_idx,&zweigstelle,&base_name_i,&blz_f);
                              break;
                           case 'p':
                              typ=1;   /* Ergebnis ist ein Integer, nur Basis-BLZs (ohne Filialen) */
                              suchfeld="Prüfziffermethode";
                              a1=atoi(ptr);
                              while(*ptr && isdigit(*ptr++));
                              if(*ptr)
                                 a2=atoi(ptr);
                              else
                                 a2=a1;
                              fprintf(stderr,"BLZ-Suche von %d bis %d\n",a1,a2);
                              ret=lut_suche_pz(a1,a2,&anzahl,&start_idx,&zweigstelle,&base_name_i,&blz_f);
                              break;
                           case 'b':   /* Suche nach Bankleitzahlen */
                              suchfeld="Bankleitzahl";
                              typ=1;   /* Ergebnis ist ein Integer, nur Basis-BLZs (ohne Filialen) */
                              a1=atoi(ptr);
                              while(*ptr && isdigit(*ptr++));
                              if(*ptr)
                                 a2=atoi(ptr);
                              else
                                 a2=a1;
                              fprintf(stderr,"BLZ-Suche von %d bis %d\n",a1,a2);
                              ret=lut_suche_blz(a1,a2,&anzahl,&start_idx,&zweigstelle,&base_name_i,&blz_f);
                              break;
                           case 'B':
                              suchfeld="BIC";
                              ret=lut_suche_bic(ptr,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_f);
                              break;
                           case 'n':
                              suchfeld="Name";
                              ret=lut_suche_namen(ptr,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_f);
                              break;
                           case 'N':
                              suchfeld="Kurzname";
                              ret=lut_suche_namen_kurz(ptr,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_f);
                              break;
                           case 'o':
                              suchfeld="Ort";
                              ret=lut_suche_ort(ptr,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_f);
                              break;
                           default:
                              suchfeld="Name (Default)";
                              ptr--;
                              ret=lut_suche_namen(ptr,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_f);
                              break;

                        }
                           /* Mittels lut_multiple() werden zunächst die Anfangsadressen der Arrays der
                            * LUT-Datei bestimmt (mit der Kontonummer NULL), um dann auch auf die Daten
                            * der Filialen zugreifen zu können.
                            */
                        if(ret!=OK)
                           fprintf(stderr,"Fehler bei der Suche: %d (%s)\n",ret,kto_check_retval2txt_short(ret));
                        else{
                           ret=lut_multiple(NULL,NULL,NULL,&name,NULL,&plz,&ort,NULL,&bic,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
                           fprintf(stderr,"---------\nSuche nach %s: %d (%s)\n",suchfeld,ret,kto_check_retval2txt_short(ret));
                           if(ret==OK)for(i=0;i<anzahl;i++){
                              j=start_idx[i];   /* Index der Bank */
                              if(typ==0)
                                 fprintf(stderr,"%d %s / %d %s / %s / %s\n",blz_f[j],base_name[j],plz[j],ort[j],name[j],bic[j]);
                              else if(typ==1){
                                 ret=lut_multiple_i(blz_f[j],NULL,NULL,&name,NULL,&plz,&ort,NULL,&bic,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
                                 fprintf(stderr,"%d %d / %d %s / %s / %s\n",blz_f[j],base_name_i[j],*plz,*ort,*name,*bic);
                              }
                              else if(typ==2){
                                 f=zweigstelle[j];
                                 ret=lut_multiple_i(blz_f[j],NULL,NULL,&name,NULL,&plz,&ort,NULL,&bic,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
                                 fprintf(stderr,"%d %d / %d %s / %s / %s\n",blz_f[j],base_name_i[j],plz[f],ort[f],name[f],bic[f]);
                              }
                           }
                           fprintf(stderr,"Anzahl gefunden: %d\n",anzahl);
                        }
                     }
                     break;

                  case 'v':   /* Info, ob geladener Datensatz gültig ist */
                     lut_info(NULL,NULL,NULL,&i,NULL);
                     printf("%s\n",kto_check_retval2txt(i));
                     break;

                  case 'z':   /* strukturierter Verwendungszweck bei IPI */
                     for(ptr=buffer+3;isspace(*ptr);ptr++);
                     if(*(buffer+2)=='g'){
                        ret=ipi_gen(ptr,ipi_buffer,ipi_papier);
                        printf("ipi_gen: %d (%s)\nIPI-Zweck: %s (Papierform: %s)\n",
                              ret,kto_check_retval2txt(ret),ipi_buffer,ipi_papier);
                     }
                     else if(*(buffer+2)=='t'){
                        ret=ipi_check(ptr);
                        printf("ipi_check: %d (%s)\n",ret,kto_check_retval2txt(ret));
                     }
                     break;

                  case 'h':   /* kurze Online-Hilfe ausgeben */
                  case '?':
                  default:
                     printf("%s\n",cmd_help);
               }
               continue;
            }
#endif
            *(buffer+999)=0;  /* nur zur Sicherheit Stringende eintragen */
            for(ptr=buffer,dptr=ptr1=buffer+1000,i=0;isalnum(*ptr) && i<8;)*dptr++=*ptr++;   /* Bankleitzahl kopieren */
            *dptr++=0;
            while(*ptr && !isdigit(*ptr))ptr++;   /* Anfang der Kontonummer suchen */
            for(ptr2=dptr,i=0;isdigit(*ptr) && i<10;)*dptr++=*ptr++;   /* Kontonummer kopieren */
            *dptr=0;
            if(*ptr1 && *ptr2){
#if FILTER_MODE==1
               if(strlen(ptr1)>3){
                  ret=kto_check_blz(ptr1,ptr2);
               }
               else{
                  ret=kto_check_pz(ptr1,ptr2,NULL);
               }
                  /* es kann per Kommando initialisiert werden, deshalb continue */
               if(ret==LUT2_NOT_INITIALIZED){
                  printf("%s %s: %s\n",ptr1,ptr2,kto_check_retval2txt(ret));
                  continue;
               }
               printf("%s %s %d\n",ptr1,ptr2,retval);
#else
               if(strlen(ptr1)>3){
#if DEBUG
                  ret=kto_check_blz_dbg(ptr1,ptr2,&retvals);
#else
                  ret=kto_check_blz(ptr1,ptr2);
#endif
                  if((ret1=lut_multiple(ptr1,&filialen,NULL,&p_name,&p_name_kurz,&p_plz,&p_ort,NULL,NULL,
                        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL))==OK || ret1==LUT2_PARTIAL_OK){
                     if(**p_name)
                        name=*p_name;
                     else
                        name=*p_name_kurz;
                     ort=*p_ort;
                     plz=*p_plz;
                  }
                  else{
                     name=ort="";
                     plz=0;
                  }
               }
               else{
#if DEBUG
                  ret=kto_check_pz_dbg(ptr1,ptr2,NULL,&retvals);
#else
                  ret=kto_check_blz(ptr1,ptr2);
#endif
                  filialen=0;
               }
#if DEBUG
               if(ret==LUT2_NOT_INITIALIZED){
                  printf("%s %s: %s\n",ptr1,ptr2,kto_check_retval2txt(ret));
                  continue;
               }
               printf("%s %s: %s mit Methode %s",ptr1,ptr2,kto_check_retval2txt(ret),retvals.methode);
               if(zeige_namen && filialen && (*name || (plz && *ort))){
                  printf(" (");
                  if(*name)printf("%s",name);
                  if(plz && *ort)printf(", %d %s",plz,ort);
                  putchar(')');
               }
               if(ret<OK)
                  printf(" PZ-Soll: %d\n",retvals.pz);
               else
                  fputc('\n',stdout);
#else
               printf("%s %s: %s",ptr1,ptr2,kto_check_retval2txt(ret));
               if(zeige_namen && filialen){
                  if(*name)printf(" (%s",name);
                  if(plz)printf(", %d",plz);
                  if(*ort)printf(" %s)",ort);
               }
               printf(")\n");
#endif
#endif
            }
            else
               printf("%s",buffer);
         }
      }
      free(buffer);
      cleanup_kto();
      return 0;
   }
#endif

if(!inputname)inputname="blz_in.txt";
   if(!outputname)outputname="blz_out.txt";

   if((in=open(inputname,O_RDONLY))<0){
      perror("Kann die Eingabedatei nicht lesen; Abbruch\n");
      exit(4);
   }
   if((out=open(outputname,O_WRONLY|O_CREAT,0640))<0){
      perror("Kann die Ausgabedatei nicht schreiben; Abbruch\n");
      exit(4);
   }

   fprintf(stderr,"Teste die Konten in %s; Ausgabe nach %s\n",inputname,outputname);
   fstat(in,&s_buf);
   if(!(buffer=malloc(s_buf.st_size+256))){
      fprintf(stderr,"Kann Speicher für filebuffer nicht allokieren; Abbruch\n");
      exit(4);
   }
   ZEIT(lesen1);
   cnt=read(in,buffer,s_buf.st_size);
   close(in);
   ZEIT(lesen2);
   if(verbose)fprintf(stderr,"%d Byte gelesen aus %s\n",cnt,inputname);
   dbuffer=malloc(OUTPUT_BUFSIZE);

		 /******************** schneller Modus ********************/
   if(action==FAST)for(eptr=buffer+cnt,sptr=buffer,dptr=dbuffer,out_cnt=zeilen=konten=0;sptr<eptr;){
      ptr1=sptr;  /* Startposition merken */
      if(dptr>dbuffer+OUTPUT_BUFSIZE-2000){
         ZEIT(schreiben1);
         cnt=write(out,dbuffer,dptr-dbuffer);
         if(cnt!=(dptr-dbuffer))perror("Schreibfehler bei Ausgabe");
         out_cnt+=cnt;
         dptr=dbuffer;
         ZEIT(schreiben2);
         schreiben+=(schreiben2-schreiben1);
      }

         /* es wird für jede Zeile eine Länge von 20 Bytes angenommen,
          * ohne daß dieses getestet wird. Falls diese Bedingung nicht
          * erfüllt ist, geht die Funktion natürlich komplett daneben;
          * aber sie ist auch nur für Testzwecke gedacht, nicht für den
          * normalen Gebrauch!!!
          * Der einzige Test, der gemacht wird, ist auf Zeilenvorschub nach
          * 20 Bytes. Falls dies nicht erfüllt ist, wird ein Fehlerzähler
          * inkrementiert; falls dieser nach den Tests nicht 0 ist, war
          * die Datei nicht für den schnellen Test geeignet; das Ergebnis
          * dürfte normalerweise unbrauchbar sein.
          */

      memcpy(dptr,ptr1,20);   /* Zeile komplett zur Ausgabe kopieren */

         /* das \n am Zeilenende wurde hier mitkopiert; das Kopieren
          * von 20 Zeichen ist schneller als das Kopieren von 19 Zeichen,
          * da dabei long-Transfers benutzt werden können. dptr wird in der
          * nächsten Zeile allerdings nur um 19 Zeichen vorgerückt, nicht
          * um 20; das störende \n wird so bei der Ergebnisausgabe
          * überschrieben.
          */
      dptr+=19;
      ptr2=ptr1+8;
      *ptr2++=0;     /* Endemarkierung für BLZ */

          /* falls kein Zeilenvorschub am Zeilenende gefunden wird,
           * Fehlerzähler inkrementieren */
      if(*(ptr2+10)!='\n')lf_error++;

      *(ptr2+10)=0;  /* Endemarkierung für das Konto */
      zeilen++;
      konten++;
      sptr+=20;

#if DEBUG
      ret=kto_check_blz_dbg(ptr1,ptr2,&retvals);
#else
      ret=kto_check_blz(ptr1,ptr2);
#endif

         /* Die Ergebnisausgabe erfolgt hier in einem switch-Statement, um
          * die Vorteile von memcpy mit festem Zähler nutzen zu können (es kann
          * vom Compiler besser optimiert werden). Damit lassen sich wieder
          * einige Taktzyklen herausschlagen ;-)))
          *
          * Das Switch-Statement enthält alle definierten Rückgabewerte, obwohl
          * viele nicht benötigt werden. Das liegt daran, daß es automatisch
          * generiert wird und eine Auswahl mehr Arbeit machen würde, als alle
          * Werte aufzunehmen.
          */
      switch(ret){
         case IBAN_CHKSUM_OK_NACHFOLGE_BLZ_DEFINED:
            memcpy(dptr,": ### Die IBAN-Prüfsumme stimmt, für die Bank gibt es allerdings eine (andere) Nachfolge-BLZ\n",93);
            dptr+=93;
            break;
         case LUT2_NOT_ALL_IBAN_BLOCKS_LOADED:
            memcpy(dptr,": ### es konnten nicht alle Datenblocks die für die IBAN-Berechnung notwendig sind geladen werden\n",98);
            dptr+=98;
            break;
         case LUT2_NOT_YET_VALID_PARTIAL_OK:
            memcpy(dptr,": ### Der Datensatz ist noch nicht gültig, außerdem konnten nicht alle Blocks geladen werden\n",93);
            dptr+=93;
            break;
         case LUT2_NO_LONGER_VALID_PARTIAL_OK:
            memcpy(dptr,": ### Der Datensatz ist nicht mehr gültig, außerdem konnten nicht alle Blocks geladen werdeng\n",94);
            dptr+=94;
            break;
         case LUT2_BLOCKS_MISSING:
            memcpy(dptr,": ### ok, bei der Initialisierung konnten allerdings ein oder mehrere Blocks nicht geladen werden\n",98);
            dptr+=98;
            break;
         case FALSE_UNTERKONTO_ATTACHED:
            memcpy(dptr,": ### falsch, es wurde ein Unterkonto hinzugefügt (IBAN-Regel)\n",63);
            dptr+=63;
            break;
         case BLZ_BLACKLISTED:
            memcpy(dptr,": ### Die BLZ findet sich in der Ausschlussliste für IBAN-Berechnungen\n",71);
            dptr+=71;
            break;
         case BLZ_MARKED_AS_DELETED:
            memcpy(dptr,": ### Die BLZ ist in der Bundesbank-Datei als gelöscht markiert und somit ungültig\n",83);
            dptr+=83;
            break;
         case IBAN_CHKSUM_OK_SOMETHING_WRONG:
            memcpy(dptr,": ### Die IBAN-Prüfsumme stimmt, es gibt allerdings einen Fehler in der eigenen IBAN-Bestimmung (wahrscheinlich falsch)\n",120);
            dptr+=120;
            break;
         case IBAN_CHKSUM_OK_NO_IBAN_CALCULATION:
            memcpy(dptr,": ### Die IBAN-Prüfsumme stimmt, eine IBAN-Berechnung ist allerdings nicht erlaubt (wahrscheinlich falsch)\n",107);
            dptr+=107;
            break;
         case IBAN_CHKSUM_OK_RULE_IGNORED:
            memcpy(dptr,": ### Die IBAN-Prüfsumme stimmt, es wurde allerdings eine IBAN-Regel nicht beachtet (wahrscheinlich falsch)\n",108);
            dptr+=108;
            break;
         case IBAN_CHKSUM_OK_UNTERKTO_MISSING:
            memcpy(dptr,": ### Die IBAN-Prüfsumme stimmt, es fehlt aber ein Unterkonto (wahrscheinlich falsch)\n",86);
            dptr+=86;
            break;
         case IBAN_INVALID_RULE:
            memcpy(dptr,": ### Die BLZ passt nicht zur angegebenen IBAN-Regel\n",53);
            dptr+=53;
            break;
         case IBAN_AMBIGUOUS_KTO:
            memcpy(dptr,": ### Die Kontonummer ist nicht eindeutig (es gibt mehrere Möglichkeiten)\n",74);
            dptr+=74;
            break;
         case IBAN_RULE_NOT_IMPLEMENTED:
            memcpy(dptr,": ### Die IBAN-Regel ist noch nicht implementiert\n",50);
            dptr+=50;
            break;
         case IBAN_RULE_UNKNOWN:
            memcpy(dptr,": ### Die IBAN-Regel ist nicht bekannt\n",39);
            dptr+=39;
            break;
         case NO_IBAN_CALCULATION:
            memcpy(dptr,": ### Für die Bankverbindung ist keine IBAN-Berechnung erlaubt\n",63);
            dptr+=63;
            break;
         case OLD_BLZ_OK_NEW_NOT:
            memcpy(dptr,": ### Die Bankverbindung ist mit der alten BLZ stimmig, mit der Nachfolge-BLZ nicht\n",84);
            dptr+=84;
            break;
         case LUT2_IBAN_REGEL_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld IBAN-Regel wurde nicht initialisiert\n",52);
            dptr+=52;
            break;
         case INVALID_IBAN_LENGTH:
            memcpy(dptr,": ### Die Länge der IBAN für das angegebene Länderkürzel ist falsch\n",68);
            dptr+=68;
            break;
         case LUT2_NO_ACCOUNT_GIVEN:
            memcpy(dptr,": ### Keine Bankverbindung/IBAN angegeben\n",42);
            dptr+=42;
            break;
         case LUT2_VOLLTEXT_INVALID_CHAR:
            memcpy(dptr,": ### Ungültiges Zeichen ( ()+-/&.,\' ) für die Volltextsuche gefunden\n",71);
            dptr+=71;
            break;
         case LUT2_VOLLTEXT_SINGLE_WORD_ONLY:
            memcpy(dptr,": ### Die Volltextsuche sucht jeweils nur ein einzelnes Wort, benutzen Sie lut_suche_multiple() zur Suche nach mehreren Worten\n",127);
            dptr+=127;
            break;
         case LUT_SUCHE_INVALID_RSC:
            memcpy(dptr,": ### die angegebene Suchresource ist ungültig\n",47);
            dptr+=47;
            break;
         case LUT_SUCHE_INVALID_CMD:
            memcpy(dptr,": ### Suche: im Verknüpfungsstring sind nur die Zeichen a-z sowie + und - erlaubt\n",82);
            dptr+=82;
            break;
         case LUT_SUCHE_INVALID_CNT:
            memcpy(dptr,": ### Suche: es müssen zwischen 1 und 26 Suchmuster angegeben werden\n",69);
            dptr+=69;
            break;
         case LUT2_VOLLTEXT_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld Volltext wurde nicht initialisiert\n",50);
            dptr+=50;
            break;
         case NO_OWN_IBAN_CALCULATION:
            memcpy(dptr,": ### das Institut erlaubt keine eigene IBAN-Berechnung\n",56);
            dptr+=56;
            break;
         case KTO_CHECK_UNSUPPORTED_COMPRESSION:
            memcpy(dptr,": ### die notwendige Kompressions-Bibliothek wurden beim Kompilieren nicht eingebunden\n",87);
            dptr+=87;
            break;
         case KTO_CHECK_INVALID_COMPRESSION_LIB:
            memcpy(dptr,": ### der angegebene Wert für die Default-Kompression ist ungültig\n",67);
            dptr+=67;
            break;
         case OK_UNTERKONTO_ATTACHED_OLD:
            memcpy(dptr,": ### (nicht mehr als Fehler, sondern positive Ausgabe - Dummy für den alten Wert)\n",83);
            dptr+=83;
            break;
         case KTO_CHECK_DEFAULT_BLOCK_INVALID:
            memcpy(dptr,": ### Ungültige Signatur im Default-Block\n",42);
            dptr+=42;
            break;
         case KTO_CHECK_DEFAULT_BLOCK_FULL:
            memcpy(dptr,": ### Die maximale Anzahl Einträge für den Default-Block wurde erreicht\n",72);
            dptr+=72;
            break;
         case KTO_CHECK_NO_DEFAULT_BLOCK:
            memcpy(dptr,": ### Es wurde noch kein Default-Block angelegt\n",48);
            dptr+=48;
            break;
         case KTO_CHECK_KEY_NOT_FOUND:
            memcpy(dptr,": ### Der angegebene Schlüssel wurde im Default-Block nicht gefunden\n",69);
            dptr+=69;
            break;
         case LUT2_NO_LONGER_VALID_BETTER:
            memcpy(dptr,": ### Beide Datensätze sind nicht mehr gültig, dieser ist aber jünger als der andere\n",85);
            dptr+=85;
            break;
         case DTA_SRC_KTO_DIFFERENT:
            memcpy(dptr,": ### Die Auftraggeber-Kontonummer des C-Datensatzes unterscheidet sich von der des A-Satzes\n",93);
            dptr+=93;
            break;
         case DTA_SRC_BLZ_DIFFERENT:
            memcpy(dptr,": ### Die Auftraggeber-Bankleitzahl des C-Datensatzes unterscheidet sich von der des A-Satzes\n",94);
            dptr+=94;
            break;
         case DTA_CR_LF_IN_FILE:
            memcpy(dptr,": ### Die DTA-Datei enthält (unzulässige) Zeilenvorschübe\n",58);
            dptr+=58;
            break;
         case DTA_INVALID_C_EXTENSION:
            memcpy(dptr,": ### ungültiger Typ bei einem Erweiterungsblock eines C-Datensatzes\n",69);
            dptr+=69;
            break;
         case DTA_FOUND_SET_A_NOT_C:
            memcpy(dptr,": ### Es wurde ein C-Datensatz erwartet, jedoch ein E-Satz gefunden\n",68);
            dptr+=68;
            break;
         case DTA_FOUND_SET_E_NOT_C:
            memcpy(dptr,": ### Es wurde ein C-Datensatz erwartet, jedoch ein E-Satz gefunden\n",68);
            dptr+=68;
            break;
         case DTA_FOUND_SET_C_NOT_EXTENSION:
            memcpy(dptr,": ### Es wurde ein C-Datensatzerweiterung erwartet, jedoch ein C-Satz gefunden\n",79);
            dptr+=79;
            break;
         case DTA_FOUND_SET_E_NOT_EXTENSION:
            memcpy(dptr,": ### Es wurde ein C-Datensatzerweiterung erwartet, jedoch ein E-Satz gefunden\n",79);
            dptr+=79;
            break;
         case DTA_INVALID_EXTENSION_COUNT:
            memcpy(dptr,": ### Die Anzahl Erweiterungen paßt nicht zur Blocklänge\n",57);
            dptr+=57;
            break;
         case DTA_INVALID_NUM:
            memcpy(dptr,": ### Ungültige Zeichen in numerischem Feld\n",44);
            dptr+=44;
            break;
         case DTA_INVALID_CHARS:
            memcpy(dptr,": ### Ungültige Zeichen im Textfeld\n",36);
            dptr+=36;
            break;
         case DTA_CURRENCY_NOT_EURO:
            memcpy(dptr,": ### Die Währung des DTA-Datensatzes ist nicht Euro\n",53);
            dptr+=53;
            break;
         case DTA_EMPTY_AMOUNT:
            memcpy(dptr,": ### In einem DTA-Datensatz wurde kein Betrag angegeben\n",57);
            dptr+=57;
            break;
         case DTA_INVALID_TEXT_KEY:
            memcpy(dptr,": ### Ungültiger Textschlüssel in der DTA-Datei\n",48);
            dptr+=48;
            break;
         case DTA_EMPTY_STRING:
            memcpy(dptr,": ### Für ein (alphanumerisches) Feld wurde kein Wert angegeben\n",64);
            dptr+=64;
            break;
         case DTA_MARKER_A_NOT_FOUND:
            memcpy(dptr,": ### Die Startmarkierung des A-Datensatzes wurde nicht gefunden\n",65);
            dptr+=65;
            break;
         case DTA_MARKER_C_NOT_FOUND:
            memcpy(dptr,": ### Die Startmarkierung des C-Datensatzes wurde nicht gefunden\n",65);
            dptr+=65;
            break;
         case DTA_MARKER_E_NOT_FOUND:
            memcpy(dptr,": ### Die Startmarkierung des E-Datensatzes wurde nicht gefunden\n",65);
            dptr+=65;
            break;
         case DTA_INVALID_SET_C_LEN:
            memcpy(dptr,": ### Die Satzlänge eines C-Datensatzes muß zwischen 187 und 622 Byte betragen\n",79);
            dptr+=79;
            break;
         case DTA_INVALID_SET_LEN:
            memcpy(dptr,": ### Die Satzlänge eines A- bzw. E-Satzes muß 128 Byte betragen\n",65);
            dptr+=65;
            break;
         case DTA_WAERUNG_NOT_EURO:
            memcpy(dptr,": ### als Währung in der DTA-Datei ist nicht Euro eingetragen\n",62);
            dptr+=62;
            break;
         case DTA_INVALID_ISSUE_DATE:
            memcpy(dptr,": ### das Ausführungsdatum ist zu früh oder zu spät (max. 15 Tage nach Dateierstellung)\n",88);
            dptr+=88;
            break;
         case DTA_INVALID_DATE:
            memcpy(dptr,": ### das Datum ist ungültig\n",29);
            dptr+=29;
            break;
         case DTA_FORMAT_ERROR:
            memcpy(dptr,": ### Formatfehler in der DTA-Datei\n",36);
            dptr+=36;
            break;
         case DTA_FILE_WITH_ERRORS:
            memcpy(dptr,": ### die DTA-Datei enthält Fehler\n",35);
            dptr+=35;
            break;
         case INVALID_SEARCH_RANGE:
            memcpy(dptr,": ### ungültiger Suchbereich angegeben (unten>oben)\n",52);
            dptr+=52;
            break;
         case KEY_NOT_FOUND:
            memcpy(dptr,": ### Die Suche lieferte kein Ergebnis\n",39);
            dptr+=39;
            break;
         case BAV_FALSE:
            memcpy(dptr,": ### BAV denkt, das Konto ist falsch (konto_check hält es für richtig)\n",72);
            dptr+=72;
            break;
         case LUT2_NO_USER_BLOCK:
            memcpy(dptr,": ### User-Blocks müssen einen Typ > 500 haben\n",47);
            dptr+=47;
            break;
         case INVALID_SET:
            memcpy(dptr,": ### für ein LUT-Set sind nur die Werte 0, 1 oder 2 möglich\n",61);
            dptr+=61;
            break;
         case NO_GERMAN_BIC:
            memcpy(dptr,": ### Ein Konto kann kann nur für deutsche Banken geprüft werden\n",65);
            dptr+=65;
            break;
         case IPI_CHECK_INVALID_LENGTH:
            memcpy(dptr,": ### Der zu validierende strukturierete Verwendungszweck muß genau 20 Zeichen enthalten\n",89);
            dptr+=89;
            break;
         case IPI_INVALID_CHARACTER:
            memcpy(dptr,": ### Im strukturierten Verwendungszweck dürfen nur alphanumerische Zeichen vorkommen\n",86);
            dptr+=86;
            break;
         case IPI_INVALID_LENGTH:
            memcpy(dptr,": ### Die Länge des IPI-Verwendungszwecks darf maximal 18 Byte sein\n",68);
            dptr+=68;
            break;
         case LUT1_FILE_USED:
            memcpy(dptr,": ### Es wurde eine LUT-Datei im Format 1.0/1.1 geladen\n",56);
            dptr+=56;
            break;
         case MISSING_PARAMETER:
            memcpy(dptr,": ### Für die aufgerufene Funktion fehlt ein notwendiger Parameter\n",67);
            dptr+=67;
            break;
         case IBAN2BIC_ONLY_GERMAN:
            memcpy(dptr,": ### Die Funktion iban2bic() arbeitet nur mit deutschen Bankleitzahlen\n",72);
            dptr+=72;
            break;
         case IBAN_OK_KTO_NOT:
            memcpy(dptr,": ### Die Prüfziffer der IBAN stimmt, die der Kontonummer nicht\n",64);
            dptr+=64;
            break;
         case KTO_OK_IBAN_NOT:
            memcpy(dptr,": ### Die Prüfziffer der Kontonummer stimmt, die der IBAN nicht\n",64);
            dptr+=64;
            break;
         case TOO_MANY_SLOTS:
            memcpy(dptr,": ### Es sind nur maximal 500 Slots pro LUT-Datei möglich (Neukompilieren erforderlich)\n",88);
            dptr+=88;
            break;
         case INIT_FATAL_ERROR:
            memcpy(dptr,": ### Initialisierung fehlgeschlagen (init_wait geblockt)\n",58);
            dptr+=58;
            break;
         case INCREMENTAL_INIT_NEEDS_INFO:
            memcpy(dptr,": ### Ein inkrementelles Initialisieren benötigt einen Info-Block in der LUT-Datei\n",83);
            dptr+=83;
            break;
         case INCREMENTAL_INIT_FROM_DIFFERENT_FILE:
            memcpy(dptr,": ### Ein inkrementelles Initialisieren mit einer anderen LUT-Datei ist nicht möglich\n",86);
            dptr+=86;
            break;
         case DEBUG_ONLY_FUNCTION:
            memcpy(dptr,": ### Die Funktion ist nur in der Debug-Version vorhanden\n",58);
            dptr+=58;
            break;
         case LUT2_INVALID:
            memcpy(dptr,": ### Kein Datensatz der LUT-Datei ist aktuell gültig\n",54);
            dptr+=54;
            break;
         case LUT2_NOT_YET_VALID:
            memcpy(dptr,": ### Der Datensatz ist noch nicht gültig\n",42);
            dptr+=42;
            break;
         case LUT2_NO_LONGER_VALID:
            memcpy(dptr,": ### Der Datensatz ist nicht mehr gültig\n",42);
            dptr+=42;
            break;
         case LUT2_GUELTIGKEIT_SWAPPED:
            memcpy(dptr,": ### Im Gültigkeitsdatum sind Anfangs- und Enddatum vertauscht\n",64);
            dptr+=64;
            break;
         case LUT2_INVALID_GUELTIGKEIT:
            memcpy(dptr,": ### Das angegebene Gültigkeitsdatum ist ungültig (Soll: JJJJMMTT-JJJJMMTT)\n",77);
            dptr+=77;
            break;
         case LUT2_INDEX_OUT_OF_RANGE:
            memcpy(dptr,": ### Der Index für die Filiale ist ungültig\n",45);
            dptr+=45;
            break;
         case LUT2_INIT_IN_PROGRESS:
            memcpy(dptr,": ### Die Bibliothek wird gerade neu initialisiert\n",51);
            dptr+=51;
            break;
         case LUT2_BLZ_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld BLZ wurde nicht initialisiert\n",45);
            dptr+=45;
            break;
         case LUT2_FILIALEN_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld Filialen wurde nicht initialisiert\n",50);
            dptr+=50;
            break;
         case LUT2_NAME_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld Bankname wurde nicht initialisiert\n",50);
            dptr+=50;
            break;
         case LUT2_PLZ_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld PLZ wurde nicht initialisiert\n",45);
            dptr+=45;
            break;
         case LUT2_ORT_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld Ort wurde nicht initialisiert\n",45);
            dptr+=45;
            break;
         case LUT2_NAME_KURZ_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld Kurzname wurde nicht initialisiert\n",50);
            dptr+=50;
            break;
         case LUT2_PAN_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld PAN wurde nicht initialisiert\n",45);
            dptr+=45;
            break;
         case LUT2_BIC_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld BIC wurde nicht initialisiert\n",45);
            dptr+=45;
            break;
         case LUT2_PZ_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld Prüfziffer wurde nicht initialisiert\n",52);
            dptr+=52;
            break;
         case LUT2_NR_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld NR wurde nicht initialisiert\n",44);
            dptr+=44;
            break;
         case LUT2_AENDERUNG_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld Änderung wurde nicht initialisiert\n",50);
            dptr+=50;
            break;
         case LUT2_LOESCHUNG_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld Löschung wurde nicht initialisiert\n",50);
            dptr+=50;
            break;
         case LUT2_NACHFOLGE_BLZ_NOT_INITIALIZED:
            memcpy(dptr,": ### Das Feld Nachfolge-BLZ wurde nicht initialisiert\n",55);
            dptr+=55;
            break;
         case LUT2_NOT_INITIALIZED:
            memcpy(dptr,": ### die Programmbibliothek wurde noch nicht initialisiert\n",60);
            dptr+=60;
            break;
         case LUT2_FILIALEN_MISSING:
            memcpy(dptr,": ### der Block mit der Filialenanzahl fehlt in der LUT-Datei\n",62);
            dptr+=62;
            break;
         case LUT2_PARTIAL_OK:
            memcpy(dptr,": ### es wurden nicht alle Blocks geladen\n",42);
            dptr+=42;
            break;
         case LUT2_Z_BUF_ERROR:
            memcpy(dptr,": ### Buffer error in den ZLIB Routinen\n",40);
            dptr+=40;
            break;
         case LUT2_Z_MEM_ERROR:
            memcpy(dptr,": ### Memory error in den ZLIB-Routinen\n",40);
            dptr+=40;
            break;
         case LUT2_Z_DATA_ERROR:
            memcpy(dptr,": ### Datenfehler im komprimierten LUT-Block\n",45);
            dptr+=45;
            break;
         case LUT2_BLOCK_NOT_IN_FILE:
            memcpy(dptr,": ### Der Block ist nicht in der LUT-Datei enthalten\n",53);
            dptr+=53;
            break;
         case LUT2_DECOMPRESS_ERROR:
            memcpy(dptr,": ### Fehler beim Dekomprimieren eines LUT-Blocks\n",50);
            dptr+=50;
            break;
         case LUT2_COMPRESS_ERROR:
            memcpy(dptr,": ### Fehler beim Komprimieren eines LUT-Blocks\n",48);
            dptr+=48;
            break;
         case LUT2_FILE_CORRUPTED:
            memcpy(dptr,": ### Die LUT-Datei ist korrumpiert\n",36);
            dptr+=36;
            break;
         case LUT2_NO_SLOT_FREE:
            memcpy(dptr,": ### Im Inhaltsverzeichnis der LUT-Datei ist kein Slot mehr frei\n",66);
            dptr+=66;
            break;
         case UNDEFINED_SUBMETHOD:
            memcpy(dptr,": ### Die (Unter)Methode ist nicht definiert\n",45);
            dptr+=45;
            break;
         case EXCLUDED_AT_COMPILETIME:
            memcpy(dptr,": ### Der benötigte Programmteil wurde beim Kompilieren deaktiviert\n",68);
            dptr+=68;
            break;
         case INVALID_LUT_VERSION:
            memcpy(dptr,": ### Die Versionsnummer für die LUT-Datei ist ungültig\n",56);
            dptr+=56;
            break;
         case INVALID_PARAMETER_STELLE1:
            memcpy(dptr,": ### ungültiger Prüfparameter (erste zu prüfende Stelle)\n",58);
            dptr+=58;
            break;
         case INVALID_PARAMETER_COUNT:
            memcpy(dptr,": ### ungültiger Prüfparameter (Anzahl zu prüfender Stellen)\n",61);
            dptr+=61;
            break;
         case INVALID_PARAMETER_PRUEFZIFFER:
            memcpy(dptr,": ### ungültiger Prüfparameter (Position der Prüfziffer)\n",57);
            dptr+=57;
            break;
         case INVALID_PARAMETER_WICHTUNG:
            memcpy(dptr,": ### ungültiger Prüfparameter (Wichtung)\n",42);
            dptr+=42;
            break;
         case INVALID_PARAMETER_METHODE:
            memcpy(dptr,": ### ungültiger Prüfparameter (Rechenmethode)\n",47);
            dptr+=47;
            break;
         case LIBRARY_INIT_ERROR:
            memcpy(dptr,": ### Problem beim Initialisieren der globalen Variablen\n",57);
            dptr+=57;
            break;
         case LUT_CRC_ERROR:
            memcpy(dptr,": ### Prüfsummenfehler in der blz.lut Datei\n",44);
            dptr+=44;
            break;
         case FALSE_GELOESCHT:
            memcpy(dptr,": ### falsch (die BLZ wurde außerdem gelöscht)\n",47);
            dptr+=47;
            break;
         case OK_NO_CHK_GELOESCHT:
            memcpy(dptr,": ### ok, ohne Prüfung (die BLZ wurde allerdings gelöscht)\n",59);
            dptr+=59;
            break;
         case OK_GELOESCHT:
            memcpy(dptr,": ### ok (die BLZ wurde allerdings gelöscht)\n",45);
            dptr+=45;
            break;
         case BLZ_GELOESCHT:
            memcpy(dptr,": ### die Bankleitzahl wurde gelöscht\n",38);
            dptr+=38;
            break;
         case INVALID_BLZ_FILE:
            memcpy(dptr,": ### Fehler in der blz.txt Datei (falsche Zeilenlänge)\n",56);
            dptr+=56;
            break;
         case LIBRARY_IS_NOT_THREAD_SAFE:
            memcpy(dptr,": ### undefinierte Funktion, die library wurde mit THREAD_SAFE=0 kompiliert\n",76);
            dptr+=76;
            break;
         case FATAL_ERROR:
            memcpy(dptr,": ### schwerer Fehler im Konto_check-Modul\n",43);
            dptr+=43;
            break;
         case INVALID_KTO_LENGTH:
            memcpy(dptr,": ### ein Konto muß zwischen 1 und 10 Stellen haben\n",52);
            dptr+=52;
            break;
         case FILE_WRITE_ERROR:
            memcpy(dptr,": ### kann Datei nicht schreiben\n",33);
            dptr+=33;
            break;
         case FILE_READ_ERROR:
            memcpy(dptr,": ### kann Datei nicht lesen\n",29);
            dptr+=29;
            break;
         case ERROR_MALLOC:
            memcpy(dptr,": ### kann keinen Speicher allokieren\n",38);
            dptr+=38;
            break;
         case NO_BLZ_FILE:
            memcpy(dptr,": ### die blz.txt Datei wurde nicht gefunden\n",45);
            dptr+=45;
            break;
         case INVALID_LUT_FILE:
            memcpy(dptr,": ### die blz.lut Datei ist inkosistent/ungültig\n",49);
            dptr+=49;
            break;
         case NO_LUT_FILE:
            memcpy(dptr,": ### die blz.lut Datei wurde nicht gefunden\n",45);
            dptr+=45;
            break;
         case INVALID_BLZ_LENGTH:
            memcpy(dptr,": ### die Bankleitzahl ist nicht achtstellig\n",45);
            dptr+=45;
            break;
         case INVALID_BLZ:
            memcpy(dptr,": ### die Bankleitzahl ist ungültig\n",36);
            dptr+=36;
            break;
         case INVALID_KTO:
            memcpy(dptr,": ### das Konto ist ungültig\n",29);
            dptr+=29;
            break;
         case NOT_IMPLEMENTED:
            memcpy(dptr,": ### die Methode wurde noch nicht implementiert\n",49);
            dptr+=49;
            break;
         case NOT_DEFINED:
            memcpy(dptr,": ### die Methode ist nicht definiert\n",38);
            dptr+=38;
            break;
         case FALSE:
            memcpy(dptr,": ### falsch\n",13);
            dptr+=13;
            break;
         case OK:
            memcpy(dptr,": ok\n",5);
            dptr+=5;
            break;
         case OK_NO_CHK:
            memcpy(dptr,": ok, ohne Prüfung\n",19);
            dptr+=19;
            break;
         case OK_TEST_BLZ_USED:
            memcpy(dptr,": ok, für den Test wurde eine Test-BLZ verwendet\n",49);
            dptr+=49;
            break;
         case LUT2_VALID:
            memcpy(dptr,": Der Datensatz ist aktuell gültig\n",35);
            dptr+=35;
            break;
         case LUT2_NO_VALID_DATE:
            memcpy(dptr,": Der Datensatz enthält kein Gültigkeitsdatum\n",46);
            dptr+=46;
            break;
         case LUT1_SET_LOADED:
            memcpy(dptr,": Die Datei ist im alten LUT-Format (1.0/1.1)\n",46);
            dptr+=46;
            break;
         case LUT1_FILE_GENERATED:
            memcpy(dptr,": ok, es wurde allerdings eine LUT-Datei im alten Format (1.0/1.1) generiert\n",77);
            dptr+=77;
            break;
         case DTA_FILE_WITH_WARNINGS:
            memcpy(dptr,": In der DTAUS-Datei wurden kleinere Fehler gefunden\n",53);
            dptr+=53;
            break;
         case LUT_V2_FILE_GENERATED:
            memcpy(dptr,": ok, es wurde allerdings eine LUT-Datei im Format 2.0 generiert (Compilerswitch)\n",82);
            dptr+=82;
            break;
         case KTO_CHECK_VALUE_REPLACED:
            memcpy(dptr,": ok, der Wert für den Schlüssel wurde überschrieben\n",53);
            dptr+=53;
            break;
         case OK_UNTERKONTO_POSSIBLE:
            memcpy(dptr,": wahrscheinlich ok, die Kontonummer kann allerdings (nicht angegebene) Unterkonten enthalten\n",94);
            dptr+=94;
            break;
         case OK_UNTERKONTO_GIVEN:
            memcpy(dptr,": wahrscheinlich ok, die Kontonummer enthält eine Unterkontonummer\n",67);
            dptr+=67;
            break;
         case OK_SLOT_CNT_MIN_USED:
            memcpy(dptr,": ok, die Anzahl Slots wurde auf SLOT_CNT_MIN (60) hochgesetzt\n",63);
            dptr+=63;
            break;
         case SOME_KEYS_NOT_FOUND:
            memcpy(dptr,": ok, ein(ige) Schlüssel wurden nicht gefunden\n",47);
            dptr+=47;
            break;
         case LUT2_KTO_NOT_CHECKED:
            memcpy(dptr,": Die Bankverbindung wurde nicht getestet\n",42);
            dptr+=42;
            break;
         case LUT2_OK_WITHOUT_IBAN_RULES:
            memcpy(dptr,": Es wurden fast alle Blocks (außer den IBAN-Regeln) geladen\n",61);
            dptr+=61;
            break;
         case OK_NACHFOLGE_BLZ_USED:
            memcpy(dptr,": ok, für die BLZ wurde allerdings die Nachfolge-BLZ eingesetzt\n",64);
            dptr+=64;
            break;
         case OK_KTO_REPLACED:
            memcpy(dptr,": ok, die Kontonummer wurde allerdings ersetzt\n",47);
            dptr+=47;
            break;
         case OK_BLZ_REPLACED:
            memcpy(dptr,": ok, die Bankleitzahl wurde allerdings ersetzt\n",48);
            dptr+=48;
            break;
         case OK_BLZ_KTO_REPLACED:
            memcpy(dptr,": ok, die Bankleitzahl und Kontonummer wurde allerdings ersetzt\n",64);
            dptr+=64;
            break;
         case OK_IBAN_WITHOUT_KC_TEST:
            memcpy(dptr,": ok, die Bankverbindung ist (ohne Test) als richtig anzusehen\n",63);
            dptr+=63;
            break;
         case OK_INVALID_FOR_IBAN:
            memcpy(dptr,": ok, für IBAN ist (durch eine Regel) allerdings ein anderer BIC definiert\n",75);
            dptr+=75;
            break;
         case OK_HYPO_REQUIRES_KTO:
            memcpy(dptr,": ok, für die BIC-Bestimmung der ehemaligen Hypo-Bank für IBAN wird i.A. zusätzlich die Kontonummer benötigt\n",109);
            dptr+=109;
            break;
         case OK_KTO_REPLACED_NO_PZ:
            memcpy(dptr,": ok, die Kontonummer wurde ersetzt, die neue Kontonummer hat keine Prüfziffer\n",79);
            dptr+=79;
            break;
         case OK_UNTERKONTO_ATTACHED:
            memcpy(dptr,": ok, es wurde ein (weggelassenes) Unterkonto angefügt\n",55);
            dptr+=55;
            break;
      }
   }

		 /******************** langsamer Modus ********************/
	else for(eptr=buffer+cnt,sptr=buffer,dptr=dbuffer,out_cnt=zeilen=konten=0;sptr<eptr;){
      if(dptr>dbuffer+OUTPUT_BUFSIZE-2000){
         ZEIT(schreiben1);
         cnt=write(out,dbuffer,dptr-dbuffer);
         if(cnt!=(dptr-dbuffer))perror("Schreibfehler bei Ausgabe");
         out_cnt+=cnt;
         dptr=dbuffer;
         ZEIT(schreiben2);
         schreiben+=(schreiben2-schreiben1);
      }
      ptr1=sptr;  /* Startposition merken */
      while((*dptr= *sptr++)!='\n')dptr++;      /* ganze Zeile kopieren */
      while(*ptr1==' ' || *ptr1=='\t')ptr1++;   /* Blanks am Zeilenanfang überspringen */
      zeilen++;
      if(!ISXDIGIT(*ptr1)){                     /* keine BLZ gefunden */
         *dptr++='\n';
         continue;
      }

		for(ptr2=ptr1+1;ISXDIGIT(*ptr2);ptr2++);    /* BLZ/Prüfziffer gefunden */
      *ptr2++=0;
      while(!ISDIGIT(*ptr2) && *ptr2!='\n')ptr2++; /* Kontonummer suchen */
      if(*ptr2=='\n'){
         *dptr++=separator;
         for(ptr1=" ##### Keine Kontonummer gefunden #####\n";(*dptr=*ptr1++);dptr++);
         continue;
      }
      konten++;
      for(ptr=ptr2;ISDIGIT(*ptr);ptr++); /* Kontonummer gefunden */
      *ptr=0;

#if DEBUG
      if((ptr2-ptr1)<7){
         ret=kto_check_pz_dbg(ptr1,ptr2,NULL,&retvals);
         if(ret==LUT2_NOT_INITIALIZED){
            printf("%s %s: %s\n",ptr1,ptr2,kto_check_retval2txt(ret));
            break;
         }
         name=ort="";
         filialen=0;
      }
      else{
         ret=kto_check_blz_dbg(ptr1,ptr2,&retvals);
         if(ret==LUT2_NOT_INITIALIZED){
            printf("%s %s: %s\n",ptr1,ptr2,kto_check_retval2txt(ret));
            break;
         }
         if((ret1=lut_multiple(ptr1,&filialen,NULL,&p_name,NULL,&p_plz,&p_ort,NULL,NULL,
               NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL))==OK || ret1==LUT2_PARTIAL_OK){
            name=*p_name;
            ort=*p_ort;
            plz=*p_plz;
         }
         else{
            name=ort="";
            plz=0;
         }
      }
#else
      if((ptr2-ptr1)<7){
         ret=kto_check_pz(ptr1,ptr2,NULL);
         if(ret==LUT2_NOT_INITIALIZED){
            printf("%s %s: %s\n",ptr1,ptr2,kto_check_retval2txt(ret));
            break;
         }
         name=ort="";
         filialen=0;
      }
      else{
         ret=kto_check_blz(ptr1,ptr2);
         if(ret==LUT2_NOT_INITIALIZED){
            printf("%s %s: %s\n",ptr1,ptr2,kto_check_retval2txt(ret));
            break;
         }
         if((ret1=lut_multiple(ptr1,&filialen,NULL,&p_name,NULL,&p_plz,&p_ort,NULL,NULL,
               NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL))==OK || ret1==LUT2_PARTIAL_OK){
            name=*p_name;
            ort=*p_ort;
            plz=*p_plz;
         }
         else{
            name=ort="";
            plz=0;
         }
      }
#endif

      *dptr++=separator;
      *dptr++=' ';
      for(ptrc=kto_check_retval2txt(ret);(*dptr= *ptrc++);dptr++);
      *dptr++='\n';
   }

   ZEIT(schreiben1);
   cnt=write(out,dbuffer,dptr-dbuffer);
   if(cnt!=(dptr-dbuffer))perror("Schreibfehler bei Ausgabe");

      /* Die Datei muß noch auf die richtige Länge abgeschnitten werden,
       * denn, falls sie schon existierte,wurden existierende Sektoren
       * nicht freigegeben, sondern nur überschrieben (etwas schneller);
       * ein einfaches ftruncate() mit der Anzahl geschriebener Bytes geht
       * allerdings bei M$* daneben, da hier immer statt \n ein \r\n
       * geschrieben wird, und die Dateilänge dann nicht mehr stimmt.
       * Daher wird mit fdopen() ein neuer Deskriptor für die Datei eröffnet
       * und die aktuelle Schreibposition mit ftell() erfragt.
       */

   out_f=fdopen(out,"w");
   ftruncate(out,ftell(out_f));
   fclose(out_f);
   close(out);
   ZEIT(t2=schreiben2);
   schreiben+=(schreiben2-schreiben1);
   if(verbose){
      fprintf(stderr,"%d Byte geschrieben nach %s\ngetestet: %d Konten in %d Zeilen in %1.3fs\n\
(Lesen: %1.3fs, Test: %1.3fs, Schreiben: %1.3fs)\n",out_cnt,outputname,konten,zeilen,
         t2-t1,lesen2-lesen1,t2-t1-schreiben-(lesen2-lesen1),schreiben);
   }
   if(lf_error)fprintf(stderr,"fehlerhafte Zeilen: %d%s\n",lf_error,lf_error>zeilen/100 || lf_error>10?
      " (die Ausgabe ist wahrscheinlich unbrauchbar; besser ohne -f probieren)":"");
   cleanup_kto();
   if(buffer)free(buffer);
   if(dbuffer)free(dbuffer);
   return 0;
}
