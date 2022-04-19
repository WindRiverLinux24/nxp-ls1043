#@TYPE: Machine inc.
#@NAME: nxp-ls1043 layer

DEFAULTTUNE = "cortexa53"
require conf/machine/include/arm/armv8a/tune-cortexa53.inc

MACHINE_FEATURES += "usbhost ext3 vfat pci"

KERNEL_IMAGETYPE = "Image"
KERNEL_DEVICETREE = "freescale/fsl-ls1043a-rdb-sdk.dtb freescale/fsl-ls1043a-rdb-usdpaa.dtb \
			freescale/fsl-ls1023a-rdb-sdk.dtb freescale/fsl-ls1023a-rdb-usdpaa.dtb"

SERIAL_CONSOLE = "115200 ttyS0"

MACHINE_EXTRA_RRECOMMENDS = " kernel-modules kernel-devicetree"
IMAGE_FSTYPES += "tar.bz2 wic wic.bmap"
WKS_FILE = "nxp-ls1043-sdimage.wks"
IMAGE_INSTALL:append = " kernel-devicetree kernel-image-image"
do_image_wic[depends] += "mtools-native:do_populate_sysroot dosfstools-native:do_populate_sysroot"
IMAGE_BOOT_FILES ?= " Image fsl-ls1043a-rdb-sdk.dtb fsl-ls1043a-rdb-usdpaa.dtb fsl-ls1023a-rdb-sdk.dtb fsl-ls1023a-rdb-usdpaa.dtb"

# multilib support
MULTILIBS ?= "multilib:lib32"
DEFAULTTUNE:virtclass-multilib-lib32 ?= "armv7athf-neon"

# it's used by many recipes in meta-freescale
MACHINE_SOCARCH = "${TUNE_PKGARCH}"

# pull in the meta-freescale layer.
BSP_NXP_DERIVED:append:nxp-ls1043  = " nxp-ls1043"

PREFERRED_PROVIDER_virtual/kernel ??= "linux-yocto"
PREFERRED_VERSION_linux-yocto ?= "5.15%"
PREFERRED_VERSION_dpdk = "21.11"

NON_MULTILIB_RECIPES:append = " rcw"

# The loader is flashed into the device separately and not part of the SD image
OSTREE_BOOTLOADER_INCLUDE ?= ""
OSTREE_SD_UBOOT_WIC1 ?= ""
OSTREE_SD_UBOOT_WIC2 ?= ""
OSTREE_SD_UBOOT_WIC3 ?= ""
OSTREE_SD_UBOOT_WIC4 ?= ""

DEFAULT_DTB = "fsl-ls1043a-rdb-sdk.dtb"

OSTREE_SD_BOOT_ALIGN ?= "61440"
OSTREE_WKS_EFI_SIZE ?= "--size=64M"
OSTREE_FDISK_BLM ?= "122880"
# Because of the size of the offset being 122880 which is ~64M, 64 must be added
# to 64
OSTREE_FDISK_FSZ ?= "128"

OSTREE_UBOOT_CMD ?= "booti"
INITRAMFS_IMAGE ??= ""
IMAGE_BOOT_FILES:append = " \
    ${@bb.utils.contains('DISTRO_FEATURES', 'ostree', 'boot.scr', '', d)} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'ostree', '${INITRAMFS_IMAGE}-${MACHINE}.${INITRAMFS_FSTYPES};initramfs', '', d)} \
"
OSTREE_KERNEL ?= "Image"
OSTREE_COPY_IMAGE_BOOT_FILES = "1"
OSTREE_BOOTSCR_PRECMD ?= "\
setenv initrd_addr 0x90000000; \
setenv fdt_addr 0x80000000; \
setenv loadaddr 0x81000000; \
setenv no_menu yes; \
setenv console ttyS0; \
setenv no_fatwrite yes; \
"

# For ustart.img
OSTREE_NETINST_DEV ?= "/dev/mmcblk0,/dev/sda,/dev/vda"
OSTREE_NETINST_ARGS ?= " \
    ${OSTREE_CONSOLE} bl=ufsd rdinit=/install \
    instdev=${OSTREE_NETINST_DEV} instname=wrlinux \
    instbr=\$BRANCH insturl=\$URL instab=${OSTREE_USE_AB} \
    instsf=1 instdate=BUILD_DATE \
"
