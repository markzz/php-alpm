/*
 *  php_alpm.h
 *
 *  Copyright (c) 2016-2019 Mark Weiman <mark.weiman@markzz.com>
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

#ifndef PHP_ALPM_H
#define PHP_ALPM_H

#define PHP_ALPM_EXTNAME "alpm"
#define PHP_ALPM_VERSION "0.5"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#include "php.h"
#include "zend_exceptions.h"

extern zend_module_entry alpm_module_entry;
#define phpext_alpm_ptr &alpm_module_entry

#endif /* PHP_ALPM_H */
