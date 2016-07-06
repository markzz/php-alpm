#ifndef PHP_ALPM_PKG_H
#define PHP_ALPM_PKG_H

#include "php.h"
#include "php_alpm.h"

zend_class_entry *alpm_ce_pkg;

void alpm_init_pkg(TSRMLS_D);

PHP_METHOD(Pkg, __construct);

PHP_METHOD(Pkg, compute_requiredby);
PHP_METHOD(Pkg, get_arch);
PHP_METHOD(Pkg, get_backup);
PHP_METHOD(Pkg, get_base64_sig);
PHP_METHOD(Pkg, get_builddate);
PHP_METHOD(Pkg, get_conflicts);
PHP_METHOD(Pkg, get_db);
PHP_METHOD(Pkg, get_depends);
PHP_METHOD(Pkg, get_desc);
PHP_METHOD(Pkg, get_download_size);
PHP_METHOD(Pkg, get_filename);
PHP_METHOD(Pkg, get_files);
PHP_METHOD(Pkg, get_groups);
PHP_METHOD(Pkg, get_has_scriptlet);
PHP_METHOD(Pkg, get_installdate);
PHP_METHOD(Pkg, get_isize);
PHP_METHOD(Pkg, get_licenses);
PHP_METHOD(Pkg, get_md5sum);
PHP_METHOD(Pkg, get_name);
PHP_METHOD(Pkg, get_optdepends);
PHP_METHOD(Pkg, get_packager);
PHP_METHOD(Pkg, get_provides);
PHP_METHOD(Pkg, get_reason);
PHP_METHOD(Pkg, get_replaces);
PHP_METHOD(Pkg, get_sha256sum);
PHP_METHOD(Pkg, get_size);
PHP_METHOD(Pkg, get_url);
PHP_METHOD(Pkg, get_version);

typedef struct _pkg_object {
    alpm_pkg_t *pkg;
    zend_object std;
} pkg_object;

static inline pkg_object *alpm_pkg_from_obj(zend_object *obj) {
    return (pkg_object *)((char*)(obj) - XtOffsetOf(pkg_object, std));
}

#define Z_PKGO_P(zv) alpm_pkg_from_obj(Z_OBJ_P(zv))

zend_object *create_pkg_struct(zend_class_entry *class TSRMLS_DC);

#endif //PHP_ALPM_PKG_H
