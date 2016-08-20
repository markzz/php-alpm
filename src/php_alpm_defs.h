/*
 *  php_alpm_defs.h
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

#ifndef PHP_ALPM_DEFS_H
#define PHP_ALPM_DEFS_H

#include <alpm.h>

#include "php.h"

#define PHP_ALPM_HANDLE_SC_NAME "AlpmHandle"
#define PHP_ALPM_HANDLE_EXCEPTION_SC_NAME "AlpmHandleException"
#define PHP_ALPM_DB_SC_NAME "AlpmDb"
#define PHP_ALPM_DB_EXCEPTION_SC_NAME "AlpmDbException"
#define PHP_ALPM_PKG_SC_NAME "AlpmPkg"
#define PHP_ALPM_PKG_EXCEPTION_SC_NAME "AlpmPkgException"
#define PHP_ALPM_TRANSACTION_SC_NAME "AlpmTransaction"
#define PHP_ALPM_TRANSACTION_EXCEPTION_SC_NAME "AlpmTransactionException"

#define DEFAULT_ROOTDIR "/"
#define DEFAULT_DBPATH "/var/lib/pacman"

typedef struct _php_alpm_handle_object {
    alpm_handle_t *handle;
    zend_object zo;
} php_alpm_handle_object;

typedef struct _php_alpm_db_object {
    alpm_db_t *db;
    zend_object zo;
} php_alpm_db_object;

typedef struct _php_alpm_pkg_object {
    alpm_pkg_t *pkg;
    zend_object zo;
} php_alpm_pkg_object;

typedef struct _php_alpm_transaction_object {
    alpm_handle_t *handle;
    zend_object zo;
} php_alpm_transaction_object;

static inline php_alpm_handle_object *php_alpm_handle_fetch_object(zend_object *obj) {
    return (php_alpm_handle_object*)((char*)(obj) - XtOffsetOf(php_alpm_handle_object, zo));
}

static inline php_alpm_db_object *php_alpm_db_fetch_object(zend_object *obj) {
    return (php_alpm_db_object*)((char*)(obj) - XtOffsetOf(php_alpm_db_object, zo));
}

static inline php_alpm_pkg_object *php_alpm_pkg_fetch_object(zend_object *obj) {
    return (php_alpm_pkg_object*)((char*)(obj) - XtOffsetOf(php_alpm_pkg_object, zo));
}

static inline php_alpm_transaction_object *php_alpm_transaction_fetch_object(zend_object *obj) {
    return (php_alpm_transaction_object*)((char*)(obj) - XtOffsetOf(php_alpm_transaction_object, zo));
}

#define Z_HANDLEO_P(zv) php_alpm_handle_fetch_object(Z_OBJ_P(zv))
#define Z_DBO_P(zv) php_alpm_db_fetch_object(Z_OBJ_P(zv))
#define Z_PKGO_P(zv) php_alpm_pkg_fetch_object(Z_OBJ_P(zv))
#define Z_TRANSO_P(zv) php_alpm_transaction_fetch_object(Z_OBJ_P(zv))

extern zend_class_entry *php_alpm_handle_sc_entry;
extern zend_class_entry *php_alpm_handle_exception_class_entry;
extern zend_class_entry *php_alpm_db_sc_entry;
extern zend_class_entry *php_alpm_db_exception_class_entry;
extern zend_class_entry *php_alpm_pkg_sc_entry;
extern zend_class_entry *php_alpm_pkg_exception_class_entry;
extern zend_class_entry *php_alpm_transaction_sc_entry;
extern zend_class_entry *php_alpm_transaction_exception_class_entry;

/* handle methods */
PHP_METHOD(Handle, __construct);
PHP_METHOD(Handle, __toString);
PHP_METHOD(Handle, add_cachedir);
PHP_METHOD(Handle, add_ignoregrp);
PHP_METHOD(Handle, add_ignorepkg);
PHP_METHOD(Handle, add_noextract);
PHP_METHOD(Handle, add_noupgrade);
PHP_METHOD(Handle, get_arch);
PHP_METHOD(Handle, get_cachedirs);
PHP_METHOD(Handle, get_checkspace);
PHP_METHOD(Handle, get_dbpath);
PHP_METHOD(Handle, get_ignoregrps);
PHP_METHOD(Handle, get_ignorepkgs);
PHP_METHOD(Handle, get_localdb);
PHP_METHOD(Handle, get_noextracts);
PHP_METHOD(Handle, get_noupgrades);
PHP_METHOD(Handle, get_syncdbs);
PHP_METHOD(Handle, init_transaction);
PHP_METHOD(Handle, load_pkg);
PHP_METHOD(Handle, register_syncdb);
PHP_METHOD(Handle, remove_cachedir);
PHP_METHOD(Handle, remove_ignoregrp);
PHP_METHOD(Handle, remove_ignorepkg);
PHP_METHOD(Handle, remove_noextract);
PHP_METHOD(Handle, remove_noupgrade);
PHP_METHOD(Handle, set_arch);
PHP_METHOD(Handle, set_checkspace);

/* db methods */
PHP_METHOD(Db, __toString);
PHP_METHOD(Db, add_server);
PHP_METHOD(Db, get_grpcache);
PHP_METHOD(Db, get_name);
PHP_METHOD(Db, get_pkg);
PHP_METHOD(Db, get_pkgcache);
PHP_METHOD(Db, get_servers);
PHP_METHOD(Db, search);
PHP_METHOD(Db, read_grp);
PHP_METHOD(Db, remove_server);
PHP_METHOD(Db, update);

/* pkg methods */
PHP_METHOD(Pkg, __toString);
PHP_METHOD(Pkg, compute_requiredby);
PHP_METHOD(Pkg, get_arch);
PHP_METHOD(Pkg, get_backup);
PHP_METHOD(Pkg, get_base64_sig);
PHP_METHOD(Pkg, get_builddate);
PHP_METHOD(Pkg, get_conflicts);
PHP_METHOD(Pkg, get_db);
PHP_METHOD(Pkg, get_depends);
PHP_METHOD(Pkg, get_desc);
PHP_METHOD(Pkg, get_download_size);
PHP_METHOD(Pkg, get_filename);
PHP_METHOD(Pkg, get_files);
PHP_METHOD(Pkg, get_groups);
PHP_METHOD(Pkg, get_has_scriptlet);
PHP_METHOD(Pkg, get_installdate);
PHP_METHOD(Pkg, get_isize);
PHP_METHOD(Pkg, get_licenses);
PHP_METHOD(Pkg, get_md5sum);
PHP_METHOD(Pkg, get_name);
PHP_METHOD(Pkg, get_optdepends);
PHP_METHOD(Pkg, get_packager);
PHP_METHOD(Pkg, get_provides);
PHP_METHOD(Pkg, get_reason);
PHP_METHOD(Pkg, get_replaces);
PHP_METHOD(Pkg, get_sha256sum);
PHP_METHOD(Pkg, get_size);
PHP_METHOD(Pkg, get_url);
PHP_METHOD(Pkg, get_version);
PHP_METHOD(Pkg, set_reason);

/* transaction methods */
PHP_METHOD(Trans, add_pkg);
PHP_METHOD(Trans, commit);
PHP_METHOD(Trans, interrupt);
PHP_METHOD(Trans, prepare);
PHP_METHOD(Trans, release);
PHP_METHOD(Trans, remove_pkg);
PHP_METHOD(Trans, system_upgrade);

#endif /* PHP_ALPM_DEFS_H */
