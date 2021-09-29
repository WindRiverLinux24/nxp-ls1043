#
# Copyright (C) 2021 Wind River Systems, Inc.
#
COMPATIBLE_MACHINE_nxp-ls1043 = "nxp-ls1043"
TARGET_SUPPORTED_KTYPES_nxp-ls1043 = "standard preempt-rt"

KERNEL_VERSION_SANITY_SKIP = "1"
SRCREV_machine_nxp-ls1043 ?= "${AUTOREV}"
SRCREV_meta_nxp-ls1043 ?= "${AUTOREV}"

FILESEXTRAPATHS_prepend_nxp-ls1043 := "${THISDIR}/files:"
SRC_URI_append_nxp-ls1043 = " \
    file://0001-arm64-mm-add-the-code-that-is-missed-when-upgrade-ke.patch \
"
