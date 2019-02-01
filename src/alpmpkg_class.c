/*
 *  alpmpkg_class.c
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

#include "php_alpm.h"
#include "php_alpm_defs.h"
#include "php_alpm_helpers.h"

PHP_METHOD(Pkg, __toString) {
    /* $pkgname $pkgver */
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *pkgname, *pkgver;
    char *tmp = NULL;
    size_t pnsize, pvsize;
    zend_string *ret;

    pkgname = alpm_pkg_get_name(intern->pkg);
    pkgver = alpm_pkg_get_version(intern->pkg);

    pnsize = strlen(pkgname);
    pvsize = strlen(pkgver);

    tmp = (char*)emalloc(sizeof(char*) * (pnsize + pvsize + strlen(" ")));
    sprintf(tmp, "%s %s", pkgname, pkgver);

    ret = zend_string_init(tmp, strlen(tmp), 0);
    efree(tmp);

    RETURN_STR(ret)
}

PHP_METHOD(Pkg, compute_requiredby) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_pkg_compute_requiredby(intern->pkg), return_value);
}
