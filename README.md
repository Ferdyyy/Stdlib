SaC standard library
====================

This repository consists of SaC modules with basic functionality like
arithmetic, stdio, etc; which together form a standard library of SaC
language.

Build instructions
==================

To build the system one requires an operational [CMake](https://cmake.org/) >= 3.3
[Flex](http://flex.sourceforge.net/), and [Bison](https://www.gnu.org/software/bison/). 

An example on how to build the library:
```bash
$ cd Stdlib
$ git submodule init
$ git submodule update
$ mkdir build
$ cd build
$ cmake ..
$ mkdir ~/.sac2crc
$ make -j4  //you should have roughly 2GB per thread :-)
$ sudo make install
```

Variables that can be passed to CMake
=========================================

When running CMake it is possible to pass the following variables:
  * `-DTARGETS=x;y;z` --- build stdlib for targets x, y and z. (defaults are `seq; mt_pth`)
  * `-DSAC2C_EXR=/path/to/sac2c` --- specify `sac2c` executable directly. Otherwise CMake will
    try to find `sac2c` on yout PATH.
  * `-DLINKSETSIZE=n` --- set `-linksetsize n` when calling `sac2c`.  This option is responsible
    for the number of C functions that are put in a single C file when compiling a SaC program.
    The rule of thumb:
    * value `0` is the fastest time-wise but potentially results in a large memory consumption
    * value `1` reduces the memory consumption to minimum, buy significantly increases compilation time.
    
      *Default value: 500.*
