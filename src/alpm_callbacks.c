/*
 *  alpm_callbacks.c
 *
 *  Copyright (c) 2016-2017 Mark Weiman <contact@markzz.net>
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

#include <stdio.h>

#include "php_alpm_defs.h"
#include "php_alpm_helpers.h"

/* FIXME: The TSMLRS_DC parameters will break a PHP 5 instance of this. Find a way to remove. */

extern zval *global_callback_functions[N_CALLBACKS];

void *php_alpm_logcb(alpm_loglevel_t level, const char *fmt, va_list va_args TSRMLS_DC) {
    char *log;
    int status, vasret;
    zval zl, zlog, ret;
    zend_string *tmp;
    zval *func = global_callback_functions[CB_LOG];

    ZVAL_LONG(&zl, level);

    vasret = ap_php_vasprintf(&log, fmt, va_args);
    if (vasret == -1) {
        log = "logcb: could not allocate memory";
    }

    tmp = zend_string_init(log, strlen(log), 1);
#ifdef ZEND_ENGINE_3
    ZVAL_STR(&zlog, tmp);
#else
    ZVAL_STRING(&zlog, tmp, 1);
#endif

    zval args[] = { zl, zlog };

    status = call_user_function(CG(function_table), NULL, func, &ret, 2, args TSRMLS_CC);

    if (status == FAILURE) {
        php_error(E_ERROR, "could not call logcb");
    }
}

void *php_alpm_dlcb(const char *filename, off_t xfered, off_t total TSRMLS_DC) {
    int status;
    zval zfn, zxf, zt, ret;
    zend_string *tmp;
    zval *func = global_callback_functions[CB_DOWNLOAD];

    ZVAL_LONG(&zxf, xfered);
    ZVAL_LONG(&zt, total);

    tmp = zend_string_init(filename, strlen(filename), 1);
#ifdef ZEND_ENGINE_3
    ZVAL_STR(&zfn, tmp);
#else
    ZVAL_STRING(&zfn, tmp, 1);
#endif

    zval args[] = { zfn, zxf, zt };
    status = call_user_function(CG(function_table), NULL, func, &ret, 3, args TSRMLS_CC);

    if (status == FAILURE) {
        php_error(E_ERROR, "could not call dlcb");
    }
}

void *php_alpm_fetchcb(off_t total TSRMLS_DC) {
    int status;
    zval zt, ret;
    zval *func = global_callback_functions[CB_FETCH];

    ZVAL_LONG(&zt, total);

    zval args[] = { zt };
    status = call_user_function(CG(function_table), NULL, func, &ret, 1, args TSRMLS_CC);

    if (status == FAILURE) {
        php_error(E_ERROR, "could not call fetchcb");
    }
}

void *php_alpm_totaldlcb(const char *url, const char *localpath, int force TSRMLS_DC) {
    int status;
    zval zu, zlp, zf, ret;
    zend_string *tmp;
    zval *func = global_callback_functions[CB_TOTALDL];

    ZVAL_BOOL(&zf, force == 0 ? IS_FALSE : IS_TRUE);
    tmp = zend_string_init(url, strlen(url), 1);
#ifdef ZEND_ENGINE_3
    ZVAL_STR(&zu, tmp);
#else
    ZVAL_STRING(&zu, tmp, 1);
#endif
    tmp = zend_string_init(localpath, strlen(localpath), 1);
#ifdef ZEND_ENGINE_3
    ZVAL_STR(&zlp, tmp);
#else
    ZVAL_STRING(&zlp, tmp, 1);
#endif

    zval args[] = { zu, zlp, zf };
    status = call_user_function(CG(function_table), NULL, func, &ret, 3, args TSRMLS_CC);

    if (status == FAILURE) {
        php_error(E_ERROR, "could not call totaldlcb");
    }
}

void *php_alpm_eventcb(alpm_event_t event, void *data1, void *data2) {
    /* TODO: Write function. */
}

void *php_alpm_questioncb(alpm_question_t question, void *data1, void *data2, void *data3, int *retcode) {
    /* TODO: Write function. */
}

void *php_alpm_progresscb(alpm_progress_t op, const char *target_name, int percentage, size_t n_targets, size_t cur_target TSRMLS_DC) {
    int status;
    zval zop, ztn, zp, znt, zct, ret;
    zval *func = global_callback_functions[CB_PROGRESS];

    ZVAL_LONG(&zop, op);
    ZVAL_LONG(&zp, percentage);
    ZVAL_LONG(&znt, n_targets);
    ZVAL_LONG(&zct, cur_target);
#ifdef ZEND_ENGINE_3
    ZVAL_STRING(&ztn, target_name);
#else
    ZVAL_STRING(&ztn, target_name, 1);
#endif

    zval args[] = { zop, ztn, zp, znt, zct };

    status = call_user_function(CG(function_table), NULL, func, &ret, 5, args TSRMLS_CC);

    if (status == FAILURE) {
        php_error(E_ERROR, "could not call progresscb");
    }
}
