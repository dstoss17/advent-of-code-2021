################################################################################
# Advent-of-Code main makefile
# Shortcut to enable calling make in individual day directories
################################################################################
ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BUILD_DIR ?= build
FULL_BUILD_DIR := $(ROOT_DIR)/$(BUILD_DIR)

# Default CMake build type
DEFAULT_BUILD_TYPE := RelWithDebInfo
BUILD_TYPE ?= ${DEFAULT_BUILD_TYPE}
CMAKE_BUILD_TYPE := -DCMAKE_BUILD_TYPE=${BUILD_TYPE}

# When configuring a project via this makefile, enable the symlink rules
CMAKE_OPTIONS := -DENABLE_SYMLINK_RULES=True

# Add any user-specified options (configure-time only)
CMAKE_OPTIONS += $(CMAKE_USER_OPTIONS)

# High-level options
MAKEFLAGS += --no-builtin-rules  # disable the built-in rules
MAKEFLAGS += --silent            # disable most output

TARGET_LIST := all clean help depend edit_cache rebuild_cache
.PHONY: $(TARGET_LIST)

# Build rule for regular targets
$(TARGET_LIST): | $(FULL_BUILD_DIR)
	$(MAKE) -C $(FULL_BUILD_DIR) $(MAKECMDGOALS)

# 'test' is a special rule since the generated rule for ctest doesn't accept a
# build directory. By default, it runs in the ROOT_DIR and not the build dir
# Additionally, it does not force a rebuild of targets, so the first step rebuilds
# the entire project before running any tests
.PHONY: test check
test check: | $(FULL_BUILD_DIR)
	$(MAKE) -C $(FULL_BUILD_DIR)
	cd $(FULL_BUILD_DIR) && $(MAKE) $@ ARGS="$(ARGS) $(filter -j%,$(MAKEFLAGS))"

# Creates the build directory if it doesn't exist
$(FULL_BUILD_DIR):
	mkdir -p $@ && cmake $(CMAKE_BUILD_TYPE) -B $@ $(CMAKE_OPTIONS)
