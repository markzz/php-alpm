#include "pkg.h"
#include "db.h"
#include "util.h"

static zend_object_handlers pkg_object_handlers;

static zend_function_entry pkg_methods[] = {
    /* TODO: For some reason this function is already declared, find out why? */
    /* PHP_ME(Pkg, __construct,        NULL, ZEND_ACC_PRIVATE|ZEND_ACC_CTOR) */

    PHP_ME(Pkg, compute_requiredby, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_arch,           NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_backup,         NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_base64_sig,     NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_builddate,      NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_conflicts,      NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_db,             NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_depends,        NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_desc,           NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_download_size,  NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_filename,       NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_files,          NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_groups,         NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_has_scriptlet,  NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_installdate,    NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_isize,          NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_licenses,       NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_md5sum,         NULL, ZEND_ACC_PUBLIC)
    /* TODO: For some reason this function is already declared, find out why? Use AlpmPkg::pkgname instead. */
    /* PHP_ME(Pkg, get_name,           NULL, ZEND_ACC_PUBLIC) */
    PHP_ME(Pkg, get_optdepends,     NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_packager,       NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_pkgname,        NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_provides,       NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_reason,         NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_replaces,       NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_sha256sum,      NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_size,           NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_url,            NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_version,        NULL, ZEND_ACC_PUBLIC)
};

static void pkg_free_storage(zend_object *obj TSRMLS_DC) {
    pkg_object *intern = alpm_pkg_from_obj(obj);
    if (!intern) {
        return;
    }

    alpm_pkg_free(intern->pkg);
    efree(intern);
}

zend_object *create_pkg_struct(zend_class_entry *class TSRMLS_DC) {
    pkg_object *intern = ecalloc(1, sizeof(pkg_object) + zend_object_properties_size(class));

    zend_object_std_init(&intern->std, class TSRMLS_CC);
    object_properties_init(&intern->std, class);
    pkg_object_handlers.offset = XtOffsetOf(pkg_object, std);
    pkg_object_handlers.free_obj = pkg_free_storage;

    intern->std.handlers = &pkg_object_handlers;

    return &intern->std;
}

void alpm_init_pkg(TSRMLS_D) {
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "AlpmPkg", pkg_methods);
    alpm_ce_pkg = zend_register_internal_class(&ce TSRMLS_CC);

    ce.create_object = create_pkg_struct;
}

PHP_METHOD(Pkg, __construct) {
    RETURN_NULL()
}

PHP_METHOD(Pkg, compute_requiredby) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_pkg_compute_requiredby(intern->pkg), return_value);
    return;
}

PHP_METHOD(Pkg, get_arch) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_STRING(alpm_pkg_get_arch(intern->pkg));
}

PHP_METHOD(Pkg, get_backup) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_pkg_get_backup(intern->pkg), return_value);
    return;
}

PHP_METHOD(Pkg, get_base64_sig) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_STRING(alpm_pkg_get_base64_sig(intern->pkg));
}

PHP_METHOD(Pkg, get_builddate) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_LONG((long)alpm_pkg_get_builddate(intern->pkg));
}

PHP_METHOD(Pkg, get_conflicts) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_pkg_get_conflicts(intern->pkg), return_value);
    return;
}

PHP_METHOD(Pkg, get_db) {
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
        RETURN_NULL()
    }

    pkg_object *intern = Z_PKGO_P(getThis());
    db_object *db;
    object_init_ex(return_value, alpm_ce_db);
    db = Z_DBO_P(return_value);
    db->db = alpm_pkg_get_db(intern->pkg);
}

PHP_METHOD(Pkg, get_depends) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_pkg_get_depends(intern->pkg), return_value);
    return;
}

PHP_METHOD(Pkg, get_desc) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_STRING(alpm_pkg_get_desc(intern->pkg));
}

PHP_METHOD(Pkg, get_download_size) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_LONG((long)alpm_pkg_download_size(intern->pkg))
}

PHP_METHOD(Pkg, get_filename) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_STRING(alpm_pkg_get_filename(intern->pkg))
}

PHP_METHOD(Pkg, get_files) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_filelist_to_zval(alpm_pkg_get_files(intern->pkg), return_value);
    return;
}

PHP_METHOD(Pkg, get_groups) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_pkg_get_groups(intern->pkg), return_value);
    return;
}

PHP_METHOD(Pkg, get_has_scriptlet) {
    pkg_object *intern = Z_PKGO_P(getThis());
    int b;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (alpm_pkg_has_scriptlet(intern->pkg) != 0) {
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}

PHP_METHOD(Pkg, get_installdate) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_LONG((long)alpm_pkg_get_installdate(intern->pkg))
}

PHP_METHOD(Pkg, get_isize) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_LONG(alpm_pkg_get_isize(intern->pkg))
}

PHP_METHOD(Pkg, get_licenses) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_pkg_get_licenses(intern->pkg), return_value);
    return;
}

PHP_METHOD(Pkg, get_md5sum) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_STRING(alpm_pkg_get_md5sum(intern->pkg))
}

PHP_METHOD(Pkg, get_pkgname) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_STRING(alpm_pkg_get_name(intern->pkg))
}

PHP_METHOD(Pkg, get_optdepends) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_pkg_get_optdepends(intern->pkg), return_value);
    return;
}

PHP_METHOD(Pkg, get_packager) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_STRING(alpm_pkg_get_packager(intern->pkg))
}

PHP_METHOD(Pkg, get_provides) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_pkg_get_provides(intern->pkg), return_value);
    return;
}

PHP_METHOD(Pkg, get_reason) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_LONG((long)alpm_pkg_get_reason(intern->pkg))
}

PHP_METHOD(Pkg, get_replaces) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_pkg_get_replaces(intern->pkg), return_value);
    return;
}

PHP_METHOD(Pkg, get_sha256sum) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_STRING(alpm_pkg_get_sha256sum(intern->pkg))
}

PHP_METHOD(Pkg, get_size) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_LONG((long)alpm_pkg_get_size(intern->pkg))
}

PHP_METHOD(Pkg, get_url) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_STRING(alpm_pkg_get_url(intern->pkg))
}

PHP_METHOD(Pkg, get_version) {
    pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    RETURN_STRING(alpm_pkg_get_version(intern->pkg))
}
