/*
 *  alpm_helpers.c
 *
 *  Copyright (c) 2016-2018 Mark Weiman <mark.weiman@markzz.com>
 *
 *  This extension is free software; you can redistribute it and/or
 *  modify it under the terms of version 2.1 of the GNU Lesser General
 *  Public License as published by the Free Software Foundation.
 *
 *  This extension is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this extension; if not see <http://www.gnu.org/licenses/>.
 */

#include "php_alpm_helpers.h"

void alpm_list_to_zval(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    zend_string *tmp;

    array_init(zv);
    for (item = list; item; item = alpm_list_next(item)) {
        tmp = zend_string_init(item->data, strlen((char*)item->data), 0);
        add_next_index_str(zv, tmp);
    }
}

void alpm_pkg_list_to_zval(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    zend_string *tmp;

    array_init(zv);
    for (item = list; item; item = alpm_list_next(item)) {
        tmp = zend_string_init(alpm_pkg_get_name((alpm_pkg_t*)item->data), strlen(alpm_pkg_get_name((alpm_pkg_t*)item->data)), 0);
        add_next_index_str(zv, tmp);
    }
}

void alpm_depend_to_zval(alpm_depend_t* d, zval *zv) {
    zend_string *tmp;

    array_init(zv);
    tmp = zend_string_init(d->name, strlen(d->name), 0);
    add_assoc_str_ex(zv, "name", strlen("name"), tmp);
    if (d->version != NULL) {
        tmp = zend_string_init(d->version, strlen(d->version), 0);
        add_assoc_str_ex(zv, "version", strlen("version"), tmp);
    } else {
        add_assoc_null_ex(zv, "version", strlen("version"));
    }

    if (d->desc != NULL) {
        tmp = zend_string_init(d->desc, strlen(d->desc), 0);
        add_assoc_str_ex(zv, "desc", strlen("desc"), tmp);
    } else {
        add_assoc_null_ex(zv, "desc", strlen("desc"));
    }
    add_assoc_long_ex(zv, "mod", strlen("mod"), d->mod);
}

void alpm_conflict_list_to_zval(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    alpm_conflict_t *conflict;
    zend_string *tmp;
    zval inner, dep_zval;

    array_init(zv);
    for (item = list; item; alpm_list_next(item)) {
        conflict = (alpm_conflict_t*)item->data;
        array_init(&inner);
        tmp = zend_string_init(conflict->package1, strlen(conflict->package1), 0);
        add_assoc_str_ex(&inner, "package1", strlen("package1"), tmp);
        tmp = zend_string_init(conflict->package2, strlen(conflict->package2), 0);
        add_assoc_str_ex(&inner, "package2", strlen("package2"), tmp);
        alpm_depend_to_zval(conflict->reason, &dep_zval);
        add_assoc_zval_ex(&inner, "reason", strlen("reason"), &dep_zval);
        add_next_index_zval(zv, &inner);
    }
}

void alpm_depend_list_to_zval(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    alpm_depend_t *d;
    zval inner;

    array_init(zv);
    for (item = list; item; item = alpm_list_next(item)) {
        d = (alpm_depend_t*)item->data;
        alpm_depend_to_zval(d, &inner);
        add_next_index_zval(zv, &inner);
    }
}

void alpm_group_list_to_zval(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    alpm_group_t *grp;
    zend_string *tmp;

    array_init(zv);
    if (zv == NULL) {
        return;
    }

    for (item = list; item; item = alpm_list_next(item)) {
        grp = (alpm_group_t*)item->data;
        tmp = zend_string_init(grp->name, strlen(grp->name), 0);
        add_next_index_str(zv, tmp);
    }
}

void alpm_list_to_pkg_array(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    php_alpm_pkg_object *pkgo;
    zval obj;

    array_init(zv);
    if (zv == NULL) {
        return;
    }

    for (item = list; item; item = alpm_list_next(item)) {
        object_init_ex(&obj, php_alpm_pkg_sc_entry);
        pkgo = Z_PKGO_P(&obj);
        pkgo->pkg = (alpm_pkg_t*)item->data;
        add_next_index_zval(zv, &obj);
    }
}

