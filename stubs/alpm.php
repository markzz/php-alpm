<?php
/**
 * PHP-ALPM Extension Stubs
 *
 * Stubs for IDE autocompletion and static analysis.
 *
 * @package php-alpm
 * @version 0.5.0
 */

/**
 * Compare two version strings
 *
 * @param string $ver1 First version string
 * @param string $ver2 Second version string
 * @return int -1 if ver1 < ver2, 0 if equal, 1 if ver1 > ver2
 */
function alpm_vercmp(string $ver1, string $ver2): int {}

/**
 * Get the libalpm version string
 *
 * @return string Version string (e.g., "16.0.1")
 */
function alpm_version(): string {}

/**
 * Get the php-alpm extension version string
 *
 * @return string Version string (e.g., "0.5.0")
 */
function php_alpm_version(): string {}

/**
 * Main ALPM handle for package management operations
 */
class AlpmHandle
{
    /** @var string[] List of architectures */
    public readonly array $architectures;

    /** @var AlpmDepend[] List of assumed-installed packages */
    public readonly array $assumeinstalled;

    /** @var string[] List of cache directories */
    public readonly array $cachedirs;

    /** @var bool Whether to check disk space */
    public readonly bool $checkspace;

    /** @var string Database file extension */
    public readonly string $dbext;

    /** @var string Database path */
    public readonly string $dbpath;

    /** @var int Default signature level */
    public readonly int $default_siglevel;

    /** @var callable|null Download callback */
    public $dlcb;

    /** @var callable|null Event callback */
    public $eventcb;

    /** @var callable|null Fetch callback */
    public $fetchcb;

    /** @var string GPG directory path */
    public readonly string $gpgdir;

    /** @var string[] List of hook directories */
    public readonly array $hookdirs;

    /** @var string[] List of ignored groups */
    public readonly array $ignoregrps;

    /** @var string[] List of ignored packages */
    public readonly array $ignorepkgs;

    /** @var int Local file signature level */
    public readonly int $local_file_siglevel;

    /** @var string Lock file path */
    public readonly string $lockfile;

    /** @var callable|null Log callback */
    public $logcb;

    /** @var string Log file path */
    public readonly string $logfile;

    /** @var string[] List of files to not extract */
    public readonly array $noextracts;

    /** @var string[] List of files to not upgrade */
    public readonly array $noupgrades;

    /** @var callable|null Progress callback */
    public $progresscb;

    /** @var callable|null Question callback */
    public $questioncb;

    /** @var int Remote file signature level */
    public readonly int $remote_file_siglevel;

    /** @var string Root path */
    public readonly string $root;

    /** @var bool Whether to use syslog */
    public readonly bool $usesyslog;

    /**
     * Create a new ALPM handle
     *
     * @param string $root Root path for package operations
     * @param string $dbpath Path to the package database
     * @throws AlpmHandleException If handle creation fails
     */
    public function __construct(string $root, string $dbpath) {}

    /**
     * Get string representation
     *
     * @return string Handle description
     */
    public function __toString(): string {}

    /**
     * Add an architecture
     *
     * @param string $architecture Architecture name (e.g., "x86_64")
     * @return bool Success
     */
    public function add_architecture(string $architecture): bool {}

    /**
     * Add an assumed-installed package
     *
     * @param string $assumeinstalled Package specification (e.g., "pkg>=1.0")
     * @return bool Success
     */
    public function add_assumeinstalled(string $assumeinstalled): bool {}

    /**
     * Add a cache directory
     *
     * @param string $cachedir Cache directory path
     * @return bool Success
     */
    public function add_cachedir(string $cachedir): bool {}

    /**
     * Add a hook directory
     *
     * @param string $hookdir Hook directory path
     * @return bool Success
     */
    public function add_hookdir(string $hookdir): bool {}

    /**
     * Add an ignored group
     *
     * @param string $group Group name
     * @return bool Success
     */
    public function add_ignoregrp(string $group): bool {}

    /**
     * Add an ignored package
     *
     * @param string $package Package name
     * @return bool Success
     */
    public function add_ignorepkg(string $package): bool {}

