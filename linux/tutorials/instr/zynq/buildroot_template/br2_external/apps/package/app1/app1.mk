APP1_VERSION=0.1
#app source
APP1_SITE=/home/opa/embedded/fpga/xilinx/zynq/proj/template/br2_external/apps/package/app1 
APP1_SITE_METHOD=local
#
define APP1_BUILD_CMDS
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D) all
endef

define APP1_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/build/app1.elf $(TARGET_DIR)/usr/bin
endef

$(eval $(generic-package))

