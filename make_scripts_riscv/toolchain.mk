##change to your toolchain path
CONFIG_TOOLCHAIN_DIR ?= $(BL60X_SDK_PATH)/../toolchain_gcc_t-head_$(shell uname | cut -d '_' -f1 | tr '[:upper:]' '[:lower:]')
CONFIG_TOOLPREFIX ?= $(CONFIG_TOOLCHAIN_DIR)/bin/riscv64-unknown-elf-
#CONFIG_TOOLPREFIX ?= riscv64-unknown-elf-
