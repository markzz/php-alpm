# php-alpm
A PHP extension to use Arch Linux's ALPM

This is still a work in progress. This will kill your first born, burn your house down, blow up your server, and more, so for the time being, I would not advise using this.

## Requirements
You need the following to build and run this.

1. PHP >=7.0
2. libalpm >=10.0

## Building
Do what you'd normally do for a php extension:

Get the code:
```
$ git clone https://github.com/markzz/php-alpm.git
```
Build it:
```
$ phpize
$ ./configure --enable-alpm
$ make
# make install
```

You should now have `alpm.so` installed in your modules folder and you need to add `extension=alpm.so` to your `php.ini`.

## Contributing
This project is licensed under the GPLv2 and any and all contributions are welcome. You can either fork this on GitHub and file a Pull Request or you can send git formatted patches to `mark.weiman@markzz.com`. Whichever you prefer.
