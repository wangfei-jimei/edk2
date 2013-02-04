Tianocore as coreboot payload
=============================

This branch introduces the corebootPkg. It allows to easily build a tianocore image
that is suitable as coreboot payload.

After setting up your EDK2 environment (BaseTools/gcc/mingw-gcc-build.py can help you
with the cross compiler), and entering the environment (". edksetup.sh"), build
corebootPkg using

  build -a IA32 -p corebootPkg/corebootPkg.dsc

This ideally creates Build/corebootIA32/DEBUG_UNIXGCC/FV/COREBOOT.fd, the payload image.

Configure coreboot to use a Tianocore payload and point it to the COREBOOT.fd
created before.

Build, run, have fun.


-- Patrick Georgi
