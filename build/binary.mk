local_cxx_src := $(LOCAL_MODULE_CXX_SRC)

local_dirs_to_create  := $(LOCAL_MODULE_OUT_PATH)
all_dirs_to_create    += $(local_dirs_to_create)

local_dirs_to_include := $(call dirs-to-include, $(LOCAL_MODULE_INCLUDE_DIRS))

local_cxxflags := $(LOCAL_MODULE_CXXFLAGS)

ifeq ($(local_cxxflags),)
	local_cxxflags := $(DEFAULT_CXXFLAGS)
endif

local_ld_libs  := $(LOCAL_MODULE_LD_LIBS)

ifeq ($(local_ld_libs),)
	local_ld_libs := $(DEFAULT_LD_LIBS)
endif

# Rule, which describes how to create executable file from cpp source.
$(local_binary): PRIVATE_INCLUDES := $(local_dirs_to_include)
$(local_binary): PRIVATE_CXX_SRC  := $(local_cxx_src)
$(local_binary): PRIVATE_CXXFLAGS := $(local_cxxflags)
$(local_binary): PRIVATE_LD_LIBS  := $(local_ld_libs)
$(local_binary): PRIVATE_STATIC_LIBS_DIR := $(STATIC_LIBS_OUT_DIR)

$(local_binary): $(local_cxx_src) $(LOCAL_MODULE_DEPS)
	$(QUIET) $(call pretty,          \
	         $(COMPILATION_MESSAGE), \
	         $(CXX) $(PRIVATE_CXX_SRC) $(PRIVATE_INCLUDES) -L$(PRIVATE_STATIC_LIBS_DIR) \
	         $(PRIVATE_LD_LIBS) $(PRIVATE_CXXFLAGS) -o $@)
