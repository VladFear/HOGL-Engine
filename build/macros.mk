# Explanation:
# Find all "Makefile" files in the subdirectories of given path.
# NOTE: Ignores Makefile, which given directory contains.
#
# Args:
# $(1) - Starting point (directory) for searching files.
#
# Example of usage:
# $(call all-subdir-makefiles,$(ROOT_DIR))
define all-subdir-makefiles
$(shell find $(1) -mindepth 2 -name "Makefile")
endef

# Explanation:
# Find all .cpp files in the given directory and it's subdirs.
#
# Args:
# $(1) - Starting point (directory) for searching files.
#
# Example of usage:
# $(call recursive-find-cpp-files,$(PATH_WHERE_TO_SEARCH))
define recursive-find-cpp-files
$(shell find $(1) -name "*.cpp")
endef

# Explanation:
# Find all .c files in the given directory and it's subdirs.
#
# Args:
# $(1) - Starting point (directory) for searching files.
#
# Example of usage:
# $(call recursive-find-c-files,$(PATH_WHERE_TO_SEARCH))
define recursive-find-c-files
$(shell find $(1) -name "*.c" -type f)
endef

# Explanation:
# Recreates the structure of source folders in another directory.
# Supposed to be used for creating src folders structure in out directory.
#
# Args:
# $(1) - Src directory path.
# $(2) - Out directory path.
#
# Example of usage:
# $(call create-out-dirs-structure, $(SRC_PATH), $(OUT_OBJ_DIR_PATH_TO_APPEND))
define create-out-dirs-structure
$(addprefix $(strip $(2))/,$(shell find $(1) -type d))
endef

# Explanation:
# Add -I flag for all words (supposed to be directories) in passed variable.
#
# Args:
# $(1) - Variable, which contains all directories to be included.
#
# Example of usage:
# $(call dirs-to-include,$(LISTED_DIRS_TO_INCLUDE)).
define dirs-to-include
$(patsubst %,-I%,$(1))
endef

# Explanation:
# Constructs correct paths for future objects from given source paths,
# and the path of the directory, where all objects will be placed.
#
# Args:
# $(1) - List of source files.
# $(2) - Out directory path.
#
# Example of usage:
# $(call gen-objs-outnames-from-cpp,$(SRC),$(OUT_OBJ_DIR_PATH_TO_APPEND)).
define gen-objs-outnames-from-cpp
$(addprefix $(strip $(2))/,$(1:%.cpp=%.o))
endef

# Explanation:
# Macro which allows to print actions process in pretty mode
#
# Args:
# $(1) - Action message
# $(2) - Command to be executed
#
# Picked from:
# http://www.lunderberg.com/2015/08/25/cpp-makefile-pretty-output/
#
define pretty
printf "%b" "$(ESC_BOLD)$(1) $(ESC_TARGET)$(@F)$(ESC_RESET)\r"; \
$(2); \
result=$${PIPESTATUS[0]}; \
if [ $$result -ne 0 ]; then \
  printf "%-60b%b" "$(ESC_TARGET) $@" " $(ESC_ERROR)$(ERROR_MESSAGE)$(ESC_RESET)\n"   ; \
elif [ -s $@.log ]; then \
  printf "%-60b%b" "$(ESC_TARGET) $@" " $(ESC_WARNING)$(WARNING_MESSAGE)$(ESC_RESET)\n"   ; \
else  \
  printf "%-60b%b" "$(ESC_BOLD)$(1)$(ESC_TARGET) $(@F)" " $(ESC_OK)$(SUCCESS_MESSAGE)$(ESC_RESET)\n"   ; \
fi; \
exit $$result
endef
