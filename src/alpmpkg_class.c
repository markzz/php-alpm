#include "php_alpm.h"
#include "php_alpm_defs.h"
#include "php_alpm_helpers.h"

PHP_METHOD(Pkg, compute_requiredby) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_pkg_compute_requiredby(intern->pkg), return_value);
    return;
}

PHP_METHOD(Pkg, get_arch) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_arch(intern->pkg);
    RETURN_STRING(ret)
}

PHP_METHOD(Pkg, get_backup) {
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
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_base64_sig(intern->pkg);
    if (ret == NULL) {
        RETURN_NULL()
    }
    RETURN_STRING(ret)
}

PHP_METHOD(Pkg, get_builddate) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    long ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_builddate(intern->pkg);
    RETURN_LONG(ret)
}

PHP_METHOD(Pkg, get_conflicts) {
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
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_desc(intern->pkg);
    RETURN_STRING(ret)
}

PHP_METHOD(Pkg, get_download_size) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    long ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_download_size(intern->pkg);
    RETURN_LONG(ret)
}

PHP_METHOD(Pkg, get_filename) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_filename(intern->pkg);
    RETURN_STRING(ret)
}

PHP_METHOD(Pkg, get_files) {
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
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_time_t ret = 0;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_installdate(intern->pkg);
    RETURN_LONG(ret)
}

PHP_METHOD(Pkg, get_isize) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    long ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_isize(intern->pkg);
    RETURN_LONG(ret)
}

PHP_METHOD(Pkg, get_licenses) {
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
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_md5sum(intern->pkg);
    RETURN_STRING(ret)
}

PHP_METHOD(Pkg, get_name) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_name(intern->pkg);
    RETURN_STRING(ret)
}

PHP_METHOD(Pkg, get_optdepends) {
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
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_packager(intern->pkg);
    RETURN_STRING(ret)
}

PHP_METHOD(Pkg, get_provides) {
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
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_sha256sum(intern->pkg);
    RETURN_STRING(ret)
}

PHP_METHOD(Pkg, get_size) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    long ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_isize(intern->pkg);
    RETURN_LONG(ret)
}

PHP_METHOD(Pkg, get_url) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_url(intern->pkg);
    RETURN_STRING(ret)
}

PHP_METHOD(Pkg, get_version) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_version(intern->pkg);
    RETURN_STRING(ret)
}

PHP_METHOD(Pkg, set_reason) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_pkgreason_t reason;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &reason) == FAILURE) {
        RETURN_NULL()
    }

    if (reason != ALPM_PKG_REASON_DEPEND && reason != ALPM_PKG_REASON_EXPLICIT) {
        zend_throw_exception(php_alpm_pkg_exception_class_entry, "not a valid install reason", 0);
        RETURN_FALSE
    }

    err = alpm_pkg_set_reason(intern->pkg, reason);
    if (err == -1) {
        RETURN_FALSE
    }
    RETURN_TRUE
}