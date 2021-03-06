#!/bin/bash

set -e

echo "Building pacman version ${1}"

case $1 in
    git)
        git clone http://git.archlinux.org/pacman.git pacman-git
        ;;
    *)
        wget -O pacman-${1}.tar.gz https://sources.archlinux.org/other/pacman/pacman-${1}.tar.gz
        tar -xzf pacman-${1}.tar.gz
        ;;
esac

if [ -x "$(command -v apt-get)" ]; then
    sudo apt-get -qq update
    sudo apt-get install -y autopoint pkg-config libtool gettext libarchive-dev curl libgpg-error-dev libassuan-dev \
                            ninja-build python3 python3-pip python3-setuptools python3-wheel
    sudo pip3 install meson


    # install a newer version of gpgme than is provided by ubuntu
    curl -O https://www.gnupg.org/ftp/gcrypt/gpgme/gpgme-1.13.1.tar.bz2
    tar -xjf gpgme-1.13.1.tar.bz2
    cd gpgme-1.13.1
    ./configure --prefix=/usr --disable-fd-passing --disable-static --disable-gpgsm-test
    make
    sudo make install
    cd ..
else
    exit 1
fi

cd pacman-${1}
set +e
if [ "${1}" == "git" ]; then
    cd ..
    curl -O https://ftp.gnu.org/gnu/bash/bash-4.4.18.tar.gz
    tar -xzf bash-4.4.18.tar.gz
    cd bash-4.4.18
    ./configure
    make; sudo make install
    cd ../pacman-${1}
fi
meson --prefix=/usr build
cd build
ninja
sudo ninja install
