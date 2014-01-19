/*
 * ##########################################################################
 * #  Dies ist der PHP Modul Code für konto_check. Das Modul wurde nach der #
 * #  (sehr guten) Anleitung von Sara Golemon (Extension Writing) aus       #
 * #  http://devzone.zend.com/node/view/id/1021 (...1024) geschrieben.      #
 * #                                                                        #
 * #  Copyright (C) 2008-2009 Michael Plugge <m.plugge@hs-mannheim.de>      #
 * ##########################################################################
 *
 * ##########################################################################
 * #  Dieses Programm ist freie Software; Sie dürfen es unter den           #
 * #  Bedingungen der GNU Lesser General Public License, wie von der Free   #
 * #  Software Foundation veröffentlicht, weiterverteilen und/oder          #
 * #  modifizieren; entweder gemäß Version 2.1 der Lizenz oder (nach Ihrer  #
 * #  Option) jeder späteren Version.                                       #
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

#include <php.h>
#include <php_ini.h>
#include "php_konto_check.h"

#if BESCHREIBUNG_TXT
#include "methoden_txt.c"
#endif

#ifndef SYMBOLIC_RETVALS
#define SYMBOLIC_RETVALS 0
#endif

#define INIT_DEFAULT_LUT_FILE INI_STR("konto_check.default_lut_file")
#define IMPLEMENTED_PZ_METHODEN "00 - E1"

#define ADD_ASSOC_STRING(dst,key,string,duplicate) do{if(string)add_assoc_string(dst,key,string,duplicate); else add_assoc_null(dst,key);}while(0)

   /* das folgende Makro wird vor der Rückgabe von Variablen aufgerufen, die
    * per reference übergeben wurden. Falls diese Variablen einen komplexen
    * Datentyp enthalten (String, Array, ...) müssen sie vor der Benutzung
    * gelöscht werden, um den entsprechenden Speicher freizugeben (sonst gibt
    * es ein Speicherleck).
    */
#define ZVAL_DTOR(var) do switch(Z_TYPE_P(var)){ \
   case IS_NULL: \
   case IS_BOOL: \
   case IS_LONG: \
   case IS_DOUBLE: break; \
   default: zval_dtor(var); break; \
}while(0)


   /* Momentan (Februar 10) scheint es kein Speicherleck mehr zugeben. Daher
    * könnte PHP_MALLOC wieder auf 1 gesetzt werden.
    *
    * Falls dieses Makro auf 1 gesetzt wird, wird von konto_check allokierter
    * Speicher nach Beendigung des Skriptes von PHP freigegeben und wieder
    * verwendet; falls jedoch noch eine konto_check Variable darauf verweist
    * und den entsprechenden Speicher benutzt, kommt es (im besten Fall!!) zum
    * Absturz von PHP, oder unkontrolliertem Verhalten (durch mehrfache
    * Verwendung von Speicher); das zeigt sich dadurch, daß (fremde) Variablen
    * modifiziert werden oder eigenartige interne PHP-Fehler auftreten.
    *
    * Bei dem C-Programm in der Version 2.99 (!!!) meldet sowohl duma als auch
    * valgrind, daß alle allokierten Blocks wieder freigegeben wurden; in 2.98
    * wurden einige Blocks nicht freigegeben und verursachten dadurch Probleme.
    * Mit dem eigenen Speichertest wurden noch einige fehlende Speicherlecks
    * aufgespürt; aktuell (Februar 10, Version 3.0/3.1) sind keine Lecks mehr
    * bekannt. 
    */
#define PHP_MALLOC 0
#include "../konto_check.c"

static int search_lutfile(char *name);
#if PHP_MAJOR_VERSION==5 && PHP_MINOR_VERSION>=3
#define STATIC
#else
#define STATIC static
#endif

#ifdef ZEND_ENGINE_2
STATIC ZEND_BEGIN_ARG_INFO(byref_0,1)
ZEND_END_ARG_INFO()

STATIC ZEND_BEGIN_ARG_INFO(byref_1,1)
   ZEND_ARG_PASS_INFO(0)
ZEND_END_ARG_INFO()

STATIC ZEND_BEGIN_ARG_INFO(byref_11,1)
   ZEND_ARG_PASS_INFO(0)
   ZEND_ARG_PASS_INFO(1)
   ZEND_ARG_PASS_INFO(0)
ZEND_END_ARG_INFO()

STATIC ZEND_BEGIN_ARG_INFO(byref_2,1)
   ZEND_ARG_PASS_INFO(0)
   ZEND_ARG_PASS_INFO(0)
ZEND_END_ARG_INFO()

STATIC ZEND_BEGIN_ARG_INFO(byref_3,1)
   ZEND_ARG_PASS_INFO(0)
   ZEND_ARG_PASS_INFO(0)
   ZEND_ARG_PASS_INFO(0)
ZEND_END_ARG_INFO()

STATIC ZEND_BEGIN_ARG_INFO(byref_4,1)
   ZEND_ARG_PASS_INFO(0)
   ZEND_ARG_PASS_INFO(0)
   ZEND_ARG_PASS_INFO(0)
   ZEND_ARG_PASS_INFO(0)
ZEND_END_ARG_INFO()

STATIC ZEND_BEGIN_ARG_INFO(byref_131,1)
   ZEND_ARG_PASS_INFO(0)
   ZEND_ARG_PASS_INFO(1)
   ZEND_ARG_PASS_INFO(1)
   ZEND_ARG_PASS_INFO(1)
   ZEND_ARG_PASS_INFO(0)
ZEND_END_ARG_INFO()

STATIC ZEND_BEGIN_ARG_INFO(byref_231,1)
   ZEND_ARG_PASS_INFO(0)
   ZEND_ARG_PASS_INFO(0)
   ZEND_ARG_PASS_INFO(1)
   ZEND_ARG_PASS_INFO(1)
   ZEND_ARG_PASS_INFO(1)
   ZEND_ARG_PASS_INFO(0)
   ZEND_ARG_PASS_INFO(1)
ZEND_END_ARG_INFO()

#else /* ZE 1 */
static unsigned char byref_0[]={1,BYREF_FORCE_REST};
static unsigned char byref_1[]={2,BYREF_NONE,BYREF_FORCE_REST};
static unsigned char byref_11[]={2,BYREF_NONE,BYREF_FORCE,BYREF_NONE,BYREF_FORCE_REST};
static unsigned char byref_2[]={3,BYREF_NONE,BYREF_NONE,BYREF_FORCE_REST};
static unsigned char byref_3[]={4,BYREF_NONE,BYREF_NONE,BYREF_NONE,BYREF_FORCE_REST};
static unsigned char byref_4[]={5,BYREF_NONE,BYREF_NONE,BYREF_NONE,BYREF_NONE,BYREF_FORCE_REST};
static unsigned char byref_131[]={5,BYREF_NONE,BYREF_FORCE,BYREF_FORCE,BYREF_FORCE,BYREF_NONE};
static unsigned char byref_231[]={5,BYREF_NONE,BYREF_NONE,BYREF_FORCE,BYREF_FORCE,BYREF_FORCE,BYREF_NONE,BYREF_FORCE_REST};
#endif

#if !defined(function_entry)  /* ab PHP 5.4 (?) neues typedef */
#define FUNCTION_ENTRY zend_function_entry
#else
#define FUNCTION_ENTRY function_entry
#endif

static FUNCTION_ENTRY konto_check_functions[]={
   PHP_FE(kto_check,NULL)
   PHP_FE(kto_check_str,NULL)
   PHP_FE(lut_init,byref_3)
   PHP_FE(kto_check_init,byref_4)
   PHP_FE(generate_lut2,NULL)
   PHP_FE(current_lutfile_name,byref_0)
   PHP_FE(read_lut_block,byref_2)
   PHP_FE(write_lut_block,NULL)
   PHP_FE(copy_lutfile,NULL)
   PHP_FE(kto_check_pz,NULL)
   PHP_FE(kto_check_blz,NULL)
   PHP_FE(kto_check_pz_dbg,byref_3)
   PHP_FE(kto_check_regel_dbg,byref_2)
   PHP_FE(kto_check_blz_dbg,byref_2)
   PHP_FE(kto_check_retval,NULL)
   PHP_FE(keep_raw_data,NULL)
   PHP_FE(kto_check_encoding,NULL)
   PHP_FE(kto_check_encoding_str,NULL)
   PHP_FE(kto_check_retval2txt,NULL)
   PHP_FE(kto_check_retval2iso,NULL)
   PHP_FE(kto_check_retval2html,NULL)
   PHP_FE(kto_check_retval2txt_short,NULL)
   PHP_FE(kto_check_retval2dos,NULL)
   PHP_FE(kto_check_retval2utf8,NULL)
   PHP_FE(get_kto_check_version,NULL)
   PHP_FE(malloc_report,NULL)
   PHP_FE(malloc_cnt,NULL)
   PHP_FE(set_default_compression,NULL)
   PHP_FE(iban_gen,byref_2)
   PHP_FE(iban_check,byref_1)
   PHP_FE(ci_check,byref_1)
   PHP_FE(iban2bic,byref_1)
   PHP_FE(ipi_gen,byref_1)
   PHP_FE(ipi_check,byref_1)
   PHP_FE(lut_cleanup,NULL)
   PHP_FE(lut_filialen,NULL)
   PHP_FE(lut2_status,NULL)
   PHP_FE(lut_valid,NULL)
   PHP_FE(lut_multiple,byref_2)
   PHP_FE(lut_info,byref_1)
   PHP_FE(lut_blz,byref_1)
   PHP_FE(lut_blocks,byref_1)
   PHP_FE(pz2str,byref_1)
   PHP_FE(lut_methode_txt,byref_11)
   PHP_FE(lut_suche_volltext,byref_231)
   PHP_FE(lut_suche_init,NULL)
   PHP_FE(lut_suche_free,NULL)
   PHP_FE(lut_suche_set,NULL)
   PHP_FE(lut_suche,byref_2)
   PHP_FE(lut_suche_multiple,byref_3)
   PHP_FE(lut_name,byref_11)
   PHP_FE(lut_name_kurz,byref_11)
   PHP_FE(lut_plz,byref_11)
   PHP_FE(lut_ort,byref_11)
   PHP_FE(lut_pan,byref_11)
   PHP_FE(lut_bic,byref_11)
   PHP_FE(lut_nr,byref_11)
   PHP_FE(lut_pz,byref_11)
   PHP_FE(lut_nachfolge_blz,byref_11)
   PHP_FE(lut_aenderung,byref_11)
   PHP_FE(lut_loeschung,byref_11)
   PHP_FE(lut_iban_regel,byref_11)
   PHP_FE(lut_suche_bic,byref_131)
   PHP_FE(lut_suche_namen,byref_131)
   PHP_FE(lut_suche_namen_kurz,byref_131)
   PHP_FE(lut_suche_ort,byref_131)
   PHP_FE(lut_suche_pz,byref_231)
   PHP_FE(lut_suche_blz,byref_231)
   PHP_FE(lut_suche_plz,byref_231)
   PHP_FE(lut_suche_regel,byref_231)
   PHP_FALIAS(lut_status,lut2_status,NULL)
   PHP_FALIAS(lut_free,lut_cleanup,NULL)
   PHP_FALIAS(kc_short,kto_check_retval2txt_short,NULL)
   PHP_FALIAS(kc_txt,kto_check_retval2txt,NULL)
   PHP_FALIAS(kc_html,kto_check_retval2html,NULL)
   PHP_FALIAS(kc_dos,kto_check_retval2dos,NULL)
   PHP_FALIAS(kc_utf8,kto_check_retval2utf8,NULL)
   PHP_FALIAS(kto_check_version,get_kto_check_version,NULL)
   {NULL, NULL, NULL}
};

