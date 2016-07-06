#ifndef PHP_ALPM_TRANSACTION_H
#define PHP_ALPM_TRANSACTION_H

#include "php.h"
#include "php_alpm.h"

zend_class_entry *alpm_ce_transaction;

void alpm_init_transaction(TSRMLS_DC);

PHP_METHOD(Transaction, add_pkg);
PHP_METHOD(Transaction, commit);
PHP_METHOD(Transaction, interrupt);
PHP_METHOD(Transaction, prepare);
PHP_METHOD(Transaction, release);
PHP_METHOD(Transaction, remove_pkg);
PHP_METHOD(Transaction, sysupgrade);

typedef struct _trans_object {
    alpm_handle_t *handle;
    zend_object std;
} trans_object;

static inline trans_object *alpm_trans_from_obj(zend_object *obj) {
    return (trans_object *)((char*)(obj) - XtOffsetOf(trans_object, std));
}

#define Z_TRANSO_P(zv) alpm_trans_from_obj(Z_OBJ_P(zv))

#endif //PHP_ALPM_TRANSACTION_H
