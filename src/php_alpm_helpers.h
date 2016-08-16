#ifndef PHP_ALPM_HELPERS_H
#define PHP_ALPM_HELPERS_H

#include "php_alpm_defs.h"

void alpm_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_depend_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_group_list_to_zval(alpm_list_t *list, zval *zv);
void alpm_list_to_pkg_array(alpm_list_t *list, zval *zv);
void alpm_list_to_db_array(alpm_list_t *list, zval *zv);
int zval_to_alpm_list(zval *zv, alpm_list_t **list);
void alpm_filelist_to_zval(alpm_filelist_t *flist, zval *zv);
void alpm_group_to_zval(alpm_group_t *grp, zval *zv);
void alpm_backup_list_to_zval(alpm_list_t *list, zval *zv);

#endif /* PHP_ALPM_HELPERS_H */
