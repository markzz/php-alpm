/*
 *  alpmpkg_class.c
 *
 *  Copyright (c) 2016-2017 Mark Weiman <mark.weiman@markzz.com>
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

    ret = zend_string_init(tmp, strlen(tmp), 1);
    efree(tmp);

    RETURN_STR(ret)
}

PHP_METHOD(Pkg, compute_requiredby) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_pkg_compute_requiredby(intern->pkg), return_value);
    return;
}

PHP_METHOD(Pkg, get_arch) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_arch() deprecated, use AlpmHandle->arch instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_arch(intern->pkg);

#ifdef ZEND_ENGINE_3
    RETURN_STRING(ret)
#else
    RETURN_STRING(ret, 1)
#endif
}

PHP_METHOD(Pkg, get_backup) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_backup() deprecated, use AlpmHandle->backup instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    list = alpm_pkg_get_backup(intern->pkg);
    if (!list) {
        RETURN_NULL()
    }

    alpm_backup_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Pkg, get_base64_sig) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_base64_sig() deprecated, use AlpmHandle->base64_sig instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_base64_sig(intern->pkg);
    if (ret == NULL) {
        RETURN_NULL()
    }

#ifdef ZEND_ENGINE_3
    RETURN_STRING(ret)
#else
    RETURN_STRING(ret, 1)
#endif
}

PHP_METHOD(Pkg, get_builddate) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_builddate() deprecated, use AlpmHandle->builddate instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    long ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_builddate(intern->pkg);

    RETURN_LONG(ret)
}

PHP_METHOD(Pkg, get_conflicts) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_conflicts() deprecated, use AlpmHandle->conflicts instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    list = alpm_pkg_get_conflicts(intern->pkg);
    if (!list) {
        RETURN_NULL()
    }

    alpm_depend_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Pkg, get_db) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_db() deprecated, use AlpmHandle->db instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    php_alpm_db_object *new_obj;
    alpm_db_t *db;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    db = alpm_pkg_get_db(intern->pkg);
    if (!db) {
        RETURN_NULL()
    }

    object_init_ex(return_value, php_alpm_db_sc_entry);
    new_obj = Z_DBO_P(return_value);
    new_obj->db = db;
    return;
}

PHP_METHOD(Pkg, get_depends) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_depends() deprecated, use AlpmHandle->depends instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    list = alpm_pkg_get_depends(intern->pkg);
    alpm_depend_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Pkg, get_desc) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_desc() deprecated, use AlpmHandle->desc instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_desc(intern->pkg);

#ifdef ZEND_ENGINE_3
    RETURN_STRING(ret)
#else
    RETURN_STRING(ret, 1)
#endif
}

PHP_METHOD(Pkg, get_download_size) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_download_size() deprecated, use AlpmHandle->download_size instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    long ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_download_size(intern->pkg);
    RETURN_LONG(ret)
}

PHP_METHOD(Pkg, get_filename) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_filename() deprecated, use AlpmHandle->filename instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_filename(intern->pkg);

#ifdef ZEND_ENGINE_3
    RETURN_STRING(ret)
#else
    RETURN_STRING(ret, 1)
#endif
}

PHP_METHOD(Pkg, get_files) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_files() deprecated, use AlpmHandle->files instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_filelist_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    list = alpm_pkg_get_files(intern->pkg);
    if (!list) {
        RETURN_NULL()
    }
    if (list->count == 0) {
        RETURN_NULL()
    }

    alpm_filelist_to_zval(list, return_value);
    return;
}

PHP_METHOD(Pkg, get_groups) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_groups() deprecated, use AlpmHandle->groups instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    list = alpm_pkg_get_groups(intern->pkg);
    if (!list) {
        RETURN_NULL()
    }

    alpm_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Pkg, get_has_scriptlet) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_has_scriptlet() deprecated, use AlpmHandle->has_scriptlet instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    int has_scriptlet;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    has_scriptlet = alpm_pkg_has_scriptlet(intern->pkg);
    if (has_scriptlet == 0) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }

    RETURN_NULL()
}

PHP_METHOD(Pkg, get_installdate) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_installdate() deprecated, use AlpmHandle->installdate instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_time_t ret = 0;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_installdate(intern->pkg);
    RETURN_LONG(ret)
}

PHP_METHOD(Pkg, get_isize) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_isize() deprecated, use AlpmHandle->isize instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    long ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_isize(intern->pkg);
    RETURN_LONG(ret)
}

PHP_METHOD(Pkg, get_licenses) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_licenses() deprecated, use AlpmHandle->licenses instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    list = alpm_pkg_get_licenses(intern->pkg);
    if (!list) {
        RETURN_NULL()
    }

    alpm_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Pkg, get_md5sum) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_md5sum() deprecated, use AlpmHandle->md5sum instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_md5sum(intern->pkg);
    if (ret == NULL) {
        RETURN_NULL()
    }

#ifdef ZEND_ENGINE_3
    RETURN_STRING(ret)
#else
    RETURN_STRING(ret, 1)
#endif
}

PHP_METHOD(Pkg, get_name) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_name() deprecated, use AlpmHandle->name instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_name(intern->pkg);

#ifdef ZEND_ENGINE_3
    RETURN_STRING(ret)
#else
    RETURN_STRING(ret, 1)
#endif
}

PHP_METHOD(Pkg, get_optdepends) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_optdepends() deprecated, use AlpmHandle->optdepends instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    list = alpm_pkg_get_optdepends(intern->pkg);
    if (!list) {
        RETURN_NULL()
    }

    alpm_depend_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Pkg, get_packager) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_packager() deprecated, use AlpmHandle->packager instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_packager(intern->pkg);

#ifdef ZEND_ENGINE_3
    RETURN_STRING(ret)
#else
    RETURN_STRING(ret, 1)
#endif
}

PHP_METHOD(Pkg, get_provides) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_provides() deprecated, use AlpmHandle->provides instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    list = alpm_pkg_get_provides(intern->pkg);
    if (!list) {
        RETURN_NULL()
    }

    alpm_depend_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Pkg, get_reason) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_reason() deprecated, use AlpmHandle->reason instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_pkgreason_t ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_reason(intern->pkg);

    /* I'm not sure if this should return more than a long which is why I
     * put the if blocks in here, perhaps if longs are fine just make a simple
     * RETURN_LONG(ret) line instead
     */
    if (ret == ALPM_PKG_REASON_EXPLICIT) {
        RETURN_LONG(ALPM_PKG_REASON_EXPLICIT) /* 0 */
    } else if (ret == ALPM_PKG_REASON_DEPEND){
        RETURN_LONG(ALPM_PKG_REASON_DEPEND) /* 1 */
    } else {
        RETURN_LONG(-1)
    }
}

