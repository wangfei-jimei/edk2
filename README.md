Tianocore as coreboot payload
=============================

This branch introduces the corebootPkg. It allows to easily build a tianocore image
that is suitable as coreboot payload.

After setting up your EDK2 environment (BaseTools/gcc/mingw-gcc-build.py can help you
with the cross compiler), and entering the environment (". edksetup.sh"), build
corebootPkg using one of

  build -a IA32 -p corebootPkg/corebootPkg.dsc
  build -a X64 -p corebootPkg/corebootPkg.dsc

This ideally creates Build/coreboot{IA32,X64}/DEBUG_UNIXGCC/FV/COREBOOT.fd, the payload image.

Configure coreboot to use a Tianocore payload and point it to the COREBOOT.fd
created before.

Build, run, have fun.

CSM Support
-----------
It's possible to run corebootPkg with SeaBIOS as CSM. David Woodhouse did the necessary work
at http://git.infradead.org/users/dwmw2/edk2.git which I integrated (Thanks David!).

1. Fetch SeaBIOS master (eg. git clone http://review.coreboot.org/seabios.git).
2. Apply http://git.infradead.org/users/dwmw2/seabios.git/commitdiff/ef6babf96de2b2a15318ee113aee38f5e882e50a to SeaBIOS
3. Build SeaBIOS as CSM (General Features - Build Target - Build as Compatibility Support Module ...)
4. Copy $SEABIOS/out/bios.bin to $TIANO/corebootPkg/Csm/Csm16/Csm16.bin
5. Add -D CSM_ENABLE=TRUE to the tiano build line above

From here, proceed as usual (add COREBOOT.fd as payload).

Please note that the vgabios-cirrus.bin shipped with QEmu/KVM isn't exactly in the format CSM expects.
See https://lists.gnu.org/archive/html/qemu-devel/2013-01/msg03650.html

Using SeaBIOS' vgabios implementation for QEmu from latest master should work.

-- Patrick Georgi
