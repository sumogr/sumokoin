package=native_cctools
$(package)_version=43f32a4c61b5ba7fde011e816136c550b1b3146f
$(package)_download_path=https://github.com/tpoechtrager/cctools-port/archive
$(package)_file_name=$($(package)_version).tar.gz
$(package)_sha256_hash=a6ae1c5265db73eeec9da22dcba2d6f37e9f7d237a6ba8e724c7d7bbb78083ae
$(package)_build_subdir=cctools
$(package)_clang_version=10.0.0
$(package)_clang_download_path=https://github.com/llvm/llvm-project/releases/download/llvmorg-$($(package)_clang_version)/
$(package)_clang_download_file=clang+llvm-$($(package)_clang_version)-x86_64-linux-gnu-ubuntu-18.04.tar.xz
$(package)_clang_file_name=clang+llvm-$($(package)_clang_version)-x86_64-linux-gnu-ubuntu-18.04.tar.xz
$(package)_clang_sha256_hash=b25f592a0c00686f03e3b7db68ca6dc87418f681f4ead4df4745a01d9be63843
$(package)_extra_sources=$($(package)_clang_file_name)

$(package)_libtapi_version=3cb307764cc5f1856c8a23bbdf3eb49dfc6bea48
$(package)_libtapi_download_path=https://github.com/tpoechtrager/apple-libtapi/archive
$(package)_libtapi_download_file=$($(package)_libtapi_version).tar.gz
$(package)_libtapi_file_name=$($(package)_libtapi_version).tar.gz
$(package)_libtapi_sha256_hash=583ffece8e378fafc2c898ef3d9cd5d74ac55afa870d682369751b72ec4f86f1

$(package)_extra_sources=$($(package)_libtapi_file_name)
$(package)_extra_sources += $($(package)_clang_file_name)


define $(package)_fetch_cmds
$(call fetch_file,$(package),$($(package)_download_path),$($(package)_download_file),$($(package)_file_name),$($(package)_sha256_hash)) && \
$(call fetch_file,$(package),$($(package)_clang_download_path),$($(package)_clang_download_file),$($(package)_clang_file_name),$($(package)_clang_sha256_hash)) && \
$(call fetch_file,$(package),$($(package)_libtapi_download_path),$($(package)_libtapi_download_file),$($(package)_libtapi_file_name),$($(package)_libtapi_sha256_hash))
endef

define $(package)_extract_cmds
  mkdir -p $($(package)_extract_dir) && \
  echo "$($(package)_sha256_hash)  $($(package)_source)" > $($(package)_extract_dir)/.$($(package)_file_name).hash && \
  echo "$($(package)_clang_sha256_hash)  $($(package)_source_dir)/$($(package)_clang_file_name)" >> $($(package)_extract_dir)/.$($(package)_file_name).hash && \
  echo "$($(package)_libtapi_sha256_hash)  $($(package)_source_dir)/$($(package)_libtapi_file_name)" >> $($(package)_extract_dir)/.$($(package)_file_name).hash && \
  $(build_SHA256SUM) -c $($(package)_extract_dir)/.$($(package)_file_name).hash && \
  mkdir -p toolchain/bin toolchain/lib/clang/$($(package)_clang_version)/include && \
  mkdir -p libtapi && \
  tar --no-same-owner --strip-components=1 -C libtapi -xf $($(package)_source_dir)/$($(package)_libtapi_file_name) && \
  tar --no-same-owner --strip-components=1 -C toolchain -xf $($(package)_source_dir)/$($(package)_clang_file_name) && \
  rm -f toolchain/lib/libc++abi.so* && \
  tar --no-same-owner --strip-components=1 -xf $($(package)_source)
endef

define $(package)_set_vars
  $(package)_config_opts=--target=$(host) --with-libtapi=$($(package)_extract_dir)
  $(package)_ldflags+=-Wl,-rpath=\\$$$$$$$$\$$$$$$$$ORIGIN/../lib
  $(package)_config_opts+=--enable-lto-support --with-llvm-config=$($(package)_extract_dir)/toolchain/bin/llvm-config
  $(package)_cc=$($(package)_extract_dir)/toolchain/bin/clang
  $(package)_cxx=$($(package)_extract_dir)/toolchain/bin/clang++
endef

define $(package)_preprocess_cmds
  CC=$($(package)_cc) CXX=$($(package)_cxx) INSTALLPREFIX=$($(package)_extract_dir) ./libtapi/build.sh && \
  CC=$($(package)_cc) CXX=$($(package)_cxx) INSTALLPREFIX=$($(package)_extract_dir) ./libtapi/install.sh && \
  sed -i.old "/define HAVE_PTHREADS/d" $($(package)_build_subdir)/ld64/src/ld/InputFiles.h
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef


define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install && \
  mkdir -p $($(package)_staging_prefix_dir)/lib/ && \
  cd $($(package)_extract_dir) && \
  cp lib/libtapi.so.6 $($(package)_staging_prefix_dir)/lib/ && \
  cd $($(package)_extract_dir)/toolchain && \
  mkdir -p $($(package)_staging_prefix_dir)/lib/clang/$($(package)_clang_version)/include && \
  mkdir -p $($(package)_staging_prefix_dir)/bin $($(package)_staging_prefix_dir)/include && \
  cp bin/clang $($(package)_staging_prefix_dir)/bin/ &&\
  cp -P bin/clang++ $($(package)_staging_prefix_dir)/bin/ &&\
  cp lib/libLTO.so $($(package)_staging_prefix_dir)/lib/ && \
  cp -rf lib/clang/$($(package)_clang_version)/include/* $($(package)_staging_prefix_dir)/lib/clang/$($(package)_clang_version)/include/ && \
  cp bin/dsymutil $($(package)_staging_prefix_dir)/bin/$(host)-dsymutil && \
  if `test -d include/c++/`; then cp -rf include/c++/ $($(package)_staging_prefix_dir)/include/; fi && \
  if `test -d lib/c++/`; then cp -rf lib/c++/ $($(package)_staging_prefix_dir)/lib/; fi
endef
