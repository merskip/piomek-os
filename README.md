Thanks for Łukasz Sowa; Przemub, Kj, Jarosław Pelczar from Wikibooks
 & Artur Danielewski for something

Getting Started
===

Build
---

 * `mkdir -p cmake-build-debug && cd cmake-build-debug/`
 * `cmake ..`
 * `make`
  - After this step you should have `PiomekOS.iso` in build directory

Run with QEMU
--

 * `sudo apt install qemu-system-x86`
 * `qemu-system-x86_64 -s -cdrom PiomekOS.iso`