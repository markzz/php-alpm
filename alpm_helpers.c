#include "php_alpm_helpers.h"

void alpm_list_to_zval(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;

    array_init(zv);
    if (zv == NULL) {
        return;
    }

    for (item = list; item; item = alpm_list_next(item)) {
        add_next_index_string(zv, (char *)item->data);
    }

//    alpm_list_free(item);
}

void alpm_group_list_to_zval(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    alpm_group_t *grp;

    array_init(zv);
    if (zv == NULL) {
        return;
    }

    for (item = list; item; item = alpm_list_next(item)) {
        grp = (alpm_group_t*)item->data;
        add_next_index_string(zv, grp->name);
    }

//    alpm_list_free(item);
}

void alpm_list_to_pkg_array(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    php_alpm_pkg_object *pkgo;
    zval *obj;

    array_init(zv);
    if (zv == NULL) {
        return;
    }

    for (item = list; item; item = alpm_list_next(item)) {
        obj = (zval*)emalloc(sizeof(zval));
        object_init_ex(obj, php_alpm_pkg_sc_entry);
        pkgo = Z_PKGO_P(obj);
        pkgo->pkg = (alpm_pkg_t*)item->data;
        add_next_index_zval(zv, obj);
    }
}

void alpm_list_to_db_array(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    php_alpm_db_object *dbo;
    zval *obj;

    array_init(zv);
    if (zv == NULL) {
        return;
    }

    for (item = list; item; item = alpm_list_next(item)) {
        obj = (zval*)emalloc(sizeof(zval));
        object_init_ex(obj, php_alpm_db_sc_entry);
        dbo = Z_DBO_P(obj);
        dbo->db = (alpm_db_t*)item->data;
        add_next_index_zval(zv, obj);
    }
}

void alpm_group_to_zval(alpm_group_t *grp, zval *zv) {
    zval *inner = (zval*)emalloc(sizeof(zval));

    array_init(zv);
    alpm_list_to_pkg_array(grp->packages, inner);
    add_assoc_zval(zv, grp->name, inner);
}