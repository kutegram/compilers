/* Everything */

#ifndef QT_DLL
#define QT_DLL
#endif

/* License information */
#define QT_PRODUCT_LICENSEE "Open Source"
#define QT_PRODUCT_LICENSE "OpenSource"

// Qt Edition
#ifndef QT_EDITION
#  define QT_EDITION QT_EDITION_OPENSOURCE
#endif

#if defined(__SYMBIAN32__)
# define QT_BUILD_KEY "Symbian full-config"
#else
# if !defined(QT_NO_DEBUG)
#  if (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#   define QT_BUILD_KEY "Windows x64 mingw debug full-config"
#  else
#   define QT_BUILD_KEY "Windows mingw debug full-config"
#  endif
# else
#  if (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#   define QT_BUILD_KEY "Windows x64 mingw release full-config"
#  else
#   define QT_BUILD_KEY "Windows mingw release full-config"
#  endif
# endif
#endif

/* Machine byte-order */
#define Q_BIG_ENDIAN 4321
#define Q_LITTLE_ENDIAN 1234
#define Q_BYTE_ORDER Q_LITTLE_ENDIAN

// Compile time features
#define QT_ARCH_SYMBIAN
#define QT_LIBINFIX ""
#if defined(QT_GRAPHICSSYSTEM_OPENVG) && defined(QT_NO_GRAPHICSSYSTEM_OPENVG)
# undef QT_GRAPHICSSYSTEM_OPENVG
#elif !defined(QT_GRAPHICSSYSTEM_OPENVG)
# define QT_GRAPHICSSYSTEM_OPENVG
#endif

#if defined(QT_NO_ACCESSIBILITY) && defined(QT_ACCESSIBILITY)
# undef QT_NO_ACCESSIBILITY
#elif !defined(QT_NO_ACCESSIBILITY)
# define QT_NO_ACCESSIBILITY
#endif

#if defined(QT_NO_CONCURRENT) && defined(QT_CONCURRENT)
# undef QT_NO_CONCURRENT
#elif !defined(QT_NO_CONCURRENT)
# define QT_NO_CONCURRENT
#endif

#if defined(QT_NO_CRASHHANDLER) && defined(QT_CRASHHANDLER)
# undef QT_NO_CRASHHANDLER
#elif !defined(QT_NO_CRASHHANDLER)
# define QT_NO_CRASHHANDLER
#endif

#if defined(QT_NO_DBUS) && defined(QT_DBUS)
# undef QT_NO_DBUS
#elif !defined(QT_NO_DBUS)
# define QT_NO_DBUS
#endif

#if defined(QT_NO_FREETYPE) && defined(QT_FREETYPE)
# undef QT_NO_FREETYPE
#elif !defined(QT_NO_FREETYPE)
# define QT_NO_FREETYPE
#endif

#if defined(QT_NO_IMAGEFORMAT_JPEG) && defined(QT_IMAGEFORMAT_JPEG)
# undef QT_NO_IMAGEFORMAT_JPEG
#elif !defined(QT_NO_IMAGEFORMAT_JPEG)
# define QT_NO_IMAGEFORMAT_JPEG
#endif

#if defined(QT_NO_IMAGEFORMAT_MNG) && defined(QT_IMAGEFORMAT_MNG)
# undef QT_NO_IMAGEFORMAT_MNG
#elif !defined(QT_NO_IMAGEFORMAT_MNG)
# define QT_NO_IMAGEFORMAT_MNG
#endif

#if defined(QT_NO_IMAGEFORMAT_TIFF) && defined(QT_IMAGEFORMAT_TIFF)
# undef QT_NO_IMAGEFORMAT_TIFF
#elif !defined(QT_NO_IMAGEFORMAT_TIFF)
# define QT_NO_IMAGEFORMAT_TIFF
#endif

#if defined(QT_NO_IPV6) && defined(QT_IPV6)
# undef QT_NO_IPV6
#elif !defined(QT_NO_IPV6)
# define QT_NO_IPV6
#endif

#if defined(QT_NO_PRINTER) && defined(QT_PRINTER)
# undef QT_NO_PRINTER
#elif !defined(QT_NO_PRINTER)
# define QT_NO_PRINTER
#endif

#if defined(QT_NO_QFUTURE) && defined(QT_QFUTURE)
# undef QT_NO_QFUTURE
#elif !defined(QT_NO_QFUTURE)
# define QT_NO_QFUTURE
#endif

