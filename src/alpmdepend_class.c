/*
 *  alpmdepend_class.c
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

zend_class_entry *php_alpm_depend_sc_entry;
static zend_object_handlers alpm_depend_object_handlers;

static void php_alpm_depend_free_storage(zend_object *obj) {
    php_alpm_depend_object *intern = php_alpm_depend_fetch_object(obj);

    if (!intern) {
        return;
    }

    if (intern->depend && intern->owned) {
        alpm_dep_free(intern->depend);
        intern->depend = NULL;
    }

    zend_object_std_dtor(&intern->zo);
}

zend_object *php_alpm_depend_object_new(zend_class_entry *class_type) {
    php_alpm_depend_object *intern;

    intern = ecalloc(1, sizeof(php_alpm_depend_object) + sizeof(zval) * (class_type->default_properties_count - 1));

    intern->depend = NULL;
    intern->owned = 0;

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->zo.handlers = &alpm_depend_object_handlers;
    return &intern->zo;
}

PHP_METHOD(Depend, __toString) {
    php_alpm_depend_object *intern = Z_DEPO_P(getThis());
    char *depstring;
    zend_string *ret;

    if (!intern->depend) {
        RETURN_STRING("");
    }

    depstring = alpm_dep_compute_string(intern->depend);
    if (!depstring) {
        RETURN_STRING("");
    }

    ret = zend_string_init(depstring, strlen(depstring), 0);
    free(depstring);

    RETURN_STR(ret);
}

PHP_METHOD(Depend, compute_string) {
    php_alpm_depend_object *intern = Z_DEPO_P(getThis());
    char *depstring;
    zend_string *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    if (!intern->depend) {
        RETURN_NULL();
    }

    depstring = alpm_dep_compute_string(intern->depend);
    if (!depstring) {
        RETURN_NULL();
    }

    ret = zend_string_init(depstring, strlen(depstring), 0);
    free(depstring);

    RETURN_STR(ret);
}

zval *php_alpm_depend_read_property(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) {
    php_alpm_depend_object *intern;
    zval *retval = NULL;
    const zend_object_handlers *std_hnd;

    std_hnd = zend_get_std_object_handlers();

    if (std_hnd->has_property(object, member, type, cache_slot)) {
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    } else {
        intern = php_alpm_depend_fetch_object(object);

        if (!intern->depend) {
            retval = rv;
            ZVAL_NULL(retval);
        } else if (strcmp(ZSTR_VAL(member), "name") == 0) {
            retval = rv;
            if (intern->depend->name) {
                ZVAL_STRING(retval, intern->depend->name);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(ZSTR_VAL(member), "version") == 0) {
            retval = rv;
            if (intern->depend->version) {
                ZVAL_STRING(retval, intern->depend->version);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(ZSTR_VAL(member), "desc") == 0) {
            retval = rv;
            if (intern->depend->desc) {
                ZVAL_STRING(retval, intern->depend->desc);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(ZSTR_VAL(member), "mod") == 0) {
            retval = rv;
            ZVAL_LONG(retval, intern->depend->mod);
        } else {
            retval = rv;
            ZVAL_NULL(retval);
        }
    }

    return retval;
}

zval *php_alpm_depend_write_property(zend_object *object, zend_string *member, zval *value, void **cache_slot) {
    /* All properties are read-only */
    php_error(E_WARNING, "AlpmDepend properties are read-only");
    return value;
}

HashTable *php_alpm_depend_get_properties(zend_object *object) {
    php_alpm_depend_object *intern = php_alpm_depend_fetch_object(object);
    HashTable *props = zend_std_get_properties(object);

    if (!intern->depend) {
        return props;
    }

    zval tmp;

    if (intern->depend->name) {
        ZVAL_STRING(&tmp, intern->depend->name);
    } else {
        ZVAL_NULL(&tmp);
    }
    zend_hash_str_update(props, "name", sizeof("name") - 1, &tmp);

    if (intern->depend->version) {
        ZVAL_STRING(&tmp, intern->depend->version);
    } else {
        ZVAL_NULL(&tmp);
    }
    zend_hash_str_update(props, "version", sizeof("version") - 1, &tmp);

    if (intern->depend->desc) {
        ZVAL_STRING(&tmp, intern->depend->desc);
    } else {
        ZVAL_NULL(&tmp);
    }
    zend_hash_str_update(props, "desc", sizeof("desc") - 1, &tmp);

    ZVAL_LONG(&tmp, intern->depend->mod);
    zend_hash_str_update(props, "mod", sizeof("mod") - 1, &tmp);

    return props;
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_depend_tostring, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_depend_compute_string, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_function_entry depend_methods[] = {
    PHP_ME(Depend, __toString, arginfo_depend_tostring, ZEND_ACC_PUBLIC)
    PHP_ME(Depend, compute_string, arginfo_depend_compute_string, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void php_alpm_depend_register_class(void) {
    zend_class_entry ce;

    memcpy(&alpm_depend_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

    INIT_CLASS_ENTRY(ce, PHP_ALPM_DEPEND_SC_NAME, depend_methods);
    ce.create_object = php_alpm_depend_object_new;
    alpm_depend_object_handlers.offset = (int) XtOffsetOf(php_alpm_depend_object, zo);
    alpm_depend_object_handlers.free_obj = php_alpm_depend_free_storage;
    alpm_depend_object_handlers.get_properties = php_alpm_depend_get_properties;
    alpm_depend_object_handlers.read_property = php_alpm_depend_read_property;
    alpm_depend_object_handlers.write_property = php_alpm_depend_write_property;
    php_alpm_depend_sc_entry = zend_register_internal_class(&ce);
}
