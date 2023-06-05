do_image_wic[prefuncs] += "nxp_ls1043_wic"

nxp_ls1043_wic() {
	if [ "${CUSTOMER_BUILD_BOOTLOADER}" = "0" ] && \
		[ ! -f ${DEPLOY_DIR_IMAGE}/firmware_ls1043ardb_uboot_sdboot.img ]; then
		# Create a dummy bootloader file.
		echo "This is a dummy bootloader file." > "${DEPLOY_DIR_IMAGE}/firmware_ls1043ardb_uboot_sdboot.img"
	fi
}