zend_module_entry konto_check_module_entry={
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_KONTO_CHECK_EXTNAME,
    konto_check_functions,
    PHP_MINIT(konto_check),
    PHP_MSHUTDOWN(konto_check),
#if USE_RINIT || CHECK_MALLOC
    PHP_RINIT(konto_check),
#else
    NULL,
#endif
#if USE_RSHUTDOWN
    PHP_RSHUTDOWN(konto_check),
#else
    NULL,
#endif
    PHP_MINFO(konto_check),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_KONTO_CHECK_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

PHP_INI_BEGIN()
PHP_INI_ENTRY("konto_check.default_lut_file", "/etc/blz.lut", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("konto_check.lut_name1", "blz.lut", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("konto_check.lut_name2", "blz.lut2", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("konto_check.lut_name3", "blz.lut2f", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("konto_check.lut_path1", ".", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("konto_check.lut_path2", "/usr/local/etc", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("konto_check.lut_path3", "/etc", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("konto_check.request_auto_init", "0", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("konto_check.request_auto_cleanup", "0", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("konto_check.request_init_default_level", "0", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("konto_check.init_default_level", "5", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("konto_check.check_malloc", "0", PHP_INI_ALL, NULL)
PHP_INI_ENTRY("konto_check.uniq", "2", PHP_INI_ALL, NULL)
PHP_INI_END()

#if USE_RINIT || CHECK_MALLOC
PHP_RINIT_FUNCTION(konto_check)
{
   int level;

#if CHECK_MALLOC
   if(malloc_entry_cnt_new() && INI_INT("konto_check.check_malloc")){
      fprintf(stderr,"\n####### konto_check Speicherproblem in PHP_RINIT_FUNCTION() ####### \n");
      malloc_report(1);
      fflush(stderr);
   }
#endif

#if USE_RINIT
      /* nur initialisieren, falls per INI-Wert freigegeben (das wird sonst bei
       * jedem Request gemacht, nicht nur, falls konto_check benötigt wird)
       */
   if(INI_INT("konto_check.request_auto_init")>0){
      level=INI_INT("konto_check.request_init_default_level");
      kto_check_init_p(INIT_DEFAULT_LUT_FILE,level,0,0);
   }
#endif
   return SUCCESS;
}
#endif

#if USE_RSHUTDOWN
PHP_RSHUTDOWN_FUNCTION(konto_check)
{
   if(INI_INT("konto_check.request_auto_cleanup") && (init_status&7)==7)lut_cleanup();   /* allokierten Speicher freigeben */
#if CHECK_MALLOC
   if(malloc_entry_cnt_new() && INI_INT("konto_check.check_malloc")){
      fprintf(stderr,"\n####### konto_check Speicherproblem in PHP_RSHUTDOWN_FUNCTION() ####### \n");
      malloc_report(1);
      fflush(stderr);
   }
#endif
   return SUCCESS;
}
#endif

PHP_MINIT_FUNCTION(konto_check)
{
   REGISTER_INI_ENTRIES();
#if SYMBOLIC_RETVALS
   REGISTER_LONG_CONSTANT("IBAN_CHKSUM_OK_NACHFOLGE_BLZ_DEFINED",-140,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NOT_ALL_IBAN_BLOCKS_LOADED",-139,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NOT_YET_VALID_PARTIAL_OK",-138,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NO_LONGER_VALID_PARTIAL_OK",-137,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_BLOCKS_MISSING",-136,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("FALSE_UNTERKONTO_ATTACHED",-135,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("BLZ_BLACKLISTED",-134,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("BLZ_MARKED_AS_DELETED",-133,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IBAN_CHKSUM_OK_SOMETHING_WRONG",-132,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IBAN_CHKSUM_OK_NO_IBAN_CALCULATION",-131,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IBAN_CHKSUM_OK_RULE_IGNORED",-130,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IBAN_CHKSUM_OK_UNTERKTO_MISSING",-129,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IBAN_INVALID_RULE",-128,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IBAN_AMBIGUOUS_KTO",-127,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IBAN_RULE_NOT_IMPLEMENTED",-126,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IBAN_RULE_UNKNOWN",-125,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("NO_IBAN_CALCULATION",-124,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OLD_BLZ_OK_NEW_NOT",-123,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_IBAN_REGEL_NOT_INITIALIZED",-122,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_IBAN_LENGTH",-121,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NO_ACCOUNT_GIVEN",-120,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_VOLLTEXT_INVALID_CHAR",-119,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_VOLLTEXT_SINGLE_WORD_ONLY",-118,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT_SUCHE_INVALID_RSC",-117,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT_SUCHE_INVALID_CMD",-116,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT_SUCHE_INVALID_CNT",-115,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_VOLLTEXT_NOT_INITIALIZED",-114,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("NO_OWN_IBAN_CALCULATION",-113,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("KTO_CHECK_UNSUPPORTED_COMPRESSION",-112,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("KTO_CHECK_INVALID_COMPRESSION_LIB",-111,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_UNTERKONTO_ATTACHED_OLD",-110,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("KTO_CHECK_DEFAULT_BLOCK_INVALID",-109,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("KTO_CHECK_DEFAULT_BLOCK_FULL",-108,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("KTO_CHECK_NO_DEFAULT_BLOCK",-107,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("KTO_CHECK_KEY_NOT_FOUND",-106,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NO_LONGER_VALID_BETTER",-105,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_SRC_KTO_DIFFERENT",-104,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_SRC_BLZ_DIFFERENT",-103,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_CR_LF_IN_FILE",-102,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_INVALID_C_EXTENSION",-101,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_FOUND_SET_A_NOT_C",-100,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_FOUND_SET_E_NOT_C",-99,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_FOUND_SET_C_NOT_EXTENSION",-98,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_FOUND_SET_E_NOT_EXTENSION",-97,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_INVALID_EXTENSION_COUNT",-96,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_INVALID_NUM",-95,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_INVALID_CHARS",-94,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_CURRENCY_NOT_EURO",-93,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_EMPTY_AMOUNT",-92,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_INVALID_TEXT_KEY",-91,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_EMPTY_STRING",-90,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_MARKER_A_NOT_FOUND",-89,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_MARKER_C_NOT_FOUND",-88,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_MARKER_E_NOT_FOUND",-87,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_INVALID_SET_C_LEN",-86,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_INVALID_SET_LEN",-85,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_WAERUNG_NOT_EURO",-84,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_INVALID_ISSUE_DATE",-83,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_INVALID_DATE",-82,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_FORMAT_ERROR",-81,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_FILE_WITH_ERRORS",-80,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_SEARCH_RANGE",-79,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("KEY_NOT_FOUND",-78,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("BAV_FALSE",-77,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NO_USER_BLOCK",-76,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_SET",-75,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("NO_GERMAN_BIC",-74,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IPI_CHECK_INVALID_LENGTH",-73,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IPI_INVALID_CHARACTER",-72,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IPI_INVALID_LENGTH",-71,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT1_FILE_USED",-70,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("MISSING_PARAMETER",-69,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IBAN2BIC_ONLY_GERMAN",-68,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("IBAN_OK_KTO_NOT",-67,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("KTO_OK_IBAN_NOT",-66,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("TOO_MANY_SLOTS",-65,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INIT_FATAL_ERROR",-64,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INCREMENTAL_INIT_NEEDS_INFO",-63,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INCREMENTAL_INIT_FROM_DIFFERENT_FILE",-62,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DEBUG_ONLY_FUNCTION",-61,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_INVALID",-60,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NOT_YET_VALID",-59,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NO_LONGER_VALID",-58,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_GUELTIGKEIT_SWAPPED",-57,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_INVALID_GUELTIGKEIT",-56,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_INDEX_OUT_OF_RANGE",-55,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_INIT_IN_PROGRESS",-54,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_BLZ_NOT_INITIALIZED",-53,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_FILIALEN_NOT_INITIALIZED",-52,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NAME_NOT_INITIALIZED",-51,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_PLZ_NOT_INITIALIZED",-50,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_ORT_NOT_INITIALIZED",-49,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NAME_KURZ_NOT_INITIALIZED",-48,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_PAN_NOT_INITIALIZED",-47,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_BIC_NOT_INITIALIZED",-46,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_PZ_NOT_INITIALIZED",-45,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NR_NOT_INITIALIZED",-44,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_AENDERUNG_NOT_INITIALIZED",-43,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_LOESCHUNG_NOT_INITIALIZED",-42,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NACHFOLGE_BLZ_NOT_INITIALIZED",-41,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NOT_INITIALIZED",-40,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_FILIALEN_MISSING",-39,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_PARTIAL_OK",-38,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_Z_BUF_ERROR",-37,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_Z_MEM_ERROR",-36,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_Z_DATA_ERROR",-35,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_BLOCK_NOT_IN_FILE",-34,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_DECOMPRESS_ERROR",-33,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_COMPRESS_ERROR",-32,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_FILE_CORRUPTED",-31,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NO_SLOT_FREE",-30,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("UNDEFINED_SUBMETHOD",-29,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("EXCLUDED_AT_COMPILETIME",-28,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_LUT_VERSION",-27,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_PARAMETER_STELLE1",-26,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_PARAMETER_COUNT",-25,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_PARAMETER_PRUEFZIFFER",-24,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_PARAMETER_WICHTUNG",-23,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_PARAMETER_METHODE",-22,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LIBRARY_INIT_ERROR",-21,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT_CRC_ERROR",-20,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("FALSE_GELOESCHT",-19,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_NO_CHK_GELOESCHT",-18,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_GELOESCHT",-17,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("BLZ_GELOESCHT",-16,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_BLZ_FILE",-15,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LIBRARY_IS_NOT_THREAD_SAFE",-14,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("FATAL_ERROR",-13,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_KTO_LENGTH",-12,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("FILE_WRITE_ERROR",-11,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("FILE_READ_ERROR",-10,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("ERROR_MALLOC",-9,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("NO_BLZ_FILE",-8,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_LUT_FILE",-7,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("NO_LUT_FILE",-6,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_BLZ_LENGTH",-5,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_BLZ",-4,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("INVALID_KTO",-3,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("NOT_IMPLEMENTED",-2,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("NOT_DEFINED",-1,CONST_CS|CONST_PERSISTENT);
      /* FALSE wird hier als KC_FALSE definiert, um nicht den PHP-Wert FALSE zu überschreiben */
   REGISTER_LONG_CONSTANT("KC_FALSE",0,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK",1,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_NO_CHK",2,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_TEST_BLZ_USED",3,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_VALID",4,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NO_VALID_DATE",5,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT1_SET_LOADED",6,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT1_FILE_GENERATED",7,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("DTA_FILE_WITH_WARNINGS",8,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT_V2_FILE_GENERATED",9,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("KTO_CHECK_VALUE_REPLACED",10,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_UNTERKONTO_POSSIBLE",11,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_UNTERKONTO_GIVEN",12,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_SLOT_CNT_MIN_USED",13,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("SOME_KEYS_NOT_FOUND",14,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_KTO_NOT_CHECKED",15,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_OK_WITHOUT_IBAN_RULES",16,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_NACHFOLGE_BLZ_USED",17,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_KTO_REPLACED",18,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_BLZ_REPLACED",19,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_BLZ_KTO_REPLACED",20,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_IBAN_WITHOUT_KC_TEST",21,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_INVALID_FOR_IBAN",22,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_HYPO_REQUIRES_KTO",23,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_KTO_REPLACED_NO_PZ",24,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("OK_UNTERKONTO_ATTACHED",25,CONST_CS|CONST_PERSISTENT);

   REGISTER_LONG_CONSTANT("LUT2_BLZ",1,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_FILIALEN",2,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NAME",3,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_PLZ",4,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_ORT",5,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NAME_KURZ",6,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_PAN",7,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_BIC",8,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_PZ",9,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NR",10,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_AENDERUNG",11,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_LOESCHUNG",12,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NACHFOLGE_BLZ",13,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NAME_NAME_KURZ",14,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_INFO",15,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_BIC_SORT",16,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NAME_SORT",17,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_NAME_KURZ_SORT",18,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_ORT_SORT",19,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_PLZ_SORT",20,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_PZ_SORT",21,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_OWN_IBAN",22,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_VOLLTEXT_TXT",23,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_VOLLTEXT_IDX",24,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_IBAN_REGEL",25,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT2_IBAN_REGEL_SORT",26,CONST_CS|CONST_PERSISTENT);

   REGISTER_LONG_CONSTANT("LUT_SUCHE_VOLLTEXT",LUT_SUCHE_VOLLTEXT,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT_SUCHE_BIC",LUT_SUCHE_BIC,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT_SUCHE_NAMEN",LUT_SUCHE_NAMEN,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT_SUCHE_NAMEN_KURZ",LUT_SUCHE_NAMEN_KURZ,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT_SUCHE_ORT",LUT_SUCHE_ORT,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT_SUCHE_BLZ",LUT_SUCHE_BLZ,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT_SUCHE_PLZ",LUT_SUCHE_PLZ,CONST_CS|CONST_PERSISTENT);
   REGISTER_LONG_CONSTANT("LUT_SUCHE_PZ",LUT_SUCHE_PZ,CONST_CS|CONST_PERSISTENT);
#endif
   return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(konto_check)
{
   UNREGISTER_INI_ENTRIES();
   return SUCCESS;
}

PHP_MINFO_FUNCTION(konto_check)
{
   char *use_rinit,*use_rinit2,*use_rshutdown,*use_rshutdown2,*check_malloc,*check_malloc2;

#if USE_RINIT || CHECK_MALLOC
   use_rinit="enabled at compile-time";
   if(INI_INT("konto_check.request_auto_init")>0)
      use_rinit2="yes";
   else
      use_rinit2="no";
#else
   use_rinit="disabled at compile-time";
   use_rinit2="no";
#endif
#if USE_RSHUTDOWN
#if CHECK_MALLOC
   check_malloc="enabled at compile-time";
   if(INI_INT("konto_check.check_malloc")>0)
      check_malloc2="yes";
   else
      check_malloc2="no";
#else
   check_malloc="disabled at compile-time";
   check_malloc2="no";
#endif
   use_rshutdown="enabled at compile-time";
   if(INI_INT("konto_check.request_auto_cleanup")>0)
      use_rshutdown2="yes";
   else
      use_rshutdown2="no";
#else
   use_rshutdown="disabled at compile-time";
   use_rinit2="no";
#endif
   php_info_print_table_start();
   php_info_print_table_row(2,"konto_check","enabled");
   php_info_print_table_row(2,"version",VERSION);
   php_info_print_table_row(2,"date",VERSION_DATE);
   php_info_print_table_row(2,"compile date",__DATE__ ", " __TIME__);
   php_info_print_table_row(2,"API version","new");
   php_info_print_table_row(2,"BAV compatible version",BAV_KOMPATIBEL ? "yes":"no");
#if SYMBOLIC_RETVALS
   php_info_print_table_row(2,"symbolic retvals","yes");
#else
   php_info_print_table_row(2,"symbolic retvals","no");
#endif
#if BESCHREIBUNG_TXT
   php_info_print_table_row(2,"description of check methods","yes");
#else
   php_info_print_table_row(2,"description of check methods","no");
#endif
   php_info_print_table_row(2,"check methods",IMPLEMENTED_PZ_METHODEN);
   php_info_print_table_end();

   php_info_print_table_start();
   php_info_print_table_header(2,"Directive","Value");
   php_info_print_table_row(2,"default lut file",INIT_DEFAULT_LUT_FILE);
   php_info_print_table_row(2,"default lut name (1)",INI_STR("konto_check.lut_name1"));
   php_info_print_table_row(2,"default lut name (2)",INI_STR("konto_check.lut_name2"));
   php_info_print_table_row(2,"default lut name (3)",INI_STR("konto_check.lut_name3"));
   php_info_print_table_row(2,"default lut path (1)",INI_STR("konto_check.lut_path1"));
   php_info_print_table_row(2,"default lut path (2)",INI_STR("konto_check.lut_path2"));
   php_info_print_table_row(2,"default lut path (3)",INI_STR("konto_check.lut_path3"));
   php_info_print_table_row(2,"request auto-init",use_rinit);
   php_info_print_table_row(2,"check_malloc debug",check_malloc);
#if USE_RINIT || CHECK_MALLOC
   php_info_print_table_row(2,"use check_malloc debug routines",check_malloc2);
   php_info_print_table_row(2,"use request auto-init",use_rinit2);
   php_info_print_table_row(2,"default request auto-init level",INI_STR("konto_check.request_init_default_level"));
#endif
   php_info_print_table_row(2,"default init level",INI_STR("konto_check.init_default_level"));
   php_info_print_table_row(2,"request auto cleanup",use_rshutdown);
   php_info_print_table_row(2,"use request auto cleanup",use_rshutdown2);
   php_info_print_table_end();
}

#ifdef COMPILE_DL_KONTO_CHECK
ZEND_GET_MODULE(konto_check)
#endif

   /* search_lutfile(): Diese Funktion sucht (physikalisch) eine LUT-Datei;
    * zunächst am angegebenen Ort, falls dort keine Datei gefunden wird, noch
    * zusätzlich mit den Dateinamen lut_name1 ... lut_name3 und den Pfaden
    * lut_path1...lut_path3. Der Parameter name muß ein (schreibbares) Array
    * der Größe LUT_NAME_BUFFER sein; in diesem Array wird der gefundene
    * Dateiname zurückgeliefert.
    *
    * Es wird nicht getestet, ob die gefundene Datei wirklich eine LUT-Datei
    * ist; das wird erst später in der C-Funktion gemacht.
    */
static int search_lutfile(char *name)
{
   char *lut_name[3],*lut_path[3];
   int retval,i,j;
   struct stat sbuf;

   if(!stat(name,&sbuf))return OK;
   lut_name[0]=INI_STR("konto_check.lut_name1");
   lut_name[1]=INI_STR("konto_check.lut_name2");
   lut_name[2]=INI_STR("konto_check.lut_name3");
   lut_path[0]=INI_STR("konto_check.lut_path1");
   lut_path[1]=INI_STR("konto_check.lut_path2");
   lut_path[2]=INI_STR("konto_check.lut_path3");
   for(i=0;i<3;i++)if(strlen(lut_path[i])){
      for(j=0;j<3;j++)if(strlen(lut_name[j])){
         snprintf(name,LUT_NAME_BUFFER,"%s/%s",lut_path[i],lut_name[j]);
         if(!stat(name,&sbuf))return OK;
      }
   }
   return NO_LUT_FILE;  /* keine Datei gefunden */
}

   /* lut_init() und kto_check_init(): die beiden Funktionen sind ähnlich
    * und dienen zur Initialisierung der kto_check Bibliothek. Die Funktion
    * lut_init() testet, ob die Bibliothek bereits von der angegebenen Datei
    * initialisiert wurde und lädt bei Bedarf noch fehlende Blocks nach;
    * falls eine andere Datei (oder ein anderer Datensatz) zur Initialisierung
    * verwendet werden soll, wird eine (Neu-)Initialisierung erzwungen. Die
    * Funktion kto_check_init() des neuen Interfaces ist dagegen wesentlich
    * allgemeiner; sie enthält die komplette Funktionalität der C-Funktion (hat
    * aber leider auch fast die Komplexität der C-Funktion).
    *
    * Die Funktion hat die nachfolgenden Parameter. Alle Parameter sind
    * optional und können über INIT-Werte gesetzt werden. Die Definition kann
    * in dieser Datei, in /etc/php.ini bzw. /etc/php.d/konto_check.ini oder in
    * einer .htaccess Datei für das jeweilige lokale Verzeichnis (sowie
    * Unterverzeichnisse) erfolgen. Die Defaultwerte sind in Klammern
    * angegeben.
    *
    * lut_name:      Name der LUT-Datei (konto_check.default_lut_file -> /etc/blz.lut)
    *
    *                Dieser Parameter kann weggelassen werden; aufgrund des
    *                Typs (String) ist er eindeutig von den anderen (Integer)
    *                zu unterscheiden. Falls als erster Parameter ein
    *                Integerwert angegeben wird, wird dieser als
    *                Initialisierungslevel interpretiert.
    *
    * required:      Blocks, die geladen werden sollen (s.u.; konto_check.init_default_level,
    *                Standard ist 5). Falls die Option konto_check.request_auto_init
    *                gesetzt ist, initialisiert die RINIT Funktion beim Start eines
    *                Skriptes automatisch die Bibliothek entsprechend dem Wert
    *                konto_check.request_init_default_level. Diese
    *                Initialisierung wird dann für jedes PHP-Skript gemacht;
    *                daher sollte die Option nur eingeschaltet werden, wenn sie
    *                wirklich benötigt wird, z.B. für ein bestimmtes
    *                Verzeichnis, bei dem der Test immer benötigt wird.
    *
    * set:           Datensatz der LUT-Datei, der benutzt werden soll; 0 für automatisch
    *                auswählen (nach Datum), sonst 1 oder 2 (Standard ist 0)
    *
    * Liste der Blocks, die für verschiedene Werte von required geladen werden:
    *
    *    0: BLZ, PZ
    *    1: BLZ, PZ, NAME_KURZ
    *    2: BLZ, PZ, NAME_KURZ,                 BIC
    *    3: BLZ, PZ, NAME,            PLZ, ORT
    *    4: BLZ, PZ, NAME,            PLZ, ORT, BIC
    *    5: BLZ, PZ, NAME, NAME_KURZ, PLZ, ORT, BIC
    *    6: BLZ, PZ, NAME, NAME_KURZ, PLZ, ORT, BIC, NACHFOLGE_BLZ
    *    7: BLZ, PZ, NAME, NAME_KURZ, PLZ, ORT, BIC, NACHFOLGE_BLZ, AENDERUNG
    *    8: BLZ, PZ, NAME, NAME_KURZ, PLZ, ORT, BIC, NACHFOLGE_BLZ, AENDERUNG, LOESCHUNG
    *    9: BLZ, PZ, NAME, NAME_KURZ, PLZ, ORT, BIC, NACHFOLGE_BLZ, AENDERUNG, LOESCHUNG, PAN, NR
    */

PHP_FUNCTION(lut_init)
{
   static char *lut_name,buffer[LUT_NAME_BUFFER];
   int have_lutname=0,required,set,ret;
   zval *z_arg1=NULL,*z_arg2=NULL,*z_arg3=NULL,*z_arg4=NULL,*z_used_lutfile=NULL;

   lut_name=INIT_DEFAULT_LUT_FILE;
   required=INI_INT("konto_check.init_default_level");
   set=0;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"|zzzz",
            &z_arg1,&z_arg2,&z_arg3,&z_arg4)==FAILURE)RETURN_NULL();
   if(z_arg1 && Z_TYPE_P(z_arg1)==IS_LONG){   /* Dateiname ausgelassen */
      required=Z_LVAL_P(z_arg1);
      if(z_arg2 && Z_TYPE_P(z_arg2)==IS_LONG)set=Z_LVAL_P(z_arg2);

         /* z_used_lutfile kann hier nicht gesetzt werden, da die drei ersten
          * Parameter by value übergeben werden. Eine Übergabe by reference ist
          * nicht möglich, da für die Parameter oft auch Konstanten verwendet
          * werden; diese lassen sich nicht by reference übergeben.
          */
   }
   else if(z_arg1 && Z_TYPE_P(z_arg1)==IS_STRING){   /* Dateiname angegeben */
      lut_name=Z_STRVAL_P(z_arg1);
      have_lutname=1;
      if(z_arg2 && Z_TYPE_P(z_arg2)==IS_LONG)required=Z_LVAL_P(z_arg2);
      if(z_arg3 && Z_TYPE_P(z_arg3)==IS_LONG)set=Z_LVAL_P(z_arg3);
      z_used_lutfile=z_arg4;
   }
   if(!have_lutname)lut_name=INIT_DEFAULT_LUT_FILE;
   snprintf(buffer,LUT_NAME_BUFFER,lut_name);
   if((ret=search_lutfile(buffer))!=OK){RETURN_LONG(ret);}  /* keine LUT-Datei gefunden */
   ret=lut_init(buffer,required,set);
   if(z_used_lutfile){
      ZVAL_DTOR(z_used_lutfile);
      ZVAL_STRING(z_used_lutfile,buffer,1);
   }
   RETURN_LONG(ret);
}

   /* generate_lut2(): diese Funktion dient zur Generierung einer LUT-Datei.
    *                Die Parameter entsprechen denen der C-Funktion. Alle
    *                Parameter außer inputname und outputname sind optional.
    *                Hier eine kurze Beschreibung:
    *
    * inputname:     Dateiname der Bundesbank-Datei
    *
    * outputname:    Dateiname der generierten LUT-Datei
    *
    * user_info:     Info-Zeile für die Datei (Benutzer-Info)
    *
    * gueltigkeit:   Gültigkeitszeitraum für den Datensatz. Der Gültigkeitszeitraum
    *                ist im Format JJJJMMTT-JJJJMMTT anzugeben, also z.B.
    *                20090309-20090607 für den Zeitraum 9.3.2009 - 6.7.2009.
    *
    * felder:        Diese Variable ist ein Skalar oder Array, in dem die in
    *                die Ausgabedatei aufzunehmenden Felder angegeben werden.
    *                Bei einem skalaren Wert sind die Felder im Anhang von
    *                00liesmich.pdf aufgezählt; bei einem Array kann man explizit
    *                bestimmen, welche Felder in die Ausgabedatei aufgenommen
    *                werden sollen. Falls die LUT-Datei auch die Filialen enthalten
    *                soll, ist zusätzlich zu den Datenblocks noch der Wert
    *                LUT2_FILIALEN in das Array einzufügen; andernfalls werden nur
    *                die Hauptstellen berücksichtigt.
    *
    *                Falls ein negativer skalarer Wert angegeben wird, werden die
    *                Werte des entsprechenden Levels mit den Filialen eingebunen.
    *
    *                Falls der Parameter nicht angegeben wird: Level 5 ohne Filialen
    *
    * slots:         Anzahl Slots im Inhaltsverzeichnis der LUT-Datei. Die Anzahl Slots
    *                kann später nicht mehr geändert werden; wenn alle Slots einer Datei
    *                belegt sind, kann kein zusätzlicher Block mehr geschrieben werden.
    *                Der Defaultwert ist 40.
    *
    *
    * lut_version:   Dateiversion der LUT-Datei, die geschrieben werden soll.
    *                Der Parameter kann die folgenden Werte annehmen:
    *
    *                0: default (aktuelle Version, jetzt 2.0)
    *                1: Version 1.0 (obsolet)
    *                2: Version 1.1 (enthält nur BLZ und Prüfziffermethoden)
    *                3: Version 2.0 (kann alle Felder enthalten)
    *
    * set:           Datensatz, der geschrieben werden soll. Eine LUT-Datei kann zwei
    *                Datensätze mit unterschiedlichem Gültigkeitsdatum enthalten.
    *                Dieser Parameter legt fest, welcher Datensatz geschrieben werden
    *                soll (1 oder 2); Default ist Datensatz 1.
    *
    * iban_file:     Der Parameter iban_file enthält den Dateinamen der Liste von
    *                Banken, die einer IBAN-Berechnung nicht zugestimmt haben; diese
    *                Liste wird in das interne  Format für konto_check konvertiert.
    *                Als Eingabedatei wird die Datei CONFIG.INI des SEPA Account
    *                Converters der Sparkassen benutzt, die Ausgabe wird direkt als
    *                Block in die LUT-Datei geschrieben. Der Block wird automatisch
    *                beim Initialisieren eingelesen und von der Funktion iban_gen()
    *                ausgewertet.
    *
    *                Hier ein Auszug aus der Anleitung des SEPA Account Converters:
    *
    *                Der SEPA Account Converter ist so eingestellt, dass nur
    *                Kontoverbindungen in IBAN und BIC umgerechnet werden, bei denen
    *                das ausgebende Kreditinstitut der Umrechnung zugestimmt hat.
    *                Kreditinstitute, welche einer Umrechnung nicht zugestimmt haben
    *                und welche zum Teil spezielle, dem SEPA Account Converter nicht
    *                bekannte Umrechnungsmethoden verwenden, sind in der Datei
    *                "CONFIG.INI" hinterlegt. Durch Löschen der Datei "CONFIG.INI" aus
    *                dem Programmverzeichnis haben Sie die Möglichkeit, eine
    *                Umrechnung für alle Konten durchzuführen. Bitte beachten Sie
    *                dabei, dass die so erhaltenen IBAN und BIC fehlerhaft sein können
    *                und deshalb mit ihren Kunden zu überprüfen sind.
    *
    *                Weblinks:
    *                https://www.sparkasse-rhein-neckar-nord.de/pdf/content/sepa/kurzanleitung.pdf
    *                https://www.sparkasse-rhein-neckar-nord.de/firmenkunden/internationales_geschaeft/sepa/vorteile/index.php
    *                https://www.sparkasse-rhein-neckar-nord.de/firmenkunden/internationales_geschaeft/sepa/vorteile/sepa_account_converter.msi
    */

PHP_FUNCTION(generate_lut2)
{
   char *inputname,*outputname,*iban_file,*user_info,*gueltigkeit;
   int inputname_len,outputname_len,user_info_len,iban_len,gueltigkeit_len,felder_1,i,j,cnt,
       *rq1,ret,filialen;
   UINT4 felder_a[MAX_SLOTS+1];
   long slots,lut_version,set;
   zval *z_felder,**z_data,temp;
   HashTable *h_felder;
   HashPosition h_ptr;

   felder_1=271828182;
   slots=lut_version=set=filialen=0;
   user_info=gueltigkeit=NULL;
   z_felder=NULL;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss|sszllls",
            &inputname,&inputname_len,&outputname,&outputname_len,&user_info,
            &user_info_len,&gueltigkeit,&gueltigkeit_len,&z_felder,&slots,
            &lut_version,&set,&iban_file,&iban_len)==FAILURE)RETURN_NULL();

   if(z_felder){
      switch(Z_TYPE_P(z_felder)){
         case IS_STRING:
         case IS_DOUBLE:
            /* Variable kopieren, damit der Typ geändert werden kann */
            temp=*z_felder;
            zval_copy_ctor(&temp);
            convert_to_long(&temp);
            felder_1=Z_LVAL(temp);
            zval_dtor(&temp);
            break;
         case IS_LONG:
            felder_1=Z_LVAL_P(z_felder);
            break;
         case IS_ARRAY: /* das Array aufdröseln, skalare Werte zum Initialisieren benutzen */
            h_felder=Z_ARRVAL_P(z_felder);
            cnt=zend_hash_num_elements(h_felder);
            for(zend_hash_internal_pointer_reset_ex(h_felder,&h_ptr),i=0;
                  zend_hash_get_current_data_ex(h_felder,(void**)&z_data,&h_ptr)==SUCCESS && i<MAX_SLOTS;
                  zend_hash_move_forward_ex(h_felder,&h_ptr),i++){
               if(Z_TYPE_PP(z_data)==IS_LONG)felder_a[i]=Z_LVAL_PP(z_data);
               if(Z_TYPE_PP(z_data)==IS_DOUBLE || Z_TYPE_PP(z_data)==IS_STRING){

                  /* Die Array-Werte müssen nach long konvertiert werden;
                   * dazu wird vorher eine Kopie angelegt, damit der alte Typ
                   * im Array erhalten bleibt.
                   */
                  temp=**z_data;
                  zval_copy_ctor(&temp);
                  convert_to_long(&temp);
                  felder_a[i]=Z_LVAL(temp);
                  zval_dtor(&temp); /* temporäre Variable wieder freigeben */
               }
            }
            felder_a[i]=0;  /* Endemarkierung einfügen */
            felder_1=271828182;
            break;
         default: /* irgendwas anderes übergeben, Default-Level benutzen */
            felder_1=INI_INT("konto_check.init_default_level");
            break;
      }
   }
   else
      felder_1=INI_INT("konto_check.init_default_level");

   if(felder_1<0){   /* auch die Filialen berücksichtigen */
      filialen=1;
      felder_1*=-1;
   }
   switch(felder_1){
      case 271828182: break;   /* es wurde ein Array übergeben; Werte sind schon eingetragen */
      case  0: rq1=lut_set_0; break;
      case  1: rq1=lut_set_1; break;
      case  2: rq1=lut_set_2; break;
      case  3: rq1=lut_set_3; break;
      case  4: rq1=lut_set_4; break;
      case  5: rq1=lut_set_5; break;
      case  6: rq1=lut_set_6; break;
      case  7: rq1=lut_set_7; break;
      case  8: rq1=lut_set_8; break;
      case  9: rq1=lut_set_9; break;
      default: rq1=lut_set_9; break;
   }
   if(felder_1>=0){
      felder_a[0]=LUT2_BLZ;
      felder_a[1]=LUT2_PZ;
      for(i=2,j=0;i<LAST_LUT_BLOCK && rq1[j];)felder_a[i++]=rq1[j++];
      if(filialen)felder_a[i++]=LUT2_FILIALEN;
      felder_a[i]=0;
   }
   ret=generate_lut2(inputname,outputname,user_info,gueltigkeit,felder_a,slots,lut_version,set);
   if(iban_len)lut_keine_iban_berechnung(iban_file,outputname,0);
   RETURN_LONG(ret);
}

   /* kto_check_init(): dies ist die allgemeine Funktion zur Initialisierung
    *                der kto_check Bibliothek. Die Parameter entsprechen
    *                weitgehend denen von lut_init(). Allerdings kann die
    *                Variable required ein Array sein, und es gibt noch eine
    *                Rückgabe über den Status aller angeforderten Blocks.
    *
    * lut_name:      s.o. (bei lut_init())
    *
    * required:      s.o.; dieser Parameter kann ein Skalar oder ein Array
    *                sein; im Fall eines Arrays lassen sich beliebige Blocks
    *                spezifizieren (wie in der C-Funktion).
    *
    * set:           s.o.
    *
    * incremental:   falls 1, wird versucht, nur Blocks nachgeladen; bei 0 wird die
    *                Bibliothek komplett neu initialisiert. Eine inkrementelle
    *                Initialisierung ist natürlich nur von derselben LUT-Datei
    *                möglich; falls eine andere LUT-Datei angegeben wird,
    *                schlägt die Initialisierung fehl.
    *
    * status:        dies ist eine Variable, die als Arrayvariable
    *                zurückgegeben wird; in ihr wird für jeden geladenen Block
    *                der Status angegeben. Damit läßt sich beim Fehler -38
    *                (Blocks teilweise geladen) feststellen, bei welchen Blocks
    *                Fehler aufgetreten sind. Diese Variable ist - anders als
    *                im C API - die letze Variable, um die Funktion kompatibel
    *                zur alten Version zu halten.
    */

PHP_FUNCTION(kto_check_init)
{
   static char *lut_name,buffer[LUT_NAME_BUFFER];
   int lut_name_len=0,required,set,ret,incremental;
   zval *z_required,*z_status,**z_data,*z_used_lutfile,temp;
   HashTable *h_required;
   HashPosition h_ptr;
   int i,j,cnt,required_a[LAST_LUT_BLOCK],*status,*rq1;

   set=incremental=0;
   for(i=0;i<LAST_LUT_BLOCK;i++)required_a[i]=0;
   z_status=z_required=NULL;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"|szllzz",
            &lut_name,&lut_name_len,&z_required,&set,&incremental,
            &z_status,&z_used_lutfile)==FAILURE)RETURN_NULL();
   if(!lut_name_len)lut_name=INIT_DEFAULT_LUT_FILE;
   snprintf(buffer,LUT_NAME_BUFFER,lut_name);
   ret=search_lutfile(buffer);
   if(z_used_lutfile){
      ZVAL_DTOR(z_used_lutfile);
      ZVAL_STRING(z_used_lutfile,buffer,1);
   }
   if(z_status)ZVAL_DTOR(z_status);
   if(ret!=OK){
      if(z_status)ZVAL_NULL(z_status);
      RETURN_LONG(ret);
   }
   switch(Z_TYPE_P(z_required)){
      case IS_STRING:
      case IS_DOUBLE:
            /* Variable kopieren, damit der Typ geändert werden kann */
         temp=*z_required;
         zval_copy_ctor(&temp);
         convert_to_long(&temp);
         required=Z_LVAL(temp);
         zval_dtor(&temp);
         break;
      case IS_LONG:
         required=Z_LVAL_P(z_required);
         break;
      case IS_ARRAY: /* das Array aufdröseln, skalare Werte zum Initialisieren benutzen */
         h_required=Z_ARRVAL_P(z_required);
         cnt=zend_hash_num_elements(h_required);
         for(zend_hash_internal_pointer_reset_ex(h_required,&h_ptr),i=0;
               zend_hash_get_current_data_ex(h_required,(void**)&z_data,&h_ptr)==SUCCESS && i<250;
               zend_hash_move_forward_ex(h_required,&h_ptr),i++){
            if(Z_TYPE_PP(z_data)==IS_LONG)required_a[i]=Z_LVAL_PP(z_data);
            if(Z_TYPE_PP(z_data)==IS_DOUBLE || Z_TYPE_PP(z_data)==IS_STRING){

                   /* Die Array-Werte müssen nach long konvertiert werden;
                    * dazu wird vorher eine Kopie angelegt, damit der alte Typ
                    * im Array erhalten bleibt.
                    */
               temp=**z_data;
               zval_copy_ctor(&temp);
               convert_to_long(&temp);
               required_a[i]=Z_LVAL(temp);
               zval_dtor(&temp); /* temporäre Variable wieder freigeben */
            }
         }
         required_a[i]=0;  /* Endemarkierung einfügen */
         required=-1;
         break;
      default: /* irgendwas anderes übergeben, Default-Level benutzen */
         required=INI_INT("konto_check.init_default_level");
         break;
   }
   switch(required){
      case -1: break;   /* es wurde ein Array übergeben; Werte sind schon eingetragen */
      case  0: rq1=lut_set_0; break;
      case  1: rq1=lut_set_1; break;
      case  2: rq1=lut_set_2; break;
      case  3: rq1=lut_set_3; break;
      case  4: rq1=lut_set_4; break;
      case  5: rq1=lut_set_5; break;
      case  6: rq1=lut_set_6; break;
      case  7: rq1=lut_set_7; break;
      case  8: rq1=lut_set_8; break;
      case  9: rq1=lut_set_9; break;
      default: rq1=lut_set_9; break;
   }
   if(required>=0){
      required_a[0]=LUT2_BLZ;
      required_a[1]=LUT2_PZ;
      required_a[2]=LUT2_FILIALEN;
      for(i=3,j=0;i<LAST_LUT_BLOCK && rq1[j];)required_a[i++]=rq1[j++];
      required_a[i]=0;
      if(init_status<7)incremental=0; /* noch nicht initialisiert, inkrementell geht nicht */
   }
   ret=kto_check_init(buffer,required_a,&status,set,incremental);
   if(z_status){
      array_init(z_status);
      for(i=0;i<=LAST_LUT_BLOCK;i++)if(status[i])add_assoc_long(z_status,lut2_feld_namen[i],status[i]);
   }
   RETURN_LONG(ret);
}

PHP_FUNCTION(lut_valid)
{
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"")==FAILURE)RETURN_NULL();
   RETURN_LONG(lut_valid());
}

PHP_FUNCTION(lut2_status)
{
   int i;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"")==FAILURE)RETURN_NULL();
   array_init(return_value);
   for(i=0;i<=LAST_LUT_BLOCK;i++)if(lut2_block_status[i]){
      add_index_long(return_value,i,lut2_block_status[i]);
      add_assoc_long(return_value,lut2_feld_namen[i],lut2_block_status[i]);
   }
}

PHP_FUNCTION(kto_check)
{
   char *blz,*kto,*lut_name;
   int blz_len,kto_len,lut_name_len;

   lut_name=INIT_DEFAULT_LUT_FILE;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss|s",
            &blz,&blz_len,&kto,&kto_len,&lut_name,&lut_name_len)==FAILURE)RETURN_NULL();
   RETURN_LONG(kto_check(blz,kto,lut_name));
}

PHP_FUNCTION(kto_check_pz)
{
   char *kto,*pz,*blz=NULL;
   int kto_len,pz_len,blz_len,ret;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss|s",
            &pz,&pz_len,&kto,&kto_len,&blz,&blz_len)==FAILURE)RETURN_NULL();
   ret=kto_check_pz(pz,kto,blz);
   RETURN_LONG(ret);
}

PHP_FUNCTION(kto_check_blz)
{
   char *blz,*kto;
   int blz_len,kto_len,ret;

   blz=kto=NULL;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss",
            &blz,&blz_len,&kto,&kto_len)==FAILURE)RETURN_NULL();
   ret=kto_check_blz(blz,kto);
   RETURN_LONG(ret);
}

PHP_FUNCTION(kto_check_pz_dbg)
{
   char *kto,*pz,*blz=NULL;
   int kto_len,pz_len,blz_len,ret;
   RETVAL retvals;
   zval *z_methode,*z_pz_methode,*z_pz,*z_pz_pos;

   z_methode=z_pz_methode=z_pz=z_pz_pos=NULL;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss|szzzz",&pz,&pz_len,&kto,&kto_len,
            &blz,&blz_len,&z_methode,&z_pz_methode,&z_pz,&z_pz_pos)==FAILURE)RETURN_NULL();
   ret=kto_check_pz_dbg(pz,kto,blz,&retvals);
#if DEBUG
   if(z_methode){
      ZVAL_DTOR(z_methode);
      ZVAL_STRING(z_methode,retvals.methode,1);
   }
   if(z_pz_methode){
      ZVAL_DTOR(z_pz_methode);
      ZVAL_LONG(z_pz_methode,retvals.pz_methode);
   }
   if(z_pz){
      ZVAL_DTOR(z_pz);
      ZVAL_LONG(z_pz,retvals.pz);
   }
   if(z_pz_pos){
      ZVAL_DTOR(z_pz_pos);
      ZVAL_LONG(z_pz_pos,(long)retvals.pz_pos);
   }
#else
   if(z_methode){
      ZVAL_DTOR(z_methode);
      ZVAL_NULL(z_methode);
   }
   if(z_pz_methode){
      ZVAL_DTOR(z_pz_methode);
      ZVAL_NULL(z_pz_methode);
   }
   if(z_pz){
      ZVAL_DTOR(z_pz);
      ZVAL_NULL(z_pz);
   }
   if(z_pz_pos){
      ZVAL_DTOR(z_pz_pos);
      ZVAL_NULL(z_pz_pos);
   }
#endif
   RETURN_LONG(ret);
}

PHP_FUNCTION(kto_check_regel_dbg)
{
   char *blz=NULL,*kto,blz2[10],kto2[16];
   const char *bic;
   int blz_len,kto_len,ret,regel;
   RETVAL retvals;
   zval *z_retvals;

   z_retvals=NULL;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss|z",&blz,&blz_len,
            &kto,&kto_len,&z_retvals)==FAILURE)RETURN_NULL();
   ret=kto_check_regel_dbg(blz,kto,blz2,kto2,&bic,&regel,&retvals);
#if DEBUG
   if(z_retvals){
      ZVAL_DTOR(z_retvals);
      if(ret<=0){
         ZVAL_NULL(z_retvals);
      }
      else{
         array_init(z_retvals);
         add_assoc_string(z_retvals,"blz2",blz2,1);
         add_assoc_string(z_retvals,"kto2",kto2,1);
         if(bic)
            add_assoc_string(z_retvals,"bic2",(char*)bic,1);
         else
            add_assoc_string(z_retvals,"bic2",(char*)"",1);
         add_assoc_long(z_retvals,"regel",regel/100);
         add_assoc_long(z_retvals,"regel_version",regel%100);
         if(retvals.methode)
            add_assoc_string(z_retvals,"methode",(char*)retvals.methode,1);
         else
            add_assoc_string(z_retvals,"methode",(char*)"",1);
         add_assoc_long(z_retvals,"pz_methode",retvals.pz_methode);
         add_assoc_long(z_retvals,"pz",retvals.pz);
         add_assoc_long(z_retvals,"pz_pos",retvals.pz_pos);
      }
   }
#else
   if(z_retvals){
      ZVAL_DTOR(z_retvals);
      ZVAL_NULL(z_retvals);
   }
#endif
   RETURN_LONG(ret);
}

PHP_FUNCTION(kto_check_blz_dbg)
{
   char *blz=NULL,*kto;
   int blz_len,kto_len,ret;
   RETVAL retvals;
   zval *z_methode,*z_pz_methode,*z_pz,*z_pz_pos;

   z_methode=z_pz_methode=z_pz=z_pz_pos=NULL;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss|zzzz",&blz,&blz_len,
            &kto,&kto_len,&z_methode,&z_pz_methode,&z_pz,&z_pz_pos)==FAILURE)RETURN_NULL();
   ret=kto_check_blz_dbg(blz,kto,&retvals);
#if DEBUG
   if(z_methode){
      ZVAL_DTOR(z_methode);
      ZVAL_STRING(z_methode,retvals.methode,1);
   }
   if(z_pz_methode){
      ZVAL_DTOR(z_pz_methode);
      ZVAL_LONG(z_pz_methode,retvals.pz_methode);
   }
   if(z_pz){
      ZVAL_DTOR(z_pz);
      ZVAL_LONG(z_pz,retvals.pz);
   }
   if(z_pz_pos){
      ZVAL_DTOR(z_pz_pos);
      ZVAL_LONG(z_pz_pos,(long)retvals.pz_pos);
   }
#else
   if(z_methode){
      ZVAL_DTOR(z_methode);
      ZVAL_NULL(z_methode);
   }
   if(z_pz_methode){
      ZVAL_DTOR(z_pz_methode);
      ZVAL_NULL(z_pz_methode);
   }
   if(z_pz){
      ZVAL_DTOR(z_pz);
      ZVAL_NULL(z_pz);
   }
   if(z_pz_pos){
      ZVAL_DTOR(z_pz_pos);
      ZVAL_NULL(z_pz_pos);
   }
#endif
   RETURN_LONG(ret);
}

#line 1235 "konto_check.lxx"
PHP_FUNCTION(lut_blocks)
{
   char *blocks_ok,*blocks_fehler,*filename;
   int mode;
   long ret;
   zval *z_lut_blocks_ok=NULL,*z_lut_blocks_fehler=NULL,*z_lut_filename=NULL;

   mode=0;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"|lzzz",&mode,&z_lut_filename,&z_lut_blocks_ok,&z_lut_blocks_fehler)==FAILURE)RETURN_NULL();
   ret=lut_blocks(mode,&filename,&blocks_ok,&blocks_fehler);
   if(ret==LUT2_NOT_INITIALIZED){
      if(z_lut_filename){
         ZVAL_DTOR(z_lut_filename);
         ZVAL_NULL(z_lut_filename);
      }
      if(z_lut_blocks_ok){
         ZVAL_DTOR(z_lut_blocks_ok);
         ZVAL_NULL(z_lut_blocks_ok);
      }
      if(z_lut_blocks_fehler){
         ZVAL_DTOR(z_lut_blocks_fehler);
         ZVAL_NULL(z_lut_blocks_fehler);
      }
   }
   else{
      if(z_lut_filename){
         ZVAL_DTOR(z_lut_filename);
         ZVAL_STRING(z_lut_filename,filename,1);
      }
      if(z_lut_blocks_ok){
         ZVAL_DTOR(z_lut_blocks_ok);
         ZVAL_STRING(z_lut_blocks_ok,blocks_ok,1);
      }
      if(z_lut_blocks_fehler){
         ZVAL_DTOR(z_lut_blocks_fehler);
         ZVAL_STRING(z_lut_blocks_fehler,blocks_fehler,1);
      }
      kc_free(filename);
      kc_free(blocks_ok);
      kc_free(blocks_fehler);
   }
   RETURN_LONG(ret);
}

PHP_FUNCTION(lut_cleanup)
{
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"")==FAILURE)RETURN_NULL();
   RETURN_LONG(lut_cleanup());
}

PHP_FUNCTION(kto_check_str)
{
   char *blz,*kto,*lut_name;
   int blz_len,kto_len,lut_name_len,ret;
   long ret_type=0;

   lut_name=INIT_DEFAULT_LUT_FILE;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss|ls",
            &blz,&blz_len,&kto,&kto_len,&ret_type,&lut_name,&lut_name_len)==FAILURE)RETURN_NULL();
   ret=kto_check(blz,kto,lut_name);
   switch(ret_type){
      case 1: RETURN_STRING(kto_check_retval2txt_short(ret),1); break;
      case 2: RETURN_STRING(kto_check_retval2txt(ret),1); break;
      case 3: RETURN_STRING(kto_check_retval2html(ret),1); break;
      case 4: RETURN_STRING(kto_check_retval2dos(ret),1); break;
      case 5: RETURN_STRING(kto_check_retval2utf8(ret),1); break;
      default: RETURN_STRING(kto_check_retval2html(ret),1); break;
   }
}

PHP_FUNCTION(lut_filialen)
{
   char *blz;
   int cnt,ret,blz_len;
   zval *retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|z",
            &blz,&blz_len,&retval)==FAILURE)RETURN_NULL();
   cnt=lut_filialen(blz,&ret);
   if(retval){
      ZVAL_DTOR(retval);
      ZVAL_LONG(retval,ret);
   }
   if(ret==OK){
      RETURN_LONG(cnt);
   }
   else{
      RETURN_NULL();
   }
}

PHP_FUNCTION(lut_blz)
{
   char *blz=NULL;
   int ret;
   long blz_len,zweigstelle=0;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|l",
            &blz,&blz_len,&zweigstelle)==FAILURE)RETURN_NULL();
   ret=lut_blz(blz,zweigstelle);
   RETURN_LONG(ret);
}

PHP_FUNCTION(pz2str)
{
   const char *pz_s;
   int ret,pz;
   long blz_len,zweigstelle=0;
   zval *z_ret=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l|z",
            &pz,&z_ret)==FAILURE)RETURN_NULL();
   pz_s=pz2str(pz,&ret);
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   RETURN_STRING(pz_s,1);
}

PHP_FUNCTION(lut_suche_volltext)
{
   char *such_name=NULL;
   int such_name_len,ret,anzahl,i,j,k,last_blz,*start_idx,*zweigstelle,*blz_base,anzahl_o,*idx_o,*cnt_o;
   long sort,sort_uniq; /* bei 1 sortieren, bei 2 sortieren + uniq */
   zval *z_blz=NULL,*z_zweigstelle=NULL,*z_cnt_o=NULL;

   sort_uniq=sort=-1;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|lzzzl",
            &such_name,&such_name_len,&sort_uniq,&z_blz,&z_zweigstelle,&z_cnt_o,&sort)==FAILURE)RETURN_NULL();
   if(!such_name)RETURN_LONG(ret);
   if(sort_uniq>0 && sort<=0)sort_uniq=2;    /* u.U. altes Verhalten: nur uniq angegeben (kann 1 sein) */
   if(sort_uniq<=0 && sort>0)sort_uniq=1;    /* nur sortieren, kein uniq */
   if(sort_uniq<0)sort_uniq=INI_INT("konto_check.uniq");
   ret=lut_suche_volltext(such_name,NULL,NULL,NULL,&anzahl,&start_idx,&zweigstelle,&blz_base);
   if(ret>=0 && sort_uniq)
      lut_suche_sort1(anzahl,blz_base,zweigstelle,start_idx,&anzahl_o,&idx_o,&cnt_o,sort_uniq>1);
   else{
      anzahl_o=anzahl;
      idx_o=start_idx;
      cnt_o=NULL;
   }
   if(z_blz){
      ZVAL_DTOR(z_blz);
      ZVAL_NULL(z_blz);
      array_init(z_blz);
   }
   if(z_zweigstelle){
      ZVAL_DTOR(z_zweigstelle);
      ZVAL_NULL(z_zweigstelle);
      array_init(z_zweigstelle);
   }
   if(z_cnt_o){
      ZVAL_DTOR(z_cnt_o);
      ZVAL_NULL(z_cnt_o);
      array_init(z_cnt_o);
   }
   if(ret<0){
      RETURN_LONG(ret);
   }

   for(i=k=0,last_blz=-1;i<anzahl_o;i++){
      j=start_idx[i];
      j=idx_o[i];
      if(sort_uniq>1 && blz_base[j]==last_blz)
         continue;
      else
         last_blz=blz_base[j];
      if(z_blz)add_index_long(z_blz,k,blz_base[j]);   /* Zweigstellen-Index */
      if(z_zweigstelle)add_index_long(z_zweigstelle,k,zweigstelle?zweigstelle[j]:0);   /* Zweigstelle */
      if(z_cnt_o)add_index_long(z_cnt_o,i,cnt_o?cnt_o[i]:1);   /* Anzahl Zweigstellen pro BLZ (v.a. interessant bei uniq) */
      k++;
   }
   if(sort_uniq){
      kc_free((char*)idx_o);
      kc_free((char*)cnt_o);
   }
   RETURN_LONG(ret);
}

