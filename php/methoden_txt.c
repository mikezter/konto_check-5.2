/*
 * ##########################################################################
 * #  Diese Datei ist Teil von konto_check; sie wird automatisch aus        #
 * #  konto_check.c generiert. Sie wird (optional) in der PHP-Version       #
 * #  verwendet; bei den anderen Ports ist sie nicht enthalten.             #
 * #                                                                        #
 * #  Copyright (C) 2009-2013 Michael Plugge <m.plugge@hs-mannheim.de>      #
 * ##########################################################################
 */

/*
 * ##########################################################################
 * #  Diese Funktion gibt zu einer Prüfziffermethode (bzw. Untermethode)    #
 * #  die nächstbenutze Folgemethode aus. Zulässige Prüfziffermethoden      #
 * #  sind im Bereich von 0 bis 999, Untermethoden werden durch die         #
 * #  Tausenderstelle dargestellt (wie intern in konto_check auch).         #
 * #                                                                        #
 * #  Die Funktion gibt jeweils zu einer Prüfziffermethode die nächste      #
 * #  benutzte Prüfziffermethode aus; falls die Methode keine weiteren      #
 * #  Methoden benutzt, wird -1 zurückgegeben. Man muß daher die Funktion   #
 * #  iterativ so lange aufrufen, bis der Rückgabewert -1 ist.              #
 * #                                                                        #
 * #  Copyright (C) 2009-2013 Michael Plugge <m.plugge@hs-mannheim.de>      #
 * ##########################################################################
 */

static long folgemethode(long methode)
{
   switch(methode){
      case    0: return -1;   /* Methode 00  */
      case    1: return -1;   /* Methode 01  */
      case    2: return -1;   /* Methode 02  */
      case    3: return  1;   /* Methode 03  */
      case    4: return  2;   /* Methode 04  */
      case    5: return  1;   /* Methode 05  */
      case    7: return  2;   /* Methode 07  */
      case    8: return  0;   /* Methode 08  */
      case    9: return -1;   /* Methode 09  */
      case   10: return  6;   /* Methode 10  */
      case   11: return  6;   /* Methode 11  */
      case   12: return -1;   /* Methode 12  */
      case   13: return  0;   /* Methode 13  */
      case 1013: return  0;   /* Methode 13a */
      case 2013: return  0;   /* Methode 13b */
      case   14: return  2;   /* Methode 14  */
      case   15: return  6;   /* Methode 15  */
      case   16: return  6;   /* Methode 16  */
      case   17: return -1;   /* Methode 17  */
      case   18: return  1;   /* Methode 18  */
      case   19: return  6;   /* Methode 19  */
      case   20: return  6;   /* Methode 20  */
      case   21: return -1;   /* Methode 21  */
      case   22: return -1;   /* Methode 22  */
      case   23: return 16;   /* Methode 23  */
      case   24: return -1;   /* Methode 24	 */
      case   25: return -1;   /* Methode 25	 */
      case   26: return  6;   /* Methode 26  */
      case   27: return  0;   /* Methode 27  */
      case   28: return -1;   /* Methode 28	 */
      case   29: return -1;   /* Methode 29	 */
      case   30: return  0;   /* Methode 30  */
      case   31: return -1;   /* Methode 31	 */
      case   32: return  6;   /* Methode 32  */
      case   33: return  6;   /* Methode 33  */
      case   34: return 28;   /* Methode 34  */
      case   35: return -1;   /* Methode 35	 */
      case   36: return  6;   /* Methode 36  */
      case   37: return  6;   /* Methode 37  */
      case   38: return  6;   /* Methode 38  */
      case   39: return  6;   /* Methode 39  */
      case   40: return  6;   /* Methode 40  */
      case   41: return  0;   /* Methode 41  */
      case   42: return  6;   /* Methode 42  */
      case   43: return -1;   /* Methode 43	 */
      case   44: return 33;   /* Methode 44  */
      case   45: return  0;   /* Methode 45  */
      case   46: return  6;   /* Methode 46  */
      case   47: return  6;   /* Methode 47  */
      case   48: return  6;   /* Methode 48  */
      case 1049: return  0;   /* Methode 49a */
      case 2049: return  1;   /* Methode 49b */
      case 1050: return  6;   /* Methode 50a */
      case 2050: return  6;   /* Methode 50b */
      case 1051: return  6;   /* Methode 51a */
      case 2051: return 33;   /* Methode 51b */
      case 3051: return  0;   /* Methode 51c */
      case 4051: return 33;   /* Methode 51d */
      case 5051: return -1;   /* Methode 51e */
      case 6051: return -1;   /* Methode 51f */
      case 1052: return 20;   /* Methode 52a */
      case 1053: return 20;   /* Methode 53a */
      case   54: return -1;   /* Methode 54	 */
      case   55: return -1;   /* Methode 55	 */
      case   56: return -1;   /* Methode 56	 */
      case 1057: return  0;   /* Methode 57a */
      case 2057: return  0;   /* Methode 57b */
      case 3057: return  9;   /* Methode 57c */
      case 4057: return -1;   /* Methode 57d */
      case   58: return  2;   /* Methode 58  */
      case   59: return  0;   /* Methode 59  */
      case   60: return  0;   /* Methode 60  */
      case   61: return -1;   /* Methode 61	 */
      case   62: return -1;   /* Methode 62	 */
      case   63: return -1;   /* Methode 63	 */
      case   64: return  6;   /* Methode 64  */
      case   65: return  0;   /* Methode 65  */
      case   66: return -1;   /* Methode 66	 */
      case   67: return  0;   /* Methode 67  */
      case   68: return  0;   /* Methode 68  */
      case 1068: return  0;   /* Methode 68a */
      case 2068: return  0;   /* Methode 68b */
      case 3068: return  0;   /* Methode 68c */
      case   69: return  9;   /* Methode 69  */
      case 1069: return 28;   /* Methode 69a */
      case 2069: return 28;   /* Methode 69b */
      case   70: return  6;   /* Methode 70  */
      case   71: return -1;   /* Methode 71	 */
      case   72: return -1;   /* Methode 72	 */
      case 1073: return  0;   /* Methode 73a */
      case 2073: return  0;   /* Methode 73b */
      case 3073: return  0;   /* Methode 73c */
      case 4073: return 51;   /* Methode 73d */
      case 5073: return 51;   /* Methode 73e */
      case 1074: return  0;   /* Methode 74a */
      case 2074: return -1;   /* Methode 74b */
      case   75: return  0;   /* Methode 75  */
      case 1075: return  0;   /* Methode 75a */
      case 2075: return -1;   /* Methode 75b */
      case 3075: return -1;   /* Methode 75c */
      case   76: return -1;   /* Methode 76	 */
      case   77: return -1;   /* Methode 77	 */
      case   78: return  0;   /* Methode 78  */
      case   79: return  0;   /* Methode 79  */
      case 1080: return  0;   /* Methode 80a */
      case 2080: return  0;   /* Methode 80b */
      case 3080: return 51;   /* Methode 80c */
      case 4080: return 51;   /* Methode 80d */
      case 1081: return 32;   /* Methode 81a */
      case 2081: return 51;   /* Methode 81b */
      case 3081: return 51;   /* Methode 81c */
      case 1082: return 10;   /* Methode 82a */
      case 2082: return 33;   /* Methode 82b */
      case 1083: return 32;   /* Methode 83a */
      case 2083: return 33;   /* Methode 83b */
      case 3083: return 33;   /* Methode 83c */
      case 4083: return -1;   /* Methode 83d */
      case 1084: return  6;   /* Methode 84a */
      case 2084: return  6;   /* Methode 84b */
      case 3084: return  6;   /* Methode 84c */
      case 4084: return 51;   /* Methode 84d */
      case 1085: return 32;   /* Methode 85a */
      case 2085: return 33;   /* Methode 85b */
      case 3085: return 33;   /* Methode 85c */
      case 4085: return  2;   /* Methode 85d */
      case 1086: return  0;   /* Methode 86a */
      case 2086: return 32;   /* Methode 86b */
      case 3086: return 51;   /* Methode 86c */
      case 4086: return 51;   /* Methode 86d */
      case 1087: return -1;   /* Methode 87a */
      case 2087: return 33;   /* Methode 87b */
      case 3087: return 84;   /* Methode 87c */
      case 4087: return 10;   /* Methode 87d */
      case 5087: return 51;   /* Methode 87e */
      case   88: return  6;   /* Methode 88  */
      case 1089: return 10;   /* Methode 89a */
      case 2089: return  6;   /* Methode 89b */
      case 1090: return 32;   /* Methode 90a */
      case 2090: return 33;   /* Methode 90b */
      case 3090: return 33;   /* Methode 90c */
      case 4090: return 33;   /* Methode 90d */
      case 5090: return 33;   /* Methode 90e */
      case 6090: return 32;   /* Methode 90f */
      case 1091: return  6;   /* Methode 91a */
      case 2091: return  6;   /* Methode 91b */
      case 3091: return  6;   /* Methode 91c */
      case   92: return  1;   /* Methode 92  */
      case 1093: return  6;   /* Methode 93a */
      case 2093: return  6;   /* Methode 93b */
      case 3093: return  6;   /* Methode 93c */
      case 4093: return  6;   /* Methode 93d */
      case   94: return  0;   /* Methode 94  */
      case   95: return  6;   /* Methode 95  */
      case 1096: return 19;   /* Methode 96a */
      case 2096: return  0;   /* Methode 96b */
      case 3096: return -1;   /* Methode 96c */
      case   97: return -1;   /* Methode 97	 */
      case 1098: return -1;   /* Methode 98a */
      case 2098: return 32;   /* Methode 98b */
      case   99: return  6;   /* Methode 99  */
      case  100: return -1;   /* Methode A0	 */
      case  101: return  0;   /* Methode A1  */
      case 1102: return  0;   /* Methode A2a */
      case 2102: return  4;   /* Methode A2b */
      case 1103: return  0;   /* Methode A3a */
      case 2103: return 10;   /* Methode A3b */
      case 1104: return  6;   /* Methode A4a */
      case 2104: return -1;   /* Methode A4b */
      case 3104: return  6;   /* Methode A4c */
      case 4104: return 93;   /* Methode A4d */
      case 5104: return 93;   /* Methode A4e */
      case 1105: return  0;   /* Methode A5a */
      case 2105: return 10;   /* Methode A5b */
      case 1106: return  0;   /* Methode A6a */
      case 2106: return  1;   /* Methode A6b */
      case 1107: return  0;   /* Methode A7a */
      case 2107: return  3;   /* Methode A7b */
      case 1108: return  6;   /* Methode A8a */
      case 2108: return  0;   /* Methode A8b */
      case 3108: return 51;   /* Methode A8c */
      case 4108: return 51;   /* Methode A8d */
      case 1109: return  1;   /* Methode A9a */
      case 2109: return  6;   /* Methode A9b */
      case 1110: return  9;   /* Methode B0a */
      case 2110: return  6;   /* Methode B0b */
      case 1111: return  5;   /* Methode B1a */
      case 2111: return  1;   /* Methode B1b */
      case 1112: return  2;   /* Methode B2a */
      case 2112: return  0;   /* Methode B2b */
      case 1113: return 32;   /* Methode B3a */
      case 2113: return  6;   /* Methode B3b */
      case 1114: return  0;   /* Methode B4a */
      case 2114: return  2;   /* Methode B4b */
      case 1115: return  5;   /* Methode B5a */
      case 2115: return  0;   /* Methode B6b */
      case 1116: return 20;   /* Methode B6a */
      case 2116: return 53;   /* Methode B7b */
      case 1117: return  1;   /* Methode B7a */
      case 2117: return  9;   /* Methode B8b */
      case 1118: return 20;   /* Methode B8a */
      case 2118: return 29;   /* Methode B8b */
      case 3118: return  9;   /* Methode B8b */
      case 1119: return -1;   /* Methode B9a */
      case 2119: return -1;   /* Methode B9b */
      case 1120: return 52;   /* Methode C0a */
      case 2120: return 20;   /* Methode C0b */
      case 1121: return 17;   /* Methode C1a */
      case 2121: return -1;   /* Methode C1b */
      case 1122: return 22;   /* Methode C2a */
      case 2122: return  0;   /* Methode C2b */
      case 1123: return  0;   /* Methode C3a */
      case 2123: return 58;   /* Methode C3b */
      case 1124: return 15;   /* Methode C4a */
      case 2124: return 58;   /* Methode C4b */
      case 1125: return 75;   /* Methode C5a */
      case 2125: return 29;   /* Methode C5b */
      case 3125: return  0;   /* Methode C5c */
      case 4125: return  9;   /* Methode C5d */
      case  126: return  0;   /* Methode C6  */
      case 1127: return 63;   /* Methode C7a */
      case 2127: return  6;   /* Methode C7b */
      case 3127: return 63;   /* Methode C7c */
      case 1128: return  0;   /* Methode C8a */
      case 2128: return  4;   /* Methode C8b */
      case 3128: return  7;   /* Methode C8c */
      case 1129: return  0;   /* Methode C9a */
      case 2129: return  7;   /* Methode C9b */
      case 1130: return 20;   /* Methode D0a */
      case 2130: return  9;   /* Methode D0b */
      case  131: return  0;   /* Methode D1  */
      case 1132: return 95;   /* Methode D2a */
      case 2132: return  0;   /* Methode D2b */
      case 3132: return 68;   /* Methode D2c */
      case 1133: return  0;   /* Methode D3a */
      case 2133: return 27;   /* Methode D3b */
      case  134: return  0;   /* Methode D4  */
      case 1135: return  6;   /* Methode D5a */
      case 2135: return  6;   /* Methode D5b */
      case 3135: return -1;   /* Methode D5c */
      case 4135: return -1;   /* Methode D5d */
      case 1136: return  7;   /* Methode D6a */
      case 2136: return  3;   /* Methode D6b */
      case 3136: return  0;   /* Methode D6c */
      case  137: return -1;   /* Methode D7  */
      case 1138: return  0;   /* Methode D8a */
      case 2138: return  9;   /* Methode D8b */
      case 1139: return  0;   /* Methode D9a */
      case 2139: return 10;   /* Methode D9b */
      case 3139: return 18;   /* Methode D9c */
      case  140: return -1;   /* Methode E0  */
      case  141: return -1;   /* Methode E1  */
      default:   return -2;   /* noch nicht eingefügte Methoden */
   }
}

/*
 * ##########################################################################
 * #  Diese Funktion gibt zu einer Prüfziffermethode den Beschreibungstext  #
 * #  aus konto_check.c zurück. Die Beschreibungen sind aus der Datei der   #
 * #  Deutschen Bundesbank entnommen (gekürzt).                             #
 * #                                                                        #
 * #  Copyright (C) 2009-2010 Michael Plugge <m.plugge@hs-mannheim.de>      #
 * ##########################################################################
 */

