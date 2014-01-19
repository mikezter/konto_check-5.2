/*
 * ##########################################################################
 * #  Dies ist der awk-Port von konto_check. Der C-Code wurde größtenteils  #
 * #  aus dem Anhang "C.3 Adding New Built-in Functions to gawk" aus dem    #
 * #  Buch "GAWK: Effective AWK Programming" von Arnold Robbins übernommen. #
 * #  Dieses Buch ist in der awk-Distribution enthalten; die PDF-Version    #
 * #  kann mit dem Befehl "make pdf" im doc-Verzeichnis erzeugt werden.     #
 * #                                                                        #
 * #  Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>           #
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
 * #  beliebig kommerziell verwertet werden. Die Offenlegung des Sourcecodes#
 * #  bezieht sich bei der LGPL *nur* auf geänderten Bibliothekscode.       #
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
 * # im Internet herunterladen.                                             #
 * #                                                                        #
 * ##########################################################################
 */

#include "awk.h"
#include "konto_check.h"

/* do_lut_init - Initialisierung von konto_check.
 * Als Parameter sind nur der LUT-Name und der Level vorgesehen.
 * Die Initialisierung wird allerdings auch schon beim Laden
 * der Bibliothek implizit gemacht (in der Funktion dlload() ).
 */
static NODE* do_lut_init(NODE *tree)
{
    NODE *lut_file,*level;
    int ret;
    char *name;

    if (do_lint && get_curfunc_arg_count() != 2)
        lintwarn("lut_init: called with incorrect number of arguments");

    lut_file = get_scalar_argument(tree,0,0);
    level = get_scalar_argument(tree,1,0);
    force_string(lut_file);
    force_number(level);
    ret=lut_init(lut_file->stptr,(int)level->numbr,0);
    free_temp(lut_file);
    free_temp(level);

       /* Set the return value */
    set_value(tmp_number((AWKNUM)ret));
       /* Just to make the interpreter happy */
    return tmp_number((AWKNUM) 0);
}

/* do_lut_free - Speicher der von konto_check benutzt wurde, freigeben
 */
static NODE* do_lut_free(NODE *tree)
{
    if (do_lint && get_curfunc_arg_count() > 0)
        lintwarn("lut_free: called with incorrect number of arguments");

       /* Set the return value */
    set_value(tmp_number((AWKNUM)lut_cleanup()));
       /* Just to make the interpreter happy */
    return tmp_number((AWKNUM) 0);
}

/*  do_konto_check: Kontonummer testen */
static NODE* do_konto_check(NODE *tree)
{
    NODE *blz,*kto;
    int ret;

    if (do_lint && get_curfunc_arg_count() != 2)
        lintwarn("konto_check: called with incorrect number of arguments");

    blz = get_scalar_argument(tree,0,0);
    kto = get_scalar_argument(tree,1,0);
    force_string(blz);
    force_string(kto);
    ret=kto_check(blz->stptr,kto->stptr,NULL);
    free_temp(blz);
    free_temp(kto);

    set_value(tmp_number((AWKNUM)ret));
    return tmp_number((AWKNUM) 0);
}

/*  do_bank_valid: testen ob eine BLZ gültig ist
 *  Die LUT-Routinen für den AWK-Port arbeiten nur mit den Hauptstellen,
 *  der Parameter für die Nebenstellen wird immer auf 0 gesetzt.
 */
static NODE* do_bank_valid(NODE *tree)
{
    NODE *blz;
    int ret;

    if (do_lint && get_curfunc_arg_count() != 1)
        lintwarn("bank_name: called with incorrect number of arguments");

    blz = get_scalar_argument(tree,0,0);
    force_string(blz);
    ret=lut_blz(blz->stptr,0);
    if(ret==LUT2_BLZ_NOT_INITIALIZED){
       lut_init(NULL,7,0);
       ret=lut_blz(blz->stptr,0);
    }
    free_temp(blz);

    set_value(tmp_number((AWKNUM)ret));
    return tmp_number((AWKNUM) 0);
}
 	
/*  do_bank_name: Banknamen zu einer BLZ bestimmen */
static NODE* do_bank_name(NODE *tree)
{
    NODE *blz;
    int ret;
    char *name;

    if (do_lint && get_curfunc_arg_count() != 1)
        lintwarn("bank_name: called with incorrect number of arguments");

    blz = get_scalar_argument(tree,0,0);
    force_string(blz);
    name=lut_name(blz->stptr,0,&ret);
    if(ret==LUT2_NAME_NOT_INITIALIZED){
       lut_init(NULL,7,0);
       name=lut_name(blz->stptr,0,NULL);
    }
    free_temp(blz);

    set_value(tmp_string(name,strlen(name)));
    return tmp_number((AWKNUM) 0);
}

/*  do_bank_name_kurz: Kurzbezeichnung der Bank zu einer BLZ bestimmen */
static NODE* do_bank_name_kurz(NODE *tree)
{
    NODE *blz;
    int ret;
    char *name;

    if (do_lint && get_curfunc_arg_count() != 1)
        lintwarn("bank_name_kurz: called with incorrect number of arguments");

    blz = get_scalar_argument(tree,0,0);
    force_string(blz);
    name=lut_name_kurz(blz->stptr,0,&ret);
    if(ret==LUT2_NAME_KURZ_NOT_INITIALIZED){
       lut_init(NULL,7,0);
       name=lut_name_kurz(blz->stptr,0,NULL);
    }
    free_temp(blz);

    set_value(tmp_string(name,strlen(name)));
    return tmp_number((AWKNUM) 0);
}
 	