PHP_FUNCTION(lut_suche_init)
{
   long uniq=-1;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"|l",&uniq)==FAILURE)RETURN_NULL();
   if(uniq<0)uniq=INI_INT("konto_check.uniq");
   RETURN_LONG(lut_suche_init(uniq));
}

PHP_FUNCTION(lut_suche_free)
{
   long id;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",&id)==FAILURE)RETURN_NULL();
   RETURN_LONG(lut_suche_free(id));
}

PHP_FUNCTION(lut_suche_set)
{
   char *such_idx=NULL,*such_str;
   int such_idx_len,such_typ,ret,p1,p2;
   long suche;
   zval *z_p1=NULL,*z_p2=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"lslz|z",
            &suche,&such_idx,&such_idx_len,&such_typ,&z_p1,&z_p2)==FAILURE)RETURN_NULL();
   p1=p2=0;
   such_str=NULL;
   switch(Z_TYPE_P(z_p1)){
      case IS_STRING:
         such_str=Z_STRVAL_P(z_p1);
         break;
      case IS_LONG:
         p1=Z_LVAL_P(z_p1);
         if(z_p2 && Z_TYPE_P(z_p2)==IS_LONG)
            p2=Z_LVAL_P(z_p2);
         else
            p2=p1;
         break;
      default:
         break;
   }
   RETURN_LONG(lut_suche_set(suche,*such_idx,such_typ,p1,p2,such_str));
}

