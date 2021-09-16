#@TYPE: Machine inc.
#@NAME: nxp-ls1043 layer

DEFAULTTUNE = "cortexa53"
require conf/machine/include/tune-cortexa53.inc

MACHINE_FEATURES += "usbhost ext3 vfat pci"

KERNEL_IMAGETYPE = "Image"
KERNEL_DEVICETREE = "freescale/fsl-ls1043a-rdb-sdk.dtb freescale/fsl-ls1043a-rdb-usdpaa.dtb"

SERIAL_CONSOLE = "115200 ttyS0"

MACHINE_EXTRA_RRECOMMENDS = " kernel-modules kernel-devicetree"
IMAGE_FSTYPES += "tar.bz2 wic wic.bmap"
WKS_FILE = "nxp-ls1043-sdimage.wks"
IMAGE_INSTALL_append = " kernel-devicetree kernel-image-image"
do_image_wic[depends] += "mtools-native:do_populate_sysroot dosfstools-native:do_populate_sysroot"
IMAGE_BOOT_FILES ?= " Image fsl-ls1043a-rdb-sdk.dtb fsl-ls1043a-rdb-usdpaa.dtb"

# multilib support
MULTILIBS ?= "multilib:lib32"
DEFAULTTUNE_virtclass-multilib-lib32 ?= "armv7athf-neon"

UBOOT_CONFIG ??= "tfa-secure-boot tfa"
UBOOT_CONFIG[tfa] = "ls1043ardb_tfa_defconfig"
UBOOT_CONFIG[tfa-secure-boot] = "ls1043ardb_tfa_SECURE_BOOT_defconfig"

# it's used by many recipes in meta-freescale
MACHINE_SOCARCH = "${TUNE_PKGARCH}"

# pull in the meta-freescale layer.
BSP_NXP_DERIVED_append_nxp-ls1043  = " nxp-ls1043"

PREFERRED_PROVIDER_virtual/kernel ??= "linux-yocto"
PREFERRED_VERSION_linux-yocto ?= "5.10%"
PREFERRED_VERSION_dpdk = "19.11-20.12"
