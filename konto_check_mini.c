/*
 * vim:cindent:ft=c
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "konto_check.h"

#undef DEFAULT_LUT_LEVEL
#define DEFAULT_LUT_LEVEL 5

void print_status(char *txt);
void print_status_nl(char *txt);
void print_help(void);

enum {TEST,GENERATE_LUT,IBAN2BIC,GENERATE_ZWECK};

   /* globale Variablen (aus Faulheitsgründen) */
int ret,verbose;

void print_help(void)
{
   printf("Aufruf: konto_check_mini [optionen/argumente]\n"
         "\n"
         "Das Programm dient zum Test von BLZ/Kontonummern, Prüfziffer/Kontonummern,\n"
         "IBAN oder Strukturieretem Verwendungszweck. Außerdem können einige Infos zu\n"
         "Banken ausgegeben werden, sowie eine LUT-Datei generiert werden.\n"
         "\n"
         "Der Default-Modus ist Test; in diesem Modus werden für die Übergabeparameter\n"
         "(abhängig von der Länge des Arguments) die folgenden Aktionen gemacht:\n"
         "\n"
         "   8 Byte            BLZ           Bank-Infos ausgeben\n"
         "   11...12 Byte      methode:kto   Prüfziffermethode/Konto testen\n"
         "   13...19 Byte      kto@blz       Bankverbindung testen\n"
         "   13...19 Byte      blz+kto       Bankverbindung testen\n"
         "   20 Byte           Zweck         Strukturierten Verwendungszweck testen\n"
         "  >20 Byte           IBAN          IBAN testen (EDV- oder Papierform)\n"
         "\n"
         "Mit der Option -z können Strukturierte Verwendungszwecke generiert werden;\n"
         "bei der Option -b wird aus einer IBAN BIC, BLZ und Kontonummer extrahiert \n"
         "(nur für deutsche Konten).\n"
         "\n"
         "Falls als *erste* Option -m angegeben wird, wird die Bibliothek nicht initialisiert;\n"
         "dieser Modus dient dazu, nur Prüfziffer/Konto-Kombinationen in der Form pz:kto\n"
         "zu prüfen. Er wird sofort abgebrochen, falls eine Option außer -v oder \n"
         "eine BLZ/Kto-Kombination der Form blz+kto oder kto@blz gefunden wird.\n"
         "\n"
         "Folgende Optionen sind möglich:\n"
         "   -1 Set 1 auswählen (bei Option -l)\n"
         "   -2 Set 2 auswählen (bei Option -l)\n"
         "   -b Modus: IBAN -> BIC\n"
         "   -d [12] ausführliches Debug einschalten (für Testzwecke)\n"
         "   -g LUT-Datei generieren (s.u.; muß als erste Option stehen)\n"
         "   -i ID der LUT-Datei ausgeben\n"
         "   -I Infos über die LUT-Datei ausgeben\n"
         "   -l LUT-Name für Initialisierung\n"
         "   -m Methoden-Test: nur Prüfziffermethoden, ohne LUT-Initialisierung\n"
         "   -t Modus: Test\n"
         "   -v verbose, 1: Zahl, 2: kurz, 4: lang, 8: HTML, 16: UTF-8\n" //, 32: CSV-Darstellung
         "   -z Modus: Strukturierten Verwendungszweck generieren\n"
         "   -?, -h kurze Hilfe anzeigen\n"
         "\n"
         "Unteroptionen für -g (LUT-Datei generieren):\n"
         "      -1 Set 1 auswählen (bei Option -l)\n"
         "      -2 Set 2 auswählen (bei Option -l)\n"
         "      -G Gültigkeitsdatum angeben (Format JJJJMMTT-JJJJMMTT)\n"
         "      -i User-Infozeile der LUT-Datei\n"
         "      -s Anzahl Slots in der LUT-Datei\n");
   exit(0);
}

void print_status_nl(char *txt)
{
   print_status(txt);
   if(verbose)putchar('\n');
}