    /**
     * Add a file to not extract
     *
     * @param string $filename Filename pattern
     * @return bool Success
     */
    public function add_noextract(string $filename): bool {}

    /**
     * Add a file to not upgrade
     *
     * @param string $filename Filename pattern
     * @return bool Success
     */
    public function add_noupgrade(string $filename): bool {}

    /**
     * Get list of architectures
     *
     * @return string[]|null List of architectures
     * @deprecated Use $handle->architectures instead
     */
    public function get_architectures(): ?array {}

    /**
     * Get the database path
     *
     * @return string Database path
     * @deprecated Use $handle->dbpath instead
     */
    public function get_dbpath(): string {}

    /**
     * Get list of cache directories
     *
     * @return string[]|null List of cache directories
     * @deprecated Use $handle->cachedirs instead
     */
    public function get_cachedirs(): ?array {}

    /**
     * Get checkspace setting
     *
     * @return bool Whether disk space checking is enabled
     * @deprecated Use $handle->checkspace instead
     */
    public function get_checkspace(): bool {}

    /**
     * Get list of ignored groups
     *
     * @return string[]|null List of ignored groups
     * @deprecated Use $handle->ignoregrps instead
     */
    public function get_ignoregrps(): ?array {}

    /**
     * Get list of ignored packages
     *
     * @return string[]|null List of ignored packages
     * @deprecated Use $handle->ignorepkgs instead
     */
    public function get_ignorepkgs(): ?array {}

    /**
     * Get the local database
     *
     * @return AlpmDb|null Local database
     */
    public function get_localdb(): ?AlpmDb {}

    /**
     * Get list of files to not extract
     *
     * @return string[]|null List of noextract patterns
     * @deprecated Use $handle->noextracts instead
     */
    public function get_noextracts(): ?array {}

    /**
     * Get list of files to not upgrade
     *
     * @return string[]|null List of noupgrade patterns
     * @deprecated Use $handle->noupgrades instead
     */
    public function get_noupgrades(): ?array {}

    /**
     * Get list of sync databases
     *
     * @return AlpmDb[]|null List of sync databases
     */
    public function get_syncdbs(): ?array {}

    /**
     * Initialize a transaction
     *
     * @param bool $nodeps Skip dependency checks
     * @param bool $force Force installation
     * @param bool $nosave Don't save old config files
     * @param bool $nodepversion Ignore dependency versions
     * @param bool $cascade Remove dependent packages
     * @param bool $recurse Remove unneeded dependencies
     * @param bool $dbonly Only modify database
     * @param bool $alldeps Mark all packages as dependencies
     * @param bool $downloadonly Only download packages
     * @param bool $noscriptlet Don't run install scriptlets
     * @param bool $noconflicts Ignore conflicts
     * @param bool $needed Don't reinstall up-to-date packages
     * @param bool $allexplicit Mark all packages as explicit
     * @param bool $unneeded Remove unneeded packages
     * @param bool $recurseall Remove all unneeded dependencies
     * @param bool $nolock Don't acquire lock
     * @return AlpmTransaction|null Transaction object
     * @throws AlpmTransactionException If transaction init fails
     */
    public function init_transaction(
        bool $nodeps = false,
        bool $force = false,
        bool $nosave = false,
        bool $nodepversion = false,
        bool $cascade = false,
        bool $recurse = false,
        bool $dbonly = false,
        bool $alldeps = false,
        bool $downloadonly = false,
        bool $noscriptlet = false,
        bool $noconflicts = false,
        bool $needed = false,
        bool $allexplicit = false,
        bool $unneeded = false,
        bool $recurseall = false,
        bool $nolock = false
    ): ?AlpmTransaction {}

    /**
     * Load a package from file
     *
     * @param string $filename Path to package file
     * @param bool $checksig Whether to check signature
     * @return AlpmPkg|null Package object
     * @throws AlpmPkgException If loading fails
     */
    public function load_pkg(string $filename, bool $checksig = false): ?AlpmPkg {}

