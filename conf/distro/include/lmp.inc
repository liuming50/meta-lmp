DISTRO_VERSION = "2.6"

# These default to 'oecore' and 'nodistro'
SDK_NAME_PREFIX = "${DISTRO}"
SDK_VERSION = "${DISTRO_VERSION}"

MAINTAINER = "LMP Support <support@foundries.io>"

TARGET_VENDOR = "-lmp"

TCLIBCAPPEND = ""

require conf/distro/include/arm-defaults.inc
require conf/distro/include/security_flags.inc

PREFERRED_PROVIDER_virtual/kernel ?= "linux-lmp"
PREFERRED_PROVIDER_iasl-native = "acpica-native"

# No need for x11 even for native
DISTRO_FEATURES_NATIVE_remove = "x11"
DISTRO_FEATURES_NATIVESDK_remove = "x11"

# TODO: review default distro features
DISTRO_FEATURES_append = " pam systemd usrmerge virtualization"
DISTRO_FEATURES_remove = "3g alsa irda pcmcia nfc pulseaudio sysvinit"
VIRTUAL-RUNTIME_init_manager = "systemd"
PACKAGECONFIG_append_pn-systemd = " journal-upload resolved networkd"
PACKAGECONFIG_append_pn-qemu-native = " libusb"

# Default image formats
IMAGE_FSTYPES = "tar.xz ext4.gz wic wic.gz wic.bmap"
IMAGE_FSTYPES_remove = "tar.gz tar.bz2"

# LMP default classes and overwrites
INHERIT += "lmp"

INHERIT += "buildhistory"
INHERIT += "image-buildinfo"
BUILDHISTORY_COMMIT = "1"

PREMIRRORS ??= "\
     git://.*/.* https://storage.googleapis.com/lmp-cache/downloads/ \n \
     ftp://.*/.* https://storage.googleapis.com/lmp-cache/downloads/ \n \
     http://.*/.* https://storage.googleapis.com/lmp-cache/downloads/ \n \
     https://.*/.* https://storage.googleapis.com/lmp-cache/downloads/ \n \
"

MIRRORS =+ "\
     ftp://.*/.* https://storage.googleapis.com/lmp-cache/downloads/ \n \
     http://.*/.* https://storage.googleapis.com/lmp-cache/downloads/ \n \
     https://.*/.* https://storage.googleapis.com/lmp-cache/downloads/ \n \
"

# QA check settings - follow poky, which is stricter than the OE-Core defaults
WARN_TO_ERROR_QA = "already-stripped compile-host-path install-host-path \
                    installed-vs-shipped ldflags pn-overrides rpaths staticdev \
                    unknown-configure-option useless-rpaths"
WARN_QA_remove = "${WARN_TO_ERROR_QA}"
ERROR_QA_append = " ${WARN_TO_ERROR_QA}"
