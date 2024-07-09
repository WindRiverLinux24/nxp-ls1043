COMPATIBLE_MACHINE:nxp-ls1043 = "nxp-ls1043"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"
SRC_URI:nxp-ls1043 = "git://github.com/nxp-qoriq/dpdk;protocol=https;nobranch=1"
SRC_URI:append:nxp-ls1043 = " \
            file://0001-meson.build-march-and-mcpu-already-passed-by-Yocto.patch \
"
SRCREV:nxp-ls1043 = "5479bb82b12306a32283d2ef88efb63a696e0d78"

MESON_BUILDTYPE:nxp-ls1043 = "release"

PACKAGECONFIG:append:nxp-ls1043 ??= "openssl"
PACKAGECONFIG[openssl] = ",,openssl"

DPDK_EXAMPLES:nxp-ls1043 = "all"
EXTRA_OEMESON:append:nxp-ls1043 = " \
		-Doptimization=3 \
		-Denable_driver_sdk=true \
		${@bb.utils.contains('DISTRO_FEATURES', 'vpp', '-Dc_args="-Ofast -fPIC -ftls-model=local-dynamic"', '', d)} \
"

RDEPENDS:${PN}:append:nxp-ls1043 = " bash python3-pyelftools"

inherit pkgconfig
