/*
 *  alpmbackup_class.c
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

zend_class_entry *php_alpm_backup_sc_entry;
static zend_object_handlers alpm_backup_object_handlers;

static void php_alpm_backup_free_storage(zend_object *obj) {
    php_alpm_backup_object *intern = php_alpm_backup_fetch_object(obj);

    if (!intern) {
        return;
    }

    /* alpm_backup_t is owned by the package, don't free it */
    intern->backup = NULL;

    zend_object_std_dtor(&intern->zo);
}

zend_object *php_alpm_backup_object_new(zend_class_entry *class_type) {
    php_alpm_backup_object *intern;

    intern = ecalloc(1, sizeof(php_alpm_backup_object) + sizeof(zval) * (class_type->default_properties_count - 1));

    intern->backup = NULL;

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->zo.handlers = &alpm_backup_object_handlers;
    return &intern->zo;
}

PHP_METHOD(Backup, __toString) {
    php_alpm_backup_object *intern = Z_BACKUPO_P(getThis());

    if (!intern->backup || !intern->backup->name) {
        RETURN_STRING("");
    }

    RETURN_STRING(intern->backup->name);
}

zval *php_alpm_backup_read_property(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) {
    php_alpm_backup_object *intern;
    zval *retval = NULL;
    const zend_object_handlers *std_hnd;

    std_hnd = zend_get_std_object_handlers();

    if (std_hnd->has_property(object, member, type, cache_slot)) {
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    } else {
        intern = php_alpm_backup_fetch_object(object);

        if (!intern->backup) {
            retval = rv;
            ZVAL_NULL(retval);
        } else if (strcmp(ZSTR_VAL(member), "name") == 0) {
            retval = rv;
            if (intern->backup->name) {
                ZVAL_STRING(retval, intern->backup->name);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(ZSTR_VAL(member), "hash") == 0) {
            retval = rv;
            if (intern->backup->hash) {
                ZVAL_STRING(retval, intern->backup->hash);
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

zval *php_alpm_backup_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) {
    /* All properties are read-only */
    php_error(E_WARNING, "AlpmBackup properties are read-only");
    return value;
}

HashTable *php_alpm_backup_get_properties(zend_object *object) {
    php_alpm_backup_object *intern = php_alpm_backup_fetch_object(object);
    HashTable *props = zend_std_get_properties(object);

    if (!intern->backup) {
        return props;
    }

    zval tmp;

    if (intern->backup->name) {
        ZVAL_STRING(&tmp, intern->backup->name);
    } else {
        ZVAL_NULL(&tmp);
    }
    zend_hash_str_update(props, "name", sizeof("name") - 1, &tmp);

    if (intern->backup->hash) {
        ZVAL_STRING(&tmp, intern->backup->hash);
    } else {
        ZVAL_NULL(&tmp);
    }
    zend_hash_str_update(props, "hash", sizeof("hash") - 1, &tmp);

    return props;
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_backup_tostring, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

static zend_function_entry backup_methods[] = {
    PHP_ME(Backup, __toString, arginfo_backup_tostring, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void php_alpm_backup_register_class(void) {
    zend_class_entry ce;

    memcpy(&alpm_backup_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

    INIT_CLASS_ENTRY(ce, PHP_ALPM_BACKUP_SC_NAME, backup_methods);
    ce.create_object = php_alpm_backup_object_new;
    alpm_backup_object_handlers.offset = (int) XtOffsetOf(php_alpm_backup_object, zo);
    alpm_backup_object_handlers.free_obj = php_alpm_backup_free_storage;
    alpm_backup_object_handlers.get_properties = php_alpm_backup_get_properties;
    alpm_backup_object_handlers.read_property = php_alpm_backup_read_property;
    alpm_backup_object_handlers.write_property = php_alpm_backup_write_property;
    php_alpm_backup_sc_entry = zend_register_internal_class(&ce);
}
