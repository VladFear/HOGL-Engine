include environment.mk

TARGET_LIB := $(BUILD_DIR)/$(ENGINE_LIB_NAME)

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	mkdir -p $(BUILD_DIR)
	ar rcs $@ $^

$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | objdirs
	$(CXX) -c $(CXXFLAGS) $< -o $@

objdirs:
	mkdir -p $(OBJECT_DIRS)

clean:
	$(RM) -r $(OBJ_DIR) $(BUILD_DIR)
