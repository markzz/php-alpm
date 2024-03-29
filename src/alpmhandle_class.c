/*
 *  alpmhandle_class.c
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

PHP_METHOD(Handle, __construct) {
    char *rootpath;
    char *dbpath;
    size_t rp, dp;
    int errcode = 0;
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_handle_t *h;

    if (ZEND_NUM_ARGS() == 0) {
        rootpath = emalloc(sizeof(char) * strlen(DEFAULT_ROOTDIR));
        dbpath = emalloc(sizeof(char) * strlen(DEFAULT_DBPATH));

        strcpy(rootpath, DEFAULT_ROOTDIR);
        strcpy(dbpath, DEFAULT_DBPATH);

        goto create;
    }
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &rootpath, &rp, &dbpath, &dp) == FAILURE) {
        RETURN_NULL();
    }

    create:

    h = alpm_initialize(rootpath, dbpath, (alpm_errno_t*) &errcode);
    if (!h) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "unable to create handle object", 0);
        RETURN_NULL();
    }

    object_init_ex(return_value, php_alpm_handle_sc_entry);
    intern->handle = h;

    if (ZEND_NUM_ARGS() == 0) {
        efree(rootpath);
        efree(dbpath);
    }
}

PHP_METHOD(Handle, __toString) {
    /* (AlpmHandle: root=$root dbpath=$dbpath) */
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    const char *dbpath = NULL, *rootpath = NULL;
    char *tmp = NULL;
    size_t dbsize, rootsize;
    zend_string *ret;

    dbpath = alpm_option_get_dbpath(intern->handle);
    rootpath = alpm_option_get_root(intern->handle);

    dbsize = strlen(dbpath);
    rootsize = strlen(rootpath);

    tmp = (char*)emalloc(sizeof(char*) * (dbsize + rootsize + strlen("(AlpmHandle: root=") + strlen(" dbpath=") + strlen(")")));
    sprintf(tmp, "(AlpmHandle: root=%s dbpath=%s)", rootpath, dbpath);

    ret = zend_string_init(tmp, strlen(tmp), 0);
    efree(tmp);

    RETURN_STR(ret);
}

PHP_METHOD(Handle, add_architecture) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error",  0);
        RETURN_NULL();
    }

    err = alpm_option_add_architecture(intern->handle, arg);
    if (err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, add_assumeinstalled) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg1;
    size_t arg1_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg1, &arg1_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm hendle error", 0);
        RETURN_NULL();
    }

    alpm_depend_t *dep = alpm_dep_from_string(arg1);
    err = alpm_option_add_assumeinstalled(intern->handle, dep);
    alpm_dep_free(dep);

    if (err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, add_cachedir) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error",  0);
        RETURN_NULL();
    }

    err = alpm_option_add_cachedir(intern->handle, arg);
    if (err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, add_hookdir) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_add_hookdir(intern->handle, arg);
    if (err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, add_ignoregrp) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_add_ignoregroup(intern->handle, arg);
    if (err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, add_ignorepkg) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_add_ignorepkg(intern->handle, arg);
    if (err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, add_noextract) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_add_noextract(intern->handle, arg);
    if (err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, add_noupgrade) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_add_noupgrade(intern->handle, arg);
    if (err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, get_architectures) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_arch() deprecated, use AlpmHandle->architectures instead");

    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    list = alpm_option_get_architectures(intern->handle);
    if (list == NULL) {
        RETURN_NULL();
    }

    alpm_list_to_zval(list, return_value);
}

PHP_METHOD(Handle, get_cachedirs) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_cachedirs() deprecated, use AlpmHandle->cachedirs instead");

    php_alpm_handle_object *intern;
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    intern = Z_HANDLEO_P(getThis());

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    list = alpm_option_get_cachedirs(intern->handle);
    if (list == NULL) {
        RETURN_NULL();
    }

    alpm_list_to_zval(list, return_value);
}

PHP_METHOD(Handle, get_checkspace) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_checkspace() deprecated, use AlpmHandle->checkspace instead");

    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    int check_space;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    check_space = alpm_option_get_checkspace(intern->handle);
    RETURN_LONG((long)check_space);
}

PHP_METHOD(Handle, get_dbpath) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_dbpath() deprecated, use AlpmHandle->dbpath instead");

    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    const char *dbpath;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    dbpath = alpm_option_get_dbpath(intern->handle);
    if (dbpath == NULL) {
        RETURN_NULL();
    }

    RETURN_STRING(dbpath);
}

PHP_METHOD(Handle, get_ignoregrps) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_ignoregrps() deprecated, use AlpmHandle->ignoregrps instead");

    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    list = alpm_option_get_ignoregroups(intern->handle);
    if (list == NULL) {
        RETURN_NULL();
    }

    alpm_list_to_zval(list, return_value);
}

PHP_METHOD(Handle, get_ignorepkgs) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_ignorepkgs() deprecated, use AlpmHandle->ignorepkgs instead");

    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    list = alpm_option_get_ignorepkgs(intern->handle);
    if (list == NULL) {
        RETURN_NULL();
    }

    alpm_list_to_zval(list, return_value);
}

