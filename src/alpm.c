/*
 *  alpm.c
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

#include "php_alpm.h"
#include "php_alpm_defs.h"
#include "php_alpm_helpers.h"

#include "ext/standard/info.h"

zend_class_entry *php_alpm_handle_sc_entry;
zend_class_entry *php_alpm_handle_exception_class_entry;
zend_class_entry *php_alpm_db_sc_entry;
zend_class_entry *php_alpm_db_exception_class_entry;
zend_class_entry *php_alpm_pkg_sc_entry;
zend_class_entry *php_alpm_pkg_exception_class_entry;
zend_class_entry *php_alpm_transaction_sc_entry;
zend_class_entry *php_alpm_transaction_exception_class_entry;

static zend_object_handlers alpm_handle_object_handlers;
static zend_object_handlers alpm_db_object_handlers;
static zend_object_handlers alpm_pkg_object_handlers;
static zend_object_handlers alpm_transaction_object_handlers;

/* external api */
PHPAPI zend_class_entry *php_alpm_handle_get_class_entry() {
    return php_alpm_handle_sc_entry;
}

PHPAPI zend_class_entry *php_alpm_db_get_class_entry() {
    return php_alpm_db_sc_entry;
}

PHPAPI zend_class_entry *php_alpm_pkg_get_class_entry() {
    return php_alpm_pkg_sc_entry;
}

zend_class_entry *php_alpm_transaction_get_class_entry() {
    return php_alpm_transaction_sc_entry;
}

PHP_FUNCTION(alpm_vercmp) {
    char *ver1, *ver2;
    size_t ver1s, ver2s;
    int ret;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &ver1, &ver1s, &ver2, &ver2s) == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_vercmp(ver1, ver2);
    RETURN_LONG((long)ret)
}

PHP_FUNCTION(alpm_version) {
    RETURN_STRING(alpm_version())
}

PHP_FUNCTION(php_alpm_version) {
    RETURN_STRING(PHP_ALPM_VERSION)
}

/* arginfo goes here */

