/*
 *  php_alpm_defs.h
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

/* New struct class names */
#define PHP_ALPM_DEPEND_SC_NAME "AlpmDepend"
#define PHP_ALPM_FILE_SC_NAME "AlpmFile"
#define PHP_ALPM_BACKUP_SC_NAME "AlpmBackup"
#define PHP_ALPM_GROUP_SC_NAME "AlpmGroup"
#define PHP_ALPM_CONFLICT_SC_NAME "AlpmConflict"
#define PHP_ALPM_DEPMISSING_SC_NAME "AlpmDepMissing"
#define PHP_ALPM_FILECONFLICT_SC_NAME "AlpmFileConflict"
#define PHP_ALPM_SIGRESULT_SC_NAME "AlpmSigResult"
#define PHP_ALPM_PGPKEY_SC_NAME "AlpmPgpKey"

#define DEFAULT_ROOTDIR "/"
#define DEFAULT_DBPATH "/var/lib/pacman"

typedef enum _alpm_callback_id {
    CB_LOG,
    CB_DOWNLOAD,
    CB_FETCH,
    /* CB_TOTALDL removed - alpm_cb_totaldl was removed in libalpm 6.0 */
    CB_EVENT,
    CB_QUESTION,
    CB_PROGRESS,
    N_CALLBACKS
} alpm_callback_id;

typedef struct _php_alpm_handle_object {
    alpm_handle_t *handle;
    zend_object zo;
} php_alpm_handle_object;

