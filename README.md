# libconsole is a portable console library.

The purpose of this library is:

* Wrap ANSI escape codes in manipulators.
* Hide the differences between Windows and Linux by providing functions such as: kbhit, getch, getche on both OS.
* Provide helper functions: read_key, read_str, read_int
* Provide an _options_ class as an alternative to Linux getopt.
* Provide a simple _menu_ class


This library is tested on

* Linux (Ubuntu 20.04)
* Windows with Visual Studio Community 2019


## How to build

This library use cmake.

* Either you build and install this lib
```
   git clone https://github.com/TheBigFred/libconsole.git
   mkdir build
   cmake -S libconsole -B build
   make -j4
   sudo make install
```

   The default install dir is /usr/local. You can change it by adding _-DCMAKE_INSTALL_PREFIX:PATH="your install path"_ at the end of the cmake command line.

   The lib provide a cmake package and is found with find_package(libconsole). Available targets are: _console-static_ and _console-shared_.

* Either you include the sources in a subfolder of your project and you include it with an add_subdirectory.
   The console CMakeLists is written carrefully be added in a parent CMakeLists.

Two cmake options are available:

* -DENABLE_DOC_libconsole:BOOL=ON : add the make target libconsole-doxygen which generate the doxygen documentation.
* -DENABLE_TEST_libconsole:BOOL=ON : enable the unitests and examples build.
