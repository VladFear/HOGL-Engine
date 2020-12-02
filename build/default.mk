DEFAULT_CXXFLAGS :=    \
    -Wall              \
    -Wextra            \
    -Werror            \
    -Wwrite-strings    \
    -Wno-parentheses   \
    -Wpedantic         \
    -Warray-bounds     \
    -std=c++2a         \
    -g                 \

DEFAULT_CFLAGS :=      \
    -Wall              \
    -Wextra            \
    -Werror            \
    -Wpedantic         \
    -Warray-bounds     \
    -g                 \

DEFAULT_DEPFLAGS := \
    -MMD            \
    -MP             \

DEFAULT_LD_LIBS := \
    -lgtest        \
    -lpthread      \
    -lGL           \
    -lglfw         \
    -lGLEW         \