/*  do_bank_bic: BIC zu einer BLZ bestimmen */
static NODE* do_bank_bic(NODE *tree)
{
    NODE *blz;
    int ret;
    char *bic;

    if (do_lint && get_curfunc_arg_count() != 1)
        lintwarn("bank_bic: called with incorrect number of arguments");

    blz = get_scalar_argument(tree,0,0);
    force_string(blz);
    bic=lut_bic(blz->stptr,0,&ret);
    if(ret==LUT2_BIC_NOT_INITIALIZED){
       lut_init(NULL,7,0);
       bic=lut_bic(blz->stptr,0,NULL);
    }
    free_temp(blz);

    set_value(tmp_string(bic,strlen(bic)));
    return tmp_number((AWKNUM) 0);
}

/*  do_bank_plz: PLZ der Hauptstelle einer Bank suchen. */
static NODE* do_bank_plz(NODE *tree)
{
    NODE *blz;
    int ret,plz;

    if (do_lint && get_curfunc_arg_count() != 1)
        lintwarn("bank_plz: called with incorrect number of arguments");

    blz = get_scalar_argument(tree,0,0);
    force_string(blz);
    plz=lut_plz(blz->stptr,0,&ret);
    if(ret==LUT2_PLZ_NOT_INITIALIZED){
       lut_init(NULL,7,0);
       plz=lut_plz(blz->stptr,0,NULL);
    }
    free_temp(blz);

    set_value(tmp_number((AWKNUM)plz));
    return tmp_number((AWKNUM) 0);
}
 	
/*  do_bank_ort: Ort des Hauptsitzes einer Bank bestimmen */
static NODE* do_bank_ort(NODE *tree)
{
    NODE *blz;
    int ret;
    char *ort;

    if (do_lint && get_curfunc_arg_count() != 1)
        lintwarn("bank_ort: called with incorrect number of arguments");

    blz = get_scalar_argument(tree,0,0);
    force_string(blz);
    ort=lut_ort(blz->stptr,0,&ret);
    if(ret==LUT2_ORT_NOT_INITIALIZED){
       lut_init(NULL,7,0);
       ort=lut_ort(blz->stptr,0,NULL);
    }
    free_temp(blz);

    set_value(tmp_string(ort,strlen(ort)));
    return tmp_number((AWKNUM) 0);
}
 	
/*  do_bank_pz: Prüfzifferberechnungsmethode für eine BLZ bestimmen */
static NODE* do_bank_pz(NODE *tree)
{
    NODE *blz;
    int ret,pz;

    if (do_lint && get_curfunc_arg_count() != 1)
        lintwarn("bank_pz: called with incorrect number of arguments");

    blz = get_scalar_argument(tree,0,0);
    force_string(blz);
    pz=lut_pz(blz->stptr,0,&ret);
    if(ret==LUT2_PZ_NOT_INITIALIZED){
       lut_init(NULL,7,0);
       pz=lut_pz(blz->stptr,0,NULL);
    }
    free_temp(blz);

    set_value(tmp_number((AWKNUM)pz));
    return tmp_number((AWKNUM) 0);
}
 	
/*  do_retval2txt: Rückgabewert in Text umwandeln */
static NODE* do_retval2txt(NODE *tree)
{
    NODE *status;
    int ret;
    char *name;

    if (do_lint && get_curfunc_arg_count() != 1)
        lintwarn("retval2txt: called with incorrect number of arguments");

    status = get_scalar_argument(tree,0,0);
    force_number(status);
    name=kto_check_retval2txt((int)status->numbr);
    free_temp(status);

    set_value(tmp_string(name,strlen(name)));
    return tmp_number((AWKNUM) 0);
}

/*  do_retval2utf8: Rückgabewert nach UTF-8 umwandeln */
static NODE* do_retval2utf8(NODE *tree)
{
    NODE *status;
    int ret;
    char *name;

    if (do_lint && get_curfunc_arg_count() != 1)
        lintwarn("retval2utf8: called with incorrect number of arguments");

    status = get_scalar_argument(tree,0,0);
    force_number(status);
    name=kto_check_retval2utf8((int)status->numbr);
    free_temp(status);

    set_value(tmp_string(name,strlen(name)));
    return tmp_number((AWKNUM) 0);
}
 	
/* dlload --- load new builtins in this library */
NODE *dlload(NODE *tree,void *dl)
{
    make_builtin("lut_init",do_lut_init,2);
    make_builtin("lut_free",do_lut_free,0);
    make_builtin("konto_check",do_konto_check,2);
    make_builtin("bank_valid",do_bank_valid,1);
    make_builtin("bank_name",do_bank_name,1);
    make_builtin("bank_name_kurz",do_bank_name_kurz,1);
    make_builtin("bank_ort",do_bank_ort,1);
    make_builtin("bank_bic",do_bank_bic,1);
    make_builtin("bank_plz",do_bank_plz,1);
    make_builtin("bank_pz",do_bank_pz,1);
    make_builtin("retval2txt",do_retval2txt,1);
    make_builtin("retval2utf8",do_retval2utf8,1);
    lut_init(NULL,7,0);
    return tmp_number((AWKNUM) 0);
}