PHP_FUNCTION(lut_suche)
{
   char *such_cmd=NULL;
   int such_cmd_len,ret,i;
   UINT4 cnt,*blz,*zweigstelle;
   long suche;
   zval *z_blz=NULL,*z_zweigstelle=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ls|zz",&suche,
            &such_cmd,&such_cmd_len,&z_blz,&z_zweigstelle)==FAILURE)RETURN_NULL();
   if(z_blz){
      ZVAL_DTOR(z_blz);
      ZVAL_NULL(z_blz);
   }
   if(z_zweigstelle){
      ZVAL_DTOR(z_zweigstelle);
      ZVAL_NULL(z_zweigstelle);
   }

   if((ret=lut_suche(suche,such_cmd,&cnt,&zweigstelle,&blz))<0)RETURN_LONG(ret);
   if(z_blz){
      array_init(z_blz);
      for(i=0;i<cnt;i++)add_next_index_long(z_blz,(long)blz[i]);
   }
   if(z_zweigstelle){
      array_init(z_zweigstelle);
      for(i=0;i<cnt;i++)add_next_index_long(z_zweigstelle,(long)zweigstelle[i]);
   }
   free(blz);
   free(zweigstelle);
   RETURN_LONG(ret);
}

PHP_FUNCTION(lut_suche_multiple)
{
   char *such_worte=NULL,*such_cmd=NULL;
   int such_worte_len,such_cmd_len,ret,i,uniq=-1;
   UINT4 cnt,*blz,*zweigstelle;
   zval *z_blz=NULL,*z_zweigstelle=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|lszz",&such_worte,&such_worte_len,
            &uniq,&such_cmd,&such_cmd_len,&z_blz,&z_zweigstelle)==FAILURE)RETURN_NULL();
   if(uniq<0)uniq=INI_INT("konto_check.uniq");
   if(z_blz){
      ZVAL_DTOR(z_blz);
      ZVAL_NULL(z_blz);
   }
   if(z_zweigstelle){
      ZVAL_DTOR(z_zweigstelle);
      ZVAL_NULL(z_zweigstelle);
   }
   if((ret=lut_suche_multiple(such_worte,uniq,such_cmd_len?such_cmd:NULL,&cnt,&zweigstelle,&blz))<0)RETURN_LONG(ret);
   if(z_blz){
      array_init(z_blz);
      for(i=0;i<cnt;i++)add_next_index_long(z_blz,(long)blz[i]);
   }
   if(z_zweigstelle){
      array_init(z_zweigstelle);
      for(i=0;i<cnt;i++)add_next_index_long(z_zweigstelle,(long)zweigstelle[i]);
   }
   free(blz);
   free(zweigstelle);
   RETURN_LONG(ret);
}