PHP_METHOD(Pkg, get_replaces) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_replaces() deprecated, use AlpmHandle->replaces instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    list = alpm_pkg_get_replaces(intern->pkg);
    if (!list) {
        RETURN_NULL()
    }

    alpm_depend_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Pkg, get_sha256sum) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_sha256sum() deprecated, use AlpmHandle->sha256sum instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_sha256sum(intern->pkg);

#ifdef ZEND_ENGINE_3
    RETURN_STRING(ret)
#else
    RETURN_STRING(ret, 1)
#endif
}

PHP_METHOD(Pkg, get_size) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_size() deprecated, use AlpmHandle->size instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    long ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_size(intern->pkg);
    RETURN_LONG(ret)
}

PHP_METHOD(Pkg, get_url) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_url() deprecated, use AlpmHandle->url instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_url(intern->pkg);

#ifdef ZEND_ENGINE_3
    RETURN_STRING(ret)
#else
    RETURN_STRING(ret, 1)
#endif
}

PHP_METHOD(Pkg, get_version) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_version() deprecated, use AlpmHandle->version instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_version(intern->pkg);

#ifdef ZEND_ENGINE_3
    RETURN_STRING(ret)
#else
    RETURN_STRING(ret, 1)
#endif
}

PHP_METHOD(Pkg, set_reason) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->set_reason() deprecated, set AlpmHandle->reason instead");

    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_pkgreason_t reason;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &reason) == FAILURE) {
        RETURN_NULL()
    }

    if (reason != ALPM_PKG_REASON_DEPEND && reason != ALPM_PKG_REASON_EXPLICIT) {
        zend_throw_exception(php_alpm_pkg_exception_class_entry, "not a valid install reason", 0 TSRMLS_CC);
        RETURN_FALSE
    }

    err = alpm_pkg_set_reason(intern->pkg, reason);
    if (err == -1) {
        RETURN_FALSE
    }
    RETURN_TRUE
}