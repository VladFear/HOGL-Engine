executable        := $(LOCAL_MODULE_OUT_PATH)/$(LOCAL_MODULE_NAME)
cpp_src           := $(LOCAL_MODULE_CPP_SRC)
all_executables   += $(executable)

dirs_to_create  := $(LOCAL_MODULE_OUT_PATH)
dirs_to_include := $(call dirs-to-include, $(LOCAL_MODULE_INCLUDES))

all_dirs_to_create += $(dirs_to_create)

cpp_flags := $(LOCAL_MODULE_CPP_FLAGS)

ifeq ($(cpp_flags),)
cpp_flags := $(CXXFLAGS)
endif

# TODO: -Lout and -lglobalengine change with dynamic substitution
# Rule, which describes how to create executable file from cpp source.
$(executable): $(cpp_src) $(LOCAL_MODULE_DEPS)
	$(QUIET) $(call pretty,          \
	         $(COMPILATION_MESSAGE), \
	         $(CXX) $^ $(dirs_to_include) -Lout -lglobalengine $(LD_LIBS) $(cpp_flags) -o $@)
