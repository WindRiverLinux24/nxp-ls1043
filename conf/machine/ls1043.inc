#@TYPE: Machine inc.
#@NAME: nxp-ls1043 layer

DEFAULTTUNE = "aarch64"
require conf/machine/include/arm/arch-armv8.inc

MACHINE_FEATURES += "usbhost ext3 vfat pci"

KERNEL_IMAGETYPE = "Image"

SERIAL_CONSOLE = "115200 ttyS0"

IMAGE_FSTYPES += "tar.bz2 wic wic.bmap"
WKS_FILE = "nxp-ls1043-sdimage.wks"
IMAGE_INSTALL_append = " kernel-devicetree kernel-image-image"
do_image_wic[depends] += "mtools-native:do_populate_sysroot dosfstools-native:do_populate_sysroot"

# multilib support
MULTILIBS ?= "multilib:lib32"
DEFAULTTUNE_virtclass-multilib-lib32 ?= "armv7athf-neon"

EXTRA_IMAGEDEPENDS = "u-boot-qoriq u-boot-uenv ppa"
UBOOT_CONFIG ??= "sdcard nor"
UBOOT_CONFIG[sdcard] = "ls1043ardb_sdcard_config,,u-boot-with-spl-pbl.bin"
UBOOT_CONFIG[nor] = "ls1043ardb_config,,u-boot-dtb.bin"

# it's used by many recipes in meta-freescale
MACHINE_SOCARCH = "${TUNE_PKGARCH}"

