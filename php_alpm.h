#ifndef PHP_ALPM_H
#define PHP_ALPM_H

#define PHP_ALPM_EXTNAME "alpm"
#define PHP_ALPM_VERSION "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#include "php.h"

extern zend_module_entry alpm_module_entry;
#define phpext_alpm_ptr &alpm_module_entry

#endif /* PHP_ALPM_H */