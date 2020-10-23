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

CFLAGS := \
    -Wall             \
    -Wextra           \
    -Werror           \
    -Wpedantic        \
    -Warray-bounds    \
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