    /**
     * Register a sync database
     *
     * @param string $dbname Database name (e.g., "core", "extra")
     * @param int $pgp_level Signature level (use ALPM_SIG_* constants)
     * @return AlpmDb|null Database object
     * @throws AlpmDbException If registration fails
     */
    public function register_syncdb(string $dbname, int $pgp_level): ?AlpmDb {}

    /**
     * Remove an architecture
     *
     * @param string $architecture Architecture name
     * @return bool Success
     */
    public function remove_architecture(string $architecture): bool {}

    /**
     * Remove an assumed-installed package
     *
     * @param string $assumeinstalled Package name
     * @return bool Success
     */
    public function remove_assumeinstalled(string $assumeinstalled): bool {}

    /**
     * Remove a cache directory
     *
     * @param string $cachedir Cache directory path
     * @return bool Success
     */
    public function remove_cachedir(string $cachedir): bool {}

    /**
     * Remove a hook directory
     *
     * @param string $hookdir Hook directory path
     * @return bool Success
     */
    public function remove_hookdir(string $hookdir): bool {}

    /**
     * Remove an ignored group
     *
     * @param string $group Group name
     * @return bool Success
     */
    public function remove_ignoregrp(string $group): bool {}

    /**
     * Remove an ignored package
     *
     * @param string $package Package name
     * @return bool Success
     */
    public function remove_ignorepkg(string $package): bool {}

    /**
     * Remove a noextract pattern
     *
     * @param string $filename Filename pattern
     * @return bool Success
     */
    public function remove_noextract(string $filename): bool {}

    /**
     * Remove a noupgrade pattern
     *
     * @param string $filename Filename pattern
     * @return bool Success
     */
    public function remove_noupgrade(string $filename): bool {}

    /**
     * Set checkspace option
     *
     * @param bool $checkspace Whether to check disk space
     * @return bool Success
     */
    public function set_checkspace(bool $checkspace): bool {}
}

/**
 * Exception thrown by AlpmHandle operations
 */
class AlpmHandleException extends Exception {}

/**
 * Package database (local or sync)
 */
class AlpmDb
{
    /** @var string Database name */
    public readonly string $name;

    /** @var string[] Server URLs */
    public readonly array $servers;

    /** @var AlpmGroup[] Group cache */
    public readonly array $grpcache;

    /** @var AlpmPkg[] Package cache */
    public readonly array $pkgcache;

    /** @var int Signature level */
    public readonly int $siglevel;

    /** @var int Usage flags */
    public readonly int $usage;

    /** @var bool Whether database is valid */
    public readonly bool $valid;

    /**
     * Get string representation
     *
     * @return string Database name
     */
    public function __toString(): string {}

    /**
     * Add a server URL
     *
     * @param string $server Server URL
     * @return bool Success
     */
    public function add_server(string $server): bool {}

    /**
     * Check PGP signature of database
     *
     * @return array Signature check results
     */
    public function check_pgp_signature(): array {}

    /**
     * Get group cache
     *
     * @return AlpmGroup[]|null List of groups
     * @deprecated Use $db->grpcache instead
     */
    public function get_grpcache(): ?array {}

    /**
     * Get database name
     *
     * @return string Database name
     * @deprecated Use $db->name instead
     */
    public function get_name(): string {}

    /**
     * Get a package by name
     *
     * @param string $name Package name
     * @return AlpmPkg|null Package object
     */
    public function get_pkg(string $name): ?AlpmPkg {}

    /**
     * Get package cache
     *
     * @return AlpmPkg[]|null List of packages
     * @deprecated Use $db->pkgcache instead
     */
    public function get_pkgcache(): ?array {}

    /**
     * Get server URLs
     *
     * @return string[]|null Server URLs
     * @deprecated Use $db->servers instead
     */
    public function get_servers(): ?array {}

    /**
     * Search packages
     *
     * @param string[] $search Search terms
     * @return AlpmPkg[]|null Matching packages
     */
    public function search(array $search): ?array {}

    /**
     * Read a group
     *
     * @param string $group Group name
     * @return AlpmGroup|null Group object
     */
    public function read_grp(string $group): ?AlpmGroup {}

