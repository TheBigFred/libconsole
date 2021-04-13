# libconsole is a portable console library.

The purpose of this library is ...

This library is tested on

* Linux (Ubuntu 20.04)
* Windows with Visual Studio Community 2019


## How to build

This library use cmake.

* Either you build and install this lib

   git clone https://github.com/TheBigFred/libconsole.git
   mkdir build
   cmake -S libconsole -B build
   make -j4
   sudo make install

   The default install dir is /usr/local. You can change it by adding -DCMAKE_INSTALL_PREFIX:PATH="your install path"
   at the end of the cmake command line.

   The lib provide a cmake package and is found with find_package(libconsole). Available targets are:
   console-static and console-shared.

* Either you include the sources in a subfolder of your project and you include it with an add_subdirectory.
The console CMakeLists is written carrefully be added in a parent CMakeLists.

Two cmake options are available:

* -DENABLE_DOC_libconsole:STRING=ON : add the make target libconsole-doxygen which generate the doxygen documentation.
* -DENABLE_TEST_libconsole:STRING=ON : enable the unitests and examples build.
