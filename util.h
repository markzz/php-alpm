#ifndef PHP_ALPM_UTIL_H
#define PHP_ALPM_UTIL_H

#include "php.h"
#include "php_alpm.h"

void alpm_list_to_zval(alpm_list_t *list, zval *zv);
void zval_to_alpm_list(zval *zv, alpm_list_t *list);
void alpm_filelist_to_zval(alpm_filelist_t *flist, zval *zv);
void alpm_group_to_zval(alpm_group_t *grp, zval *zv);

#define ADD_METHOD_START() char *arg; size_t arg_size; if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_size) == FAILURE) { RETURN_NULL() } handle_object *intern = Z_HANDLEO_P(getThis());
#define GET_ARRAY_METHOD(func, o) if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) { RETURN_NULL() } handle_object *intern = Z_HANDLEO_P(getThis()); alpm_list_t *list = func(intern->o); if (list == NULL) { RETURN_NULL() } alpm_list_to_zval(list, return_value); alpm_list_free(list); return;
#define SETTER_METHOD(func, o) char *arg; size_t arg_size; if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_size) == FAILURE) { RETURN_NULL() } handle_object *intern = Z_HANDLEO_P(getThis()); func(intern->o, arg); RETURN_NULL()
#define INT_SETTER_METHOD(func, o) int arg; if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &arg) == FAILURE) { RETURN_NULL() } handle_object *intern = Z_HANDLEO_P(getThis()); func(intern->o, arg); RETURN_NULL()
#define GETTER_METHOD(func, o) if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) { RETURN_NULL() } handle_object *intern = Z_HANDLEO_P(getThis()); RETURN_STRING(func(intern->o))
#define INT_GETTER_METHOD(func, o) if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) { RETURN_NULL() } handle_object *intern = Z_HANDLEO_P(getThis()); RETURN_LONG(func(intern->o))

#endif //PHP_ALPM_UTIL_H
