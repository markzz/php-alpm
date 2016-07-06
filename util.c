//#include "php_alpm.h"
#include "pkg.h"
#include "util.h"

void alpm_list_to_zval(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;

    array_init(zv);
    if (zv == NULL) {
        return;
    }

    for (item = list; item; item = alpm_list_next(item)) {
        add_next_index_string(zv, (char *)item->data);
    }

    alpm_list_free(item);
}

void alpm_list_to_pkg_array(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    pkg_object *pkgo;
    zval *obj = (zval*)emalloc(sizeof(zval));

    array_init(zv);
    if (zv == NULL) {
        return;
    }

    for (item = list; item; item = alpm_list_next(item)) {
        object_init_ex(obj, alpm_ce_pkg);
        pkgo = Z_PKGO_P(obj);
        pkgo->pkg = (alpm_pkg_t*)item->data;

        add_next_index_zval(zv, obj);
    }
}

void zval_to_alpm_list(zval *zv, alpm_list_t *list) {
    zval *data;

    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(zv), data) {
        list = alpm_list_add(list, (void*)Z_STRVAL_P(data));
    } ZEND_HASH_FOREACH_END();
}

void alpm_filelist_to_zval(alpm_filelist_t *flist, zval *zv) {
    zval *inner = NULL;
    ssize_t i;

    array_init(zv);
    for (i = 0; i < (ssize_t)flist->count; i++) {
        const alpm_file_t *file = flist->files + i;
        array_init(inner);
        add_next_index_string(inner, file->name);
        add_next_index_long(inner, file->size);
        add_next_index_long(inner, file->mode);
        add_next_index_zval(zv, inner);
    }
}

void alpm_group_to_zval(alpm_group_t *grp, zval *zv) {
    zval *inner = (zval*)emalloc(sizeof(zval));

    array_init(zv);
    alpm_list_to_pkg_array(grp->packages, inner);
    add_assoc_zval(zv, grp->name, inner);
    efree(inner);
}

//static PyObject* _pyobject_from_pmgrp(void *group) {
//    const alpm_group_t* grp = (alpm_group_t*)group;
//    if (!grp)
//        Py_RETURN_NONE;
//    else {
//        PyObject *fst = PyUnicode_FromString(grp->name);
//        PyObject *snd = alpmlist_to_pylist(grp->packages,
//                                           pyalpm_package_from_pmpkg);
//        PyObject *tuple = PyTuple_Pack(2, fst, snd);
//        Py_DECREF(fst);
//        Py_DECREF(snd);
//        return tuple;
//    }
//}