/*
 *  alpmfile_class.c
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

zend_class_entry *php_alpm_file_sc_entry;
static zend_object_handlers alpm_file_object_handlers;

static void php_alpm_file_free_storage(zend_object *obj) {
    php_alpm_file_object *intern = php_alpm_file_fetch_object(obj);

    if (!intern) {
        return;
    }

    /* alpm_file_t is owned by the package, don't free it */
    intern->file = NULL;

    zend_object_std_dtor(&intern->zo);
}

zend_object *php_alpm_file_object_new(zend_class_entry *class_type) {
    php_alpm_file_object *intern;

    intern = ecalloc(1, sizeof(php_alpm_file_object) + sizeof(zval) * (class_type->default_properties_count - 1));

    intern->file = NULL;

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->zo.handlers = &alpm_file_object_handlers;
    return &intern->zo;
}

PHP_METHOD(File, __toString) {
    php_alpm_file_object *intern = Z_FILEO_P(getThis());

    if (!intern->file || !intern->file->name) {
        RETURN_STRING("");
    }

    RETURN_STRING(intern->file->name);
}

zval *php_alpm_file_read_property(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) {
    php_alpm_file_object *intern;
    zval *retval = NULL;
    const zend_object_handlers *std_hnd;

    std_hnd = zend_get_std_object_handlers();

    if (std_hnd->has_property(object, member, type, cache_slot)) {
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    } else {
        intern = php_alpm_file_fetch_object(object);

        if (!intern->file) {
            retval = rv;
            ZVAL_NULL(retval);
        } else if (strcmp(ZSTR_VAL(member), "name") == 0) {
            retval = rv;
            if (intern->file->name) {
                ZVAL_STRING(retval, intern->file->name);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(ZSTR_VAL(member), "size") == 0) {
            retval = rv;
            ZVAL_LONG(retval, intern->file->size);
        } else if (strcmp(ZSTR_VAL(member), "mode") == 0) {
            retval = rv;
            ZVAL_LONG(retval, intern->file->mode);
        } else {
            retval = rv;
            ZVAL_NULL(retval);
        }
    }

    return retval;
}

zval *php_alpm_file_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) {
    /* All properties are read-only */
    php_error(E_WARNING, "AlpmFile properties are read-only");
    return value;
}

HashTable *php_alpm_file_get_properties(zend_object *object) {
    php_alpm_file_object *intern = php_alpm_file_fetch_object(object);
    HashTable *props = zend_std_get_properties(object);

    if (!intern->file) {
        return props;
    }

    zval tmp;

    if (intern->file->name) {
        ZVAL_STRING(&tmp, intern->file->name);
    } else {
        ZVAL_NULL(&tmp);
    }
    zend_hash_str_update(props, "name", sizeof("name") - 1, &tmp);

    ZVAL_LONG(&tmp, intern->file->size);
    zend_hash_str_update(props, "size", sizeof("size") - 1, &tmp);

    ZVAL_LONG(&tmp, intern->file->mode);
    zend_hash_str_update(props, "mode", sizeof("mode") - 1, &tmp);

    return props;
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_file_tostring, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

static zend_function_entry file_methods[] = {
    PHP_ME(File, __toString, arginfo_file_tostring, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void php_alpm_file_register_class(void) {
    zend_class_entry ce;

    memcpy(&alpm_file_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

    INIT_CLASS_ENTRY(ce, PHP_ALPM_FILE_SC_NAME, file_methods);
    ce.create_object = php_alpm_file_object_new;
    alpm_file_object_handlers.offset = (int) XtOffsetOf(php_alpm_file_object, zo);
    alpm_file_object_handlers.free_obj = php_alpm_file_free_storage;
    alpm_file_object_handlers.get_properties = php_alpm_file_get_properties;
    alpm_file_object_handlers.read_property = php_alpm_file_read_property;
    alpm_file_object_handlers.write_property = php_alpm_file_write_property;
    php_alpm_file_sc_entry = zend_register_internal_class(&ce);
}
