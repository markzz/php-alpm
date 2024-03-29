/*
 *  alpmtransaction_class.c
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

#include "php_alpm.h"
#include "php_alpm_defs.h"
#include "php_alpm_helpers.h"

PHP_METHOD(Trans, add_pkg) {
    php_alpm_transaction_object *intern = Z_TRANSO_P(getThis());
    php_alpm_pkg_object *pkg_object;
    zval *pkg_zval;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "o", &pkg_zval) == FAILURE) {
        RETURN_NULL();
    }

    pkg_object = Z_PKGO_P(pkg_zval);
    err = alpm_add_pkg(intern->handle, pkg_object->pkg);
    if (err == -1) {
        RETURN_FALSE;
    }

    ZVAL_UNDEF(pkg_zval);
    RETURN_TRUE;
}

PHP_METHOD(Trans, commit) {
    php_alpm_transaction_object *intern = Z_TRANSO_P(getThis());
    int ret;
    enum _alpm_errno_t pmerr;
    alpm_list_t *list = NULL;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    ret = alpm_trans_commit(intern->handle, &list);

    if (ret == 0) RETURN_NULL();
    if (ret != -1) {
        zend_throw_exception(php_alpm_transaction_exception_class_entry, "unexpected return value", ret);
        RETURN_NULL();
    }

    pmerr = alpm_errno(intern->handle);
    switch (pmerr) {
        case ALPM_ERR_FILE_CONFLICTS:
            alpm_fileconflicts_to_zval(list, return_value);
            break;
        case ALPM_ERR_PKG_INVALID:
        case ALPM_ERR_PKG_INVALID_CHECKSUM:
        case ALPM_ERR_PKG_INVALID_SIG:
            alpm_list_to_zval(list, return_value);
            break;
        default:
            break;
    }

    RETURN_NULL();
}

PHP_METHOD(Trans, interrupt) {
    php_alpm_transaction_object *intern = Z_TRANSO_P(getThis());
    int ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    ret = alpm_trans_release(intern->handle);
    if (ret == -1) {
        zend_throw_exception(php_alpm_transaction_exception_class_entry, "could not release transaction", 0);
    }

    RETURN_NULL();
}

PHP_METHOD(Trans, prepare) {
    php_alpm_transaction_object *intern = Z_TRANSO_P(getThis());
    alpm_list_t *data;
    alpm_errno_t err;
    zval inner_error_array;
    int ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    ret = alpm_trans_prepare(intern->handle, &data);
    if (ret == -1) {
        err = alpm_errno(intern->handle);

        array_init(return_value);
        add_assoc_long_ex(return_value, "errno", strlen("errno"), err);

        switch (err) {
            case ALPM_ERR_PKG_INVALID_ARCH:

                alpm_list_to_zval(data, &inner_error_array);
                break;
            case ALPM_ERR_UNSATISFIED_DEPS:
                alpm_depmissing_list_to_zval(data, &inner_error_array);
                break;
            case ALPM_ERR_CONFLICTING_DEPS:
                alpm_conflict_list_to_zval(data, &inner_error_array);
                break;
            default:
                break;
        }

        add_assoc_zval_ex(return_value, "offenders", strlen("offenders"), &inner_error_array);
        return;
    }

    RETURN_NULL();
}

PHP_METHOD(Trans, release) {
    php_alpm_transaction_object *intern = Z_TRANSO_P(getThis());
    int ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    ret = alpm_trans_release(intern->handle);
    if (ret == -1) {
        zend_throw_exception(php_alpm_transaction_exception_class_entry, "unable to release transaction", 0);
    }

    RETURN_NULL();
}

PHP_METHOD(Trans, remove_pkg) {
    php_alpm_transaction_object *intern = Z_TRANSO_P(getThis());
    php_alpm_pkg_object *pkg_object;
    zval *pkg_zval;
    int err;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "o", &pkg_zval) == FAILURE) {
        RETURN_NULL();
    }

    pkg_object = Z_PKGO_P(pkg_zval);
    err = alpm_remove_pkg(intern->handle, pkg_object->pkg);
    if (err == -1) {
        RETURN_FALSE;
    }

    ZVAL_UNDEF(pkg_zval);
    RETURN_TRUE;
}

PHP_METHOD(Trans, system_upgrade) {
    php_alpm_transaction_object *intern = Z_TRANSO_P(getThis());
    zend_bool downgrade = 0;
    int do_downgrade, ret;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|b", &downgrade) == FAILURE) {
        RETURN_NULL();
    }

    do_downgrade = downgrade == 1 ? 1 : 0;
    ret = alpm_sync_sysupgrade(intern->handle, do_downgrade);
    if (ret == -1) {
        zend_throw_exception(php_alpm_transaction_exception_class_entry, "unable to perform system upgrade", 0);
    }
    RETURN_NULL();
}