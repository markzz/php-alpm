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
    alpm_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Pkg, get_base64_sig) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_base64_sig(intern->pkg);
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
    alpm_list_to_pkg_array(list, return_value);
    return;
}

PHP_METHOD(Pkg, get_db) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_depends) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    list = alpm_pkg_get_depends(intern->pkg);
    alpm_list_to_pkg_array(list, return_value);
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
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_groups) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_has_scriptlet) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_installdate) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_isize) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_licenses) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_md5sum) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_name) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_optdepends) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_packager) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_provides) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_reason) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_replaces) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_sha256sum) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_size) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_url) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Pkg, get_version) {
    /* implement */
    RETURN_NULL()
}