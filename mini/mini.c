#include <stdio.h>
#include "konto_check.h"

int main(int argc,char **argv)
{
   char blz[16],kto[16],buffer[256],*name,*ort,*retval_txt;
   int retval,r1,plz;
   FILE *in,*out;

   if(argc<2)return 1;
   if(!(in=fopen(argv[1],"r")))return 2;
   if(!(out=fopen(argv[2],"w")))return 3;
   if((retval=lut_init("blz.lut2",5,0))!=OK && retval!=LUT2_PARTIAL_OK){  /* Bibliothek initialisieren */

         /* Rückgabewert als Klartext ausgeben */
      fprintf(stderr,"lut_init: %d / %s\n",retval,kto_check_retval2txt(retval));
      return 4;
   }

   while(!feof(in)){
      fgets(buffer,256,in); /* Datei zeilenweise einlesen */
      if(sscanf(buffer,"%s %s",blz,kto)<2 || feof(in))continue;
      retval=kto_check_blz(blz,kto);            /* Bankverbindung testen */
      retval_txt=kto_check_retval2txt(retval);  /* Rückgabewert als Klartext ausgeben */
      name=lut_name(blz,0,NULL);                /* Banknamen holen */
      plz=lut_plz(blz,0,NULL);                  /* PLZ holen */
      ort=lut_ort(blz,0,NULL);                  /* Ort holen */
      if(retval>=OK)
         fprintf(out,"%s %s: %s; %s, %d %s\n",blz,kto,retval_txt,name,plz,ort);
      else
         fprintf(out,"%s %s: %s\n",blz,kto,retval_txt);
   }
   lut_cleanup(); /* Speicher wieder freigeben */
}
