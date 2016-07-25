Coding Guidelines
=================

Although the code here doesn't necessarily follow all the guidelines, this is to establish a standard coding style for this project for future commits.

Coding Style
------------

Column width: 80 columns or less within reason.

Indentation: 4 spaces.
Please don't add mode lines.

Blocks: When opening blocks like 'while', 'if', or 'for', the opening brace must be on the same line of the code block. The closing brace gets its own line. Also, the opening parenthesis must be one space from the keyword used.

```
for (item = list; item; item = alpm_list_next(item)) {
    grp = (alpm_group_t*)item->data;
    tmp = zend_string_init(grp->name, strlen(grp->name) + 1, 1);
    add_next_index_str(zv, tmp);
}

if (err) {
    zend_throw_error(php_alpm_handle_exception_class_entry, "could not set checkspace", 0);
    RETURN_NULL()
}
```

Functions: Like blocks, you need to put the opening brace on the same line as the function declaration. Same for the closing brace. Try to keep functions in alphabetical order.

```
void alpm_list_to_zval(alpm_list_t *list, zval *zv) {
    alpm_list_t *item;
    zend_string *tmp;
    ...
}

PHP_METHOD(Handle, remove_noupgrade) {
    php_alpm_handle_object *intern = Z_HANDLEO_P(getThis());
    char *arg;
    ...
}
```

Comments: They should be ANSI-C89 compliant. No `// Comment` style, but instead use only `/* Comment */`. 

```
/* Good Comment */
// Bad comment
```

Return statements: Do not write them like function calls.

```
return 0  /* good */
return(0) /* bad */
```

Variables: Declare them __all__ at the start of the block.

```
/* Good */
PHP_METHOD(Pkg, get_arch) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());
    const char *ret;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    ret = alpm_pkg_get_arch(intern->pkg);
    RETURN_STRING(ret)
}

/* Bad */
PHP_METHOD(Pkg, get_arch) {
    php_alpm_pkg_object *intern = Z_PKGO_P(getThis());

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL()
    }

    const char *ret = alpm_pkg_get_arch(intern->pkg);
    RETURN_STRING(ret)
}
```

Pointers: When declaring pointers (this includes for functions), don't put any spaces between the asterisk and the name.

```
/* Good */
alpm_list_t *list;
alpm_list_t **list;

/* Bad */
alpm_list_t* list;
alpm_list_t * list;
alpm_list_t* *list;
```