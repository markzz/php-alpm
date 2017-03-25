PHP_ARG_ENABLE(alpm, whether to enable alpm support, [ --enable-alpm Enable alpm support])

if test "$PHP_ALPM" != "no"; then
    SEARCH_PATH="/usr/local/include /usr/include"
    SEARCH_FOR="alpm.h"

    if test -r $PHP_ALPM/$SEARCH_FOR; then
        ALPM_DIR=$PHP_ALPM
    else
        AC_MSG_CHECKING([for alpm files in default path])
        for i in $SEARCH_PATH; do
            if test -r $i/$SEARCH_FOR; then
                ALPM_DIR=$i
                AC_MSG_RESULT(found in $i)
            fi
        done
    fi

    if test -z "$ALPM_DIR"; then
        AC_MSG_RESULT([not found])
        AC_MSG_ERROR([Please reinstall libalpm (pacman)])
    fi

    PHP_ADD_INCLUDE($ALPM_DIR)

    LIBNAME=alpm
    LIBSYMBOL=alpm_version

    PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
    [
        PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ALPM_DIR/lib, ALPM_SHARED_LIBADD)
        AC_DEFINE(HAVE_ALPM, 1, [Whether you have alpm])
    ],[
        AC_MSG_ERROR([Wrong libalpm version or libalpm not found])
    ],[
        -L$ALPM_DIR/lib -1m $ALPM_DL

    ])
    PHP_SUBST(ALPM_SHARED_LIBADD)

    PHP_NEW_EXTENSION(alpm, src/alpmhandle_class.c src/alpmdb_class.c src/alpmpkg_class.c src/alpmtransaction_class.c src/alpm_helpers.c src/alpm_callbacks.c src/alpm.c, $ext_shared)
fi