    /**
     * Remove a server URL
     *
     * @param string $server Server URL
     * @return bool Success
     */
    public function remove_server(string $server): bool {}

    /**
     * Update database
     *
     * @param bool $force Force update even if up-to-date
     * @return bool Success
     */
    public function update(bool $force = false): bool {}
}

/**
 * Exception thrown by AlpmDb operations
 */
class AlpmDbException extends Exception {}

/**
 * Package information
 */
class AlpmPkg
{
    /** @var string Package architecture */
    public readonly string $arch;

    /** @var AlpmBackup[] Backup files */
    public readonly array $backup;

    /** @var string|null Base64 encoded signature */
    public readonly ?string $base64_sig;

    /** @var int Build date timestamp */
    public readonly int $builddate;

    /** @var AlpmDepend[] Conflicts */
    public readonly array $conflicts;

    /** @var AlpmDb|null Source database */
    public readonly ?AlpmDb $db;

    /** @var AlpmDepend[] Dependencies */
    public readonly array $depends;

    /** @var string Package description */
    public readonly string $desc;

    /** @var int Download size in bytes */
    public readonly int $download_size;

    /** @var string Package filename */
    public readonly string $filename;

    /** @var AlpmFile[] Package files */
    public readonly array $files;

    /** @var string[] Groups this package belongs to */
    public readonly array $groups;

    /** @var bool Whether package has install scriptlet */
    public readonly bool $has_scriptlet;

    /** @var int Install date timestamp */
    public readonly int $installdate;

    /** @var int Installed size in bytes */
    public readonly int $isize;

    /** @var string[] Licenses */
    public readonly array $licenses;

    /** @var string Package name */
    public readonly string $name;

    /** @var AlpmDepend[] Optional dependencies */
    public readonly array $optdepends;

    /** @var string Packager name/email */
    public readonly string $packager;

    /** @var AlpmDepend[] Provides */
    public readonly array $provides;

    /** @var int Install reason (ALPM_PKG_REASON_*) */
    public readonly int $reason;

    /** @var AlpmDepend[] Replaces */
    public readonly array $replaces;

    /** @var string|null SHA256 checksum */
    public readonly ?string $sha256sum;

    /** @var int Package size in bytes */
    public readonly int $size;

    /** @var string Upstream URL */
    public readonly string $url;

    /** @var string Package version */
    public readonly string $version;

    /**
     * Get string representation
     *
     * @return string "name version"
     */
    public function __toString(): string {}

    /**
     * Compute packages that require this package
     *
     * @return string[] Package names
     */
    public function compute_requiredby(): array {}

    /**
     * Get extended data
     *
     * @return array<string, string> Key-value pairs
     */
    public function get_xdata(): array {}

    /**
     * Set install reason
     *
     * @param int $reason ALPM_PKG_REASON_EXPLICIT or ALPM_PKG_REASON_DEPEND
     * @return bool Success
     * @throws AlpmPkgException If invalid reason
     */
    public function set_reason(int $reason): bool {}

    /**
     * Check PGP signature
     *
     * @return array Signature check results
     */
    public function check_pgp_signature(): array {}

