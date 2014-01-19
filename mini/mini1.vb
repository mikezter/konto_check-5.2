'vim:cindent:ft=c:foldmethod=marker:fmr=+§§§,-§§§
'
' Code-Beispiel und Definitionen für konto_check unter Visual VB.net +§§§1
' 
' Diese Schnittstelle wurde mit der freien Version des Instant VB Converters
' von http://www.tangiblesoftwaresolutions.com/Product_Details/Instant_VB.html
' aus mini1.cs generiert und an wenigen Stellen angepaßt (Kommentare, Überladungen).
' Es kann mit dem Befehl >>vbc mini1.vb<< übersetzt werden.
' 
' Die Schnittstelle benutzt einige DLL-Einsprungpunkte die erst ab Version 4.0
' von konto_check verfügbar sind (kc_alloc() in iban2bic() und ipi_gen() sowie
' kto_check_idx2blz() in den Suchroutinen). Daher ist sie mit den
' DLL-Versionen 3.x nur eingeschränkt nutzbar.
' 
' Die main() Routine ist die von mini.vb; sie nimmt als Eingabe eine Datei mit
' einer Liste von BLZ/Kontonummer-Paaren (durch Blank getrennt). Diese werden
' auf Gültigkeit testet und das Ergebnis in eine Ausgabedatei geschrieben. Es
' wird nur ein kleiner Teil der Definitionen benutzt.
' 
' Die auskommentierten Überschriften der Funktionsköpfe sind noch die von C#;
' sie dienen nur zur Orientierung, welche Funktionsüberladung jeweils definiert
' wird, und sind insofern nicht weiter relevant.

' Copyright-Notiz +§§§3
' ##########################################################################
' #  Dies ist die Schnittstelle für Visual VB.net zu konto_check, sowie    #
' #  ein kleines Code-Beispiel für die Verwendung einzelner Routinen.      #
' #                                                                        #
' #  Copyright (C) 2012 Michael Plugge <m.plugge@hs-mannheim.de>           #
' #                                                                        #
' #  Dieses Programm ist freie Software; Sie dürfen es unter den           #
' #  Bedingungen der GNU Lesser General Public License, wie von der Free   #
' #  Software Foundation veröffentlicht, weiterverteilen und/oder          #
' #  modifizieren; entweder gemäß Version 2.1 der Lizenz oder (nach Ihrer  #
' #  Option) jeder späteren Version.                                       #
' #                                                                        #
' #  Die GNU LGPL ist weniger infektiös als die normale GPL; Code, der von #
' #  Ihnen hinzugefügt wird, unterliegt nicht der Offenlegungspflicht      #
' #  (wie bei der normalen GPL); außerdem müssen Programme, die diese      #
' #  Bibliothek benutzen, nicht (L)GPL lizensiert sein, sondern können     #
' #  beliebig kommerziell verwertet werden. Die Offenlegung des Sourcecodes#
' #  bezieht sich bei der LGPL *nur* auf geänderten Bibliothekscode.       #
' #                                                                        #
' #  Dieses Programm wird in der Hoffnung weiterverbreitet, daß es         #
' #  nützlich sein wird, jedoch OHNE IRGENDEINE GARANTIE, auch ohne die    #
' #  implizierte Garantie der MARKTREIFE oder der VERWENDBARKEIT FÜR       #
' #  EINEN BESTIMMTEN ZWECK. Mehr Details finden Sie in der GNU Lesser     #
' #  General Public License.                                               #
' #                                                                        #
' #  Sie sollten eine Kopie der GNU Lesser General Public License          #
' #  zusammen mit diesem Programm erhalten haben; falls nicht,             #
' #  schreiben Sie an die Free Software Foundation, Inc., 59 Temple        #
' #  Place, Suite 330, Boston, MA 02111-1307, USA. Sie können sie auch     #
' #  von                                                                   #
' #                                                                        #
' #       http://www.gnu.org/licenses/lgpl.html                            #
' #                                                                        #
' # im Internet herunterladen.                                             #
' ##########################################################################

' Using-Direktiven +§§§3 
Imports System
Imports System.IO
Imports System.Runtime.InteropServices
' -§§§3 

Namespace mini
   Friend Class Program

' Entrypoints der DLL-Funktionen +§§§2 
#Region "Externals"

' In diesem Teil sind nur die DLL-Einsprungpunkte definiert. Eine
' kurze Beschreibung der einzelnen Funktionen findet sich unten bei
' der Definition der einzelnen Funktionen.

       ' Allgemeine Funktionen +§§§3 
#Region "Allgemeine Funktionen"
       ' Entrypoint kto_check_idx2blz +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "kto_check_idx2blz", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function kto_check_idx2blz(ByVal idx As Int32, ByRef zweigstelle As Int32, ByRef retval As Int32) As Int32
     End Function

       ' Entrypoint kto_check_encoding +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "kto_check_encoding", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function kto_check_encoding_i(ByVal encoding As Int32) As Int32
     End Function

       ' Entrypoint kto_check_init_p +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "kto_check_init_p", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function kto_check_init_i(ByVal lutName As String, ByVal required As Int32, ByVal [set] As Int32, ByVal incremental As Int32) As Int32
     End Function

       ' Entrypoint current_lutfile_name +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "current_lutfile_name", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function current_lutfile_name_i(ByRef [set] As Int32, ByRef level As Int32, ByRef retval As Int32) As IntPtr
     End Function

       ' Entrypoint kto_check_blz +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "kto_check_blz", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function kto_check_blz(ByVal blz As String, ByVal kto As String) As Int32
     End Function

       ' Entrypoint kto_check_retval2txt +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "kto_check_retval2txt", CallingConvention:=CallingConvention.Cdecl)> _
     Private Shared Function kto_check_retval2txt(ByVal retval As Int32) As IntPtr
     End Function

       ' Entrypoint kto_check_retval2txt_short +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "kto_check_retval2txt_short", CallingConvention:=CallingConvention.Cdecl)> _
     Private Shared Function kto_check_retval2txt_short(ByVal retval As Int32) As IntPtr
     End Function

       ' Entrypoint cleanup_kto +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "cleanup_kto", CallingConvention:=CallingConvention.Cdecl)> _
     Private Shared Sub cleanup_kto()
     End Sub

       ' Entrypoint kc_alloc +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "kc_alloc", CallingConvention:=CallingConvention.Cdecl)> _
     Private Shared Function kc_alloc(ByVal size As Int32, ByRef retval As Int32) As IntPtr
     End Function

       ' Entrypoint kc_free +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "kc_free", CallingConvention:=CallingConvention.Cdecl)> _
     Private Shared Sub kc_free(ByVal ptr As IntPtr)
     End Sub

       ' IBAN-Funktionen +§§§3 
       ' Entrypoint iban2bic +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "iban2bic", CallingConvention:=CallingConvention.Cdecl)> _
     Private Shared Function iban2bic_i(ByVal iban As String, ByRef retval As Int32, ByVal blz As IntPtr, ByVal kto As IntPtr) As IntPtr
     End Function

       ' Entrypoint iban_gen +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "iban_bic_gen1", CallingConvention:=CallingConvention.Cdecl)> _
     Private Shared Function iban_gen_i(ByVal blz As String, ByVal kto As String, ByRef bic As String, ByRef retval As Int32) As IntPtr
     End Function

       ' Entrypoint ci_check +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "ci_check", CallingConvention:=CallingConvention.Cdecl)> _
     Private Shared Function ci_check_i(ByVal ci As String) As Int32
     End Function

       ' Entrypoint iban_check +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "iban_check", CallingConvention:=CallingConvention.Cdecl)> _
     Private Shared Function iban_check_i(ByVal iban As String, ByRef retval As Int32) As Int32
     End Function

       ' Entrypoint ipi_gen +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "ipi_gen", CallingConvention:=CallingConvention.Cdecl)> _
     Private Shared Function ipi_gen_i(ByVal zweck As String, ByRef dst As IntPtr, ByRef papier As IntPtr) As Int32
     End Function

       ' Entrypoint ipi_check +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "ipi_check", CallingConvention:=CallingConvention.Cdecl)> _
     Private Shared Function ipi_check(ByVal ipi As String) As Int32
     End Function
#End Region

       ' Suchfunktionen +§§§3 
#Region "Suchfunktionen"
       ' Entrypoint lut_suche_bic +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_suche_bic", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_suche_bic(ByVal such_name As String, ByRef anzahl As Int32, ByRef start_idx As IntPtr, ByRef zweigstellen As IntPtr, ByRef base_name As IntPtr, ByRef blz_base As IntPtr) As Int32
     End Function

       ' Entrypoint lut_suche_namen +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_suche_namen", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_suche_namen(ByVal such_name As String, ByRef anzahl As Int32, ByRef start_idx As IntPtr, ByRef zweigstellen As IntPtr, ByRef base_name As IntPtr, ByRef blz_base As IntPtr) As Int32
     End Function

       ' Entrypoint lut_suche_namen_kurz +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_suche_namen_kurz", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_suche_namen_kurz(ByVal such_name As String, ByRef anzahl As Int32, ByRef start_idx As IntPtr, ByRef zweigstellen As IntPtr, ByRef base_name As IntPtr, ByRef blz_base As IntPtr) As Int32
     End Function

       ' Entrypoint lut_suche_ort +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_suche_ort", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_suche_ort(ByVal such_name As String, ByRef anzahl As Int32, ByRef start_idx As IntPtr, ByRef zweigstellen As IntPtr, ByRef base_name As IntPtr, ByRef blz_base As IntPtr) As Int32
     End Function

       ' Entrypoint lut_suche_plz +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_suche_plz", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_suche_plz(ByVal such1 As Int32, ByVal such2 As Int32, ByRef anzahl As Int32, ByRef start_idx As IntPtr, ByRef zweigstellen As IntPtr, ByRef base_name As IntPtr, ByRef blz_base As IntPtr) As Int32
     End Function

       ' Entrypoint lut_suche_blz +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_suche_blz", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_suche_blz(ByVal such1 As Int32, ByVal such2 As Int32, ByRef anzahl As Int32, ByRef start_idx As IntPtr, ByRef zweigstellen As IntPtr, ByRef base_name As IntPtr, ByRef blz_base As IntPtr) As Int32
     End Function

       ' Entrypoint lut_suche_pz +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_suche_pz", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_suche_pz(ByVal such1 As Int32, ByVal such2 As Int32, ByRef anzahl As Int32, ByRef start_idx As IntPtr, ByRef zweigstellen As IntPtr, ByRef base_name As IntPtr, ByRef blz_base As IntPtr) As Int32
     End Function

		 ' Entrypoint lut_suche_volltext +§§§4 
	  <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_suche_volltext", CallingConvention := CallingConvention.Cdecl)> _
	  Private Shared Function lut_suche_volltext(ByVal such_wort As String, ByRef anzahl As Int32, ByRef base_name_idx As Int32, ByRef base_name As IntPtr, ByRef zweigstellen_anzahl As Int32, ByRef start_idx As IntPtr, ByRef zweigstellen_base As IntPtr, ByRef blz_base As IntPtr) As Int32
	  End Function

		 ' Entrypoint lut_suche_multiple +§§§4 
	  <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_suche_multiple", CallingConvention := CallingConvention.Cdecl)> _
	  Private Shared Function lut_suche_multiple(ByVal such_str As String, ByVal uniq As Int32, ByVal such_cmd As String, ByRef anzahl As Int32, ByRef zweigstellen_base As IntPtr, ByRef blz_base As IntPtr) As Int32
	  End Function

