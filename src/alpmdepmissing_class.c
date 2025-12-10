/*
 *  alpmdepmissing_class.c
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

zend_class_entry *php_alpm_depmissing_sc_entry;
static zend_object_handlers alpm_depmissing_object_handlers;

static void php_alpm_depmissing_free_storage(zend_object *obj) {
    php_alpm_depmissing_object *intern = php_alpm_depmissing_fetch_object(obj);

    if (!intern) {
        return;
    }

    /* alpm_depmissing_t from transactions should be freed */
    if (intern->depmissing) {
        alpm_depmissing_free(intern->depmissing);
        intern->depmissing = NULL;
    }

    zend_object_std_dtor(&intern->zo);
}

zend_object *php_alpm_depmissing_object_new(zend_class_entry *class_type) {
    php_alpm_depmissing_object *intern;

    intern = ecalloc(1, sizeof(php_alpm_depmissing_object) + sizeof(zval) * (class_type->default_properties_count - 1));

    intern->depmissing = NULL;

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->zo.handlers = &alpm_depmissing_object_handlers;
    return &intern->zo;
}

PHP_METHOD(DepMissing, __toString) {
    php_alpm_depmissing_object *intern = Z_DEPMISSINGO_P(getThis());
    char *depstring;
    char *result;
    size_t len;

    if (!intern->depmissing) {
        RETURN_STRING("");
    }

    depstring = alpm_dep_compute_string(intern->depmissing->depend);
    if (!depstring) {
        RETURN_STRING("");
    }

    len = strlen(intern->depmissing->target) + strlen(depstring) + 16;
    result = emalloc(len);
    snprintf(result, len, "%s requires %s", intern->depmissing->target, depstring);
    free(depstring);

    RETVAL_STRING(result);
    efree(result);
}

zval *php_alpm_depmissing_read_property(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) {
    php_alpm_depmissing_object *intern;
    zval *retval = NULL;
    const zend_object_handlers *std_hnd;

    std_hnd = zend_get_std_object_handlers();

    if (std_hnd->has_property(object, member, type, cache_slot)) {
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    } else {
        intern = php_alpm_depmissing_fetch_object(object);

        if (!intern->depmissing) {
            retval = rv;
            ZVAL_NULL(retval);
        } else if (strcmp(ZSTR_VAL(member), "target") == 0) {
            retval = rv;
            if (intern->depmissing->target) {
                ZVAL_STRING(retval, intern->depmissing->target);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(ZSTR_VAL(member), "depend") == 0) {
            retval = rv;
            php_alpm_depend_object *depo;
            object_init_ex(retval, php_alpm_depend_sc_entry);
            depo = Z_DEPO_P(retval);
            depo->depend = intern->depmissing->depend;
            depo->owned = 0; /* owned by depmissing */
        } else if (strcmp(ZSTR_VAL(member), "causingpkg") == 0) {
            retval = rv;
            if (intern->depmissing->causingpkg) {
                ZVAL_STRING(retval, intern->depmissing->causingpkg);
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

zval *php_alpm_depmissing_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) {
    /* All properties are read-only */
    php_error(E_WARNING, "AlpmDepMissing properties are read-only");
    return value;
}

HashTable *php_alpm_depmissing_get_properties(zend_object *object) {
    php_alpm_depmissing_object *intern = php_alpm_depmissing_fetch_object(object);
    HashTable *props = zend_std_get_properties(object);

    if (!intern->depmissing) {
        return props;
    }

    zval tmp;
    php_alpm_depend_object *depo;

    if (intern->depmissing->target) {
        ZVAL_STRING(&tmp, intern->depmissing->target);
    } else {
        ZVAL_NULL(&tmp);
    }
    zend_hash_str_update(props, "target", sizeof("target") - 1, &tmp);

    object_init_ex(&tmp, php_alpm_depend_sc_entry);
    depo = Z_DEPO_P(&tmp);
    depo->depend = intern->depmissing->depend;
    depo->owned = 0;
    zend_hash_str_update(props, "depend", sizeof("depend") - 1, &tmp);

    if (intern->depmissing->causingpkg) {
        ZVAL_STRING(&tmp, intern->depmissing->causingpkg);
    } else {
        ZVAL_NULL(&tmp);
    }
    zend_hash_str_update(props, "causingpkg", sizeof("causingpkg") - 1, &tmp);

    return props;
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_depmissing_tostring, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

static zend_function_entry depmissing_methods[] = {
    PHP_ME(DepMissing, __toString, arginfo_depmissing_tostring, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void php_alpm_depmissing_register_class(void) {
    zend_class_entry ce;

    memcpy(&alpm_depmissing_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

    INIT_CLASS_ENTRY(ce, PHP_ALPM_DEPMISSING_SC_NAME, depmissing_methods);
    ce.create_object = php_alpm_depmissing_object_new;
    alpm_depmissing_object_handlers.offset = (int) XtOffsetOf(php_alpm_depmissing_object, zo);
    alpm_depmissing_object_handlers.free_obj = php_alpm_depmissing_free_storage;
    alpm_depmissing_object_handlers.get_properties = php_alpm_depmissing_get_properties;
    alpm_depmissing_object_handlers.read_property = php_alpm_depmissing_read_property;
    alpm_depmissing_object_handlers.write_property = php_alpm_depmissing_write_property;
    php_alpm_depmissing_sc_entry = zend_register_internal_class(&ce);
}
