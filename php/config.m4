PHP_ARG_ENABLE(konto_check, whether to enable konto_check support,
[  --enable-konto_check    Enable konto_check support])

PHP_ARG_ENABLE(bav, whether to make the library compatible with BAV,
[  --enable-bav            build BAV compatible version; default=no], no, no)

PHP_ARG_ENABLE(beschreibung, whether to add description text of the check methods,
[  --enable-beschreibung   include description text of check methods; default=yes], yes, yes)

PHP_ARG_ENABLE(check_malloc, whether to include code to check for memory allocation problems,
[  --enable-check_malloc   include malloc debug code; default=no], no, no)

PHP_ARG_ENABLE(symbolic_retvals, whether to include code to check for memory allocation problems,
[  --enable-symbolic_retvals   define symbolic retvals; default=yes], yes, yes)

if test "$PHP_KONTO_CHECK" = "yes"; then
  AC_DEFINE(HAVE_KONTO_CHECK, 1, [Whether you have konto_check])
  PHP_NEW_EXTENSION(konto_check, konto_check.c, $ext_shared)
fi

if test "$PHP_BAV" != "no"; then
   AC_DEFINE(BAV_KOMPATIBEL,1,[Define to 1 to use BAV compatible version.])
fi

if test "$PHP_BESCHREIBUNG" != "no"; then
   AC_DEFINE(BESCHREIBUNG_TXT,1,[Define to 1 to add description text of the check methods.])
fi

if test "$PHP_CHECK_MALLOC" != "no"; then
   AC_DEFINE(CHECK_MALLOC,1,[Define to 1 to include malloc debug code.])
fi

if test "$PHP_SYMBOLIC_RETVALS" != "no"; then
   AC_DEFINE(SYMBOLIC_RETVALS,1,[Define to 1 to add symbolic retvals.])
fi

AC_DEFINE(PACKAGE_BUGREPORT,"m.plugge@hs-mannheim.de",[Define to the address where bug reports for this package should be sent.])
AC_DEFINE(PACKAGE_NAME,"konto_check",[Define to the full name of this package.])
AC_DEFINE(PACKAGE_STRING,"konto_check 5.2",[Define to the full name and version of this package.])
AC_DEFINE(PACKAGE_VERSION,"5.2",[Define to the version of this package.])
