include build/config.mk
include $(BUILD_SYSTEM)/macros.mk
include $(BUILD_SYSTEM)/default.mk

.PHONY: GlobalEngine
.DEFAULT_GOAL := GlobalEngine ## Compile GlobalEngine library and tests
$(.DEFAULT_GOAL): artifacts | $(OUT_DIR)

all_libraries   :=
all_tests       :=
all_executables :=

# Include makefiles in subdirectories
all_subdir_makefiles := $(call all-subdir-makefiles, ./)
$(foreach mk, $(all-subdir-makefiles), $(eval include $(mk)))

artifacts: $(all_libraries) $(all_tests) $(all_executables)

$(OUT_DIR):
	$(QUIET) mkdir -p $@

.PHONY: clean
clean: ## Remove out directory
	$(info Remove out directory.)
	$(QUIET) $(RM) -r $(OUT_DIR)

.PHONY: clean-engine
clean-engine: ## Remove engine objs and engine library
	$(info Remove object directory and engine library.)
	$(QUIET) $(RM) -r $(OBJECT_OUT_DIR) out/$(ENGINE_LIB_NAME)

.PHONY: clean-tests
clean-tests: ## Remove directory with precompiled tests
	$(info Remove directory with tests - out/tests.)
	$(RM) -r $(TEST_OUT_DIR)

.PHONY: help
help:
	@awk -F ':|##' '/^[^\t].+?:.*?##/ {\
	printf "\033[36m%-30s\033[0m %s\n", $$1, $$NF \
	}' $(MAKEFILE_LIST)
