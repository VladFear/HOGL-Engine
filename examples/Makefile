include $(CLEAR_VARS)

LOCAL_MODULE_NAME          := TestApplication
LOCAL_MODULE_OUT_PATH      := $(OUT_DIR)/$(EXAMPLES_DIR)
LOCAL_MODULE_SRC_PATH      := $(EXAMPLES_DIR)/$(LOCAL_MODULE_NAME)
LOCAL_MODULE_CXX_SRC       := $(call recursive-find-cxx-files, $(LOCAL_MODULE_SRC_PATH))
LOCAL_MODULE_DEPS          := $(STATIC_LIBS_OUT_DIR)/libGlobalEngine.a
LOCAL_MODULE_INCLUDE_DIRS  := $(INCLUDE_DIR) \
                              $(LOCAL_MODULE_SRC_PATH) \
                              $(EXTERNAL_DIR)/SOIL2/src/SOIL2/
LOCAL_MODULE_LD_LIBS       := -lGlobalEngine $(DEFAULT_LD_LIBS)

include $(BUILD_EXECUTABLE)
