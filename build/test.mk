local_binary := $(LOCAL_MODULE_OUT_PATH)/$(LOCAL_MODULE_NAME)
all_tests    += $(local_binary)

include $(BUILD_SYSTEM)/binary.mk