PHP_FUNCTION(lut_methode_txt)
{
   int zeilen,txtlen;
   long m=0,line_begin_len=0;
   char *ptr,*ptr1,*dptr,*line_begin=NULL,*buffer;
   zval *z_folgemethode=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l|zs",
            &m,&z_folgemethode,&line_begin,&line_begin_len)==FAILURE)RETURN_NULL();
   if(!line_begin){
      line_begin="   ";       /* Kompatibilität zur alten Version: drei Blanks */
      line_begin_len=3;
   }
   else if(!line_begin_len)   /* leerer String übergeben; kein Zeilenanfang */
      line_begin="";
   if(z_folgemethode){
      ZVAL_DTOR(z_folgemethode);
#if BESCHREIBUNG_TXT
      ZVAL_LONG(z_folgemethode,folgemethode(m));
#else
      ZVAL_LONG(z_folgemethode,-2);
#endif
   }      
#if BESCHREIBUNG_TXT
   for(ptr=mtxt(m),txtlen=zeilen=1;*ptr++;){
      txtlen++;
      if(*ptr=='\n')zeilen++;
   }

      /* nun den Beschreibungstext nach buffer kopieren, dabei den gewünschten Zeilenanfang einfügen */
   buffer=emalloc(txtlen+zeilen*line_begin_len);
   for(dptr=buffer,ptr1=line_begin;*dptr=*ptr1++;dptr++);   /* vor der ersten Zeile */
   for(ptr=mtxt(m);*dptr++=*ptr;ptr++)if(*ptr=='\n' && *(ptr+1))for(ptr1=line_begin;*dptr=*ptr1++;dptr++);

      /* Buffer als String zurückgeben *ohne* Kopieren => free() wird von PHP erledigt */
   RETURN_STRING(buffer,0);
#else
   RETURN_STRING("Das Modul wurde ohne die Beschreibungstexte kompiliert",1);
#endif
}

PHP_FUNCTION(keep_raw_data)
{
   int mode;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",
            &mode)==FAILURE)RETURN_NULL();
   RETURN_LONG(keep_raw_data(mode));
}

PHP_FUNCTION(kto_check_encoding)
{
   char *enc=NULL;
   int e;
   long enc_len=0;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s",
            &enc,&enc_len)==FAILURE)RETURN_NULL();
   if(!(e=atoi(enc)))e=*enc;   /* Kodierung wahlweise als String oder Zahl */
   if(e=='m' || e=='M')switch(tolower(*(enc+1))){
      case 'i': e=51; break;
      case 'u': e=52; break;
      case 'h': e=53; break;
      case 'd': e=54; break;
      default:  e=DEFAULT_ENCODING%10+50;   /* nicht recht spezifiziert, Makro+Default-Encoding nehmen */
   }
   RETURN_LONG(kto_check_encoding(e));
}

PHP_FUNCTION(kto_check_encoding_str)
{
   char *enc=NULL;
   int e;
   long enc_len=0;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s",
            &enc,&enc_len)==FAILURE)RETURN_NULL();
   if(!(e=atoi(enc)))e=*enc;   /* Kodierung wahlweise als String oder Zahl */
   if(e=='m' || e=='M')switch(tolower(*(enc+1))){
      case 'i': e=51; break;
      case 'u': e=52; break;
      case 'h': e=53; break;
      case 'd': e=54; break;
      default:  e=DEFAULT_ENCODING%10+50;   /* nicht recht spezifiziert, Makro+Default-Encoding nehmen */
   }
   RETURN_STRING(kto_check_encoding_str(e),1);
}

PHP_FUNCTION(kto_check_retval2txt)
{
   long ret;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",
            &ret)==FAILURE)RETURN_NULL();
   RETURN_STRING(kto_check_retval2txt(ret),1);
}

PHP_FUNCTION(kto_check_retval2iso)
{
   long ret;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",
            &ret)==FAILURE)RETURN_NULL();
   RETURN_STRING(kto_check_retval2iso(ret),1);
}

PHP_FUNCTION(kto_check_retval2html)
{
   long ret;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",
            &ret)==FAILURE)RETURN_NULL();
   RETURN_STRING(kto_check_retval2html(ret),1);
}

PHP_FUNCTION(kto_check_retval2txt_short)
{
   long ret;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",
            &ret)==FAILURE)RETURN_NULL();
   RETURN_STRING(kto_check_retval2txt_short(ret),1);
}

PHP_FUNCTION(kto_check_retval2dos)
{
   long ret;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",
            &ret)==FAILURE)RETURN_NULL();
   RETURN_STRING(kto_check_retval2dos(ret),1);
}

PHP_FUNCTION(kto_check_retval2utf8)
{
   long ret;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",
            &ret)==FAILURE)RETURN_NULL();
   RETURN_STRING(kto_check_retval2utf8(ret),1);
}

PHP_FUNCTION(lut_name)
{
   char *blz=NULL;
   const char *ret_str=NULL;
   int ret;
   long blz_len,zweigstelle=0;
   zval *z_retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zl",
            &blz,&blz_len,&z_retval,&zweigstelle)==FAILURE)RETURN_NULL();
   ret_str=lut_name(blz,zweigstelle,&ret);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,ret);
   }
   if(ret<OK || lut2_block_status[LUT2_NAME]!=OK){
      RETURN_NULL();
   }
   else
      RETURN_STRING(ret_str,1);
}

PHP_FUNCTION(lut_name_kurz)
{
   char *blz=NULL;
   const char *ret_str=NULL;
   int ret;
   long blz_len,zweigstelle=0;
   zval *z_retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zl",
            &blz,&blz_len,&z_retval,&zweigstelle)==FAILURE)RETURN_NULL();
   ret_str=lut_name_kurz(blz,zweigstelle,&ret);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,ret);
   }
   if(ret<OK || lut2_block_status[LUT2_NAME_KURZ]!=OK){
      RETURN_NULL();
   }
   else
      RETURN_STRING(ret_str,1);
}

PHP_FUNCTION(lut_plz)
{
   char *blz=NULL;
   int ret;
   long ret_long,blz_len,zweigstelle=0;
   zval *z_retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zl",
            &blz,&blz_len,&z_retval,&zweigstelle)==FAILURE)RETURN_NULL();
   ret_long=lut_plz(blz,zweigstelle,&ret);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,ret);
   }
   if(ret<OK || lut2_block_status[LUT2_PLZ]!=OK){
      RETURN_NULL();
   }
   else
      RETURN_LONG(ret_long);
}

PHP_FUNCTION(lut_ort)
{
   char *blz=NULL;
   const char *ret_str=NULL;
   int ret;
   long blz_len,zweigstelle=0;
   zval *z_retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zl",
            &blz,&blz_len,&z_retval,&zweigstelle)==FAILURE)RETURN_NULL();
   ret_str=lut_ort(blz,zweigstelle,&ret);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,ret);
   }
   if(ret<OK || lut2_block_status[LUT2_ORT]!=OK){
      RETURN_NULL();
   }
   else
      RETURN_STRING(ret_str,1);
}

PHP_FUNCTION(lut_pan)
{
   char *blz=NULL;
   int ret;
   long ret_long,blz_len,zweigstelle=0;
   zval *z_retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zl",
            &blz,&blz_len,&z_retval,&zweigstelle)==FAILURE)RETURN_NULL();
   ret_long=lut_pan(blz,zweigstelle,&ret);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,ret);
   }
   if(ret<OK || lut2_block_status[LUT2_PAN]!=OK){
      RETURN_NULL();
   }
   else
      RETURN_LONG(ret_long);
}

PHP_FUNCTION(lut_bic)
{
   char *blz=NULL;
   const char *ret_str=NULL;
   int ret;
   long blz_len,zweigstelle=0;
   zval *z_retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zl",
            &blz,&blz_len,&z_retval,&zweigstelle)==FAILURE)RETURN_NULL();
   ret_str=lut_bic(blz,zweigstelle,&ret);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,ret);
   }
   if(ret<OK || lut2_block_status[LUT2_BIC]!=OK){
      RETURN_NULL();
   }
   else
      RETURN_STRING(ret_str,1);
}

PHP_FUNCTION(lut_nr)
{
   char *blz=NULL;
   int ret;
   long ret_long,blz_len,zweigstelle=0;
   zval *z_retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zl",
            &blz,&blz_len,&z_retval,&zweigstelle)==FAILURE)RETURN_NULL();
   ret_long=lut_nr(blz,zweigstelle,&ret);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,ret);
   }
   if(ret<OK || lut2_block_status[LUT2_NR]!=OK){
      RETURN_NULL();
   }
   else
      RETURN_LONG(ret_long);
}

PHP_FUNCTION(lut_pz)
{
   char *blz=NULL;
   int ret;
   long ret_long,blz_len,zweigstelle=0;
   zval *z_retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zl",
            &blz,&blz_len,&z_retval,&zweigstelle)==FAILURE)RETURN_NULL();
   ret_long=lut_pz(blz,zweigstelle,&ret);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,ret);
   }
   if(ret<OK || lut2_block_status[LUT2_PZ]!=OK){
      RETURN_NULL();
   }
   else
      RETURN_LONG(ret_long);
}

PHP_FUNCTION(lut_nachfolge_blz)
{
   char *blz=NULL;
   int ret;
   long ret_long,blz_len,zweigstelle=0;
   zval *z_retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zl",
            &blz,&blz_len,&z_retval,&zweigstelle)==FAILURE)RETURN_NULL();
   ret_long=lut_nachfolge_blz(blz,zweigstelle,&ret);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,ret);
   }
   if(ret<OK || lut2_block_status[LUT2_NACHFOLGE_BLZ]!=OK){
      RETURN_NULL();
   }
   else
      RETURN_LONG(ret_long);
}

PHP_FUNCTION(lut_aenderung)
{
   char *blz=NULL,ret_c[2];
   int ret;
   long ret_long,blz_len,zweigstelle=0;
   zval *z_retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zl",
            &blz,&blz_len,&z_retval,&zweigstelle)==FAILURE)RETURN_NULL();
   ret_long=lut_aenderung(blz,zweigstelle,&ret);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,ret);
   }
   if(ret<OK || lut2_block_status[LUT2_AENDERUNG]!=OK){
      RETURN_NULL();
   }
   else
      ret_c[0]=ret_long;
      ret_c[1]=0;
      RETURN_STRING(ret_c,1);
}

PHP_FUNCTION(lut_loeschung)
{
   char *blz=NULL,ret_c[2];
   int ret;
   long ret_long,blz_len,zweigstelle=0;
   zval *z_retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zl",
            &blz,&blz_len,&z_retval,&zweigstelle)==FAILURE)RETURN_NULL();
   ret_long=lut_loeschung(blz,zweigstelle,&ret);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,ret);
   }
   if(ret<OK || lut2_block_status[LUT2_LOESCHUNG]!=OK){
      RETURN_NULL();
   }
   else
      ret_c[0]=ret_long;
      ret_c[1]=0;
      RETURN_STRING(ret_c,1);
}

PHP_FUNCTION(lut_iban_regel)
{
   char *blz=NULL;
   int ret;
   long ret_long,blz_len,zweigstelle=0;
   zval *z_retval=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zl",
            &blz,&blz_len,&z_retval,&zweigstelle)==FAILURE)RETURN_NULL();
   ret_long=lut_iban_regel(blz,zweigstelle,&ret);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,ret);
   }
   if(ret<OK || lut2_block_status[LUT2_IBAN_REGEL]!=OK){
      RETURN_NULL();
   }
   else
      RETURN_LONG(ret_long);
}

PHP_FUNCTION(current_lutfile_name)
{
   const char *lutfile_name;
   int ret,level,set;
   zval *z_set=NULL,*z_ret=NULL,*z_level=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"|zzz",
            &z_set,&z_level,&z_ret)==FAILURE)RETURN_NULL();
   lutfile_name=current_lutfile_name(&set,&level,&ret);
   if(z_set){
      ZVAL_DTOR(z_set);
      ZVAL_LONG(z_set,set);
   }
   if(z_level){
      ZVAL_DTOR(z_level);
      ZVAL_LONG(z_level,level);
   }
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   if(lutfile_name){
      RETURN_STRING(lutfile_name,1);
   }
   else{
      RETURN_NULL();
   }
}

PHP_FUNCTION(read_lut_block)
{
   char *lut_name;
   UINT4 block_len;
   int lut_name_len,retval;
   long typ;
   char *data;
   zval *z_retval;

   z_retval=NULL;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"sl|z",
            &lut_name,&lut_name_len,&typ,&z_retval)==FAILURE)RETURN_NULL();
   retval=read_lut_block(lut_name,(UINT4)typ,&block_len,&data);
   if(z_retval){
      ZVAL_DTOR(z_retval);
      ZVAL_LONG(z_retval,retval);
   }
   ZVAL_STRINGL(return_value,data,block_len,1);
   FREE(data);
}

PHP_FUNCTION(write_lut_block)
{
   char *lut_name,*data;
   int lut_name_len,data_len,retval;
   long typ;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"sls",
            &lut_name,&lut_name_len,&typ,&data,&data_len)==FAILURE)RETURN_NULL();
   retval=write_lut_block(lut_name,(UINT4)typ,(UINT4)data_len,data);
   RETURN_LONG(retval);
}

PHP_FUNCTION(copy_lutfile)
{
   char *old_name,*new_name;
   int old_name_len,new_name_len,retval;
   long slots;

   retval=slots=0;
   old_name=new_name=NULL;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ssl",
            &old_name,&old_name_len,&new_name,&new_name_len,&slots)==FAILURE)RETURN_NULL();
   if(old_name && new_name)retval=copy_lutfile(old_name,new_name,slots);
   RETURN_LONG(retval);
}

