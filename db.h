#ifndef PHP_ALPM_DB_H
#define PHP_ALPM_DB_H

#include <alpm.h>

#include "php.h"
#include "php_alpm.h"

zend_class_entry *alpm_ce_db;

void alpm_init_db(TSRMLS_D);

PHP_METHOD(Db, __construct);

PHP_METHOD(Db, add_server);
PHP_METHOD(Db, get_grpcache);
PHP_METHOD(Db, get_name);
PHP_METHOD(Db, get_pkg);
PHP_METHOD(Db, get_pkgcache);
PHP_METHOD(Db, get_servers);
PHP_METHOD(Db, search);
PHP_METHOD(Db, read_grp);
PHP_METHOD(Db, remove_server);
PHP_METHOD(Db, update);

typedef struct _db_object {
    alpm_db_t *db;

    zend_object std;
} db_object;

static inline db_object *alpm_db_from_obj(zend_object *obj) {
    return (db_object *)((char *)(obj) - XtOffsetOf(db_object, std));
}

#define Z_DBO_P(zv) alpm_db_from_obj(Z_OBJ_P(zv))

zend_object *create_db_struct(zend_class_entry *ce TSRMLS_DC);
void free_alpm_db(void *object TSRMLS_DC);

#endif /* PHP_ALPM_DB_H */
