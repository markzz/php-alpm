#include "db.h"
#include "pkg.h"
#include "util.h"

static zend_object_handlers db_object_handlers;

static zend_function_entry db_methods[] = {
    PHP_ME(Db, __construct,    NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)

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

    alpm_db_unregister(intern->db);
    efree(intern);
}

zend_object *create_db_struct(zend_class_entry *ce TSRMLS_DC) {
    db_object *intern = ecalloc(1, sizeof(db_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);
    db_object_handlers.offset = XtOffsetOf(db_object, std);
    db_object_handlers.free_obj = db_free_storage;

    intern->std.handlers = &db_object_handlers;

    return &intern->std;
}

void alpm_init_db(TSRMLS_D) {
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "Db", db_methods);
    alpm_ce_db = zend_register_internal_class(&ce TSRMLS_CC);

    ce.create_object = create_db_struct;
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
    alpm_list_t *list;
    db_object *intern = Z_DBO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    list = alpm_db_get_groupcache(intern->db);
    alpm_list_to_zval(list, return_value);
    alpm_list_free(list);
    return;
}

PHP_METHOD(Db, get_name) {
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
        RETURN_NULL()
    }
    db_object *intern = Z_DBO_P(getThis());
    RETURN_STRING(alpm_db_get_name(intern->db))
}

PHP_METHOD(Db, get_pkg) {
    char *pkgname;
    int *pkgname_int;
    pkg_object *pkg;
    db_object *db = Z_DBO_P(getThis());

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pkgname, &pkgname_int) == FAILURE) {
        RETURN_NULL()
    }

    object_init_ex(return_value, alpm_ce_pkg);
    pkg = Z_PKGO_P(return_value);
    pkg->pkg = alpm_db_get_pkg(db->db, pkgname);
}

PHP_METHOD(Db, get_pkgcache) {
    db_object *db = Z_DBO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    alpm_list_to_zval(alpm_db_get_pkgcache(db->db), return_value);
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
    alpm_list_t *list = NULL;
    db_object *db = Z_DBO_P(getThis());
    zval *arr;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {
        RETURN_NULL()
    }

    zval_to_alpm_list(arr, list);
    alpm_list_to_zval(alpm_db_search(db->db, list), return_value);
    return;
}

PHP_METHOD(Db, read_grp) {
    db_object *db = Z_DBO_P(getThis());
    char *name;
    size_t n_size;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &n_size) == FAILURE) {
        RETURN_NULL()
    }

    alpm_group_to_zval(alpm_db_get_group(db->db, name), return_value);
    return;
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