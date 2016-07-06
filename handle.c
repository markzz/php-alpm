#include "handle.h"
#include "db.h"
#include "pkg.h"
#include "transaction.h"
#include "util.h"

static zend_object_handlers handle_object_handlers;

ZEND_BEGIN_ARG_INFO_EX(handle_construct_args, 0, 0, 2)
    ZEND_ARG_INFO(0, root)
    ZEND_ARG_INFO(0, dbpath)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_one_param_cachedir, 0, 0, 1)
    ZEND_ARG_INFO(0, cachedir)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_one_param_group, 0, 0, 1)
    ZEND_ARG_INFO(0, group)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_one_param_package, 0, 0, 1)
    ZEND_ARG_INFO(0, package)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(handle_zero_args, 0, 0, 0)
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

ZEND_BEGIN_ARG_INFO_EX(handle_set_pkgreason_args, 0, 0, 2)
    ZEND_ARG_OBJ_INFO(0, package, Pkg, 0)
    ZEND_ARG_INFO(0, reason)
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

static zend_function_entry handle_methods[] = {
    PHP_ME(Handle, __construct,      handle_construct_args,       ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)

    PHP_ME(Handle, add_cachedir,     handle_one_param_cachedir,   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_ignoregrp,    handle_one_param_group,      ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_ignorepkg,    handle_one_param_package,    ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_noextract,    handle_one_param_package,    ZEND_ACC_PUBLIC)
    PHP_ME(Handle, add_noupgrade,    handle_one_param_package,    ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_arch,         handle_zero_args,            ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_dbpath,       handle_zero_args,            ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_cachedirs,    handle_zero_args,            ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_checkspace,   handle_zero_args,            ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_ignoregrps,   handle_zero_args,            ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_localdb,      handle_zero_args,            ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_noextracts,   handle_zero_args,            ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_noupgrades,   handle_zero_args,            ZEND_ACC_PUBLIC)
    PHP_ME(Handle, get_syncdbs,      handle_zero_args,            ZEND_ACC_PUBLIC)
    PHP_ME(Handle, init_transaction, handle_init_trans_args,      ZEND_ACC_PUBLIC)
    PHP_ME(Handle, load_pkg,         handle_load_pkg_args,        ZEND_ACC_PUBLIC)
    PHP_ME(Handle, register_syncdb,  handle_register_syncdb_args, ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_cachedir,  handle_one_param_cachedir,   ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_ignoregrp, handle_one_param_group,      ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_ignorepkg, handle_one_param_package,    ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_noextract, handle_one_param_package,    ZEND_ACC_PUBLIC)
    PHP_ME(Handle, remove_noupgrade, handle_one_param_package,    ZEND_ACC_PUBLIC)
    PHP_ME(Handle, set_arch,         handle_set_arch_args,        ZEND_ACC_PUBLIC)
    PHP_ME(Handle, set_checkspace,   handle_set_checkspace_args,  ZEND_ACC_PUBLIC)
    PHP_ME(Handle, set_pkgreason,    handle_set_pkgreason_args,   ZEND_ACC_PUBLIC)

    {NULL, NULL, NULL}
};

static void handle_free_storage(zend_object *obj TSRMLS_DC) {
    handle_object *intern = alpm_handle_from_obj(obj);
    if (!intern) {
        return;
    }

    alpm_release(intern->handle);
    efree(intern);
}

zend_object *create_handle_struct(zend_class_entry *class TSRMLS_DC) {
    handle_object *intern = ecalloc(1, sizeof(handle_object) + zend_object_properties_size(class));

    zend_object_std_init(&intern->std, class TSRMLS_CC);
    object_properties_init(&intern->std, class);
    handle_object_handlers.offset = XtOffsetOf(handle_object, std);
    handle_object_handlers.free_obj = handle_free_storage;

    intern->std.handlers = &handle_object_handlers;

    return &intern->std;
}

void alpm_init_handle(TSRMLS_D) {
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "Handle", handle_methods);
    alpm_ce_handle = zend_register_internal_class(&ce TSRMLS_CC);

    ce.create_object = create_handle_struct;

