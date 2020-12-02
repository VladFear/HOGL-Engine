local_library  := $(LOCAL_MODULE_OUT_PATH)/lib$(LOCAL_MODULE_NAME).a
all_libraries  += $(local_library)

local_objs := $(call gen-objs-outnames-from-cxx, \
                     $(LOCAL_MODULE_CXX_SRC),    \
                     $(LOCAL_MODULE_OUT_OBJ_DIR))

local_objs += $(call gen-objs-outnames-from-c, \
                     $(LOCAL_MODULE_C_SRC),    \
                     $(LOCAL_MODULE_OUT_OBJ_DIR))

local_objs += $(LOCAL_MODULE_OBJS)

local_dep_files := $(local_objs:%.o=%.d)
local_dep_files += $(local_objs:%.o=%.d)

local_dirs_to_create := $(LOCAL_MODULE_OUT_PATH)
local_dirs_to_create += $(call create-out-dirs-structure,  \
                               $(LOCAL_MODULE_SRC_PATH),   \
                               $(LOCAL_MODULE_OUT_OBJ_DIR))

all_dirs_to_create += $(local_dirs_to_create)

local_cxxflags := $(LOCAL_MODULE_CXXFLAGS)
local_cflags   := $(LOCAL_MODULE_CFLAGS)

ifeq ($(local_cxxflags),)
	local_cxxflags := $(DEFAULT_CXXFLAGS)
endif

ifeq ($(local_cflags),)
	local_cflags := $(DEFAULT_CFLAGS)
endif

$(local_library): PRIVATE_OBJS := $(local_objs)

$(local_library): $(local_objs) $(LOCAL_MODULE_DEPS)
	$(QUIET) $(call pretty,      \
	         $(LINKING_MESSAGE), \
	         $(AR) rcs $@ $(PRIVATE_OBJS))

$(LOCAL_MODULE_OUT_OBJ_DIR)/%.o: PRIVATE_INCLUDES := $(local_dirs_to_include)
$(LOCAL_MODULE_OUT_OBJ_DIR)/%.o: PRIVATE_CXXFLAGS := $(local_cxxflags)
$(LOCAL_MODULE_OUT_OBJ_DIR)/%.o: PRIVATE_CFLAGS   := $(local_cflags)
$(LOCAL_MODULE_OUT_OBJ_DIR)/%.o: PRIVATE_DEPFLAGS := $(DEFAULT_DEPFLAGS)

$(LOCAL_MODULE_OUT_OBJ_DIR)/%.o: %.cpp
	$(QUIET) $(call pretty,          \
	         $(COMPILATION_MESSAGE), \
	         $(CXX) -c $(PRIVATE_INCLUDES) $(PRIVATE_DEPFLAGS) \
	         $(PRIVATE_CXXFLAGS) $< -o $@)

$(LOCAL_MODULE_OUT_OBJ_DIR)/%.o: %.c
	$(QUIET) $(call pretty,          \
	         $(COMPILATION_MESSAGE), \
	         $(CC) -c $(PRIVATE_INCLUDES) $(PRIVATE_DEPFLAGS) \
	         $(PRIVATE_CFLAGS) $< -o $@)

local_dirs_to_include := $(call dirs-to-include, $(LOCAL_MODULE_INCLUDE_DIRS))

-include $(local_dep_files)