static char *mtxt(long methode)
{
   switch(methode%1000){

      case 0: return "\
######################################################################\n\
#               Berechnung nach der Methode 00                       #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2.                  #\n\
# Die einzelnen Stellen der Kontonummer sind von rechts nach         #\n\
# links mit den Ziffern 2, 1, 2, 1, 2 usw. zu multiplizieren.        #\n\
# Die jeweiligen Produkte werden addiert, nachdem jeweils aus        #\n\
# den zweistelligen Produkten die Quersumme gebildet wurde           #\n\
# (z.B. Produkt 16 = Quersumme 7). Nach der Addition bleiben         #\n\
# außer der Einerstelle alle anderen Stellen unberücksichtigt.       #\n\
# Die Einerstelle wird von dem Wert 10 subtrahiert. Das Ergebnis     #\n\
# ist die Prüfziffer. Ergibt sich nach der Subtraktion der           #\n\
# Rest 10, ist die Prüfziffer 0.                                     #\n\
######################################################################\n";

      case 1: return "\
######################################################################\n\
#               Berechnung nach der Methode 01                       #\n\
######################################################################\n\
# Modulus 10, Gewichtung 3, 7, 1, 3, 7, 1, 3, 7, 1.                  #\n\
# Die einzelnen Stellen der Kontonummer sind von rechts nach         #\n\
# links mit den Ziffern 3, 7, 1, 3, 7, 1 usw. zu multiplizieren.     #\n\
# Die jeweiligen Produkte werden addiert. Nach der Addition          #\n\
# bleiben außer der Einerstelle alle anderen Stellen                 #\n\
# Unberücksichtigt. Die Einerstelle wird von dem Wert 10             #\n\
# subtrahiert. Das Ergebnis ist die Prüfziffer. Ergibt sich nach     #\n\
# der Subtraktion der Rest 10, ist die Prüfziffer 0.                 #\n\
######################################################################\n";

      case 2: return "\
######################################################################\n\
#               Berechnung nach der Methode 02                       #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 2.                  #\n\
# Die einzelnen Stellen der Kontonummer sind von rechts nach         #\n\
# links mit den Ziffern 2, 3, 4, 5, 6, 7, 8, 9, 2 zu                 #\n\
# multiplizieren. Die jeweiligen Produkte werden addiert.            #\n\
# Die Summe ist durch 11 zu dividieren. Der verbleibende Rest        #\n\
# wird vom Divisor (11) subtrahiert. Das Ergebnis ist die            #\n\
# Prüfziffer. Verbleibt nach der Division durch 11 kein Rest,        #\n\
# ist die Prüfziffer 0. Ergibt sich als Rest 1, ist die              #\n\
# Prüfziffer zweistellig und kann nicht verwendet werden.            #\n\
# Die Kontonummer ist dann nicht verwendbar.                         #\n\
######################################################################\n";

      case 3: return "\
######################################################################\n\
#               Berechnung nach der Methode 03                       #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2.                  #\n\
# Die Berechnung erfolgt wie bei Verfahren 01.                       #\n\
######################################################################\n";

      case 4: return "\
######################################################################\n\
#               Berechnung nach der Methode 04                       #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 2, 3, 4.                  #\n\
# Die Berechnung erfolgt wie bei Verfahren 02.                       #\n\
######################################################################\n";

      case 5: return "\
######################################################################\n\
#               Berechnung nach der Methode 05                       #\n\
######################################################################\n\
# Modulus 10, Gewichtung 7, 3, 1, 7, 3, 1, 7, 3, 1.                  #\n\
# Die Berechnung erfolgt wie bei Verfahren 01.                       #\n\
######################################################################\n";

      case 6: return "\
######################################################################\n\
#               Berechnung nach der Methode 06                       #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7 (modifiziert)              #\n\
# Die einzelnen Stellen der Kontonummer sind von rechts nach         #\n\
# links mit den Ziffern 2, 3, 4, 5, 6, 7, 2, 3 ff. zu multiplizieren.#\n\
# Die jeweiligen Produkte werden addiert. Die Summe ist              #\n\
# durch 11 zu dividieren. Der verbleibende Rest wird vom             #\n\
# Divisor (11) subtrahiert. Das Ergebnis ist die Prüfziffer.         #\n\
# Ergibt sich als Rest 1, findet von dem Rechenergebnis 10           #\n\
# nur die Einerstelle (0) als Prüfziffer Verwendung. Verbleibt       #\n\
# nach der Division durch 11 kein Rest, dann ist auch die            #\n\
# Prüfziffer 0. Die Stelle 10 der Kontonummer ist die Prüfziffer.    #\n\
######################################################################\n";

      case 7: return "\
######################################################################\n\
#               Berechnung nach der Methode 07                       #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 10.                 #\n\
# Die Berechnung erfolgt wie bei Verfahren 02.                       #\n\
######################################################################\n";

      case 8: return "\
######################################################################\n\
#               Berechnung nach der Methode 08                       #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2 (modifiziert).    #\n\
# Die Berechnung erfolgt wie bei Verfahren 00, jedoch erst           #\n\
# ab der Kontonummer 60 000.                                         #\n\
######################################################################\n";

      case 9: return "\
######################################################################\n\
#               Berechnung nach der Methode 09                       #\n\
######################################################################\n\
# Keine Prüfziffernberechung (es wird immer richtig zurückgegeben).  #\n\
######################################################################\n";

      case 10: return "\
######################################################################\n\
#               Berechnung nach der Methode 10                       #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 10 (modifiziert).   #\n\
# Die Berechnung erfolgt wie bei Verfahren 06.                       #\n\
######################################################################\n";

      case 11: return "\
######################################################################\n\
#              Berechnung nach der Methode 11                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 10 (modifiziert).   #\n\
# Die Berechnung erfolgt wie bei Verfahren 06. Beim Rechenergebnis   #\n\
# 10 wird die Null jedoch durch eine 9 ersetzt.                      #\n\
######################################################################\n";

      case 12: return "\
######################################################################\n\
#              Berechnung nach der Methode 12                        #\n\
######################################################################\n\
# frei/nicht definiert                                               #\n\
# Beim Aufruf dieser Methode wird grundsätzlich ein Fehler zurück-   #\n\
# gegeben, um nicht eine (evl. falsche) Implementation vorzutäuschen.#\n\
######################################################################\n";

      case 13: return "\
######################################################################\n\
#              Berechnung nach der Methode 13                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1.                           #\n\
# Die Berechnung erfolgt wie bei Verfahren 00. Es ist jedoch zu      #\n\
# beachten, daß die zweistellige Unterkonto-Nummer (Stellen 9        #\n\
# und 10) nicht in das Prüfziffernberechnungsverfahren mit           #\n\
# einbezogen werden darf. Die für die Berechnung relevante           #\n\
# sechsstellige Grundnummer befindet sich in den Stellen 2 bis 7,    #\n\
# die Prüfziffer in Stelle 8. Die Kontonummer ist neunstellig,       #\n\
# Stelle 1 ist also unbenutzt.                                       #\n\
# Ist die obengenannte Unternummer = 00 kommt es vor, daß sie        #\n\
# auf den Zahlungsverkehrsbelegen nicht angegeben ist. Ergibt        #\n\
# die erste Berechnung einen Prüfziffernfehler, wird empfohlen,      #\n\
# die Prüfziffernberechnung ein zweites Mal durchzuführen und        #\n\
# dabei die \"gedachte\" Unternummer 00 zu berücksichtigen.            #\n\
######################################################################\n";

      case 14: return "\
######################################################################\n\
#              Berechnung nach der Methode 14                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7.                           #\n\
# Die Berechnung erfolgt wie bei Verfahren 02. Es ist jedoch zu      #\n\
# beachten, daß die zweistellige Kontoart nicht in das Prüfziffern-  #\n\
# berechnungsverfahren mit einbezogen wird. Die Kontoart belegt      #\n\
# die Stellen 2 und 3, die zu berechnende Grundnummer die Stellen    #\n\
# 4 bis 9. Die Prüfziffer befindet sich in Stelle 10.                #\n\
######################################################################\n";

      case 15: return "\
######################################################################\n\
#              Berechnung nach der Methode 15                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5.                                 #\n\
# Die Berechnung erfolgt wie bei Verfahren 06. Es ist jedoch zu      #\n\
# beachten, daß nur die vierstellige Kontonummer in das              #\n\
# Prüfziffernberechnungsverfahren einbezogen wird. Sie befindet      #\n\
# sich in den Stellen 6 bis 9, die Prüfziffer in Stelle 10           #\n\
# der Kontonummer.                                                   #\n\
######################################################################\n";

      case 16: return "\
######################################################################\n\
#              Berechnung nach der Methode 16                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 2, 3, 4                   #\n\
# Die Berechnung erfolgt wie bei Verfahren 06. Sollte sich jedoch    #\n\
# nach der Division der Rest 1 ergeben, so ist die Kontonummer       #\n\
# unabhängig vom eigentlichen Berechnungsergebnis                    #\n\
# richtig, wenn die Ziffern an 10. und 9. Stelle identisch sind.     #\n\
######################################################################\n";

      case 17: return "\
######################################################################\n\
#              Berechnung nach der Methode 17                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 1, 2, 1, 2, 1, 2                            #\n\
# Die Kontonummer ist 10-stellig mit folgendem Aufbau:               #\n\
#                                                                    #\n\
#     KSSSSSSPUU                                                     #\n\
#     K = Kontoartziffer                                             #\n\
#     S = Stammnummer                                                #\n\
#     P = Prüfziffer                                                 #\n\
#     U = Unterkontonummer                                           #\n\
#                                                                    #\n\
# Die für die Berechnung relevante 6-stellige Stammnummer            #\n\
# (Kundennummer) befindet sich in den Stellen 2 bis 7 der            #\n\
# Kontonummer, die Prüfziffer in der Stelle 8. Die einzelnen         #\n\
# Stellen der Stammnummer (S) sind von links nach rechts mit         #\n\
# den Ziffern 1, 2, 1, 2, 1, 2 zu multiplizieren. Die                #\n\
# jeweiligen Produkte sind zu addieren, nachdem aus eventuell        #\n\
# zweistelligen Produkten der 2., 4. und 6. Stelle der               #\n\
# Stammnummer die Quersumme gebildet wurde. Von der Summe ist        #\n\
# der Wert \"1\" zu subtrahieren. Das Ergebnis ist dann durch          #\n\
# 11 zu dividieren. Der verbleibende Rest wird von 10                #\n\
# subtrahiert. Das Ergebnis ist die Prüfziffer. Verbleibt            #\n\
# nach der Division durch 11 kein Rest, ist die Prüfziffer 0.        #\n\
######################################################################\n";

      case 18: return "\
######################################################################\n\
#              Berechnung nach der Methode 18                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 3, 9, 7, 1, 3, 9, 7, 1, 3.                  #\n\
# Die Berechnung erfolgt wie bei Verfahren 01.                       #\n\
######################################################################\n";

      case 19: return "\
######################################################################\n\
#              Berechnung nach der Methode 19                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 1.                  #\n\
# Die Berechnung erfolgt wie bei Verfahren 06.                       #\n\
######################################################################\n";

      case 20: return "\
######################################################################\n\
#              Berechnung nach der Methode 20                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 3 (modifiziert).    #\n\
# Die Berechnung erfolgt wie bei Verfahren 06.                       #\n\
######################################################################\n";

      case 21: return "\
######################################################################\n\
#              Berechnung nach der Methode 21                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2 (modifiziert).    #\n\
# Die Berechnung erfolgt wie bei Verfahren 00. Nach der Addition     #\n\
# der Produkte werden neben der Einerstelle jedoch alle Stellen      #\n\
# berücksichtigt, indem solange Quersummen gebildet werden, bis      #\n\
# ein einstelliger Wert verbleibt. Die Differenz zwischen diesem     #\n\
# Wert und dem Wert 10 ist die Prüfziffer.                           #\n\
######################################################################\n";

      case 22: return "\
######################################################################\n\
#              Berechnung nach der Methode 22                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 3, 1, 3, 1, 3, 1, 3, 1, 3.                  #\n\
# Die einzelnen Stellen der Kontonummer sind von rechts nach         #\n\
# links mit den Ziffern 3, 1, 3, 1 usw. zu multiplizieren.           #\n\
# Von den jeweiligen Produkten bleiben die Zehnerstellen             #\n\
# unberücksichtigt. Die verbleibenden Zahlen (Einerstellen)          #\n\
# werden addiert. Die Differenz bis zum nächsten Zehner ist          #\n\
# die Prüfziffer.                                                    #\n\
######################################################################\n";

      case 23: return "\
######################################################################\n\
#     Berechnung nach der Methode 23 (geändert zum 3.9.2001)         #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7.                           #\n\
# Das Prüfziffernverfahren entspricht dem der Kennziffer 16,         #\n\
# wird jedoch nur auf die ersten sechs Ziffern der Kontonummer       #\n\
# angewandt. Die Prüfziffer befindet sich an der 7. Stelle der       #\n\
# Kontonummer. Die drei folgenden Stellen bleiben ungeprüft.         #\n\
# Sollte sich nach der Division der Rest 1 ergeben, so ist           #\n\
# die Kontonummer unabhängig vom eigentlichen Berechnungsergebnis    #\n\
# richtig, wenn die Ziffern an 6. und 7. Stelle identisch sind.      #\n\
######################################################################\n";

      case 24: return "\
######################################################################\n\
#              Berechnung nach der Methode 24                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 1, 2, 3, 1, 2, 3, 1, 2, 3                   #\n\
# Die für die Berechnung relevanten Stellen der Kontonummer          #\n\
# befinden sich in den Stellen 1 - 9 und die Prüfziffer in           #\n\
# Stelle 10 des zehnstelligen Kontonummernfeldes. Eine evtl.         #\n\
# in Stelle 1 vorhandene Ziffer 3, 4, 5, 6 wird wie 0 gewertet.      #\n\
# Eine ggf. in Stelle 1 vorhandene Ziffer 9 wird als 0 gewertet und  #\n\
# führt dazu, dass auch die beiden nachfolgenden Ziffern in den      #\n\
# Stellen 2 und 3 der Kontonummer als 0 gewertet werden müssen. Der  #\n\
# o. g. Prüfalgorithmus greift in diesem Fall also erst ab Stelle 4  #\n\
# der 10stelligen Kontonummer. Die Stelle 4 ist ungleich 0.          #\n\
#                                                                    #\n\
# Die einzelnen Stellen der Kontonummer sind von                     #\n\
# links nach rechts, beginnend mit der ersten signifikanten          #\n\
# Ziffer (Ziffer ungleich 0) in den Stellen 1 - 9, mit den           #\n\
# Ziffern 1, 2, 3, 1, 2, 3, 1, 2, 3 zu multiplizieren. Zum           #\n\
# jeweiligen Produkt ist die entsprechende Gewichtungsziffer         #\n\
# zu addieren (zum ersten Produkt + 1; zum zweiten Produkt + 2;      #\n\
# zum dritten Produkt +3; zum vierten Produkt + 1 usw.).             #\n\
# Die einzelnen Rechenergebnisse sind durch 11 zu dividieren.        #\n\
# Die sich nach der Division ergebenden Reste sind zu summieren.     #\n\
# Die Summe der Reste ist durch 10 zu dividieren. Der sich           #\n\
# danach ergebende Rest ist die Prüfziffer.                          #\n\
######################################################################\n";

      case 25: return "\
######################################################################\n\
#              Berechnung nach der Methode 25                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9 ohne Quersumme.      #\n\
# Die einzelnen Stellen der Kontonummer sind von rechts nach         #\n\
# links mit den Ziffern 2, 3, 4, 5, 6, 7, 8, 9 zu multiplizieren.    #\n\
# Die jeweiligen Produkte werden addiert. Die Summe ist durch        #\n\
# 11 zu dividieren. Der verbleibende Rest wird vom Divisor (11)      #\n\
# subtrahiert. Das Ergebnis ist die Prüfziffer. Verbleibt nach       #\n\
# der Division durch 11 kein Rest, ist die Prüfziffer 0.             #\n\
# Ergibt sich als Rest 1, ist die Prüfziffer immer 0 und kann        #\n\
# nur für die Arbeitsziffer 8 und 9 verwendet werden. Die            #\n\
# Kontonummer ist für die Arbeitsziffer 0, 1, 2, 3, 4, 5, 6          #\n\
# und 7 dann nicht verwendbar.                                       #\n\
# Die Arbeitsziffer (Geschäftsbereich oder Kontoart) befindet        #\n\
# sich in der 2. Stelle (von links) des zehnstelligen                #\n\
# Kontonummernfeldes.                                                #\n\
######################################################################\n";

      case 26: return "\
######################################################################\n\
#              Berechnung nach der Methode 26                        #\n\
######################################################################\n\
# Modulus 11. Gewichtung 2, 3, 4, 5, 6, 7, 2                         #\n\
# Die Kontonummer ist 10-stellig. Sind Stelle 1 und 2 mit            #\n\
# Nullen gefüllt ist die Kontonummer um 2 Stellen nach links         #\n\
# zu schieben und Stelle 9 und 10 mit Nullen zu füllen. Die          #\n\
# Berechnung erfolgt wie bei Verfahren 06 mit folgender              #\n\
# Modifizierung: für die Berechnung relevant sind die Stellen 1-7;   #\n\
# die Prüfziffer steht in Stelle 8. Bei den Stellen 9 und 10 handelt #\n\
# es sich um eine Unterkontonummer, welche für die Berechnung  nicht #\n\
# berücksichtigt wird.                                               #\n\
######################################################################\n";

      case 27: return "\
######################################################################\n\
#              Berechnung nach der Methode 27                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2 (modifiziert).    #\n\
# Die Berechnung erfolgt wie bei Verfahren 00, jedoch nur für        #\n\
# die Kontonummern von 1 bis 999.999.999. Ab Konto 1.000.000.000     #\n\
# kommt das Prüfziffernverfahren M10H (Iterierte Transformation)     #\n\
# zum Einsatz.                                                       #\n\
# Es folgt die Beschreibung der iterierten Transformation:           #\n\
# Die Position der einzelnen Ziffer von rechts nach links            #\n\
# innerhalb der Kontonummer gibt die Zeile 1 bis 4 der               #\n\
# Transformationstabelle an. Aus ihr sind die Übersetzungswerte      #\n\
# zu summieren. Die Einerstelle wird von 10 subtrahiert und          #\n\
# stellt die Prüfziffer dar.                                         #\n\
# Transformationstabelle:                                            #\n\
#    Ziffer    0 1 2 3 4 5 6 7 8 9                                   #\n\
#    Ziffer 1  0 1 5 9 3 7 4 8 2 6                                   #\n\
#    Ziffer 2  0 1 7 6 9 8 3 2 5 4                                   #\n\
#    Ziffer 3  0 1 8 4 6 2 9 5 7 3                                   #\n\
#    Ziffer 4  0 1 2 3 4 5 6 7 8 9                                   #\n\
######################################################################\n";

      case 28: return "\
######################################################################\n\
#              Berechnung nach der Methode 28                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8.                        #\n\
# Innerhalb der 10stelligen Kontonummer ist die 8. Stelle die        #\n\
# Prüfziffer. Die 9. und 10. Stelle der Kontonummer sind             #\n\
# Unterkontonummern, die nicht in die Prüfziffernberechnung          #\n\
# einbezogen sind.                                                   #\n\
# Jede Stelle der Konto-Stamm-Nummer wird mit einem festen           #\n\
# Stellenfaktor (Reihenfolge 8, 7, 6, 5, 4, 3, 2) multipliziert.     #\n\
# Die sich ergebenden Produkte werden addiert. Die aus der           #\n\
# Addition erhaltene Summe wird durch 11 dividiert. Der Rest         #\n\
# wird von 11 subtrahiert. Die Differenz wird der Konto-Stamm-       #\n\
# Nummer als Prüfziffer beigefügt. Wird als Rest eine 0 oder         #\n\
# eine 1 ermittelt, so lautet die Prüfziffer 0.                      #\n\
######################################################################\n";

      case 29: return "\
######################################################################\n\
#              Berechnung nach der Methode 29                        #\n\
######################################################################\n\
# Modulus 10, Iterierte Transformation.                              #\n\
# Die einzelnen Ziffern der Kontonummer werden über eine Tabelle     #\n\
# in andere Werte transformiert. Jeder einzelnen Stelle der          #\n\
# Kontonummer ist hierzu eine der Zeilen 1 bis 4 der Transforma-     #\n\
# tionstabelle fest zugeordnet. Die Transformationswerte werden      #\n\
# addiert. Die Einerstelle der Summe wird von 10 subtrahiert.        #\n\
# Das Ergebnis ist die Prüfziffer. Ist das Ergebnis = 10, ist        #\n\
# die Prüfziffer = 0.                                                #\n\
# Transformationstabelle:                                            #\n\
#    Ziffer    0 1 2 3 4 5 6 7 8 9                                   #\n\
#    Ziffer 1  0 1 5 9 3 7 4 8 2 6                                   #\n\
#    Ziffer 2  0 1 7 6 9 8 3 2 5 4                                   #\n\
#    Ziffer 3  0 1 8 4 6 2 9 5 7 3                                   #\n\
#    Ziffer 4  0 1 2 3 4 5 6 7 8 9                                   #\n\
######################################################################\n";

      case 30: return "\
######################################################################\n\
#              Berechnung nach der Methode 30                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 0, 0, 0, 0, 1, 2, 1, 2.                  #\n\
# Die letzte Stelle ist per Definition die Prüfziffer. Die           #\n\
# einzelnen Stellen der Kontonummer sind ab der ersten Stelle von    #\n\
# links nach rechts mit den Ziffern 2, 0, 0, 0, 0, 1, 2, 1, 2 zu     #\n\
# multiplizieren. Die jeweiligen Produkte werden addiert (ohne       #\n\
# Quersummenbildung). Die weitere Berechnung erfolgt wie bei         #\n\
# Verfahren 00.                                                      #\n\
######################################################################\n";

      case 31: return "\
######################################################################\n\
#              Berechnung nach der Methode 31                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 9, 8, 7, 6, 5, 4, 3, 2, 1                   #\n\
# Die Kontonummer ist 10-stellig. Die Stellen 1 bis 9 der            #\n\
# Kontonummer sind von rechts nach links mit den Ziffern 9,          #\n\
# 8, 7, 6, 5, 4, 3, 2, 1 zu multiplizieren. Die jeweiligen Produkte  #\n\
# werden addiert. Die Summe ist durch 11 zu dividieren. Der          #\n\
# verbleibende Rest ist die Prüfziffer. Verbleibt nach der           #\n\
# Division durch 11 kein Rest, ist die Prüfziffer 0. Ergibt sich ein #\n\
# Rest 10, ist die Kontonummer falsch.Die Prüfziffer  befindet sich  #\n\
# in der 10. Stelle der Kontonummer.                                 #\n\
######################################################################\n";

      case 32: return "\
######################################################################\n\
#              Berechnung nach der Methode 32                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7.                           #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 10 der Kontonummer ist         #\n\
# per Definition die Prüfziffer.                                     #\n\
# Es wird das Berechnungsverfahren 06 in modifizierter Form          #\n\
# auf die Stellen 4 bis 9 angewendet. Die Gewichtung ist             #\n\
# 2, 3, 4, 5, 6, 7. Die genannten Stellen werden von rechts          #\n\
# nach links mit diesen Faktoren multipliziert. Die restliche        #\n\
# Berechnung und mögliche Ergebnisse entsprechen dem Verfahren 06.   #\n\
######################################################################\n";

      case 33: return "\
######################################################################\n\
#              Berechnung nach der Methode 33                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6.                              #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 10 der Kontonummer ist         #\n\
# per Definition die Prüfziffer.                                     #\n\
# Es wird das Berechnungsverfahren 06 in modifizierter Form          #\n\
# auf die Stellen 5 bis 9 angewendet. Die Gewichtung ist             #\n\
# 2, 3, 4, 5, 6. Die genannten Stellen werden von rechts             #\n\
# nach links mit diesen Faktoren multipliziert. Die restliche        #\n\
# Berechnung und mögliche Ergebnisse entsprechen dem Verfahren 06.   #\n\
######################################################################\n";

      case 34: return "\
######################################################################\n\
#              Berechnung nach der Methode 34                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 4, 8, 5, A, 9, 7.                        #\n\
# Die Kontonummer ist 10-stellig. Es wird das Berechnungsverfahren   #\n\
# 28 mit modifizierter Gewichtung angewendet. Die Gewichtung         #\n\
# lautet: 2, 4, 8, 5, A, 9, 7. Dabei steht der Buchstabe A für       #\n\
# den Wert 10.                                                       #\n\
######################################################################\n";

      case 35: return "\
######################################################################\n\
#              Berechnung nach der Methode 35                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 10                  #\n\
# Die Kontonummer ist ggf. durch linksbündige Nullenauffüllung       #\n\
# 10-stellig darzustellen. Die 10. Stelle der Kontonummer ist die    #\n\
# Prüfziffer. Die Stellen 1 bis 9 der Kontonummer werden von         #\n\
# rechts nach links mit den Ziffern 2, 3, 4, ff. multipliziert. Die  #\n\
# jeweiligen Produkte werden addiert. Die Summe der Produkte         #\n\
# ist durch 11 zu dividieren. Der verbleibende Rest ist die          #\n\
# Prüfziffer. Sollte jedoch der Rest 10 ergeben, so ist die          #\n\
# Kontonummer unabhängig vom eigentlichen Berechnungsergebnis        #\n\
# richtig, wenn die Ziffern an 10. und 9. Stelle identisch           #\n\
# sind.                                                              #\n\
######################################################################\n";

      case 36: return "\
######################################################################\n\
#              Berechnung nach der Methode 36                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 4, 8, 5.                                 #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 10 der Kontonummer ist         #\n\
# per Definition die Prüfziffer.                                     #\n\
# Es wird das Berechnungsverfahren 06 in modifizierter Form          #\n\
# auf die Stellen 6 bis 9 angewendet. Die Gewichtung ist             #\n\
# 2, 4, 8, 5. Die genannten Stellen werden von rechts nach links     #\n\
# mit diesen Faktoren multipliziert. Die restliche Berechnung        #\n\
# und mögliche Ergebnisse entsprechen dem Verfahren 06.              #\n\
######################################################################\n";

      case 37: return "\
######################################################################\n\
#              Berechnung nach der Methode 37                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 4, 8, 5, A.                              #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 10 der Kontonummer ist         #\n\
# per Definition die Prüfziffer.                                     #\n\
# Es wird das Berechnungsverfahren 06 in modifizierter Form          #\n\
# auf die Stellen 5 bis 9 angewendet. Die Gewichtung ist             #\n\
# 2, 4, 8, 5, A. Dabei steht der Buchstabe A für den                 #\n\
# Wert 10. Die genannten Stellen werden von rechts nach links        #\n\
# mit diesen Faktoren multipliziert. Die restliche Berechnung        #\n\
# und mögliche Ergebnisse entsprechen dem Verfahren 06.              #\n\
######################################################################\n";

      case 38: return "\
######################################################################\n\
#              Berechnung nach der Methode 38                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 4, 8, 5, A, 9.                           #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 10 der Kontonummer ist         #\n\
# per Definition die Prüfziffer.                                     #\n\
# Es wird das Berechnungsverfahren 06 in modifizierter Form          #\n\
# auf die Stellen 4 bis 9 angewendet. Die Gewichtung ist             #\n\
# 2, 4, 8, 5, A, 9. Dabei steht der Buchstabe A für den              #\n\
# Wert 10. Die genannten Stellen werden von rechts nach links        #\n\
# mit diesen Faktoren multipliziert. Die restliche Berechnung        #\n\
# und mögliche Ergebnisse entsprechen dem Verfahren 06.              #\n\
######################################################################\n";

      case 39: return "\
######################################################################\n\
#              Berechnung nach der Methode 39                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 4, 8, 5, A, 9, 7.                        #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 10 der Kontonummer ist         #\n\
# per Definition die Prüfziffer.                                     #\n\
# Es wird das Berechnungsverfahren 06 in modifizierter Form          #\n\
# auf die Stellen 3 bis 9 angewendet. Die Gewichtung ist             #\n\
# 2, 4, 8, 5, A, 9, 7. Dabei steht der Buchstabe A für den           #\n\
# Wert 10. Die genannten Stellen werden von rechts nach links        #\n\
# mit diesen Faktoren multipliziert. Die restliche Berechnung        #\n\
# und mögliche Ergebnisse entsprechen dem Verfahren 06.              #\n\
######################################################################\n";

      case 40: return "\
######################################################################\n\
#              Berechnung nach der Methode 40                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 4, 8, 5, A, 9, 7, 3, 6.                  #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 10 der Kontonummer ist         #\n\
# per Definition die Prüfziffer.                                     #\n\
# Es wird das Berechnungsverfahren 06 in modifizierter Form          #\n\
# auf die Stellen 1 bis 9 angewendet. Die Gewichtung ist             #\n\
# 2, 4, 8, 5, A, 9, 7, 3, 6. Dabei steht der Buchstabe A für den     #\n\
# Wert 10. Die genannten Stellen werden von rechts nach links        #\n\
# mit diesen Faktoren multipliziert. Die restliche Berechnung        #\n\
# und mögliche Ergebnisse entsprechen dem Verfahren 06.              #\n\
######################################################################\n";

      case 41: return "\
######################################################################\n\
#              Berechnung nach der Methode 41                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2 (modifiziert)     #\n\
# Die Berechnung erfolgt wie bei Verfahren 00                        #\n\
# Ausnahme:                                                          #\n\
# Ist die 4. Stelle der Kontonummer (von links) = 9, so werden       #\n\
# die Stellen 1 bis 3 nicht in die Prüfzifferberechnung einbezogen.  #\n\
######################################################################\n";

      case 42: return "\
######################################################################\n\
#              Berechnung nach der Methode 42                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9.                     #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 10 der Kontonummer ist         #\n\
# per Definition die Prüfziffer.                                     #\n\
# Es wird das Berechnungsverfahren 06 in modifizierter Form          #\n\
# auf die Stellen 2 bis 9 angewendet. Die Gewichtung ist             #\n\
# 2, 3, 4, 5, 6, 7, 8, 9. Die genannten Stellen werden von           #\n\
# rechts nach links mit diesen Faktoren multipliziert. Die           #\n\
# restliche Berechnung und mögliche Ergebnisse entsprechen           #\n\
# dem Verfahren 06.                                                  #\n\
######################################################################\n";

      case 43: return "\
######################################################################\n\
#              Berechnung nach der Methode 43                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 1, 2, 3, 4, 5, 6, 7, 8, 9.                  #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 10 der Kontonummer ist         #\n\
# per Definition die Prüfziffer.                                     #\n\
# Das Verfahren wird auf die Stellen 1 bis 9 angewendet.             #\n\
# Die genannten Stellen werden von rechts nach links                 #\n\
# mit den Gewichtungsfaktoren multipliziert. Die Summe der           #\n\
# Produkte wird durch den Wert 10 dividiert. Der Rest der            #\n\
# Division wird vom Divisor subtrahiert. Die Differenz               #\n\
# ist die Prüfziffer. Ergibt die Berechnung eine Differenz           #\n\
# von 10, lautet die Prüfziffer 0.                                   #\n\
######################################################################\n";

      case 44: return "\
######################################################################\n\
#              Berechnung nach der Methode 44                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 4, 8, 5, A, 0, 0, 0, 0  (A = 10)         #\n\
#                                                                    #\n\
# Die Berechnung erfolgt wie bei Verfahren 33.                       #\n\
# Stellennr.:    1 2 3 4 5 6 7 8 9 10                                #\n\
# Kontonr.:      x x x x x x x x x P                                 #\n\
# Gewichtung:    0 0 0 0 A 5 8 4 2    (A = 10)                       #\n\
######################################################################\n";

      case 45: return "\
######################################################################\n\
#              Berechnung nach der Methode 45                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Die Berechnung erfolgt wie bei Verfahren 00                        #\n\
# Ausnahme:                                                          #\n\
# Kontonummern, die an Stelle 1 (von links) eine 0 enthalten,        #\n\
# und Kontonummern, die an Stelle 5 eine 1 enthalten,                #\n\
# beinhalten keine Prüfziffer.                                       #\n\
# Testkontonummern:                                                  #\n\
# 3545343232, 4013410024                                             #\n\
# Keine Prüfziffer enthalten:                                        #\n\
# 0994681254, 0000012340 (da 1. Stelle = 0)                          #\n\
# 1000199999, 0100114240 (da 5. Stelle = 1)                          #\n\
######################################################################\n";

      case 46: return "\
######################################################################\n\
#              Berechnung nach der Methode 46                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6.                              #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 8 der Kontonummer ist          #\n\
# per Definition die Prüfziffer.                                     #\n\
# Es wird das Berechnungsverfahren 06 in modifizierter Form          #\n\
# auf die Stellen 3 bis 7 angewendet. Die Gewichtung ist             #\n\
# 2, 3, 4, 5, 6. Die genannten Stellen werden von                    #\n\
# rechts nach links mit diesen Faktoren multipliziert. Die           #\n\
# restliche Berechnung und mögliche Ergebnisse entsprechen           #\n\
# dem Verfahren 06.                                                  #\n\
######################################################################\n";

      case 47: return "\
######################################################################\n\
#              Berechnung nach der Methode 47                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6.                              #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 9 der Kontonummer ist          #\n\
# per Definition die Prüfziffer.                                     #\n\
# Es wird das Berechnungsverfahren 06 in modifizierter Form          #\n\
# auf die Stellen 4 bis 8 angewendet. Die Gewichtung ist             #\n\
# 2, 3, 4, 5, 6. Die genannten Stellen werden von                    #\n\
# rechts nach links mit diesen Faktoren multipliziert. Die           #\n\
# restliche Berechnung und mögliche Ergebnisse entsprechen           #\n\
# dem Verfahren 06.                                                  #\n\
######################################################################\n";

      case 48: return "\
######################################################################\n\
#              Berechnung nach der Methode 48                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7.                           #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 9 der Kontonummer ist          #\n\
# per Definition die Prüfziffer.                                     #\n\
# Es wird das Berechnungsverfahren 06 in modifizierter Form          #\n\
# auf die Stellen 3 bis 8 angewendet. Die Gewichtung ist             #\n\
# 2, 3, 4, 5, 6, 7. Die genannten Stellen werden von                 #\n\
# rechts nach links mit diesen Faktoren multipliziert. Die           #\n\
# restliche Berechnung und mögliche Ergebnisse entsprechen           #\n\
# dem Verfahren 06.                                                  #\n\
######################################################################\n";

      case 49: return "\
######################################################################\n\
#              Berechnung nach der Methode 49                        #\n\
######################################################################\n\
# Variante 1                                                         #\n\
# Die Prüfzifferberechnung ist nach Kennziffer 00                    #\n\
# durchzuführen. Führt die Berechnung nach Variante 1 zu             #\n\
# einem Prüfzifferfehler, so ist die Berechnung nach                 #\n\
# Variante 2 vorzunehmen.                                            #\n\
#                                                                    #\n\
# Variante 2                                                         #\n\
# Die Prüfzifferberechnung ist nach Kennziffer 01                    #\n\
# durchzuführen.                                                     #\n\
######################################################################\n";

      case 50: return "\
######################################################################\n\
#              Berechnung nach der Methode 50                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7.                           #\n\
# Die Kontonummer ist 10-stellig. Die einzelnen Stellen der          #\n\
# Kontonummer werden von links nach rechts aufsteigend von           #\n\
# 1 bis 10 durchnumeriert. Die Stelle 7 der Kontonummer ist          #\n\
# per Definition die Prüfziffer.                                     #\n\
# Es wird das Berechnungsverfahren 06 in modifizierter Form          #\n\
# auf die Stellen 1 bis 6 angewendet. Die Gewichtung ist             #\n\
# 2, 3, 4, 5, 6, 7. Die genannten Stellen werden von                 #\n\
# rechts nach links mit diesen Faktoren multipliziert. Die           #\n\
# restliche Berechnung und mögliche Ergebnisse entsprechen           #\n\
# dem Verfahren 06.                                                  #\n\
# Ergibt die erste Berechnung einen Prüfziffernfehler, wird          #\n\
# empfohlen, die Prüfziffernberechnung ein zweites Mal durch-        #\n\
# zuführen und dabei die \"gedachte\" Unternummer 000 an die           #\n\
# Stellen 8 bis 10 zu setzen und die vorhandene Kontonummer          #\n\
# vorher um drei Stellen nach links zu verschieben                   #\n\
######################################################################\n";

      case 51: return "\
######################################################################\n\
#              Berechnung nach der Methode 51 (geändert 3.6.13)      #\n\
######################################################################\n\
# Die Kontonummer ist immer 10-stellig. Die für die Berechnung       #\n\
# relevante Kundennummer (K) befindet sich bei den Methoden A und C  #\n\
# in den Stellen 4 bis 9 der Kontonummer und bei den Methoden        #\n\
# B + D in den Stellen 5 bis 9, die Prüfziffer in Stelle 10          #\n\
# der Kontonummer.                                                   #\n\
#                                                                    #\n\
# Methode A:                                                         #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7                            #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen dem             #\n\
# Verfahren 06.                                                      #\n\
# Stellennr.:    1 2 3 4 5 6 7 8 9 A (A = 10)                        #\n\
# Kontonr.:      x x x K K K K K K P                                 #\n\
# Gewichtung:          7 6 5 4 3 2                                   #\n\
#                                                                    #\n\
# Ergibt die Berechnung der Prüfziffer nach der Methode A            #\n\
# einen Prüfzifferfehler, ist eine weitere Berechnung mit der        #\n\
# Methode B vorzunehmen.                                             #\n\
#                                                                    #\n\
# Methode B:                                                         #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6                               #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen dem             #\n\
# Verfahren 33.                                                      #\n\
# Stellennr.:    1 2 3 4 5 6 7 8 9 A (A = 10)                        #\n\
# Kontonr.:      x x x x K K K K K P                                 #\n\
# Gewichtung:            6 5 4 3 2                                   #\n\
#                                                                    #\n\
# Ergibt auch die Berechnung der Prüfziffer nach Methode B           #\n\
# einen Prüfzifferfehler, ist eine weitere Berechnung mit der        #\n\
# Methode C vorzunehmen.                                             #\n\
#                                                                    #\n\
# Methode C:                                                         #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1                            #\n\
# Die Berechnung und die möglichen Ergebnisse entsprechen            #\n\
# dem Verfahren 00; es ist jedoch zu beachten, dass nur die          #\n\
# Stellen 4 bis 9 in das Prüfzifferberechnungsverfahren              #\n\
# einbezogen werden                                                  #\n\
# Stellennr.:    1 2 3 4 5 6 7 8 9 A (A = 10)                        #\n\
# Kontonr.:      x x x K K K K K K P                                 #\n\
# Gewichtung:          1 2 1 2 1 2                                   #\n\
#                                                                    #\n\
# Ergibt auch die Berechnung der Prüfziffer nach Methode C           #\n\
# einen Prüfzifferfehler, ist eine weitere Berechnung mit der        #\n\
# Methode D vorzunehmen.                                             #\n\
#                                                                    #\n\
# Methode D:                                                         #\n\
# Kontonummern, die bis zur Methode D gelangen und in der 10.        #\n\
# Stelle eine 7, 8 oder 9 haben, sind ungültig.                      #\n\
# Modulus 7, Gewichtung 2, 3, 4, 5, 6                                #\n\
# Das Berechnungsverfahren entspricht Methode B. Die Summe der       #\n\
# Produkte ist jedoch durch 7 zu dividieren. Der verbleibende        #\n\
# Rest wird vom Divisor (7) subtrahiert. Das Ergebnis ist die        #\n\
# Prüfziffer. Verbleibt kein Rest, ist die Prüfziffer 0.             #\n\
#                                                                    #\n\
# Ausnahme:                                                          #\n\
# Ist nach linksbündiger Auffüllung mit Nullen auf 10 Stellen die    #\n\
# 3. Stelle der Kontonummer = 9 (Sachkonten), so erfolgt die         #\n\
# Berechnung wie folgt:                                              #\n\
#                                                                    #\n\
# Variante 1 zur Ausnahme                                            #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8                         #\n\
# Die für die Berechnung relevanten Stellen 3 bis 9 werden von       #\n\
# rechts nach links mit den Ziffern 2, 3, 4, 5, 6, 7, 8              #\n\
# multipliziert. Die Produkte werden addiert. Die Summe ist durch 11 #\n\
# zu dividieren. Der verbleibende Rest wird vom Divisor (11)         #\n\
# subtrahiert. Das Ergebnis ist die Prüfziffer. Ergibt sich als Rest #\n\
# 1 oder 0, ist die Prüfziffer 0.                                    #\n\
#                                                                    #\n\
# Stellennr.:   1 2 3 4 5 6 7 8 9 A (A=10)                           #\n\
# Kontonr.;     x x 9 x x x x x x P                                  #\n\
# Gewichtung:       8 7 6 5 4 3 2                                    #\n\
#                                                                    #\n\
# Führt die Variante 1 zur Ausnahme zu einem Prüfzifferfehler, ist   #\n\
# eine weitere Berechnung nach der Variante 2 vorzunehmen.           #\n\
#                                                                    #\n\
# Variante 2 zur Ausnahme                                            #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 10                  #\n\
# Berechnung und Ergebnisse entsprechen der Variante 1 zur Ausnahme. #\n\
######################################################################\n";

      case 52: return "\
######################################################################\n\
#              Berechnung nach der Methode 52                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 4, 8, 5, 10, 9, 7, 3, 6, 1, 2, 4.        #\n\
# Zur Berechnung der Prüfziffer muß zunächst aus der angegebenen     #\n\
# achtstelligen Kontonummer die zugehörige Kontonummer des ESER-     #\n\
# Altsystems (maximal 12stellig) ermittelt werden. Die einzelnen     #\n\
# Stellen dieser Alt-Kontonummer sind von rechts nach links mit      #\n\
# den Ziffern 2, 4, 8, 5, 10, 9, 7, 3, 6, 1, 2, 4 zu multipli-       #\n\
# zieren. Dabei ist für die Prüfziffer, die sich immer an der        #\n\
# 6. Stelle von links der Alt-Kontonummer befindet, 0 zu setzen.     #\n\
# Die jeweiligen Produkte werden addiert und die Summe durch 11      #\n\
# dividiert. Zum Divisionsrest (ggf. auch 0) ist das Gewicht         #\n\
# oder ein Vielfaches des Gewichtes über der Prüfziffer zu           #\n\
# addieren. Die Summe wird durch 11 dividiert; der Divisionsrest     #\n\
# muß 10 lauten. Die Prüfziffer ist der verwendete Faktor des        #\n\
# Gewichtes. Kann bei der Division kein Rest 10 erreicht werden,     #\n\
# ist die Konto-Nr. nicht verwendbar.                                #\n\
# Bildung der Konto-Nr. des ESER-Altsystems aus angegebener          #\n\
# Bankleitzahl und Konto-Nr.: XXX5XXXX XPXXXXXX (P=Prüfziffer)       #\n\
# Kontonummer des Altsystems: XXXX-XP-XXXXX (XXXXX = variable        #\n\
# Länge, da evtl.vorlaufende Nullen eliminiert werden).              #\n\
# Bei 10stelligen, mit 9 beginnenden Kontonummern ist die            #\n\
# Prüfziffer nach Kennziffer 20 zu berechnen.                        #\n\
######################################################################\n";

      case 53: return "\
######################################################################\n\
#              Berechnung nach der Methode 53                        #\n\
######################################################################\n\
# Analog Kennziffer 52, jedoch für neunstellige Kontonummern.        #\n\
# Bildung der Kontonummern des ESER-Altsystems aus angegebener       #\n\
# Bankleitzahl und angegebener neunstelliger Kontonummer:            #\n\
# XXX5XXXX XTPXXXXXX (P=Prüfziffer)                                  #\n\
# Kontonummer des Altsystems: XXTX-XP-XXXXX (XXXXX = variable        #\n\
# Länge, da evtl.vorlaufende Nullen eliminiert werden).              #\n\
# Die Ziffer T ersetzt die 3. Stelle von links der nach              #\n\
# Kennziffer 52 gebildeten Kontonummer des ESER-Altsystems.          #\n\
# Bei der Bildung der Kontonummer des ESER-Altsystems wird die       #\n\
# Ziffer T nicht in den Kundennummernteil (7.-12. Stelle der         #\n\
# Kontonummer) übernommen.                                           #\n\
# Bei 10stelligen, mit 9 beginnenden Kontonummern ist die            #\n\
# Prüfziffer nach Kennziffer 20 zu berechnen.                        #\n\
######################################################################\n";

      case 54: return "\
######################################################################\n\
#              Berechnung nach der Methode 54                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 2                         #\n\
# Die Kontonummer ist 10-stellig, wobei die Stellen 1 u. 2           #\n\
# generell mit 49 belegt sind. Die einzelnen Stellen der             #\n\
# Kontonummer sind von rechts nach links mit den Ziffern 2, 3,       #\n\
# 4, 5, 6, 7, 2 zu multiplizieren. Die jeweiligen Produkte werden    #\n\
# addiert. Die Summe ist durch 11 zu dividieren. Der verbleibende    #\n\
# Rest wird vom Divisor (11) subtrahiert. Das Ergebnis ist die       #\n\
# Prüfziffer. Ergibt sich als Rest 0 oder 1, ist die Prüfziffer      #\n\
# zweistellig und kann nicht verwendet werden. Die Kontonummer       #\n\
# ist dann nicht verwendbar.                                         #\n\
######################################################################\n";

      case 55: return "\
######################################################################\n\
#              Berechnung nach der Methode 55                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 7, 8 (modifiziert).    #\n\
# Die Berechnung erfolgt wie bei Verfahren 06.                       #\n\
# Die einzelnen Stellen der Kontonummer sind von rechts nach         #\n\
# links mit den Ziffern 2, 3, 4, 5, 6, 7, 8, 7, 8 zu                 #\n\
# multiplizieren. Die jeweiligen Produkte werden addiert.            #\n\
# Die Summe ist durch 11 zu dividieren. Der verbleibende Rest        #\n\
# wird vom Divisor (11) subtrahiert. Das Ergebnis ist die            #\n\
# Prüfziffer. Verbleibt nach der Division durch 11 kein Rest,        #\n\
# ist die Prüfziffer 0. Ergibt sich als Rest 1, entsteht bei         #\n\
# der Subtraktion 11 - 1 = 10. Das Rechenergebnis ist                #\n\
# nicht verwendbar und muß auf eine Stelle reduziert werden.         #\n\
# Die linke Seite wird eliminiert, und nur die rechte Stelle         #\n\
# (Null) findet als Prüfziffer Verwendung.                           #\n\
######################################################################\n";

      case 56: return "\
######################################################################\n\
#              Berechnung nach der Methode 56                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 2, 3, 4.                  #\n\
# Prüfziffer ist die letzte Stelle der Kontonummer.                  #\n\
# Von rechts beginnend werden die einzelnen Ziffern der              #\n\
# Kontonummer mit den Gewichten multipliziert. Die Produkte der      #\n\
# Multiplikation werden addiert und diese Summe durch 11             #\n\
# dividiert. Der Rest wird von 11 abgezogen, das Ergebnis ist        #\n\
# die Prüfziffer, die an die Kontonummer angehängt wird.             #\n\
# 1. Bei dem Ergebnis 10 oder 11 ist die Kontonummer ungültig.       #\n\
# 2. Beginnt eine zehnstellige Kontonummer mit 9, so wird beim       #\n\
# Ergebnis 10 die Prüfziffer 7 und beim Ergebnis 11 die              #\n\
# Prüfziffer 8 gesetzt.                                              #\n\
######################################################################\n";

      case 57: return "\
######################################################################\n\
#    Berechnung nach der Methode 57 (geändert zum 09.09.2013)        #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen. Die    #\n\
# Berechnung der Prüfziffer und die möglichen Ergebnisse richten     #\n\
# sich nach dem jeweils bei der entsprechenden Variante angegebenen  #\n\
# Kontonummernkreis. Führt die Berechnung der Prüfziffer nach der    #\n\
# vorgegebenen Variante zu einem Prüfzifferfehler, so ist die        #\n\
# Kontonummer ungültig. Kontonummern, die mit 00 beginnen sind       #\n\
# immer als falsch zu bewerten.                                      #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 10, Gewichtung 1, 2, 1, 2, 1, 2, 1, 2, 1                   #\n\
# Anzuwenden ist dieses Verfahren für Kontonummern, die mit den      #\n\
# folgenden Zahlen beginnen:                                         #\n\
#                                                                    #\n\
# 51, 55, 61, 64, 65, 66, 70, 73 bis 82, 88, 94 und 95               #\n\
# (Konten, die mit 74 beginnen, ab 9.9.2013; bis dahin werden diese  #\n\
# mit Variante 2 berechnet)                                          #\n\
#                                                                    #\n\
# Die Stellen 1 bis 9 der Kontonummer sind von                       #\n\
# links beginnend mit den Gewichten zu multiplizieren. Die 10.       #\n\
# Stelle ist die Prüfziffer. Die Berechnung und mögliche Ergebnisse  #\n\
# entsprechen der Methode 00.                                        #\n\
#                                                                    #\n\
# Ausnahme: Kontonummern, die mit den Zahlen 777777 oder 888888      #\n\
# beginnen sind immer als richtig (= Methode 09; keine Prüfziffer-   #\n\
# berechnung) zu bewerten.                                           #\n\
#                                                                    #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 10, Gewichtung 1, 2, 1, 2, 1, 2, 1, 2, 1                   #\n\
# Anzuwenden ist dieses Verfahren für Kontonummern, die mit den      #\n\
# folgenden Zahlen beginnen:                                         #\n\
#                                                                    #\n\
# 32 bis 39, 41 bis 49, 52, 53, 54, 56 bis 60, 62, 63, 67, 68, 69,   #\n\
# 71, 72, 83 bis 87, 89, 90, 92, 93, 96, 97 und 98                   #\n\
# (bis 9.9.2013 auch Konten, die mit 74 beginnen)                    #\n\
#                                                                    #\n\
# Die Stellen 1, 2, 4, 5, 6, 7, 8, 9 und 10 der Kontonummer sind     #\n\
# von links beginnend mit den Gewichten zu multiplizieren. Die 3.    #\n\
# Stelle ist die Prüfziffer. Die Berechnung und mögliche Ergebnisse  #\n\
# entsprechen der Methode 00.                                        #\n\
#                                                                    #\n\
# Variante 3:                                                        #\n\
# Für die Kontonummern, die mit den folgenden Zahlen beginnen gilt   #\n\
# die Methode 09 (keine Prüfzifferberechnung):                       #\n\
# 40, 50, 91 und 99                                                  #\n\
#                                                                    #\n\
# Variante 4:                                                        #\n\
# Kontonummern die mit 01 bis 31 beginnen haben an der dritten bis   #\n\
# vierten Stelle immer einen Wert zwischen 01 und 12 *und* an der    #\n\
# siebten bis neunten Stelle immer einen Wert kleiner 500.           #\n\
#                                                                    #\n\
# Ausnahme: Die Kontonummer 0185125434 ist als richtig zu            #\n\
# bewerten.                                                          #\n\
######################################################################\n";

      case 58: return "\
######################################################################\n\
#   Berechnung nach der Methode 58 (geändert zum 4.3.2002)           #\n\
######################################################################\n\
# Die Kontonummer (mindestens 6-stellig) ist durch linksbündige      #\n\
# Nullenauffüllung 10-stellig darzustellen. Danach ist die 10.       #\n\
# Stelle die Prüfziffer. Die Stellen 5 bis 9 werden von rechts nach  #\n\
# links mit den Ziffern 2, 3, 4, 5, 6 multipliziert. Die restliche   #\n\
# Berechnung und die Ergebnisse entsprechen dem Verfahren 02.        #\n\
#                                                                    #\n\
# Ergibt die Division einen Rest von 0, so ist die Prüfziffer = 0.   #\n\
# Bei einem Rest von 1 ist die Kontonummer falsch.                   #\n\
######################################################################\n";

      case 59: return "\
######################################################################\n\
#    Berechnung nach der Methode 59 (geändert seit 3.12.2001)        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2.                  #\n\
# Die Berechnung erfolgt wie bei Verfahren 00; es ist jedoch         #\n\
# zu beachten, daß Kontonummern, die kleiner als 9-stellig sind,     #\n\
# nicht in die Prüfziffernberechnung einbezogen werden.              #\n\
######################################################################\n";

      case 60: return "\
######################################################################\n\
#              Berechnung nach der Methode 60                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2.                        #\n\
# Die Berechnung erfolgt wie bei Verfahren 00. Es ist jedoch zu      #\n\
# beachten, daß die zweistellige Unterkontonummer (Stellen 1 und     #\n\
# 2) nicht in das Prüfziffernverfahren mit einbezogen werden darf.   #\n\
# Die für die Berechnung relevante siebenstellige Grundnummer        #\n\
# befindet sich in den Stellen 3 bis 9, die Prüfziffer in der        #\n\
# Stelle 10.                                                         #\n\
######################################################################\n";

      case 61: return "\
######################################################################\n\
#              Berechnung nach der Methode 61                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2.                        #\n\
# Darstellung der Kontonummer: B B B S S S S P A U (10-stellig).     #\n\
# B = Betriebsstellennummer                                          #\n\
# S = Stammnummer                                                    #\n\
# P = Prüfziffer                                                     #\n\
# A = Artziffer                                                      #\n\
# U = Unternummer                                                    #\n\
# Die Berechnung erfolgt wie bei Verfahren 00 über Betriebs-         #\n\
# stellennummer und Stammnummer mit der Gewichtung 2, 1, 2, 1,       #\n\
# 2, 1, 2.                                                           #\n\
# Ist die Artziffer (neunte Stelle der Kontonummer) eine 8, so       #\n\
# werden die neunte und zehnte Stelle der Kontonummer in die         #\n\
# Prüfziffernermittlung einbezogen. Die Berechnung erfolgt dann      #\n\
# über Betriebsstellennummer, Stammnummer, Artziffer und Unter-      #\n\
# nummer mit der Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2.               #\n\
######################################################################\n";

      case 62: return "\
######################################################################\n\
#              Berechnung nach der Methode 62                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2.                              #\n\
# Die beiden ersten und die beiden letzten Stellen sind              #\n\
# nicht zu berücksichtigen. Die Stellen drei bis sieben              #\n\
# sind von rechts nach links mit den Ziffern 2, 1, 2, 1, 2           #\n\
# zu multiplizieren. Aus zweistelligen Einzelergebnissen             #\n\
# ist eine Quersumme zu bilden. Alle Ergebnisse sind dann            #\n\
# zu addieren. Die Differenz zum nächsten Zehner ergibt die          #\n\
# Prüfziffer auf Stelle acht. Ist die Differenz 10, ist die          #\n\
# Prüfziffer 0.                                                      #\n\
######################################################################\n";

      case 63: return "\
######################################################################\n\
#              Berechnung nach der Methode 63                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1.                           #\n\
# Die für die Berechnung relevante 6-stellige Grundnummer            #\n\
# (Kundennummer) befindet sich in den Stellen 2-7, die Prüfziffer    #\n\
# in Stelle 8 der Kontonummer. Die zweistellige Unterkontonummer     #\n\
# (Stellen 9-10) ist nicht in das Prüfziffernverfahren einzu-        #\n\
# beziehen. Die einzelnen Stellen der Grundnummer sind von rechts    #\n\
# nach links mit den Ziffern 2, 1, 2, 1, 2, 1 zu multiplizieren.     #\n\
# Die jeweiligen Produkte werden addiert, nachdem jeweils aus        #\n\
# den zweistelligen Produkten die Quersumme gebildet wurde           #\n\
# (z.B. Produkt 16 = Quersumme 7). Nach der Addition bleiben         #\n\
# außer der Einerstelle alle anderen Stellen unberücksichtigt.       #\n\
# Die Einerstelle wird von dem Wert 10 subtrahiert. Das Ergebnis     #\n\
# ist die Prüfziffer (Stelle 8). Hat die Einerstelle den Wert 0,     #\n\
# ist die Prüfziffer 0. Ausnahmen:                                   #\n\
# Ist die Ziffer in Stelle 1 vor der sechsstelligen Grundnummer      #\n\
# nicht 0, ist das Ergebnis als falsch zu werten.                    #\n\
# Ist die Unterkontonummer 00, kann es vorkommen, daß sie auf        #\n\
# den Zahlungsverkehrsbelegen nicht angegeben ist, die Kontonummer   #\n\
# jedoch um führende Nullen ergänzt wurde. In diesem Fall sind       #\n\
# z.B. die Stellen 1-3 000, die Prüfziffer ist an der Stelle 10.     #\n\
######################################################################\n";

      case 64: return "\
######################################################################\n\
#              Berechnung nach der Methode 64                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 9, 10, 5, 8, 4, 2.                          #\n\
#  Die Kontonummer ist 10-stellig. Die für die Berechnung relevanten #\n\
#  Stellen der Kontonummer befinden sich in den Stellen 1 bis 6 und  #\n\
#  werden von links nach rechts mit den Ziffern 9, 10, 5, 8, 4, 2    #\n\
#  multipliziert. Die weitere Berechnung und Ergebnisse entsprechen  #\n\
#  dem Verfahren 06. Die Prüfziffer befindet sich in Stelle 7 der    #\n\
#  Kontonummer.                                                      #\n\
######################################################################\n";

      case 65: return "\
######################################################################\n\
#              Berechnung nach der Methode 65                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2.                        #\n\
# Die Kontonummer ist zehnstellig: G G G S S S S P K U               #\n\
# G = Geschäftstellennummer                                          #\n\
# S = Stammnummer                                                    #\n\
# P = Prüfziffer                                                     #\n\
# K = Kontenartziffer                                                #\n\
# U = Unterkontonummer                                               #\n\
# Die Berechnung erfolgt wie bei Verfahren 00 über Geschäfts-        #\n\
# stellennummer und Stammnummer mit der Gewichtung 2, 1, 2,...       #\n\
# Ausnahme: Ist die Kontenartziffer (neunte Stelle der Konto-        #\n\
# nummer) eine 9, so werden die neunte und zehnte Stelle der         #\n\
# Kontonummer in die Prüfziffernermittlung einbezogen. Die           #\n\
# Berechnung erfolgt dann über die Geschäftsstellennummer,           #\n\
# Stammnummer, Kontenartziffer und Unterkontonummer mit der          #\n\
# Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2.                              #\n\
######################################################################\n";

      case 66: return "\
######################################################################\n\
#              Berechnung nach der Methode 66                        #\n\
######################################################################\n\
# Aufbau der 9-stelligen Kontonummer (innerhalb des                  #\n\
# zwischenbetrieblich 10-stelligen Feldes)                           #\n\
# Stelle    1    = gehört nicht zur Kontonummer, muss                #\n\
#                  daher 0 sein                                      #\n\
#           2    = Stammnunmmer                                      #\n\
#           3-4  = Unterkontonummer, wird bei der Prüfziffer-        #\n\
#                  berechnung nicht berücksichtigt                   #\n\
#           5-9  = Stammnummer                                       #\n\
#           10   = Prüfziffer                                        #\n\
# Der 9-stelligen Kontonummer wird für die Prüfzifferberechnung      #\n\
# eine 0 vorangestellt. Die Prüfziffer steht in Stelle 10. Die für   #\n\
# die Berechnung relevante 6-stellige Stammnummer (Kundenummer)      #\n\
# befindet sich in den Stellen 2 und  5 bis 9. Die zweistellige      #\n\
# Unterkontonummer (Stellen 3 und 4) wird nicht in das               #\n\
# Prüfzifferberechnungsverfahren mit einbezogen und daher mit 0      #\n\
# gewichtet. Die einzelnen Stellen der Stammnummer sind von rechts   #\n\
# nach links mit den Ziffern 2, 3, 4, 5, 6, 0, 0, 7 zu               #\n\
# multiplizieren. Die jeweiligen Produkte werden addiert. Die        #\n\
# Summe ist durch 11 zu dividieren. Bei einem verbleibenden Rest     #\n\
# von 0 ist die Prüfziffer 1. Bei einem Rest von 1 ist die           #\n\
# Prüfziffer 0 Verbleibt ein Rest von 2 bis 10, so wird dieser vom   #\n\
# Divison (11) subtrahiert. Die Differenz ist dann die Prüfziffer.   #\n\
######################################################################\n";

      case 67: return "\
######################################################################\n\
#              Berechnung nach der Methode 67                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2.                        #\n\
# Die Kontonummer ist zehnstellig. Die Berechnung erfolgt wie bei    #\n\
# Verfahren 00. Es ist jedoch zu beachten, daß die zweistellige      #\n\
# Unterkontonummer (Stellen 9 und 10) nicht in das Prüfziffern-      #\n\
# verfahren mit einbezogen werden darf. Die für die Berechnung       #\n\
# relevante siebenstellige Stammnummer befindet sich in den          #\n\
# Stellen 1 bis 7, die Prüfziffer in der Stelle 8.                   #\n\
######################################################################\n";

      case 68: return "\
######################################################################\n\
#              Berechnung nach der Methode 68                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2.                  #\n\
# Die Kontonummern sind 6 bis 10stellig und enthalten keine          #\n\
# führenden Nullen. Die erste Stelle von rechts ist die              #\n\
# Prüfziffer. Die Berechnung erfolgt wie bei Verfahren 00,           #\n\
# hierbei sind jedoch folgende Besonderheiten zu beachten:           #\n\
# Bei 10stelligen Kontonummern erfolgt die Berechnung für die        #\n\
# 2. bis 7. Stelle (von rechts!). Stelle 7 muß eine 9 sein.          #\n\
# 6 bis 9stellige Kontonummern sind in zwei Varianten prüfbar.       #\n\
# Variante 1: voll prüfbar.                                          #\n\
# Ergibt die Berechnung nach Variante 1 einen Prüfziffernfehler,     #\n\
# muß Variante 2 zu einer korrekten Prüfziffer führen.               #\n\
# Variante 2: Stellen 7 und 8 werden nicht geprüft.                  #\n\
# 9stellige Kontonummern im Nummerenbereich 400000000 bis            #\n\
# 4999999999 sind nicht prüfbar, da diese Nummern keine              #\n\
# Prüfziffer enthalten.                                              #\n\
######################################################################\n";

      case 69: return "\
######################################################################\n\
#              Berechnung nach der Methode 69                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8.                        #\n\
# Die Berechnung erfolgt wie bei Verfahren 28. Ergibt die            #\n\
# Berechnung einen Prüfziffernfehler, so ist die Prüfziffer          #\n\
# nach Variante II zu ermitteln (s.u.).                              #\n\
# Ausnahmen:                                                         #\n\
# Für den Kontonummernkreis 9300000000 - 9399999999 ist keine        #\n\
# Prüfziffernberechnung möglich = Kennziffer 09.                     #\n\
# Für den Kontonummernkreis 9700000000 - 9799999999 ist die          #\n\
# Prüfziffernberechnung wie folgt vorzunehmen (Variante II):         #\n\
# Die Position der einzelnen Ziffern von rechts nach links           #\n\
# innerhalb der Kontonummer gibt die Zeile 1 bis 4 der Trans-        #\n\
# formationstabelle an. Aus ihr sind die Übersetzungswerte zu        #\n\
# summieren. Die Einerstelle wird von 10 subtrahiert und stellt      #\n\
# die Prüfziffer dar.                                                #\n\
# Transformationstabelle:                                            #\n\
# Ziffer    : 0123456789                                             #\n\
# Zeile 1   : 0159374826                                             #\n\
# Zeile 2   : 0176983254                                             #\n\
# Zeile 3   : 0184629573                                             #\n\
# Zeile 4   : 0123456789                                             #\n\
######################################################################\n";

      case 70: return "\
######################################################################\n\
#              Berechnung nach der Methode 70                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7.                           #\n\
# Die Kontonummer ist zehnstellig. Die einzelnen Stellen der         #\n\
# Kontonummer sind von rechts nach links mit den Ziffern             #\n\
# 2,3,4,5,6,7,2,3,4 zu multiplizieren. Die Berechnung erfolgt wie    #\n\
# bei Verfahren 06.                                                  #\n\
# Ausnahme: Ist die 4. Stelle der Kontonummer = 5 oder die 4. -      #\n\
# 5. Stelle der Kontonummer = 69, so werden die Stellen 1 - 3        #\n\
# nicht in die Prüfziffernermittlung einbezogen.                     #\n\
######################################################################\n";

      case 71: return "\
######################################################################\n\
#              Berechnung nach der Methode 71                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 6, 5, 4, 3, 2, 1.                           #\n\
# Die Kontonummer ist immer 10-stellig. Die Stellen 2 bis 7          #\n\
# sind von links nach rechts mit den Ziffern 6, 5, 4, 3, 2, 1 zu     #\n\
# multiplizieren. Die Ergebnisse sind dann ohne Quersummenbildung    #\n\
# zu addieren. Die Summe ist durch 11 zu dividieren.                 #\n\
# Der verbleibende Rest wird vom Divisor (11) subtrahiert.           #\n\
# Das Ergebnis ist die Prüfziffer.                                   #\n\
# Ausnahmen: Verbleibt nach der Division durch 11 kein Rest, ist     #\n\
# die Prüfziffer 0. Ergibt sich als Rest 1, entsteht bei der         #\n\
# Subtraktion 11 ./. 1 = 10; die Zehnerstelle (1) ist dann           #\n\
# die Prüfziffer.                                                    #\n\
######################################################################\n";

      case 72: return "\
######################################################################\n\
#              Berechnung nach der Methode 72                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1.                           #\n\
# Die Kontonummer ist zehnstellig. Die Berechnung erfolgt wie bei    #\n\
# Verfahren 00. Es ist jedoch zu beachten, daß die zweistellige      #\n\
# Unterkontonummer (Stellen 1 und 2) und die Artziffer (Stelle 3)    #\n\
# nicht in das Prüfziffernverfahren mit einbezogen werden.           #\n\
# Die für die Berechnung relevante sechsstellige Kundennummer        #\n\
# befindet sich in den Stellen 4 bis 9, die Prüfziffer in der        #\n\
# Stelle 10.                                                         #\n\
######################################################################\n";

      case 73: return "\
######################################################################\n\
#    Berechnung nach der Methode 73  (geändert zum 6.12.2004)        #\n\
######################################################################\n\
#                                                                    #\n\
# Die Kontonummer ist durch linksbündiges Auffüllen mit Nullen       #\n\
# 10-stellig darzustellen. Die 10. Stelle der Kontonummer ist die    #\n\
# Prüfziffer.                                                        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1                            #\n\
# Die Stellen 4 bis 9 der Kontonummer werden von rechts nach links   #\n\
# mit den Ziffern 2, 1, 2, 1, 2, 1 multipliziert. Die Berechnung und #\n\
# Ergebnisse entsprechen dem Verfahren 00.                           #\n\
#                                                                    #\n\
# Führt die Berechnung nach Variante 1 zu einem Prüfzifferfehler,    #\n\
# ist eine weitere Berechnung nach Variante 2 vorzunehmen.           #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2                               #\n\
# Das Berechnungsverfahren entspricht Variante 1, es ist jedoch zu   #\n\
# beachten, dass nur die Stellen 5 bis 9 in das Prüfziffern-         #\n\
# berechnungsverfahren einbezogen werden.                            #\n\
#                                                                    #\n\
# Führt die Berechnung auch nach Variante 2 zu einem Prüfziffer-     #\n\
# fehler, ist die Berechnung nach Variante 3 vorzunehmen:            #\n\
#                                                                    #\n\
# Variante 3                                                         #\n\
# Modulus 7, Gewichtung 2, 1, 2, 1, 2 Das Berechnungsverfahren       #\n\
# entspricht Variante 2. Die Summe der Produkt-Quersummen ist jedoch #\n\
# durch 7 zu dividieren. Der verbleibende Rest wird vom Divisor (7)  #\n\
# subtrahiert. Das Ergebnis ist die Prüfziffer. Verbleibt nach der   #\n\
# Division kein Rest, ist die Prüfziffer = 0                         #\n\
#                                                                    #\n\
# Ausnahme:                                                          #\n\
# Ist nach linksbündiger Auffüllung mit Nullen auf 10 Stellen die 3. #\n\
# Stelle der Kontonummer = 9 (Sachkonten), so erfolgt die Berechnung #\n\
# gemäß der Ausnahme in Methode 51 mit den gleichen Ergebnissen und  #\n\
# Testkontonummern.                                                  #\n\
######################################################################\n";

      case 74: return "\
######################################################################\n\
#    Berechnung nach der Methode 74 (geändert zum 4.6.2007)          #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2 ff.                           #\n\
# Die Kontonummer (2- bis 10-stellig) ist durch linksbündige         #\n\
# Nullenauffüllung 10-stellig darzustellen. Die 10. Stelle ist       #\n\
# per Definition die Prüfziffer. Die für die Berechnung              #\n\
# relevanten Stellen werden von rechts nach links mit den Ziffern    #\n\
# 2, 1, 2, 1, 2 ff. multipliziert. Die weitere Berechnung und die    #\n\
# Ergebnisse entsprechen dem Verfahren 00.                           #\n\
#                                                                    #\n\
# Ausnahme:                                                          #\n\
# Bei 6-stelligen Kontonummern ist folgende Besonderheit zu          #\n\
# beachten.                                                          #\n\
# Ergibt die erste Berechnung der Prüfziffer nach dem Verfahren 00   #\n\
# einen Prüfziffernfehler, so ist eine weitere Berechnung            #\n\
# vorzunehmen. Hierbei ist die Summe der Produkte auf die nächste    #\n\
# Halbdekade hochzurechnen. Die Differenz ist die Prüfziffer.        #\n\
######################################################################\n";

      case 75: return "\
######################################################################\n\
#              Berechnung nach der Methode 75                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2.                              #\n\
# Die Kontonummer (6-, 7- oder 9-stellig) ist durch linksbündige     #\n\
# Nullenauffüllung 10-stellig darzustellen. Die für die Berech-      #\n\
# nung relevante 5-stellige Stammnummer wird von links nach          #\n\
# rechts mit den Ziffern 2, 1, 2, 1, 2 multipliziert. Die weitere    #\n\
# Berechnung und die Ergebnisse entsprechen dem Verfahren 00.        #\n\
# Bei 6- und 7-stelligen Kontonummern befindet sich die für die      #\n\
# Berechnung relevante Stammnummer in den Stellen 5 bis 9, die       #\n\
# Prüfziffer in Stelle 10 der Kontonummer.                           #\n\
# Bei 9-stelligen Kontonummern befindet sich die für die Berech-     #\n\
# nung relevante Stammnummer in den Stellen 2 bis 6, die Prüf-       #\n\
# ziffer in der 7. Stelle der Kontonummer. Ist die erste Stelle      #\n\
# der 9-stelligen Kontonummer = 9 (2. Stelle der \"gedachten\"         #\n\
# Kontonummer), so befindet sich die für die Berechnung relevante    #\n\
# Stammnummer in den Stellen 3 bis 7, die Prüfziffer in der 8.       #\n\
# Stelle der Kontonummer.                                            #\n\
######################################################################\n";

      case 76: return "\
######################################################################\n\
#              Berechnung nach der Methode 76                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5 ff.                              #\n\
# Die einzelnen Stellen der für die Berechnung der Prüfziffer        #\n\
# relevanten 5-, 6- oder 7-stelligen Stammnummer sind von rechts     #\n\
# nach links mit den Ziffern 2, 3, 4, 5 ff. zu multiplizieren.       #\n\
# Die jeweiligen Produkte werden addiert. Die Summe ist durch 11     #\n\
# zu dividieren. Der verbleibende Rest ist die Prüfziffer. Ist       #\n\
# der Rest 10, kann die Kontonummer nicht verwendet werden.          #\n\
# Darstellung der Kontonummer: ASSSSSSPUU.                           #\n\
# Ist die Unterkontonummer \"00\", kann es vorkommen, daß sie auf      #\n\
# Zahlungsbelegen nicht angegeben ist. Die Prüfziffer ist dann       #\n\
# an die 10. Stelle gerückt.                                         #\n\
# Die Kontoart (1. Stelle) kann den Wert 0, 4, 6, 7, 8 oder 9 haben. #\n\
######################################################################\n";

      case 77: return "\
######################################################################\n\
#              Berechnung nach der Methode 77                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 1, 2, 3, 4, 5.                              #\n\
# Die Kontonummer ist 10-stellig. Die für die Berechnung             #\n\
# relevanten Stellen 6 bis 10 werden von rechts nach links mit       #\n\
# den Ziffern 1, 2, 3, 4, 5 multipliziert. Die Produkte werden       #\n\
# addiert. Die Summe ist durch 11 zu dividieren. Verbleibt nach      #\n\
# der Division der Summe durch 11 ein Rest, ist folgende neue        #\n\
# Berechnung durchzuführen:                                          #\n\
# Modulus 11, Gewichtung 5, 4, 3, 4, 5.                              #\n\
# Ergibt sich bei der erneuten Berechnung wiederum ein Rest,         #\n\
# dann ist die Kontonummer falsch.                                   #\n\
######################################################################\n";

      case 78: return "\
######################################################################\n\
#              Berechnung nach der Methode 78                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2.                  #\n\
# Die Berechnung erfolgt wie bei Verfahren 00. Ausnahme:             #\n\
# 8-stellige Kontonummern sind nicht prüfbar, da diese Nummern       #\n\
# keine Prüfziffer enthalten.                                        #\n\
######################################################################\n";

      case 79: return "\
######################################################################\n\
#              Berechnung nach der Methode 79                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2 ff.                     #\n\
# Die Kontonummer ist 10-stellig. Die Berechnung und Ergebnisse      #\n\
# entsprechen dem Verfahren 00. Es ist jedoch zu beachten, dass      #\n\
# die Berechnung vom Wert der 1. Stelle der Kontonummer abhängig     #\n\
# ist.                                                               #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Die 1. Stelle der Kontonummer hat die Ziffer 3, 4, 5, 6, 7         #\n\
# oder 8                                                             #\n\
# Die für die Berechnung relevanten Stellen der Kontonummer          #\n\
# befinden sich in den Stellen 1 bis 9. Die 10. Stelle ist per       #\n\
# Definition die Prüfziffer.                                         #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Die 1. Stelle der Kontonummer hat die Ziffer 1, 2 oder 9           #\n\
# Die für die Berechnung relevanten Stellen der Kontonummer          #\n\
# befinden sich in den Stellen 1 bis 8. Die 9. Stelle ist die        #\n\
# Prüfziffer der 10-stelligen Kontonummer.                           #\n\
#                                                                    #\n\
# Kontonummern, die in der 1. Stelle eine 0 haben,                   #\n\
# wurden nicht vergeben und gelten deshalb als falsch.               #\n\
######################################################################\n";

      case 80: return "\
######################################################################\n\
#    Berechnung nach der Methode 80 (geändert zum 8.6.2004)          #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2.                              #\n\
# Die Berechnung und die möglichen Ergebnisse entsprechen dem        #\n\
# Verfahren 00; es ist jedoch  zu beachten, daß nur die Stellen      #\n\
# 5 bis 9 in das Prüfziffernberechnungsverfahren einbezogen          #\n\
# werden.                                                            #\n\
# Führt die Berechnung zu einem Prüfziffernfehler, so ist die        #\n\
# Berechnung nach Variante 2 vorzunehmen. Das Berechnungsverfahren   #\n\
# entspricht Variante 1. Die Summe der Produkte ist jedoch durch     #\n\
# 7 zu dividieren. Der verbleibende Rest wird vom Divisor (7)        #\n\
# subtrahiert. Das Ergebnis ist die Prüfziffer. Verbleibt nach       #\n\
# der Division kein Rest, ist die Prüfziffer 0.                      #\n\
#                                                                    #\n\
# Ausnahme:                                                          #\n\
# Ist nach linksbündiger Auffüllung mit Nullen auf 10 Stellen die    #\n\
# 3. Stelle der Kontonummer = 9 (Sachkonten), so erfolgt die         #\n\
# Berechnung gemäß der Ausnahme in Methode 51 mit den gleichen       #\n\
# Ergebnissen und Testkontonummern.                                  #\n\
######################################################################\n";

      case 81: return "\
######################################################################\n\
#    Berechnung nach der Methode 81  (geändert zum 6.9.2004)         #\n\
######################################################################\n\
#                                                                    #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7                            #\n\
# Die Kontonummer ist durch linksbündige Nullenauffüllung stellig    #\n\
# darzustellen. Die 10. Stelle ist per Definition Prüfziffer. Die    #\n\
# für die Berechnung relevanten Stellen werden von rechts nach       #\n\
# links mit den Ziffern 2, 3, 4, 5, 6, multipliziert. Die weitere    #\n\
# Berechnung und die möglichen Ergebnisse entsprechen dem Verfahren  #\n\
# 32.                                                                #\n\
#                                                                    #\n\
# Ausnahme:                                                          #\n\
# Ist nach linksbündiger Auffüllung mit Nullen auf 10 Stellen 3.     #\n\
# Stelle der Kontonummer = 9 (Sachkonten), so erfolgt Berechnung     #\n\
# gemäß der Ausnahme in Methode 51 mit gleichen Ergebnissen und      #\n\
# Testkontonummern.                                                  #\n\
######################################################################\n";

      case 82: return "\
######################################################################\n\
#              Berechnung nach der Methode 82                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7.                           #\n\
# Sind die 3. und 4. Stelle der Kontonummer = 99, so erfolgt die     #\n\
# Berechnung nach Verfahren 10, sonst nach Verfahren 33.             #\n\
######################################################################\n";

      case 83: return "\
######################################################################\n\
#              Berechnung nach der Methode 83                        #\n\
######################################################################\n\
# 1. Kundenkonten                                                    #\n\
# A. Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7                         #\n\
# B. Modulus 11, Gewichtung 2, 3, 4, 5, 6                            #\n\
# C. Modulus  7, Gewichtung 2, 3, 4, 5, 6                            #\n\
# Gemeinsame Anmerkungen für die Berechnungsverfahren:               #\n\
# Die Kontonummer ist immer 10-stellig. Die für die Berechnung       #\n\
# relevante Kundennummer (K) befindet sich bei der Methode A in      #\n\
# den Stellen 4 bis 9 der Kontonummer und bei den Methoden B + C     #\n\
# in den Stellen 5 - 9, die Prüfziffer in Stelle 10 der              #\n\
# Kontonummer.                                                       #\n\
#                                                                    #\n\
# Ergibt die erste Berechnung der Prüfziffer nach dem Verfahren A    #\n\
# einen Prüfzifferfehler, so sind weitere Berechnungen mit den       #\n\
# anderen Methoden vorzunehmen. Kontonummern, die nach               #\n\
# Durchführung aller 3 Berechnungsmethoden nicht zu einem            #\n\
# richtigen Ergebnis führen, sind nicht prüfbar.                     #\n\
#                                                                    #\n\
# Methode A:                                                         #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7                            #\n\
# Die Berechnung und möglichen Ergebnisse entsprechen                #\n\
# dem Verfahren 32.                                                  #\n\
#                                                                    #\n\
# Methode B:                                                         #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6                               #\n\
# Die Berechnung und möglichen Ergebnisse entsprechen                #\n\
# dem Verfahren 33.                                                  #\n\
#                                                                    #\n\
# Methode C:                                                         #\n\
# Kontonummern, die bis zur Methode C gelangen und in der 10.        #\n\
# Stelle eine 7, 8 oder 9 haben, sind ungültig. Modulus 7,           #\n\
# Gewichtung 2, 3, 4, 5, 6 Das Berechnungsverfahren entspricht       #\n\
# Methode B. Die Summe der Produkte ist jedoch durch 7 zu            #\n\
# dividieren. Der verbleibende Rest wird vom Divisor (7)             #\n\
# subtrahiert. Das Ergebnis ist die Prüfziffer. Verbleibt kein       #\n\
# Rest, ist die Prüfziffer 0.                                        #\n\
#                                                                    #\n\
# 2. Sachkonten                                                      #\n\
# Berechnungsmethode:                                                #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8                         #\n\
# Die Sachkontonummer ist immer 10-stellig. Die für die Berechnung   #\n\
# relevante  Sachkontontenstammnummer (S) befindet sich in den       #\n\
# Stellen 3 bis 9 der Kontonummer, wobei die 3. und 4. Stelle        #\n\
# immer jeweils 9 sein müssen; die Prüfziffer ist in Stelle 10 der   #\n\
# Sachkontonummer. Führt die Berechnung nicht zu einem richtigen     #\n\
# Ergebnis, ist die Nummer nicht prüfbar.                            #\n\
# Berechnung:                                                        #\n\
# Die einzelnen Stellen der Sachkontonummern sind von rechts nach    #\n\
# links mit den Ziffern 2, 3, 4, 5, 6, 7, 8 zu multiplizieren. Die   #\n\
# jeweiligen Produkte werden addiert. Die Summe ist durch 11 zu      #\n\
# dividieren. Der verbleibende Rest wird vom Divisor (11)            #\n\
# subtrahiert. Das Ergebnis ist die Prüfziffer. Verbleibt nach der   #\n\
# Division durch die 11 kein Rest, ist die Prüfziffer \"0\". Das       #\n\
# Rechenergebnis \"10\" ist nicht verwendbar und muss auf eine         #\n\
# Stelle reduziert werden. Die rechte Stelle Null findet als         #\n\
# Prüfziffer Verwendung.                                             #\n\
######################################################################\n";

      case 84: return "\
######################################################################\n\
#          Berechnung nach der Methode 84 (geändert zum 3.6.13)      #\n\
######################################################################\n\
# Die Kontonummer ist durch linksbündige Nullenauffüllung            #\n\
# 10-stellig darzustellen. Die 10. Stelle ist per Definition die     #\n\
# Prüfziffer.                                                        #\n\
#                                                                    #\n\
# Es ist zu beachten, dass nur die Stellen 5 bis 9 in das            #\n\
# Prüfzifferberechnungsverfahren einbezogen werden.                  #                                                                   #\n\
#                                                                    #\n\
# Methode A                                                          #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6                               #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen dem             #\n\
# Verfahren 06.                                                      #\n\
#                                                                    #\n\
# Stelle-Nr.         1 2 3 4 5 6 7 8 9 10                            #\n\
# Kontonummer        X X X X K K K K K  P                            #\n\
# Gewichtung                 6 5 4 3 2                               #\n\
#                                                                    #\n\
# Führt die Berechnung nach Variante 1 zu einem Prüfziffer-          #\n\
# fehler, ist die Berechnung nach Variante 2 vorzunehmen.            #\n\
#                                                                    #\n\
# Methode B                                                          #\n\
# Modulus 7, Gewichtung 2, 3, 4, 5, 6                                #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen dem             #\n\
# Verfahren 06. Dabei ist zu beachten, daß als Divisor 7 zu          #\n\
# verwenden ist.                                                     #\n\
#                                                                    #\n\
# Stelle-Nr.         1 2 3 4 5 6 7 8 9 10                            #\n\
# Kontonummer        X X X X K K K K K  P                            #\n\
# Gewichtung                 6 5 4 3 2                               #\n\
#                                                                    #\n\
#                                                                    #\n\
# Methode C                                                          #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2                               #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen dem             #\n\
# Verfahren 06.                                                      #\n\
#                                                                    #\n\
# Stelle-Nr.         1 2 3 4 5 6 7 8 9 10                            #\n\
# Kontonummer        X X X X K K K K K  P                            #\n\
# Gewichtung                 2 1 2 1 2                               #\n\
#                                                                    #\n\
# Ausnahme:                                                          #\n\
# Ist nach linksbündiger Auffüllung mit Nullen auf 10 Stellen die    #\n\
# 3. Stelle der Kontonummer = 9 (Sachkonten), so erfolgt die         #\n\
# Berechnung gemäß der Ausnahme in Methode 51 mit den gleichen       #\n\
# Ergebnissen und Testkontonummern.                                  #\n\
######################################################################\n";

      case 85: return "\
######################################################################\n\
#              Berechnung nach der Methode 85                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6.                              #\n\
# Wie Verfahren 83, jedoch folgende Ausnahme:                        #\n\
# Sind die 3. und 4. Stelle der Kontonummer = 99, so ist folgende    #\n\
# Prüfziffernberechnung maßgebend:                                   #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8.                        #\n\
# Die für die Berechnung relevanten Stellen 3 bis 9 der Kontonr      #\n\
# werden von rechts nach links mit den Ziffern 2, 3, 4, 5, 6, 7, 8   #\n\
# multipliziert. Die weitere Berechnung und möglichen Ergebnisse     #\n\
# entsprechen dem Verfahren 02.                                      #\n\
######################################################################\n";

      case 86: return "\
######################################################################\n\
#    Berechnung nach der Methode 86 (geändert zum 6.9.2004)          #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1                            #\n\
#                                                                    #\n\
# Methode A                                                          #\n\
# Die Kontonummer ist durch linksbündige Nullenauffüllung 10-        #\n\
# stellig darzustellen. Die Berechnung und die möglichen             #\n\
# Ergebnisse entsprechen dem Verfahren 00; es ist jedoch zu          #\n\
# beachten, dass nur die Stellen 4 bis 9 in das                      #\n\
# Prüfzifferberechnungsverfahren einbezogen werden. Die Stelle       #\n\
# 10 der Kontonummer ist die Prüfziffer.                             #\n\
#                                                                    #\n\
# Führt die Berechnung nach Methode A zu einem Prüfziffer-           #\n\
# fehler, so ist die Berechnung nach Methode B vorzunehmen.          #\n\
#                                                                    #\n\
# Methode B                                                          #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7                            #\n\
# Die Kontonummer ist durch linksbündige Nullenauffüllung 10-        #\n\
# stellig darzustellen. Die Stellen 4 bis 9 der Kontonummer          #\n\
# werden von rechts nach links mit den Ziffern 2, 3, 4, 5, 6, 7      #\n\
# multipliziert. Die weitere Berechnung und die möglichen            #\n\
# Ergebnisse entsprechen dem Verfahren 32. Die Stelle 10 ist die     #\n\
# Prüfziffer.                                                        #\n\
#                                                                    #\n\
# Ausnahme:                                                          #\n\
# Ist nach linksbündiger Auffüllung mit Nullen auf 10 Stellen        #\n\
# die 3. Stelle der Kontonummer = 9 (Sachkonten), so erfolgt die     #\n\
# Berechnung gemäß der Ausnahme in Methode 51 mit den gleichen       #\n\
# Ergebnissen und Testkontonummern.                                  #\n\
######################################################################\n";

      case 87: return "\
######################################################################\n\
#          Berechnung nach der Methode 87 (geändert zum 6.9.04)      #\n\
######################################################################\n\
# Ausnahme:                                                          #\n\
# Ist nach linksbündiger Auffüllung mit Nullen auf 10 Stellen die    #\n\
# 3. Stelle der Kontonummer = 9 (Sachkonten), so erfolgt die         #\n\
# Berechnung gemäß der Ausnahme in Methode 51 mit den                #\n\
# gleichen Ergebnissen und Testkontonummern.                         #\n\
#                                                                    #\n\
# Methode A:                                                         #\n\
# Vorgegebener Pascalcode, anzuwenden auf Stellen 5 bis 9            #\n\
# von links der Kontonummer, Prüfziffer in Stelle 10.                #\n\
# Der vorgegebener Pseudocode (pascal-ähnlich) wurde nach C          #\n\
# umgeschrieben. Eine Beschreibung des Berechnungsverfahrens findet  #\n\
# sich in der Datei pz<mmyy>.pdf (z.B. pz0602.pdf) der  Deutschen    #\n\
# Bundesbank.                                                        #\n\
#                                                                    #\n\
# Methode B:                                                         #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6                               #\n\
# Die für die Berechnung relevanten Stellen werden von rechts        #\n\
# nach links mit den Ziffern 2, 3, 4, 5, 6 multipliziert. Die        #\n\
# weitere Berechnung und die möglichen Ergebnisse entsprechen dem    #\n\
# Verfahren 33.                                                      #\n\
# Führt die Berechnung nach Methode B wiederum zu einem              #\n\
# Prüfzifferfehlen, ist eine weitere Berechnung nach Methode C       #\n\
# vorzunehmen.                                                       #\n\
#                                                                    #\n\
# Methode C:                                                         #\n\
# Modulus 7, Gewichtung 2, 3, 4, 5, 6                                #\n\
# Die Stellen 5 bis 9 der Kontonummer werden von rechts nach         #\n\
# links mit den Gewichten multipliziert. Die jeweiligen Produkte     #\n\
# werden addiert. Die Summe ist durch 7 zu dividieren. Der           #\n\
# verbleibende Rest wird vom Divisor (7) subtrahiert. Das            #\n\
# Ergebnis ist die Prüfziffer. Verbleibt nach der Division kein      #\n\
# Rest, ist die Prüfziffer = 0.                                      #\n\
######################################################################\n";

      case 88: return "\
######################################################################\n\
#              Berechnung nach der Methode 88                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7.                           #\n\
# Die Stellen 4 bis 9 werden von rechts nach links mit den           #\n\
# Gewichten 2, 3, 4, 5, 6, 7 multipliziert. Die weitere Berechnung   #\n\
# entspricht dem Verfahren 06.                                       #\n\
# Ausnahme: Ist die 3. Stelle der Kontonummer = 9, so werden         #\n\
# die Stellen 3 bis 9 von rechts nach links mit den Gewichten        #\n\
# 2, 3, 4, 5, 6, 7, 8 multipliziert.                                 #\n\
######################################################################\n";

      case 89: return "\
######################################################################\n\
#              Berechnung nach der Methode 89                        #\n\
######################################################################\n\
# 8- und 9-stellige Kontonummern sind mit dem                        #\n\
# Berechnungsverfahren 10 zu prüfen.                                 #\n\
#                                                                    #\n\
# 7-stellige Kontonummern sind wie folgt zu prüfen:                  #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7                            #\n\
# Die Kontonummer ist durch linksbündige Nullenauffüllung            #\n\
# 10-stellig darzustellen. Die für die Berechnung relevante          #\n\
# 6-stellige Stammnummer (x) befindet sich in den Stellen 4 bis      #\n\
# 9, die Prüfziffer in Stelle 10 der Kontonummer. Die einzelnen      #\n\
# Stellen der Stammnummer sind von rechts nach links mit den         #\n\
# Ziffern 2, 3, 4, 5, 6, 7 zu multiplizieren. Die jeweiligen         #\n\
# Produkte werden addiert, nachdem jeweils aus den 2- stelligen      #\n\
# Produkten Quersummen gebildet wurden. Die Summe ist durch 11       #\n\
# zu dividieren. Die weiteren Berechnungen und Ergebnisse            #\n\
# entsprechen dem Verfahren 06.                                      #\n\
#                                                                    #\n\
# 1- bis 6- und 10-stellige Kontonummern sind nicht zu               #\n\
# prüfen, da diese keine Prüfziffer enthalten.                       #\n\
# Testkontonummern: 1098506, 32028008, 218433000                     #\n\
######################################################################\n";

      case 90: return "\
######################################################################\n\
#      Berechnung nach der Methode 90 (geändert zum 6.6.2005)        #\n\
######################################################################\n\
# 1. Kundenkonten                                                    #\n\
# A. Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7. -> Methode 32          #\n\
# B. Modulus 11, Gewichtung 2, 3, 4, 5, 6.    -> Methode 33          #\n\
# C. Modulus  7, Gewichtung 2, 3, 4, 5, 6.    -> Methode 33 mod7     #\n\
# D. Modulus  9, Gewichtung 2, 3, 4, 5, 6.    -> Methode 33 mod9     #\n\
# E. Modulus 10, Gewichtung 2, 1, 2, 1, 2.    -> Methode 33 mod10    #\n\
#                                                                    #\n\
# Die Kontonummer ist immer 10-stellig. Die für die Berechnung       #\n\
# relevante Kundennummer befindet sich bei der Methode A in den      #\n\
# Stellen 4 bis 9 der Kontonummer und bei den Methoden B - E in      #\n\
# den Stellen 5 bis 9, die Prüfziffer in Stelle 10.                  #\n\
#                                                                    #\n\
# Ergibt die erste Berechnung der Prüfziffer nach dem Verfahren A    #\n\
# einen Prüfziffernfehler, so sind weitere Berechnungen mit den      #\n\
# anderen Methoden vorzunehmen.                                      #\n\
# Die Methode A enstpricht Verfahren 32. Die Methoden B - E          #\n\
# entsprechen Verfahren 33, jedoch mit Divisoren 11, 7, 9 und 10.    #\n\
#                                                                    #\n\
# Ausnahme: Ist nach linksbündigem Auffüllen mit Nullen auf 10       #\n\
# Stellen die 3. Stelle der Kontonummer = 9 (Sachkonten) befindet    #\n\
# sich die für die Berechnung relevante Sachkontonummer (S) in       #\n\
# den Stellen 3 bis 9. Diese Kontonummern sind ausschließlich        #\n\
# nach Methode F zu prüfen.                                          #\n\
#                                                                    #\n\
# 2. Sachkonten -> Methode 32 (modifiziert)                          #\n\
# F. Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8.                     #\n\
# Die 3. Stelle ist 9, die für die Berechnung relevanten  Stellen    #\n\
# befinden sich in den Stellen 3 bis 9.                              #\n\
######################################################################\n";

      case 91: return "\
######################################################################\n\
#   Berechnung nach der Methode 91 (geändert zum 8.12.03)            #\n\
######################################################################\n\
# 1. Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7                         #\n\
# 2. Modulus 11, Gewichtung 7, 6, 5, 4, 3, 2                         #\n\
# 3. Modulus 11, Gewichtung 2, 3, 4, 0, 5, 6, 7, 8, 9, A (A = 10)    #\n\
# 4. Modulus 11, Gewichtung 2, 4, 8, 5, 10, 9                        #\n\
#                                                                    #\n\
# Gemeinsame Hinweise für die Berechnungsvarianten 1 bis 4:          #\n\
#                                                                    #\n\
# Die Kontonummer ist immer 10-stellig. Die einzelnen Stellen        #\n\
# der Kontonummer werden von links nach rechts von 1 bis 10          #\n\
# durchnummeriert. Die Stelle 7 der Kontonummer ist die              #\n\
# Prüfziffer. Die für die Berechnung relevanten Kundennummern        #\n\
# (K) sind von rechts nach links mit den jeweiligen Gewichten zu     #\n\
# multiplizieren. Die restliche Berechnung und möglichen             #\n\
# Ergebnisse entsprechen dem Verfahren 06.                           #\n\
#                                                                    #\n\
# Ergibt die Berechnung nach der ersten beschriebenen Variante       #\n\
# einen Prüfzifferfehler, so sind in der angegebenen Reihenfolge     #\n\
# weitere Berechnungen mit den anderen Varianten                     #\n\
# vorzunehmen, bis die Berechnung keinen Prüfzifferfehler mehr       #\n\
# ergibt. Kontonummern, die endgültig nicht zu einem richtigen       #\n\
# Ergebnis führen, sind nicht prüfbar.                               #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7                            #\n\
# Die Stellen 8 bis 10 werden nicht in die Berechnung                #\n\
# einbezogen.                                                        #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 11, Gewichtung 7, 6, 5, 4, 3, 2                            #\n\
# Die Stellen 8 bis 10 werden nicht in die Berechnung                #\n\
# einbezogen.                                                        #\n\
#                                                                    #\n\
# Variante 3:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 0, 5, 6, 7, 8, 9, A (A = 10)       #\n\
# Die Stellen 1 bis 10 werden in die Berechnung einbezogen.          #\n\
#                                                                    #\n\
# Variante 4:                                                        #\n\
# Modulus 11, Gewichtung 2, 4, 8, 5, A, 9 (A = 10)                   #\n\
# Die Stellen 8 bis 10 werden nicht in die Berechnung einbezogen.    #\n\
######################################################################\n";

      case 92: return "\
######################################################################\n\
#              Berechnung nach der Methode 92                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 3, 7, 1, 3, 7, 1.                           #\n\
# Die Berechnung erfolgt wie bei Verfahren 01, jedoch werden nur     #\n\
# die Stellen 4 bis 9 einbezogen. Stelle 10 ist die Prüfziffer.      #\n\
######################################################################\n";

      case 93: return "\
######################################################################\n\
#              Berechnung nach der Methode 93                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6.                              #\n\
# Die für die Berechnung relevante Kundennummer befindet sich        #\n\
# entweder                                                           #\n\
# a) in den Stellen 1 bis 5, die Prüfziffer in Stelle  6,            #\n\
# b) in den Stellen 5 bis 9, die Prüfziffer in Stelle 10.            #\n\
# Die 2-stellige Unternummer und die 2-stellige Kontoartnummer       #\n\
# werden nicht in die Berechnung einbezogen. Sie befinden sich im    #\n\
# Fall a) an Stelle 7 bis 10. Im Fall b) befinden Sie sich an        #\n\
# Stelle 1 bis 4 und müssen \"0000\" lauten.                           #\n\
# Die 5-stellige Kundennummer wird von rechts nach links mit den     #\n\
# Gewichten multipliziert. Die weitere Berechnung und die            #\n\
# möglichen Ergebnisse entsprechen dem Verfahren 06.                 #\n\
# Führt die Berechnung zu einem Prüfziffernfehler, so ist die        #\n\
# Berechnung nach Variante 2 vorzunehmen. Das Berechnungsverfahren   #\n\
# entspricht Variante 1. Die Summe der Produkte ist jedoch durch     #\n\
# 7 zu dividieren. Der verbleibende Rest wird vom Divisor (7)        #\n\
# subtrahiert. Das Ergebnis ist die Prüfziffer.                      #\n\
######################################################################\n";

      case 94: return "\
######################################################################\n\
#              Berechnung nach der Methode 94                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 1, 2, 1, 2, 1, 2, 1, 2, 1.                  #\n\
# Die Stellen 1 bis 9 der Kontonummer sind von rechts nach links     #\n\
# mit den Gewichten zu multiplizieren. Die weitere Berechnung        #\n\
# erfolgt wie bei Verfahren 00.                                      #\n\
######################################################################\n";

      case 95: return "\
######################################################################\n\
#      Berechnung nach der Methode 95 (geändert zum 9.9.2013)        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 2, 3, 4                   #\n\
# Die Berechnung erfolgt wie bei Verfahren 06.                       #\n\
# Ausnahmen:                                                         #\n\
# Kontonr.: 0000000001 bis 0001999999                                #\n\
# Kontonr.: 0009000000 bis 0025999999                                #\n\
# Kontonr.: 0396000000 bis 0499999999                                #\n\
# Kontonr.: 0700000000 bis 0799999999                                #\n\
# Kontonr.: 0910000000 bis 0989999999 (ab 9.9.2013)                  #\n\
# Für diese Kontonummernkreise ist keine Prüfzifferberechnung        #\n\
# möglich. Sie sind als richtig anzusehen.                           #\n\
######################################################################\n";

      case 96: return "\
######################################################################\n\
#              Berechnung nach der Methode 96                        #\n\
######################################################################\n\
# A. Modulus 11, Gewichtung 2,3,4,5,6,7,8,9,1                        #\n\
# B. Modulus 10, Gewichtung 2,1,2,1,2,1,2,1,2                        #\n\
# Die Prüfziffernberechnung ist nach Kennziffer 19 durchzuführen.    #\n\
# Führt die Berechnung zu einem Fehler, so ist sie nach Kennziffer   #\n\
# 00 durchzuführen. Führen beide Varianten zu einem Fehler, so       #\n\
# gelten Kontonummern zwischen 0001300000 und 0099399999 als         #\n\
# richtig.                                                           #\n\
######################################################################\n";

      case 97: return "\
######################################################################\n\
#              Berechnung nach der Methode 97                        #\n\
######################################################################\n\
#  Modulus 11:                                                       #\n\
#  Die Kontonummer (5, 6, 7, 8, 9 o. 10-stellig) ist durch links-    #\n\
#  bündige Nullenauffüllung 10-stellig darzustellen. Danach ist die  #\n\
#  10. Stelle die Prüfziffer.                                        #\n\
#                                                                    #\n\
#  Die Kontonummer ist unter Weglassung der Prüfziffer (= Wert X)    #\n\
#  durch 11 zu teilen. Das Ergebnis der Division ist ohne die        #\n\
#  Nachkomma-Stellen mit 11 zu multiplizieren. Das Produkt ist vom   #\n\
#  'Wert X' zu subtrahieren.                                         #\n\
#                                                                    #\n\
#  Ist das Ergebnis < 10, so entspricht das Ergebnis der Prüfziffer. #\n\
#  Ist das Ergebnis = 10, so ist die Prüfziffer = 0                  #\n\
######################################################################\n";

      case 98: return "\
######################################################################\n\
#              Berechnung nach der Methode 98                        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 3, 1, 7, 3, 1, 7, 3                         #\n\
# Die Kontonummer ist 10-stellig. Die Berechnung erfolgt wie         #\n\
# bei Verfahren 01. Es ist jedoch zu beachten, dass nur die          #\n\
# Stellen 3 bis 9 in die Prüfzifferberechnung einbezogen             #\n\
# werden. Die Stelle 10 der Kontonummer ist die Prüfziffer.          #\n\
# Führt die Berechnung zu einem falschen Ergebnis, so ist            #\n\
# alternativ das Verfahren 32 anzuwenden.                            #\n\
######################################################################\n";

      case 99: return "\
######################################################################\n\
#              Berechnung nach der Methode 99                        #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 2, 3, 4                   #\n\
# Die Berechnung erfolgt wie bei Verfahren 06.                       #\n\
# Ausnahmen: Kontonr.: 0396000000 bis 0499999999                     #\n\
# Für diese Kontonummern ist keine Prüfzifferberechnung              #\n\
# möglich.  Sie sind als richtig anzusehen.                          #\n\
######################################################################\n";

      case 100: return "\
######################################################################\n\
#              Berechnung nach der Methode A0                       #\n\
######################################################################\n\
#  Modulus 11, Gewichtung 2, 4, 8, 5, 10, 0, 0, 0, 0 Die             #\n\
#  Kontonummer ist einschließlich der Prüfziffer 10- stellig,        #\n\
#  ggf. ist die Kontonummer für die Prüfzifferberechnung durch       #\n\
#  linksbündige Auffüllung mit Nullen 10-stellig darzustellen.       #\n\
#  Die Stelle 10 ist die Prüfziffer. Die einzelnen Stellen der       #\n\
#  Kontonummer (ohne Prüfziffer) sind von rechts nach links mit      #\n\
#  dem zugehörigen Gewicht (2, 4, 8, 5, 10, 0, 0, 0, 0) zu           #\n\
#  multiplizieren. Die Produkte werden addiert. Das Ergebnis ist     #\n\
#  durch 11 zu dividieren. Ergibt sich nach der Division ein         #\n\
#  Rest von 0 oder 1, so ist die Prüfziffer 0. Ansonsten ist der     #\n\
#  Rest vom Divisor (11) zu subtrahieren. Das Ergebnis ist die       #\n\
#  Prüfziffer.                                                       #\n\
#  Ausnahme: 3-stellige Kontonummern bzw. Kontonummern, deren        #\n\
#  Stellen 1 bis 7 = 0 sind, enthalten keine Prüfziffer und sind     #\n\
#  als richtig anzusehen.                                            #\n\
######################################################################\n";

      case 101: return "\
######################################################################\n\
#    Berechnung nach der Methode A1 (geändert zum 9.6.2003)          #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 0, 0.                  #\n\
#                                                                    #\n\
# Die Kontonummern sind 8- oder 10-stellig. Kontonummern (ohne       #\n\
# führende Nullen  gezählt) mit 9 oder weniger als 8 Stellen sind    #\n\
# falsch. 8-stellige Kontonummern sind für die Prüfzifferberechnung  #\n\
# durch linksbündige Auffüllung mit Nullen 10-stellig darzustellen.  #\n\
# Die Berechnung erfolgt wie beim Verfahren 00.                      #\n\
######################################################################\n";

      case 102: return "\
######################################################################\n\
#              Berechnung nach der Methode A2                       #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 2, 3, 4                   #\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1: Gewichtung und Berechnung erfolgen nach der Methode 00.#\n\
# Führt die Berechnung nach Variante 1 zu einem Prüfzifferfehler,    #\n\
# so ist nach Variante 2 zu prüfen.                                  #\n\
#                                                                    #\n\
# Variante 2: Gewichtung und Berechnung erfolgen nach der Methode 04.#\n\
######################################################################\n";

      case 103: return "\
######################################################################\n\
#              Berechnung nach der Methode A3                       #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 10                  #\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1: Gewichtung und Berechnung erfolgen nach der Methode 00.#\n\
# Führt die Berechnung nach Variante 1 zu einem Prüfzifferfehler,    #\n\
# so ist nach Variante 2 zu prüfen.                                  #\n\
#                                                                    #\n\
# Variante 2: Gewichtung und Berechnung erfolgen nach der Methode 10.#\n\
######################################################################\n";

      case 104: return "\
######################################################################\n\
#              Berechnung nach der Methode A4                       #\n\
######################################################################\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 0, 0, 0                   #\n\
# Modulus 7,  Gewichtung 2, 3, 4, 5, 6, 7, 0, 0, 0                   #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 0, 0, 0, 0                   #\n\
# Modulus 7,  Gewichtung 2, 3, 4, 5, 6, 0, 0, 0, 0                   #\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen. Zur    #\n\
# Prüfung einer Kontonummer sind die folgenden Varianten zu          #\n\
# rechnen. Dabei ist zu beachten, dass Kontonummern mit der          #\n\
# Ziffernfolge 99 an den Stellen 3 und 4 (XX99XXXXXX) nur nach       #\n\
# Variante 3 und ggf. 4 zu prüfen sind. Alle anderen Kontonummern    #\n\
# sind nacheinander nach den Varianten 1, ggf. 2 und ggf. 4 zu       #\n\
# prüfen.                                                            #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 0, 0, 0                   #\n\
#                                                                    #\n\
# In die Prüfzifferberechnung werden nur die Stellen 4 bis 9         #\n\
# einbezogen. Die Stelle 10 ist die Prüfziffer. Die weitere          #\n\
# Berechnung erfolgt nach dem Verfahren 06.                          #\n\
#                                                                    #\n\
# Führt die Berechnung zu einem Fehler, ist nach Variante 2 zu       #\n\
# prüfen.                                                            #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 7, Gewichtung 2, 3, 4, 5, 6, 7, 0, 0, 0                    #\n\
#                                                                    #\n\
# Die Stellen 4 bis 9 der Kontonummer werden von rechts nach links   #\n\
# mit den Gewichten multipliziert. Die jeweiligen Produkte werden    #\n\
# addiert. Die Summe ist durch 7 zu dividieren. Der verbleibende     #\n\
# Rest wird vom Divisor (7) subtrahiert. Das Ergebnis ist die        #\n\
# Prüfziffer (Stelle 10). Verbleibt nach der Division kein Rest,     #\n\
# ist die Prüfziffer 0.                                              #\n\
#                                                                    #\n\
# Führt die Berechnung zu einem Fehler, ist nach Variante 4 zu       #\n\
# prüfen.                                                            #\n\
#                                                                    #\n\
# Variante 3:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 0, 0, 0, 0                   #\n\
#                                                                    #\n\
# In die Prüfzifferberechnung werden nur die Stellen 5 bis 9         #\n\
# einbezogen. Die Stelle 10 ist die Prüfziffer. Die weitere          #\n\
# Berechnung erfolgt nach dem Verfahren 06.                          #\n\
#                                                                    #\n\
# Führt die Berechnung zu einem Fehler, ist nach Variante 4 zu       #\n\
# prüfen.                                                            #\n\
#                                                                    #\n\
# Variante 4:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 0, 0, 0, 0                   #\n\
# Modulus 7,  Gewichtung 2, 3, 4, 5, 6, 0, 0, 0, 0                   #\n\
# Die Berechnung erfolgt nach der Methode 93.                        #\n\
######################################################################\n";

      case 105: return "\
######################################################################\n\
#              Berechnung nach der Methode A5                       #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 10                  #\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1: Gewichtung und Berechnung erfolgen nach der Methode    #\n\
# 00. Führt die Berechnung nach Variante 1 zu einem                  #\n\
# Prüfzifferfehler, so sind 10-stellige Konten mit einer 9 an        #\n\
# Stelle 1 falsch, alle anderen Konten sind nach Variante 2 zu       #\n\
# prüfen.                                                            #\n\
#                                                                    #\n\
# Variante 2: Gewichtung und Berechnung erfolgen nach der Methode 10.#\n\
######################################################################\n";

      case 106: return "\
######################################################################\n\
#              Berechnung nach der Methode A6                       #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Modulus 10, Gewichtung 3, 7, 1, 3, 7, 1, 3, 7, 1                   #\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10- stellig,     #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen. Die    #\n\
# Stelle 10 ist die Prüfziffer.                                      #\n\
#                                                                    #\n\
# Sofern dann an der zweiten Stelle der Kontonummer eine 8 steht,    #\n\
# erfolgen Gewichtung und Berechnung wie beim Verfahren 00.          #\n\
#                                                                    #\n\
# Bei allen Kontonummern, die keine 8 an der zweiten Stelle          #\n\
# haben, erfolgen Gewichtung und Berechnung wie beim Verfahren 01.   #\n\
######################################################################\n";

      case 107: return "\
######################################################################\n\
#              Berechnung nach der Methode A7                       #\n\
######################################################################\n\
#  Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                  #\n\
#                                                                    #\n\
#  Die Kontonummer ist einschließlich der Prüfziffer 10- stellig,    #\n\
#  ggf. ist die Kontonummer für die Prüfzifferberechnung durch       #\n\
#  linksbündige Auffüllung mit Nullen 10-stellig darzustellen.       #\n\
#                                                                    #\n\
#  Variante 1:                                                       #\n\
#  Gewichtung und Berechnung erfolgen nach der Methode 00. Führt die #\n\
#  Berechnung nach Variante 1 zu einem Prüfzifferfehler, ist nach    #\n\
#  Variante 2 zu prüfen.                                             #\n\
#                                                                    #\n\
#  Variante 2:                                                       #\n\
#  Gewichtung und Berechnung erfolgen nach der Methode 03.           #\n\
######################################################################\n";

      case 108: return "\
######################################################################\n\
#   Berechnung nach der Methode A8 (geändert zum 7.3.05)             #\n\
######################################################################\n\
# Die Kontonummer ist durch linksbündige Nullenauffüllung 10-        #\n\
# stellig darzustellen. Die 10. Stelle ist per Definition die        #\n\
# Prüfziffer.                                                        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7                            #\n\
# Die Stellen 4 bis 9 der Kontonummer werden von rechts nach links   #\n\
# mit den Ziffern 2, 3, 4, 5, 6, 7 multipliziert. Die weitere        #\n\
# Berechnung und die möglichen Ergebnisse entsprechen dem Verfahren  #\n\
# 06. Führt die Berechnung nach Variante 1 zu einem Prüfziffer-      #\n\
# fehler, so sind die Konten nach Variante 2 zu prüfen.              #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1                            #\n\
# Die Stellen 4 bis 9 der Kontonummer werden von rechts nach links   #\n\
# mit den Ziffern 2, 1, 2, 1, 2, 1 multipliziert. Die weiter         #\n\
# Berechnung und die möglichen Ergebnisse entsprechen dem Verfahren  #\n\
# 00.                                                                #\n\
#                                                                    #\n\
# Ausnahme:                                                          #\n\
# Ist nach linksbündiger Auffüllung mit Nullen auf 10 Stellen die    #\n\
# 3. Stelle der Kontonummer = 9 (Sachkonten), so erfolgt die         #\n\
# Berechnung gemäß der Ausnahme in Methode 51 mit den gleichen       #\n\
# Ergebnissen und Testkontonummern.                                  #\n\
######################################################################\n";

      case 109: return "\
######################################################################\n\
#              Berechnung nach der Methode A9                       #\n\
######################################################################\n\
# Modulus 10, Gewichtung 3, 7, 1, 3, 7, 1, 3, 7, 1                   #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 2, 3, 4                   #\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Gewichtung und Berechnung erfolgen nach der Methode 01. Führt die  #\n\
# Berechnung nach Variante 1 zu einem Prüfzifferfehler, so ist nach  #\n\
# Variante 2 zu prüfen.                                              #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Gewichtung und Berechnung erfolgen nach der Methode 06.            #\n\
######################################################################\n";

      case 110: return "\
######################################################################\n\
#              Berechnung nach der Methode B0                       #\n\
######################################################################\n\
#                                                                    #\n\
# Die Kontonummern sind immer 10-stellig. Kontonummern (ohne         #\n\
# führende Nullen gezählt) mit 9 oder weniger Stellen sind falsch.   #\n\
# Kontonummern mit 8 an der ersten Stelle sind ebenfalls falsch.     #\n\
# Die weitere Verfahrensweise richtet sich nach der 8. Stelle der    #\n\
# Kontonummer:                                                       #\n\
#                                                                    #\n\
# Variante 1                                                         #\n\
#                                                                    #\n\
# Für Kontonummern mit einer 1, 2, 3, oder 6 an der 8. Stelle gilt   #\n\
# das Verfahren 09 (Keine Prüfzifferberechnung, alle Kontonummern    #\n\
# sind richtig).                                                     #\n\
#                                                                    #\n\
# Variante 2                                                         #\n\
#                                                                    #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 2, 3, 4                   #\n\
#             (von rechts beginnend)                                 #\n\
#                                                                    #\n\
# Für Kontonummern mit einer 0, 4, 5, 7, 8 oder 9 an der 8. Stelle   #\n\
# erfolgen Gewichtung und Berechnung wie beim Verfahren 06.          #\n\
######################################################################\n";

      case 111: return "\
######################################################################\n\
#              Berechnung nach der Methode B1                       #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 10, Gewichtung 7, 3, 1, 7, 3, 1, 7, 3, 1                   #\n\
# Gewichtung und Berechnung erfolgen nach der Methode 05. Führt die  #\n\
# Berechnung nach Variante 1 zu einem Prüfzifferfehler, so ist nach  #\n\
# Variante 2 zu prüfen.                                              #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 10, Gewichtung 3, 7, 1, 3, 7, 1, 3, 7, 1                   #\n\
# Gewichtung und Berechnung erfolgen nach der Methode 01.            #\n\
######################################################################\n";

      case 112: return "\
######################################################################\n\
#              Berechnung nach der Methode B2                        #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 2                   #\n\
# Kontonummern, die an der 1. Stelle von links der 10- stelligen     #\n\
# Kontonummer den Wert 0 bis 7 beinhalten, sind nach der Methode 02  #\n\
# zu rechnen.                                                        #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Kontonummern, die an der 1. Stelle von links der 10- stelligen     #\n\
# Kontonummer den Wert 8 oder 9 beinhalten, sind nach der Methode    #\n\
# 00 zu rechnen.                                                     #\n\
######################################################################\n";

      case 113: return "\
######################################################################\n\
#              Berechnung nach der Methode B3                        #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig, ggf. #\n\
# ist die Kontonummer für die Prüfzifferberechnung durch             #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
#                                                                    #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7                            #\n\
#                                                                    #\n\
# Die Kontonummer ist 10-stellig. Kontonummern, die an der 1. Stelle #\n\
# von links der 10-stelligen Kontonummer den Wert bis 8 beinhalten   #\n\
# sind nach der Methode 32 zu rechen.                                #\n\
#                                                                    #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
#                                                                    #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 2, 3, 4                   #\n\
#                                                                    #\n\
# Kontonummern, die an der 1. Stelle von links der 10- stelligen     #\n\
# Kontonummer den Wert 9 beinhalten sind nach der Methode 06 zu      #\n\
# rechen.                                                            #\n\
######################################################################\n";

      case 114: return "\
######################################################################\n\
#              Berechnung nach der Methode B4                        #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
#                                                                    #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Kontonummern, die an der 1. Stelle von links der 10-stelligen      #\n\
# Kontonummer den Wert 9 beinhalten, sind nach der Methode 00 zu     #\n\
# rechnen.                                                           #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
#                                                                    #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 10                  #\n\
# Kontonummern, die an der 1. Stelle von links der 10-stelligen      #\n\
# Kontonummer den Wert 0 bis 8 beinhalten, sind nach der Methode     #\n\
# 02 zu rechnen.                                                     #\n\
######################################################################\n";

      case 115: return "\
######################################################################\n\
#              Berechnung nach der Methode B5                        #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 10, Gewichtung 7, 3, 1 ,7, 3, 1, 7, 3, 1                   #\n\
# Die Gewichtung entspricht der Methode 05. Die Berechnung           #\n\
# entspricht der Methode 01. Führt die Berechnung nach der Variante  #\n\
# 1 zu einem Prüfzifferfehler, so sind Kontonummern, die an der 1.   #\n\
# Stelle von links der 10-stelligen Kontonummer den Wert 8 oder 9    #\n\
# beinhalten, falsch. Alle anderen Kontonummern sind nach der        #\n\
# Variante 2 zu prüfen.                                              #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Gewichtung und Berechnung erfolgen nach der Methode  00.           #\n\
######################################################################\n";

      case 116: return "\
######################################################################\n\
#          Berechnung nach der Methode B6 (geändert zum 5.9.11)      #\n\
######################################################################\n\
# Variante 1:                                                        #\n\
# Modulus 11, Gewichtung 2,3,4,5,6,7,8,9,3                           #\n\
# Kontonummern, die an der 1. Stelle der 10-stelligen Kontonummer    #\n\
# den Wert 1-9 oder an den Stellen 1-5 die Werte 02691-02699         #\n\
# beinhalten, sind nach der Methode 20 zu prüfen. Alle anderen       #                                               #\n\
# Kontonummern sind nach der Variante 2 zu prüfen.                   #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 11, Gewichtung 2,4,8,5,10,9,7,3,6,1,2,4                    #\n\
# Die Berechnung erfolgt nach der Methode 53.                        #\n\
######################################################################\n";

      case 117: return "\
######################################################################\n\
#              Berechnung nach der Methode B7                        #\n\
######################################################################\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggff. ist die Kontonummer für die Prüfzifferberechnung durch       #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen. Die    #\n\
# 10. Stelle der Kontonummer ist die Prüfziffer.                     #\n\
#                                                                    #\n\
# Variante 1: Modulus 10, Gewichtung 3, 7, 1, 3, 7, 1, 3, 7, 1       #\n\
# Kontonummern der Kontenkreise 0001000000 bis 0005999999 sowie      #\n\
# 0700000000 bis 0899999999 sind nach der Methode (Kennziffer) 01    #\n\
# zu prüfen. Führt die Berechnung nach der Variante 1 zu einem       #\n\
# Prüfzifferfehler, so ist die Kontonummer falsch.                   #\n\
#                                                                    #\n\
# Variante 2: Für alle anderen Kontonummern gilt die Methode 09      #\n\
# (keine Prüfzifferberechnung).                                      #\n\
######################################################################\n";

      case 118: return "\
######################################################################\n\
#              Berechnung nach der Methode B8 (geändert zum 6.6.11)  #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen. Die    #\n\
# 10. Stelle der Kontonummer ist die Prüfziffer.                     #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 3 (modifiziert)     #\n\
#                                                                    #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der Methode 20. #\n\
# Führt die Berechnung nach Variante 1 zu einem Prüfzifferfehler,    #\n\
# so ist nach Variante 2 zu prüfen.                                  #\n\
#                                                                    #\n\
# Variante 2: Modulus 10, iterierte Transformation.                  #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der Methode 29. #\n\
# Führt die Berechnung nach Variante 2 zu einem  Prüfzifferfehler,   #\n\
# so ist nach Variante 3 zu prüfen.                                  #\n\
#                                                                    #\n\
# Variante 3:                                                        #\n\
# Für die folgenden Kontonummernkreise gilt die Methode 09 (keine    #\n\
# Prüfzifferberechnung):                                             #\n\
# 10-stellige Kontonummer; 1. + 2. Stelle = 51 - 59                  #\n\
# Kontonummernkreis 5100000000 - 5999999999                          #\n\
# 10-stellige Kontonummer; Stellen 1 - 3 = 901 - 910                 #\n\
# Kontonummernkreis 9010000000 - 9109999999                          #\n\
######################################################################\n";

      case 119: return "\
######################################################################\n\
#              Berechnung nach der Methode B9                        #\n\
######################################################################\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Kontonummern mit weniger als zwei oder mehr als drei führenden     #\n\
# Nullen sind falsch. Die Kontonummern mit zwei führenden Nullen     #\n\
# sind nach Variante 1, mit drei führenden Nullen nach Variante 2    #\n\
# zu prüfen.                                                         #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus (11,10), Gewichtung 1, 3, 2, 1, 3, 2, 1                    #\n\
# Die für die Berechnung relevanten Stellen der Kontonummer befinden #\n\
# sich - von links nach rechts gelesen ­ in den Stellen 3-9 (die     #\n\
# Prüfziffer ist in Stelle 10). Sie sind von rechts nach links       #\n\
# mit den zugehörigen Gewichtungsfaktoren zu multiplizieren.         #\n\
#                                                                    #\n\
# Zum jeweiligen Produkt ist der zugehörige Gewichtungsfaktor zu     #\n\
# addieren. Das jeweilige Ergebnis ist durch 11 zu dividieren. Die   #\n\
# sich aus der Division ergebenden Reste sind zu summieren. Diese    #\n\
# Summe ist durch 10 zu dividieren. Der Rest ist die berechnete      #\n\
# Prüfziffer.                                                        #\n\
#                                                                    #\n\
# Führt die Berechnung zu einem Prüfzifferfehler, so ist die         #\n\
# berechnete Prüfziffer um 5 zu erhöhen und erneut zu prüfen. Ist    #\n\
# die Prüfziffer größer oder gleich 10, ist 10 abzuziehen und das    #\n\
# Ergebnis ist dann die Prüfziffer.                                  #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 11, Gewichtung 1, 2, 3, 4, 5, 6                            #\n\
# Die für die Berechnung relevanten Stellen der Kontonummer          #\n\
# befinden sich - von links nach rechts gelesen - in den Stellen     #\n\
# 4-9 (die Prüfziffer ist in Stelle 10). Sie sind von rechts nach    #\n\
# links mit den zugehörigen Gewichtungsfaktoren zu multiplizieren.   #\n\
# Die Summe dieser Produkte ist zu bilden, und das erzielte          #\n\
# Ergebnis ist durch 11 zu dividieren. Der Rest ist die berechnete   #\n\
# Prüfziffer.                                                        #\n\
#                                                                    #\n\
# Führt die Berechnung zu einem Prüfzifferfehler, so ist die         #\n\
# berechnete Prüfziffer um 5 zu erhöhen und erneut zu prüfen. Ist    #\n\
# die Prüfziffer größer oder gleich 10, ist 10 abzuziehen und das    #\n\
# Ergebnis ist dann die Prüfziffer.                                  #\n\
######################################################################\n";

      case 120: return "\
######################################################################\n\
#              Berechnung nach der Methode C0                        #\n\
######################################################################\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Kontonummern mit zwei führenden Nullen sind nach Variante 1 zu     #\n\
# prüfen. Führt die Berechnung nach der Variante 1 zu einem          #\n\
# Prüfzifferfehler, ist die Berechnung nach Variante 2               #\n\
# vorzunehmen.                                                       #\n\
#                                                                    #\n\
# Kontonummern mit weniger oder mehr als zwei führenden Nullen       #\n\
# sind ausschließlich nach der Variante 2 zu                         #\n\
# prüfen.                                                            #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 11, Gewichtung 2, 4, 8, 5, 10, 9, 7, 3, 6, 1, 2, 4         #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen                 #\n\
# der Methode 52.                                                    #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 3                   #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der Methode 20  #\n\
######################################################################\n";

      case 121: return "\
######################################################################\n\
#              Berechnung nach der Methode C1                        #\n\
######################################################################\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Kontonummern, die an der 1. Stelle der 10-stelligen                #\n\
# Kontonummer einen Wert ungleich  5  beinhalten, sind nach der      #\n\
# Variante 1 zu prüfen. Kontonummern, die an der 1. Stelle der       #\n\
# 10-stelligen Kontonummer den Wert  5  beinhalten, sind nach        #\n\
# der Variante 2 zu prüfen.                                          #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 11, Gewichtung 1, 2, 1, 2, 1, 2                            #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der             #\n\
# Methode 17. Führt die Berechnung nach der Variante 1 zu einem      #\n\
# Prüfzifferfehler, so ist die Kontonummer falsch.                   #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 11, Gewichtung 1, 2, 1, 2, 1, 2                            #\n\
# Die Kontonummer ist 10-stellig mit folgendem Aufbau:               #\n\
#                                                                    #\n\
# KNNNNNNNNP                                                         #\n\
# K = Kontoartziffer                                                 #\n\
# N = laufende Nummer                                                #\n\
# P = Prüfziffer                                                     #\n\
#                                                                    #\n\
# Für die Berechnung fließen die Stellen 1 bis 9 ein. Stelle 10      #\n\
# ist die ermittelte Prüfziffer. Die Stellen 1 bis 9 sind von        #\n\
# links nach rechts mit den Ziffern 1, 2, 1, 2, 1, 2, 1, 2, 1        #\n\
# zu multiplizieren. Die jeweiligen Produkte sind zu addieren,       #\n\
# nachdem aus eventuell zweistelligen Produkten der 2., 4., 6.       #\n\
# und 8. Stelle die Quersumme gebildet wurde. Von der Summe ist      #\n\
# der Wert  1  zu subtrahieren. Das Ergebnis ist dann durch 11       #\n\
# zu dividieren. Der verbleibende Rest wird von 10 subtrahiert.      #\n\
# Das Ergebnis ist die Prüfziffer. Verbleibt nach der Division       #\n\
# durch 11 kein Rest, ist die Prüfziffer 0.                          #\n\
#                                                                    #\n\
# Beispiel:                                                          #\n\
#                                                                    #\n\
# Stellen-Nr.: K   N   N   N   N   N   N   N   N   P                 #\n\
# Konto-Nr.:   5   4   3   2   1   1   2   3   4   9                 #\n\
# Gewichtung:  1   2   1   2   1   2   1   2   1                     #\n\
#              5 + 8 + 3 + 4 + 1 + 2 + 2 + 6 + 4 = 35                #\n\
# 35 - 1 = 34                                                        #\n\
# 34 : 11 = 3, Rest 1                                                #\n\
# 10 - 1 = 9 (Prüfziffer)                                            #\n\
######################################################################\n";

      case 122: return "\
######################################################################\n\
#              Berechnung nach der Methode C2                        #\n\
######################################################################\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
# Die 10. Stelle der Kontonummer ist die Prüfziffer.                 #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 10, Gewichtung 3, 1, 3, 1, 3, 1, 3, 1, 3                   #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der             #\n\
# Methode 22. Führt die Berechnung nach Variante 1 zu einem          #\n\
# Prüfzifferfehler, so ist nach Variante 2 zu prüfen.                #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der             #\n\
# Methode 00.                                                        #\n\
######################################################################\n";

      case 123: return "\
######################################################################\n\
#              Berechnung nach der Methode C3                        #\n\
######################################################################\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
# Die 10. Stelle der Kontonummer ist die Prüfziffer. Kontonummern,   #\n\
# die an der 1. Stelle der 10-stelligen Kontonummer einen Wert       #\n\
# ungleich 9 beinhalten, sind nach der Variante 1 zu prüfen.         #\n\
# Kontonummern, die an der 1. Stelle der 10-stelligen Kontonummer    #\n\
# den Wert 9 beinhalten, sind nach der Variante 2 zu prüfen.         #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der             #\n\
# Methode 00.                                                        #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 0, 0, 0, 0                   #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der             #\n\
# Methode 58.                                                        #\n\
######################################################################\n";

      case 124: return "\
######################################################################\n\
#              Berechnung nach der Methode C4                        #\n\
######################################################################\n\
#                                                                    #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen. Die    #\n\
# 10. Stelle der Kontonummer ist die Prüfziffer.                     #\n\
# Kontonummern, die an der 1. Stelle der 10-stelligen Kontonummer    #\n\
# einen Wert ungleich 9 beinhalten, sind nach der Variante 1 zu      #\n\
# prüfen.                                                            #\n\
# Kontonummern, die an der 1. Stelle der 10-stelligen Kontonummer    #\n\
# den Wert 9 beinhalten, sind nach der Variante 2 zu prüfen.         #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5                                  #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der Methode 15. #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 0, 0, 0, 0                   #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der Methode 58. #\n\
######################################################################\n";

      case 125: return "\
######################################################################\n\
#              Berechnung nach der Methode C5                        #\n\
######################################################################\n\
#                                                                    #\n\
# Die Kontonummern sind einschließlich der Prüfziffer 6- oder 8-     #\n\
# bis 10-stellig, ggf. ist die Kontonummer für die Prüfziffer-       #\n\
# berechnung durch linksbündige Auffüllung mit Nullen 10-stellig     #\n\
# darzustellen.                                                      #\n\
#                                                                    #\n\
# Die Berechnung der Prüfziffer und die möglichen Ergebnisse         #\n\
# richten sich nach dem jeweils bei der entsprechenden Variante      #\n\
# angegebenen Kontonummernkreis. Entspricht eine Kontonummer         #\n\
# keinem der vorgegebenen Kontonummernkreise oder führt die          #\n\
# Berechnung der Prüfziffer nach der vorgegebenen Variante zu        #\n\
# einem Prüfzifferfehler, so ist die Kontonummer ungültig.           #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2                               #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der             #\n\
# Methode 75.                                                        #\n\
#                                                                    #\n\
# 6-stellige Kontonummern; 5. Stelle = 1-8                           #\n\
# Kontonummernkreis 0000100000 bis 0000899999                        #\n\
#                                                                    #\n\
# 9-stellige Kontonummern; 2. Stelle = 1-8                           #\n\
# Kontonummernkreis 0100000000 bis 0899999999                        #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 10, iterierte Transformation                               #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der             #\n\
# Methode 29.                                                        #\n\
#                                                                    #\n\
# 10-stellige Kontonummern, 1. Stelle = 1, 4, 5, 6 oder 9            #\n\
# Kontonummernkreis 1000000000 bis 1999999999                        #\n\
# Kontonummernkreis 4000000000 bis 6999999999                        #\n\
# Kontonummernkreis 9000000000 bis 9999999999                        #\n\
#                                                                    #\n\
# Variante 3:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der             #\n\
# Methode 00.                                                        #\n\
# 10-stellige Kontonummern, 1. Stelle = 3                            #\n\
# Kontonummernkreis 3000000000 bis 3999999999                        #\n\
#                                                                    #\n\
# Variante 4:                                                        #\n\
# Für die folgenden Kontonummernkreise gilt die Methode 09           #\n\
# (keine Prüfzifferberechnung).                                      #\n\
#                                                                    #\n\
# 8-stellige Kontonummern; 3. Stelle = 3, 4 oder 5                   #\n\
# Kontonummernkreis 0030000000 bis 0059999999                        #\n\
#                                                                    #\n\
# 10-stellige Kontonummern; 1.+ 2. Stelle = 70 oder 85               #\n\
# Kontonummernkreis 7000000000 bis 7099999999                        #\n\
# Kontonummernkreis 8500000000 bis 8599999999                        #\n\
######################################################################\n";

      case 126: return "\
######################################################################\n\
#   Berechnung nach der Methode C6  (letze Änderung 4.3.2013)        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 1, 2, 1, 2, 1, 2, 1, 2                      #\n\
#                                                                    #\n\
# Die Kontonummer ist 10-stellig, ggf. ist die Kontonummer für die   #\n\
# Prüfzifferberechnung durch linksbündige Auffüllung mit Nullen      #\n\
# 10-stellig darzustellen. Die 10. Stelle der Konto-nummer ist die   #\n\
# Prüfziffer.                                                        #\n\
#                                                                    #\n\
# Alle Kontonummern sind wie folgt zu prüfen:                        #\n\
#                                                                    #\n\
# Für die Berechnung der Prüfziffer werden die Stellen 2 bis 9 der   #\n\
# Kontonummer verwendet. Diese Stellen sind links um eine Zahl       #\n\
# (Konstante) gemäß der folgenden Tabelle zu ergänzen.               #\n\
#                                                                    #\n\
#   1. Stelle von links                                              #\n\
#     der 10-stelligen                                               #\n\
#       Kontonummer    Zahl (Konstante)                              #\n\
#                                                                    #\n\
#            0          4451970                                      #\n\
#            1          4451981                                      #\n\
#            2          4451992                                      #\n\
#            3          4451993                                      #\n\
#            4          4344992                                      #\n\
#            5          4344990                                      #\n\
#            6          4344991                                      #\n\
#            7          5499570                                      #\n\
#            8          4451994                                      #\n\
#            9          5499579                                      #\n\
#                                                                    #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der Methode 00. #\n\
######################################################################\n\
# Anmerkung zur Berechnung (MP): Da die Konstante immer nur einen    #\n\
# festen Wert zur Berechnung beiträgt, wird diese Berechnung nicht   #\n\
# gemacht, sondern gleich der Wert als Initialwert für die Quersumme #\n\
# verwendet. Die Berechnung beginnt erst mit der zweiten Stelle der  #\n\
# Kontonummer.                                                       #\n\
######################################################################\n";

      case 127: return "\
######################################################################\n\
#              Berechnung nach der Methode C7                        #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1                                                         #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1                            #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der             #\n\
# Methode 63. Führt die Berechnung nach Variante 1 zu einem          #\n\
# Prüfzifferfehler, so ist nach Variante 2 zu prüfen.                #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7 (modifiziert)              #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der Methode 06  #\n\
######################################################################\n";

      case 128: return "\
######################################################################\n\
#              Berechnung nach der Methode C8                        #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #  \n\
# Gewichtung und Berechnung erfolgen nach der Methode 00. Führt      # \n\
# die Berechnung nach Variante 1 zu einem Prüfzifferfehler, so ist   #    \n\
# nach Variante 2 zu prüfen.                                         #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 2, 3, 4                   #  \n\
# Gewichtung und Berechnung erfolgen nach der Methode 04. Führt      # \n\
# auch die Berechnung nach Variante 2 zu einem Prüfzifferfehler,     #  \n\
# oder ist keine gültige Prüfziffer zu ermitteln, d.h. Rest 1 nach   #\n\
# der Division durch 11, so ist nach Variante 3 zu prüfen.           #\n\
#                                                                    #\n\
# Variante 3:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 10                  #   \n\
# Gewichtung und Berechnung erfolgen nach der Methode 07.            #  \n\
######################################################################\n";

      case 129: return "\
######################################################################\n\
#              Berechnung nach der Methode C9                        #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Gewichtung und Berechnung erfolgen nach der Methode 00. Führt die  #\n\
# Berechnung nach Variante 1 zu einem Prüfzifferfehler, so ist nach  #\n\
# Variante 2 zu prüfen.                                              #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 10                  #\n\
# Gewichtung und Berechnung erfolgen nach der Methode 07.            #\n\
######################################################################\n";

      case 130: return "\
######################################################################\n\
#              Berechnung nach der Methode D0                        #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
# Kontonummern, die an der 1. und 2. Stelle der 10-stelligen         #\n\
# Kontonummer einen Wert ungleich ,,57\" beinhalten, sind nach der    #\n\
# Variante 1 zu prüfen. Kontonummern, die an der 1. und 2. Stelle    #\n\
# der 10-stelligen Kontonummer den Wert \"57\" beinhalten, sind nach   #\n\
# der Variante 2 zu prüfen.                                          #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 3 (modifiziert)     #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der Methode     #\n\
# 20. Führt die Berechnung nach der Variante 1 zu einem              #\n\
# Prüfzifferfehler, so ist die Kontonummer falsch.                   #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Für den Kontonummernkreis 5700000000 bis 5799999999 gilt die       #\n\
# Methode 09 (keine Prüfzifferberechnung, alle Kontonummern sind     #\n\
# als richtig zu werten).                                            #\n\
######################################################################\n";

      case 131: return "\
######################################################################\n\
#   Berechnung nach der Methode D1 (letzte Änderung 4.3.2013)        #\n\
######################################################################\n\
# Modulus 10, Gewichtung 1, 2, 1, 2, 1, 2, 1, 2                      #\n\
#                                                                    #\n\
# Die Kontonummer ist 10-stellig, ggf. ist die Kontonummer für die   #\n\
# Prüfzifferberechnung durch linksbündige Auffüllung mit Nullen      #\n\
# 10-stellig darzustellen. Die 10. Stelle der Kontonummer ist die    #\n\
# Prüfziffer.                                                        #\n\
#                                                                    #\n\
# Kontonummern, die an der 1. Stelle von links der 10-stelligen      #\n\
# Kontonummer den Wert 8 enthalten sind falsch.                      #\n\
#                                                                    #\n\
# Kontonummern, die an der 1. Stelle von links der 10-stelligen      #\n\
# Kontonummer einen der Werte 0, 1, 2, 3, 4, 5, 6, 7 oder 9          #\n\
# beinhalten sind wie folgt zu prüfen:                               #\n\
#                                                                    #\n\
# Für die Berechnung der Prüfziffer werden die Stellen 2 bis 9 der   #\n\
# Kontonummer von links verwendet. Diese Stellen sind links um eine  #\n\
# Zahl (Konstante) gemäß der folgenden Tabelle zu ergänzen.          #\n\
# zu ergänzen.                                                       #\n\
#                                                                    #\n\
#       1. Stelle von links   Zahl (Konstante)                       #\n\
#        der 10-stelligen                                            #\n\
#        Kontonummer                                                 #\n\
#                 0                  4363380                         #                                                                                                   #\n\
#                 1                  4363381                         #                                                                                           #\n\
#                 2                  4363382                         #                                                                                           #\n\
#                 3                  4363383                         #\n\
#                 4                  4363384                         #\n\
#                 5                  4363385                         #\n\
#                 6                  4363386                         #\n\
#                 7                  4363387                         #\n\
#                 9                  4363389                         #\n\
#                                                                    #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der             #\n\
# Methode 00.                                                        #\n\
######################################################################\n\
# Anmerkung zur Berechnung (MP): die zusätzliche feste Konstante     #\n\
# wird wie in Methode C6 im voraus berechnet und als Initialwert für #\n\
# die Quersumme verwendet. Die Berechnung beginnt allerdings -       #\n\
# entgegen der Beschreibung - mit der ersten Stelle der Kontonummer, #\n\
# da diese in der Konstanten enthalten ist.                          #\n\
######################################################################\n";

      case 132: return "\
######################################################################\n\
#              Berechnung nach der Methode D2                        #\n\
######################################################################\n\
# Variante 1:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 2, 3, 4                   #\n\
# Die Berechnung, Ausnahmen und möglichen Ergebnisse entsprechen     #\n\
# der Methode 95. Führt die Berechnung nach Variante 1 zu einem      #\n\
# Prüfzifferfehler, so ist nach Variante 2 zu prüfen.                #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Die Berechnung und möglichen Ergebnisse entsprechen der Methode    #\n\
# 00. Führt auch die Berechnung nach Variante 2 zu einem Prüfziffer- #\n\
# fehler, so ist nach Variante 3 zu prüfen.                          #\n\
#                                                                    #\n\
# Variante 3:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Die Berechnung, Ausnahmen und möglichen Ergebnisse entsprechen     #\n\
# der Methode 68. Führt auch die Berechnung nach Variante 3 zu       #\n\
# einem Prüfzifferfehler, so ist die Kontonummer falsch.             #\n\
######################################################################\n";

      case 133: return "\
######################################################################\n\
#              Berechnung nach der Methode D3                        #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Gewichtung und Berechnung erfolgen nach der Methode 00. Führt die  #\n\
# Berechnung nach Variante 1 zu einem Prüfzifferfehler, so ist nach  #\n\
# Variante 2 zu prüfen.                                              #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2 (modifiziert)     #\n\
# Gewichtung und Berechnung erfolgen nach der Methode 27.            #\n\
######################################################################\n";

      case 134: return "\
######################################################################\n\
#              Berechnung nach der Methode D4 (geändert zum 6.6.11)  #\n\
######################################################################\n\
# Modulus 10, Gewichtung 1, 2, 1, 2, 1, 2, 1, 2                      #\n\
#                                                                    #\n\
# Die Kontonummer ist 10-stellig, ggf. ist die Kontonummer für die   #\n\
# Prüfzifferberechnung durch linksbündige Auffüllung mit Nullen      #\n\
# 10-stellig darzustellen. Die 10. Stelle der Kontonummer ist die    #\n\
# Prüfziffer.                                                        #\n\
#                                                                    #\n\
# Kontonummern, die an der 1. Stelle von links der 10-stelligen      #\n\
# Kontonummer den Wert 0 beinhalten, sind falsch.                    #\n\
#                                                                    #\n\
# Kontonummern, die an der 1. Stelle von links der 10- stelligen     #\n\
# Kontonummer einen der Werte 1, 2, 3, 4, 5, 6, 7, 8 oder 9          #\n\
# beinhalten, sind wie folgt zu prüfen:                              #\n\
#                                                                    #\n\
# Für die Berechnung der Prüfziffer werden die Stellen 1 bis 9 der   #\n\
# Kontonummer von links verwendet. Diese Stellen sind links um die   #\n\
# Zahl (Konstante) \"428259\" zu ergänzen.                             #\n\
#                                                                    #\n\
# Die Berechnung und mögliche Ergebnisse entsprechen der Methode 00. #\n\
######################################################################\n";

      case 135: return "\
######################################################################\n\
#              Berechnung nach der Methode D5                        #\n\
######################################################################\n\
#                                                                    #\n\
#  1. Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 0, 0               #\n\
#  2. Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 0, 0, 0               #\n\
#  3. Modulus 7, Gewichtung  2, 3, 4, 5, 6, 7, 0, 0, 0               #\n\
#  4. Modulus 10, Gewichtung 2, 3, 4, 5, 6, 7, 0, 0, 0               #\n\
#                                                                    #\n\
#  Die Kontonummer ist einschließlich der Prüfziffer (P) 10-stellig, #\n\
#  ggf. ist die Kontonummer für die Prüfziffer-berechnung durch      #\n\
#  linksbündige Auffüllung mit Nullen 10-stellig darzustellen.       #\n\
#                                                                    #\n\
#  Konten mit der Ziffernfolge 99 an Stelle 3 und 4 (xx99xxxxxx)     #\n\
#  sind nur nach Variante 1 zu prüfen. Alle übrigen Konten sind      #\n\
#  nacheinander nach den Varianten 2, ggf. 3 und ggf. 4 zu prüfen.   #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 0, 0                   #\n\
#                                                                    #\n\
# In die Prüfzifferberechnung werden nur die Stellen 3 bis 9         #\n\
# einbezogen. Die Stelle 10 ist die Prüfziffer (P). Die weitere      #\n\
# Berechnung erfolgt nach dem Verfahren 06.                          #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 0, 0, 0                   #\n\
#                                                                    #\n\
# In die Prüfzifferberechnung werden nur die Stellen 4 bis 9         #\n\
# einbezogen. Die Stelle 10 ist die Prüfziffer (P). Die weitere      #\n\
# Berechnung erfolgt nach dem Verfahren 06.                          #\n\
#                                                                    #\n\
# Führt die Berechnung zu einem Fehler, ist nach Variante 3 zu       #\n\
# prüfen.                                                            #\n\
#                                                                    #\n\
# Variante 3:                                                        #\n\
# Modulus 7, Gewichtung 2, 3, 4, 5, 6, 7, 0, 0, 0                    #\n\
#                                                                    #\n\
# Die Stellen 4 bis 9 der Kontonummer werden von rechts nach links   #\n\
# mit den Gewichten multipliziert. Die jeweiligen Produkte werden    #\n\
# addiert. Die Summe ist durch 7 zu dividieren. Der verbleibende     #\n\
# Rest wird vom Divisor (7) subtrahiert. Das Ergebnis ist die        #\n\
# Prüfziffer (Stelle 10). Verbleibt nach der Division durch 7 kein   #\n\
# Rest, ist die Prüfziffer 0.                                        #\n\
#                                                                    #\n\
# Führt die Berechnung zu einem Fehler, ist nach Variante 4 zu       #\n\
# prüfen.                                                            #\n\
#                                                                    #\n\
# Variante 4:                                                        #\n\
# Modulus 10, Gewichtung 2, 3, 4, 5, 6, 7, 0, 0, 0                   #\n\
#                                                                    #\n\
# Die Berechnung erfolgt analog zu Variante 3, jedoch ist als        #\n\
# Divisor der Wert 10 zu verwenden.Verbleibt nach der Division       #\n\
# durch 10 kein Rest, ist die Prüfziffer 0.                          #\n\
######################################################################\n";

      case 136: return "\
######################################################################\n\
#              Berechnung nach der Methode D6                        #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Die Berechnung entspricht der Methode 07. Führt die Berechnung     #\n\
# nach Variante 1 zu einem Prüfzifferfehler, so ist nach Variante    #\n\
# 2 zu prüfen.                                                       #\n\
#                                                                    #\n\
# Variante 2                                                         #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Die Berechnung entspricht der Methode 03.                          #\n\
# Führt die Berechnung nach Variante 2 zu einem Prüfzifferfehler,    #\n\
# so ist nach Variante 3 zu prüfen.                                  #\n\
#                                                                    #\n\
#                                                                    #\n\
# Variante 3                                                         #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Die Berechnung entspricht der Methode 00.                          #\n\
# Führt auch die Berechnung nach Variante 3 zu einem                 #\n\
# Prüfzifferfehler, so ist die Kontonummer falsch.                   #\n\
######################################################################\n";

      case 137: return "\
######################################################################\n\
#               Berechnung nach der Methode D7                       #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Die Stellen der Kontonummer sind von rechts nach links mit         #\n\
# den Ziffern 2, 1, 2, 1, 2, 1,  2, 1, 2 zu multiplizieren. Die      #\n\
# jeweiligen Produkte werden addiert, nachdem jeweils aus den        #\n\
# zweistelligen Produkten die Quersumme gebildet wurde (z. B.        #\n\
# Produkt 18 = Quersumme 9). Nach der Addition bleiben außer         #\n\
# der Einerstelle alle anderen Stellen unberücksichtigt; diese       #\n\
# Einerstelle ist die Prüfziffer (Ergebnis = 27 / Prüfziffer = 7).   #\n\
######################################################################\n\
# Anm. (M.P.): Die Methode entspricht (bis auf die Subtraktion von   #\n\
# 10) der Prüfziffermethode 00, und wird auch weitgehend von dieser  #\n\
# Methode kopiert.                                                   #\n\
######################################################################\n";

      case 138: return "\
######################################################################\n\
#               Berechnung nach der Methode D8                       #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
# Die Berechnung der Prüfziffer und die möglichen Ergebnisse         #\n\
# richten sich nach dem jeweils bei der entsprechenden  Variante     #\n\
# angegebenen Kontonummernkreis. Entspricht eine  Kontonummer        #\n\
# keinem der vorgegebenen Kontonummernkreise oder führt die          #\n\
# Berechnung der Prüfziffer nach der Variante 1 zu einem             #\n\
# Prüfzifferfehler, so ist die Kontonummer ungültig.                 #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Für Kontonummern aus dem Kontonummernkreis                         #\n\
# 1000000000 bis 9999999999 entsprechen die Berechnung               #\n\
# und mögliche Ergebnisse der Methode 00.                            #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Für den Kontonummernkreis 0010000000 bis 0099999999 gilt  die      #\n\
# Methode 09 (keine Prüfzifferberechnung, alle Kontonummern sind     #\n\
# als richtig zu werten).                                            #\n\
######################################################################\n";

      case 139: return "\
######################################################################\n\
#               Berechnung nach der Methode D9                       #\n\
######################################################################\n\
# Die Kontonummer ist einschließlich der Prüfziffer 10-stellig,      #\n\
# ggf. ist die Kontonummer für die Prüfzifferberechnung durch        #\n\
# linksbündige Auffüllung mit Nullen 10-stellig darzustellen.        #\n\
#                                                                    #\n\
# Variante 1:                                                        #\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
#                                                                    #\n\
# Gewichtung und Berechnung erfolgen nach der Methode 00. Führt      #\n\
# die Berechnung nach Variante 1 zu einem Prüfzifferfehler, so       #\n\
# ist nach Variante 2 zu prüfen.                                     #\n\
#                                                                    #\n\
# Variante 2:                                                        #\n\
# Modulus 11, Gewichtung 2, 3, 4, 5, 6, 7, 8, 9, 10                  #\n\
#                                                                    #\n\
# Gewichtung und Berechnung erfolgen nach der Methode 10.            #\n\
# Führt die Berechnung nach Variante 2 zu einem Prüfzifferfehler,    #\n\
# so ist nach Variante 3 zu prüfen.                                  #\n\
#                                                                    #\n\
# Variante 3:                                                        #\n\
# Modulus 10, Gewichtung 3, 9, 7, 1, 3, 9, 7, 1, 3                   #\n\
#                                                                    #\n\
# Gewichtung und Berechnung erfolgen nach der Methode 18.            #\n\
######################################################################\n";

      case 140: return "\
######################################################################\n\
#               Berechnung nach der Methode E0                       #\n\
######################################################################\n\
# Modulus 10, Gewichtung 2, 1, 2, 1, 2, 1, 2, 1, 2                   #\n\
# Die Stellen der Kontonummer sind von rechts nach links mit den     #\n\
# Ziffern 2, 1, 2, 1, 2 usw. zu multiplizieren. Die jeweiligen       #\n\
# Produkte werden addiert, nachdem jeweils aus den zweistelligen     #\n\
# Produkten die Quersumme gebildet wurde (z. B. Produkt 18 =         #\n\
# Quersumme 9) plus den Wert 7. Nach der Addition bleiben außer      #\n\
# der Einerstelle alle anderen Stellen unberücksichtigt. Die         #\n\
# Einerstelle wird von dem Wert 10 subtrahiert. Das Ergebnis ist     #\n\
# die Prüfziffer (10. Stelle der Kontonummer). Ergibt sich nach der  #\n\
# Subtraktion der Rest 10, ist die Prüfziffer 0.                     #\n\
######################################################################\n";

      case 141: return "\
######################################################################\n\
#               Berechnung nach der Methode E1                       #\n\
######################################################################\n\
#                                                                    #\n\
# Modulus 11, Gewichtung 1, 2, 3, 4, 5, 6, 11, 10, 9                 #\n\
# Die Kontonummer sowohl für Kontokorrentkonten als auch für         #\n\
# Sparkonten ist 9-stellig und für die Prüfzifferberechnung durch    #\n\
# linksbündige Auffüllung mit einer Null 10-stellig darzustellen.    #\n\
# Die 10. Stelle der Kontonummer ist die Prüfziffer.                 #\n\
# Vor der Berechnung der Prüfziffer sind die einzelnen Stellen der   #\n\
# Kontonummer durch folgende Werte (ASCII Wert) zu ersetzen:         #\n\
#                                                                    #\n\
# Ziffern der Kontonummer      0  1  2  3  4  5  6  7  8  9          #\n\
# ASCII-Wert                  48 49 50 51 52 53 54 55 56 57          #\n\
#                                                                    #\n\
# Die einzelnen ASCII-Werte sind von rechts nach links mit den       #\n\
# Ziffern 1, 2, 3, 4, 5, 6, 11, 10, 9 zu multiplizieren. Die         #\n\
# jeweiligen Produkte werden addiert. Die Summe ist durch 11 zu      #\n\
# dividieren. Der verbleibende Rest ist die Prüfziffer. Verbleibt    #\n\
# nach der Division durch 11 kein Rest, ist die Prüfziffer 0.        #\n\
# Ergibt sich ein Rest 10, ist die Kontonummer falsch.               #\n\
#                                                                    #\n\
# Anmerkung (M.P.): nach der Multiplikation wird ein Wert von 2442   #\n\
# subtrahiert; dies ist ein Vielfaches von 11, das sich bei der      #\n\
# \"Kontonummer\" 0 ergibt. Durch die ASCII-Darstellung wird das       #\n\
# Ergebnis nur unnötig vergrößert; die Subtraktion ändert das        #\n\
# Endergebnis nicht, bringt aber die Summe in einen Bereich, der für #\n\
# das Makros MOD_11_352 akzeptabel ist.                              #\n\
######################################################################\n";

      default: return "Unbekannte oder nicht implementierte Prüfziffermethode\n";
   }
}