PHP_FUNCTION(lut_info)
{
   char *lut_name,*info1,*info2;
   int lut_name_len,valid1,valid2,ret;
   zval *z_info1,*z_info2,*z_valid1,*z_valid2,*z_info3,*z_slots;
   char slot_buffer[512],*ptr;
   int i,ok,retval,len1,len2,slotdir[MAX_SLOTS];
   UINT4 slot_cnt,typ,len,compressed_len,adler;
   FILE *lut;

   lut_name=NULL;
   z_info1=z_info2=z_valid1=z_valid2=z_info3=z_slots=NULL;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"|szzzzzz",
            &lut_name,&lut_name_len,&z_info1,&z_valid1,&z_info2,
            &z_valid2,&z_info3,&z_slots)==FAILURE)RETURN_NULL();
   ret=lut_info(lut_name,&info1,&info2,&valid1,&valid2);

   if(z_info1){
      ZVAL_DTOR(z_info1);
      if(info1){
         ZVAL_STRING(z_info1,info1,1);
      }
      else{
         ZVAL_NULL(z_info1);
      }
   }
   if(z_info2){
      ZVAL_DTOR(z_info2);
      if(info2){
         ZVAL_STRING(z_info2,info2,1);
      }
      else{
         ZVAL_NULL(z_info2);
      }
   }
   if(z_valid1){
      ZVAL_DTOR(z_valid1);
      ZVAL_LONG(z_valid1,valid1);
   }
   if(z_valid2){
      ZVAL_DTOR(z_valid2);
      ZVAL_LONG(z_valid2,valid2);
   }
   if(z_info3){
      ZVAL_DTOR(z_info3);
      ZVAL_NULL(z_info3);
   }
   if(z_slots){
      ZVAL_DTOR(z_slots);
      ZVAL_NULL(z_slots);
   }
   if(info1)FREE(info1);
   if(info2)FREE(info2);
   if(lut_name && (z_slots || z_info3)){
      if((lut=fopen(lut_name,"rb"))){
         ok=1;
         if(z_slots){
            array_init(z_slots);
            snprintf(slot_buffer,512,"  Slot  retval   Typ      Inhalt              Laenge    kompr.   Verh.  Adler32   Test");
            add_index_string(z_slots,0,slot_buffer,1);
         }
         for(len1=len2=0,i=slot_cnt=1;i<=slot_cnt;i++){
            retval=lut_dir(lut,i,&slot_cnt,&typ,&len,&compressed_len,&adler,NULL,NULL);
            if(retval==LUT2_FILE_CORRUPTED){
               if(z_slots){ZVAL_NULL(z_slots);}
               if(z_info3){ZVAL_STRING(z_info3,"Die LUT-Datei ist korrumpiert",1);}
               ok=0;
               break;
            }
            if(retval==INVALID_LUT_FILE){
               if(z_slots){ZVAL_NULL(z_slots);}
            if(z_info3){ZVAL_STRING(z_info3,"die Datei ist keine LUT-Datei",1);}
               ok=0;
               break;
            }
            if(retval==LUT1_FILE_USED){
               if(z_slots){ZVAL_NULL(z_slots);}
               if(z_info3){ZVAL_STRING(z_info3,"Die LUT-Datei ist im alten Format (1.0/1.1)",1);}
               ok=0;
               break;
            }
            if(z_slots){
               if(len)
                  snprintf(slot_buffer,512,"%3d/%3u %3d %8d   %-20s %8u %8u%7.1f%%  0x%08x   %s",
                        i,slot_cnt,retval,typ,typ<400?lut_block_name2[typ]:"(Userblock)",
                        len,compressed_len,(double)compressed_len/len*100,
                        adler,retval==OK?"OK":"FEHLER");
               else
                  snprintf(slot_buffer,512,"%3d/%3u %3d %8d   %-20s %8u %8u%7s   0x%08x   %s",
                        i,slot_cnt,1,0,"   (ungenutzt)",0,0,"-",0,"OK");
               add_index_string(z_slots,i,slot_buffer,1);
            }
            len1+=len;
            len2+=compressed_len;
         }
         if(ok && z_info3){
            snprintf(slot_buffer,512,"Gesamtgroesse unkomprimiert: %d, Gesamtgroesse komprimiert: %d\nKompressionsrate: %1.2f%%\n",
                  len1,len2,100.*(double)len2/len1);
            for(ptr=slot_buffer,len=512;*ptr;ptr++,len--);
            retval=lut_dir(lut,0,&slot_cnt,NULL,NULL,NULL,NULL,slotdir,NULL);
            snprintf(ptr,len,"Slotdir (kurz): ");
            for(;*ptr;ptr++,len--);
            for(i=0;i<slot_cnt && len>10;i++)if(slotdir[i]){
               snprintf(ptr,len,"%d ",slotdir[i]);
               for(;*ptr;ptr++,len--);
            }
            ZVAL_STRING(z_info3,slot_buffer,1);
         }
         fclose(lut);
      }
   }
   RETURN_LONG(ret);
}

PHP_FUNCTION(lut_multiple)
{
   char *blz,*p_blz,**p_name,**p_name_kurz,**p_ort,**p_bic,*p_aenderung,*p_loeschung,short_buf[2];
   int blz_len,cnt,*p_plz,*p_pan,p_pz,*p_nr,*p_nachfolge_blz,ret;
   char ***pp_name,***pp_name_kurz,***pp_ort,***pp_bic,**pp_aenderung,**pp_loeschung;
   int **pp_plz,**pp_pan,*pp_pz,**pp_nr,**pp_nachfolge_blz;
   long zweigstelle=0;
   zval *z_cnt,*z_name,*z_name_kurz,*z_plz,*z_ort,*z_pan,*z_bic,*z_pz,*z_nr,
        *z_aenderung,*z_loeschung,*z_nachfolge_blz;

   if(init_status<7)RETURN_LONG(LUT2_NOT_INITIALIZED);
   z_cnt=z_name=z_name_kurz=z_plz=z_ort=z_pan=z_bic=z_pz=z_nr=z_aenderung=
      z_loeschung=z_nachfolge_blz=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|lzzzzzzzzzzzz",
            &blz,&blz_len,&zweigstelle,&z_cnt,&z_name,&z_name_kurz,&z_plz,&z_ort,
            &z_pan,&z_bic,&z_pz,&z_nr,&z_aenderung,&z_loeschung,&z_nachfolge_blz)==FAILURE)RETURN_NULL();

      /* es muß noch eine zusätzliche Pointerschicht eingebaut werden, um nicht
       * immer den Fehler -38 (LUT2_PARTIAL_OK) zu bekommen, wie wenn man direkt
       * die Variablenpointer an lut_multiple() übergibt. Im alten Interface
       * werden immer alle Werte abgefragt; daher bekommt man in der Version
       * beim Aufruf dieser Funktion üblicherweise immer -38 zurück (außer,
       * falls auch alle Blocks der BLZ-Datei geladen wurden).
       */
   short_buf[1]=0;
   if(z_name){ZVAL_DTOR(z_name); pp_name=&p_name;} else pp_name=NULL;
   if(z_name_kurz){ZVAL_DTOR(z_name_kurz); pp_name_kurz=&p_name_kurz;} else pp_name_kurz=NULL;
   if(z_plz){ZVAL_DTOR(z_plz); pp_plz=&p_plz;} else pp_plz=NULL;
   if(z_ort){ZVAL_DTOR(z_ort); pp_ort=&p_ort;} else pp_ort=NULL;
   if(z_pan){ZVAL_DTOR(z_pan); pp_pan=&p_pan;} else pp_pan=NULL;
   if(z_bic){ZVAL_DTOR(z_bic); pp_bic=&p_bic;} else pp_bic=NULL;
   if(z_pz){ZVAL_DTOR(z_pz); pp_pz=&p_pz;} else pp_pz=NULL;
   if(z_nr){ZVAL_DTOR(z_nr); pp_nr=&p_nr;} else pp_nr=NULL;
   if(z_aenderung){ZVAL_DTOR(z_aenderung); pp_aenderung=&p_aenderung;} else pp_aenderung=NULL;
   if(z_loeschung){ZVAL_DTOR(z_loeschung); pp_loeschung=&p_loeschung;} else pp_loeschung=NULL;
   if(z_nachfolge_blz){ZVAL_DTOR(z_nachfolge_blz); pp_nachfolge_blz=&p_nachfolge_blz;} else pp_nachfolge_blz=NULL;

   ret=lut_multiple(blz,&cnt,NULL,pp_name,pp_name_kurz,pp_plz,pp_ort,pp_pan,pp_bic,
         pp_pz,pp_nr,pp_aenderung,pp_loeschung,pp_nachfolge_blz,NULL,NULL,NULL);

   if(zweigstelle>=cnt || (ret<OK && ret!=LUT2_PARTIAL_OK)){
      if(z_cnt){ZVAL_NULL(z_cnt);}
      if(z_name){ZVAL_NULL(z_name);}
      if(z_name_kurz){ZVAL_NULL(z_name_kurz);}
      if(z_plz){ZVAL_NULL(z_plz);}
      if(z_ort){ZVAL_NULL(z_ort);}
      if(z_pan){ZVAL_NULL(z_pan);}
      if(z_bic){ZVAL_NULL(z_bic);}
      if(z_pz){ZVAL_NULL(z_pz);}
      if(z_nr){ZVAL_NULL(z_nr);}
      if(z_aenderung){ZVAL_NULL(z_aenderung);}
      if(z_loeschung){ZVAL_NULL(z_loeschung);}
      if(z_nachfolge_blz){ZVAL_NULL(z_nachfolge_blz);}
      if(zweigstelle>=cnt){
         RETURN_LONG(LUT2_INDEX_OUT_OF_RANGE);
      }
      else{
         RETURN_LONG(ret);
      }
   }
   if(z_cnt)ZVAL_LONG(z_cnt,cnt);

#define Z_RETURN_STRING(z_name,lut2_name,p_name) if(z_name){ \
      if(lut2_block_status[lut2_name]==OK){ \
         ZVAL_STRING(z_name,p_name[zweigstelle],1); \
      } \
      else{ \
         ZVAL_NULL(z_name); \
      } \
   }
#define Z_RETURN_LONG(z_name,lut2_name,p_name) if(z_name){ \
      if(lut2_block_status[lut2_name]==OK){ \
         ZVAL_LONG(z_name,p_name[zweigstelle]); \
      } \
      else{ \
         ZVAL_NULL(z_name); \
      } \
   }
   Z_RETURN_STRING(z_name,LUT2_NAME,p_name)
   Z_RETURN_STRING(z_name_kurz,LUT2_NAME_KURZ,p_name_kurz)
   Z_RETURN_LONG(z_plz,LUT2_PLZ,p_plz)
   Z_RETURN_STRING(z_ort,LUT2_ORT,p_ort)
   Z_RETURN_LONG(z_pan,LUT2_PAN,p_pan)
   Z_RETURN_STRING(z_bic,LUT2_BIC,p_bic)
   Z_RETURN_LONG(z_nr,LUT2_NR,p_nr)
   Z_RETURN_LONG(z_nachfolge_blz,LUT2_NACHFOLGE_BLZ,p_nachfolge_blz)
   if(z_pz){
      if(lut2_block_status[LUT2_PZ]==OK){
         ZVAL_LONG(z_pz,p_pz);
      }
      else{
         ZVAL_NULL(z_pz);
      }
   }
   if(z_aenderung){
      if(lut2_block_status[LUT2_AENDERUNG]==OK){
         *short_buf=p_aenderung[zweigstelle];
         ZVAL_STRING(z_aenderung,short_buf,1);
      }
      else{
         ZVAL_NULL(z_aenderung);
      }
   }
   if(z_loeschung){
      if(lut2_block_status[LUT2_LOESCHUNG]==OK){
         ZVAL_LONG(z_loeschung,(int)p_loeschung[zweigstelle]-48);
      }
      else{
         ZVAL_NULL(z_loeschung);
      }
   }
   RETURN_LONG(ret);
}

PHP_FUNCTION(iban_gen)
{
   char *iban,*blz,*kto,i_buffer[64],blz2[16],kto2[16],*ptr,*dptr;
   const char *bic;
   int blz_len,kto_len,ret;
   zval *z_ret=NULL,*z_papier=NULL,*z_bic=NULL,*z_blz2=NULL,*z_kto2=NULL,*z_regel=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"ss|zzzzzz",
            &blz,&blz_len,&kto,&kto_len,&z_ret,&z_papier,&z_bic,&z_blz2,&z_kto2,&z_regel)==FAILURE)RETURN_NULL();
   iban=iban_bic_gen(blz,kto,&bic,blz2,kto2,&ret);
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   if(z_blz2){ /* Fehlerbehandlung erfolgt schon in der C-Funktion */
      ZVAL_DTOR(z_blz2);
      ZVAL_STRING(z_blz2,blz2,1);
   }
   if(z_kto2){
      ZVAL_DTOR(z_kto2);
      ZVAL_STRING(z_kto2,kto2,1);
   }
   if(z_regel){
      ZVAL_DTOR(z_regel);
      ZVAL_LONG(z_regel,lut_iban_regel(blz,0,NULL)/100);
   }
   if(iban){
         /* Ergebnis nach i_buffer kopieren (ohne Blanks) */
      for(ptr=iban,dptr=i_buffer;*ptr;ptr++)if(*ptr!=' ')*dptr++=*ptr;
      *dptr=0;
      if(z_papier){
         ZVAL_DTOR(z_papier);
         ZVAL_STRING(z_papier,iban,1);
      }
      if(z_bic){
         ZVAL_DTOR(z_bic);
         if(bic){
            ZVAL_STRING(z_bic,bic,1);
         }
         else{
            ZVAL_NULL(z_bic);
         }
      }
      free(iban);
      RETURN_STRING(i_buffer,1);
   }
   else{
      if(z_papier){
         ZVAL_DTOR(z_papier);
         ZVAL_NULL(z_papier);
      }
      if(z_bic){
         ZVAL_DTOR(z_bic);
         if(bic){
            ZVAL_STRING(z_bic,bic,1);
         }
         else{
            ZVAL_NULL(z_bic);
         }
      }
      RETURN_NULL();
   }
}

PHP_FUNCTION(iban_check)
{
   char *iban;
   int iban_len,ret,ret_kto;
   zval *z_ret_kto=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|z",
            &iban,&iban_len,&z_ret_kto)==FAILURE)RETURN_NULL();
   ret=iban_check(iban,&ret_kto);
   if(z_ret_kto){
      ZVAL_DTOR(z_ret_kto);
      ZVAL_LONG(z_ret_kto,ret_kto);
   }
   RETURN_LONG(ret);
}

PHP_FUNCTION(ci_check)
{
   char *ci;
   int ci_len,ret;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s",
            &ci,&ci_len)==FAILURE)RETURN_NULL();
   ret=ci_check(ci);
   RETURN_LONG(ret);
}

PHP_FUNCTION(iban2bic)
{
   char *iban=NULL,bptr[16],kptr[16];
   const char *bic1;
   int iban_len,ret;
   zval *z_ret=NULL,*z_blz=NULL,*z_kto=NULL;


   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zzz",
            &iban,&iban_len,&z_ret,&z_blz,&z_kto)==FAILURE)RETURN_NULL();
   if(!iban)RETURN_NULL();
   bic1=iban2bic(iban,&ret,bptr,kptr);
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   if(ret==IBAN2BIC_ONLY_GERMAN){
      if(z_blz){
         ZVAL_DTOR(z_blz);
         ZVAL_NULL(z_blz);
      }
      if(z_kto){
         ZVAL_DTOR(z_kto);
         ZVAL_NULL(z_kto);
      }
      RETURN_NULL();
   }
   else{
      if(z_blz){
         ZVAL_DTOR(z_blz);
         ZVAL_STRING(z_blz,bptr,1);
      }
      if(z_kto){
         ZVAL_DTOR(z_kto);
         ZVAL_STRING(z_kto,kptr,1);
      }
      RETURN_STRING(bic1,1);
   }
}

PHP_FUNCTION(ipi_gen)
{
   char *zweck,dst[24],papier[32];
   int zweck_len,ret;
   zval *z_ret,*z_papier;

   z_ret=z_papier=NULL;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zz",
            &zweck,&zweck_len,&z_ret,&z_papier)==FAILURE)RETURN_NULL();
   ret=ipi_gen(zweck,dst,papier);
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   if(z_papier)ZVAL_DTOR(z_papier);
   if(ret==OK){
      if(z_papier)ZVAL_STRING(z_papier,papier,1);
      RETURN_STRING(dst,1);
   }
   else{
      if(z_papier)ZVAL_NULL(z_papier);
      RETURN_NULL();
   }
}

PHP_FUNCTION(ipi_check)
{
   char *zweck;
   int zweck_len,ret;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s",
            &zweck,&zweck_len)==FAILURE)RETURN_NULL();
   ret=ipi_check(zweck);
   RETURN_LONG(ret);
}

PHP_FUNCTION(lut_suche_bic)
{
   char *such_name=NULL,**base_name;
   int such_name_len,ret,anzahl,i,j,*start_idx,*zweigstelle,*blz_base,anzahl_o,*idx_o,*cnt_o;
   long sort_uniq=-1; /* bei 1 sortieren, bei 2 sortieren + uniq */
   zval *z_ret=NULL,*z_blz=NULL,*z_zweigstelle=NULL,*z_cnt_o=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zzzlz",
            &such_name,&such_name_len,&z_ret,&z_blz,&z_zweigstelle,&sort_uniq,&z_cnt_o)==FAILURE)RETURN_NULL();
   if(!such_name)RETURN_NULL();
   if(sort_uniq<0)sort_uniq=INI_INT("konto_check.uniq");
   ret=lut_suche_bic(such_name,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_base);
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   if(ret!=OK)RETURN_NULL();
   if(z_blz){
      ZVAL_DTOR(z_blz);
      ZVAL_NULL(z_blz);
      array_init(z_blz);
   }
   if(z_zweigstelle){
      ZVAL_DTOR(z_zweigstelle);
      ZVAL_NULL(z_zweigstelle);
      array_init(z_zweigstelle);
   }
   if(z_cnt_o){
      ZVAL_DTOR(z_cnt_o);
      ZVAL_NULL(z_cnt_o);
      array_init(z_cnt_o);
   }
   array_init(return_value);
   if(sort_uniq)
      lut_suche_sort1(anzahl,blz_base,zweigstelle,start_idx,&anzahl_o,&idx_o,&cnt_o,sort_uniq>1);
   else{
      anzahl_o=anzahl;
      idx_o=start_idx;
      cnt_o=NULL;
   }
   for(i=0;i<anzahl_o;i++){
      j=idx_o[i];
      if(z_blz)add_index_long(z_blz,i,blz_base[j]);   /* Zweigstellen-Index */
      if(z_zweigstelle)add_index_long(z_zweigstelle,i,zweigstelle?zweigstelle[j]:0);   /* Zweigstelle */
      if(z_cnt_o)add_index_long(z_cnt_o,i,cnt_o?cnt_o[i]:1);   /* Anzahl Zweigstellen pro BLZ (v.a. interessant bei uniq) */
      add_index_string(return_value,i,base_name[j],1);
   }
   if(sort_uniq){
      kc_free((char*)idx_o);
      kc_free((char*)cnt_o);
   }
}

