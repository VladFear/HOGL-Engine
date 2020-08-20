CXX := g++

LD_LIBS := -lGL \
           -lglfw \
           -lGLEW \

LD_DIRS := -L/usr/lib \
           -L/usr/include \

ENGINE_LIB_NAME := libglobalengine.a

INC_DIR       := include
SRC_DIR       := source
OBJ_DIR       := objects
LIB_DIR       := lib
BUILD_DIR     := build
TEST_DIR      := tests
TEST_OUT_DIR  := $(OBJ_DIR)/$(TEST_DIR)

CXXFLAGS := -I$(INC_DIR) -g -Wall -Wextra -Werror
DEPFLAGS := -MMD -MP
LDFLAGS  := $(LD_DIRS) $(LD_LIBS)

OBJECT_DIRS := $(subst $(SRC_DIR),$(OBJ_DIR),$(shell find $(SRC_DIR) -type d))
TEST_DIRS   := $(addprefix $(OBJ_DIR)/,$(shell find $(TEST_DIR) -type d))

INCS  := $(shell find $(INC_DIR) -name "*.h")
SRCS  := $(shell find $(SRC_DIR) -name "*.cpp")
TESTS := $(shell find $(TEST_DIR) -name "*.cpp")
OBJS  := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS  := $(OBJS:%.o=%.d)
TEST_EXECS := $(TESTS:%.cpp=$(OBJ_DIR)/%.out)
