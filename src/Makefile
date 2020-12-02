include $(CLEAR_VARS)

LOCAL_MODULE_NAME          := GlobalEngine
LOCAL_MODULE_OUT_PATH      := $(STATIC_LIBS_OUT_DIR)
LOCAL_MODULE_SRC_PATH      := $(SOURCE_DIR)
LOCAL_MODULE_OUT_OBJ_DIR   := $(OBJECT_OUT_DIR)
LOCAL_MODULE_CXX_SRC       := $(call recursive-find-cxx-files, $(LOCAL_MODULE_SRC_PATH))
LOCAL_MODULE_INCLUDE_DIRS  := $(INCLUDE_DIR) $(EXTERNAL_DIR)/SOIL2/src/SOIL2/
LOCAL_MODULE_OBJS          := $(OBJECT_OUT_DIR)/external/SOIL2/src/SOIL2/image_DXT.o \
                              $(OBJECT_OUT_DIR)/external/SOIL2/src/SOIL2/image_helper.o \
                              $(OBJECT_OUT_DIR)/external/SOIL2/src/SOIL2/wfETC.o \
                              $(OBJECT_OUT_DIR)/external/SOIL2/src/SOIL2/SOIL2.o
LOCAL_MODULE_DEPS          := $(STATIC_LIBS_OUT_DIR)/libSOIL2.a

include $(BUILD_STATIC_LIBRARY)
