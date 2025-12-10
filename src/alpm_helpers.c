/*
 *  alpm_helpers.c
 *
 *  Copyright (c) 2016-2025 Mark King <mark.king@markzz.com>
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
    php_alpm_depend_object *depo;

    object_init_ex(zv, php_alpm_depend_sc_entry);
    depo = Z_DEPO_P(zv);
    depo->depend = d;
    depo->owned = 0; /* not owned, don't free */
}

void alpm_conflict_list_to_zval(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    alpm_conflict_t *conflict;
    zval obj;
    php_alpm_conflict_object *conflicto;

    array_init(zv);
    for (item = list; item; item = alpm_list_next(item)) {
        conflict = (alpm_conflict_t*)item->data;
        object_init_ex(&obj, php_alpm_conflict_sc_entry);
        conflicto = Z_CONFLICTO_P(&obj);
        conflicto->conflict = conflict;
        add_next_index_zval(zv, &obj);
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
    zval obj;
    php_alpm_group_object *groupo;

    array_init(zv);
    if (zv == NULL) {
        return;
    }

    for (item = list; item; item = alpm_list_next(item)) {
        grp = (alpm_group_t*)item->data;
        object_init_ex(&obj, php_alpm_group_sc_entry);
        groupo = Z_GROUPO_P(&obj);
        groupo->group = grp;
        add_next_index_zval(zv, &obj);
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

void alpm_list_to_db_array(alpm_handle_t *handle, alpm_list_t *list, zval *zv) {
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
        dbo->handle = handle;
        add_next_index_zval(zv, &obj);
    }
}

void alpm_fileconflicts_to_zval(alpm_list_t *fc_list, zval *zv) {
    zval obj;
    alpm_list_t *tmp;
    alpm_fileconflict_t *fc;
    php_alpm_fileconflict_object *fco;

    array_init(zv);
    for (tmp = fc_list; tmp; tmp = tmp->next) {
        fc = (alpm_fileconflict_t*)tmp->data;
        object_init_ex(&obj, php_alpm_fileconflict_sc_entry);
        fco = Z_FILECONFLICTO_P(&obj);
        fco->fileconflict = fc;
        add_next_index_zval(zv, &obj);
    }
}

void alpm_filelist_to_zval(alpm_filelist_t *flist, zval *zv) {
    zval obj;
    ssize_t i;
    php_alpm_file_object *fileo;

    array_init(zv);
    for (i = 0; i < (ssize_t)flist->count; i++) {
        alpm_file_t *file = (alpm_file_t*)(flist->files + i);
        object_init_ex(&obj, php_alpm_file_sc_entry);
        fileo = Z_FILEO_P(&obj);
        fileo->file = file;
        add_next_index_zval(zv, &obj);
    }
}

void alpm_backup_list_to_zval(alpm_list_t *list, zval *zv) {
    zval obj;
    alpm_list_t *item;
    alpm_backup_t *backup;
    php_alpm_backup_object *backupo;

    array_init(zv);
    for (item = list; item; item = alpm_list_next(item)) {
        backup = (alpm_backup_t*)item->data;
        object_init_ex(&obj, php_alpm_backup_sc_entry);
        backupo = Z_BACKUPO_P(&obj);
        backupo->backup = backup;
        add_next_index_zval(zv, &obj);
    }
}

void alpm_depmissing_list_to_zval(alpm_list_t *list, zval *zv) {
    zval obj;
    alpm_list_t *item;
    alpm_depmissing_t *dm;
    php_alpm_depmissing_object *dmo;

    array_init(zv);
    for (item = list; item; item = alpm_list_next(item)) {
        dm = (alpm_depmissing_t*)item->data;
        object_init_ex(&obj, php_alpm_depmissing_sc_entry);
        dmo = Z_DEPMISSINGO_P(&obj);
        dmo->depmissing = dm;
        add_next_index_zval(zv, &obj);
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
    php_alpm_group_object *groupo;

    object_init_ex(zv, php_alpm_group_sc_entry);
    groupo = Z_GROUPO_P(zv);
    groupo->group = grp;
}
