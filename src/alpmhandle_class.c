#include "php_alpm.h"
#include "php_alpm_defs.h"
#include "php_alpm_helpers.h"

PHP_METHOD(Handle, __construct) {
    char *rootpath;
    char *dbpath;
    size_t rp, dp;
    enum _alpm_errno_t errcode = 0;
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_handle_t *h;

    if (ZEND_NUM_ARGS() == 0) {
        rootpath = emalloc(sizeof(char) * strlen(DEFAULT_ROOTDIR));
        dbpath = emalloc(sizeof(char) * strlen(DEFAULT_DBPATH));

        strcpy(rootpath, DEFAULT_ROOTDIR);
        strcpy(dbpath, DEFAULT_DBPATH);

        goto create;
    }
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &rootpath, &rp, &dbpath, &dp) == FAILURE) {
        RETURN_NULL()
    }

    create:

    h = alpm_initialize(rootpath, dbpath, &errcode);
    if (!h) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "unable to create handle object", 0);
        RETURN_NULL()
    }

    object_init_ex(return_value, php_alpm_handle_sc_entry);
    intern->handle = h;

    if (ZEND_NUM_ARGS() == 0) {
        efree(rootpath);
        efree(dbpath);
    }
}

PHP_METHOD(Handle, add_cachedir) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error",  0);
        RETURN_NULL()
    }

    err = alpm_option_add_cachedir(intern->handle, arg);
    if (err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Handle, add_ignoregrp) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    err = alpm_option_add_ignoregroup(intern->handle, arg);
    if (err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Handle, add_ignorepkg) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    err = alpm_option_add_ignorepkg(intern->handle, arg);
    if (err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Handle, add_noextract) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    err = alpm_option_add_noextract(intern->handle, arg);
    if (err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Handle, add_noupgrade) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    err = alpm_option_add_noupgrade(intern->handle, arg);
    if (err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Handle, get_arch) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    const char *arch;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    arch = alpm_option_get_arch(intern->handle);
    if (arch == NULL) {
        RETURN_NULL()
    }

    RETURN_STRING(arch)
}

PHP_METHOD(Handle, get_cachedirs) {
    php_alpm_handle_object *intern;
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    intern = Z_HANDLEO_P(getThis());

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    list = alpm_option_get_cachedirs(intern->handle);
    if (list == NULL) {
        RETURN_NULL()
    }

    alpm_list_to_zval(list, return_value);
}

PHP_METHOD(Handle, get_checkspace) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    int check_space;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    check_space = alpm_option_get_checkspace(intern->handle);
    RETURN_LONG((long)check_space)
}

PHP_METHOD(Handle, get_dbpath) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    const char *dbpath;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    dbpath = alpm_option_get_dbpath(intern->handle);
    if (dbpath == NULL) {
        RETURN_NULL()
    }

    RETURN_STRING(dbpath)
}

PHP_METHOD(Handle, get_ignoregrps) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    list = alpm_option_get_ignoregroups(intern->handle);
    if (list == NULL) {
        RETURN_NULL()
    }

    alpm_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Handle, get_ignorepkgs) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    list = alpm_option_get_ignorepkgs(intern->handle);
    if (list == NULL) {
        RETURN_NULL()
    }

    alpm_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Handle, get_localdb) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    php_alpm_db_object *new_obj;
    alpm_db_t *db;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    db = alpm_get_localdb(intern->handle);
    if (!db) {
        RETURN_NULL()
    }

    object_init_ex(return_value, php_alpm_db_sc_entry);
    new_obj = Z_DBO_P(return_value);
    new_obj->db = db;
    return;
}

PHP_METHOD(Handle, get_noextracts) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    list = alpm_option_get_noextracts(intern->handle);
    if (list == NULL) {
        RETURN_NULL()
    }

    alpm_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Handle, get_noupgrades) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_list_t *list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    list = alpm_option_get_noupgrades(intern->handle);
    if (list == NULL) {
        RETURN_NULL()
    }

    alpm_list_to_zval(list, return_value);
    return;
}

PHP_METHOD(Handle, get_syncdbs) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    alpm_list_t *db_list;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    db_list = alpm_get_syncdbs(intern->handle);
    if (db_list == NULL) {
        RETURN_NULL()
    }

    alpm_list_to_db_array(db_list, return_value);
    return;
}

#define FLAGS(a) a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[8], a[9], \
a[10], a[11], a[13], a[14], a[15], a[16], a[17]

PHP_METHOD(Handle, init_transaction) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    zend_bool flags[18] = {0};
    alpm_transflag_t flag_int = 0;
    int i, ret;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|bbbbbbbbbbbbbbbb", FLAGS(flags)) == FAILURE) {
        RETURN_NULL()
    }

    for (i = 0; i < 18; i++) {
        if (flags[i]) {
            flag_int |= 1U << i;
        }
    }
    ret = alpm_trans_init(intern->handle, flag_int);

    if (ret == -1) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "unable to initialize transaction", 0);
        RETURN_NULL()
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
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    err = alpm_pkg_load(intern->handle, fn, 1, ALPM_SIG_PACKAGE_OPTIONAL, &pkg);
    if (err) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "could not load pkg", 0);
        RETURN_NULL()
    }

    object_init_ex(return_value, php_alpm_pkg_sc_entry);
    new_obj = Z_PKGO_P(return_value);
    new_obj->pkg = pkg;
    return;
}

PHP_METHOD(Handle, register_syncdb) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    php_alpm_db_object *new_obj;
    alpm_db_t *db;
    char *dbname;
    size_t *dbname_size;
    long pgp_level;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sl", &dbname, &dbname_size, &pgp_level) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    db = alpm_register_syncdb(intern->handle, dbname, pgp_level);
    if (!db) {
        RETURN_NULL()
    }

    object_init_ex(return_value, php_alpm_db_sc_entry);
    new_obj = Z_DBO_P(return_value);
    new_obj->db = db;
    return;
}

PHP_METHOD(Handle, remove_cachedir) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    err = alpm_option_remove_cachedir(intern->handle, arg);
    if (!err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Handle, remove_ignoregrp) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    err = alpm_option_remove_ignoregroup(intern->handle, arg);
    if (!err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Handle, remove_ignorepkg) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    err = alpm_option_remove_ignorepkg(intern->handle, arg);
    if (!err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Handle, remove_noextract) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    err = alpm_option_remove_noextract(intern->handle, arg);
    if (!err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Handle, remove_noupgrade) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    err = alpm_option_remove_noupgrade(intern->handle, arg);
    if (!err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Handle, set_arch) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    size_t *arg_size;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_size) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    err = alpm_option_set_arch(intern->handle, arg);
    if (err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}

PHP_METHOD(Handle, set_checkspace) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis()) ;
    long checkspace;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &checkspace) == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->handle) {
        zend_throw_exception(php_alpm_handle_exception_class_entry, "alpm handle error", 0);
        RETURN_NULL()
    }

    err = alpm_option_set_checkspace(intern->handle, (int)checkspace);
    if (err) {
        RETURN_FALSE
    }

    RETURN_TRUE
}
