#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_alpm.h"

#include "handle.h"
#include "db.h"
#include "transaction.h"
#include "pkg.h"

ZEND_DECLARE_MODULE_GLOBALS(alpm)

PHP_FUNCTION(alpm_version);
PHP_FUNCTION(php_alpm_version);

static zend_function_entry alpm_functions[] = {
    PHP_FE(alpm_version, NULL)
    PHP_FE(php_alpm_version, NULL)

    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(alpm) {
    alpm_init_handle(TSRMLS_C);
    alpm_init_transaction(TSRMLS_C);
    alpm_init_pkg(TSRMLS_C);
    alpm_init_db(TSRMLS_C);
}

zend_module_entry alpm_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_ALPM_EXTNAME,
    alpm_functions,
    PHP_MINIT(alpm),
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_ALPM_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ALPM
ZEND_GET_MODULE(alpm)
#endif

/* Generic functions, mostly information about the extension or libalpm itself */

PHP_FUNCTION(alpm_version) {
    RETURN_STRING(alpm_version())
}

PHP_FUNCTION(php_alpm_version) {
    RETURN_STRING(PHP_ALPM_VERSION)
}
