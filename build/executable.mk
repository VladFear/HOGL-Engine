executable        := $(LOCAL_MODULE_OUT_PATH)/$(LOCAL_MODULE_NAME)
cpp_src           := $(LOCAL_MODULE_CPP_SRC)
all_executables   += $(executable)

dirs_to_create  := $(LOCAL_MODULE_OUT_PATH)
dirs_to_include := $(call dirs-to-include, $(LOCAL_MODULE_INCLUDES))

# TODO: -Lout and -lglobalengine change with dynamic substitution
# Rule, which describes how to create executable file from cpp source.
$(executable): $(cpp_src) $(LOCAL_MODULE_DEPS) | $(dirs_to_create)
	$(QUIET) $(call pretty,          \
	         $(COMPILATION_MESSAGE), \
	         $(CXX) $^ $(dirs_to_include) -Lout -lglobalengine $(LD_LIBS) $(CXXFLAGS) -o $@)

$(dirs_to_create)::
	$(QUIET) mkdir -p $@
