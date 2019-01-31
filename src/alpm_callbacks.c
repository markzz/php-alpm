/*
 *  alpm_callbacks.c
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

#include <stdio.h>

#include "php_alpm_defs.h"

extern zval *global_callback_functions[N_CALLBACKS];

void php_alpm_logcb(alpm_loglevel_t level, const char *fmt, va_list va_args) {
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

void php_alpm_dlcb(const char *filename, off_t xfered, off_t total) {
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

void php_alpm_fetchcb(off_t total) {
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

void php_alpm_totaldlcb(const char *url, const char *localpath, int force) {
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

void php_alpm_eventcb(alpm_event_t *event) {
    int status;
    const char *eventstr;
    zval ret, val, type;
    zval *func = global_callback_functions[CB_EVENT];

    switch (event->type) {
        case ALPM_EVENT_CHECKDEPS_START:
            eventstr = "Checking dependencies";
            break;
        case ALPM_EVENT_CHECKDEPS_DONE:
            eventstr = "Done checking dependencies";
            break;
        case ALPM_EVENT_FILECONFLICTS_START:
            eventstr = "Checking file conflicts";
            break;
        case ALPM_EVENT_FILECONFLICTS_DONE:
            eventstr = "Done checking file conflicts";
            break;
        case ALPM_EVENT_RESOLVEDEPS_START:
            eventstr = "Resolving dependencies";
            break;
        case ALPM_EVENT_RESOLVEDEPS_DONE:
            eventstr = "Done resolving dependencies";
            break;
        case ALPM_EVENT_INTERCONFLICTS_START:
            eventstr = "Checking inter conflicts";
            break;
        case ALPM_EVENT_INTERCONFLICTS_DONE:
            eventstr = "Done checking inter conflicts";
            break;
        case ALPM_EVENT_PACKAGE_OPERATION_START:
            eventstr = "Operating on a package";
            switch(((alpm_event_package_operation_t*)event)->operation) {
                case ALPM_PACKAGE_INSTALL:
                    eventstr = "Adding a package";
                    break;
                case ALPM_PACKAGE_UPGRADE:
                    eventstr = "Upgrading a package";
                    break;
                case ALPM_PACKAGE_REINSTALL:
                    eventstr = "Reinstalling a package";
                    break;
                case ALPM_PACKAGE_DOWNGRADE:
                    eventstr = "Downgrading a package";
                    break;
                case ALPM_PACKAGE_REMOVE:
                    eventstr = "Removing a package";
                    break;
            }
            break;
        case ALPM_EVENT_PACKAGE_OPERATION_DONE:
            eventstr = "Done operating on a package";
            switch(((alpm_event_package_operation_t*)event)->operation) {
                case ALPM_PACKAGE_INSTALL:
                    eventstr = "Done adding a package";
                    break;
                case ALPM_PACKAGE_UPGRADE:
                    eventstr = "Done upgrading a package";
                    break;
                case ALPM_PACKAGE_REINSTALL:
                    eventstr = "Done reinstalling a package";
                    break;
                case ALPM_PACKAGE_DOWNGRADE:
                    eventstr = "Done downgrading a package";
                    break;
                case ALPM_PACKAGE_REMOVE:
                    eventstr = "Done removing a package";
                    break;
            }
            break;
        case ALPM_EVENT_INTEGRITY_START:
            eventstr = "Checking integrity";
            break;
        case ALPM_EVENT_INTEGRITY_DONE:
            eventstr = "Done checking integrity";
            break;
        case ALPM_EVENT_LOAD_START:
        case ALPM_EVENT_LOAD_DONE:
        case ALPM_EVENT_DELTA_INTEGRITY_START:
        case ALPM_EVENT_DELTA_INTEGRITY_DONE:
        case ALPM_EVENT_DELTA_PATCHES_START:
        case ALPM_EVENT_DELTA_PATCHES_DONE:
        case ALPM_EVENT_DELTA_PATCH_START:
            /* info here */
        case ALPM_EVENT_DELTA_PATCH_DONE:
        case ALPM_EVENT_DELTA_PATCH_FAILED:
        case ALPM_EVENT_SCRIPTLET_INFO:
            /* info here */
        case ALPM_EVENT_RETRIEVE_START:
        case ALPM_EVENT_RETRIEVE_DONE:
        case ALPM_EVENT_RETRIEVE_FAILED:
            /* info here */
            eventstr = "event not implemented";
            break;
        case ALPM_EVENT_DISKSPACE_START:
            eventstr = "Checking disk space";
            break;
        case ALPM_EVENT_DISKSPACE_DONE:
            eventstr = "Done checking disk space";
            break;
        case ALPM_EVENT_OPTDEP_REMOVAL:
        case ALPM_EVENT_DATABASE_MISSING:
            eventstr = "event not implemented";
            break;
        case ALPM_EVENT_KEYRING_START:
            eventstr = "Checking keys in keyring";
            break;
        case ALPM_EVENT_KEYRING_DONE:
            eventstr = "Done checking keys in keyring";
            break;
        case ALPM_EVENT_KEY_DOWNLOAD_START:
        case ALPM_EVENT_KEY_DOWNLOAD_DONE:
        case ALPM_EVENT_PACNEW_CREATED:
        case ALPM_EVENT_PACSAVE_CREATED:
        case ALPM_EVENT_HOOK_START:
        case ALPM_EVENT_HOOK_DONE:
        case ALPM_EVENT_HOOK_RUN_START:
        case ALPM_EVENT_HOOK_RUN_DONE:
        default:
            eventstr = "unknown event";
    }

    ZVAL_LONG(&type, event->type);
    ZVAL_STRING(&val, eventstr);
    zval args[] = { type, val };

    status = call_user_function(CG(function_table), NULL, func, &ret, 1, args);

    if (status == FAILURE) {
        php_error(E_ERROR, "could not call eventcb");
    }
}

void php_alpm_questioncb(alpm_question_t *question) {
    int status;
    zval type, ret;
    zval *func = global_callback_functions[CB_QUESTION];

    ZVAL_LONG(&type, question->type);
    zval args[] = { type };

    status = call_user_function(CG(function_table), NULL, func, &ret, 1, args);

    if (status == FAILURE) {
        php_error(E_ERROR, "could not call questioncb");
    }
}

void php_alpm_progresscb(alpm_progress_t op, const char *target_name, int percentage, size_t n_targets, size_t cur_target) {
    int status;
    zval zop, ztn, zp, znt, zct, ret;
    zval *func = global_callback_functions[CB_PROGRESS];

    ZVAL_LONG(&zop, op);
    ZVAL_LONG(&zp, percentage);
    ZVAL_LONG(&znt, n_targets);
    ZVAL_LONG(&zct, cur_target);
    ZVAL_STRING(&ztn, target_name);
    zval args[] = { zop, ztn, zp, znt, zct };

    status = call_user_function(CG(function_table), NULL, func, &ret, 5, args);

    if (status == FAILURE) {
        php_error(E_ERROR, "could not call progresscb");
    }
}
