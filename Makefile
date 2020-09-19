include environment.mk

TARGET_LIB := $(BUILD_DIR)/$(ENGINE_LIB_NAME)

all: $(TARGET_LIB)

tests: $(TEST_EXECS)

$(TARGET_LIB): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -c $(DEPFLAGS) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/%.out: %.cpp | $(TEST_OUT_DIR)
	$(CXX) $< $(OBJS) $(CXXFLAGS) $(LDFLAGS) -lgtest -pthread -o $@

$(TEST_OUT_DIR):
	@mkdir -p $(TEST_DIRS)

$(OBJ_DIR):
	@mkdir -p $(OBJECT_DIRS)

clean:
	$(RM) -r $(OBJ_DIR) $(BUILD_DIR)

.PHONY: all tests clean

-include $(DEPS)
