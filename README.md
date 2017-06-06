[![Build Status](https://travis-ci.org/markzz/php-alpm.png)](https://travis-ci.org/markzz/php-alpm)

# php-alpm
A PHP extension to use Arch Linux's ALPM

This is still a work in progress. Although most features work, some do not and
there may still be some memory leaking hidden in here.

The main thing to be cautious about is using `AlpmTransaction` as it is very
leaky. If you are just using this to gather information from a Pacman database
(using `AlpmHandle`, `AlpmDb`, and `AlpmPkg`), it should result in very few
problems.

## Requirements
You need the following to build and run this.

1. PHP >= 5.6
    * **Note**: Code is written for PHP >=5.3, but is untested.
2. libalpm >=10.0

## Building
Do what you'd normally do for a php extension:

Get the code:
```
$ git clone https://github.com/markzz/php-alpm.git
```
If you are not on Arch Linux, you will need to build and install pacman (which
contains libalpm) first:

On Ubuntu (maybe Debian):
```
# apt-get install asciidoc libarchive-dev curl libgpgme11-dev
$ curl -O https://sources.archlinux.org/other/pacman/pacman-5.0.1.tar.gz
$ tar -xzvf pacman-5.0.1.tar.gz
$ cd pacman-5.0.1 && ./configure --prefix=/usr/local && make
# make install
```
Build it:
```
$ phpize
$ ./configure --enable-alpm
$ make
# make install
```

You should now have `alpm.so` installed in your modules folder and you need to
add `extension=alpm.so` to your `php.ini`.

## Contributing
This project is licensed under the LGPLv2.1 and any and all contributions are
welcome. You can either fork this on GitHub and file a Pull Request or you can
send git formatted patches to `mark.weiman@markzz.com`. Whichever you prefer.
