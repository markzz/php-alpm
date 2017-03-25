#include <stdio.h>

#include "php_alpm_defs.h"

extern zval *global_callback_functions[N_CALLBACKS];

void *php_alpm_logcb(alpm_loglevel_t level, const char *fmt, va_list va_args) {
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
    ZVAL_STR(&zlog, tmp);

    zval args[] = { zl, zlog };

    status = call_user_function(CG(function_table), NULL, func, &ret, 2, args);

    if (status == FAILURE) {
        php_error(E_ERROR, "could not call logcb");
    }
}

void *php_alpm_dlcb(const char *filename, off_t xfered, off_t total) {
    int status;
    zval zfn, zxf, zt, ret;
    zend_string *tmp;
    zval *func = global_callback_functions[CB_DOWNLOAD];

    ZVAL_LONG(&zxf, xfered);
    ZVAL_LONG(&zt, total);

    tmp = zend_string_init(filename, strlen(filename), 1);
    ZVAL_STR(&zfn, tmp);

    zval args[] = { zfn, zxf, zt };
    status = call_user_function(CG(function_table), NULL, func, &ret, 3, args);

    if (status == FAILURE) {
        php_error(E_ERROR, "could not call dlcb");
    }
}

void *php_alpm_fetchcb(off_t total) {
    int status;
    zval zt, ret;
    zval *func = global_callback_functions[CB_FETCH];

    ZVAL_LONG(&zt, total);

    zval args[] = { zt };
    status = call_user_function(CG(function_table), NULL, func, &ret, 1, args);

    if (status == FAILURE) {
        php_error(E_ERROR, "could not call fetchcb");
    }
}

void *php_alpm_totaldlcb(const char *url, const char *localpath, int force) {
    int status;
    zval zu, zlp, zf, ret;
    zend_string *tmp;
    zval *func = global_callback_functions[CB_TOTALDL];

    ZVAL_BOOL(&zf, force == 0 ? IS_FALSE : IS_TRUE);
    tmp = zend_string_init(url, strlen(url), 1);
    ZVAL_STR(&zu, tmp);
    tmp = zend_string_init(localpath, strlen(localpath), 1);
    ZVAL_STR(&zlp, tmp);

    zval args[] = { zu, zlp, zf };
    status = call_user_function(CG(function_table), NULL, func, &ret, 3, args);

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

void *php_alpm_progresscb(alpm_progress_t op, const char *target_name, int percentage, size_t n_targets, size_t cur_target) {
    int status;
    zval zop, ztn, zp, znt, zct, ret;
    zend_string *tmp;
    zval *func = global_callback_functions[CB_PROGRESS];

    tmp = zend_string_init(target_name, strlen(target_name), 1);

    ZVAL_LONG(&zop, op);
    ZVAL_LONG(&zp, percentage);
    ZVAL_LONG(&znt, n_targets);
    ZVAL_LONG(&zct, cur_target);
    ZVAL_STR(&ztn, tmp);

    zval args[] = { zop, ztn, zp, znt, zct };

    status = call_user_function(CG(function_table), NULL, func, &ret, 5, args);

    if (status == FAILURE) {
        php_error(E_ERROR, "could not call progresscb");
    }
}
