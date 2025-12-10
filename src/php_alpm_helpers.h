/*
 *  php_alpm_helpers.h
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

#ifndef PHP_ALPM_HELPERS_H
#define PHP_ALPM_HELPERS_H

#include "php_alpm_defs.h"

/* String list conversion */
void alpm_list_to_zval(alpm_list_t *list, zval *zv);
int zval_to_alpm_list(zval *zv, alpm_list_t **list);

/* Object list conversions */
void alpm_list_to_pkg_array(alpm_list_t *list, zval *zv);
void alpm_list_to_db_array(alpm_handle_t *handle, alpm_list_t *list, zval *zv);
void alpm_pkg_list_to_zval(alpm_list_t *list, zval *zv);

/* Struct list conversions (now return objects) */
void alpm_depend_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_conflict_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_group_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_filelist_to_zval(alpm_filelist_t *flist, zval *zv);
void alpm_backup_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_depmissing_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_fileconflicts_to_zval(alpm_list_t *fc_list, zval *zv);
void alpm_group_to_zval(alpm_group_t *grp, zval *zv);

/* Class registration functions */
void php_alpm_depend_register_class(void);
void php_alpm_file_register_class(void);
void php_alpm_backup_register_class(void);
void php_alpm_group_register_class(void);
void php_alpm_conflict_register_class(void);
void php_alpm_depmissing_register_class(void);
void php_alpm_fileconflict_register_class(void);

/* Object creation functions */
zend_object *php_alpm_depend_object_new(zend_class_entry *class_type);
zend_object *php_alpm_file_object_new(zend_class_entry *class_type);
zend_object *php_alpm_backup_object_new(zend_class_entry *class_type);
zend_object *php_alpm_group_object_new(zend_class_entry *class_type);
zend_object *php_alpm_conflict_object_new(zend_class_entry *class_type);
zend_object *php_alpm_depmissing_object_new(zend_class_entry *class_type);
zend_object *php_alpm_fileconflict_object_new(zend_class_entry *class_type);

#endif /* PHP_ALPM_HELPERS_H */