#End Region

       ' Funktionen für die LUT-datei +§§§3 
#Region "Funktionen für die LUT-datei"
       ' Entrypoint generate_lut2_p +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "generate_lut2_p", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function generate_lut2_p(ByVal inputname As String, ByVal outputname As String, ByVal user_info As String, ByVal gueltigkeit As String, ByVal felder As Int32, ByVal filialen As Int32, ByVal slots As Int32, ByVal lut_version As Int32, ByVal [set] As Int32) As Int32
     End Function

       ' Entrypoint lut_keine_iban_berechnung +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_keine_iban_berechnung", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_keine_iban_berechnung_i(ByVal iban_blacklist As String, ByVal lutfile As String, ByVal [set] As Int32) As Int32
     End Function

       ' Entrypoint lut_dir_dump_str +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_dir_dump_str", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_dir_dump_str_i(ByVal lutname As String, ByRef dptr As IntPtr) As Int32
     End Function

     ' Entrypoint lut_info +§§§4 
   <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_info", CallingConvention := CallingConvention.Cdecl)> _
   Private Shared Function lut_info_i(ByVal lutname As String, ByRef info1 As IntPtr, ByRef info2 As IntPtr, ByRef valid1 As Int32, ByRef valid2 As Int32) As Int32
   End Function

       ' Entrypoint lut_blz +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_blz", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_blz(ByVal blz As String, ByVal zweigstelle As Int32) As Int32
     End Function

       ' Entrypoint lut_filialen +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_filialen", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_filialen(ByVal blz As String, ByRef retval As Int32) As Int32
     End Function

       ' Entrypoint lut_name +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_name", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_name(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As IntPtr
     End Function

       ' Entrypoint lut_name_kurz +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_name_kurz", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_name_kurz(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As IntPtr
     End Function

       ' Entrypoint lut_plz +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_plz", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_plz(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
     End Function

       ' Entrypoint lut_ort +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_ort", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_ort(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As IntPtr
     End Function

       ' Entrypoint lut_pan +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_pan", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_pan(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
     End Function

       ' Entrypoint lut_bic +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_bic", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_bic(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As IntPtr
     End Function

       ' Entrypoint lut_nr +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_nr", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_nr(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
     End Function

       ' Entrypoint lut_pz +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_pz", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_pz(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
     End Function

       ' Entrypoint lut_aenderung +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_aenderung", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_aenderung(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
     End Function

       ' Entrypoint lut_loeschung +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_loeschung", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_loeschung(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
     End Function

       ' Entrypoint lut_nachfolge_blz +§§§4 
     <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_nachfolge_blz", CallingConvention := CallingConvention.Cdecl)> _
     Private Shared Function lut_nachfolge_blz(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
     End Function

#End Region
#End Region

#Region "kc_defs"
' VB-Definitionen: Allgemeine Funktionen +§§§2 
#Region "allgemeine Funktionen"
       ' Funktion kto_check_init() +§§§3 
#Region "kto_check_init()"
' Die Funktion kto_check_init() initialisiert die Bibliothek mit den
' Werten aus einer LUT-Datei. Die Parameter sind alle optional, da in
' der konto_check Bibliothek viele Defaultwerte vorgegeben sind, die
' normalerweise ausreichen. Die Parameter haben die folgende Bedeutung:
' 
' lutfile:      Die Datei aus der gelesen werden soll. Defaultwerte
'               sind dabei für den Dateipfad (in dieser Reihenfolge)
'               ".","C:","C:\\Programme\\konto_check"
'               und für den Dateinamen "blz.lut","blz.lut2f","blz.lut2".
'               Die Werte können in der Datei konto_check.h beliebig
'               verändert werden.
' 
' required:     (Integerwert zwischen 0 und 9). Gibt an, welche BLocks
'               geladen werden sollen; Default ist 7. Eine Liste der
'               geladenen Blocks findet sich im Anhang der Datei
'               00liesmich.pdf.
' 
' set:          (Integer, 0, 1 oder 2). In einer LUT-Datei können zwei
'               Datensätze enthalten sein; dieser Parameter bestimmt,
'               welcher Satz zu laden ist. Bei 0 wird der Datensatz
'               anhand des Systemdatums und Gültigkeitszeitraums der
'               beiden Datensätze automatisch bestimmt.
' 
' incremental: falls der Parameter 1 ist, wird eine inkrementelle
'              Initialisierung (Nachladen von noch nicht geladenen
'              Blocks) versucht. Diese ist allerdings nur vom selben
'              Datensatz wie bei der initialen Initialisierung
'              möglich.

       ' Funktion kto_check_init() +§§§4 
     Private Shared Function kto_check_init() As Int32
       Return kto_check_init_i("", 7, 0, 0)
     End Function
       ' Funktion kto_check_init(String lutfile) +§§§4 
     Private Shared Function kto_check_init(ByVal lutfile As String) As Int32
       Return kto_check_init_i(lutfile, 7, 0, 0)
     End Function
       ' Funktion kto_check_init(String lutfile, Int32 level) +§§§4 
     Private Shared Function kto_check_init(ByVal lutfile As String, ByVal level As Int32) As Int32
       Return kto_check_init_i(lutfile, level,0,0)
     End Function
       ' Funktion kto_check_init(String lutfile, Int32 level, Int32 set) +§§§4 
     Private Shared Function kto_check_init(ByVal lutfile As String, ByVal level As Int32, ByVal [set] As Int32) As Int32
       Return kto_check_init_i(lutfile, level,[set],0)
     End Function
       ' Funktion kto_check_init(String lutfile, Int32 level, Int32 set, Int32 incremental) +§§§4 
     Private Shared Function kto_check_init(ByVal lutfile As String, ByVal level As Int32, ByVal [set] As Int32, ByVal incremental As Int32) As Int32
       Return kto_check_init_i(lutfile, level, [set], incremental)
     End Function
#End Region

       ' Funktion kto_check_encoding() +§§§3 
#Region "kto_check_encoding()"
' Die Funktion kto_check_encoding() setzt (bzw. liest) die Kodierung
' für die konto_check Bibliothek. Es kann sowohl die Kodierung für
' die Fehlermeldungen als auch die der LUT-Datei gesetzt werden.
' Innerhalb der LUT-Datei sind die Werte im Format ISO-8859-1
' gespeichert; sie werden bei der Initialisierung konvertiert.
' 
' Für den Parameter mode werden die folgenden Werte akzeptiert:
'       1: ISO-8859-1
'       2: UTF-8
'       3: HTML-Entities
'       4: DOS (CP850)
'      51: Fehlermeldungen als Makronamen, Rest in ISO-8859-1
'      52: Fehlermeldungen als Makronamen, Rest in UTF-8
'      53: Fehlermeldungen als Makronamen, Rest in HTML-Entities
'      54: Fehlermeldungen als Makronamen, Rest in DOS (CP850)
' 
' Rückgabewert ist der aktuell gesetzte Modus (als Zahl). Falls die
' Funktion mit dem Parameter 0 aufgerufen wird, wird nur die aktuelle
' Kodierung zurückgegeben.

       ' Funktion kto_check_encoding() +§§§4 
     Private Shared Function kto_check_encoding() As Int32
       Return kto_check_encoding_i(0)
     End Function
       ' Funktion kto_check_encoding(Int32 encoding) +§§§4 
     Private Shared Function kto_check_encoding(ByVal encoding As Int32) As Int32
       Return kto_check_encoding_i(encoding)
     End Function
#End Region

       ' Funktion current_lutfile_name() +§§§3 
#Region "current_lutfile_name()"
' Die Funktion liefert den Namen der LUT-Datei von der initialisiert
' wurde, sowie das benutzte Set und den Initialisierungslevel zurück.
' Die Parameter haben die folgende Bedeutung:
' 
' set:          Das benutzte Set (1 oder 2), oder 0 falls noch nicht
'               initialisiert wurde.
' 
' level:        Der Initialisierungslevel (0...9).
' 
' retval:       Statuswert; er kann die Werte -40 (noch nicht
'               initialisiert) oder 1 (OK) annehmen:
' 
' Der Rückgabewert ist der Name der LUT-Datei, von der initialisiert
' wurde.

       ' Funktion current_lutfile_name() +§§§4 
     Private Shared Function current_lutfile_name() As String
       Dim [set], level, retval As Int32

       Return Marshal.PtrToStringAnsi(current_lutfile_name_i([set],level,retval))
     End Function
       ' Funktion current_lutfile_name(out Int32 set) +§§§4 
     Private Shared Function current_lutfile_name(ByRef [set] As Int32) As String
       Dim level, retval As Int32

       Return Marshal.PtrToStringAnsi(current_lutfile_name_i([set],level,retval))
     End Function
       ' Funktion current_lutfile_name(out Int32 set,out Int32 level) +§§§4 
     Private Shared Function current_lutfile_name(ByRef [set] As Int32, ByRef level As Int32) As String
       Dim retval As Int32

       Return Marshal.PtrToStringAnsi(current_lutfile_name_i([set],level,retval))
     End Function
       ' Funktion current_lutfile_name(out Int32 set,out Int32 level,out Int32 retval) +§§§4 
     Private Shared Function current_lutfile_name(ByRef [set] As Int32, ByRef level As Int32, ByRef retval As Int32) As String
       Return Marshal.PtrToStringAnsi(current_lutfile_name_i([set],level,retval))
     End Function
#End Region

       ' Funktion retval2txt() +§§§3 
#Region "retval2txt()"

' ###########################################################################
' # Die Funktion kto_check_retval2txt() wandelt die numerischen Rückgabe-   #
' # werte in Klartext um. Die Funktion retval2txt_short macht dasselbe,     #
' # nur mit symbolischen Klartexten (Makronamen).                           #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion retval2txt(Int32 retval) +§§§4 
     Private Shared Function retval2txt(ByVal retval As Int32) As String
       Return Marshal.PtrToStringAnsi(kto_check_retval2txt(retval))
     End Function

       ' Funktion retval2txt_short(Int32 retval) +§§§4 
     Private Shared Function retval2txt_short(ByVal retval As Int32) As String
       Return Marshal.PtrToStringAnsi(kto_check_retval2txt_short(retval))
     End Function
#End Region
#Region "kto_check_free()"

' ###########################################################################
' # Die Funktion kto_check_free() gibt allen benutzten Speicher der         #
' # konto_check Bibliothek wieder frei.                                     #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion kto_check_free() +§§§4 
     Private Shared Sub kto_check_free()
       cleanup_kto()
     End Sub
#End Region
#End Region

' VB-Definitionen: IBAN-Funktionen +§§§2 
#Region "IBAN-Funktionen"
       ' Funktion iban2bic() +§§§3 
#Region "iban2bic()"

' ###########################################################################
' # Die Funktion iban2bic extrahiert aus einer IBAN (International Bank     #
' # Account Number) Kontonummer und Bankleitzahl, und bestimmt zu der BLZ   #
' # die zugehörige BIC. Voraussetzung ist natürlich, daß das BIC Feld in    #
' # der geladenen LUT-Datei enthalten ist. BLZ und Kontonummer werden,      #
' # falls gewünscht, in zwei Variablen zurückgegeben.                       #
' #                                                                         #
' # Die Funktion arbeitet nur für deutsche Banken, da für andere keine      #
' # Infos vorliegen.                                                        #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################


       ' Funktion iban2bic(String iban) +§§§4 
     Private Shared Function iban2bic(ByVal iban As String) As String
       Dim rv As Int32
       Dim blz_p, kto_p As IntPtr
       Dim bic As String

       blz_p=kc_alloc(10,rv)
       kto_p=kc_alloc(16,rv)
       bic=Marshal.PtrToStringAnsi(iban2bic_i(iban,rv,blz_p,kto_p))
       kc_free(blz_p)
       kc_free(kto_p)
       Return bic
     End Function
       ' Funktion iban2bic(String iban,out Int32 retval) +§§§4 
     Private Shared Function iban2bic(ByVal iban As String, ByRef retval As Int32) As String
       Dim rv As Int32
       Dim blz_p, kto_p As IntPtr
       Dim bic As String

       blz_p=kc_alloc(10,rv)
       kto_p=kc_alloc(16,rv)
       bic=Marshal.PtrToStringAnsi(iban2bic_i(iban,retval,blz_p,kto_p))
       kc_free(blz_p)
       kc_free(kto_p)
       Return bic
     End Function
       ' Funktion iban2bic(String iban,out String blz, out String kto) +§§§4 
     Private Shared Function iban2bic(ByVal iban As String, ByRef blz As String, ByRef kto As String) As String
       Dim rv As Int32
       Dim blz_p, kto_p As IntPtr
       Dim bic As String

       blz_p=kc_alloc(10,rv)
       kto_p=kc_alloc(16,rv)
       bic=Marshal.PtrToStringAnsi(iban2bic_i(iban,rv,blz_p,kto_p))
       blz=Marshal.PtrToStringAnsi(blz_p)
       kto=Marshal.PtrToStringAnsi(kto_p)
       kc_free(blz_p)
       kc_free(kto_p)
       Return bic
     End Function
       ' Funktion iban2bic(String iban,out String blz, out String kto,out Int32 retval) +§§§4 
     Private Shared Function iban2bic(ByVal iban As String, ByRef blz As String, ByRef kto As String, ByRef retval As Int32) As String
       Dim rv As Int32
       Dim blz_p, kto_p As IntPtr
       Dim bic As String

       blz_p=kc_alloc(10,rv)
       kto_p=kc_alloc(16,rv)
       bic=Marshal.PtrToStringAnsi(iban2bic_i(iban,retval,blz_p,kto_p))
       blz=Marshal.PtrToStringAnsi(blz_p)
       kto=Marshal.PtrToStringAnsi(kto_p)
       kc_free(blz_p)
       kc_free(kto_p)
       Return bic
     End Function
#End Region

       ' Funktion iban_gen() +§§§3 
#Region "iban_gen()"
       ' Funktion iban_gen(String blz, String kto) +§§§4 
     Private Shared Function iban_gen(ByVal blz As String, ByVal kto As String) As String
       Dim retval As Int32
       Dim iban_p,bic_p As IntPtr
       Dim iban As String

       iban_p=iban_gen_i(blz,kto,bic_p,retval)
       iban=Marshal.PtrToStringAnsi(iban_p)
       kc_free(iban_p)
       Return iban
     End Function
       ' Funktion iban_gen(String blz, String kto,out String bic) +§§§4 
     Private Shared Function iban_gen(ByVal blz As String, ByVal kto As String, ByRef bic as String) As String
       Dim retval As Int32
       Dim iban_p,bic_p As IntPtr
       Dim iban As String

       iban_p=iban_gen_i(blz,kto,bic_p,retval)
       iban=Marshal.PtrToStringAnsi(iban_p)
       bic=Marshal.PtrToStringAnsi(bic_p)
       kc_free(iban_p)
       Return iban
	   End Function
       ' Funktion iban_gen(String blz, String kto,out Int32 retval) +§§§4 
     Private Shared Function iban_gen(ByVal blz As String, ByVal kto As String, ByRef retval As Int32) As String
       Dim iban_p,bic_p As IntPtr
       Dim iban As String

       iban_p=iban_gen_i(blz,kto,bic_p,retval)
       iban=Marshal.PtrToStringAnsi(iban_p)
       kc_free(iban_p)
       Return iban
	   End Function
       ' Funktion iban_gen(String blz, String kto,out String bic,out Int32 retval) +§§§4 
     Private Shared Function iban_gen(ByVal blz As String, ByVal kto As String, ByRef bic As String, ByRef retval As Int32) As String
       Dim iban_p,bic_p As IntPtr
       Dim iban As String

       iban_p=iban_gen_i(blz,kto,bic_p,retval)
       iban=Marshal.PtrToStringAnsi(iban_p)
       bic=Marshal.PtrToStringAnsi(bic_p)
       kc_free(iban_p)
       Return iban
     End Function
#End Region

       ' Funktion ci_check() +§§§3 
#Region "ci_check()"

' ###########################################################################
' # Die Funktion ci_check testet die Prüfsumme eines Creditor Identifiers   # 
' # (Gläubiger-Identifikationsnummer)                                       #
' #                                                                         #
' # Copyright (C) 2013 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion ci_check(String ci) +§§§4 
     Private Shared Function ci_check(ByVal iban As String) As Int32
       Return ci_check_i(iban)
     End Function
#End Region

       ' Funktion iban_check() +§§§3 
#Region "iban_check()"

' ###########################################################################
' # Die Funktion iban_check prüft, ob die Prüfsumme des IBAN ok ist und     #
' # testet außerdem noch die BLZ/Konto Kombination. Für den Test des Kontos #
' # wird keine Initialisierung gemacht; diese muß vorher erfolgen. Der      #
' # Rückgabewert ist das Ergebnis der IBAN-Prüfung; in der (optionalen)     #
' # Variablen retval wird das Ergebnis der Kontoprüfung (nur für deutsche   #
' # Konten möglich) zurückgegeben.                                          #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion iban_check(String iban) +§§§4 
     Private Shared Function iban_check(ByVal iban As String) As Int32
       Dim retval As Int32

       Return iban_check_i(iban,retval)
     End Function
       ' Funktion iban_check(String iban, out Int32 retval) +§§§4 
     Private Shared Function iban_check(ByVal iban As String, ByRef retval As Int32) As Int32
       Return iban_check_i(iban,retval)
     End Function
#End Region

       ' Funktion ipi_gen() +§§§3 c
#Region "ipi_gen()"

' ###########################################################################
' # Die Funktion ipi_gen generiert einen Strukturierten Verwendungszweck    #
' # für eine IPI (International Payment Instruction). Der Zweck darf nur    #
' # Buchstaben und Zahlen enthalten; Buchstaben werden dabei in Großbuch-   #
' # staben umgewandelt. Andere Zeichen sind hier nicht zulässig. Der        #
' # Verwendungszweck wird links mit Nullen bis auf 18 Byte aufgefüllt, dann #
' # die Prüfsumme berechnet und eingesetzt. Optional wird auch eine         #
' # Papierform (mit einem Leerzeichen nach jeweils 5 Zeichen) sowie ein     #
' # Statuscode zurückgegeben.                                               #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion ipi_gen(String zweck) +§§§4 
     Private Shared Function ipi_gen(ByVal zweck As String) As String
       Dim retval As Int32
       Dim papier_p, ipi_p As IntPtr
       Dim ipi As String

       ipi_p=kc_alloc(24,retval)
       papier_p=kc_alloc(28,retval)
       retval=ipi_gen_i(zweck,ipi_p, papier_p)
       ipi=Marshal.PtrToStringAnsi(ipi_p)
       kc_free(papier_p)
       kc_free(ipi_p)
       Return ipi
     End Function
       ' Funktion ipi_gen(String zweck, out Int32 retval) +§§§4 
     Private Shared Function ipi_gen(ByVal zweck As String, ByRef retval As Int32) As String
       Dim papier_p, ipi_p As IntPtr
       Dim ipi As String

       ipi_p=kc_alloc(24,retval)
       papier_p=kc_alloc(28,retval)
       retval=ipi_gen_i(zweck,ipi_p, papier_p)
       ipi=Marshal.PtrToStringAnsi(ipi_p)
       kc_free(papier_p)
       kc_free(ipi_p)
       Return ipi
     End Function
       ' Funktion ipi_gen(String zweck, out String papier) +§§§4 
     Private Shared Function ipi_gen(ByVal zweck As String, ByRef papier As String) As String
       Dim retval As Int32
       Dim papier_p, ipi_p As IntPtr
       Dim ipi As String

       ipi_p=kc_alloc(24,retval)
       papier_p=kc_alloc(28,retval)
       retval=ipi_gen_i(zweck,ipi_p, papier_p)
       ipi=Marshal.PtrToStringAnsi(ipi_p)
       papier=Marshal.PtrToStringAnsi(papier_p)
       kc_free(papier_p)
       kc_free(ipi_p)
       Return ipi
     End Function
       ' Funktion ipi_gen(String zweck, out String papier, out Int32 retval) +§§§4 
     Private Shared Function ipi_gen(ByVal zweck As String, ByRef papier As String, ByRef retval As Int32) As String
       Dim papier_p, ipi_p As IntPtr
       Dim ipi As String

       ipi_p=kc_alloc(24,retval)
       papier_p=kc_alloc(28,retval)
       retval=ipi_gen_i(zweck,ipi_p, papier_p)
       ipi=Marshal.PtrToStringAnsi(ipi_p)
       papier=Marshal.PtrToStringAnsi(papier_p)
       kc_free(papier_p)
       kc_free(ipi_p)
       Return ipi
     End Function
#End Region

       ' Funktion ipi_check() +§§§3 
#Region "ipi_check()"

' ###########################################################################
' # Die Funktion ipi_check testet einen Strukturierten Verwendungszweck     #
' # für eine IPI (International Payment Instruction). Der Zweck darf nur    #
' # Buchstaben und Zahlen enthalten und muß genau 20 Byte lang sein, wobei  #
' # eingestreute Blanks oder Tabs ignoriert werden.                         #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion ipi_check(String ipi) +§§§4 
       ' Die Funktion kann direkt aus der DLL aufgerufen werden, ohne Wrapper 
#End Region
#End Region

' VB-Definitionen: Suchfunktionen +§§§2 
#Region "Suchfunktionen"

'          Die Suchfunktionen der C-Bibliothek stellen ein Low-Level Interface
'          * zur Verfügung, das durch VB.net nur schlecht unterstützt wird. Die
'          * Funktionen sind so implementiert, daß zunächst ein Array mit den
'          * Indizes der Bankleitzahlen in der gewünschten Suchordnung erstellt
'          * (bzw. eingelesen) wird; für eine konkrete Suche wird dann ein
'          * Pointer auf den ersten Index, der die Suchkriterien erfüllt sowie
'          * die Anzahl der Banken, die das Kriterium erfüllen, zurückgegeben.
'          * Auch für die Zweigstellen wird nur ein Pointer auf ein Array
'          * zurückgegeben, das für jeden Index die Nummer der jeweiligen
'          * Zweigstelle enthält.
'          *
'          * Da VB.net einen wahlfreien Zugriff in IntPtr-Feldern (mit einem
'          * beliebigem Startindex, normalerweise ungleich 0) - soweit ich bis
'          * jetzt gesehen habe - nicht unterstützt, wurde eine zusätzliche
'          * Funktion kto_check_idx2blz() geschrieben, das zu einem gegebenen
'          * Index BLZ und Zweigstelle zurückliefert. Die Funktion ist erst ab
'          * Version 4.0 verfügbar; für frühere Versionen der DLL sind die
'          * Suchfunktionen daher nicht verwendbar.


       ' Funktion bank_suche_bic() +§§§3 
#Region "bank_suche_bic()"

' ###########################################################################
' # bank_suche_bic(): Banken mit gegebenem BIC suchen.                      #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_suche_bic(String bic) +§§§4 
     Private Shared Function bank_suche_bic(ByVal bic As String) As Int32()
       Dim retval As Int32
       Return bank_suche_bic(bic,retval)
     End Function
       ' Funktion bank_suche_bic(String bic, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_bic(ByVal bic As String, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_bic(bic, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
       Next i
       Return blz_a
     End Function
       ' Funktion bank_suche_bic(String bic, out int[] zweigstellen) +§§§4 
     Private Shared Function bank_suche_bic(ByVal bic As String, ByRef zweigstellen() As Integer) As Int32()
       Dim retval As Int32
       Return bank_suche_bic(bic,zweigstellen,retval)
     End Function
       ' Funktion bank_suche_bic(String bic, out int[] zweigstellen, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_bic(ByVal bic As String, ByRef zweigstellen() As Integer, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_bic(bic, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       zweigstellen = New Integer(anzahl - 1){}
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
         zweigstellen(i) = zw
       Next i
       Return blz_a
     End Function
#End Region

       ' Funktion bank_suche_namen() +§§§3 
#Region "bank_suche_namen()"

' ###########################################################################
' # bank_suche_namen: Banken mit gegebenem Langnamen suchen.                #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_suche_namen(String namen) +§§§4 
     Private Shared Function bank_suche_namen(ByVal namen As String) As Int32()
       Dim retval As Int32
       Return bank_suche_namen(namen,retval)
     End Function
       ' Funktion bank_suche_namen(String namen, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_namen(ByVal namen As String, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_namen(namen, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
       Next i
       Return blz_a
     End Function
       ' Funktion bank_suche_namen(String namen, out int[] zweigstellen) +§§§4 
     Private Shared Function bank_suche_namen(ByVal namen As String, ByRef zweigstellen() As Integer) As Int32()
       Dim retval As Int32
       Return bank_suche_namen(namen,zweigstellen,retval)
     End Function
       ' Funktion bank_suche_namen(String namen, out int[] zweigstellen, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_namen(ByVal namen As String, ByRef zweigstellen() As Integer, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_namen(namen, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       zweigstellen = New Integer(anzahl - 1){}
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
         zweigstellen(i) = zw
       Next i
       Return blz_a
     End Function
#End Region

       ' Funktion bank_suche_namen_kurz() +§§§3 
#Region "bank_suche_namen_kurz()"

' ###########################################################################
' # bank_suche_namen_kurz: Banken gegebenem Kurznamen suchen.               #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_suche_namen_kurz(String namen_kurz) +§§§4 
     Private Shared Function bank_suche_namen_kurz(ByVal namen_kurz As String) As Int32()
       Dim retval As Int32
       Return bank_suche_namen_kurz(namen_kurz,retval)
     End Function
       ' Funktion bank_suche_namen_kurz(String namen_kurz, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_namen_kurz(ByVal namen_kurz As String, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_namen_kurz(namen_kurz, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
       Next i
       Return blz_a
     End Function
       ' Funktion bank_suche_namen_kurz(String namen_kurz, out int[] zweigstellen) +§§§4 
     Private Shared Function bank_suche_namen_kurz(ByVal namen_kurz As String, ByRef zweigstellen() As Integer) As Int32()
       Dim retval As Int32
       Return bank_suche_namen_kurz(namen_kurz,zweigstellen,retval)
     End Function
       ' Funktion bank_suche_namen_kurz(String namen_kurz, out int[] zweigstellen, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_namen_kurz(ByVal namen_kurz As String, ByRef zweigstellen() As Integer, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_namen_kurz(namen_kurz, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       zweigstellen = New Integer(anzahl - 1){}
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
         zweigstellen(i) = zw
       Next i
       Return blz_a
     End Function
#End Region

       ' Funktion bank_suche_ort() +§§§3 
#Region "bank_suche_ort()"

' ###########################################################################
' # bank_suche_ort: Banken in einem gegebenen Ort suchen.                   #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_suche_ort(String ort) +§§§4 
     Private Shared Function bank_suche_ort(ByVal ort As String) As Int32()
       Dim retval As Int32
       Return bank_suche_ort(ort,retval)
     End Function
       ' Funktion bank_suche_ort(String ort, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_ort(ByVal ort As String, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_ort(ort, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
       Next i
       Return blz_a
     End Function
       ' Funktion bank_suche_ort(String ort, out int[] zweigstellen) +§§§4 
     Private Shared Function bank_suche_ort(ByVal ort As String, ByRef zweigstellen() As Integer) As Int32()
       Dim retval As Int32
       Return bank_suche_ort(ort,zweigstellen,retval)
     End Function
       ' Funktion bank_suche_ort(String ort, out int[] zweigstellen, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_ort(ByVal ort As String, ByRef zweigstellen() As Integer, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_ort(ort, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       zweigstellen = New Integer(anzahl - 1){}
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
         zweigstellen(i) = zw
       Next i
       Return blz_a
     End Function
#End Region

       ' Funktion bank_suche_plz() +§§§3 
#Region "bank_suche_plz()"

' ###########################################################################
' # bank_suche_plz: Banken mit vorgegebener PLZ oder PLZ zwischen plz1 und  #
' # plz2 suchen.                                                            #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_suche_plz(Int32 plz) +§§§4 
     Private Shared Function bank_suche_plz(ByVal plz As Int32) As Int32()
       Dim retval As Int32
       Return bank_suche_plz(plz,plz,retval)
     End Function
       ' Funktion bank_suche_plz(Int32 plz1, Int32 plz2) +§§§4 
     Private Shared Function bank_suche_plz(ByVal plz1 As Int32, ByVal plz2 As Int32) As Int32()
       Dim retval As Int32
       Return bank_suche_plz(plz1,plz2,retval)
     End Function
       ' Funktion bank_suche_plz(Int32 plz1, Int32 plz2, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_plz(ByVal plz1 As Int32, ByVal plz2 As Int32, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_plz(plz1, plz2, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
       Next i
       Return blz_a
     End Function
       ' Funktion bank_suche_plz(Int32 plz1, Int32 plz2, out int[] zweigstellen) +§§§4 
     Private Shared Function bank_suche_plz(ByVal plz1 As Int32, ByVal plz2 As Int32, ByRef zweigstellen() As Integer) As Int32()
       Dim retval As Int32
       Return bank_suche_plz(plz1, plz2,zweigstellen,retval)
     End Function
       ' Funktion bank_suche_plz(Int32 plz1, Int32 plz2, out int[] zweigstellen, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_plz(ByVal plz1 As Int32, ByVal plz2 As Int32, ByRef zweigstellen() As Integer, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_plz(plz1, plz2, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       zweigstellen = New Integer(anzahl - 1){}
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
         zweigstellen(i) = zw
       Next i
       Return blz_a
     End Function
#End Region

       ' Funktion bank_suche_blz() +§§§3 
#Region "bank_suche_blz()"

' ###########################################################################
' # bank_suche_blz: Banken mit vorgegebener BLZ oder BLZ zwischen blz1 und  #
' # blz2 suchen.                                                            #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_suche_blz(Int32 blz) +§§§4 
     Private Shared Function bank_suche_blz(ByVal blz As Int32) As Int32()
       Dim retval As Int32
       Return bank_suche_blz(blz,blz,retval)
     End Function
       ' Funktion bank_suche_blz(Int32 blz1, Int32 blz2) +§§§4 
     Private Shared Function bank_suche_blz(ByVal blz1 As Int32, ByVal blz2 As Int32) As Int32()
       Dim retval As Int32
       Return bank_suche_blz(blz1,blz2,retval)
     End Function
       ' Funktion bank_suche_blz(Int32 blz1, Int32 blz2, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_blz(ByVal blz1 As Int32, ByVal blz2 As Int32, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_blz(blz1, blz2, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
       Next i
       Return blz_a
     End Function
       ' Funktion bank_suche_blz(Int32 blz1, Int32 blz2, out int[] zweigstellen) +§§§4 
     Private Shared Function bank_suche_blz(ByVal blz1 As Int32, ByVal blz2 As Int32, ByRef zweigstellen() As Integer) As Int32()
       Dim retval As Int32
       Return bank_suche_blz(blz1, blz2,zweigstellen,retval)
     End Function
       ' Funktion bank_suche_blz(Int32 blz1, Int32 blz2, out int[] zweigstellen, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_blz(ByVal blz1 As Int32, ByVal blz2 As Int32, ByRef zweigstellen() As Integer, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_blz(blz1, blz2, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       zweigstellen = New Integer(anzahl - 1){}
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
         zweigstellen(i) = zw
       Next i
       Return blz_a
     End Function
#End Region

       ' Funktion bank_suche_pz() +§§§3 
#Region "bank_suche_pz()"

' ###########################################################################
' # bank_suche_pz: Banken mit vorgegebenem Prüfzifferverfahren pz oder      #
' # Prüfzifferverfahren zwischen pz1 und pz2 suchen.                        #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_suche_pz(Int32 pz) +§§§4 
     Private Shared Function bank_suche_pz(ByVal pz As Int32) As Int32()
       Dim retval As Int32
       Return bank_suche_pz(pz,pz,retval)
     End Function
       ' Funktion bank_suche_pz(Int32 pz1, Int32 pz2) +§§§4 
     Private Shared Function bank_suche_pz(ByVal pz1 As Int32, ByVal pz2 As Int32) As Int32()
       Dim retval As Int32
       Return bank_suche_pz(pz1,pz2,retval)
     End Function
       ' Funktion bank_suche_pz(Int32 pz1, Int32 pz2, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_pz(ByVal pz1 As Int32, ByVal pz2 As Int32, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_pz(pz1, pz2, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
       Next i
       Return blz_a
     End Function
       ' Funktion bank_suche_pz(Int32 pz1, Int32 pz2, out int[] zweigstellen) +§§§4 
     Private Shared Function bank_suche_pz(ByVal pz1 As Int32, ByVal pz2 As Int32, ByRef zweigstellen() As Integer) As Int32()
       Dim retval As Int32
       Return bank_suche_pz(pz1, pz2,zweigstellen,retval)
     End Function
       ' Funktion bank_suche_pz(Int32 pz1, Int32 pz2, out int[] zweigstellen, out Int32 retval) +§§§4 
     Private Shared Function bank_suche_pz(ByVal pz1 As Int32, ByVal pz2 As Int32, ByRef zweigstellen() As Integer, ByRef retval As Int32) As Int32()
       Dim anzahl, rv, i, zw As Int32
       Dim start_idx, zs, base_name, blz_base As IntPtr

       retval = lut_suche_pz(pz1, pz2, anzahl, start_idx, zs, base_name, blz_base)
       Dim idx_a(anzahl - 1) As Integer
       Dim blz_a(anzahl - 1) As Integer
       zweigstellen = New Integer(anzahl - 1){}
       Marshal.Copy(start_idx, idx_a, 0, anzahl)
       For i = 0 To anzahl - 1
         blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
         zweigstellen(i) = zw
       Next i
       Return blz_a
     End Function
#End Region

		 ' Funktion bank_suche_volltext() +§§§3 
#Region "bank_suche_volltext()"

' ###########################################################################
' # bank_suche_volltext: Volltextsuche in Langnamen, Kurznamen und Ort      #
' #                                                                         #
' # Copyright (C) 2012 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

		 ' Funktion bank_suche_volltext(String such_wort) +§§§4 
	  Private Shared Function bank_suche_volltext(ByVal such_wort As String) As Int32()
		 Dim retval As Int32
		 Return bank_suche_volltext(such_wort,retval)
	  End Function
		 ' Funktion bank_suche_volltext(String such_wort, out Int32 retval) +§§§4 
	  Private Shared Function bank_suche_volltext(ByVal such_wort As String, ByRef retval As Int32) As Int32()
		 Dim anzahl, rv, i, zw, base_name_idx, zweigstellen_anzahl As Int32
		 Dim start_idx, zs, base_name, blz_base As IntPtr

		 retval = lut_suche_volltext(such_wort, anzahl, base_name_idx, base_name, zweigstellen_anzahl, start_idx, zs, blz_base)
		 Dim idx_a(anzahl - 1) As Integer
		 Dim blz_a(anzahl - 1) As Integer
		 Marshal.Copy(start_idx, idx_a, 0, anzahl)
		 For i = 0 To anzahl - 1
			blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
		 Next i
		 Return blz_a
	  End Function
		 ' Funktion bank_suche_volltext(String such_wort, out int[] zweigstellen) +§§§4 
	  Private Shared Function bank_suche_volltext(ByVal such_wort As String, ByRef zweigstellen() As Integer) As Int32()
		 Dim retval As Int32
		 Return bank_suche_volltext(such_wort,zweigstellen,retval)
	  End Function
		 ' Funktion bank_suche_volltext(String such_wort, out int[] zweigstellen, out Int32 retval) +§§§4 
	  Private Shared Function bank_suche_volltext(ByVal such_wort As String, ByRef zweigstellen() As Integer, ByRef retval As Int32) As Int32()
		 Dim anzahl, rv, i, zw, base_name_idx, zweigstellen_anzahl As Int32
		 Dim start_idx, zs, base_name, blz_base As IntPtr

		 retval = lut_suche_volltext(such_wort, anzahl, base_name_idx, base_name, zweigstellen_anzahl, start_idx, zs, blz_base)
		 Dim idx_a(anzahl - 1) As Integer
		 Dim blz_a(anzahl - 1) As Integer
		 zweigstellen = New Integer(anzahl - 1){}
		 Marshal.Copy(start_idx, idx_a, 0, anzahl)
		 For i = 0 To anzahl - 1
			blz_a(i) = kto_check_idx2blz(idx_a(i), zw, rv)
			zweigstellen(i) = zw
		 Next i
		 Return blz_a
	  End Function
#End Region

		 ' Funktion bank_suche_multiple() +§§§3 
#Region "bank_suche_multiple()"

' ###########################################################################
' # bank_suche_multiple: Suche nach mehreren Kriterien                      #
' #                                                                         #
' # Copyright (C) 2012 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

		 ' Funktion bank_suche_multiple(String such_str) +§§§4 
	  Private Shared Function bank_suche_multiple(ByVal such_str As String) As Int32()
		 Dim retval As Int32
		 Return bank_suche_multiple(such_str,0,"",retval)
	  End Function
		 ' Funktion bank_suche_multiple(String such_str,Int32 uniq, String such_cmd) +§§§4 
	  Private Shared Function bank_suche_multiple(ByVal such_str As String, ByVal uniq As Int32, ByVal such_cmd As String) As Int32()
		 Dim retval As Int32
		 Return bank_suche_multiple(such_str,uniq,such_cmd,retval)
	  End Function
		 ' Funktion bank_suche_multiple(String such_str,Int32 uniq, String such_cmd, out Int32 retval) +§§§4 
	  Private Shared Function bank_suche_multiple(ByVal such_str As String, ByVal uniq As Int32, ByVal such_cmd As String, ByRef retval As Int32) As Int32()
		 Dim anzahl, zw As Int32
		 Dim zs, blz_base As IntPtr

		 retval = lut_suche_multiple(such_str, uniq, such_cmd, anzahl, zs, blz_base)
		 Dim blz_a(anzahl - 1) As Integer
		 Marshal.Copy(blz_a, 0, blz_base, anzahl)
		 kc_free(blz_base)
		 kc_free(zw)
		 Return blz_a
	  End Function
		 ' Funktion bank_suche_multiple(String such_str, Int32 uniq, String such_cmd, out int[] zweigstellen, out Int32 retval) +§§§4 
	  Private Shared Function bank_suche_multiple(ByVal such_str As String, ByVal uniq As Int32, ByVal such_cmd As String, ByRef zweigstellen() As Integer, ByRef retval As Int32) As Int32()
		 Dim anzahl, zw As Int32
		 Dim zs, blz_base As IntPtr

		 retval = lut_suche_multiple(such_str, uniq, such_cmd, anzahl, zs, blz_base)
		 Dim blz_a(anzahl - 1) As Integer
		 zweigstellen = New Integer(anzahl - 1){}
		 Marshal.Copy(blz_a, 0, blz_base, anzahl)
		 Marshal.Copy(zweigstellen, 0, zs, anzahl)
		 kc_free(blz_base)
		 kc_free(zw)
		 Return blz_a
	  End Function
#End Region

#End Region

' VB-Definitionen: Funktionen für die LUT-datei +§§§2 
#Region "Funktionen für die LUT-datei"
       ' Funktion bank_blz() +§§§3 
#Region "Funktion bank_blz()"

' ###########################################################################
' # bank_blz(): Test ob eine BLZ existiert                                  #
' # Diese Funktion testet, ob eine BLZ (und Zweigstelle, falls gewünscht)   #
' # existiert und gültig ist.                                               #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_blz(String blz) +§§§4 
     Private Shared Function bank_blz(ByVal blz As String) As Int32
       Return lut_blz(blz,0)
     End Function
       ' Funktion bank_blz(String blz, Int32 zweigstelle) +§§§4 
     Private Shared Function bank_blz(ByVal blz As String, ByVal zweigstelle As Int32) As Int32
       Return lut_blz(blz, zweigstelle)
     End Function
#End Region

       ' Funktion lut_info() +§§§3 
#Region "Funktion lut_info()"

       ' Funktion lut_info() 
' ###########################################################################
' # Die Funktion lut_info() extrahiert die beiden Infoblocks aus einer      #
' # LUT-Datei und vergleicht das Gültigkeitsdatum mit dem aktuellen Datum.  #
' # Falls eine LUT-Datei keinen Infoblock oder kein Gültigkeitsdatum        #
' # enthält, wird (in den Variablen valid1 bzw. valid2) ein entsprechender  #
' # Fehlercode zurückgegeben.                                               #
' #                                                                         #
' # Falls als Dateiname NULL oder ein Leerstring übergeben wird, wird die   #
' # Gültigkeit des aktuell geladenen Datensatzes bestimmt, und (optional)   #
' # mit dem zugehörigen Infoblock zurückgegeben. In diesem Fall wird info2  #
' # auf "" und valid2 auf LUT2_BLOCK_NOT_IN_FILE gesetzt.                   #
' #                                                                         #
' # Parameter:                                                              #
' #    lut_name: Name der LUT-Datei oder NULL/Leerstring                    #
' #    info1:    Rückgabestring mit dem primären Infoblock                  #
' #    info2:    Rückgabestring mit dem sekundären Infoblock                #
' #    valid1:   Statusvariable für den primären Datensatz                  #
' #    valid2:   Statusvariable für den sekundären Datensatz                #
' #                                                                         #
' # Rückgabewerte:                                                          #
' #    OK:                     ok, weiteres in valid1 und valid2            #
' #    LUT2_NOT_INITIALIZED:   die library wurde noch nicht initialisiert   #
' #                                                                         #
' # Werte für valid1 und valid2:                                            #
' #    LUT2_VALID:             Der Datenblock ist aktuell gültig            #
' #    LUT2_NO_LONGER_VALID:   Der Datenblock ist nicht mehr gültig         #
' #    LUT2_NOT_YET_VALID:     Der Datenblock ist noch nicht gültig         #
' #    LUT2_NO_VALID_DATE:     Der Datenblock enthält kein Gültigkeitsdatum #
' #    LUT2_BLOCK_NOT_IN_FILE: Die LUT-Datei enthält den Infoblock nicht    #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion lut_info(out String info,out Int32 valid) +§§§4 
     Private Shared Function lut_info(ByRef info As String, ByRef valid As Int32) As Int32
       Dim retval, valid2 As Int32
       Dim info1_p, info2_p As IntPtr

       retval=lut_info_i("",info1_p,info2_p,valid,valid2)
       info=Marshal.PtrToStringAnsi(info1_p)
       kc_free(info1_p)
       kc_free(info2_p)
       Return retval
     End Function
       ' Funktion lut_info(String lutfile,Int32 set,out String info,out Int32 valid) +§§§4 
     Private Shared Function lut_info(ByVal lutfile As String, ByVal [set] As Int32, ByRef info As String, ByRef valid As Int32) As Int32
       Dim retval, valid1, valid2 As Int32
       Dim info1_p, info2_p As IntPtr

       retval=lut_info_i(lutfile,info1_p,info2_p,valid1,valid2)
       If [set]=1 Then
         info=Marshal.PtrToStringAnsi(info1_p)
         valid=valid1
       ElseIf [set]=2 Then
         info=Marshal.PtrToStringAnsi(info2_p)
         valid=valid2
       Else
         info=""
         valid=0
       End If
       kc_free(info1_p)
       kc_free(info2_p)
       Return retval
     End Function
       ' Funktion lut_info(String lutfile,out String info1,out Int32 valid1,out String info2,out Int32 valid2) +§§§4 
     Private Shared Function lut_info(ByVal lutfile As String, ByRef info1 As String, ByRef valid1 As Int32, ByRef info2 As String, ByRef valid2 As Int32) As Int32
       Dim retval As Int32
       Dim info1_p, info2_p As IntPtr

       retval=lut_info_i(lutfile,info1_p,info2_p,valid1,valid2)
       info1=Marshal.PtrToStringAnsi(info1_p)
       info2=Marshal.PtrToStringAnsi(info2_p)
       kc_free(info1_p)
       kc_free(info2_p)
       Return retval
     End Function
#End Region

       ' Funktion generate_lut() +§§§3 
#Region "Funktion generate_lut()"

' ###########################################################################
' # generate_lut(): LUT-Datei generieren.                                   #
' #                                                                         #
' # Diese Funktion generiert aus der Textdatei der Deutschen Bundesbank     #
' # eine LUT-Datei die für die konto_check Bibliothek benötigt wird.        #
' # Die Felder der Bundesbankdatei werden dabei in einzelnen Blocks in der  #
' # LUT-Datei gespeichert, die unabhängig voneinander eingelesen werden     #
' # können und in einem (normalerweise mittels zlib) komprimierten Format   #
' # gespeichert werden. In einer LUT-Datei können zwei Datensätze (d.h.     #
' # zwei Bundesbankdateien) mit unterschiedlichem Gültigkeitsdatum          #
' # gespeichert werden. Die Entscheidung welcher Datensatz aktuell gültig   #
' # ist wird bei der Initialisierung anhand des Systemdatums gefällt.       #
' # Es ist ferner möglich, nur die Daten der Hauptstellen in die LUT-Datei  #
' # aufzunehmen; die Datei wird dadurch natürlich wesentlich kleiner.       #
' #                                                                         #
' # Folgende Parameter werden unterstützt:                                  #
' #                                                                         #
' # inputname:      Name der Bundesbankdatei (Textversion)                  #
' #                                                                         #
' # outputname:     Name zu generierenden LUT-Datei                         #
' #                                                                         #
' # user_info:      Kommentarfeld in der LUT-Datei                          #
' #                                                                         #
' # gueltigkeit:    Gültigkeit des Datensatzes im Format JJJJMMDD-JJJJMMDD  #
' #                                                                         #
' # iban_blacklist: Name der Datei mit den Instituten, die einer            #
' #                 Selbstberechnung der IBAN nicht zugestimmt haben.       #
' #                 Nähere Infos und Weblinks zu dieser Datei gibt es bei   #
' #                 der Funktion lut_keine_iban_berechnung() (s.u.).        #
' #                                                                         #
' # felder:         Integer (0...9), welche Blocks in die LUT-Datei         #
' #                 aufgenommen werden sollen. Eine Liste der Blocks findet #
' #                 sich im Anhang der Datei 00liesmich.pdf.                #
' #                                                                         #
' # filialen:       Flag (0 oder 1), ob die Daten der Filialen aufgenommen  #
' #                 werden sollen.                                          #
' #                                                                         #
' # slots:          Anzahl Slots im Inhaltsverzeichnis der LUT-Datei. Diese #
' #                 Zahl kann nachträglich nicht mehr geändert werden; sie  #
' #                 gibt die maximale Anzahl Blocks an, die in der Datei    #
' #                 enthalten sein können. Der Minimalwert für diesen       #
' #                 Parameter ist in konto_check.h mit 40 festgelegt.       #
' #                                                                         #
' #                                                                         #
' # set:            (Integer 0, 1, 2 oder 10, 11, 12). Angabe welcher       #
' #                 Datensatz geschrieben werden soll. Bei 0 wird die Datei #
' #                 neu angelegt und der Datensatz 1 geschrieben; bei 1     #
' #                 oder 2 wird der entsprechende Datensatz an die          #
' #                 LUT-Datei angehängt. Falls in der Datei schon Blocks    #
' #                 mit derselben Blocknummer enthalten sind, werden sie    #
' #                 durch die neuen Blocks ersetzt.                         #
' #                                                                         #
' #                 Die Werte 10, 11 und 12 entsprechen den Fällen 0, 1 und #
' #                 2; nur wird in dem Fall kein Indexblock für die Suche   #
' #                 nach den verschiedenen Werten geschrieben; der Index    #
' #                 muß in diesem Fall jeweils beim ersten Aufruf einer     #
' #                 Suchfunktion generiert werden.                          #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion generate_lut(String inputname,String outputname) +§§§4 
     Private Shared Function generate_lut(ByVal inputname As String, ByVal outputname As String) As Int32
       Return generate_lut2_p(inputname,outputname,"","",0,0,0,0,0)
     End Function
       ' Funktion generate_lut(String inputname,String outputname,String user_info) +§§§4 
     Private Shared Function generate_lut(ByVal inputname As String, ByVal outputname As String, ByVal user_info As String) As Int32
       Return generate_lut2_p(inputname,outputname,user_info,"",0,0,0,0,0)
     End Function
       ' Funktion generate_lut(String inputname,String outputname,String user_info, String gueltigkeit) +§§§4 
     Private Shared Function generate_lut(ByVal inputname As String, ByVal outputname As String, ByVal user_info As String, ByVal gueltigkeit As String) As Int32
       Return generate_lut2_p(inputname,outputname,user_info,gueltigkeit,0,0,0,0,0)
     End Function
       ' Funktion generate_lut(String inputname,String outputname,String user_info, String gueltigkeit,String iban_blacklist) +§§§4 
     Private Shared Function generate_lut(ByVal inputname As String, ByVal outputname As String, ByVal user_info As String, ByVal gueltigkeit As String, ByVal iban_blacklist As String) As Int32
       Dim retval As Int32

       retval=generate_lut2_p(inputname,outputname,user_info,gueltigkeit,0,0,0,0,0)
       If retval<=0 Then
          Return retval
       End If
       lut_keine_iban_berechnung_i(iban_blacklist,outputname,0)
       Return retval
     End Function
       ' Funktion generate_lut(String inputname,String outputname,String user_info, String gueltigkeit,Int32 felder) +§§§4 
     Private Shared Function generate_lut(ByVal inputname As String, ByVal outputname As String, ByVal user_info As String, ByVal gueltigkeit As String, ByVal felder As Int32) As Int32
       Return generate_lut2_p(inputname,outputname,user_info,gueltigkeit,felder,0,0,0,0)
     End Function
       ' Funktion generate_lut(String inputname,String outputname,String user_info, String gueltigkeit,String iban_blacklist,Int32 felder) +§§§4 
     Private Shared Function generate_lut(ByVal inputname As String, ByVal outputname As String, ByVal user_info As String, ByVal gueltigkeit As String, ByVal iban_blacklist As String, ByVal felder As Int32) As Int32
       Dim retval As Int32

       retval=generate_lut2_p(inputname,outputname,user_info,gueltigkeit,felder,0,0,0,0)
       If retval<=0 Then
          Return retval
       End If
       lut_keine_iban_berechnung_i(iban_blacklist,outputname,0)
       Return retval
     End Function
       ' Funktion generate_lut(String inputname,String outputname,String user_info, String gueltigkeit,Int32 felder,Int32 filialen) +§§§4 
     Private Shared Function generate_lut(ByVal inputname As String, ByVal outputname As String, ByVal user_info As String, ByVal gueltigkeit As String, ByVal felder As Int32, ByVal filialen As Int32) As Int32
       Return generate_lut2_p(inputname,outputname,user_info,gueltigkeit,felder,filialen,0,0,0)
     End Function
       ' Funktion generate_lut(String inputname,String outputname,String user_info, String gueltigkeit,String iban_blacklist,Int32 felder,Int32 filialen) +§§§4 
     Private Shared Function generate_lut(ByVal inputname As String, ByVal outputname As String, ByVal user_info As String, ByVal gueltigkeit As String, ByVal iban_blacklist As String, ByVal felder As Int32, ByVal filialen As Int32) As Int32
       Dim retval As Int32

       retval=generate_lut2_p(inputname,outputname,user_info,gueltigkeit,felder,filialen,0,0,0)
       If retval<=0 Then
          Return retval
       End If
       lut_keine_iban_berechnung_i(iban_blacklist,outputname,0)
       Return retval
     End Function
       ' Funktion generate_lut(String inputname,String outputname,String user_info, String gueltigkeit,Int32 felder,Int32 filialen,Int32 set) +§§§4 
     Private Shared Function generate_lut(ByVal inputname As String, ByVal outputname As String, ByVal user_info As String, ByVal gueltigkeit As String, ByVal felder As Int32, ByVal filialen As Int32, ByVal [set] As Int32) As Int32
       Return generate_lut2_p(inputname,outputname,user_info,gueltigkeit,felder,filialen,0,0,[set])
     End Function
       ' Funktion generate_lut(String inputname,String outputname,String user_info, String gueltigkeit,String iban_blacklist,Int32 felder,Int32 filialen,Int32 set) +§§§4 
     Private Shared Function generate_lut(ByVal inputname As String, ByVal outputname As String, ByVal user_info As String, ByVal gueltigkeit As String, ByVal iban_blacklist As String, ByVal felder As Int32, ByVal filialen As Int32, ByVal [set] As Int32) As Int32
       Dim retval As Int32

       retval=generate_lut2_p(inputname,outputname,user_info,gueltigkeit,felder,filialen,0,0,[set])
       If retval<=0 Then
          Return retval
       End If
       lut_keine_iban_berechnung_i(iban_blacklist,outputname,0)
       Return retval
     End Function
       ' Funktion generate_lut(String inputname,String outputname,String user_info, String gueltigkeit,Int32 felder,Int32 filialen,Int32 slots,Int32 set) +§§§4 
     Private Shared Function generate_lut(ByVal inputname As String, ByVal outputname As String, ByVal user_info As String, ByVal gueltigkeit As String, ByVal felder As Int32, ByVal filialen As Int32, ByVal slots As Int32, ByVal [set] As Int32) As Int32
       Return generate_lut2_p(inputname,outputname,user_info,gueltigkeit,felder,filialen,slots,0,[set])
     End Function
       ' Funktion generate_lut(String inputname,String outputname,String user_info, String gueltigkeit,String iban_blacklist,Int32 felder,Int32 filialen,Int32 slots,Int32 set) +§§§4 
     Private Shared Function generate_lut(ByVal inputname As String, ByVal outputname As String, ByVal user_info As String, ByVal gueltigkeit As String, ByVal iban_blacklist As String, ByVal felder As Int32, ByVal filialen As Int32, ByVal slots As Int32, ByVal [set] As Int32) As Int32
       Dim retval As Int32

       retval=generate_lut2_p(inputname,outputname,user_info,gueltigkeit,felder,filialen,slots,0,[set])
       If retval<=0 Then
          Return retval
       End If
       lut_keine_iban_berechnung_i(iban_blacklist,outputname,0)
       Return retval
     End Function
#End Region

       ' Funktion lut_keine_iban_berechnung() +§§§3 
#Region "Funktion lut_keine_iban_berechnung()"

' ############################################################################
' # Die Funktion lut_keine_iban_berechnung() konvertiert die Liste der       #  
' # Banken, die einer IBAN-Berechnung nicht zugestimmt haben in das interne  #
' # Format für konto_check. Als Eingabedatei wird die Datei CONFIG.INI des   #
' # SEPA Account Converters der Sparkassen benutzt, die Ausgabe wird direkt  #
' # als Block in die LUT-Datei geschrieben. Der Block wird automatisch beim  #
' # Initialisieren eingelesen und von der Funktion iban_gen() ausgewertet.   #
' #                                                                          #
' # Hier ein Auszug aus der Anleitung des SEPA Account Converters:           #
' #                                                                          #
' # Der SEPA Account Converter ist so eingestellt, dass nur                  #
' # Kontoverbindungen in IBAN und BIC umgerechnet werden, bei denen das      #
' # ausgebende Kreditinstitut der Umrechnung zugestimmt hat.                 #
' # Kreditinstitute, welche einer Umrechnung nicht zugestimmt haben und      #
' # welche zum Teil spezielle, dem SEPA Account Converter nicht bekannte     #
' # Umrechnungsmethoden verwenden, sind in der Datei "CONFIG.INI"            #
' # hinterlegt. Durch Löschen der Datei "CONFIG.INI" aus dem                 #
' # Programmverzeichnis haben Sie die Möglichkeit, eine Umrechnung für alle  #
' # Konten durchzuführen. Bitte beachten Sie dabei, dass die so erhaltenen   #
' # IBAN und BIC fehlerhaft sein können und deshalb mit ihren Kunden zu      #
' # überprüfen sind.                                                         #
' ############################################################################

' Weblinks:
'  * https://www.sparkasse-rhein-neckar-nord.de/pdf/content/sepa/kurzanleitung.pdf
'  * https://www.sparkasse-rhein-neckar-nord.de/firmenkunden/internationales_geschaeft/sepa/vorteile/index.php
'  * https://www.sparkasse-rhein-neckar-nord.de/firmenkunden/internationales_geschaeft/sepa/vorteile/sepa_account_converter.msi
'  * http://www.sfirm.de/update/prgupd.htm


       ' Funktion lut_keine_iban_berechnung(String iban_blacklist,String lutfile) +§§§4 
     Private Shared Function lut_keine_iban_berechnung(ByVal iban_blacklist As String, ByVal lutfile As String) As Int32
       Return lut_keine_iban_berechnung_i(iban_blacklist,lutfile,0)
     End Function
       ' Funktion lut_keine_iban_berechnung(String iban_blacklist,String lutfile,Int32 set) +§§§4 
     Private Shared Function lut_keine_iban_berechnung(ByVal iban_blacklist As String, ByVal lutfile As String, ByVal [set] As Int32) As Int32
       Return lut_keine_iban_berechnung_i(iban_blacklist,lutfile,[set])
     End Function
#End Region

       ' Funktion lut_dir_dump_str() +§§§3 
#Region "Funktion lut_dir_dump_str()"

' ###########################################################################
' # Die Funktion lut_dir_dump_str liest eine LUT-Datei und gibt die Infos   #
' # zu den enthaltenen Blocks im Ausgabestring zurück. Außerdem wird noch   #
' # die Gesamtgröße der Daten (sowohl komprimiert als auch unkomprimiert)   #
' # ausgegeben.                                                             #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion lut_dir_dump_str(String lutfile) +§§§4 
     Private Shared Function lut_dir_dump_str(ByVal lutfile As String) As String
       Dim retval As Int32
       Dim dptr As IntPtr
       Dim lut_dir As String

       retval=lut_dir_dump_str_i(lutfile,dptr)
       lut_dir=Marshal.PtrToStringAnsi(dptr)
       kc_free(dptr)
       Return lut_dir
     End Function
       ' Funktion lut_dir_dump_str(String lutfile, out Int32 retval) +§§§4 
     Private Shared Function lut_dir_dump_str(ByVal lutfile As String, ByRef retval As Int32) As String
       Dim dptr As IntPtr
       Dim lut_dir As String

       retval=lut_dir_dump_str_i(lutfile,dptr)
       lut_dir=Marshal.PtrToStringAnsi(dptr)
       kc_free(dptr)
       Return lut_dir
     End Function
#End Region

       ' Funktion bank_filialen() +§§§3 
#Region "Funktion bank_filialen()"

' ###########################################################################
' # bank_filialen(): Anzahl der Filialen zu einer gegebenen Bankleitzahl    #
' # bestimmen.                                                              #
' #                                                                         #
' # Copyright (C) 2007 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_filialen(String blz) +§§§4 
     Private Shared Function bank_filialen(ByVal blz As String) As Int32
       Dim retval As Int32

       Return lut_filialen(blz,retval)
     End Function
       ' Funktion bank_filialen(String blz, out Int32 retval) +§§§4 
     Private Shared Function bank_filialen(ByVal blz As String, ByRef retval As Int32) As Int32
       Return lut_filialen(blz, retval)
     End Function
#End Region

'          Die folgenden Funktionen haben jeweils drei Parameter: BLZ, Filiale
'          * und retval. Die BLZ ist notwendig, Filiale und retval sind
'          * optional. Falls die Filiale nicht angegeben wird wird 0 angenommen
'          * (Hauptstelle). In der Variablen retval wird ein Statuscode zum
'          * Funktionsaufruf zurückgegeben.

       ' Funktion bank_name() +§§§3 
#Region "Funktion bank_name()"

' ###########################################################################
' # bank_name(): Banknamen (lange Form) bestimmen                           #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_name(String blz) +§§§4 
     Private Shared Function bank_name(ByVal blz As String) As String
       Dim retval As Int32
       Return Marshal.PtrToStringAnsi(lut_name(blz, 0, retval))
     End Function
       ' Funktion bank_name(String blz, out Int32 retval) +§§§4 
     Private Shared Function bank_name(ByVal blz As String, ByRef retval As Int32) As String
       Return Marshal.PtrToStringAnsi(lut_name(blz, 0, retval))
     End Function
       ' Funktion bank_name(String blz, Int32 zweigstelle, out Int32 retval) +§§§4 
     Private Shared Function bank_name(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As String
       Return Marshal.PtrToStringAnsi(lut_name(blz, zweigstelle, retval))
     End Function
#End Region

       ' Funktion bank_name_kurz() +§§§3 
#Region "Funktion bank_name_kurz()"

' ###########################################################################
' # bank_name_kurz(): Kurzbezeichnung mit Ort einer Bank bestimmen          #
' #                                                                         #
' # Kurzbezeichnung und Ort sollen für die Empfängerangaben auf Rechnungen  #
' # und Formularen angegeben werden. Hierdurch wird eine eindeutige Zu-     #
' # ordnung der eingereichten Zahlungsaufträge ermöglicht. Auf Grund der    #
' # Regelungen in den Richtlinien beziehungsweise Zahlungsverkehrs-Abkommen #
' # der deutschen Kreditwirtschaft ist die Länge der Angaben für die        #
' # Bezeichnung des Kreditinstituts begrenzt.                               #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_name_kurz(String blz) +§§§4 
     Private Shared Function bank_name_kurz(ByVal blz As String) As String
       Dim retval As Int32
       Return Marshal.PtrToStringAnsi(lut_name_kurz(blz, 0, retval))
     End Function
       ' Funktion bank_name_kurz(String blz, out Int32 retval) +§§§4 
     Private Shared Function bank_name_kurz(ByVal blz As String, ByRef retval As Int32) As String
       Return Marshal.PtrToStringAnsi(lut_name_kurz(blz, 0, retval))
     End Function
       ' Funktion bank_name_kurz(String blz, Int32 zweigstelle, out Int32 retval) +§§§4 
     Private Shared Function bank_name_kurz(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As String
       Return Marshal.PtrToStringAnsi(lut_name_kurz(blz, zweigstelle, retval))
     End Function
#End Region

       ' Funktion bank_plz() +§§§3 
#Region "Funktion bank_plz()"

' ###########################################################################
' # bank_plz(): Postleitzahl bestimmen                                      #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_plz(String blz) +§§§4 
     Private Shared Function bank_plz(ByVal blz As String) As Int32
       Dim retval As Int32
       Return lut_plz(blz, 0, retval)
     End Function
       ' Funktion bank_plz(String blz, out Int32 retval) +§§§4 
     Private Shared Function bank_plz(ByVal blz As String, ByRef retval As Int32) As Int32
       Return lut_plz(blz, 0, retval)
     End Function
       ' Funktion bank_plz(String blz, Int32 zweigstelle, out Int32 retval) +§§§4 
     Private Shared Function bank_plz(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
       Return lut_plz(blz, zweigstelle, retval)
     End Function
#End Region

       ' Funktion bank_ort() +§§§3 
#Region "Funktion bank_ort()"

' ###########################################################################
' # bank_ort(): Sitz einer Bank bestimmen                                   #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_ort(String blz) +§§§4 
     Private Shared Function bank_ort(ByVal blz As String) As String
       Dim retval As Int32
       Return Marshal.PtrToStringAnsi(lut_ort(blz, 0, retval))
     End Function
       ' Funktion bank_ort(String blz, out Int32 retval) +§§§4 
     Private Shared Function bank_ort(ByVal blz As String, ByRef retval As Int32) As String
       Return Marshal.PtrToStringAnsi(lut_ort(blz, 0, retval))
     End Function
       ' Funktion bank_ort(String blz, Int32 zweigstelle, out Int32 retval) +§§§4 
     Private Shared Function bank_ort(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As String
       Return Marshal.PtrToStringAnsi(lut_ort(blz, zweigstelle, retval))
     End Function
#End Region

       ' Funktion bank_pan() +§§§3 
#Region "Funktion bank_pan()"

' ###########################################################################
' # bank_pan(): PAN-Nummer bestimmen                                        #
' #                                                                         #
' # Für den internationalen Kartenzahlungsverkehr mittels Bankkunden-       #
' # karten haben die Spitzenverbände des Kreditgewerbes und die Deutsche    #
' # Bundesbank eine gesonderte Institutsnummerierung festgelegt; danach     #
' # erhält das kartenausgebende Kreditinstitut eine fünfstellige Instituts- #
' # nummer für PAN (= Primary Account Number). Diese setzt sich zusammen    #
' # aus der Institutsgruppennummer (grundsätzlich = vierte Stelle der       #
' # Bankleitzahl) und einer nachfolgenden vierstelligen, von den einzelnen  #
' # Institutionen frei gewählten Nummer. Abweichend hiervon ist den         #
' # Mitgliedsinstituten des Bundesverbandes deutscher Banken e.V. sowie     #
' # den Stellen der Deutschen Bundesbank stets die Institutsgruppennummer   #
' # 2 zugewiesen worden.                                                    #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_pan(String blz) +§§§4 
     Private Shared Function bank_pan(ByVal blz As String) As Int32
       Dim retval As Int32
       Return lut_pan(blz, 0, retval)
     End Function
       ' Funktion bank_pan(String blz, out Int32 retval) +§§§4 
     Private Shared Function bank_pan(ByVal blz As String, ByRef retval As Int32) As Int32
       Return lut_pan(blz, 0, retval)
     End Function
       ' Funktion bank_pan(String blz, Int32 zweigstelle, out Int32 retval) +§§§4 
     Private Shared Function bank_pan(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
       Return lut_pan(blz, zweigstelle, retval)
     End Function
#End Region

       ' Funktion bank_bic() +§§§3 
#Region "Funktion bank_bic()"

' ###########################################################################
' # bank_bic(): BIC (Bank Identifier Code) einer Bank bestimmen.            #
' #                                                                         #
' # Der Bank Identifier Code (BIC) besteht aus acht oder elf                #
' # zusammenhängenden Stellen und setzt sich aus den Komponenten BANKCODE   #
' # (4 Stellen), LÄNDERCODE (2 Stellen), ORTSCODE (2 Stellen) sowie ggf.    #
' # einem FILIALCODE (3 Stellen) zusammen.                                  #
' #                                                                         #
' # Jedes Kreditinstitut führt grundsätzlich einen BIC je Bankleitzahl und  #
' # teilt diesen der Deutschen Bundesbank mit. Ausnahmen hiervon können auf #
' # Antrag für Bankleitzahlen zugelassen werden, die im BIC-gestützten      #
' # Zahlungsverkehr (grenzüberschreitender Zahlungsverkehr und inländischer #
' # Individualzahlungsverkehr) nicht verwendet werden.                      #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_bic(String blz) +§§§4 
     Private Shared Function bank_bic(ByVal blz As String) As String
       Dim retval As Int32
       Return Marshal.PtrToStringAnsi(lut_bic(blz, 0, retval))
     End Function
       ' Funktion bank_bic(String blz, out Int32 retval) +§§§4 
     Private Shared Function bank_bic(ByVal blz As String, ByRef retval As Int32) As String
       Return Marshal.PtrToStringAnsi(lut_bic(blz, 0, retval))
     End Function
       ' Funktion bank_bic(String blz, Int32 zweigstelle, out Int32 retval) +§§§4 
     Private Shared Function bank_bic(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As String
       Return Marshal.PtrToStringAnsi(lut_bic(blz, zweigstelle, retval))
     End Function
#End Region

       ' Funktion bank_nr() +§§§3 
#Region "Funktion bank_nr()"

' ###########################################################################
' # bank_nr(): Nummer des Datensatzes in der BLZ-Datei                      #
' #                                                                         #
' # Bei jeder Neuanlage eines Datensatzes wird von der Deutschen Bundesbank #
' # automatisiert eine eindeutige Nummer vergeben. Eine einmal verwendete   #
' # Nummer wird nicht noch einmal vergeben.                                 #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_nr(String blz) +§§§4 
     Private Shared Function bank_nr(ByVal blz As String) As Int32
       Dim retval As Int32
       Return lut_nr(blz, 0, retval)
     End Function
       ' Funktion bank_nr(String blz, out Int32 retval) +§§§4 
     Private Shared Function bank_nr(ByVal blz As String, ByRef retval As Int32) As Int32
       Return lut_nr(blz, 0, retval)
     End Function
       ' Funktion bank_nr(String blz, Int32 zweigstelle, out Int32 retval) +§§§4 
     Private Shared Function bank_nr(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
       Return lut_nr(blz, zweigstelle, retval)
     End Function
#End Region

       ' Funktion bank_pz() +§§§3 
#Region "Funktion bank_pz()"

' ###########################################################################
' # bank_pz(): Prüfzifferverfahren für eine Bankleitzahl. Das Verfahren wird#
' # numerisch zurückgegeben, also z.B. 108 für die Methode A8.              #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_pz(String blz) +§§§4 
     Private Shared Function bank_pz(ByVal blz As String) As Int32
       Dim retval As Int32
       Return lut_pz(blz, 0, retval)
     End Function
       ' Funktion bank_pz(String blz, out Int32 retval) +§§§4 
     Private Shared Function bank_pz(ByVal blz As String, ByRef retval As Int32) As Int32
       Return lut_pz(blz, 0, retval)
     End Function
       ' Funktion bank_pz(String blz, Int32 zweigstelle, out Int32 retval) +§§§4 
     Private Shared Function bank_pz(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
       Return lut_pz(blz, zweigstelle, retval)
     End Function
#End Region

       ' Funktion bank_aenderung() +§§§3 
#Region "Funktion bank_aenderung()"

' ###########################################################################
' # bank_aenderung(): Änderungskennzeichen einer Bank betimmen (A Addition, #
' # M Modified, U Unchanged, D Deletion). Gelöschte Datensätze werden mit   #
' # dem Kennzeichen 'D' gekennzeichnet und sind - als Hinweis - letztmalig  #
' # in der Bankleitzahlendatei enthalten. Diese Datensätze sind ab dem      #
' # Gültigkeitstermin der Bankleitzahlendatei im Zahlungsverkehr nicht mehr #
' # zu verwenden.                                                           #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_aenderung(String blz) +§§§4 
     Private Shared Function bank_aenderung(ByVal blz As String) As Int32
       Dim retval As Int32
       Return lut_aenderung(blz, 0, retval)
     End Function
       ' Funktion bank_aenderung(String blz, out Int32 retval) +§§§4 
     Private Shared Function bank_aenderung(ByVal blz As String, ByRef retval As Int32) As Int32
       Return lut_aenderung(blz, 0, retval)
     End Function
       ' Funktion bank_aenderung(String blz, Int32 zweigstelle, out Int32 retval) +§§§4 
     Private Shared Function bank_aenderung(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
       Return lut_aenderung(blz, zweigstelle, retval)
     End Function
#End Region

       ' Funktion bank_loeschung() +§§§3 
#Region "Funktion bank_loeschung()"

' ###########################################################################
' # bank_loeschung(): Hinweis auf eine beabsichtigte Bankleitzahllöschung   #
' #                                                                         #
' # Zur frühzeitigen Information der Teilnehmer am Zahlungsverkehr und      #
' # zur Beschleunigung der Umstellung der Bankverbindung kann ein Kredit-   #
' # institut, das die Löschung einer Bankleitzahl mit dem Merkmal 1 im      #
' # Feld 2 (Hauptstelle) beabsichtigt, die Löschung ankündigen. Die         #
' # Ankündigung kann erfolgen, sobald das Kreditinstitut seine Kunden       #
' # über die geänderte Kontoverbindung informiert hat. Es wird empfohlen,   #
' # diese Ankündigung mindestens eine Änderungsperiode vor der              #
' # eigentlichen Löschung anzuzeigen.                                       #
' #                                                                         #
' # Das Feld enthält das Merkmal 0 (keine Angabe) oder 1 (BLZ im Feld 1     #
' # ist zur Löschung vorgesehen).                                           #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_loeschung(String blz) +§§§4 
     Private Shared Function bank_loeschung(ByVal blz As String) As Int32
       Dim retval As Int32
       Return lut_loeschung(blz, 0, retval)
     End Function
       ' Funktion bank_loeschung(String blz, out Int32 retval) +§§§4 
     Private Shared Function bank_loeschung(ByVal blz As String, ByRef retval As Int32) As Int32
       Return lut_loeschung(blz, 0, retval)
     End Function
       ' Funktion bank_loeschung(String blz, Int32 zweigstelle, out Int32 retval) +§§§4 
     Private Shared Function bank_loeschung(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
       Return lut_loeschung(blz, zweigstelle, retval)
     End Function
#End Region

       ' Funktion bank_nachfolge_blz() +§§§3 
#Region "Funktion bank_nachfolge_blz()"

' ###########################################################################
' # bank_nachfolge_blz(): entweder 0 (Bankleitzahl ist nicht zur Löschung   #
' # vorgesehen, bzw. das Institut hat keine Nachfolge-BLZ veröffentlicht)   #
' # oder eine Bankleitzahl. Eine Bankleitzahl kann nur für Hauptstellen an- #
' # gegeben werden werden, wenn die Bankleitzahl zur Löschung angekündigt   #
' # wurde (bank_loeschung()==1) oder die Bankleitzahl zum aktuellen Gültig- #
' # keitstermin gelöscht wird (bank_aenderung()=='D').                      #
' #                                                                         #
' # Copyright (C) 2011 Michael Plugge <m.plugge@hs-mannheim.de>             #
' ###########################################################################

       ' Funktion bank_nachfolge_blz(String blz) +§§§4 
     Private Shared Function bank_nachfolge_blz(ByVal blz As String) As Int32
       Dim retval As Int32
       Return lut_nachfolge_blz(blz, 0, retval)
     End Function
       ' Funktion bank_nachfolge_blz(String blz, out Int32 retval) +§§§4 
     Private Shared Function bank_nachfolge_blz(ByVal blz As String, ByRef retval As Int32) As Int32
       Return lut_nachfolge_blz(blz, 0, retval)
     End Function
       ' Funktion bank_nachfolge_blz(String blz, Int32 zweigstelle, out Int32 retval) +§§§4 
     Private Shared Function bank_nachfolge_blz(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
       Return lut_nachfolge_blz(blz, zweigstelle, retval)
     End Function
#End Region

#End Region
#End Region

     Shared Sub Main(ByVal args() As String)
       Dim retval As Int32
       Dim blz, kto, s, retval_txt As String
       Dim s2() As String

       If args.Length < 2 Then
         Console.WriteLine("Aufruf: mini1 <eingabedatei> <ausgabedatei>")
         Console.ReadLine()
         Return
       End If

       kto_check_init()
       Dim input As New StreamReader(args(0))
       Dim output As New StreamWriter(args(1))

       s = input.ReadLine()
       Do While s IsNot Nothing
         s2 = s.Split(" "c)
         If s2.Length > 1 Then
            blz = s2(0)
               kto = s2(1)
               retval = kto_check_blz(blz, kto)
               retval_txt= retval2txt(retval)
               If retval >= 0 Then
                  output.WriteLine(blz &" " & kto &": " & retval_txt &"; " & bank_name(blz) & ", " & bank_plz(blz).ToString() & " " & bank_ort(blz))
               Else
                  output.WriteLine(blz &" " & kto &": " & retval_txt)
               End If
            Else
               output.WriteLine(s)
            End If
         s = input.ReadLine()
       Loop
       input.Close()
       output.Close()
       kto_check_free()
     End Sub
' -§§§2 
   End Class
End Namespace
