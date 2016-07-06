#ifndef PHP_ALPM_HANDLE_H
#define PHP_ALPM_HANDLE_H

#include "php.h"
#include "php_alpm.h"

zend_class_entry *alpm_ce_handle;

void alpm_init_handle(TSRMLS_D);

PHP_METHOD(Handle, __construct);

PHP_METHOD(Handle, add_cachedir);
PHP_METHOD(Handle, add_ignoregrp);
PHP_METHOD(Handle, add_ignorepkg);
PHP_METHOD(Handle, add_noextract);
PHP_METHOD(Handle, add_noupgrade);
PHP_METHOD(Handle, get_arch);
PHP_METHOD(Handle, get_cachedirs);
PHP_METHOD(Handle, get_checkspace);
PHP_METHOD(Handle, get_dbpath);
PHP_METHOD(Handle, get_ignoregrps);
PHP_METHOD(Handle, get_localdb);
PHP_METHOD(Handle, get_noextracts);
PHP_METHOD(Handle, get_noupgrades);
PHP_METHOD(Handle, get_syncdbs);
PHP_METHOD(Handle, init_transaction);
PHP_METHOD(Handle, load_pkg);
PHP_METHOD(Handle, register_syncdb);
PHP_METHOD(Handle, remove_cachedir);
PHP_METHOD(Handle, remove_ignoregrp);
PHP_METHOD(Handle, remove_ignorepkg);
PHP_METHOD(Handle, remove_noextract);
PHP_METHOD(Handle, remove_noupgrade);
PHP_METHOD(Handle, set_arch);
PHP_METHOD(Handle, set_checkspace);
PHP_METHOD(Handle, set_pkgreason);

typedef struct _handle_object {
    alpm_errno_t err;
    alpm_handle_t *handle;
    zend_object std;
} handle_object;

static inline handle_object *alpm_handle_from_obj(zend_object *obj) {
    return (handle_object *)((char*)(obj) - XtOffsetOf(handle_object, std));
}

#define Z_HANDLEO_P(zv) alpm_handle_from_obj(Z_OBJ_P(zv))

zend_object *create_handle_struct(zend_class_entry *class TSRMLS_DC);
void free_alpm_handle(void *object TSRMLS_DC);

#endif //PHP_ALPM_HANDLE_H
