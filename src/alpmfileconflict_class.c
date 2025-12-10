/*
 *  alpmfileconflict_class.c
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

#include "php_alpm.h"
#include "php_alpm_defs.h"
#include "php_alpm_helpers.h"

zend_class_entry *php_alpm_fileconflict_sc_entry;
static zend_object_handlers alpm_fileconflict_object_handlers;

static void php_alpm_fileconflict_free_storage(zend_object *obj) {
    php_alpm_fileconflict_object *intern = php_alpm_fileconflict_fetch_object(obj);

    if (!intern) {
        return;
    }

    /* alpm_fileconflict_t from transactions should be freed */
    if (intern->fileconflict) {
        alpm_fileconflict_free(intern->fileconflict);
        intern->fileconflict = NULL;
    }

    zend_object_std_dtor(&intern->zo);
}

zend_object *php_alpm_fileconflict_object_new(zend_class_entry *class_type) {
    php_alpm_fileconflict_object *intern;

    intern = ecalloc(1, sizeof(php_alpm_fileconflict_object) + sizeof(zval) * (class_type->default_properties_count - 1));

    intern->fileconflict = NULL;

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->zo.handlers = &alpm_fileconflict_object_handlers;
    return &intern->zo;
}

PHP_METHOD(FileConflict, __toString) {
    php_alpm_fileconflict_object *intern = Z_FILECONFLICTO_P(getThis());

    if (!intern->fileconflict || !intern->fileconflict->file) {
        RETURN_STRING("");
    }

    /* Return something like "target: file (type)" */
    char *result;
    const char *type_str;
    size_t len;

    if (intern->fileconflict->type == ALPM_FILECONFLICT_TARGET) {
        type_str = "target conflict";
    } else {
        type_str = "filesystem conflict";
    }

    len = strlen(intern->fileconflict->target) + strlen(intern->fileconflict->file) + strlen(type_str) + 8;
    result = emalloc(len);
    snprintf(result, len, "%s: %s (%s)", intern->fileconflict->target, intern->fileconflict->file, type_str);

    RETVAL_STRING(result);
    efree(result);
}

zval *php_alpm_fileconflict_read_property(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) {
    php_alpm_fileconflict_object *intern;
    zval *retval = NULL;
    const zend_object_handlers *std_hnd;

    std_hnd = zend_get_std_object_handlers();

    if (std_hnd->has_property(object, member, type, cache_slot)) {
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    } else {
        intern = php_alpm_fileconflict_fetch_object(object);

        if (!intern->fileconflict) {
            retval = rv;
            ZVAL_NULL(retval);
        } else if (strcmp(ZSTR_VAL(member), "target") == 0) {
            retval = rv;
            if (intern->fileconflict->target) {
                ZVAL_STRING(retval, intern->fileconflict->target);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(ZSTR_VAL(member), "type") == 0) {
            retval = rv;
            ZVAL_LONG(retval, intern->fileconflict->type);
        } else if (strcmp(ZSTR_VAL(member), "file") == 0) {
            retval = rv;
            if (intern->fileconflict->file) {
                ZVAL_STRING(retval, intern->fileconflict->file);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(ZSTR_VAL(member), "ctarget") == 0) {
            retval = rv;
            if (intern->fileconflict->ctarget) {
                ZVAL_STRING(retval, intern->fileconflict->ctarget);
            } else {
                ZVAL_NULL(retval);
            }
        } else {
            retval = rv;
            ZVAL_NULL(retval);
        }
    }

    return retval;
}

zval *php_alpm_fileconflict_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) {
    /* All properties are read-only */
    php_error(E_WARNING, "AlpmFileConflict properties are read-only");
    return value;
}

HashTable *php_alpm_fileconflict_get_properties(zend_object *object) {
    php_alpm_fileconflict_object *intern = php_alpm_fileconflict_fetch_object(object);
    HashTable *props = zend_std_get_properties(object);

    if (!intern->fileconflict) {
        return props;
    }

    zval tmp;

    if (intern->fileconflict->target) {
        ZVAL_STRING(&tmp, intern->fileconflict->target);
    } else {
        ZVAL_NULL(&tmp);
    }
    zend_hash_str_update(props, "target", sizeof("target") - 1, &tmp);

    ZVAL_LONG(&tmp, intern->fileconflict->type);
    zend_hash_str_update(props, "type", sizeof("type") - 1, &tmp);

    if (intern->fileconflict->file) {
        ZVAL_STRING(&tmp, intern->fileconflict->file);
    } else {
        ZVAL_NULL(&tmp);
    }
    zend_hash_str_update(props, "file", sizeof("file") - 1, &tmp);

    if (intern->fileconflict->ctarget) {
        ZVAL_STRING(&tmp, intern->fileconflict->ctarget);
    } else {
        ZVAL_NULL(&tmp);
    }
    zend_hash_str_update(props, "ctarget", sizeof("ctarget") - 1, &tmp);

    return props;
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_fileconflict_tostring, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

static zend_function_entry fileconflict_methods[] = {
    PHP_ME(FileConflict, __toString, arginfo_fileconflict_tostring, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void php_alpm_fileconflict_register_class(void) {
    zend_class_entry ce;

    memcpy(&alpm_fileconflict_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

    INIT_CLASS_ENTRY(ce, PHP_ALPM_FILECONFLICT_SC_NAME, fileconflict_methods);
    ce.create_object = php_alpm_fileconflict_object_new;
    alpm_fileconflict_object_handlers.offset = (int) XtOffsetOf(php_alpm_fileconflict_object, zo);
    alpm_fileconflict_object_handlers.free_obj = php_alpm_fileconflict_free_storage;
    alpm_fileconflict_object_handlers.get_properties = php_alpm_fileconflict_get_properties;
    alpm_fileconflict_object_handlers.read_property = php_alpm_fileconflict_read_property;
    alpm_fileconflict_object_handlers.write_property = php_alpm_fileconflict_write_property;
    php_alpm_fileconflict_sc_entry = zend_register_internal_class(&ce);
}