PHP_FUNCTION(lut_suche_namen)
{
   char *such_name=NULL,**base_name;
   int such_name_len,ret,anzahl,i,j,*start_idx,*zweigstelle,*blz_base,anzahl_o,*idx_o,*cnt_o;
   long sort_uniq=-1; /* bei 1 sortieren, bei 2 sortieren + uniq */
   zval *z_ret=NULL,*z_blz=NULL,*z_zweigstelle=NULL,*z_cnt_o=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zzzlz",
            &such_name,&such_name_len,&z_ret,&z_blz,&z_zweigstelle,&sort_uniq,&z_cnt_o)==FAILURE)RETURN_NULL();
   if(!such_name)RETURN_NULL();
   if(sort_uniq<0)sort_uniq=INI_INT("konto_check.uniq");
   ret=lut_suche_namen(such_name,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_base);
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   if(ret!=OK)RETURN_NULL();
   if(z_blz){
      ZVAL_DTOR(z_blz);
      ZVAL_NULL(z_blz);
      array_init(z_blz);
   }
   if(z_zweigstelle){
      ZVAL_DTOR(z_zweigstelle);
      ZVAL_NULL(z_zweigstelle);
      array_init(z_zweigstelle);
   }
   if(z_cnt_o){
      ZVAL_DTOR(z_cnt_o);
      ZVAL_NULL(z_cnt_o);
      array_init(z_cnt_o);
   }
   array_init(return_value);
   if(sort_uniq)
      lut_suche_sort1(anzahl,blz_base,zweigstelle,start_idx,&anzahl_o,&idx_o,&cnt_o,sort_uniq>1);
   else{
      anzahl_o=anzahl;
      idx_o=start_idx;
      cnt_o=NULL;
   }
   for(i=0;i<anzahl_o;i++){
      j=idx_o[i];
      if(z_blz)add_index_long(z_blz,i,blz_base[j]);   /* Zweigstellen-Index */
      if(z_zweigstelle)add_index_long(z_zweigstelle,i,zweigstelle?zweigstelle[j]:0);   /* Zweigstelle */
      if(z_cnt_o)add_index_long(z_cnt_o,i,cnt_o?cnt_o[i]:1);   /* Anzahl Zweigstellen pro BLZ (v.a. interessant bei uniq) */
      add_index_string(return_value,i,base_name[j],1);
   }
   if(sort_uniq){
      kc_free((char*)idx_o);
      kc_free((char*)cnt_o);
   }
}

PHP_FUNCTION(lut_suche_namen_kurz)
{
   char *such_name=NULL,**base_name;
   int such_name_len,ret,anzahl,i,j,*start_idx,*zweigstelle,*blz_base,anzahl_o,*idx_o,*cnt_o;
   long sort_uniq=-1; /* bei 1 sortieren, bei 2 sortieren + uniq */
   zval *z_ret=NULL,*z_blz=NULL,*z_zweigstelle=NULL,*z_cnt_o=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zzzlz",
            &such_name,&such_name_len,&z_ret,&z_blz,&z_zweigstelle,&sort_uniq,&z_cnt_o)==FAILURE)RETURN_NULL();
   if(!such_name)RETURN_NULL();
   if(sort_uniq<0)sort_uniq=INI_INT("konto_check.uniq");
   ret=lut_suche_namen_kurz(such_name,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_base);
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   if(ret!=OK)RETURN_NULL();
   if(z_blz){
      ZVAL_DTOR(z_blz);
      ZVAL_NULL(z_blz);
      array_init(z_blz);
   }
   if(z_zweigstelle){
      ZVAL_DTOR(z_zweigstelle);
      ZVAL_NULL(z_zweigstelle);
      array_init(z_zweigstelle);
   }
   if(z_cnt_o){
      ZVAL_DTOR(z_cnt_o);
      ZVAL_NULL(z_cnt_o);
      array_init(z_cnt_o);
   }
   array_init(return_value);
   if(sort_uniq)
      lut_suche_sort1(anzahl,blz_base,zweigstelle,start_idx,&anzahl_o,&idx_o,&cnt_o,sort_uniq>1);
   else{
      anzahl_o=anzahl;
      idx_o=start_idx;
      cnt_o=NULL;
   }
   for(i=0;i<anzahl_o;i++){
      j=idx_o[i];
      if(z_blz)add_index_long(z_blz,i,blz_base[j]);   /* Zweigstellen-Index */
      if(z_zweigstelle)add_index_long(z_zweigstelle,i,zweigstelle?zweigstelle[j]:0);   /* Zweigstelle */
      if(z_cnt_o)add_index_long(z_cnt_o,i,cnt_o?cnt_o[i]:1);   /* Anzahl Zweigstellen pro BLZ (v.a. interessant bei uniq) */
      add_index_string(return_value,i,base_name[j],1);
   }
   if(sort_uniq){
      kc_free((char*)idx_o);
      kc_free((char*)cnt_o);
   }
}

PHP_FUNCTION(lut_suche_ort)
{
   char *such_name=NULL,**base_name;
   int such_name_len,ret,anzahl,i,j,*start_idx,*zweigstelle,*blz_base,anzahl_o,*idx_o,*cnt_o;
   long sort_uniq=-1; /* bei 1 sortieren, bei 2 sortieren + uniq */
   zval *z_ret=NULL,*z_blz=NULL,*z_zweigstelle=NULL,*z_cnt_o=NULL;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s|zzzlz",
            &such_name,&such_name_len,&z_ret,&z_blz,&z_zweigstelle,&sort_uniq,&z_cnt_o)==FAILURE)RETURN_NULL();
   if(!such_name)RETURN_NULL();
   if(sort_uniq<0)sort_uniq=INI_INT("konto_check.uniq");
   ret=lut_suche_ort(such_name,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_base);
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   if(ret!=OK)RETURN_NULL();
   if(z_blz){
      ZVAL_DTOR(z_blz);
      ZVAL_NULL(z_blz);
      array_init(z_blz);
   }
   if(z_zweigstelle){
      ZVAL_DTOR(z_zweigstelle);
      ZVAL_NULL(z_zweigstelle);
      array_init(z_zweigstelle);
   }
   if(z_cnt_o){
      ZVAL_DTOR(z_cnt_o);
      ZVAL_NULL(z_cnt_o);
      array_init(z_cnt_o);
   }
   array_init(return_value);
   if(sort_uniq)
      lut_suche_sort1(anzahl,blz_base,zweigstelle,start_idx,&anzahl_o,&idx_o,&cnt_o,sort_uniq>1);
   else{
      anzahl_o=anzahl;
      idx_o=start_idx;
      cnt_o=NULL;
   }
   for(i=0;i<anzahl_o;i++){
      j=idx_o[i];
      if(z_blz)add_index_long(z_blz,i,blz_base[j]);   /* Zweigstellen-Index */
      if(z_zweigstelle)add_index_long(z_zweigstelle,i,zweigstelle?zweigstelle[j]:0);   /* Zweigstelle */
      if(z_cnt_o)add_index_long(z_cnt_o,i,cnt_o?cnt_o[i]:1);   /* Anzahl Zweigstellen pro BLZ (v.a. interessant bei uniq) */
      add_index_string(return_value,i,base_name[j],1);
   }
   if(sort_uniq){
      kc_free((char*)idx_o);
      kc_free((char*)cnt_o);
   }
}

PHP_FUNCTION(lut_suche_pz)
{
   int such1,such2,ret,anzahl,i,j,*base_name,*start_idx,*zweigstelle,*blz_base,anzahl_o,*idx_o,*cnt_o;
   long sort_uniq=-1; /* bei 1 sortieren, bei 2 sortieren + uniq */
   zval *z_ret=NULL,*z_blz=NULL,*z_zweigstelle=NULL,*z_cnt_o=NULL;

   such2=0;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l|lzzzlz",
            &such1,&such2,&z_ret,&z_blz,&z_zweigstelle,&sort_uniq,&z_cnt_o)==FAILURE)RETURN_NULL();
   if(sort_uniq<0)sort_uniq=INI_INT("konto_check.uniq");
   ret=lut_suche_pz(such1,such2,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_base);
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   if(ret!=OK)RETURN_NULL();
   if(z_blz){
      ZVAL_DTOR(z_blz);
      ZVAL_NULL(z_blz);
      array_init(z_blz);
   }
   if(z_zweigstelle){
      ZVAL_DTOR(z_zweigstelle);
      ZVAL_NULL(z_zweigstelle);
      array_init(z_zweigstelle);
   }
   if(z_cnt_o){
      ZVAL_DTOR(z_cnt_o);
      ZVAL_NULL(z_cnt_o);
      array_init(z_cnt_o);
   }
   array_init(return_value);
   if(sort_uniq)
      lut_suche_sort1(anzahl,blz_base,zweigstelle,start_idx,&anzahl_o,&idx_o,&cnt_o,sort_uniq>1);
   else{
      anzahl_o=anzahl;
      idx_o=start_idx;
      cnt_o=NULL;
   }
   for(i=0;i<anzahl_o;i++){
      j=idx_o[i];
      if(z_blz)add_index_long(z_blz,i,blz_base[j]);   /* Zweigstellen-Index */
      if(z_zweigstelle)add_index_long(z_zweigstelle,i,zweigstelle?zweigstelle[j]:0);   /* Zweigstelle */
      if(z_cnt_o)add_index_long(z_cnt_o,i,cnt_o?cnt_o[i]:1);   /* Anzahl Zweigstellen pro BLZ (v.a. interessant bei uniq) */
      add_index_long(return_value,i,base_name[j]);
   }
   if(sort_uniq){
      kc_free((char*)idx_o);
      kc_free((char*)cnt_o);
   }
}

PHP_FUNCTION(lut_suche_blz)
{
   int such1,such2,ret,anzahl,i,j,*base_name,*start_idx,*zweigstelle,*blz_base,anzahl_o,*idx_o,*cnt_o;
   long sort_uniq=-1; /* bei 1 sortieren, bei 2 sortieren + uniq */
   zval *z_ret=NULL,*z_blz=NULL,*z_zweigstelle=NULL,*z_cnt_o=NULL;

   such2=0;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l|lzzzlz",
            &such1,&such2,&z_ret,&z_blz,&z_zweigstelle,&sort_uniq,&z_cnt_o)==FAILURE)RETURN_NULL();
   if(sort_uniq<0)sort_uniq=INI_INT("konto_check.uniq");
   ret=lut_suche_blz(such1,such2,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_base);
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   if(ret!=OK)RETURN_NULL();
   if(z_blz){
      ZVAL_DTOR(z_blz);
      ZVAL_NULL(z_blz);
      array_init(z_blz);
   }
   if(z_zweigstelle){
      ZVAL_DTOR(z_zweigstelle);
      ZVAL_NULL(z_zweigstelle);
      array_init(z_zweigstelle);
   }
   if(z_cnt_o){
      ZVAL_DTOR(z_cnt_o);
      ZVAL_NULL(z_cnt_o);
      array_init(z_cnt_o);
   }
   array_init(return_value);
   if(sort_uniq)
      lut_suche_sort1(anzahl,blz_base,zweigstelle,start_idx,&anzahl_o,&idx_o,&cnt_o,sort_uniq>1);
   else{
      anzahl_o=anzahl;
      idx_o=start_idx;
      cnt_o=NULL;
   }
   for(i=0;i<anzahl_o;i++){
      j=idx_o[i];
      if(z_blz)add_index_long(z_blz,i,blz_base[j]);   /* Zweigstellen-Index */
      if(z_zweigstelle)add_index_long(z_zweigstelle,i,zweigstelle?zweigstelle[j]:0);   /* Zweigstelle */
      if(z_cnt_o)add_index_long(z_cnt_o,i,cnt_o?cnt_o[i]:1);   /* Anzahl Zweigstellen pro BLZ (v.a. interessant bei uniq) */
      add_index_long(return_value,i,base_name[j]);
   }
   if(sort_uniq){
      kc_free((char*)idx_o);
      kc_free((char*)cnt_o);
   }
}

PHP_FUNCTION(lut_suche_plz)
{
   int such1,such2,ret,anzahl,i,j,*base_name,*start_idx,*zweigstelle,*blz_base,anzahl_o,*idx_o,*cnt_o;
   long sort_uniq=-1; /* bei 1 sortieren, bei 2 sortieren + uniq */
   zval *z_ret=NULL,*z_blz=NULL,*z_zweigstelle=NULL,*z_cnt_o=NULL;

   such2=0;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l|lzzzlz",
            &such1,&such2,&z_ret,&z_blz,&z_zweigstelle,&sort_uniq,&z_cnt_o)==FAILURE)RETURN_NULL();
   if(sort_uniq<0)sort_uniq=INI_INT("konto_check.uniq");
   ret=lut_suche_plz(such1,such2,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_base);
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   if(ret!=OK)RETURN_NULL();
   if(z_blz){
      ZVAL_DTOR(z_blz);
      ZVAL_NULL(z_blz);
      array_init(z_blz);
   }
   if(z_zweigstelle){
      ZVAL_DTOR(z_zweigstelle);
      ZVAL_NULL(z_zweigstelle);
      array_init(z_zweigstelle);
   }
   if(z_cnt_o){
      ZVAL_DTOR(z_cnt_o);
      ZVAL_NULL(z_cnt_o);
      array_init(z_cnt_o);
   }
   array_init(return_value);
   if(sort_uniq)
      lut_suche_sort1(anzahl,blz_base,zweigstelle,start_idx,&anzahl_o,&idx_o,&cnt_o,sort_uniq>1);
   else{
      anzahl_o=anzahl;
      idx_o=start_idx;
      cnt_o=NULL;
   }
   for(i=0;i<anzahl_o;i++){
      j=idx_o[i];
      if(z_blz)add_index_long(z_blz,i,blz_base[j]);   /* Zweigstellen-Index */
      if(z_zweigstelle)add_index_long(z_zweigstelle,i,zweigstelle?zweigstelle[j]:0);   /* Zweigstelle */
      if(z_cnt_o)add_index_long(z_cnt_o,i,cnt_o?cnt_o[i]:1);   /* Anzahl Zweigstellen pro BLZ (v.a. interessant bei uniq) */
      add_index_long(return_value,i,base_name[j]);
   }
   if(sort_uniq){
      kc_free((char*)idx_o);
      kc_free((char*)cnt_o);
   }
}

PHP_FUNCTION(lut_suche_regel)
{
   int such1,such2,ret,anzahl,i,j,*base_name,*start_idx,*zweigstelle,*blz_base,anzahl_o,*idx_o,*cnt_o;
   long sort_uniq=-1; /* bei 1 sortieren, bei 2 sortieren + uniq */
   zval *z_ret=NULL,*z_blz=NULL,*z_zweigstelle=NULL,*z_cnt_o=NULL;

   such2=0;
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l|lzzzlz",
            &such1,&such2,&z_ret,&z_blz,&z_zweigstelle,&sort_uniq,&z_cnt_o)==FAILURE)RETURN_NULL();
   if(sort_uniq<0)sort_uniq=INI_INT("konto_check.uniq");
   ret=lut_suche_regel(such1,such2,&anzahl,&start_idx,&zweigstelle,&base_name,&blz_base);
   if(z_ret){
      ZVAL_DTOR(z_ret);
      ZVAL_LONG(z_ret,ret);
   }
   if(ret!=OK)RETURN_NULL();
   if(z_blz){
      ZVAL_DTOR(z_blz);
      ZVAL_NULL(z_blz);
      array_init(z_blz);
   }
   if(z_zweigstelle){
      ZVAL_DTOR(z_zweigstelle);
      ZVAL_NULL(z_zweigstelle);
      array_init(z_zweigstelle);
   }
   if(z_cnt_o){
      ZVAL_DTOR(z_cnt_o);
      ZVAL_NULL(z_cnt_o);
      array_init(z_cnt_o);
   }
   array_init(return_value);
   if(sort_uniq)
      lut_suche_sort1(anzahl,blz_base,zweigstelle,start_idx,&anzahl_o,&idx_o,&cnt_o,sort_uniq>1);
   else{
      anzahl_o=anzahl;
      idx_o=start_idx;
      cnt_o=NULL;
   }
   for(i=0;i<anzahl_o;i++){
      j=idx_o[i];
      if(z_blz)add_index_long(z_blz,i,blz_base[j]);   /* Zweigstellen-Index */
      if(z_zweigstelle)add_index_long(z_zweigstelle,i,zweigstelle?zweigstelle[j]:0);   /* Zweigstelle */
      if(z_cnt_o)add_index_long(z_cnt_o,i,cnt_o?cnt_o[i]:1);   /* Anzahl Zweigstellen pro BLZ (v.a. interessant bei uniq) */
      add_index_long(return_value,i,base_name[j]);
   }
   if(sort_uniq){
      kc_free((char*)idx_o);
      kc_free((char*)cnt_o);
   }
}