void print_status(char *txt)
{
   int first;
   if(verbose){
      first=1;
      printf("%s: [",txt);
      if(verbose&1){
         printf("%d",ret);
         first=0;
      }
      if(verbose&2){
         if(!first)putchar('/');
         printf("%s",kto_check_retval2txt_short(ret));
         first=0;
      }
      if(verbose&4){
         if(!first)putchar('/');
         printf("%s",kto_check_retval2txt(ret));
         first=0;
      }
      if(verbose&8){
         if(!first)putchar('/');
         printf("%s",kto_check_retval2html(ret));
         first=0;
      }
      if(verbose&16){
         if(!first)putchar('/');
         printf("%s",kto_check_retval2utf8(ret));
         first=0;
      }
      putchar(']');
   }
}

#define GET_OPTARG do{if(*(argv[i]+2)) \
                     optarg=argv[i]+2; \
                  else if(++i<argc && *argv[i]!='-') \
                     optarg=argv[i]; \
                  else{ \
                     fprintf(stderr,"Die Option -%c benötigt ein Argument, aber es wurde keins angegeben; Abbruch\n",*(argv[--i]+1)); \
                     return 2; \
                  }}while(0)

int main(int argc,char **argv)
{
   char *ptr,*ptr1,*blz,*kto,**name,**name_kurz,**ort,**bic,*trennzeile,*dummy[1],
        *lut_name,*gueltigkeit,*user_info,buffer[64],*optarg,*inputname,*outputname;
   int i,i1,j,k,ret2,*plz,len,action=TEST,format,filialen,lut_level,ok,g1,g2,set,
       slots,delimiter,di[1];

   if(argc==1)print_help();
   trennzeile="----------------------------------------------------------------\n";
   set=slots=filialen=0;
   format=3;
   verbose=2;
   lut_level=5;
   i1=1; /* wird bei Option -m benutzt, um die Tests nicht von vorn anfangen zu lassen */
   user_info=lut_name=NULL;

   if(*argv[1]=='-' && *(argv[1]+1)=='g'){   /* generate_lut extra behandeln */
      inputname=outputname=NULL;
      gueltigkeit="00000000-00000000";
      for(i=1;i<argc;i++){
         if(*argv[i]=='-'){
            switch(*(argv[i]+1)){
               case '1':
                  set=1;
                  break;

               case '2':
                  set=2;
                  break;

               case 'g':
                  action=GENERATE_LUT;
                  GET_OPTARG;
                  if(optarg){
                     ptr=optarg;
                     switch(*ptr){
                        case '1': format=1; break;
                        case '2': format=2; break;
                        case '3': format=3; break;
                        case 'f': filialen=1; break;
                        default: break;
                     }
                     if(*++ptr=='f')
                        filialen=1;
                     else if(*ptr>='0' && *ptr<='9')
                        lut_level=*ptr-'0';
                     if(*++ptr=='f')filialen=1;
                  }
                  break;

               case 'G':
                  GET_OPTARG;
                  if((*(ptr=optarg)=='-' || *ptr=='0') && !*(ptr+1))continue;
                  gueltigkeit=optarg;
                  for(ptr=gueltigkeit,ok=1,j=0;j<8;j++)if(!isdigit(*ptr++))ok=0;
                  if(*ptr++!='-')ok=0;
                  for(j=0;j<8;j++)if(!isdigit(*ptr++))ok=0;
                  if(!ok || *ptr){
                     printf("Fehler: ungültiges Format für den Gültigkeitszeitraum\nSollformat: JJJJMMTT-JJJJMMTT (angegeben: %s)\n",gueltigkeit);
                     exit(1);
                  }
                  g1=atoi(gueltigkeit);
                  g2=atoi(gueltigkeit+9);
                  if(g1>g2){
                     printf("Fehler: Das Anfangsdatum für die Gültigkeit liegt nach dem Enddatum\n");
                     exit(1);
                  }
                  break;

               case 'i':
                  GET_OPTARG;
                  user_info=optarg;
                  break;

               case 's':
                  GET_OPTARG;
                  slots=atoi(optarg);
                  break;

               case 'v':
                  GET_OPTARG;
                  verbose=atoi(optarg);
                  break;

               case '?':
               case 'h':
                  print_help();
                  exit(0);
                  break;

               default:
                  fprintf(stderr,"Ungültige Option %s (ignoriert)\n",argv[i]);
                  break;
            }
         }
         else if(!inputname)
            inputname=argv[i];
         else if(!outputname)
            outputname=argv[i];
      }
      ret=generate_lut2_p(inputname,outputname,user_info,gueltigkeit,lut_level,filialen,slots,format,set);
      print_status_nl("generate_lut");
      return 0;
   }

   if(*argv[1]=='-' && *(argv[1]+1)=='r'){   /* Sonderfall -r: rebuild BLZ-File */
      if(argc<4){
         fprintf(stderr,"konto_check_mini: Bei der Option -r müssen noch Eingabe- und Ausgabedateiname angegeben werden");
         exit(1);
      }
      inputname=argv[2];
      outputname=argv[3];
      ret=rebuild_blzfile(inputname,outputname,0);
      print_status_nl("rebuild_blzfile");
      return 0;
   }

   if(*argv[1]=='-' && *(argv[1]+1)=='m'){   /* Sonderbehandlung für Methodentest (-m, ohne Initialisierung) */
      for(i=2;i<argc;i++){
         if(*argv[i]=='-'){ /* bei Optionen (außer -v) wird dieser Test abgebrochen */
            if(*(argv[i]+1)=='v'){
               GET_OPTARG;
               verbose=atoi(optarg);
            }
            else{
               i1=i;
               break;
            }
         }
         else{
            len=strlen(ptr=argv[i]);
            for(ptr=argv[i];isalnum(*ptr);ptr++);
            delimiter=*ptr;
            *ptr++=0;
            if(len>13 || delimiter!=':'){   /* keine Prüfziffermethode */
               i1=i;
               *--ptr=delimiter; /* alten delimiter zurückschreiben für nächsten Test */
               break;
            }
            ret=kto_check_pz(argv[i],ptr,NULL);
            *--ptr=delimiter;
            printf("Test PZ/Kto. %s",argv[i]);
            print_status_nl("");
         }
      }
      i1=i;
   }

      /* Normale Fälle (außer generate_lut()) behandeln
       * zunächst komplett mit Default-Werten initialisieren 
       */
   if((ret=lut_init(NULL,DEFAULT_LUT_LEVEL,0))<OK && ret!=LUT2_PARTIAL_OK){
      print_status_nl("lut_init");
      exit(1);
   }

   for(set=0,i=i1;i<argc;i++){
      if(*argv[i]=='-'){
         switch(*(argv[i]+1)){
            case '1':
               set=1;
               break;

            case '2':
               set=2;
               break;

            case 'b':
               action=IBAN2BIC;
               break;

            case 'd':
               GET_OPTARG;
               set_verbose_debug(atoi(optarg));
               break;

            case 'g':
               fprintf(stderr,"Die Option -g muß an erster Stelle stehen\n");
               exit(3);

            case 'i':
               GET_OPTARG;
               ret=get_lut_id(optarg,set,buffer);
               printf("Datei-ID von Set %d",set);
               print_status("");
               printf(" >%s<\n",buffer);
               return 0;

            case 'I':
               GET_OPTARG;
               ret=lut_info(optarg,&ptr,&ptr1,&j,&k);
               print_status_nl("lut_info");
               printf("%sPrimärer Datensatz:   %s\nSekundärer Datensatz: %s\n%s",
                     trennzeile,kto_check_retval2txt(j),kto_check_retval2txt(k),trennzeile);
               if(ptr){
                  printf("%s%s",ptr,trennzeile);
                  free(ptr);
               }
               if(ptr1){
                  printf("%s%s",ptr1,trennzeile);
                  free(ptr1);
               }
               return 0;

            case 'l':
               GET_OPTARG;
               lut_name=optarg;
               if((ret=kto_check_init_p(lut_name,DEFAULT_LUT_LEVEL,set,0))<=0){
                  print_status("kto_check_init");
                  return 1;
               }
               break;

            case 't':
               action=TEST;
               break;

            case 'v':
               GET_OPTARG;
               verbose=atoi(optarg);
               break;

            case 'm':   /* schon fertig */
               break;

            case 'z':
               action=GENERATE_ZWECK;
               break;

            case '?':
            case 'h':
               print_help();
               exit(0);
               break;

            default:
               fprintf(stderr,"Ungültige Option %s (ignoriert)\n",argv[i]);
               break;
         }
      }
      else{
         len=strlen(ptr=argv[i]);
         switch(action){
            case IBAN2BIC:
               ptr=iban2bic(argv[i],&ret,blz=buffer,kto=buffer+10);
               print_status("iban2bic");
               printf(" BIC: %s, BLZ: %s, Kto: %s\n",ptr,blz,kto);
               break;

            case GENERATE_ZWECK:
               ret=ipi_gen(argv[i],buffer,NULL);
               print_status("gen_zweck");
               printf(" %s\n",buffer);
               break;

            default:
            case TEST:
               if(len==8){
                     /* weitere Infos zur Bank holen */
                  ret=lut_multiple(blz=argv[i],NULL,NULL,&name,&name_kurz,&plz,&ort,NULL,&bic,
                        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);

                     /* im Fehlerfall wird u.U. für die Felder NULL zurückgegeben; das muß
                      * auf ein Dummy-Array umgelenkt werden, damit das *var in
                      * printf() keinen Lesezugriff auf einen NULL-Pointer macht
                      */
                  *dummy="";
                  *di=0;
                  if(!plz)plz=di;
                  if(!name)name=dummy;
                  if(!name_kurz)name_kurz=dummy;
                  if(!ort)ort=dummy;
                  if(!bic)bic=dummy;

                     /* nun alles ausgeben */
                  print_status("Bankinfo");
                  printf(" %s %d %s, Kurzname %s, BIC %s\n",
                        *name,*plz,*ort,*name_kurz,*bic);
                  break;
               }
               else if(len==20){
                  ret=ipi_check(argv[i]);
                  printf("Test Zweck %s",argv[i]);
                  print_status_nl("");
               }
               else if(len>20){  /* etwas willkürlich (Papierform wird nur für IBAN akzeptiert */
                  ret=iban_check(argv[i],&ret2);
                  printf("Test IBAN %s",argv[i]);
                  print_status("");
                  ret=ret2;
                  print_status_nl(" KC");

               }
               else{ /* 8 Stellen BLZ, 1 Stelle delimiter, maximal 10 Stellen Kto => 10..19 Byte */
                  for(ptr=argv[i];isalnum(*ptr);ptr++);
                  delimiter=*ptr;
                  *ptr++=0;
                  switch(delimiter){
                     case ':':
                        ret=kto_check_pz(argv[i],ptr,NULL);
                        *--ptr=delimiter;
                        printf("Test PZ/Kto. %s",argv[i]);
                        print_status_nl("");
                        break;
                     case '@':
                        ret=kto_check_blz(ptr,argv[i]);
                        *--ptr=delimiter;
                        printf("Test Kto/BLZ %s",argv[i]);
                        print_status_nl("");
                        break;
                     case '+':
                        ret=kto_check_blz(argv[i],ptr);
                        *--ptr=delimiter;
                        printf("Test BLZ/Kto %s",argv[i]);
                        print_status_nl("");
                        break;
                     default:
                        break;
                  }
               }
               break;
         }
      }

   }
   return 0;
}
