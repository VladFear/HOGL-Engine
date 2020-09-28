CXXFLAGS := \
    -Wall             \
    -Wextra           \
    -Werror           \
    -Wwrite-strings   \
    -Wno-parentheses  \
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