void alpm_list_to_db_array(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    php_alpm_db_object *dbo;
    zval obj;

    array_init(zv);
    if (zv == NULL) {
        return;
    }

    for (item = list; item; item = alpm_list_next(item)) {
        object_init_ex(&obj, php_alpm_db_sc_entry);
        dbo = Z_DBO_P(&obj);
        dbo->db = (alpm_db_t*)item->data;
        add_next_index_zval(zv, &obj);
    }
}

void alpm_fileconflicts_to_zval(alpm_list_t *fc_list, zval *zv) {
    zval inner;
    alpm_list_t *tmp;
    alpm_fileconflict_t *fc;

    array_init(zv);
    for (tmp = fc_list; tmp; tmp = tmp->next) {
        fc = (alpm_fileconflict_t*)tmp->data;
        array_init(&inner);
        add_assoc_string_ex(&inner, "target", strlen("target"), fc->target);
        add_assoc_long_ex(&inner, "type", strlen("type"), fc->type);
        add_assoc_string_ex(&inner, "file", strlen("file"), fc->file);
        add_assoc_string_ex(&inner, "ctarget", strlen("ctarget"), fc->ctarget);
        add_next_index_zval(zv, &inner);
    }
}

void alpm_filelist_to_zval(alpm_filelist_t *flist, zval *zv) {
    zval inner;
    ssize_t i;

    array_init(zv);
    for (i = 0; i < (ssize_t)flist->count; i++) {
        const alpm_file_t *file = flist->files + i;
        array_init(&inner);
        add_assoc_string_ex(&inner, "filename", strlen("filename"), file->name);
        add_assoc_long_ex(&inner, "size", strlen("size"), file->size);
        add_assoc_long_ex(&inner, "mode", strlen("mode"), file->mode);
        add_next_index_zval(zv, &inner);
    }
}

void alpm_backup_list_to_zval(alpm_list_t *list, zval *zv) {
    zval inner;
    zend_string *tmp;
    alpm_list_t *item;
    alpm_backup_t *backup;

    array_init(zv);
    for (item = list; item; item = alpm_list_next(item)) {
        array_init(&inner);
        backup = (alpm_backup_t*)item->data;
        tmp = zend_string_init(backup->name, strlen(backup->name), 0);
        add_next_index_str(&inner, tmp);

        if (backup->hash == NULL) {
            add_next_index_null(&inner);
        } else {
            tmp = zend_string_init(backup->hash, strlen(backup->hash), 0);
            add_next_index_str(&inner, tmp);
        }

        add_next_index_zval(zv, &inner);
    }
}

void alpm_depmissing_list_to_zval(alpm_list_t *list, zval *zv) {
    zval inner;
    zend_string *tmp;
    alpm_list_t *item;
    alpm_depmissing_t *dm;
    alpm_depend_t *d;

    array_init(zv);
    for (item = list; item; item = alpm_list_next(item)) {
        array_init(&inner);
        dm = (alpm_depmissing_t*)item->data;
        if (dm->target == NULL) {
            add_next_index_null(&inner);
        } else {
            tmp = zend_string_init(dm->target, strlen(dm->target), 0);
            add_next_index_str(&inner, tmp);
        }

        d = dm->depend;
        tmp = zend_string_init(d->name, strlen(d->name), 0);
        add_next_index_str(&inner, tmp);

        if (dm->causingpkg == NULL) {
            add_next_index_null(&inner);
        } else {
            tmp = zend_string_init(dm->causingpkg, strlen(dm->causingpkg), 0);
            add_next_index_str(&inner, tmp);
        }

        add_next_index_zval(zv, &inner);
    }
}


int zval_to_alpm_list(zval *zv, alpm_list_t **list) {
    alpm_list_t *ret = NULL;

    zval *data;
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(zv), data) {
        ret = alpm_list_add(ret, Z_STRVAL_P(data));
    } ZEND_HASH_FOREACH_END();

    *list = ret;
    return 0;
}

void alpm_group_to_zval(alpm_group_t *grp, zval *zv) {
    zval inner;

    array_init(zv);
    alpm_list_to_pkg_array(grp->packages, &inner);
    add_assoc_zval(zv, grp->name, &inner);
}
