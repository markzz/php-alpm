#include "db.h"
#include "pkg.h"
#include "util.h"

static zend_object_handlers db_object_handlers;

static zend_function_entry db_methods[] = {
    /* PHP_ME(Db, __construct,    NULL, ZEND_ACC_PRIVATE|ZEND_ACC_CTOR) */

    PHP_ME(Db, add_server,     NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Db, get_grpcache,   NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Db, get_name,       NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Db, get_pkg,        NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Db, get_pkgcache,   NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Db, get_servers,    NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Db, search,         NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Db, read_grp,       NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Db, remove_server,  NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Db, update,         NULL, ZEND_ACC_PUBLIC)

    {NULL, NULL, NULL}
};

static void db_free_storage(zend_object *obj TSRMLS_DC) {
    db_object *intern = alpm_db_from_obj(obj);
    if (!intern) {
        return;
    }

    if (intern->db) {
//        intern->db = NULL;
    }

    zend_object_std_dtor(&intern->std TSRMLS_CC);
    efree(intern);
}

static zend_object *create_db_struct(zend_class_entry *ce TSRMLS_DC) {
    db_object *intern = ecalloc(1, sizeof(db_object) + sizeof(zval) * (ce->default_properties_count - 1));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->db = NULL;
    intern->std.handlers = &db_object_handlers;

    return &intern->std;
}

void alpm_init_db(TSRMLS_DC) {
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "AlpmDb", db_methods);
    alpm_ce_db = zend_register_internal_class(&ce TSRMLS_CC);

    ce.create_object = create_db_struct;

    memcpy(&db_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    db_object_handlers.offset = XtOffsetOf(db_object, std);
    db_object_handlers.free_obj = db_free_storage;
}

static void create_pkg_object(zval *pzval, alpm_pkg_t *pkg TSRMLS_DC) {
    pkg_object *p;

    object_init_ex(pzval, alpm_ce_pkg);
    p = Z_PKGO_P(pzval);
    p->pkg = pkg;
}

#define DB_ERROR() if (!intern->db) { \
    zend_throw_error(php_alpm_db_exception_class_entry, "alpm database error", 0); \
    RETURN_NULL() \
}

PHP_METHOD(Db, __construct) {
    php_printf("WARN: You need to create a Db object through Handle->get_localdb() or Handle->register_syncdb!");
    RETURN_NULL()
}

PHP_METHOD(Db, add_server) {
    char *url;
    size_t url_size;
    db_object *intern = Z_DBO_P(getThis());

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &url, &url_size) == FAILURE) {
        RETURN_NULL()
    }

    alpm_db_add_server(intern->db, url);
    RETURN_NULL()
}

PHP_METHOD(Db, get_grpcache) {
    db_object *intern = Z_DBO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    DB_ERROR()

    alpm_group_list_to_zval(alpm_db_get_groupcache(intern->db), return_value);
    return;
}

PHP_METHOD(Db, get_name) {
    db_object *intern = Z_DBO_P(getThis());
    const char *name;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    if (!intern->db) {
        zend_throw_error(php_alpm_db_exception_class_entry, "alpm database error", 0);
        RETURN_NULL()
    }

    name = alpm_db_get_name(intern->db);
    if (name == NULL) {
        RETURN_NULL()
    }

    RETURN_STRING(name)
}

PHP_METHOD(Db, get_pkg) {
    char *pkgname;
    size_t pkgname_size;
    alpm_pkg_t *pkg;
    alpm_db_t *db;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &pkgname, &pkgname_size) == FAILURE) {
        RETURN_NULL()
    }

    db_object *dbo = Z_DBO_P(getThis());
    db = dbo->db;

    if (db == NULL) {
        zend_throw_error(php_alpm_db_exception_class_entry, "alpm database error", 0);
        RETURN_NULL()
    }

    pkg = alpm_db_get_pkg(db, pkgname);

    if (pkg == NULL) {
        zend_throw_error(php_alpm_pkg_exception_class_entry, "alpm pkg error", 0);
        RETURN_NULL()
    }

    object_init_ex(return_value, alpm_ce_pkg);
    pkg_object *pko = Z_PKGO_P(return_value);
    pko->pkg = pkg;
    php_log_err(alpm_pkg_get_name(pko->pkg));

    /* this is some horrible, horrible hacking here,
     * if a kind soul wants to fix this please do so. */
//    dbo->db = db;
    return;
}

PHP_METHOD(Db, get_pkgcache) {
    db_object *dbo = Z_DBO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }


    if (!dbo->db) {
        zend_throw_error(php_alpm_db_exception_class_entry, "alpm database error", 0);
        RETURN_NULL()
    }
    alpm_db_t *db_ptr = dbo->db;

    alpm_list_to_pkg_array(alpm_db_get_pkgcache(db_ptr), return_value);
    return;
}

PHP_METHOD(Db, get_servers) {
    db_object *db = Z_DBO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_db_get_servers(db->db), return_value);
    return;
}

PHP_METHOD(Db, search) {
    /* TODO: FIX THIS METHOD */

    alpm_list_t *list = NULL;
    db_object *db = Z_DBO_P(getThis());
    zval *arr;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &arr) == FAILURE) {
        RETURN_NULL()
    }

    zval_to_alpm_list(arr, list);
    alpm_list_to_zval(alpm_db_search(db->db, list), return_value);
    alpm_list_free(list);
    return;
}

PHP_METHOD(Db, read_grp) {
    db_object *self = Z_DBO_P(getThis());
    char *grpname;
    size_t grpname_size;
    alpm_group_t *grp;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &grpname, &grpname_size) == FAILURE) {
        RETURN_NULL()
    }

    grp = alpm_db_get_group(self->db, grpname);
    alpm_group_to_zval(grp, return_value);
//    db_object *dbo = Z_DBO_P(getThis());
//    alpm_db_t *alpm_db;
//    char *name;
//    size_t n_size;
//
//    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &n_size) == FAILURE) {
//        RETURN_NULL()
//    }
//
//    if (dbo->db == NULL) {
//        zend_throw_error(php_alpm_db_exception_class_entry, "alpm database error", 0);
//        RETURN_NULL()
//    }
//
//    alpm_db = dbo->db;
//
//    alpm_group_to_zval(alpm_db_get_group(dbo->db, name), return_value);
//    return;
}

PHP_METHOD(Db, remove_server) {
    char *server;
    size_t server_size;
    db_object *intern = Z_DBO_P(getThis());

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &server, &server_size) == FAILURE) {
        RETURN_NULL()
    }

    alpm_db_remove_server(intern->db, server);
    RETURN_NULL()
}

PHP_METHOD(Db, update) {
    long force;
    db_object *intern = Z_DBO_P(getThis());

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &force) == FAILURE) {
        RETURN_NULL()
    }

    alpm_db_update((int)force, intern->db);
    RETURN_NULL()
}