    // Deprecated getter methods
    /** @deprecated Use $pkg->arch instead */
    public function get_arch(): string {}
    /** @deprecated Use $pkg->backup instead */
    public function get_backup(): ?array {}
    /** @deprecated Use $pkg->base64_sig instead */
    public function get_base64_sig(): ?string {}
    /** @deprecated Use $pkg->builddate instead */
    public function get_builddate(): int {}
    /** @deprecated Use $pkg->conflicts instead */
    public function get_conflicts(): ?array {}
    /** @deprecated Use $pkg->db instead */
    public function get_db(): ?AlpmDb {}
    /** @deprecated Use $pkg->depends instead */
    public function get_depends(): ?array {}
    /** @deprecated Use $pkg->desc instead */
    public function get_desc(): string {}
    /** @deprecated Use $pkg->download_size instead */
    public function get_download_size(): int {}
    /** @deprecated Use $pkg->filename instead */
    public function get_filename(): string {}
    /** @deprecated Use $pkg->files instead */
    public function get_files(): ?array {}
    /** @deprecated Use $pkg->groups instead */
    public function get_groups(): ?array {}
    /** @deprecated Use $pkg->has_scriptlet instead */
    public function get_has_scriptlet(): bool {}
    /** @deprecated Use $pkg->installdate instead */
    public function get_installdate(): int {}
    /** @deprecated Use $pkg->isize instead */
    public function get_isize(): int {}
    /** @deprecated Use $pkg->licenses instead */
    public function get_licenses(): ?array {}
    /** @deprecated Use $pkg->name instead */
    public function get_name(): string {}
    /** @deprecated Use $pkg->optdepends instead */
    public function get_optdepends(): ?array {}
    /** @deprecated Use $pkg->packager instead */
    public function get_packager(): string {}
    /** @deprecated Use $pkg->provides instead */
    public function get_provides(): ?array {}
    /** @deprecated Use $pkg->reason instead */
    public function get_reason(): int {}
    /** @deprecated Use $pkg->replaces instead */
    public function get_replaces(): ?array {}
    /** @deprecated Use $pkg->sha256sum instead */
    public function get_sha256sum(): string {}
    /** @deprecated Use $pkg->size instead */
    public function get_size(): int {}
    /** @deprecated Use $pkg->url instead */
    public function get_url(): string {}
    /** @deprecated Use $pkg->version instead */
    public function get_version(): string {}
}

/**
 * Exception thrown by AlpmPkg operations
 */
class AlpmPkgException extends Exception {}

/**
 * Transaction for package operations
 */
class AlpmTransaction
{
    /**
     * Add a package to the transaction
     *
     * @param AlpmPkg $pkg Package to add
     * @return bool Success
     */
    public function add_pkg(AlpmPkg $pkg): bool {}

    /**
     * Commit the transaction
     *
     * @return bool Success
     * @throws AlpmTransactionException On commit failure
     */
    public function commit(): bool {}

    /**
     * Get packages to be installed
     *
     * @return AlpmPkg[]|null Packages to install
     */
    public function get_add(): ?array {}

    /**
     * Get transaction flags
     *
     * @return int Flags bitmask
     */
    public function get_flags(): int {}

    /**
     * Get packages to be removed
     *
     * @return AlpmPkg[]|null Packages to remove
     */
    public function get_remove(): ?array {}

    /**
     * Interrupt the transaction
     *
     * @return bool Success
     */
    public function interrupt(): bool {}

    /**
     * Prepare the transaction
     *
     * @return bool Success
     * @throws AlpmTransactionException On prepare failure
     */
    public function prepare(): bool {}

    /**
     * Release the transaction
     *
     * @return bool Success
     */
    public function release(): bool {}

    /**
     * Remove a package from the transaction
     *
     * @param AlpmPkg $pkg Package to remove
     * @return bool Success
     */
    public function remove_pkg(AlpmPkg $pkg): bool {}

    /**
     * Add system upgrade to transaction
     *
     * @param bool $do_downgrade Allow downgrades
     * @return bool Success
     */
    public function system_upgrade(bool $do_downgrade = false): bool {}
}

/**
 * Exception thrown by AlpmTransaction operations
 */
class AlpmTransactionException extends Exception {}

/**
 * Package dependency specification
 */
class AlpmDepend
{
    /** @var string Package name */
    public readonly string $name;

    /** @var string|null Version constraint */
    public readonly ?string $version;

    /** @var string|null Description (for optional deps) */
    public readonly ?string $desc;

    /** @var int Comparison modifier (ALPM_DEP_MOD_*) */
    public readonly int $mod;

    /**
     * Get string representation
     *
     * @return string Dependency string (e.g., "pkg>=1.0")
     */
    public function __toString(): string {}

    /**
     * Compute dependency string
     *
     * @return string Dependency string (e.g., "pkg>=1.0")
     */
    public function compute_string(): string {}
}

/**
 * File entry in a package
 */
class AlpmFile
{
    /** @var string File path */
    public readonly string $name;

    /** @var int File size in bytes */
    public readonly int $size;

