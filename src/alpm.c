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
    php_alpm_handle_sc_entry = zend_register_internal_class(&ce);

    INIT_CLASS_ENTRY(ce, PHP_ALPM_DB_SC_NAME, db_methods);
    ce.create_object = php_alpm_db_object_new;
    alpm_db_object_handlers.offset = XtOffsetOf(php_alpm_db_object, zo);
    alpm_db_object_handlers.free_obj = php_alpm_db_free_storage;
    php_alpm_db_sc_entry = zend_register_internal_class(&ce);

    INIT_CLASS_ENTRY(ce, PHP_ALPM_PKG_SC_NAME, pkg_methods);
    ce.create_object = php_alpm_pkg_object_new;
    alpm_pkg_object_handlers.offset = XtOffsetOf(php_alpm_pkg_object, zo);
    alpm_pkg_object_handlers.free_obj = php_alpm_pkg_free_storage;
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