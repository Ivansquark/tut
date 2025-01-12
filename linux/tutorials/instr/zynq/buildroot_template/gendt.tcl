hsi::open_hw_design xsa/driver.xsa
hsi::set_repo_path /home/opa/embedded/vivado/dt_git/device-tree-xlnx
hsi::create_sw_design device-tree -os device_tree -proc ps7_cortexa9_0
hsi::generate_target -dir dt/
exit
