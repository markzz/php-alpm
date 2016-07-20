#ifndef PHP_ALPM_SHARED_H
#define PHP_ALPM_SHARED_H

#include "php.h"

PHPAPI zend_class_entry *php_alpm_handle_get_class_entry();
PHPAPI zend_class_entry *php_alpm_db_get_class_entry();
PHPAPI zend_class_entry *php_alpm_pkg_get_class_entry();

#endif /* PHP_ALPM_SHARED_H */