    /** @var int File mode/permissions */
    public readonly int $mode;

    /**
     * Get string representation
     *
     * @return string File path
     */
    public function __toString(): string {}
}

/**
 * Backup file entry
 */
class AlpmBackup
{
    /** @var string File path */
    public readonly string $name;

    /** @var string|null File hash */
    public readonly ?string $hash;

    /**
     * Get string representation
     *
     * @return string File path
     */
    public function __toString(): string {}
}

/**
 * Package group
 */
class AlpmGroup
{
    /** @var string Group name */
    public readonly string $name;

    /** @var AlpmPkg[] Packages in this group */
    public readonly array $packages;

    /**
     * Get string representation
     *
     * @return string Group name
     */
    public function __toString(): string {}
}

/**
 * Package conflict
 */
class AlpmConflict
{
    /** @var AlpmPkg First conflicting package */
    public readonly AlpmPkg $package1;

    /** @var AlpmPkg Second conflicting package */
    public readonly AlpmPkg $package2;

    /** @var AlpmDepend Conflict reason */
    public readonly AlpmDepend $reason;

    /**
     * Get string representation
     *
     * @return string Conflict description
     */
    public function __toString(): string {}
}

/**
 * Missing dependency information
 */
class AlpmDepMissing
{
    /** @var string Package needing the dependency */
    public readonly string $target;

    /** @var AlpmDepend Missing dependency */
    public readonly AlpmDepend $depend;

    /** @var string|null Package causing the removal */
    public readonly ?string $causingpkg;

    /**
     * Get string representation
     *
     * @return string Missing dependency description
     */
    public function __toString(): string {}
}

/**
 * File conflict information
 */
class AlpmFileConflict
{
    /** @var string Package causing the conflict */
    public readonly string $target;

    /** @var int Conflict type (ALPM_FILECONFLICT_*) */
    public readonly int $type;

    /** @var string Conflicting file path */
    public readonly string $file;

    /** @var string|null Other package involved */
    public readonly ?string $ctarget;

    /**
     * Get string representation
     *
     * @return string File conflict description
     */
    public function __toString(): string {}
}

// ============================================================================
// Constants
// ============================================================================

// Dependency modifiers
/** Any version */
const ALPM_DEP_MOD_ANY = 1;
/** Equal to version */
const ALPM_DEP_MOD_EQ = 2;
/** Greater than or equal to version */
const ALPM_DEP_MOD_GE = 3;
/** Less than or equal to version */
const ALPM_DEP_MOD_LE = 4;
/** Greater than version */
const ALPM_DEP_MOD_GT = 5;
/** Less than version */
const ALPM_DEP_MOD_LT = 6;

// File conflict types
/** Conflict with another package's file */
const ALPM_FILECONFLICT_TARGET = 1;
/** Conflict with existing filesystem file */
const ALPM_FILECONFLICT_FILESYSTEM = 2;

// Database usage flags
/** Use for all operations */
const ALPM_DB_USAGE_ALL = 31;
/** Use for install operations */
const ALPM_DB_USAGE_INSTALL = 1;
/** Use for search operations */
const ALPM_DB_USAGE_SEARCH = 2;
/** Use for sync operations */
const ALPM_DB_USAGE_SYNC = 4;
/** Use for upgrade operations */
const ALPM_DB_USAGE_UPGRADE = 8;

// Signature levels
/** Require package signatures */
const ALPM_SIG_PACKAGE = 1;
/** Package signatures optional */
const ALPM_SIG_PACKAGE_OPTIONAL = 2;
/** Allow marginal trust for packages */
const ALPM_SIG_PACKAGE_MARGINAL_OK = 4;
/** Allow unknown trust for packages */
const ALPM_SIG_PACKAGE_UNKNOWN_OK = 8;
/** Require database signatures */
const ALPM_SIG_DATABASE = 16;
/** Database signatures optional */
const ALPM_SIG_DATABASE_OPTIONAL = 32;
/** Allow marginal trust for databases */
const ALPM_SIG_DATABASE_MARGINAL_OK = 64;
/** Allow unknown trust for databases */
const ALPM_SIG_DATABASE_UNKNOWN_OK = 128;
/** Use default signature level */
const ALPM_SIG_USE_DEFAULT = 256;

