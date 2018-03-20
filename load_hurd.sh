
  qemu-system-i386  -m 1024 -net nic,model=rtl8139   -net   user,hostfwd=tcp::5555-:22 -drive format=raw,cache=writeback,index=0,media=disk,file=debian-hurd-20171101.img