PHP_FUNCTION(kto_check_retval)
{
   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"")==FAILURE)RETURN_NULL();
   array_init(return_value);
   add_assoc_long(return_value,"IBAN_CHKSUM_OK_NACHFOLGE_BLZ_DEFINED",-140);
   add_assoc_long(return_value,"LUT2_NOT_ALL_IBAN_BLOCKS_LOADED",-139);
   add_assoc_long(return_value,"LUT2_NOT_YET_VALID_PARTIAL_OK",-138);
   add_assoc_long(return_value,"LUT2_NO_LONGER_VALID_PARTIAL_OK",-137);
   add_assoc_long(return_value,"LUT2_BLOCKS_MISSING",-136);
   add_assoc_long(return_value,"FALSE_UNTERKONTO_ATTACHED",-135);
   add_assoc_long(return_value,"BLZ_BLACKLISTED",-134);
   add_assoc_long(return_value,"BLZ_MARKED_AS_DELETED",-133);
   add_assoc_long(return_value,"IBAN_CHKSUM_OK_SOMETHING_WRONG",-132);
   add_assoc_long(return_value,"IBAN_CHKSUM_OK_NO_IBAN_CALCULATION",-131);
   add_assoc_long(return_value,"IBAN_CHKSUM_OK_RULE_IGNORED",-130);
   add_assoc_long(return_value,"IBAN_CHKSUM_OK_UNTERKTO_MISSING",-129);
   add_assoc_long(return_value,"IBAN_INVALID_RULE",-128);
   add_assoc_long(return_value,"IBAN_AMBIGUOUS_KTO",-127);
   add_assoc_long(return_value,"IBAN_RULE_NOT_IMPLEMENTED",-126);
   add_assoc_long(return_value,"IBAN_RULE_UNKNOWN",-125);
   add_assoc_long(return_value,"NO_IBAN_CALCULATION",-124);
   add_assoc_long(return_value,"OLD_BLZ_OK_NEW_NOT",-123);
   add_assoc_long(return_value,"LUT2_IBAN_REGEL_NOT_INITIALIZED",-122);
   add_assoc_long(return_value,"INVALID_IBAN_LENGTH",-121);
   add_assoc_long(return_value,"LUT2_NO_ACCOUNT_GIVEN",-120);
   add_assoc_long(return_value,"LUT2_VOLLTEXT_INVALID_CHAR",-119);
   add_assoc_long(return_value,"LUT2_VOLLTEXT_SINGLE_WORD_ONLY",-118);
   add_assoc_long(return_value,"LUT_SUCHE_INVALID_RSC",-117);
   add_assoc_long(return_value,"LUT_SUCHE_INVALID_CMD",-116);
   add_assoc_long(return_value,"LUT_SUCHE_INVALID_CNT",-115);
   add_assoc_long(return_value,"LUT2_VOLLTEXT_NOT_INITIALIZED",-114);
   add_assoc_long(return_value,"NO_OWN_IBAN_CALCULATION",-113);
   add_assoc_long(return_value,"KTO_CHECK_UNSUPPORTED_COMPRESSION",-112);
   add_assoc_long(return_value,"KTO_CHECK_INVALID_COMPRESSION_LIB",-111);
   add_assoc_long(return_value,"OK_UNTERKONTO_ATTACHED_OLD",-110);
   add_assoc_long(return_value,"KTO_CHECK_DEFAULT_BLOCK_INVALID",-109);
   add_assoc_long(return_value,"KTO_CHECK_DEFAULT_BLOCK_FULL",-108);
   add_assoc_long(return_value,"KTO_CHECK_NO_DEFAULT_BLOCK",-107);
   add_assoc_long(return_value,"KTO_CHECK_KEY_NOT_FOUND",-106);
   add_assoc_long(return_value,"LUT2_NO_LONGER_VALID_BETTER",-105);
   add_assoc_long(return_value,"DTA_SRC_KTO_DIFFERENT",-104);
   add_assoc_long(return_value,"DTA_SRC_BLZ_DIFFERENT",-103);
   add_assoc_long(return_value,"DTA_CR_LF_IN_FILE",-102);
   add_assoc_long(return_value,"DTA_INVALID_C_EXTENSION",-101);
   add_assoc_long(return_value,"DTA_FOUND_SET_A_NOT_C",-100);
   add_assoc_long(return_value,"DTA_FOUND_SET_E_NOT_C",-99);
   add_assoc_long(return_value,"DTA_FOUND_SET_C_NOT_EXTENSION",-98);
   add_assoc_long(return_value,"DTA_FOUND_SET_E_NOT_EXTENSION",-97);
   add_assoc_long(return_value,"DTA_INVALID_EXTENSION_COUNT",-96);
   add_assoc_long(return_value,"DTA_INVALID_NUM",-95);
   add_assoc_long(return_value,"DTA_INVALID_CHARS",-94);
   add_assoc_long(return_value,"DTA_CURRENCY_NOT_EURO",-93);
   add_assoc_long(return_value,"DTA_EMPTY_AMOUNT",-92);
   add_assoc_long(return_value,"DTA_INVALID_TEXT_KEY",-91);
   add_assoc_long(return_value,"DTA_EMPTY_STRING",-90);
   add_assoc_long(return_value,"DTA_MARKER_A_NOT_FOUND",-89);
   add_assoc_long(return_value,"DTA_MARKER_C_NOT_FOUND",-88);
   add_assoc_long(return_value,"DTA_MARKER_E_NOT_FOUND",-87);
   add_assoc_long(return_value,"DTA_INVALID_SET_C_LEN",-86);
   add_assoc_long(return_value,"DTA_INVALID_SET_LEN",-85);
   add_assoc_long(return_value,"DTA_WAERUNG_NOT_EURO",-84);
   add_assoc_long(return_value,"DTA_INVALID_ISSUE_DATE",-83);
   add_assoc_long(return_value,"DTA_INVALID_DATE",-82);
   add_assoc_long(return_value,"DTA_FORMAT_ERROR",-81);
   add_assoc_long(return_value,"DTA_FILE_WITH_ERRORS",-80);
   add_assoc_long(return_value,"INVALID_SEARCH_RANGE",-79);
   add_assoc_long(return_value,"KEY_NOT_FOUND",-78);
   add_assoc_long(return_value,"BAV_FALSE",-77);
   add_assoc_long(return_value,"LUT2_NO_USER_BLOCK",-76);
   add_assoc_long(return_value,"INVALID_SET",-75);
   add_assoc_long(return_value,"NO_GERMAN_BIC",-74);
   add_assoc_long(return_value,"IPI_CHECK_INVALID_LENGTH",-73);
   add_assoc_long(return_value,"IPI_INVALID_CHARACTER",-72);
   add_assoc_long(return_value,"IPI_INVALID_LENGTH",-71);
   add_assoc_long(return_value,"LUT1_FILE_USED",-70);
   add_assoc_long(return_value,"MISSING_PARAMETER",-69);
   add_assoc_long(return_value,"IBAN2BIC_ONLY_GERMAN",-68);
   add_assoc_long(return_value,"IBAN_OK_KTO_NOT",-67);
   add_assoc_long(return_value,"KTO_OK_IBAN_NOT",-66);
   add_assoc_long(return_value,"TOO_MANY_SLOTS",-65);
   add_assoc_long(return_value,"INIT_FATAL_ERROR",-64);
   add_assoc_long(return_value,"INCREMENTAL_INIT_NEEDS_INFO",-63);
   add_assoc_long(return_value,"INCREMENTAL_INIT_FROM_DIFFERENT_FILE",-62);
   add_assoc_long(return_value,"DEBUG_ONLY_FUNCTION",-61);
   add_assoc_long(return_value,"LUT2_INVALID",-60);
   add_assoc_long(return_value,"LUT2_NOT_YET_VALID",-59);
   add_assoc_long(return_value,"LUT2_NO_LONGER_VALID",-58);
   add_assoc_long(return_value,"LUT2_GUELTIGKEIT_SWAPPED",-57);
   add_assoc_long(return_value,"LUT2_INVALID_GUELTIGKEIT",-56);
   add_assoc_long(return_value,"LUT2_INDEX_OUT_OF_RANGE",-55);
   add_assoc_long(return_value,"LUT2_INIT_IN_PROGRESS",-54);
   add_assoc_long(return_value,"LUT2_BLZ_NOT_INITIALIZED",-53);
   add_assoc_long(return_value,"LUT2_FILIALEN_NOT_INITIALIZED",-52);
   add_assoc_long(return_value,"LUT2_NAME_NOT_INITIALIZED",-51);
   add_assoc_long(return_value,"LUT2_PLZ_NOT_INITIALIZED",-50);
   add_assoc_long(return_value,"LUT2_ORT_NOT_INITIALIZED",-49);
   add_assoc_long(return_value,"LUT2_NAME_KURZ_NOT_INITIALIZED",-48);
   add_assoc_long(return_value,"LUT2_PAN_NOT_INITIALIZED",-47);
   add_assoc_long(return_value,"LUT2_BIC_NOT_INITIALIZED",-46);
   add_assoc_long(return_value,"LUT2_PZ_NOT_INITIALIZED",-45);
   add_assoc_long(return_value,"LUT2_NR_NOT_INITIALIZED",-44);
   add_assoc_long(return_value,"LUT2_AENDERUNG_NOT_INITIALIZED",-43);
   add_assoc_long(return_value,"LUT2_LOESCHUNG_NOT_INITIALIZED",-42);
   add_assoc_long(return_value,"LUT2_NACHFOLGE_BLZ_NOT_INITIALIZED",-41);
   add_assoc_long(return_value,"LUT2_NOT_INITIALIZED",-40);
   add_assoc_long(return_value,"LUT2_FILIALEN_MISSING",-39);
   add_assoc_long(return_value,"LUT2_PARTIAL_OK",-38);
   add_assoc_long(return_value,"LUT2_Z_BUF_ERROR",-37);
   add_assoc_long(return_value,"LUT2_Z_MEM_ERROR",-36);
   add_assoc_long(return_value,"LUT2_Z_DATA_ERROR",-35);
   add_assoc_long(return_value,"LUT2_BLOCK_NOT_IN_FILE",-34);
   add_assoc_long(return_value,"LUT2_DECOMPRESS_ERROR",-33);
   add_assoc_long(return_value,"LUT2_COMPRESS_ERROR",-32);
   add_assoc_long(return_value,"LUT2_FILE_CORRUPTED",-31);
   add_assoc_long(return_value,"LUT2_NO_SLOT_FREE",-30);
   add_assoc_long(return_value,"UNDEFINED_SUBMETHOD",-29);
   add_assoc_long(return_value,"EXCLUDED_AT_COMPILETIME",-28);
   add_assoc_long(return_value,"INVALID_LUT_VERSION",-27);
   add_assoc_long(return_value,"INVALID_PARAMETER_STELLE1",-26);
   add_assoc_long(return_value,"INVALID_PARAMETER_COUNT",-25);
   add_assoc_long(return_value,"INVALID_PARAMETER_PRUEFZIFFER",-24);
   add_assoc_long(return_value,"INVALID_PARAMETER_WICHTUNG",-23);
   add_assoc_long(return_value,"INVALID_PARAMETER_METHODE",-22);
   add_assoc_long(return_value,"LIBRARY_INIT_ERROR",-21);
   add_assoc_long(return_value,"LUT_CRC_ERROR",-20);
   add_assoc_long(return_value,"FALSE_GELOESCHT",-19);
   add_assoc_long(return_value,"OK_NO_CHK_GELOESCHT",-18);
   add_assoc_long(return_value,"OK_GELOESCHT",-17);
   add_assoc_long(return_value,"BLZ_GELOESCHT",-16);
   add_assoc_long(return_value,"INVALID_BLZ_FILE",-15);
   add_assoc_long(return_value,"LIBRARY_IS_NOT_THREAD_SAFE",-14);
   add_assoc_long(return_value,"FATAL_ERROR",-13);
   add_assoc_long(return_value,"INVALID_KTO_LENGTH",-12);
   add_assoc_long(return_value,"FILE_WRITE_ERROR",-11);
   add_assoc_long(return_value,"FILE_READ_ERROR",-10);
   add_assoc_long(return_value,"ERROR_MALLOC",-9);
   add_assoc_long(return_value,"NO_BLZ_FILE",-8);
   add_assoc_long(return_value,"INVALID_LUT_FILE",-7);
   add_assoc_long(return_value,"NO_LUT_FILE",-6);
   add_assoc_long(return_value,"INVALID_BLZ_LENGTH",-5);
   add_assoc_long(return_value,"INVALID_BLZ",-4);
   add_assoc_long(return_value,"INVALID_KTO",-3);
   add_assoc_long(return_value,"NOT_IMPLEMENTED",-2);
   add_assoc_long(return_value,"NOT_DEFINED",-1);
   add_assoc_long(return_value,"FALSE",0);
   add_assoc_long(return_value,"OK",1);
   add_assoc_long(return_value,"OK_NO_CHK",2);
   add_assoc_long(return_value,"OK_TEST_BLZ_USED",3);
   add_assoc_long(return_value,"LUT2_VALID",4);
   add_assoc_long(return_value,"LUT2_NO_VALID_DATE",5);
   add_assoc_long(return_value,"LUT1_SET_LOADED",6);
   add_assoc_long(return_value,"LUT1_FILE_GENERATED",7);
   add_assoc_long(return_value,"DTA_FILE_WITH_WARNINGS",8);
   add_assoc_long(return_value,"LUT_V2_FILE_GENERATED",9);
   add_assoc_long(return_value,"KTO_CHECK_VALUE_REPLACED",10);
   add_assoc_long(return_value,"OK_UNTERKONTO_POSSIBLE",11);
   add_assoc_long(return_value,"OK_UNTERKONTO_GIVEN",12);
   add_assoc_long(return_value,"OK_SLOT_CNT_MIN_USED",13);
   add_assoc_long(return_value,"SOME_KEYS_NOT_FOUND",14);
   add_assoc_long(return_value,"LUT2_KTO_NOT_CHECKED",15);
   add_assoc_long(return_value,"LUT2_OK_WITHOUT_IBAN_RULES",16);
   add_assoc_long(return_value,"OK_NACHFOLGE_BLZ_USED",17);
   add_assoc_long(return_value,"OK_KTO_REPLACED",18);
   add_assoc_long(return_value,"OK_BLZ_REPLACED",19);
   add_assoc_long(return_value,"OK_BLZ_KTO_REPLACED",20);
   add_assoc_long(return_value,"OK_IBAN_WITHOUT_KC_TEST",21);
   add_assoc_long(return_value,"OK_INVALID_FOR_IBAN",22);
   add_assoc_long(return_value,"OK_HYPO_REQUIRES_KTO",23);
   add_assoc_long(return_value,"OK_KTO_REPLACED_NO_PZ",24);
   add_assoc_long(return_value,"OK_UNTERKONTO_ATTACHED",25);
}

PHP_FUNCTION(get_kto_check_version)
{
   long type=0;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"|l",&type)==FAILURE)RETURN_NULL();
   switch(type){
      case 0: RETURN_STRING(get_kto_check_version(),1);
      default: RETURN_STRING(get_kto_check_version_x(type),1);
   }
}

PHP_FUNCTION(set_default_compression)
{
   long mode=0;

   if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",&mode)==FAILURE)RETURN_NULL();
   RETURN_LONG(set_default_compression(mode));
}

#if CHECK_MALLOC
PHP_FUNCTION(malloc_report)
{
   RETURN_STRING(malloc_report_string(0),1);
}

PHP_FUNCTION(malloc_cnt)
{
   RETURN_LONG(malloc_entry_cnt());
}
#else
PHP_FUNCTION(malloc_report)
{
   RETURN_NULL();
}

PHP_FUNCTION(malloc_cnt)
{
   RETURN_NULL();
}
#endif
