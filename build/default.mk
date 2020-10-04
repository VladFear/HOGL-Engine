CXXFLAGS := \
    -Wall             \
    -Wextra           \
    -Werror           \
    -Wwrite-strings   \
    -Wno-parentheses  \
    -Wpedantic        \
    -Warray-bounds    \
    -std=c++2a        \
    -g

DEPFLAGS := \
    -MMD    \
    -MP

LD_LIBS := \
    -lgtest     \
    -lpthread   \
    -lGL        \
    -lglfw      \
    -lGLEW
