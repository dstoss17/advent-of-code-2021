################################################################################
# Advent-of-Code main makefile
# Shortcut to enable calling make in individual day directories
################################################################################
ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# Common commands
MKDIR := mkdir -p
RM    := rm -rf
CD    := cd
CMAKE := cmake

# Default settings
DEFAULT_BUILD_TYPE := RelWithDebInfo
DEFAULT_BUILD_TOOL := ninja
DEFAULT_BUILD_DIR  := build

# Setup build directory
BUILD_DIR ?= $(DEFAULT_BUILD_DIR)
FULL_BUILD_DIR := $(ROOT_DIR)/$(BUILD_DIR)

# CMake build type
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
ifneq (,$(wildcard $(FULL_BUILD_DIR)/Makefile))
CFG_BUILD_TOOL := make
else ifneq (,$(wildcard $(FULL_BUILD_DIR)/build.ninja))
CFG_BUILD_TOOL := ninja
else
CFG_BUILD_TOOL := $(DEFAULT_BUILD_TOOL)
endif

# If BUILD_TOOL is not set, use the configured build tool
BUILD_TOOL ?= $(CFG_BUILD_TOOL)

# If the build tool and the configured build tool do not match, the build dir
# needs to be regenerated
ifneq ($(BUILD_TOOL),$(CFG_BUILD_TOOL))
$(info Updating configured build tool - $(BUILD_TOOL))
$(shell $(RM) $(FULL_BUILD_DIR))
endif

# Allow CTest to use parallel execution
CTEST_ENV = CTEST_PARALLEL_LEVEL=$(patsubst -j%,%,$(filter -j%,$(MAKEFLAGS)))

# Build tool-specific configuration
ifeq (make,$(BUILD_TOOL))
BUILD_CMD = +$(MAKE)
TEST_CMD = $(MAKE)
CMAKE_GENERATOR := "Unix Makefiles"
else ifeq (ninja,$(BUILD_TOOL))
BUILD_CMD = ninja
TEST_CMD = ninja
CMAKE_GENERATOR := "Ninja"
else
$(error Unsupported build tool - $(BUILD_TOOL))
endif

# Begin build rules
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
	$(CD) $(FULL_BUILD_DIR) && $(CTEST_ENV) $(TEST_CMD) $@

# Creates the build directory if it doesn't exist
$(FULL_BUILD_DIR):
	$(info Configuring for $(BUILD_TOOL) ($(CMAKE_GENERATOR)))
	$(MKDIR) $@ && $(CMAKE) $(CMAKE_OPTIONS) $(CMAKE_BUILD_TYPE) -B $@ -S $(ROOT_DIR) -G $(CMAKE_GENERATOR)

