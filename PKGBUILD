# Maintainer: Matthias Quintern <matthiasqui@protonmail.com>
pkgname=gz-cpp-util
pkgver=1.3
pkgrel=4
pkgdesc="Utility library for c++"
arch=('any')
url="https://github.com/MatthiasQuintern/gz-cpp-util"
license=('GPL3')
makedepends=('git')
source=("git+${url}#branch=main")
md5sums=('SKIP')

build() {
	mkdir -p pkg
	cd "${pkgname}/src"
	make
	make DESTDIR="${srcdir}/pkg_tmp/usr" install
}


package() {
	mv ${srcdir}/pkg_tmp/* ${pkgdir}
	rm -d ${srcdir}/pkg_tmp
}
