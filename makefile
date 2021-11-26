################################################################################
# Advent-of-Code main makefile
# Shortcut to enable calling make in individual day directories
################################################################################
ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BUILD_DIR ?= build
FULL_BUILD_DIR := $(ROOT_DIR)/$(BUILD_DIR)

# CMake build type
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

# currently selected build tool
DEFAULT_BUILD_TOOL := make
BUILD_TOOL ?= $(DEFAULT_BUILD_TOOL)

# High-level options
ifeq (make,$(BUILD_TOOL))
BUILD_CMD = $(MAKE)
CTEST_ARGS = ARGS="$(ARGS) $(filter -j%,$(MAKEFLAGS))"
CMAKE_GENERATOR := "Unix Makefiles"
else ifeq (ninja,$(BUILD_TOOL))
BUILD_CMD = $(BUILD_TOOL)
CTEST_ARGS :=
CMAKE_GENERATOR := "Ninja"
else
$(error Unsupported build tool - $(BUILD_TOOL))
endif

TARGET_LIST := all clean help depend edit_cache rebuild_cache
.PHONY: $(TARGET_LIST)

# Build rule for regular targets
$(TARGET_LIST): | $(FULL_BUILD_DIR)
	$(BUILD_CMD) -C $(FULL_BUILD_DIR) $(MAKECMDGOALS)

# 'test' is a special rule since the generated rule for ctest doesn't accept a
# build directory. By default, it runs in the ROOT_DIR and not the build dir
# Additionally, it does not force a rebuild of targets, so the first step rebuilds
# the entire project before running any tests
.PHONY: test check
test check: | $(FULL_BUILD_DIR)
	$(BUILD_CMD) -C $(FULL_BUILD_DIR)
	cd $(FULL_BUILD_DIR) && $(BUILD_CMD) $@ $(CTEST_ARGS)

# Creates the build directory if it doesn't exist
$(FULL_BUILD_DIR):
	$(info Configuring for $(BUILD_TOOL) ($(CMAKE_GENERATOR)))
	mkdir -p $@ && cmake $(CMAKE_BUILD_TYPE) -B $@ $(CMAKE_OPTIONS) -G $(CMAKE_GENERATOR)
