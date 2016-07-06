#include "transaction.h"

static zend_object_handlers transaction_object_handlers;

static zend_function_entry trans_methods[] = {

};

static void transaction_free_storage(zend_object *obj TSRMLS_DC) {
    trans_object *intern = alpm_trans_from_obj(obj);
    if (!intern) {
        return;
    }

    efree(intern);
}

zend_object *create_transaction_struct(zend_class_entry *class TSRMLS_DC) {
    trans_object *intern = ecalloc(1, sizeof(trans_object) + zend_object_properties_size(class));

    zend_object_std_init(&intern->std, class TSRMLS_CC);
    object_properties_init(&intern->std, class);
    transaction_object_handlers.offset = XtOffsetOf(trans_object, std);
    transaction_object_handlers.free_obj = transaction_free_storage;

    intern->std.handlers = &transaction_object_handlers;

    return &intern->std;
}

void alpm_init_transaction(TSRMLS_D) {
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "Transaction", trans_methods);
    alpm_ce_transaction = zend_register_internal_class(&ce TSRMLS_CC);

    ce.create_object = create_transaction_struct;
}