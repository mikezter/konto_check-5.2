' Dies ist ein kleines Programm das eine Liste von BLZ/Kontonummer-Paaren (durch Blank getrennt)
' einliest, auf Gültigkeit testet und das Ergebnis in eine Ausgabedatei schreibt. Es ist nur als
' kleines Beispiel für die Anwendung der konto_check Bibliothek unter C# gedacht; das komplette
' Interface für die Bibliothek ist natürlich einiges größer und mächtiger.
'
' Dieses Programm wurde mit der freien Version des Instant VB Converters
' von http://www.tangiblesoftwaresolutions.com/Product_Details/Instant_VB.html
' aus mini.cs generiert; es kann mit dem Befehl >>vbc mini.vb<< übersetzt werden.

Imports System
Imports System.IO
Imports System.Runtime.InteropServices

Namespace mini
   Friend Class Program
#Region "Externals"
	  <DllImport("konto_check.cdecl.dll", EntryPoint := "kto_check_init_p", CallingConvention := CallingConvention.Cdecl)> _
	  Private Shared Function kto_check_init_i(ByVal lutName As String, ByVal required As Int32, ByVal [set] As Int32, ByVal incremental As Int32) As Int32
	  End Function

	  <DllImport("konto_check.cdecl.dll", EntryPoint := "kto_check_blz", CallingConvention := CallingConvention.Cdecl)> _
	  Private Shared Function kto_check_blz(ByVal blz As String, ByVal kto As String) As Int32
	  End Function

	  <DllImport("konto_check.cdecl.dll", EntryPoint := "kto_check_retval2txt", CallingConvention:=CallingConvention.Cdecl)> _
	  Private Shared Function kto_check_retval2txt(ByVal retval As Int32) As IntPtr
	  End Function

	  <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_name", CallingConvention := CallingConvention.Cdecl)> _
	  Private Shared Function lut_name(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As IntPtr
	  End Function

	  <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_ort", CallingConvention := CallingConvention.Cdecl)> _
	  Private Shared Function lut_ort(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As IntPtr
	  End Function

	  <DllImport("konto_check.cdecl.dll", EntryPoint := "lut_plz", CallingConvention := CallingConvention.Cdecl)> _
	  Private Shared Function lut_plz(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As Int32
	  End Function

	  <DllImport("konto_check.cdecl.dll", EntryPoint := "cleanup_kto", CallingConvention:=CallingConvention.Cdecl)> _
	  Private Shared Sub cleanup_kto()
	  End Sub
#End Region

#Region "kc_defs"
	  Private Shared Function kto_check_init() As Int32
		 Return kto_check_init_i("", 7, 0, 0)
	  End Function

	  Private Shared Function bank_name(ByVal blz As String) As String
		 Dim rv As Int32
		 Return Marshal.PtrToStringAnsi(lut_name(blz, 0, rv))
	  End Function

	  Private Shared Function bank_plz(ByVal blz As String) As Int32
		 Dim rv As Int32
		 Return lut_plz(blz, 0, rv)
	  End Function

' Das Interface ist für alle Funktionen auf die notwendigen Parameter
' reduziert; man kann es natürlich (mittels Überladung) wesentlich
' ausführlicher gestalten. Hier als Beispiel noch die Version der
' Funktion bank_ort() mit allen Parametern.

	  Private Shared Function bank_ort(ByVal blz As String, ByVal zweigstelle As Int32, ByRef retval As Int32) As String
		 Return Marshal.PtrToStringAnsi(lut_ort(blz, zweigstelle, retval))
	  End Function

	  Private Shared Function bank_ort(ByVal blz As String) As String
		 Dim rv As Int32
		 Return Marshal.PtrToStringAnsi(lut_ort(blz, 0, rv))
	  End Function

	  Private Shared Function retval2txt(ByVal retval As Int32) As String
		 Return Marshal.PtrToStringAnsi(kto_check_retval2txt(retval))
	  End Function

	  Private Shared Sub kto_check_free()
		 cleanup_kto()
	  End Sub
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

		 Dim input As New StreamReader(args(0))
		 Dim output As New StreamWriter(args(1))

		 kto_check_init()
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
   End Class
End Namespace
