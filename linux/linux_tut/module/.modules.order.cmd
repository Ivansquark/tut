cmd_/home/debian/embedded/desktop/vim/linux/module/modules.order := {   echo /home/debian/embedded/desktop/vim/linux/module/opa_printk.ko; :; } | awk '!x[$$0]++' - > /home/debian/embedded/desktop/vim/linux/module/modules.order