#if defined(QT_NO_SCRIPTTOOLS) && defined(QT_SCRIPTTOOLS)
# undef QT_NO_SCRIPTTOOLS
#elif !defined(QT_NO_SCRIPTTOOLS)
# define QT_NO_SCRIPTTOOLS
#endif

#if defined(QT_NO_STYLE_CDE) && defined(QT_STYLE_CDE)
# undef QT_NO_STYLE_CDE
#elif !defined(QT_NO_STYLE_CDE)
# define QT_NO_STYLE_CDE
#endif

#if defined(QT_NO_STYLE_CLEANLOOKS) && defined(QT_STYLE_CLEANLOOKS)
# undef QT_NO_STYLE_CLEANLOOKS
#elif !defined(QT_NO_STYLE_CLEANLOOKS)
# define QT_NO_STYLE_CLEANLOOKS
#endif

#if defined(QT_NO_STYLE_GTK) && defined(QT_STYLE_GTK)
# undef QT_NO_STYLE_GTK
#elif !defined(QT_NO_STYLE_GTK)
# define QT_NO_STYLE_GTK
#endif

#if defined(QT_NO_STYLE_MOTIF) && defined(QT_STYLE_MOTIF)
# undef QT_NO_STYLE_MOTIF
#elif !defined(QT_NO_STYLE_MOTIF)
# define QT_NO_STYLE_MOTIF
#endif

#if defined(QT_NO_STYLE_PLASTIQUE) && defined(QT_STYLE_PLASTIQUE)
# undef QT_NO_STYLE_PLASTIQUE
#elif !defined(QT_NO_STYLE_PLASTIQUE)
# define QT_NO_STYLE_PLASTIQUE
#endif

#if defined(QT_NO_STYLE_WINDOWSCE) && defined(QT_STYLE_WINDOWSCE)
# undef QT_NO_STYLE_WINDOWSCE
#elif !defined(QT_NO_STYLE_WINDOWSCE)
# define QT_NO_STYLE_WINDOWSCE
#endif

#if defined(QT_NO_STYLE_WINDOWSMOBILE) && defined(QT_STYLE_WINDOWSMOBILE)
# undef QT_NO_STYLE_WINDOWSMOBILE
#elif !defined(QT_NO_STYLE_WINDOWSMOBILE)
# define QT_NO_STYLE_WINDOWSMOBILE
#endif

#if defined(QT_NO_STYLE_WINDOWSVISTA) && defined(QT_STYLE_WINDOWSVISTA)
# undef QT_NO_STYLE_WINDOWSVISTA
#elif !defined(QT_NO_STYLE_WINDOWSVISTA)
# define QT_NO_STYLE_WINDOWSVISTA
#endif

#if defined(QT_NO_STYLE_WINDOWSXP) && defined(QT_STYLE_WINDOWSXP)
# undef QT_NO_STYLE_WINDOWSXP
#elif !defined(QT_NO_STYLE_WINDOWSXP)
# define QT_NO_STYLE_WINDOWSXP
#endif

#if defined(QT_NO_SYSTEMTRAYICON) && defined(QT_SYSTEMTRAYICON)
# undef QT_NO_SYSTEMTRAYICON
#elif !defined(QT_NO_SYSTEMTRAYICON)
# define QT_NO_SYSTEMTRAYICON
#endif

#if defined(QT_NO_WEBKIT) && defined(QT_WEBKIT)
# undef QT_NO_WEBKIT
#elif !defined(QT_NO_WEBKIT)
# define QT_NO_WEBKIT
#endif

#if defined(QT_OPENGL_ES) && defined(QT_NO_OPENGL_ES)
# undef QT_OPENGL_ES
#elif !defined(QT_OPENGL_ES)
# define QT_OPENGL_ES
#endif

#if defined(QT_OPENGL_ES_2) && defined(QT_NO_OPENGL_ES_2)
# undef QT_OPENGL_ES_2
#elif !defined(QT_OPENGL_ES_2)
# define QT_OPENGL_ES_2
#endif

#if defined(QT_SQL_SQLITE) && defined(QT_NO_SQL_SQLITE)
# undef QT_SQL_SQLITE
#elif !defined(QT_SQL_SQLITE)
# define QT_SQL_SQLITE
#endif

#define QT_NO_ICONV
#define QT_NO_GLIB
