/* Dies ist ein kleines Programm das eine Liste von BLZ/Kontonummer-Paaren (durch Blank getrennt)
 * einliest, auf Gültigkeit testet und das Ergebnis in eine Ausgabedatei schreibt. Es ist nur als
 * kleines Beispiel für die Anwendung der konto_check Bibliothek unter C# gedacht; das komplette
 * Interface für die Bibliothek ist natürlich einiges größer und mächtiger.
 */

using System;
using System.IO;
using System.Runtime.InteropServices;

namespace mini
{
   class Program
   {
#region Externals
      [DllImport("konto_check.cdecl.dll", EntryPoint = "kto_check_init_p", CallingConvention = CallingConvention.Cdecl)]
         private static extern Int32 kto_check_init_i(String lutName, Int32 required, Int32 set, Int32 incremental);

      [DllImport("konto_check.cdecl.dll", EntryPoint = "kto_check_blz", CallingConvention = CallingConvention.Cdecl)]
         private static extern Int32 kto_check_blz(String blz, String kto);

      [DllImport("konto_check.cdecl.dll", EntryPoint = "kto_check_retval2txt", CallingConvention=CallingConvention.Cdecl)]
         private static extern IntPtr kto_check_retval2txt(Int32 retval);

      [DllImport("konto_check.cdecl.dll", EntryPoint = "lut_name", CallingConvention = CallingConvention.Cdecl)]
         private static extern IntPtr lut_name(String blz, Int32 zweigstelle, out Int32 retval);

      [DllImport("konto_check.cdecl.dll", EntryPoint = "lut_ort", CallingConvention = CallingConvention.Cdecl)]
         private static extern IntPtr lut_ort(String blz, Int32 zweigstelle, out Int32 retval);

      [DllImport("konto_check.cdecl.dll", EntryPoint = "lut_plz", CallingConvention = CallingConvention.Cdecl)]
         private static extern Int32 lut_plz(String blz, Int32 zweigstelle, out Int32 retval);

      [DllImport("konto_check.cdecl.dll", EntryPoint = "cleanup_kto", CallingConvention=CallingConvention.Cdecl)]
         private static extern void cleanup_kto();
#endregion

#region kc_defs
      static Int32 kto_check_init()
      {
         return kto_check_init_i("", 7, 0, 0);
      }

      static String bank_name(String blz)
      {
         Int32 rv;
         return Marshal.PtrToStringAnsi(lut_name(blz, 0, out rv));
      }

      static Int32 bank_plz(String blz)
      {
         Int32 rv;
         return lut_plz(blz, 0, out rv);
      }

         /* Das Interface ist für alle Funktionen auf die notwendigen Parameter
          * reduziert; man kann es natürlich (mittels Überladung) wesentlich
          * ausführlicher gestalten. Hier als Beispiel noch die Version der
          * Funktion bank_ort() mit allen Parametern.
          */
      static String bank_ort(String blz, Int32 zweigstelle, out Int32 retval)
      {
         return Marshal.PtrToStringAnsi(lut_ort(blz, zweigstelle, out retval));
      }

      static String bank_ort(String blz)
      {
         Int32 rv;
         return Marshal.PtrToStringAnsi(lut_ort(blz, 0, out rv));
      }

      static String retval2txt(Int32 retval)
      {
         return Marshal.PtrToStringAnsi(kto_check_retval2txt(retval));
      }

      static void kto_check_free()
      {
         cleanup_kto();
      }
#endregion

      static void Main(string[] args)
      {
         Int32 retval;
         String blz,kto,s,retval_txt;
         string[] s2;

         if (args.Length < 2){
            Console.WriteLine("Aufruf: mini <eingabedatei> <ausgabedatei>");
            Console.ReadLine();
            return;
         }

         kto_check_init();
         StreamReader input = new StreamReader(args[0]);
         StreamWriter output = new StreamWriter(args[1]);

         while ((s = input.ReadLine()) != null) {
            s2 = s.Split(' ');
            blz = s2[0];
            kto = s2[1];
            retval = kto_check_blz(blz, kto);
            retval_txt=retval2txt(retval);
            if (retval >= 0)
               output.WriteLine(blz+" "+kto+": "+retval_txt+"; "
                     + bank_name(blz)
                     + ", " + bank_plz(blz).ToString()
                     + " " + bank_ort(blz));
            else
               output.WriteLine(blz+" "+kto+": "+retval_txt);
         }
         input.Close();
         output.Close();
         kto_check_free();
      }
   }
}
