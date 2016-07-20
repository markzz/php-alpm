#include "php_alpm.h"
#include "php_alpm_defs.h"
#include "php_alpm_helpers.h"

PHP_METHOD(Db, add_server) {
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->db) {
        zend_throw_error(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    err = alpm_db_add_server(intern->db, arg);
    if (err) {
        zend_throw_error(php_alpm_db_exception_class_entry, "could not add server", 0);
        RETURN_NULL()
    }

    RETURN_NULL()
}

PHP_METHOD(Db, get_grpcache) {
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    alpm_list_t *list = NULL;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->db) {
        zend_throw_error(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    list = alpm_db_get_groupcache(intern->db);
    if (list == NULL) {
        zend_throw_error(php_alpm_db_exception_class_entry, "could not get group cache", 0);
        RETURN_NULL()
    }

    alpm_group_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Db, get_name) {
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    const char *name;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->db) {
        zend_throw_error(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    name = alpm_db_get_name(intern->db);
    if (name == NULL) {
        zend_throw_error(php_alpm_db_exception_class_entry, "could not get db name", 0);
        RETURN_NULL()
    }

    RETURN_STRING(name)
}

PHP_METHOD(Db, get_pkg) {
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    php_alpm_pkg_object *new_obj;
    char *arg;
    size_t *arg_size;
    alpm_pkg_t *pkg;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->db) {
        zend_throw_error(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    pkg = alpm_db_get_pkg(intern->db, arg);
    if (pkg == NULL) {
        zend_throw_error(php_alpm_db_exception_class_entry, "could not create pkg object", 0);
        RETURN_NULL()
    }

    object_init_ex(return_value, php_alpm_pkg_sc_entry);
    new_obj = Z_PKGO_P(return_value);
    new_obj->pkg = pkg;
    return;
}

PHP_METHOD(Db, get_pkgcache) {
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->db) {
        zend_throw_error(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    list = alpm_db_get_pkgcache(intern->db);
    if (list == NULL) {
        zend_throw_error(php_alpm_db_exception_class_entry, "could not get pkg cache", 0);
        RETURN_NULL()
    }

    alpm_list_to_pkg_array(list, return_value);
    return;
}

PHP_METHOD(Db, get_servers) {
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->db) {
        zend_throw_error(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    list = alpm_db_get_servers(intern->db);
    if (list == NULL) {
        zend_throw_error(php_alpm_db_exception_class_entry, "could not get server list", 0);
        RETURN_NULL()
    }

    alpm_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Db, search) {
    /* implement */
    RETURN_NULL()
}

PHP_METHOD(Db, read_grp) {
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    char *grpname;
    size_t grpname_size;
    alpm_group_t *grp;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &grpname, &grpname_size) == FAILURE) {
        RETURN_NULL()
    }

    grp = alpm_db_get_group(intern->db, grpname);
    if (grp == NULL) {
        zend_throw_error(php_alpm_db_exception_class_entry, "could not get group information", 0);
        RETURN_NULL()
    }

    alpm_group_to_zval(grp, return_value);
}

PHP_METHOD(Db, remove_server) {
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    err = alpm_db_remove_server(intern->db, arg);
    if (err) {
        zend_throw_error(php_alpm_db_exception_class_entry, "could not remove server", 0);
        RETURN_NULL()
    }

    RETURN_NULL()
}

PHP_METHOD(Db, update) {
    /* implement */
    RETURN_NULL()
}