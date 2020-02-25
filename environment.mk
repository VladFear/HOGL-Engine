CXX := g++

LD_LIB := -lGL \
          -lglfw \
          -lGLEW \

LD_DIR := -L/usr/lib \
          -L/usr/include \

INC_DIR := include
SRC_DIR := source
OBJ_DIR := objects
LIB_DIR := lib
BUILD_DIR := build
OBJECT_DIRS := $(subst $(SRC_DIR),$(OBJ_DIR),$(shell find $(SRC_DIR) -type d))

CXXFLAGS := -I$(INC_DIR) -g -Wall

ENGINE_LIB_NAME := libglobalengine.a

INCS := $(shell find $(INC_DIR) -name "*.h")
SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
