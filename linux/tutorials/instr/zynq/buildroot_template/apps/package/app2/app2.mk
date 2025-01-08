APP2_VERSION=0.1
#app source
APP2_SITE=/home/opa/embedded/fpga/xilinx/zynq/proj/template/apps/package/app2
APP2_SITE_METHOD=local
APP2_INSTALL_TARGET = YES
APP2_DEPENDENCIES = host-pkgconf

$(eval $(cmake-package))
