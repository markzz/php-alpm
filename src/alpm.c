/*
 *  alpm.c
 *
 *  Copyright (c) 2016 Mark Weiman <contact@markzz.net>
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

PHP_FUNCTION(alpm_version) {
    RETURN_STRING(alpm_version())
}

PHP_FUNCTION(php_alpm_version) {
    RETURN_STRING(PHP_ALPM_VERSION)
}

/* arginfo goes here */

ZEND_BEGIN_ARG_INFO_EX(zero_args, 0, 0, 0)
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
    PHP_FE(alpm_version,     zero_args)
    PHP_FE(php_alpm_version, zero_args)
    {NULL, NULL, NULL}
};

static zend_function_entry handle_methods[] = {
    PHP_ME(Handle, __construct,      handle_construct_args,       ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(Handle, __toString,       zero_args,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_cachedir,     handle_one_param_cachedir,   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_ignoregrp,    one_param_group,             ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_ignorepkg,    handle_one_param_package,    ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_noextract,    handle_one_param_file,       ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_noupgrade,    handle_one_param_file,       ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_arch,         zero_args,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_dbpath,       zero_args,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_cachedirs,    zero_args,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_checkspace,   zero_args,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_ignoregrps,   zero_args,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_ignorepkgs,   zero_args,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_localdb,      zero_args,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_noextracts,   zero_args,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_noupgrades,   zero_args,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_syncdbs,      zero_args,                   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, init_transaction, handle_init_trans_args,      ZEND_ACC_PUBLIC)
    PHP_ME(Handle, load_pkg,         handle_load_pkg_args,        ZEND_ACC_PUBLIC)
    PHP_ME(Handle, register_syncdb,  handle_register_syncdb_args, ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_cachedir,  handle_one_param_cachedir,   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_ignoregrp, one_param_group,             ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_ignorepkg, handle_one_param_package,    ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_noextract, handle_one_param_file,       ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_noupgrade, handle_one_param_file,       ZEND_ACC_PUBLIC)
    PHP_ME(Handle, set_arch,         handle_set_arch_args,        ZEND_ACC_PUBLIC)
    PHP_ME(Handle, set_checkspace,   handle_set_checkspace_args,  ZEND_ACC_PUBLIC)
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
    zend_object_handlers *std_hnd;

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
        } else if (strcmp(Z_STRVAL_P(member), "checkspace") == 0) {
            retval = rv;
            ZVAL_BOOL(retval, alpm_option_get_checkspace(intern->handle));
        } else if (strcmp(Z_STRVAL_P(member), "dbpath") == 0) {
            RET_STRING_VAL(alpm_option_get_dbpath, handle);
        } else if (strcmp(Z_STRVAL_P(member), "deltaratio") == 0) {
            retval = rv;
            ZVAL_DOUBLE(retval, alpm_option_get_deltaratio(intern->handle));
        } else if (strcmp(Z_STRVAL_P(member), "gpgdir") == 0) {
            RET_STRING_VAL(alpm_option_get_gpgdir, handle);
        } else if (strcmp(Z_STRVAL_P(member), "lockfile") == 0) {
            RET_STRING_VAL(alpm_option_get_lockfile, handle);
        } else if (strcmp(Z_STRVAL_P(member), "logfile") == 0) {
            RET_STRING_VAL(alpm_option_get_logfile, handle);
        } else if (strcmp(Z_STRVAL_P(member), "root") == 0) {
            RET_STRING_VAL(alpm_option_get_root, handle);
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
    zend_object_handlers *std_hnd;

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
                alpm_group_list_to_zval(list, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "name") == 0) {
            RET_STRING_VAL(alpm_db_get_name, db);
        } else if (strcmp(Z_STRVAL_P(member), "pkgcache") == 0) {
            alpm_list_t *list = alpm_db_get_pkgcache(intern->db);
            if (list != NULL) {
                alpm_pkg_list_to_zval(list, retval);
            } else {
                ZVAL_NULL(retval);
            }
        } else if (strcmp(Z_STRVAL_P(member), "servers") == 0) {
            alpm_list_t *list = alpm_db_get_servers(intern->db);
            if (list != NULL) {
                alpm_list_to_zval(list, retval);
            } else {
                ZVAL_NULL(retval);
            }
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
    zend_object_handlers *std_hnd;

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
    zend_object_handlers *std_hnd;

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
    } else if (strcmp(Z_STRVAL_P(member), "checkspace") == 0) {
        if (Z_TYPE_P(value) == IS_TRUE || Z_TYPE_P(value) == IS_FALSE) {
            alpm_option_set_checkspace(intern->handle, Z_TYPE_P(value) == IS_TRUE ? 1 : 0);
        } else {
            php_error(E_NOTICE, "checkspace must be a bool");
        }
    } else if (strcmp(Z_STRVAL_P(member), "dbpath") == 0) {
        php_error(E_NOTICE, "Cannot set dbpath");
    } else if (strcmp(Z_STRVAL_P(member), "deltaratio") == 0) {
        if (Z_TYPE_P(value) == IS_DOUBLE) {
            alpm_option_set_deltaratio(intern->handle, Z_DVAL_P(value));
        } else {
            php_error(E_NOTICE, "deltaratio must be a float");
        }
    } else if (strcmp(Z_STRVAL_P(member), "gpgdir") == 0) {
        if (Z_TYPE_P(value) == IS_STRING) {
            alpm_option_set_gpgdir(intern->handle, Z_STRVAL_P(value));
        } else {
            php_error(E_NOTICE, "gpgdir must be a string");
        }
    } else if (strcmp(Z_STRVAL_P(member), "lockfile") == 0) {
        php_error(E_NOTICE, "Cannot set lockfile");
    } else if (strcmp(Z_STRVAL_P(member), "logfile") == 0) {
        if (Z_TYPE_P(value) == IS_STRING) {
            alpm_option_set_logfile(intern->handle, Z_STRVAL_P(value));
        } else {
            php_error(E_NOTICE, "logfile must be a string");
        }
    } else if (strcmp(Z_STRVAL_P(member), "root") == 0) {
        php_error(E_NOTICE, "Cannot set root");
    } else if (strcmp(Z_STRVAL_P(member), "usesyslog") == 0) {
        if (Z_TYPE_P(value) == IS_TRUE || Z_TYPE_P(value) == IS_FALSE) {
            alpm_option_set_usesyslog(intern->handle, Z_TYPE_P(value) == IS_TRUE ? 1 : 0);
        } else {
            php_error(E_NOTICE, "checkspace must be a bool");
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
    zend_object_handlers *std_hnd;

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
    zend_object_handlers *std_hnd;

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
    } else if (strcmp(Z_STRVAL_P(member), "base64_sig") == 0) {
        php_error(E_NOTICE, "cannot set base64_sig");
    } else if (strcmp(Z_STRVAL_P(member), "builddate") == 0) {
        php_error(E_NOTICE, "cannot set builddate");
    } else if (strcmp(Z_STRVAL_P(member), "conflicts") == 0) {
        php_error(E_NOTICE, "cannot set conflicts");
    } else if (strcmp(Z_STRVAL_P(member), "db") == 0) {
        php_error(E_NOTICE, "cannot set db");
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
        val = zend_string_init(stmp, strlen(stmp), 1); \
        ZVAL_STR(&zv, val); \
    } else { \
        ZVAL_NULL(&zv); \
    } \
    key = zend_string_init(keyname, strlen(keyname), 1); \
    zend_hash_add(props, key, &zv); \
} while (0)

static int hashtable_key_sort(const void *a, const void *b) {
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
            return zendi_smart_strcmp(f->key, s->key);
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
    zval zv;
    const char *stmp;
    int itmp;
    double dtmp;

    props = zend_std_get_properties(object);
    intern = Z_HANDLEO_P(object);

    ADD_STRING_TO_HASH(alpm_option_get_arch, handle, "arch");

    itmp = alpm_option_get_checkspace(intern->handle);
    ZVAL_BOOL(&zv, itmp);
    key = zend_string_init("checkspace", strlen("checkspace"), 1);
    zend_hash_add(props, key, &zv);

    ADD_STRING_TO_HASH(alpm_option_get_dbpath, handle, "dbpath");

    dtmp = alpm_option_get_deltaratio(intern->handle);
    ZVAL_DOUBLE(&zv, dtmp);
    key = zend_string_init("deltaratio", strlen("deltaratio"), 1);
    zend_hash_add(props, key, &zv);

    ADD_STRING_TO_HASH(alpm_option_get_gpgdir, handle, "gpgdir");
    ADD_STRING_TO_HASH(alpm_option_get_lockfile, handle, "lockfile");
    ADD_STRING_TO_HASH(alpm_option_get_logfile, handle, "logfile");
    ADD_STRING_TO_HASH(alpm_option_get_root, handle, "root");

    itmp = alpm_option_get_usesyslog(intern->handle);
    ZVAL_BOOL(&zv, itmp);
    key = zend_string_init("usesyslog", strlen("usesyslog"), 1);
    zend_hash_add(props, key, &zv);

    zend_hash_sort(props, hashtable_key_sort, 0);

    return props;
}

static HashTable *php_alpm_db_get_properties(zval *object) {
    php_alpm_db_object *intern;
    HashTable *props;
    zend_string *key, *val;
    zval zv;
    const char *stmp;
    alpm_list_t *ltmp;

    props = zend_std_get_properties(object);
    intern = Z_DBO_P(object);

    ltmp = alpm_db_get_groupcache(intern->db);
    if (ltmp != NULL) {
        alpm_group_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("grpcache", strlen("grpcache"), 1);
    zend_hash_add(props, key, &zv);

    ADD_STRING_TO_HASH(alpm_db_get_name, db, "name");

    ltmp = alpm_db_get_pkgcache(intern->db);
    if (ltmp != NULL) {
        alpm_pkg_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("pkgcache", strlen("pkgcache"), 1);
    zend_hash_add(props, key, &zv);

    ltmp = alpm_db_get_servers(intern->db);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("servers", strlen("servers"), 1);
    zend_hash_add(props, key, &zv);

    zend_hash_sort(props, hashtable_key_sort, 0);

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
    double dtmp;
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
    key = zend_string_init("backup", strlen("backup"), 1);
    zend_hash_add(props, key, &zv);

    ADD_STRING_TO_HASH(alpm_pkg_get_base64_sig, pkg, "base64_sig");

    ltmp = alpm_pkg_get_conflicts(intern->pkg);
    if (ltmp != NULL) {
        alpm_depend_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("conflicts", strlen("conflicts"), 1);
    zend_hash_add(props, key, &zv);

    dbtmp = alpm_pkg_get_db(intern->pkg);
    if (dbtmp != NULL) {
        object_init_ex(&zv, php_alpm_db_sc_entry);
        php_alpm_db_object *db = Z_DBO_P(&zv);
        db->db = dbtmp;
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("db", strlen("db"), 1);
    zend_hash_add(props, key, &zv);

    ltmp = alpm_pkg_get_depends(intern->pkg);
    if (ltmp != NULL) {
        alpm_depend_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("depends", strlen("depends"), 1);
    zend_hash_add(props, key, &zv);

    ADD_STRING_TO_HASH(alpm_pkg_get_desc, pkg, "desc");

    lotmp = (long)alpm_pkg_download_size(intern->pkg);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("download_size", strlen("download_size"), 1);
    zend_hash_add(props, key, &zv);

    ADD_STRING_TO_HASH(alpm_pkg_get_filename, pkg, "filename");

    ftmp = alpm_pkg_get_files(intern->pkg);
    if (ftmp != NULL) {
        alpm_filelist_to_zval(ftmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("files", strlen("files"), 1);
    zend_hash_add(props, key, &zv);

    ltmp = alpm_pkg_get_groups(intern->pkg);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("groups", strlen("groups"), 1);
    zend_hash_add(props, key, &zv);

    itmp = alpm_pkg_has_scriptlet(intern->pkg);
    ZVAL_BOOL(&zv, itmp);
    key = zend_string_init("has_scriptlet", strlen("has_scriptlet"), 1);
    zend_hash_add(props, key, &zv);

    lotmp = alpm_pkg_get_installdate(intern->pkg);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("installdate", strlen("installdate"), 1);
    zend_hash_add(props, key, &zv);

    lotmp = alpm_pkg_get_isize(intern->pkg);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("isize", strlen("isize"), 1);
    zend_hash_add(props, key, &zv);

    ltmp = alpm_pkg_get_licenses(intern->pkg);
    if (ltmp != NULL) {
        alpm_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("licenses", strlen("licenses"), 1);
    zend_hash_add(props, key, &zv);

    ADD_STRING_TO_HASH(alpm_pkg_get_md5sum, pkg, "md5sum");
    ADD_STRING_TO_HASH(alpm_pkg_get_name, pkg, "name");

    ltmp = alpm_pkg_get_optdepends(intern->pkg);
    if (ltmp != NULL) {
        alpm_depend_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("optdepends", strlen("optdepends"), 1);
    zend_hash_add(props, key, &zv);

    ADD_STRING_TO_HASH(alpm_pkg_get_packager, pkg, "packager");

    ltmp = alpm_pkg_get_provides(intern->pkg);
    if (ltmp != NULL) {
        alpm_depend_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("provides", strlen("provides"), 1);
    zend_hash_add(props, key, &zv);

    itmp = alpm_pkg_get_reason(intern->pkg);
    ZVAL_LONG(&zv, itmp);
    key = zend_string_init("reason", strlen("reason"), 1);
    zend_hash_add(props, key, &zv);

    ltmp = alpm_pkg_get_replaces(intern->pkg);
    if (ltmp != NULL) {
        alpm_depend_list_to_zval(ltmp, &zv);
    } else {
        ZVAL_NULL(&zv);
    }
    key = zend_string_init("replaces", strlen("replaces"), 1);
    zend_hash_add(props, key, &zv);

    ADD_STRING_TO_HASH(alpm_pkg_get_sha256sum, pkg, "sha256sum");

    lotmp = alpm_pkg_get_size(intern->pkg);
    ZVAL_LONG(&zv, lotmp);
    key = zend_string_init("size", strlen("size"), 1);
    zend_hash_add(props, key, &zv);

    ADD_STRING_TO_HASH(alpm_pkg_get_url, pkg, "url");
    ADD_STRING_TO_HASH(alpm_pkg_get_version, pkg, "version");

    zend_hash_sort(props, hashtable_key_sort, 0);

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
    alpm_handle_object_handlers.offset = XtOffsetOf(php_alpm_handle_object, zo);
    alpm_handle_object_handlers.free_obj = php_alpm_handle_free_storage;
    alpm_handle_object_handlers.get_properties = php_alpm_handle_get_properties;
    alpm_handle_object_handlers.read_property = php_alpm_handle_read_property;
    alpm_handle_object_handlers.write_property = php_alpm_handle_write_property;
    php_alpm_handle_sc_entry = zend_register_internal_class(&ce);

    INIT_CLASS_ENTRY(ce, PHP_ALPM_DB_SC_NAME, db_methods);
    ce.create_object = php_alpm_db_object_new;
    alpm_db_object_handlers.offset = XtOffsetOf(php_alpm_db_object, zo);
    alpm_db_object_handlers.free_obj = php_alpm_db_free_storage;
    alpm_db_object_handlers.get_properties = php_alpm_db_get_properties;
    alpm_db_object_handlers.read_property = php_alpm_db_read_property;
    alpm_db_object_handlers.write_property = php_alpm_db_write_property;
    php_alpm_db_sc_entry = zend_register_internal_class(&ce);

    INIT_CLASS_ENTRY(ce, PHP_ALPM_PKG_SC_NAME, pkg_methods);
    ce.create_object = php_alpm_pkg_object_new;
    alpm_pkg_object_handlers.offset = XtOffsetOf(php_alpm_pkg_object, zo);
    alpm_pkg_object_handlers.free_obj = php_alpm_pkg_free_storage;
    alpm_pkg_object_handlers.get_properties = php_alpm_pkg_get_properties;
    alpm_pkg_object_handlers.read_property = php_alpm_pkg_read_property;
    alpm_pkg_object_handlers.write_property = php_alpm_pkg_write_property;
    php_alpm_pkg_sc_entry = zend_register_internal_class(&ce);

    INIT_CLASS_ENTRY(ce, PHP_ALPM_TRANSACTION_SC_NAME, trans_methods);
    ce.create_object = php_alpm_transaction_object_new;
    alpm_transaction_object_handlers.offset = XtOffsetOf(php_alpm_transaction_object, zo);
    alpm_transaction_object_handlers.free_obj = php_alpm_transaction_free_storage;
    php_alpm_transaction_sc_entry = zend_register_internal_class(&ce);

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

    return SUCCESS;
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
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_ALPM_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ALPM
ZEND_GET_MODULE(alpm)
#endif