// Package install reasons
/** Installed as dependency */
const ALPM_PKG_REASON_DEPEND = 1;
/** Explicitly installed */
const ALPM_PKG_REASON_EXPLICIT = 0;

// Package origins
/** Loaded from file */
const ALPM_PKG_FROM_FILE = 1;
/** From local database */
const ALPM_PKG_FROM_LOCALDB = 2;
/** From sync database */
const ALPM_PKG_FROM_SYNCDB = 3;

// Package validation
/** Unknown validation */
const ALPM_PKG_VALIDATION_UNKNOWN = 0;
/** No validation */
const ALPM_PKG_VALIDATION_NONE = 1;
/** MD5 checksum validated */
const ALPM_PKG_VALIDATION_MD5SUM = 2;
/** SHA256 checksum validated */
const ALPM_PKG_VALIDATION_SHA256SUM = 4;
/** Signature validated */
const ALPM_PKG_VALIDATION_SIGNATURE = 8;

// Event types
const ALPM_EVENT_CHECKDEPS_START = 1;
const ALPM_EVENT_CHECKDEPS_DONE = 2;
const ALPM_EVENT_FILECONFLICTS_START = 3;
const ALPM_EVENT_FILECONFLICTS_DONE = 4;
const ALPM_EVENT_RESOLVEDEPS_START = 5;
const ALPM_EVENT_RESOLVEDEPS_DONE = 6;
const ALPM_EVENT_INTERCONFLICTS_START = 7;
const ALPM_EVENT_INTERCONFLICTS_DONE = 8;
const ALPM_EVENT_TRANSACTION_START = 9;
const ALPM_EVENT_TRANSACTION_DONE = 10;
const ALPM_EVENT_PACKAGE_OPERATION_START = 11;
const ALPM_EVENT_PACKAGE_OPERATION_DONE = 12;
const ALPM_EVENT_INTEGRITY_START = 13;
const ALPM_EVENT_INTEGRITY_DONE = 14;
const ALPM_EVENT_LOAD_START = 15;
const ALPM_EVENT_LOAD_DONE = 16;
const ALPM_EVENT_SCRIPTLET_INFO = 17;
const ALPM_EVENT_DISKSPACE_START = 18;
const ALPM_EVENT_DISKSPACE_DONE = 19;
const ALPM_EVENT_OPTDEP_REMOVAL = 20;
const ALPM_EVENT_DATABASE_MISSING = 21;
const ALPM_EVENT_KEYRING_START = 22;
const ALPM_EVENT_KEYRING_DONE = 23;
const ALPM_EVENT_KEY_DOWNLOAD_START = 24;
const ALPM_EVENT_KEY_DOWNLOAD_DONE = 25;
const ALPM_EVENT_PACNEW_CREATED = 26;
const ALPM_EVENT_PACSAVE_CREATED = 27;
const ALPM_EVENT_HOOK_START = 28;
const ALPM_EVENT_HOOK_DONE = 29;
const ALPM_EVENT_HOOK_RUN_START = 30;
const ALPM_EVENT_HOOK_RUN_DONE = 31;

// Log levels
const ALPM_LOG_ERROR = 1;
const ALPM_LOG_WARNING = 2;
const ALPM_LOG_DEBUG = 4;
const ALPM_LOG_FUNCTION = 8;

// Progress types
const ALPM_PROGRESS_ADD_START = 0;
const ALPM_PROGRESS_UPGRADE_START = 1;
const ALPM_PROGRESS_DOWNGRADE_START = 2;
const ALPM_PROGRESS_REINSTALL_START = 3;
const ALPM_PROGRESS_REMOVE_START = 4;
const ALPM_PROGRESS_CONFLICTS_START = 5;
const ALPM_PROGRESS_DISKSPACE_START = 6;
const ALPM_PROGRESS_INTEGRITY_START = 7;
const ALPM_PROGRESS_LOAD_START = 8;
const ALPM_PROGRESS_KEYRING_START = 9;
