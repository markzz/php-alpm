/*
 *  php_alpm_helpers.h
 *
 *  Copyright (c) 2016-2019 Mark Weiman <mark.weiman@markzz.com>
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

void alpm_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_conflict_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_depend_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_group_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_list_to_pkg_array(alpm_list_t *list, zval *zv);
void alpm_list_to_db_array(alpm_handle_t *handle, alpm_list_t *list, zval *zv);
int zval_to_alpm_list(zval *zv, alpm_list_t **list);
void alpm_fileconflicts_to_zval(alpm_list_t *fc_list, zval *zv);
void alpm_filelist_to_zval(alpm_filelist_t *flist, zval *zv);
void alpm_group_to_zval(alpm_group_t *grp, zval *zv);
void alpm_backup_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_depmissing_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_pkg_list_to_zval(alpm_list_t *list, zval *zv);

#endif /* PHP_ALPM_HELPERS_H */
