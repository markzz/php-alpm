/*
 *  php_alpm_shared.h
 *
 *  Copyright (c) 2016-2017 Mark Weiman <contact@markzz.net>
 *
 *  This extension is free software; you can redistribute it and/or
 *  modify it under the terms of version 2.1 of the GNU Lesser General
 *  Public License as published by the Free Software Foundation.
 *
 *  This extension is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this extension; if not see <http://www.gnu.org/licenses/>.
 */

#ifndef PHP_ALPM_SHARED_H
#define PHP_ALPM_SHARED_H

#include "php.h"

PHPAPI zend_class_entry *php_alpm_handle_get_class_entry();
PHPAPI zend_class_entry *php_alpm_db_get_class_entry();
PHPAPI zend_class_entry *php_alpm_pkg_get_class_entry();

#endif /* PHP_ALPM_SHARED_H */
