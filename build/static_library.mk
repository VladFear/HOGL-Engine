library        := $(LOCAL_MODULE_OUT_PATH)/lib$(LOCAL_MODULE_NAME).a
all_libraries  += $(library)

cpp_objs := $(call gen-objs-outnames-from-cpp, \
                   $(LOCAL_MODULE_CPP_SRC),    \
                   $(LOCAL_MODULE_OUT_OBJ_DIR))

c_objs   := $(call gen-objs-outnames-from-c, \
                   $(LOCAL_MODULE_C_SRC),    \
                   $(LOCAL_MODULE_OUT_OBJ_DIR))

dep_files := $(cpp_objs:%.o=%.d)
dep_files += $(c_objs:%.o=%.d)

dirs_to_create := $(LOCAL_MODULE_OUT_PATH)
dirs_to_create += $(call create-out-dirs-structure,  \
                          $(LOCAL_MODULE_SRC_PATH),  \
                          $(LOCAL_MODULE_OUT_OBJ_DIR))

all_dirs_to_create += $(dirs_to_create)

dirs_to_include := $(call dirs-to-include, $(LOCAL_MODULE_INCLUDES))

cpp_flags := $(LOCAL_MODULE_CPP_FLAGS)
c_flags   := $(LOCAL_MODULE_C_FLAGS)

ifeq ($(cpp_flags),)
cpp_flags := $(CXXFLAGS)
endif

ifeq ($(c_flags),)
c_flags := $(CFLAGS)
endif

# TODO: https://www.gnu.org/software/make/manual/html_node/Archive-Members.html#Archive-Members
$(library): $(cpp_objs) $(c_objs)
	$(QUIET) $(call pretty,      \
	         $(LINKING_MESSAGE), \
	         $(AR) rcs $@ $^)

# Rule, which describes how to create object file from cpp source.
$(LOCAL_MODULE_OUT_OBJ_DIR)/%.o: %.cpp
	$(QUIET) $(call pretty,          \
	         $(COMPILATION_MESSAGE), \
	         $(CXX) -c $(dirs_to_include) $(DEPFLAGS) $(cpp_flags) $< -o $@)

# Rule, which describes how to create object file from c source.
$(LOCAL_MODULE_OUT_OBJ_DIR)/%.o: %.c
	$(QUIET) $(call pretty,          \
	         $(COMPILATION_MESSAGE), \
	         $(CC) -c $(dirs_to_include) $(DEPFLAGS) $(c_flags) $< -o $@)

-include $(dep_files)
