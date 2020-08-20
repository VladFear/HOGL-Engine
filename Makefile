include environment.mk

TARGET_LIB := $(BUILD_DIR)/$(ENGINE_LIB_NAME)

all: $(TARGET_LIB)

tests: $(TEST_EXECS)

$(TARGET_LIB): $(OBJS)
	mkdir -p $(BUILD_DIR)
	ar rcs $@ $^

$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | objdirs
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(TEST_EXECS): $(OBJ_DIR)/%.out : %.cpp | testdirs
	$(CXX) $< $(CXXFLAGS) -lgtest -pthread -o $@

testdirs:
	mkdir -p $(TEST_DIRS)

objdirs:
	mkdir -p $(OBJECT_DIRS)

clean:
	$(RM) -r $(OBJ_DIR) $(BUILD_DIR)
