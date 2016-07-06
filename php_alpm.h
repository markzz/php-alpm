#ifndef PHP_ALPM_H
#define PHP_ALPM_H

#include <alpm.h>

#ifdef ZTS
#include "TSRM.h"
#endif

#define DEFAULT_ROOTDIR "/"
#define DEFAULT_DBPATH "/var/lib/pacman"

ZEND_BEGIN_MODULE_GLOBALS(alpm)
ZEND_END_MODULE_GLOBALS(alpm)

#ifdef ZTS
#define ALPM_G(v) TSRMG(alpm_globals_id, zend_hello_globals *, v)
#else
#define ALPM_G(v) (alpm_globals.v)
#endif

#define PHP_ALPM_VERSION "0.1"
#define PHP_ALPM_EXTNAME "alpm"

PHP_MINIT_FUNCTION(alpm);
//PHP_MSHUTDOWN_FUNCTION(alpm);
//PHP_RINIT_FUNCTION(alpm);

extern zend_module_entry alpm_module_entry;
#define phpext_alpm_ptr &alpm_module_entry

#endif