typedef struct _php_alpm_db_object {
    alpm_db_t *db;
    alpm_handle_t *handle;
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

/* New struct wrapper objects */
typedef struct _php_alpm_depend_object {
    alpm_depend_t *depend;
    zend_bool owned;  /* true if we should free the depend on destruction */
    zend_object zo;
} php_alpm_depend_object;

typedef struct _php_alpm_file_object {
    alpm_file_t *file;
    zend_object zo;
} php_alpm_file_object;

typedef struct _php_alpm_backup_object {
    alpm_backup_t *backup;
    zend_object zo;
} php_alpm_backup_object;

typedef struct _php_alpm_group_object {
    alpm_group_t *group;
    zend_object zo;
} php_alpm_group_object;

typedef struct _php_alpm_conflict_object {
    alpm_conflict_t *conflict;
    zend_object zo;
} php_alpm_conflict_object;

typedef struct _php_alpm_depmissing_object {
    alpm_depmissing_t *depmissing;
    zend_object zo;
} php_alpm_depmissing_object;

typedef struct _php_alpm_fileconflict_object {
    alpm_fileconflict_t *fileconflict;
    zend_object zo;
} php_alpm_fileconflict_object;

typedef struct _php_alpm_sigresult_object {
    alpm_sigresult_t *sigresult;
    zend_object zo;
} php_alpm_sigresult_object;

typedef struct _php_alpm_pgpkey_object {
    alpm_pgpkey_t *pgpkey;
    zend_object zo;
} php_alpm_pgpkey_object;

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

static inline php_alpm_depend_object *php_alpm_depend_fetch_object(zend_object *obj) {
    return (php_alpm_depend_object*)((char*)(obj) - XtOffsetOf(php_alpm_depend_object, zo));
}

static inline php_alpm_file_object *php_alpm_file_fetch_object(zend_object *obj) {
    return (php_alpm_file_object*)((char*)(obj) - XtOffsetOf(php_alpm_file_object, zo));
}

static inline php_alpm_backup_object *php_alpm_backup_fetch_object(zend_object *obj) {
    return (php_alpm_backup_object*)((char*)(obj) - XtOffsetOf(php_alpm_backup_object, zo));
}

static inline php_alpm_group_object *php_alpm_group_fetch_object(zend_object *obj) {
    return (php_alpm_group_object*)((char*)(obj) - XtOffsetOf(php_alpm_group_object, zo));
}

static inline php_alpm_conflict_object *php_alpm_conflict_fetch_object(zend_object *obj) {
    return (php_alpm_conflict_object*)((char*)(obj) - XtOffsetOf(php_alpm_conflict_object, zo));
}

static inline php_alpm_depmissing_object *php_alpm_depmissing_fetch_object(zend_object *obj) {
    return (php_alpm_depmissing_object*)((char*)(obj) - XtOffsetOf(php_alpm_depmissing_object, zo));
}

static inline php_alpm_fileconflict_object *php_alpm_fileconflict_fetch_object(zend_object *obj) {
    return (php_alpm_fileconflict_object*)((char*)(obj) - XtOffsetOf(php_alpm_fileconflict_object, zo));
}

static inline php_alpm_sigresult_object *php_alpm_sigresult_fetch_object(zend_object *obj) {
    return (php_alpm_sigresult_object*)((char*)(obj) - XtOffsetOf(php_alpm_sigresult_object, zo));
}

static inline php_alpm_pgpkey_object *php_alpm_pgpkey_fetch_object(zend_object *obj) {
    return (php_alpm_pgpkey_object*)((char*)(obj) - XtOffsetOf(php_alpm_pgpkey_object, zo));
}

#define Z_HANDLEO_P(zv) php_alpm_handle_fetch_object(Z_OBJ_P(zv))
#define Z_DBO_P(zv) php_alpm_db_fetch_object(Z_OBJ_P(zv))
#define Z_PKGO_P(zv) php_alpm_pkg_fetch_object(Z_OBJ_P(zv))
#define Z_TRANSO_P(zv) php_alpm_transaction_fetch_object(Z_OBJ_P(zv))
#define Z_DEPO_P(zv) php_alpm_depend_fetch_object(Z_OBJ_P(zv))
#define Z_FILEO_P(zv) php_alpm_file_fetch_object(Z_OBJ_P(zv))
#define Z_BACKUPO_P(zv) php_alpm_backup_fetch_object(Z_OBJ_P(zv))
#define Z_GROUPO_P(zv) php_alpm_group_fetch_object(Z_OBJ_P(zv))
#define Z_CONFLICTO_P(zv) php_alpm_conflict_fetch_object(Z_OBJ_P(zv))
#define Z_DEPMISSINGO_P(zv) php_alpm_depmissing_fetch_object(Z_OBJ_P(zv))
#define Z_FILECONFLICTO_P(zv) php_alpm_fileconflict_fetch_object(Z_OBJ_P(zv))
#define Z_SIGRESULTO_P(zv) php_alpm_sigresult_fetch_object(Z_OBJ_P(zv))
#define Z_PGPKEYO_P(zv) php_alpm_pgpkey_fetch_object(Z_OBJ_P(zv))

extern zend_class_entry *php_alpm_handle_sc_entry;
extern zend_class_entry *php_alpm_handle_exception_class_entry;
extern zend_class_entry *php_alpm_db_sc_entry;
extern zend_class_entry *php_alpm_db_exception_class_entry;
extern zend_class_entry *php_alpm_pkg_sc_entry;
extern zend_class_entry *php_alpm_pkg_exception_class_entry;
extern zend_class_entry *php_alpm_transaction_sc_entry;
extern zend_class_entry *php_alpm_transaction_exception_class_entry;

/* New struct class entries */
extern zend_class_entry *php_alpm_depend_sc_entry;
extern zend_class_entry *php_alpm_file_sc_entry;
extern zend_class_entry *php_alpm_backup_sc_entry;
extern zend_class_entry *php_alpm_group_sc_entry;
extern zend_class_entry *php_alpm_conflict_sc_entry;
extern zend_class_entry *php_alpm_depmissing_sc_entry;
extern zend_class_entry *php_alpm_fileconflict_sc_entry;
extern zend_class_entry *php_alpm_sigresult_sc_entry;
extern zend_class_entry *php_alpm_pgpkey_sc_entry;

/* handle methods */
PHP_METHOD(Handle, __construct);
PHP_METHOD(Handle, __toString);
PHP_METHOD(Handle, add_architecture);
PHP_METHOD(Handle, add_assumeinstalled);
PHP_METHOD(Handle, add_cachedir);
PHP_METHOD(Handle, add_hookdir);
PHP_METHOD(Handle, add_ignoregrp);
PHP_METHOD(Handle, add_ignorepkg);
PHP_METHOD(Handle, add_noextract);
PHP_METHOD(Handle, add_noupgrade);
PHP_METHOD(Handle, get_architectures);
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
PHP_METHOD(Handle, remove_architecture);
PHP_METHOD(Handle, remove_assumeinstalled);
PHP_METHOD(Handle, remove_cachedir);
PHP_METHOD(Handle, remove_hookdir);
PHP_METHOD(Handle, remove_ignoregrp);
PHP_METHOD(Handle, remove_ignorepkg);
PHP_METHOD(Handle, remove_noextract);
PHP_METHOD(Handle, remove_noupgrade);
PHP_METHOD(Handle, set_arch);
PHP_METHOD(Handle, set_checkspace);

/* db methods */
PHP_METHOD(Db, __toString);
PHP_METHOD(Db, add_server);
PHP_METHOD(Db, check_pgp_signature);
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
/* PHP_METHOD(Pkg, get_md5sum); - REMOVED: alpm_pkg_get_md5sum() removed in libalpm 5.2 */
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
PHP_METHOD(Pkg, get_xdata);
PHP_METHOD(Pkg, set_reason);
PHP_METHOD(Pkg, check_pgp_signature);

/* transaction methods */
PHP_METHOD(Trans, add_pkg);
PHP_METHOD(Trans, commit);
PHP_METHOD(Trans, get_add);
PHP_METHOD(Trans, get_flags);
PHP_METHOD(Trans, get_remove);
PHP_METHOD(Trans, interrupt);
PHP_METHOD(Trans, prepare);
PHP_METHOD(Trans, release);
PHP_METHOD(Trans, remove_pkg);
PHP_METHOD(Trans, system_upgrade);

/* depend methods */
PHP_METHOD(Depend, __toString);
PHP_METHOD(Depend, compute_string);

/* file methods */
PHP_METHOD(File, __toString);

/* backup methods */
PHP_METHOD(Backup, __toString);

/* group methods */
PHP_METHOD(Group, __toString);

/* conflict methods */
PHP_METHOD(Conflict, __toString);

/* depmissing methods */
PHP_METHOD(DepMissing, __toString);

/* fileconflict methods */
PHP_METHOD(FileConflict, __toString);

/* sigresult methods */
PHP_METHOD(SigResult, __toString);

/* pgpkey methods */
PHP_METHOD(PgpKey, __toString);

/* callback function wrappers - updated for libalpm 16 API */
void php_alpm_logcb(void *ctx, alpm_loglevel_t level, const char *fmt, va_list va_args);
void php_alpm_dlcb(void *ctx, const char *filename, alpm_download_event_type_t event, void *data);
int php_alpm_fetchcb(void *ctx, const char *url, const char *localpath, int force);
/* php_alpm_totaldlcb removed - alpm_cb_totaldl was removed in libalpm 6.0 */
void php_alpm_eventcb(void *ctx, alpm_event_t *event);
void php_alpm_questioncb(void *ctx, alpm_question_t *question);
void php_alpm_progresscb(void *ctx, alpm_progress_t op, const char *target_name, int percentage, size_t n_targets, size_t cur_target);

#endif /* PHP_ALPM_DEFS_H */