ZEND_BEGIN_ARG_INFO_EX(zero_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(two_string, 0, 0, 2)
    ZEND_ARG_INFO(0, a)
    ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(one_param_group, 0, 0, 1)
    ZEND_ARG_INFO(0, group)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_construct_args, 0, 0, 2)
    ZEND_ARG_INFO(0, root)
    ZEND_ARG_INFO(0, dbpath)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_one_param_cachedir, 0, 0, 1)
    ZEND_ARG_INFO(0, cachedir)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_one_param_assumeinstalled, 0, 0, 1)
    ZEND_ARG_INFO(0, assumeinstalled)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_one_param_hookdir, 0, 0, 1)
    ZEND_ARG_INFO(0, hookdir)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_one_param_package, 0, 0, 1)
    ZEND_ARG_INFO(0, package)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_one_param_file, 0, 0, 1)
    ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_load_pkg_args, 0, 0, 1)
    ZEND_ARG_INFO(0, filename)
    ZEND_ARG_INFO(0, checksig)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_register_syncdb_args, 0, 0, 2)
    ZEND_ARG_INFO(0, dbname)
    ZEND_ARG_INFO(0, pgp_level)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_set_arch_args, 0, 0, 1)
    ZEND_ARG_INFO(0, arch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_set_checkspace_args, 0, 0, 1)
    ZEND_ARG_INFO(0, checkspace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_init_trans_args, 0, 0, 0)
    ZEND_ARG_INFO(0, nodeps)
    ZEND_ARG_INFO(0, force)
    ZEND_ARG_INFO(0, nosave)
    ZEND_ARG_INFO(0, nodepversion)
    ZEND_ARG_INFO(0, cascade)
    ZEND_ARG_INFO(0, recurse)
    ZEND_ARG_INFO(0, dbonly)
    ZEND_ARG_INFO(0, alldeps)
    ZEND_ARG_INFO(0, downloadonly)
    ZEND_ARG_INFO(0, noscriptlet)
    ZEND_ARG_INFO(0, noconflicts)
    ZEND_ARG_INFO(0, needed)
    ZEND_ARG_INFO(0, allexplicit)
    ZEND_ARG_INFO(0, unneeded)
    ZEND_ARG_INFO(0, recurseall)
    ZEND_ARG_INFO(0, nolock)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(db_server_args, 0, 0, 1)
    ZEND_ARG_INFO(0, server)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(db_search, 0, 0, 1)
    ZEND_ARG_ARRAY_INFO(0, search, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(db_update, 0, 0, 0)
    ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(pkg_reason, 0, 0, 1)
    ZEND_ARG_INFO(0, reason)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(one_alpmpkg, 0, 0, 1)
    ZEND_ARG_OBJ_INFO(1, pkg, AlpmPkg, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(sysupdate, 0, 0, 0)
    ZEND_ARG_INFO(0, do_downgrade)
ZEND_END_ARG_INFO()

static zend_function_entry php_alpm_functions[] = {
    PHP_FE(alpm_vercmp,      two_string)
    PHP_FE(alpm_version,     zero_args)
    PHP_FE(php_alpm_version, zero_args)
    {NULL, NULL, NULL}
};

static zend_function_entry handle_methods[] = {
    PHP_ME(Handle, __construct,            handle_construct_args,             ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(Handle, __toString,             zero_args,                         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_assumeinstalled,    handle_one_param_assumeinstalled,  ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_cachedir,           handle_one_param_cachedir,         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_hookdir,            handle_one_param_hookdir,          ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_ignoregrp,          one_param_group,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_ignorepkg,          handle_one_param_package,          ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_noextract,          handle_one_param_file,             ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_noupgrade,          handle_one_param_file,             ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_arch,               zero_args,                         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_dbpath,             zero_args,                         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_cachedirs,          zero_args,                         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_checkspace,         zero_args,                         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_ignoregrps,         zero_args,                         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_ignorepkgs,         zero_args,                         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_localdb,            zero_args,                         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_noextracts,         zero_args,                         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_noupgrades,         zero_args,                         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_syncdbs,            zero_args,                         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, init_transaction,       handle_init_trans_args,            ZEND_ACC_PUBLIC)
    PHP_ME(Handle, load_pkg,               handle_load_pkg_args,              ZEND_ACC_PUBLIC)
    PHP_ME(Handle, register_syncdb,        handle_register_syncdb_args,       ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_assumeinstalled, handle_one_param_assumeinstalled,  ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_cachedir,        handle_one_param_cachedir,         ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_hookdir,         handle_one_param_hookdir,          ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_ignoregrp,       one_param_group,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_ignorepkg,       handle_one_param_package,          ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_noextract,       handle_one_param_file,             ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_noupgrade,       handle_one_param_file,             ZEND_ACC_PUBLIC)
    PHP_ME(Handle, set_arch,               handle_set_arch_args,              ZEND_ACC_PUBLIC)
    PHP_ME(Handle, set_checkspace,         handle_set_checkspace_args,        ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_function_entry db_methods[] = {
    /* PHP_ME(Db, __construct,    NULL, ZEND_ACC_PRIVATE|ZEND_ACC_CTOR) */
    PHP_ME(Db, __toString,     zero_args,           ZEND_ACC_PUBLIC)
    PHP_ME(Db, add_server,     db_server_args,      ZEND_ACC_PUBLIC)
    PHP_ME(Db, get_grpcache,   zero_args,           ZEND_ACC_PUBLIC)
    PHP_ME(Db, get_name,       zero_args,           ZEND_ACC_PUBLIC)
    PHP_ME(Db, get_pkg,        zero_args,           ZEND_ACC_PUBLIC)
    PHP_ME(Db, get_pkgcache,   zero_args,           ZEND_ACC_PUBLIC)
    PHP_ME(Db, get_servers,    zero_args,           ZEND_ACC_PUBLIC)
    PHP_ME(Db, search,         db_search,           ZEND_ACC_PUBLIC)
    PHP_ME(Db, read_grp,       one_param_group,     ZEND_ACC_PUBLIC)
    PHP_ME(Db, remove_server,  db_server_args,      ZEND_ACC_PUBLIC)
    PHP_ME(Db, update,         db_update,           ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_function_entry pkg_methods[] = {
    /* PHP_ME(Pkg, __construct,        NULL, ZEND_ACC_PRIVATE|ZEND_ACC_CTOR) */
    PHP_ME(Pkg, __toString,         zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, compute_requiredby, zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_arch,           zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_backup,         zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_base64_sig,     zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_builddate,      zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_conflicts,      zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_db,             zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_depends,        zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_desc,           zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_download_size,  zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_filename,       zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_files,          zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_groups,         zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_has_scriptlet,  zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_installdate,    zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_isize,          zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_licenses,       zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_md5sum,         zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_name,           zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_optdepends,     zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_packager,       zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_provides,       zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_reason,         zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_replaces,       zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_sha256sum,      zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_size,           zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_url,            zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, get_version,        zero_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Pkg, set_reason,         pkg_reason, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_function_entry trans_methods[] = {
    PHP_ME(Trans, add_pkg,        one_alpmpkg, ZEND_ACC_PUBLIC)
    PHP_ME(Trans, commit,         zero_args,   ZEND_ACC_PUBLIC)
    PHP_ME(Trans, interrupt,      zero_args,   ZEND_ACC_PUBLIC)
    PHP_ME(Trans, prepare,        zero_args,   ZEND_ACC_PUBLIC)
    PHP_ME(Trans, release,        zero_args,   ZEND_ACC_PUBLIC)
    PHP_ME(Trans, remove_pkg,     one_alpmpkg, ZEND_ACC_PUBLIC)
    PHP_ME(Trans, system_upgrade, sysupdate,   ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static void php_alpm_handle_free_storage(zend_object *obj) {
    php_alpm_handle_object *intern = php_alpm_handle_fetch_object(obj);

    if (!intern) {
        return;
    }

    if (intern->handle) {
        alpm_release(intern->handle);
        intern->handle = NULL;
    }

    zend_object_std_dtor(&intern->zo);
}

static void php_alpm_db_free_storage(zend_object *obj) {
    php_alpm_db_object *intern = php_alpm_db_fetch_object(obj);

    if (!intern) {
        return;
    }

    if (intern->db) {
        intern->db = NULL;
    }

    zend_object_std_dtor(&intern->zo);
}

static void php_alpm_pkg_free_storage(zend_object *obj) {
    php_alpm_pkg_object *intern = php_alpm_pkg_fetch_object(obj);

    if (!intern) {
        return;
    }

    if (intern->pkg) {
        intern->pkg = NULL;
    }

    zend_object_std_dtor(&intern->zo);
}

static void php_alpm_transaction_free_storage(zend_object *obj) {
    php_alpm_transaction_object *intern = php_alpm_transaction_fetch_object(obj);

    if (!intern) {
        return;
    }

    if (intern->handle) {
        intern->handle = NULL;
    }

    zend_object_std_dtor(&intern->zo);
}

static zend_object *php_alpm_handle_object_new_ex(zend_class_entry *class_type, php_alpm_handle_object **ptr) {
    php_alpm_handle_object *intern;

    intern = ecalloc(1, sizeof(php_alpm_handle_object) + sizeof(zval) * (class_type->default_properties_count - 1));

    if (ptr) {
        *ptr = intern;
    }

    intern->handle = NULL;

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->zo.handlers = &alpm_handle_object_handlers;
    return &intern->zo;
}

static zend_object *php_alpm_handle_object_new(zend_class_entry *class_type) {
    return php_alpm_handle_object_new_ex(class_type, NULL);
}

static zend_object *php_alpm_db_object_new_ex(zend_class_entry *class_type, php_alpm_db_object **ptr) {
    php_alpm_db_object *intern;

    intern = ecalloc(1, sizeof(php_alpm_db_object) + sizeof(zval) * (class_type->default_properties_count - 1));

    if (ptr) {
        *ptr = intern;
    }

    intern->db = NULL;

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->zo.handlers = &alpm_db_object_handlers;
    return &intern->zo;
}

static zend_object *php_alpm_db_object_new(zend_class_entry *class_type) {
    return php_alpm_db_object_new_ex(class_type, NULL);
}

static zend_object *php_alpm_pkg_object_new_ex(zend_class_entry *class_type, php_alpm_pkg_object **ptr) {
    php_alpm_pkg_object *intern;

    intern = ecalloc(1, sizeof(php_alpm_pkg_object) + sizeof(zval) * (class_type->default_properties_count - 1));

    if (ptr) {
        *ptr = intern;
    }

    intern->pkg = NULL;

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->zo.handlers = &alpm_pkg_object_handlers;
    return &intern->zo;
}

static zend_object *php_alpm_pkg_object_new(zend_class_entry *class_type) {
    return php_alpm_pkg_object_new_ex(class_type, NULL);
}

static zend_object *php_alpm_transaction_object_new_ex(zend_class_entry *class_type, php_alpm_transaction_object **ptr) {
    php_alpm_transaction_object *intern;

    intern = ecalloc(1, sizeof(php_alpm_transaction_object) + sizeof(zval) * (class_type->default_properties_count - 1));

    if (ptr) {
        *ptr = intern;
    }

    intern->handle = NULL;

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->zo.handlers = &alpm_transaction_object_handlers;
    return &intern->zo;
}

static zend_object *php_alpm_transaction_object_new(zend_class_entry *class_type) {
    return php_alpm_transaction_object_new_ex(class_type, NULL);
}

/* callback attributes
 *
 * I'm not a big fan of how this is implemented (because multiple AlpmHandle
 * objects will have the same callbacks, but it is beyond me how to implement
 * this feature. This is also consistent with pyalpm (the project php-alpm is
 * modeled against). If ANYONE has a better method of implementing this, I
 * will happily accept a patch and you deserve a cookie.
 */
typedef int (*alpm_cb_setter)(alpm_handle_t*, void*);
struct _alpm_cb_getset {
    alpm_cb_setter setter;
    void *cb_wrapper;
    alpm_callback_id id;
};

static struct _alpm_cb_getset cb_getsets[N_CALLBACKS] = {
        { (alpm_cb_setter)alpm_option_set_logcb, php_alpm_logcb, CB_LOG },
        { (alpm_cb_setter)alpm_option_set_dlcb, php_alpm_dlcb, CB_DOWNLOAD },
        { (alpm_cb_setter)alpm_option_set_fetchcb, php_alpm_fetchcb, CB_FETCH },
        { (alpm_cb_setter)alpm_option_set_totaldlcb, php_alpm_totaldlcb, CB_TOTALDL },
        { (alpm_cb_setter)alpm_option_set_eventcb, php_alpm_eventcb, CB_EVENT },
        { (alpm_cb_setter)alpm_option_set_questioncb, php_alpm_questioncb, CB_QUESTION },
        { (alpm_cb_setter)alpm_option_set_progresscb, php_alpm_progresscb, CB_PROGRESS },
};

zval *global_callback_functions[N_CALLBACKS];

static zval *_get_cb_attr(php_alpm_handle_object *ho, const struct _alpm_cb_getset *closure) {
    /* TODO: Figure out how to use ho */
    zval *cb = global_callback_functions[closure->id];
    return cb;
}

static int _set_cb_attr(php_alpm_handle_object *ho, zval *value, const struct _alpm_cb_getset *closure) {
    if (Z_TYPE_P(value) == IS_NULL) {
        efree(global_callback_functions[closure->id]);
        closure->setter(ho->handle, NULL);
    } else if (zend_is_callable(value, IS_CALLABLE_CHECK_NO_ACCESS, NULL)) {
        efree(global_callback_functions[closure->id]);
        global_callback_functions[closure->id] = value;
        closure->setter(ho->handle, closure->cb_wrapper);
    } else {
        php_error(E_NOTICE, "value must be null or a callable");
        return -1;
    }

    return 0;
}
#define RET_STRING_VAL(func, type) do { \
    retval = rv; \
    const char *tmp = func(intern->type); \
    if (tmp != NULL) { \
        ZVAL_STRINGL(retval, tmp, strlen(tmp)); \
    } else { \
        ZVAL_NULL(retval); \
    } \
} while(0)

zval *php_alpm_handle_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv) {
    int ret;
    php_alpm_handle_object *intern;
    zval *retval = NULL;
    zval tmp_member;
    const zend_object_handlers *std_hnd;

    ZVAL_DEREF(member);
    if (Z_TYPE_P(member) != IS_STRING) {
        tmp_member = *member;
        zval_copy_ctor(&tmp_member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
    }

    std_hnd = zend_get_std_object_handlers();

    ret = std_hnd->has_property(object, member, type, cache_slot);

    if (ret) {
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    } else {
        intern = Z_HANDLEO_P(object);

        if (strcmp(Z_STRVAL_P(member), "arch") == 0) {
            RET_STRING_VAL(alpm_option_get_arch, handle);
        } else if (strcmp(Z_STRVAL_P(member), "assumeinstalled") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_option_get_assumeinstalled(intern->handle);
            if (ltmp != NULL) {
                alpm_depend_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "cachedirs") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_option_get_cachedirs(intern->handle);
            if (ltmp != NULL) {
                alpm_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "checkspace") == 0) {
            retval = rv;
            ZVAL_BOOL(retval, alpm_option_get_checkspace(intern->handle));
        } else if (strcmp(Z_STRVAL_P(member), "dbext") == 0) {
            RET_STRING_VAL(alpm_option_get_dbext, handle);
        } else if (strcmp(Z_STRVAL_P(member), "dbpath") == 0) {
            RET_STRING_VAL(alpm_option_get_dbpath, handle);
        } else if (strcmp(Z_STRVAL_P(member), "default_siglevel") == 0) {
            retval = rv;
            ZVAL_LONG(retval, alpm_option_get_default_siglevel(intern->handle));
        } else if (strcmp(Z_STRVAL_P(member), "deltaratio") == 0) {
            retval = rv;
            ZVAL_DOUBLE(retval, alpm_option_get_deltaratio(intern->handle));
        } else if (strcmp(Z_STRVAL_P(member), "dlcb") == 0) {
            retval = rv;
            zval *tmp;
            struct _alpm_cb_getset closure = cb_getsets[CB_DOWNLOAD];
            tmp = _get_cb_attr(intern, &closure);
            if (Z_TYPE_P(tmp) == IS_STRING) {
                ZVAL_STRING(retval, Z_STRVAL_P(tmp));
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "eventcb") == 0) {
            retval = rv;
            zval *tmp;
            struct _alpm_cb_getset closure = cb_getsets[CB_EVENT];
            tmp = _get_cb_attr(intern, &closure);
            if (Z_TYPE_P(tmp) == IS_STRING) {
                ZVAL_STRING(retval, Z_STRVAL_P(tmp));
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "fetchcb") == 0) {
            retval = rv;
            zval *tmp;
            struct _alpm_cb_getset closure = cb_getsets[CB_FETCH];
            tmp = _get_cb_attr(intern, &closure);
            if (Z_TYPE_P(tmp) == IS_STRING) {
                ZVAL_STRING(retval, Z_STRVAL_P(tmp));
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "gpgdir") == 0) {
            RET_STRING_VAL(alpm_option_get_gpgdir, handle);
        } else if (strcmp(Z_STRVAL_P(member), "hookdirs") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_option_get_hookdirs(intern->handle);
            if (ltmp != NULL) {
                alpm_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "ignoregrps") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_option_get_ignoregroups(intern->handle);
            if (ltmp != NULL) {
                alpm_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "ignorepkgs") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_option_get_ignorepkgs(intern->handle);
            if (ltmp != NULL) {
                alpm_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "local_file_siglevel") == 0) {
            retval = rv;
            ZVAL_LONG(retval, alpm_option_get_local_file_siglevel(intern->handle));
        } else if (strcmp(Z_STRVAL_P(member), "lockfile") == 0) {
            RET_STRING_VAL(alpm_option_get_lockfile, handle);
        } else if (strcmp(Z_STRVAL_P(member), "logcb") == 0) {
            retval = rv;
            zval *tmp;
            struct _alpm_cb_getset closure = cb_getsets[CB_LOG];
            tmp = _get_cb_attr(intern, &closure);
            if (Z_TYPE_P(tmp) == IS_STRING) {
                ZVAL_STRING(retval, Z_STRVAL_P(tmp));
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "logfile") == 0) {
            RET_STRING_VAL(alpm_option_get_logfile, handle);
        } else if (strcmp(Z_STRVAL_P(member), "noextracts") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_option_get_noextracts(intern->handle);
            if (ltmp != NULL) {
                alpm_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "noupgrades") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_option_get_noupgrades(intern->handle);
            if (ltmp != NULL) {
                alpm_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "progresscb") == 0) {
            retval = rv;
            zval *tmp;
            struct _alpm_cb_getset closure = cb_getsets[CB_PROGRESS];
            tmp = _get_cb_attr(intern, &closure);
            if (Z_TYPE_P(tmp) == IS_STRING) {
                ZVAL_STRING(retval, Z_STRVAL_P(tmp));
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "questioncb") == 0) {
            retval = rv;
            zval *tmp;
            struct _alpm_cb_getset closure = cb_getsets[CB_QUESTION];
            tmp = _get_cb_attr(intern, &closure);
            if (Z_TYPE_P(tmp) == IS_STRING) {
                ZVAL_STRING(retval, Z_STRVAL_P(tmp));
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "remote_file_siglevel") == 0) {
            retval = rv;
            ZVAL_LONG(retval, alpm_option_get_remote_file_siglevel(intern->handle));
        } else if (strcmp(Z_STRVAL_P(member), "root") == 0) {
            RET_STRING_VAL(alpm_option_get_root, handle);
        } else if (strcmp(Z_STRVAL_P(member), "totaldlcb") == 0) {
            retval = rv;
            zval *tmp;
            struct _alpm_cb_getset closure = cb_getsets[CB_TOTALDL];
            tmp = _get_cb_attr(intern, &closure);
            if (Z_TYPE_P(tmp) == IS_STRING) {
                ZVAL_STRING(retval, Z_STRVAL_P(tmp));
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "usesyslog") == 0) {
            retval = rv;
            ZVAL_BOOL(retval, alpm_option_get_usesyslog(intern->handle));
        }
    }

    if (!retval) {
        retval = &EG(uninitialized_zval);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }

    return retval;
}

zval *php_alpm_db_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv) {
    int ret;
    php_alpm_db_object *intern;
    zval *retval = NULL;
    zval tmp_member;
    const zend_object_handlers *std_hnd;

    ZVAL_DEREF(member);
    if (Z_TYPE_P(member) != IS_STRING) {
        tmp_member = *member;
        zval_copy_ctor(&tmp_member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
    }

    std_hnd = zend_get_std_object_handlers();

    ret = std_hnd->has_property(object, member, type, cache_slot);

    if (ret) {
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    } else {
        intern = Z_DBO_P(object);

        if (strcmp(Z_STRVAL_P(member), "grpcache") == 0) {
            alpm_list_t *list = alpm_db_get_groupcache(intern->db);
            if (list != NULL) {
                retval = rv;
                alpm_group_list_to_zval(list, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "name") == 0) {
            RET_STRING_VAL(alpm_db_get_name, db);
        } else if (strcmp(Z_STRVAL_P(member), "pkgcache") == 0) {
            retval = rv;
            alpm_list_t *list = alpm_db_get_pkgcache(intern->db);
            if (list != NULL) {
                alpm_pkg_list_to_zval(list, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "servers") == 0) {
            retval = rv;
            alpm_list_t *list = alpm_db_get_servers(intern->db);
            if (list != NULL) {
                alpm_list_to_zval(list, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "siglevel") == 0) {
            retval = rv;
            ZVAL_LONG(retval, alpm_db_get_siglevel(intern->db));
        } else if (strcmp(Z_STRVAL_P(member), "usage") == 0) {
            retval = rv;
            alpm_db_usage_t tmp;
            alpm_db_get_usage(intern->db, (void*)&tmp);
            ZVAL_LONG(retval, tmp);
        } else if (strcmp(Z_STRVAL_P(member), "valid") == 0) {
            retval = rv;
            ZVAL_BOOL(retval, alpm_db_get_valid(intern->db) == 0 ? IS_TRUE : IS_FALSE);
        }
    }

    if (!retval) {
        retval = &EG(uninitialized_zval);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }

    return retval;
}

zval *php_alpm_pkg_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv) {
    int ret;
    php_alpm_pkg_object *intern;
    zval *retval = NULL;
    zval tmp_member;
    const zend_object_handlers *std_hnd;

    ZVAL_DEREF(member);
    if (Z_TYPE_P(member) != IS_STRING) {
        tmp_member = *member;
        zval_copy_ctor(&tmp_member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
    }

    std_hnd = zend_get_std_object_handlers();

    ret = std_hnd->has_property(object, member, type, cache_slot);

    if (ret) {
        retval = std_hnd->read_property(object, member, type, cache_slot, rv);
    } else {
        intern = Z_PKGO_P(object);

        if (strcmp(Z_STRVAL_P(member), "arch") == 0) {
            RET_STRING_VAL(alpm_pkg_get_arch, pkg);
        } else if (strcmp(Z_STRVAL_P(member), "backup") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_pkg_get_backup(intern->pkg);
            if (ltmp != NULL) {
                alpm_backup_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "base") == 0) {
            RET_STRING_VAL(alpm_pkg_get_base, pkg);
        } else if (strcmp(Z_STRVAL_P(member), "base64_sig") == 0) {
            RET_STRING_VAL(alpm_pkg_get_base64_sig, pkg);
        } else if (strcmp(Z_STRVAL_P(member), "builddate") == 0) {
            retval = rv;
            long lotmp = alpm_pkg_get_builddate(intern->pkg);
            ZVAL_LONG(retval, lotmp);
        } else if (strcmp(Z_STRVAL_P(member), "conflicts") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_pkg_get_conflicts(intern->pkg);
            if (ltmp != NULL) {
                alpm_depend_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "db") == 0) {
            retval = rv;
            alpm_db_t *dbtmp = alpm_pkg_get_db(intern->pkg);
            if (dbtmp != NULL) {
                object_init_ex(retval, php_alpm_db_sc_entry);
                php_alpm_db_object *db_object = Z_DBO_P(retval);
                db_object->db = dbtmp;
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "deltas") == 0) {
            retval = rv;
            alpm_list_t *list = alpm_pkg_get_deltas(intern->pkg);
            if (list != NULL) {
                alpm_list_to_zval(list, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "depends") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_pkg_get_depends(intern->pkg);
            if (ltmp != NULL) {
                alpm_depend_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "desc") == 0) {
            RET_STRING_VAL(alpm_pkg_get_desc, pkg);
        } else if (strcmp(Z_STRVAL_P(member), "download_size") == 0) {
            retval = rv;
            long lotmp = alpm_pkg_download_size(intern->pkg);
            ZVAL_LONG(retval, lotmp);
        } else if (strcmp(Z_STRVAL_P(member), "filename") == 0) {
            RET_STRING_VAL(alpm_pkg_get_filename, pkg);
        } else if (strcmp(Z_STRVAL_P(member), "files") == 0) {
            retval = rv;
            alpm_filelist_t *fltmp = alpm_pkg_get_files(intern->pkg);
            if (fltmp != NULL) {
                alpm_filelist_to_zval(fltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "groups") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_pkg_get_groups(intern->pkg);
            if (ltmp != NULL) {
                alpm_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "has_scriptlet") == 0) {
            retval = rv;
            long lotmp = alpm_pkg_has_scriptlet(intern->pkg);
            ZVAL_BOOL(retval, lotmp);
        } else if (strcmp(Z_STRVAL_P(member), "installdate") == 0) {
            retval = rv;
            long lotmp = alpm_pkg_get_installdate(intern->pkg);
            ZVAL_LONG(retval, lotmp);
        } else if (strcmp(Z_STRVAL_P(member), "isize") == 0) {
            retval = rv;
            long lotmp = alpm_pkg_get_isize(intern->pkg);
            ZVAL_LONG(retval, lotmp);
        } else if (strcmp(Z_STRVAL_P(member), "licenses") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_pkg_get_licenses(intern->pkg);
            if (ltmp != NULL) {
                alpm_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "md5sum") == 0) {
            RET_STRING_VAL(alpm_pkg_get_md5sum, pkg);
        } else if (strcmp(Z_STRVAL_P(member), "name") == 0) {
            RET_STRING_VAL(alpm_pkg_get_name, pkg);
        } else if (strcmp(Z_STRVAL_P(member), "optdepends") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_pkg_get_optdepends(intern->pkg);
            if (ltmp != NULL) {
                alpm_depend_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "origin") == 0) {
            retval = rv;
            ZVAL_LONG(retval, alpm_pkg_get_origin(intern->pkg));
        } else if (strcmp(Z_STRVAL_P(member), "packager") == 0) {
            RET_STRING_VAL(alpm_pkg_get_packager, pkg);
        } else if (strcmp(Z_STRVAL_P(member), "provides") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_pkg_get_provides(intern->pkg);
            if (ltmp != NULL) {
                alpm_depend_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "reason") == 0) {
            retval = rv;
            long lotmp = alpm_pkg_get_reason(intern->pkg);
            ZVAL_LONG(retval, lotmp);
        } else if (strcmp(Z_STRVAL_P(member), "replaces") == 0) {
            retval = rv;
            alpm_list_t *ltmp = alpm_pkg_get_replaces(intern->pkg);
            if (ltmp != NULL) {
                alpm_depend_list_to_zval(ltmp, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "sha256sum") == 0) {
            RET_STRING_VAL(alpm_pkg_get_sha256sum, pkg);
        } else if (strcmp(Z_STRVAL_P(member), "size") == 0) {
            retval = rv;
            long lotmp = alpm_pkg_get_size(intern->pkg);
            ZVAL_LONG(retval, lotmp);
        } else if (strcmp(Z_STRVAL_P(member), "url") == 0) {
            RET_STRING_VAL(alpm_pkg_get_url, pkg);
        } else if (strcmp(Z_STRVAL_P(member), "version") == 0) {
            RET_STRING_VAL(alpm_pkg_get_version, pkg);
        } else if (strcmp(Z_STRVAL_P(member), "validation") == 0) {
            retval = rv;
            long lotmp = alpm_pkg_get_validation(intern->pkg);
            ZVAL_LONG(retval, lotmp);
        }
    }

    if (!retval) {
        retval = &EG(uninitialized_zval);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }

    return retval;
}

void php_alpm_handle_write_property(zval *object, zval *member, zval *value, void **cache_slot) {
    php_alpm_handle_object *intern;
    zval tmp_member;
    const zend_object_handlers *std_hnd;

    ZVAL_DEREF(member);
    if (Z_TYPE_P(member) != IS_STRING) {
        tmp_member = *member;
        zval_copy_ctor(&tmp_member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
    }

    std_hnd = zend_get_std_object_handlers();
    intern = Z_HANDLEO_P(object);

    if (strcmp(Z_STRVAL_P(member), "arch") == 0) {
        if (Z_TYPE_P(value) == IS_STRING) {
            alpm_option_set_arch(intern->handle, Z_STRVAL_P(value));
        } else {
            php_error(E_NOTICE, "arch must be a string");
        }
    } else if (strcmp(Z_STRVAL_P(member), "assumeinstalled") == 0) {
        php_error(E_NOTICE, "cannot set assumeinstalled directly");
    } else if (strcmp(Z_STRVAL_P(member), "cachedirs") == 0) {
        php_error(E_NOTICE, "cannot set cachedirs directly");
    } else if (strcmp(Z_STRVAL_P(member), "checkspace") == 0) {
        if (Z_TYPE_P(value) == IS_TRUE || Z_TYPE_P(value) == IS_FALSE) {
            alpm_option_set_checkspace(intern->handle, Z_TYPE_P(value) == IS_TRUE ? 1 : 0);
        } else {
            php_error(E_NOTICE, "checkspace must be a bool");
        }
    } else if (strcmp(Z_STRVAL_P(member), "dbext") == 0) {
        if (Z_TYPE_P(value) == IS_STRING) {
            alpm_option_set_dbext(intern->handle, Z_STRVAL_P(value));
        } else {
            php_error(E_NOTICE, "dbext must be a string");
        }
    } else if (strcmp(Z_STRVAL_P(member), "dbpath") == 0) {
        php_error(E_NOTICE, "Cannot set dbpath");
    } else if (strcmp(Z_STRVAL_P(member), "default_siglevel") == 0) {
        if (Z_TYPE_P(value) == IS_LONG) {
            alpm_option_set_default_siglevel(intern->handle, (alpm_siglevel_t)Z_LVAL_P(value));
        } else {
            php_error(E_NOTICE, "default_siglevel must be an integer");
        }
    } else if (strcmp(Z_STRVAL_P(member), "deltaratio") == 0) {
        if (Z_TYPE_P(value) == IS_DOUBLE) {
            alpm_option_set_deltaratio(intern->handle, Z_DVAL_P(value));
        } else if (Z_TYPE_P(value) == IS_LONG) {
            alpm_option_set_deltaratio(intern->handle, (double)(Z_LVAL_P(value)));
        } else {
            php_error(E_NOTICE, "deltaratio must be a float");
        }
    } else if (strcmp(Z_STRVAL_P(member), "dlcb") == 0) {
        struct _alpm_cb_getset closure = cb_getsets[CB_DOWNLOAD];
        _set_cb_attr(intern, value, &closure);
    } else if (strcmp(Z_STRVAL_P(member), "fetchcb") == 0) {
        struct _alpm_cb_getset closure = cb_getsets[CB_FETCH];
        _set_cb_attr(intern, value, &closure);
    } else if (strcmp(Z_STRVAL_P(member), "eventcb") == 0) {
        struct _alpm_cb_getset closure = cb_getsets[CB_EVENT];
        _set_cb_attr(intern, value, &closure);
    } else if (strcmp(Z_STRVAL_P(member), "gpgdir") == 0) {
        if (Z_TYPE_P(value) == IS_STRING) {
            alpm_option_set_gpgdir(intern->handle, Z_STRVAL_P(value));
        } else {
            php_error(E_NOTICE, "gpgdir must be a string");
        }
    } else if (strcmp(Z_STRVAL_P(member), "hookdirs") == 0) {
        php_error(E_NOTICE, "cannot set hookdirs directly");
    } else if (strcmp(Z_STRVAL_P(member), "ignoregrps") == 0) {
        php_error(E_NOTICE, "cannot set ignoregrps directly");
    } else if (strcmp(Z_STRVAL_P(member), "ignorepkgs") == 0) {
        php_error(E_NOTICE, "cannot set ignorepkgs directly");
    } else if (strcmp(Z_STRVAL_P(member), "local_file_siglevel") == 0) {
        if (Z_TYPE_P(value) == IS_LONG) {
            alpm_option_set_local_file_siglevel(intern->handle, (alpm_siglevel_t)Z_LVAL_P(value));
        } else {
            php_error(E_NOTICE, "local_file_siglevel must be an integer");
        }
    } else if (strcmp(Z_STRVAL_P(member), "lockfile") == 0) {
        php_error(E_NOTICE, "Cannot set lockfile");
    } else if (strcmp(Z_STRVAL_P(member), "logcb") == 0) {
        struct _alpm_cb_getset closure = cb_getsets[CB_LOG];
        _set_cb_attr(intern, value, &closure);
    } else if (strcmp(Z_STRVAL_P(member), "logfile") == 0) {
        if (Z_TYPE_P(value) == IS_STRING) {
            alpm_option_set_logfile(intern->handle, Z_STRVAL_P(value));
        } else {
            php_error(E_NOTICE, "logfile must be a string");
        }
    } else if (strcmp(Z_STRVAL_P(member), "noextracts") == 0) {
        php_error(E_NOTICE, "cannot set noextracts directly");
    } else if (strcmp(Z_STRVAL_P(member), "noupgrades") == 0) {
        php_error(E_NOTICE, "cannot set noupgrades directly");
    } else if (strcmp(Z_STRVAL_P(member), "progresscb") == 0) {
        struct _alpm_cb_getset closure = cb_getsets[CB_PROGRESS];
        _set_cb_attr(intern, value, &closure);
    } else if (strcmp(Z_STRVAL_P(member), "questioncb") == 0) {
        struct _alpm_cb_getset closure = cb_getsets[CB_QUESTION];
        _set_cb_attr(intern, value, &closure);
    } else if (strcmp(Z_STRVAL_P(member), "remote_file_siglevel") == 0) {
        if (Z_TYPE_P(value) == IS_LONG) {
            alpm_option_set_remote_file_siglevel(intern->handle, (alpm_siglevel_t)Z_LVAL_P(value));
        } else {
            php_error(E_NOTICE, "remote_file_siglevel must be an integer");
        }
    } else if (strcmp(Z_STRVAL_P(member), "root") == 0) {
        php_error(E_NOTICE, "Cannot set root");
    } else if (strcmp(Z_STRVAL_P(member), "totaldlcb") == 0) {
        struct _alpm_cb_getset closure = cb_getsets[CB_TOTALDL];
        _set_cb_attr(intern, value, &closure);
    } else if (strcmp(Z_STRVAL_P(member), "usesyslog") == 0) {
        if (Z_TYPE_P(value) == IS_TRUE || Z_TYPE_P(value) == IS_FALSE) {
            alpm_option_set_usesyslog(intern->handle, Z_TYPE_P(value) == IS_TRUE ? 1 : 0);
        } else {
            php_error(E_NOTICE, "usesyslog must be a bool");
        }
    } else {
        std_hnd->write_property(object, member, value, cache_slot);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }
}

void php_alpm_db_write_property(zval *object, zval *member, zval *value, void **cache_slot) {
    zval tmp_member;
    const zend_object_handlers *std_hnd;

    php_alpm_db_object *intern;
    intern = Z_DBO_P(object);

    ZVAL_DEREF(member);
    if (Z_TYPE_P(member) != IS_STRING) {
        tmp_member = *member;
        zval_copy_ctor(&tmp_member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
    }

    std_hnd = zend_get_std_object_handlers();
    if (strcmp(Z_STRVAL_P(member), "grpcache") == 0) {
        php_error(E_NOTICE, "cannot set grpcache");
    } else if (strcmp(Z_STRVAL_P(member), "name") == 0) {
        php_error(E_NOTICE, "cannot set name");
    } else if (strcmp(Z_STRVAL_P(member), "pkgcache") == 0) {
        php_error(E_NOTICE, "cannot set pkgcache");
    } else if (strcmp(Z_STRVAL_P(member), "servers") == 0) {
        php_error(E_NOTICE, "cannot set servers");
    } else if (strcmp(Z_STRVAL_P(member), "siglevel") == 0) {
        php_error(E_NOTICE, "cannot set siglevel");
    } else if (strcmp(Z_STRVAL_P(member), "usage") == 0) {
        if (Z_TYPE_P(value) == IS_LONG) {
            alpm_db_set_usage(intern->db, (alpm_db_usage_t) Z_LVAL_P(value));
        } else {
            php_error(E_NOTICE, "usage must be type long");
        }
    } else if (strcmp(Z_STRVAL_P(member), "valid") == 0) {
        php_error(E_NOTICE, "cannot set valid");
    } else {
        std_hnd->write_property(object, member, value, cache_slot);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }
}

void php_alpm_pkg_write_property(zval *object, zval *member, zval *value, void **cache_slot) {
    php_alpm_pkg_object *intern;
    zval tmp_member;
    const zend_object_handlers *std_hnd;

    ZVAL_DEREF(member);
    if (Z_TYPE_P(member) != IS_STRING) {
        tmp_member = *member;
        zval_copy_ctor(&tmp_member);
        convert_to_string(&tmp_member);
        member = &tmp_member;
    }

    std_hnd = zend_get_std_object_handlers();
    intern = Z_PKGO_P(object);

    if (strcmp(Z_STRVAL_P(member), "arch") == 0) {
        php_error(E_NOTICE, "cannot set arch");
    } else if (strcmp(Z_STRVAL_P(member), "backup") == 0) {
        php_error(E_NOTICE, "cannot set backup");
    } else if (strcmp(Z_STRVAL_P(member), "base") == 0) {
        php_error(E_NOTICE, "cannot set base");
    } else if (strcmp(Z_STRVAL_P(member), "base64_sig") == 0) {
        php_error(E_NOTICE, "cannot set base64_sig");
    } else if (strcmp(Z_STRVAL_P(member), "builddate") == 0) {
        php_error(E_NOTICE, "cannot set builddate");
    } else if (strcmp(Z_STRVAL_P(member), "conflicts") == 0) {
        php_error(E_NOTICE, "cannot set conflicts");
    } else if (strcmp(Z_STRVAL_P(member), "db") == 0) {
        php_error(E_NOTICE, "cannot set db");
    } else if (strcmp(Z_STRVAL_P(member), "deltas") == 0) {
        php_error(E_NOTICE, "cannot set deltas");
    } else if (strcmp(Z_STRVAL_P(member), "depends") == 0) {
        php_error(E_NOTICE, "cannot set depends");
    } else if (strcmp(Z_STRVAL_P(member), "desc") == 0) {
        php_error(E_NOTICE, "cannot set desc");
    } else if (strcmp(Z_STRVAL_P(member), "download_size") == 0) {
        php_error(E_NOTICE, "cannot set download_size");
    } else if (strcmp(Z_STRVAL_P(member), "filename") == 0) {
        php_error(E_NOTICE, "cannot set filename");
    } else if (strcmp(Z_STRVAL_P(member), "files") == 0) {
        php_error(E_NOTICE, "cannot set files");
    } else if (strcmp(Z_STRVAL_P(member), "groups") == 0) {
        php_error(E_NOTICE, "cannot set groups");
    } else if (strcmp(Z_STRVAL_P(member), "has_scriptlet") == 0) {
        php_error(E_NOTICE, "cannot set has_scriptlet");
    } else if (strcmp(Z_STRVAL_P(member), "installdate") == 0) {
        php_error(E_NOTICE, "cannot set installdate");
    } else if (strcmp(Z_STRVAL_P(member), "isize") == 0) {
        php_error(E_NOTICE, "cannot set isize");
    } else if (strcmp(Z_STRVAL_P(member), "licenses") == 0) {
        php_error(E_NOTICE, "cannot set licenses");
    } else if (strcmp(Z_STRVAL_P(member), "md5sum") == 0) {
        php_error(E_NOTICE, "cannot set md5sum");
    } else if (strcmp(Z_STRVAL_P(member), "name") == 0) {
        php_error(E_NOTICE, "cannot set name");
    } else if (strcmp(Z_STRVAL_P(member), "optdepends") == 0) {
        php_error(E_NOTICE, "cannot set optdepends");
    } else if (strcmp(Z_STRVAL_P(member), "origin") == 0) {
        php_error(E_NOTICE, "cannot set origin");
    } else if (strcmp(Z_STRVAL_P(member), "packager") == 0) {
        php_error(E_NOTICE, "cannot set packager");
    } else if (strcmp(Z_STRVAL_P(member), "provides") == 0) {
        php_error(E_NOTICE, "cannot set provides");
    } else if (strcmp(Z_STRVAL_P(member), "reason") == 0) {
        if (Z_TYPE_P(value) == IS_LONG) {
            alpm_pkg_set_reason(intern->pkg, (alpm_pkgreason_t)Z_LVAL_P(value));
        } else {
            php_error(E_NOTICE, "reason must be type long");
        }
    } else if (strcmp(Z_STRVAL_P(member), "replaces") == 0) {
        php_error(E_NOTICE, "cannot set replaces");
    } else if (strcmp(Z_STRVAL_P(member), "sha256sum") == 0) {
        php_error(E_NOTICE, "cannot set sha256sum");
    } else if (strcmp(Z_STRVAL_P(member), "size") == 0) {
        php_error(E_NOTICE, "cannot set size");
    } else if (strcmp(Z_STRVAL_P(member), "url") == 0) {
        php_error(E_NOTICE, "cannot set url");
    } else if (strcmp(Z_STRVAL_P(member), "version") == 0) {
        php_error(E_NOTICE, "cannot set version");
    } else if (strcmp(Z_STRVAL_P(member), "validation") == 0) {
        php_error(E_NOTICE, "cannot set validation");
    } else {
        std_hnd->write_property(object, member, value, cache_slot);
    }

    if (member == &tmp_member) {
        zval_dtor(member);
    }
}

#define ADD_STRING_TO_HASH(func, type, keyname) do { \
    stmp = func(intern->type); \
    if (stmp != NULL) { \
        val = zend_string_init(stmp, strlen(stmp), 0); \
        ZVAL_STR(&zv, val); \
    } else { \
        ZVAL_NULL(&zv); \
    } \
    key = zend_string_init(keyname, strlen(keyname), 0); \
    zend_hash_add(props, key, &zv); \
    zend_string_release(key); \
} while (0)

static int hashtable_key_cmp(const void *a, const void *b) {
    Bucket *f = (Bucket *) a;
    Bucket *s = (Bucket *) b;
    zend_uchar t;
    zend_long l1, l2;
    double d;

    if (f->key == NULL) {
        if (s->key == NULL) {
            return (zend_long)f->h > (zend_long)s->h ? 1 : -1;
        } else {
            l1 = (zend_long)f->h;
            t = is_numeric_string(s->key->val, s->key->len, &l2, &d, 1);
            if (t == IS_LONG) {
                /* do nothing */
            } else if (t == IS_DOUBLE) {
                return ZEND_NORMALIZE_BOOL((double)l1 - d);
            } else {
                l2 = 0;
            }
        }
    } else {
        if (s->key) {
            return (int) zendi_smart_strcmp(f->key, s->key);
        } else {
            l2 = (zend_long)s->h;
            t = is_numeric_string(f->key->val, f->key->len, &l1, &d, 1);
            if (t == IS_LONG) {
                /* no nothing */
            } else if (t == IS_DOUBLE) {
                return ZEND_NORMALIZE_BOOL(d - (double)l2);
            } else {
                l1 = 0;
            }
        }
    }
    return l1 > l2 ? 1 : (l1 < l2 ? -1 : 0);
}

static HashTable *php_alpm_handle_get_properties(zval *object) {
    php_alpm_handle_object *intern;
    HashTable *props;
    zend_string *key, *val;
    zval zv, *zv2;
    const char *stmp;
    int itmp;
    double dtmp;
    long lotmp;
    alpm_list_t *ltmp;

    props = zend_std_get_properties(object);
    intern = Z_HANDLEO_P(object);

    ADD_STRING_TO_HASH(alpm_option_get_arch, handle, "arch");

    ltmp = alpm_option_get_assumeinstalled(intern->handle);
    if (ltmp != NULL) {
        alpm_depend_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("assumeinstalled", strlen("assumeinstalled"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ltmp = alpm_option_get_cachedirs(intern->handle);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("cachedirs", strlen("cachedrs"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    itmp = alpm_option_get_checkspace(intern->handle);
    ZVAL_BOOL(&zv, itmp);
    key = zend_string_init("checkspace", strlen("checkspace"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_option_get_dbext, handle, "dbext");
    ADD_STRING_TO_HASH(alpm_option_get_dbpath, handle, "dbpath");

    lotmp = alpm_option_get_default_siglevel(intern->handle);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("default_siglevel", strlen("default_siglevel"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    dtmp = alpm_option_get_deltaratio(intern->handle);
    ZVAL_DOUBLE(&zv, dtmp);
    key = zend_string_init("deltaratio", strlen("deltaratio"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    zv2 = global_callback_functions[CB_DOWNLOAD];
    if (zv2 == NULL) {
        ZVAL_NULL(&zv);
    } else if (Z_TYPE_P(zv2) == IS_STRING) {
        ZVAL_STRING(&zv, Z_STRVAL_P(zv2));
    }
    key = zend_string_init("dlcb", strlen("dlcb"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    zv2 = global_callback_functions[CB_EVENT];
    if (zv2 == NULL) {
        ZVAL_NULL(&zv);
    } else if (Z_TYPE_P(zv2) == IS_STRING) {
        ZVAL_STRING(&zv, Z_STRVAL_P(zv2));
    }
    key = zend_string_init("eventcb", strlen("eventcb"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    zv2 = global_callback_functions[CB_FETCH];
    if (zv2 == NULL) {
        ZVAL_NULL(&zv);
    } else if (Z_TYPE_P(zv2) == IS_STRING) {
        ZVAL_STRING(&zv, Z_STRVAL_P(zv2));
    }
    key = zend_string_init("fetchcb", strlen("fetchcb"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_option_get_gpgdir, handle, "gpgdir");

    ltmp = alpm_option_get_hookdirs(intern->handle);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("hookdirs", strlen("hookdirs"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ltmp = alpm_option_get_ignoregroups(intern->handle);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("ignoregrps", strlen("ignoregrps"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ltmp = alpm_option_get_ignorepkgs(intern->handle);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("ignorepkgs", strlen("ignorepkgs"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    lotmp = alpm_option_get_local_file_siglevel(intern->handle);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("local_file_siglevel", strlen("local_file_siglevel"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_option_get_lockfile, handle, "lockfile");

    zv2 = global_callback_functions[CB_LOG];
    if (zv2 == NULL) {
        ZVAL_NULL(&zv);
    } else if (Z_TYPE_P(zv2) == IS_STRING) {
        ZVAL_STRING(&zv, Z_STRVAL_P(zv2));
    }
    key = zend_string_init("logcb", strlen("logcb"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_option_get_logfile, handle, "logfile");

    ltmp = alpm_option_get_noextracts(intern->handle);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("noextracts", strlen("noextracts"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ltmp = alpm_option_get_noupgrades(intern->handle);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("noupgrades", strlen("noupgrades"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    zv2 = global_callback_functions[CB_PROGRESS];
    if (zv2 == NULL) {
        ZVAL_NULL(&zv);
    } else if (Z_TYPE_P(zv2) == IS_STRING) {
        ZVAL_STRING(&zv, Z_STRVAL_P(zv2));
    }
    key = zend_string_init("progresscb", strlen("progresscb"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    zv2 = global_callback_functions[CB_QUESTION];
    if (zv2 == NULL) {
        ZVAL_NULL(&zv);
    } else if (Z_TYPE_P(zv2) == IS_STRING) {
        ZVAL_STRING(&zv, Z_STRVAL_P(zv2));
    }
    key = zend_string_init("questioncb", strlen("questioncb"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    lotmp = alpm_option_get_remote_file_siglevel(intern->handle);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("remote_file_siglevel", strlen("remote_file_siglevel"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_option_get_root, handle, "root");

    zv2 = global_callback_functions[CB_TOTALDL];
    if (zv2 == NULL) {
        ZVAL_NULL(&zv);
    } else if (Z_TYPE_P(zv2) == IS_STRING) {
        ZVAL_STRING(&zv, Z_STRVAL_P(zv2));
    }
    key = zend_string_init("totaldlcb", strlen("totaldlcb"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    itmp = alpm_option_get_usesyslog(intern->handle);
    ZVAL_BOOL(&zv, itmp);
    key = zend_string_init("usesyslog", strlen("usesyslog"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    zend_hash_sort(props, hashtable_key_cmp, 0);

    return props;
}

static HashTable *php_alpm_db_get_properties(zval *object) {
    php_alpm_db_object *intern;
    HashTable *props;
    zend_string *key, *val;
    zval zv;
    alpm_db_usage_t utmp;
    const char *stmp;
    long lotmp;
    alpm_list_t *ltmp;

    props = zend_std_get_properties(object);
    intern = Z_DBO_P(object);

    ltmp = alpm_db_get_groupcache(intern->db);
    if (ltmp != NULL) {
        alpm_group_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("grpcache", strlen("grpcache"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_db_get_name, db, "name");

    ltmp = alpm_db_get_pkgcache(intern->db);
    if (ltmp != NULL) {
        alpm_pkg_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("pkgcache", strlen("pkgcache"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ltmp = alpm_db_get_servers(intern->db);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("servers", strlen("servers"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    lotmp = alpm_db_get_siglevel(intern->db);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("siglevel", strlen("siglevel"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    alpm_db_get_usage(intern->db, (void*)&utmp);
    ZVAL_LONG(&zv, (long)utmp);
    key = zend_string_init("usage", strlen("usage"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    lotmp = alpm_db_get_valid(intern->db);
    ZVAL_BOOL(&zv, lotmp == 0 ? IS_TRUE : IS_FALSE);
    key = zend_string_init("valid", strlen("valid"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    zend_hash_sort(props, hashtable_key_cmp, 0);

    return props;
}

static HashTable *php_alpm_pkg_get_properties(zval *object) {
    php_alpm_pkg_object *intern;
    HashTable *props;
    zend_string *key, *val;
    zval zv;
    const char *stmp;
    int itmp;
    long lotmp;
    alpm_filelist_t *ftmp;
    alpm_list_t *ltmp;
    alpm_db_t *dbtmp;

    props = zend_std_get_properties(object);
    intern = Z_PKGO_P(object);

    ADD_STRING_TO_HASH(alpm_pkg_get_arch, pkg, "arch");

    ltmp = alpm_pkg_get_backup(intern->pkg);
    if (ltmp != NULL) {
        alpm_backup_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("backup", strlen("backup"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_pkg_get_base, pkg, "base");
    ADD_STRING_TO_HASH(alpm_pkg_get_base64_sig, pkg, "base64_sig");

    ltmp = alpm_pkg_get_conflicts(intern->pkg);
    if (ltmp != NULL) {
        alpm_depend_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("conflicts", strlen("conflicts"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    dbtmp = alpm_pkg_get_db(intern->pkg);
    if (dbtmp != NULL) {
        object_init_ex(&zv, php_alpm_db_sc_entry);
        php_alpm_db_object *db = Z_DBO_P(&zv);
        db->db = dbtmp;
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("db", strlen("db"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ltmp = alpm_pkg_get_deltas(intern->pkg);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("deltas", strlen("deltas"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ltmp = alpm_pkg_get_depends(intern->pkg);
    if (ltmp != NULL) {
        alpm_depend_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("depends", strlen("depends"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_pkg_get_desc, pkg, "desc");

    lotmp = (long)alpm_pkg_download_size(intern->pkg);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("download_size", strlen("download_size"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_pkg_get_filename, pkg, "filename");

    ftmp = alpm_pkg_get_files(intern->pkg);
    if (ftmp != NULL) {
        alpm_filelist_to_zval(ftmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("files", strlen("files"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ltmp = alpm_pkg_get_groups(intern->pkg);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("groups", strlen("groups"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    itmp = alpm_pkg_has_scriptlet(intern->pkg);
    ZVAL_BOOL(&zv, itmp);
    key = zend_string_init("has_scriptlet", strlen("has_scriptlet"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    lotmp = alpm_pkg_get_installdate(intern->pkg);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("installdate", strlen("installdate"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    lotmp = alpm_pkg_get_isize(intern->pkg);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("isize", strlen("isize"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ltmp = alpm_pkg_get_licenses(intern->pkg);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("licenses", strlen("licenses"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_pkg_get_md5sum, pkg, "md5sum");
    ADD_STRING_TO_HASH(alpm_pkg_get_name, pkg, "name");

    ltmp = alpm_pkg_get_optdepends(intern->pkg);
    if (ltmp != NULL) {
        alpm_depend_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("optdepends", strlen("optdepends"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    lotmp = alpm_pkg_get_origin(intern->pkg);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("origin", strlen("origin"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_pkg_get_packager, pkg, "packager");

    ltmp = alpm_pkg_get_provides(intern->pkg);
    if (ltmp != NULL) {
        alpm_depend_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("provides", strlen("provides"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    itmp = alpm_pkg_get_reason(intern->pkg);
    ZVAL_LONG(&zv, itmp);
    key = zend_string_init("reason", strlen("reason"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ltmp = alpm_pkg_get_replaces(intern->pkg);
    if (ltmp != NULL) {
        alpm_depend_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("replaces", strlen("replaces"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_pkg_get_sha256sum, pkg, "sha256sum");

    lotmp = alpm_pkg_get_size(intern->pkg);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("size", strlen("size"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    ADD_STRING_TO_HASH(alpm_pkg_get_url, pkg, "url");
    ADD_STRING_TO_HASH(alpm_pkg_get_version, pkg, "version");

    lotmp = alpm_pkg_get_validation(intern->pkg);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("validation", strlen("validation"), 0);
    zend_hash_add(props, key, &zv);
    zend_string_release(key);

    zend_hash_sort(props, hashtable_key_cmp, 0);

    return props;
}

PHP_MINIT_FUNCTION(alpm) {
    zend_class_entry ce;

    memcpy(&alpm_handle_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    memcpy(&alpm_db_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    memcpy(&alpm_pkg_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    memcpy(&alpm_transaction_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

    INIT_CLASS_ENTRY(ce, PHP_ALPM_HANDLE_EXCEPTION_SC_NAME, NULL);
    php_alpm_handle_exception_class_entry = zend_register_internal_class_ex(&ce, zend_ce_exception);

    INIT_CLASS_ENTRY(ce, PHP_ALPM_DB_EXCEPTION_SC_NAME, NULL);
    php_alpm_db_exception_class_entry = zend_register_internal_class_ex(&ce, zend_ce_exception);

    INIT_CLASS_ENTRY(ce, PHP_ALPM_PKG_EXCEPTION_SC_NAME, NULL);
    php_alpm_pkg_exception_class_entry = zend_register_internal_class_ex(&ce, zend_ce_exception);

    INIT_CLASS_ENTRY(ce, PHP_ALPM_TRANSACTION_EXCEPTION_SC_NAME, NULL);
    php_alpm_transaction_exception_class_entry = zend_register_internal_class_ex(&ce, zend_ce_exception);

    INIT_CLASS_ENTRY(ce, PHP_ALPM_HANDLE_SC_NAME, handle_methods);
    ce.create_object = php_alpm_handle_object_new;
    alpm_handle_object_handlers.offset = (int) XtOffsetOf(php_alpm_handle_object, zo);
    alpm_handle_object_handlers.free_obj = php_alpm_handle_free_storage;
    alpm_handle_object_handlers.get_properties = php_alpm_handle_get_properties;
    alpm_handle_object_handlers.read_property = php_alpm_handle_read_property;
    alpm_handle_object_handlers.write_property = php_alpm_handle_write_property;
    php_alpm_handle_sc_entry = zend_register_internal_class(&ce);

    INIT_CLASS_ENTRY(ce, PHP_ALPM_DB_SC_NAME, db_methods);
    alpm_db_object_handlers.offset = (int) XtOffsetOf(php_alpm_db_object, zo);
    ce.create_object = php_alpm_db_object_new;
    alpm_db_object_handlers.free_obj = php_alpm_db_free_storage;
    alpm_db_object_handlers.get_properties = php_alpm_db_get_properties;
    alpm_db_object_handlers.read_property = php_alpm_db_read_property;
    alpm_db_object_handlers.write_property = php_alpm_db_write_property;
    php_alpm_db_sc_entry = zend_register_internal_class(&ce);

    INIT_CLASS_ENTRY(ce, PHP_ALPM_PKG_SC_NAME, pkg_methods);
    ce.create_object = php_alpm_pkg_object_new;
    alpm_pkg_object_handlers.offset = (int) XtOffsetOf(php_alpm_pkg_object, zo);
    alpm_pkg_object_handlers.free_obj = php_alpm_pkg_free_storage;
    alpm_pkg_object_handlers.get_properties = php_alpm_pkg_get_properties;
    alpm_pkg_object_handlers.read_property = php_alpm_pkg_read_property;
    alpm_pkg_object_handlers.write_property = php_alpm_pkg_write_property;
    php_alpm_pkg_sc_entry = zend_register_internal_class(&ce);

    INIT_CLASS_ENTRY(ce, PHP_ALPM_TRANSACTION_SC_NAME, trans_methods);
    ce.create_object = php_alpm_transaction_object_new;
    alpm_transaction_object_handlers.offset = (int) XtOffsetOf(php_alpm_transaction_object, zo);
    alpm_transaction_object_handlers.free_obj = php_alpm_transaction_free_storage;
    php_alpm_transaction_sc_entry = zend_register_internal_class(&ce);

    /* alpm_db_usage_t */
    REGISTER_LONG_CONSTANT("ALPM_DB_USAGE_ALL", ALPM_DB_USAGE_ALL, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_DB_USAGE_INSTALL", ALPM_DB_USAGE_INSTALL, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_DB_USAGE_SEARCH", ALPM_DB_USAGE_SEARCH, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_DB_USAGE_SYNC", ALPM_DB_USAGE_SYNC, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_DB_USAGE_UPGRADE", ALPM_DB_USAGE_UPGRADE, CONST_CS|CONST_PERSISTENT);

    /* alpm_depmod_t */
    REGISTER_LONG_CONSTANT("ALPM_DEP_MOD_ANY", ALPM_DEP_MOD_ANY, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_DEP_MOD_EQ", ALPM_DEP_MOD_EQ, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_DEP_MOD_GE", ALPM_DEP_MOD_GE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_DEP_MOD_LE", ALPM_DEP_MOD_LE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_DEP_MOD_GT", ALPM_DEP_MOD_GT, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_DEP_MOD_LT", ALPM_DEP_MOD_LT, CONST_CS|CONST_PERSISTENT);

    /* alpm_siglevel_t */
    REGISTER_LONG_CONSTANT("ALPM_SIG_PACKAGE", ALPM_SIG_PACKAGE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_SIG_PACKAGE_OPTIONAL", ALPM_SIG_PACKAGE_OPTIONAL, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_SIG_PACKAGE_MARGINAL_OK", ALPM_SIG_PACKAGE_MARGINAL_OK, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_SIG_PACKAGE_UNKNOWN_OK", ALPM_SIG_PACKAGE_UNKNOWN_OK, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_SIG_DATABASE", ALPM_SIG_DATABASE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_SIG_DATABASE_OPTIONAL", ALPM_SIG_DATABASE_OPTIONAL, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_SIG_DATABASE_MARGINAL_OK", ALPM_SIG_DATABASE_MARGINAL_OK, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_SIG_DATABASE_UNKNOWN_OK", ALPM_SIG_DATABASE_UNKNOWN_OK, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_SIG_USE_DEFAULT", ALPM_SIG_USE_DEFAULT, CONST_CS|CONST_PERSISTENT);

    /* alpm_pkgreason_t */
    REGISTER_LONG_CONSTANT("ALPM_PKG_REASON_DEPEND", ALPM_PKG_REASON_DEPEND, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_PKG_REASON_EXPLICIT", ALPM_PKG_REASON_EXPLICIT, CONST_CS|CONST_PERSISTENT);

    /* alpm_event_type_t */
    REGISTER_LONG_CONSTANT("ALPM_EVENT_CHECKDEPS_START", ALPM_EVENT_CHECKDEPS_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_CHECKDEPS_DONE", ALPM_EVENT_CHECKDEPS_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_FILECONFLICTS_START", ALPM_EVENT_FILECONFLICTS_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_FILECONFLICTS_DONE", ALPM_EVENT_FILECONFLICTS_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_RESOLVEDEPS_START", ALPM_EVENT_RESOLVEDEPS_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_RESOLVEDEPS_DONE", ALPM_EVENT_RESOLVEDEPS_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_INTERCONFLICTS_START", ALPM_EVENT_INTERCONFLICTS_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_INTERCONFLICTS_DONE", ALPM_EVENT_INTERCONFLICTS_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_TRANSACTION_START", ALPM_EVENT_TRANSACTION_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_TRANSACTION_DONE", ALPM_EVENT_TRANSACTION_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_PACKAGE_OPERATION_START", ALPM_EVENT_PACKAGE_OPERATION_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_PACKAGE_OPERATION_DONE", ALPM_EVENT_PACKAGE_OPERATION_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_INTEGRITY_START", ALPM_EVENT_INTEGRITY_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_INTEGRITY_DONE", ALPM_EVENT_INTEGRITY_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_LOAD_START", ALPM_EVENT_LOAD_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_LOAD_DONE", ALPM_EVENT_LOAD_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_DELTA_INTEGRITY_START", ALPM_EVENT_DELTA_INTEGRITY_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_DELTA_INTEGRITY_DONE", ALPM_EVENT_DELTA_INTEGRITY_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_DELTA_PATCHES_START", ALPM_EVENT_DELTA_PATCHES_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_DELTA_PATCHES_DONE", ALPM_EVENT_DELTA_PATCHES_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_DELTA_PATCH_START", ALPM_EVENT_DELTA_PATCH_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_DELTA_PATCH_DONE", ALPM_EVENT_DELTA_PATCH_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_DELTA_PATCH_FAILED", ALPM_EVENT_DELTA_PATCH_FAILED, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_SCRIPTLET_INFO", ALPM_EVENT_SCRIPTLET_INFO, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_RETRIEVE_START", ALPM_EVENT_RETRIEVE_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_RETRIEVE_DONE", ALPM_EVENT_RETRIEVE_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_RETRIEVE_FAILED", ALPM_EVENT_RETRIEVE_FAILED, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_PKGDOWNLOAD_START", ALPM_EVENT_PKGDOWNLOAD_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_PKGDOWNLOAD_DONE", ALPM_EVENT_PKGDOWNLOAD_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_PKGDOWNLOAD_FAILED", ALPM_EVENT_PKGDOWNLOAD_FAILED, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_DISKSPACE_START", ALPM_EVENT_DISKSPACE_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_DISKSPACE_DONE", ALPM_EVENT_DISKSPACE_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_OPTDEP_REMOVAL", ALPM_EVENT_OPTDEP_REMOVAL, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_DATABASE_MISSING", ALPM_EVENT_DATABASE_MISSING, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_KEYRING_START", ALPM_EVENT_KEYRING_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_KEYRING_DONE", ALPM_EVENT_KEYRING_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_KEY_DOWNLOAD_START", ALPM_EVENT_KEY_DOWNLOAD_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_KEY_DOWNLOAD_DONE", ALPM_EVENT_KEY_DOWNLOAD_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_PACNEW_CREATED", ALPM_EVENT_PACNEW_CREATED, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_PACSAVE_CREATED", ALPM_EVENT_PACSAVE_CREATED, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_HOOK_START", ALPM_EVENT_HOOK_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_HOOK_DONE", ALPM_EVENT_HOOK_DONE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_HOOK_RUN_START", ALPM_EVENT_HOOK_RUN_START, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_EVENT_HOOK_RUN_DONE", ALPM_EVENT_HOOK_RUN_DONE, CONST_CS|CONST_PERSISTENT);

    /* alpm_question_type_t */
    REGISTER_LONG_CONSTANT("ALPM_QUESTION_INSTALL_IGNOREPKG", ALPM_QUESTION_INSTALL_IGNOREPKG, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_QUESTION_REPLACE_PKG", ALPM_QUESTION_REPLACE_PKG, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_QUESTION_CONFLICT_PKG", ALPM_QUESTION_CONFLICT_PKG, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_QUESTION_CORRUPTED_PKG", ALPM_QUESTION_CORRUPTED_PKG, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_QUESTION_REMOVE_PKGS", ALPM_QUESTION_REMOVE_PKGS, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_QUESTION_SELECT_PROVIDER", ALPM_QUESTION_SELECT_PROVIDER, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("ALPM_QUESTION_IMPORT_KEY", ALPM_QUESTION_IMPORT_KEY, CONST_CS|CONST_PERSISTENT);

    return SUCCESS;
}

PHP_MINFO_FUNCTION(alpm) {
    php_info_print_table_start();
    php_info_print_table_header(2, "alpm module", "enabled");
    php_info_print_table_row(2, "alpm module version", PHP_ALPM_VERSION);
    php_info_print_table_row(2, "alpm classes", "AlpmHandle, AlpmDb, AlpmPkg, AlpmTransaction");
    php_info_print_table_row(2, "libalpm version", alpm_version());
    php_info_print_table_end();
    DISPLAY_INI_ENTRIES();
}

zend_module_entry alpm_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_ALPM_EXTNAME,
    php_alpm_functions,
    PHP_MINIT(alpm),
    NULL,
    NULL,
    NULL,
    PHP_MINFO(alpm),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_ALPM_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ALPM
ZEND_GET_MODULE(alpm)
#endif