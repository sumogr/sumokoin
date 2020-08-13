OSX_MIN_VERSION=10.14
OSX_SDK_VERSION=10.15
OSX_SDK=$(SDK_PATH)/MacOSX$(OSX_SDK_VERSION).sdk
LD64_VERSION=530
darwin_CC=clang -target $(host) -mmacosx-version-min=$(OSX_MIN_VERSION) --sysroot $(OSX_SDK) -mlinker-version=$(LD64_VERSION) -B $(host_prefix)/native/bin
darwin_CXX=clang++ -target $(host) -mmacosx-version-min=$(OSX_MIN_VERSION) --sysroot $(OSX_SDK) -isystem $(OSX_SDK)/usr/include/c++/v1 -mlinker-version=$(LD64_VERSION) -stdlib=libc++ -B $(host_prefix)/native/bin

darwin_CFLAGS=-pipe
darwin_CXXFLAGS=$(darwin_CFLAGS)
darwin_ARFLAGS=cr

darwin_release_CFLAGS=-O1
darwin_release_CXXFLAGS=$(darwin_release_CFLAGS)

darwin_debug_CFLAGS=-O1
darwin_debug_CXXFLAGS=$(darwin_debug_CFLAGS)

darwin_native_binutils=native_cctools
darwin_native_toolchain=native_cctools

darwin_cmake_system=Darwin
