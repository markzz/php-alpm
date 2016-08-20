/*
 *  alpmdb_class.c
 *
 *  Copyright (c) 2016 Mark Weiman <contact@markzz.net>
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

PHP_METHOD(Db, __toString) {
    /* $dbname */
    /* This is essentially the same as calling get_name() */
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    RETURN_STRING(alpm_db_get_name(intern->db))
}

PHP_METHOD(Db, add_server) {
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->db) {
        zend_throw_exception(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    err = alpm_db_add_server(intern->db, arg);
    if (err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Db, get_grpcache) {
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    alpm_list_t *list = NULL;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->db) {
        zend_throw_exception(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    list = alpm_db_get_groupcache(intern->db);
    if (list == NULL) {
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
        zend_throw_exception(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    name = alpm_db_get_name(intern->db);
    if (name == NULL) {
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
        zend_throw_exception(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    pkg = alpm_db_get_pkg(intern->db, arg);
    if (pkg == NULL) {
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
        zend_throw_exception(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    list = alpm_db_get_pkgcache(intern->db);
    if (list == NULL) {
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
        zend_throw_exception(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    list = alpm_db_get_servers(intern->db);
    if (list == NULL) {
        RETURN_NULL()
    }

    alpm_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Db, search) {
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    zval *arr;
    alpm_list_t *list = NULL, *result = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &arr) == FAILURE) {
        RETURN_NULL()
    }

    zval_to_alpm_list(arr, &list);
    result = alpm_db_search(intern->db, list);
    if (!result) {
        RETURN_NULL()
    }

    alpm_list_to_pkg_array(result, return_value);
    return;
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
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Db, update) {
    php_alpm_db_object *intern = Z_DBO_P(getThis());
    zend_bool force = 0;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|b", &force) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->db) {
        zend_throw_exception(php_alpm_db_exception_class_entry, "alpm db error", 0);
        RETURN_NULL()
    }

    err = alpm_db_update(force, intern->db);
    if (err == 1) {
        RETURN_FALSE
    } else if (err == 0) {
        RETURN_TRUE
    } else if (err == -1) {
        zend_throw_exception(php_alpm_db_exception_class_entry, "could not update database (most likely no permissions)", 0);
        RETURN_FALSE
    }
}