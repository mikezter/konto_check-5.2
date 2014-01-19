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

#ifndef PHP_KONTO_CHECK_H
#define PHP_KONTO_CHECK_H 1

#ifdef HAVE_CONFIG_H
#   undef PACKAGE_BUGREPORT
#   undef PACKAGE_NAME
#   undef PACKAGE_STRING
#   undef PACKAGE_VERSION
#   include "config.h"
#endif

   /* die check_malloc Routinen wurden entfernt */
#define CHECK_MALLOC 0

#ifndef BESCHREIBUNG_TXT
#define BESCHREIBUNG_TXT 0
#endif

#ifndef BAV_KOMPATIBEL
#define BAV_KOMPATIBEL 0
#endif

#define PHP_KONTO_CHECK_VERSION "5.2"
#define PHP_KONTO_CHECK_EXTNAME "konto_check"

#define USE_RINIT       0  /* bei 1: (optional) request init benutzen */
#define USE_RSHUTDOWN   1  /* bei 1: (optional) request shutdown benutzen */
#define USE_RET         1  /* bei 1: numerischen Rückgabewert mit add_assoc_long hinzufügen */
#define USE_RET1        1  /* bei 1: Klartext-Rückgabewert mit add_assoc_string hinzufügen */
#define USE_RET2        1  /* bei 1: kurzen Klartext-Rückgabewert mit add_assoc_string hinzufügen */
#define USE_RET3        1  /* bei 1: HTML-Rückgabewert mit add_assoc_string hinzufügen */
#define USE_ARGS        0  /* bei 1: einige Parameter (BLZ, Zweigstelle etc.) im Rückgabewert hinzufügen */
#define LUT_NAME_BUFFER 256

PHP_MINIT_FUNCTION(konto_check);
PHP_MSHUTDOWN_FUNCTION(konto_check);
PHP_MINFO_FUNCTION(konto_check);

#if USE_RINIT || CHECK_MALLOC
PHP_RINIT_FUNCTION(konto_check);
#endif

#if USE_RSHUTDOWN
PHP_RSHUTDOWN_FUNCTION(konto_check);
#endif

PHP_FUNCTION(kto_check);
PHP_FUNCTION(kto_check_str);
PHP_FUNCTION(lut_init);
PHP_FUNCTION(kto_check_init);
PHP_FUNCTION(generate_lut2);
PHP_FUNCTION(current_lutfile_name);
PHP_FUNCTION(read_lut_block);
PHP_FUNCTION(write_lut_block);
PHP_FUNCTION(copy_lutfile);
PHP_FUNCTION(kto_check_pz);
PHP_FUNCTION(kto_check_blz);
PHP_FUNCTION(kto_check_pz_dbg);
PHP_FUNCTION(kto_check_regel_dbg);
PHP_FUNCTION(kto_check_blz_dbg);
PHP_FUNCTION(kto_check_retval);
PHP_FUNCTION(keep_raw_data);
PHP_FUNCTION(kto_check_encoding);
PHP_FUNCTION(kto_check_encoding_str);
PHP_FUNCTION(kto_check_retval2txt);
PHP_FUNCTION(kto_check_retval2iso);
PHP_FUNCTION(kto_check_retval2html);
PHP_FUNCTION(kto_check_retval2txt_short);
PHP_FUNCTION(kto_check_retval2dos);
PHP_FUNCTION(kto_check_retval2utf8);
PHP_FUNCTION(get_kto_check_version);
PHP_FUNCTION(malloc_report);
PHP_FUNCTION(malloc_cnt);
PHP_FUNCTION(set_default_compression);
PHP_FUNCTION(iban_gen);
PHP_FUNCTION(iban_check);
PHP_FUNCTION(ci_check);
PHP_FUNCTION(iban2bic);
PHP_FUNCTION(ipi_gen);
PHP_FUNCTION(ipi_check);
PHP_FUNCTION(lut_cleanup);
PHP_FUNCTION(lut_filialen);
PHP_FUNCTION(lut2_status);
PHP_FUNCTION(lut_valid);
PHP_FUNCTION(lut_multiple);
PHP_FUNCTION(lut_info);
PHP_FUNCTION(lut_blz);
PHP_FUNCTION(lut_blocks);
PHP_FUNCTION(pz2str);
PHP_FUNCTION(lut_name);
PHP_FUNCTION(lut_name_kurz);
PHP_FUNCTION(lut_plz);
PHP_FUNCTION(lut_ort);
PHP_FUNCTION(lut_pan);
PHP_FUNCTION(lut_bic);
PHP_FUNCTION(lut_nr);
PHP_FUNCTION(lut_pz);
PHP_FUNCTION(lut_nachfolge_blz);
PHP_FUNCTION(lut_aenderung);
PHP_FUNCTION(lut_loeschung);
PHP_FUNCTION(lut_iban_regel);
PHP_FUNCTION(lut_methode_txt);
PHP_FUNCTION(lut_suche_volltext);
PHP_FUNCTION(lut_suche_init);
PHP_FUNCTION(lut_suche_free);
PHP_FUNCTION(lut_suche_set);
PHP_FUNCTION(lut_suche);
PHP_FUNCTION(lut_suche_multiple);
PHP_FUNCTION(lut_suche_bic);
PHP_FUNCTION(lut_suche_namen);
PHP_FUNCTION(lut_suche_namen_kurz);
PHP_FUNCTION(lut_suche_ort);
PHP_FUNCTION(lut_suche_pz);
PHP_FUNCTION(lut_suche_blz);
PHP_FUNCTION(lut_suche_plz);
PHP_FUNCTION(lut_suche_regel);

extern zend_module_entry konto_check_module_entry;
#define phpext_konto_check_ptr &konto_check_module_entry

#endif