//    zend_declare_property_string(alpm_ce_handle, "dbpath", sizeof("dbpath") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
//    zend_declare_property_double(alpm_ce_handle, "deltaratio", sizeof("deltaratio") - 1, 0.0, ZEND_ACC_PUBLIC TSRMLS_CC);
////    zend_declare_property_string(alpm_ce_handle, "dlcb", sizeof("dlcb") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
////    zend_declare_property_string(alpm_ce_handle, "eventcb", sizeof("eventcb") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
////    zend_declare_property_string(alpm_ce_handle, "fetchcb", sizeof("fetchcb") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
//    zend_declare_property_string(alpm_ce_handle, "gpgdir", sizeof("gpgdir") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
////    zend_declare_property_string(alpm_ce_handle, "logcb", sizeof("logcb") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
//    zend_declare_property_string(alpm_ce_handle, "logfile", sizeof("logfile") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
////    zend_declare_property_string(alpm_ce_handle, "progresscb", sizeof("progresscb") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
////    zend_declare_property_string(alpm_ce_handle, "questioncb", sizeof("questioncb") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
//    zend_declare_property_string(alpm_ce_handle, "root", sizeof("root") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
////    zend_declare_property_string(alpm_ce_handle, "totaldlcb", sizeof("totaldlcb") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
//    zend_declare_property_long(alpm_ce_handle, "usesyslog", sizeof("usesyslog") - 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
}

PHP_METHOD(Handle, __construct) {
    char *rootpath;
    char *dbpath;
    size_t rp, dp;

    if (ZEND_NUM_ARGS() == 0) {
        rootpath = emalloc(sizeof(char) * strlen(DEFAULT_ROOTDIR));
        dbpath = emalloc(sizeof(char) * strlen(DEFAULT_DBPATH));

        strcpy(rootpath, DEFAULT_ROOTDIR);
        strcpy(dbpath, DEFAULT_DBPATH);

        rp = strlen(rootpath);
        dp = strlen(dbpath);

        goto create;
    }
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &rootpath, &rp, &dbpath, &dp) == FAILURE) {
        RETURN_NULL()
    }

    create:
    object_init_ex(return_value, alpm_ce_handle);

    handle_object *intern = Z_HANDLEO_P(getThis());

    alpm_handle_t *h = alpm_initialize(rootpath, dbpath, &intern->err);
    intern->handle = h;

    if (ZEND_NUM_ARGS() == 0) {
        efree(rootpath);
        efree(dbpath);
    }
}

PHP_METHOD(Handle, add_cachedir) {
    ADD_METHOD_START()
    alpm_option_add_cachedir(intern->handle, arg);
    RETURN_NULL()
}

PHP_METHOD(Handle, add_ignoregrp) {
    ADD_METHOD_START()
    alpm_option_add_ignoregroup(intern->handle, arg);
    RETURN_NULL()
}

PHP_METHOD(Handle, add_ignorepkg) {
    ADD_METHOD_START()
    alpm_option_add_ignorepkg(intern->handle, arg);
    RETURN_NULL()
}

PHP_METHOD(Handle, add_noextract) {
    ADD_METHOD_START()
    alpm_option_add_noextract(intern->handle, arg);
    RETURN_NULL()
}

PHP_METHOD(Handle, add_noupgrade) {
    ADD_METHOD_START()
    alpm_option_add_noupgrade(intern->handle, arg);
    RETURN_NULL()
}

PHP_METHOD(Handle, get_arch) {
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
        RETURN_NULL()
    }
    handle_object *intern = Z_HANDLEO_P(getThis());
    RETURN_STRING(alpm_option_get_arch(intern->handle));
}

PHP_METHOD(Handle, get_cachedirs) {
    GET_ARRAY_METHOD(alpm_option_get_cachedirs, handle)
}

PHP_METHOD(Handle, get_checkspace) {
    INT_GETTER_METHOD(alpm_option_get_checkspace, handle)
}

PHP_METHOD(Handle, get_dbpath) {
    const char *r;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
        RETURN_NULL()
    }
    handle_object *intern = Z_HANDLEO_P(getThis());
    r = alpm_option_get_dbpath(intern->handle);

    RETURN_STRING(r)
}

PHP_METHOD(Handle, get_ignoregrps) {
    GET_ARRAY_METHOD(alpm_option_get_ignoregroups, handle)
}

PHP_METHOD(Handle, get_ignorepkgs) {
    GET_ARRAY_METHOD(alpm_option_get_ignorepkgs, handle)
}

PHP_METHOD(Handle, get_localdb) {
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
        RETURN_NULL()
    }

    handle_object *intern = Z_HANDLEO_P(getThis());
    db_object *db;
    object_init_ex(return_value, alpm_ce_db);
    db = Z_DBO_P(return_value);
    db->db = alpm_get_localdb(intern->handle);
}

PHP_METHOD(Handle, get_noextracts) {
    GET_ARRAY_METHOD(alpm_option_get_noextracts, handle)
}

PHP_METHOD(Handle, get_noupgrades) {
    GET_ARRAY_METHOD(alpm_option_get_noupgrades, handle)
}

PHP_METHOD(Handle, get_syncdbs) {
    GET_ARRAY_METHOD(alpm_get_syncdbs, handle)
}

