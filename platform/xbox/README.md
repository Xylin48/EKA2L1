# Original Xbox / nxdk build probe

This is a **toolchain smoke test**, not an EKA2L1 port or an Xbox runtime memory detector.

The official [XboxDev nxdk](https://github.com/XboxDev/nxdk) README and getting-started guide describe installing its prerequisites, cloning with submodules, running `bin/activate`, and building projects using its Makefile.

After installing and activating nxdk:

```sh
make -C platform/xbox
```

The Makefile deliberately uses `NXDK_DIR` from the nxdk activation environment and includes `$(NXDK_DIR)/Makefile`, as documented by nxdk. The resulting XBE is **only a platform probe** and must not be represented as a functioning emulator.

The sample's 128 MiB value is a compile-time test fixture, **not** a hardware RAM measurement or a XeFu request. Next work: establish a documented runtime memory query, integrate actual emulation components, and test on target hardware.

No upstream subsystem has been removed or disabled to create this probe. The complete emulator's original CMake build remains unchanged.
