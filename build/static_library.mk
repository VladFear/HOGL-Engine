library        := $(LOCAL_MODULE_OUT_PATH)/lib$(LOCAL_MODULE_NAME).a
all_libraries  += $(library)

cpp_objs       := $(call gen-objs-outnames-from-cpp, \
                         $(LOCAL_MODULE_CPP_SRC),    \
                         $(LOCAL_MODULE_OUT_OBJ_DIR))

dep_files := $(cpp_objs:%.o=%.d)

dirs_to_create  := $(call create-out-dirs-structure,  \
                          $(LOCAL_MODULE_SRC_PATH),   \
                          $(LOCAL_MODULE_OUT_OBJ_DIR))

dirs_to_include := $(call dirs-to-include, $(LOCAL_MODULE_INCLUDES))

# TODO: https://www.gnu.org/software/make/manual/html_node/Archive-Members.html#Archive-Members
$(library): $(cpp_objs)
	$(QUIET) $(call pretty,      \
	         $(LINKING_MESSAGE), \
	         $(AR) rcs $@ $^)

# Rule, which describes how to create object file from cpp source.
$(LOCAL_MODULE_OUT_OBJ_DIR)/%.o: %.cpp | $(dirs_to_create)
	$(QUIET) $(call pretty,          \
	         $(COMPILATION_MESSAGE), \
	         $(CXX) -c $(dirs_to_include) $(DEPFLAGS) $(CXXFLAGS) $< -o $@)

$(dirs_to_create)::
	$(QUIET) mkdir -p $@

-include $(dep_files)