#define FLAGS(a) a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[8], a[9], \
    a[10], a[11], a[13], a[14], a[15], a[16], a[17]

PHP_METHOD(Handle, init_transaction) {
    handle_object *intern = Z_HANDLEO_P(getThis());
    zend_bool flags[18] = {0};
    alpm_transflag_t flag_int = 0;
    int i, ret;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|bbbbbbbbbbbbbbbb", FLAGS(flags)) == FAILURE) {
        RETURN_NULL()
    }

    for (i = 0; i < 18; i++) {
        if (flags[i]) {
            flag_int |= 1U << i;
        }
    }
    ret = alpm_trans_init(intern->handle, flag_int);

    if (ret == -1) {
        /* TODO: CREATE ERROR HANDLING */
        RETURN_NULL()
    }

    trans_object *to;
    object_init_ex(return_value, alpm_ce_transaction);
    to = Z_TRANSO_P(return_value);
    to->handle = intern->handle;
}

PHP_METHOD(Handle, load_pkg) {
    alpm_pkg_t *pkg;
    char *filename;
    long check_sig = ALPM_SIG_PACKAGE_OPTIONAL;
    size_t fn_size;
    handle_object *intern = Z_HANDLEO_P(getThis());

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &filename, &fn_size, &check_sig) == FAILURE) {
        RETURN_NULL()
    }

    alpm_pkg_load(intern->handle, filename, 1, check_sig, &pkg);

    pkg_object *po;
    object_init_ex(return_value, alpm_ce_pkg);
    po = Z_PKGO_P(return_value);
    po->pkg = pkg;
}

PHP_METHOD(Handle, register_syncdb) {
    char *dbname;
    long pgp_level;
    size_t dbname_size;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &dbname, &dbname_size, &pgp_level) == FAILURE) {
        RETURN_NULL()
    }

    handle_object *intern = Z_HANDLEO_P(getThis());
    db_object *db;
    object_init_ex(return_value, alpm_ce_db);
    db = Z_DBO_P(return_value);
    db->db = alpm_register_syncdb(intern->handle, dbname, pgp_level);
}

PHP_METHOD(Handle, remove_cachedir) {
    char *cd;
    size_t cd_size;
    handle_object *intern = Z_HANDLEO_P(getThis());

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &cd, &cd_size) == FAILURE) {
        RETURN_NULL()
    }

    alpm_option_remove_cachedir(intern->handle, cd);
    RETURN_NULL()
}

PHP_METHOD(Handle, remove_ignoregrp) {
    char *ig;
    size_t ig_size;
    handle_object *intern = Z_HANDLEO_P(getThis());

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ig, &ig_size) == FAILURE) {
        RETURN_NULL()
    }

    alpm_option_remove_ignoregroup(intern->handle, ig);
    RETURN_NULL()
}

PHP_METHOD(Handle, remove_ignorepkg) {
    char *ip;
    size_t ip_size;
    handle_object *intern = Z_HANDLEO_P(getThis());

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ip, &ip_size) == FAILURE) {
        RETURN_NULL()
    }

    alpm_option_remove_ignorepkg(intern->handle, ip);
    RETURN_NULL()
}

PHP_METHOD(Handle, remove_noextract) {
    char *ne;
    size_t ne_size;
    handle_object *intern = Z_HANDLEO_P(getThis());

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &ne, &ne_size) == FAILURE) {
        RETURN_NULL()
    }

    alpm_option_remove_noextract(intern->handle, ne);
    RETURN_NULL()
}

PHP_METHOD(Handle, remove_noupgrade) {
    char *nu;
    size_t nu_size;
    handle_object *intern = Z_HANDLEO_P(getThis());

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &nu, &nu_size) == FAILURE) {
        RETURN_NULL()
    }

    alpm_option_remove_noupgrade(intern->handle, nu);
    RETURN_NULL()
}

PHP_METHOD(Handle, set_arch) {
    SETTER_METHOD(alpm_option_set_arch, handle)
}

PHP_METHOD(Handle, set_checkspace) {
    INT_SETTER_METHOD(alpm_option_set_checkspace, handle)
}

PHP_METHOD(Handle, set_pkgreason) {
    pkg_object *pkg;
    zval *pzval;
    long reason;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ol", &pzval, &reason) == FAILURE) {
        RETURN_NULL()
    }

    pkg = Z_PKGO_P(pzval);

    if (reason == 1) {
        alpm_pkg_set_reason(pkg->pkg, ALPM_PKG_REASON_DEPEND);
        RETURN_TRUE
    } else if (reason == 0) {
        alpm_pkg_set_reason(pkg->pkg, ALPM_PKG_REASON_EXPLICIT);
        RETURN_TRUE
    } else {
        RETURN_FALSE
    }
}