PHP_METHOD(Handle, get_localdb) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    php_alpm_db_object *new_obj;
    alpm_db_t *db;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    db = alpm_get_localdb(intern->handle);
    if (!db) {
        RETURN_NULL();
    }

    object_init_ex(return_value, php_alpm_db_sc_entry);
    new_obj = Z_DBO_P(return_value);
    new_obj->db = db;
    new_obj->handle = intern->handle;
}

PHP_METHOD(Handle, get_noextracts) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_noextracts() deprecated, use AlpmHandle->noextracts instead");

    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    list = alpm_option_get_noextracts(intern->handle);
    if (list == NULL) {
        RETURN_NULL();
    }

    alpm_list_to_zval(list, return_value);
}

PHP_METHOD(Handle, get_noupgrades) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->get_noupgrades() deprecated, use AlpmHandle->noupgrades instead");

    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    list = alpm_option_get_noupgrades(intern->handle);
    if (list == NULL) {
        RETURN_NULL();
    }

    alpm_list_to_zval(list, return_value);
}

PHP_METHOD(Handle, get_syncdbs) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_list_t *db_list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    db_list = alpm_get_syncdbs(intern->handle);
    if (db_list == NULL) {
        RETURN_NULL();
    }

    alpm_list_to_db_array(intern->handle, db_list, return_value);
}

#define FLAGS(a) &(a)[0], &(a)[1], &(a)[2], &(a)[3], &(a)[4], &(a)[5], &(a)[6], &(a)[8], &(a)[9], \
&(a)[10], &(a)[11], &(a)[13], &(a)[14], &(a)[15], &(a)[16], &(a)[17]

PHP_METHOD(Handle, init_transaction) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    zend_bool flags[18] = {0};
    int flag_int = 0;
    int i, ret;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|bbbbbbbbbbbbbbbb", FLAGS(flags)) == FAILURE) {
        RETURN_NULL();
    }

    for (i = 0; i < 18; i++) {
        if (flags[i]) {
            flag_int |= 1U << i;
        }
    }
    ret = alpm_trans_init(intern->handle, (alpm_transflag_t) flag_int);

    if (ret == -1) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, alpm_strerror(alpm_errno(intern->handle)), alpm_errno(intern->handle));
        RETURN_NULL();
    }

    php_alpm_transaction_object *to;
    object_init_ex(return_value, php_alpm_transaction_sc_entry);
    to = Z_TRANSO_P(return_value);
    to->handle = intern->handle;
}

PHP_METHOD(Handle, load_pkg) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    php_alpm_pkg_object *new_obj;
    alpm_pkg_t *pkg;
    char *fn;
    size_t fn_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &fn, &fn_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_pkg_load(intern->handle, fn, 1, ALPM_SIG_PACKAGE_OPTIONAL, &pkg);
    if (err) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "could not load pkg", 0);
        RETURN_NULL();
    }

    object_init_ex(return_value, php_alpm_pkg_sc_entry);
    new_obj = Z_PKGO_P(return_value);
    new_obj->pkg = pkg;
}

PHP_METHOD(Handle, register_syncdb) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    php_alpm_db_object *new_obj;
    alpm_db_t *db;
    char *dbname;
    size_t *dbname_size;
    long pgp_level;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sl", &dbname, &dbname_size, &pgp_level) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    db = alpm_register_syncdb(intern->handle, dbname, (alpm_siglevel_t) pgp_level);
    if (!db) {
        RETURN_NULL();
    }

    object_init_ex(return_value, php_alpm_db_sc_entry);
    new_obj = Z_DBO_P(return_value);
    new_obj->db = db;
    new_obj->handle = intern->handle;
}

PHP_METHOD(Handle, remove_architecture) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_remove_architecture(intern->handle, arg);
    if (!err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, remove_assumeinstalled) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_depend_t *dep = NULL, *to_rm = NULL;
    alpm_list_t *lp = NULL, *tmp;
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    lp = alpm_option_get_assumeinstalled(intern->handle);
    if (lp != NULL) {
        for (tmp = lp; tmp; tmp = tmp->next) {
            dep = tmp->data;
            if (strcmp(dep->name, arg) == 0) {
                to_rm = dep;
                break;
            }
        }
    }

    if (to_rm != NULL) {
        err = alpm_option_remove_assumeinstalled(intern->handle, to_rm);
        if (!err) {
            RETURN_FALSE;
        }
    } else {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, remove_cachedir) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_remove_cachedir(intern->handle, arg);
    if (!err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, remove_hookdir) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_remove_hookdir(intern->handle, arg);
    if (!err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, remove_ignoregrp) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_remove_ignoregroup(intern->handle, arg);
    if (!err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, remove_ignorepkg) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_remove_ignorepkg(intern->handle, arg);
    if (!err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, remove_noextract) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_remove_noextract(intern->handle, arg);
    if (!err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, remove_noupgrade) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_remove_noupgrade(intern->handle, arg);
    if (!err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(Handle, set_checkspace) {
    php_error(E_DEPRECATED, "(removed in 1.0) AlpmHandle->set_checkspace() deprecated, set AlpmHandle->checkspace instead");

    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis()) ;
    long checkspace;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &checkspace) == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL();
    }

    err = alpm_option_set_checkspace(intern->handle, (int)checkspace);
    if (err) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}
