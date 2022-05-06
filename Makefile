CSOURCES := $(shell find . -name "*.c")
CPPSOURCES := $(shell find . -name "*.cpp")
CFLAGS := -Wall -Wextra -Wfloat-equal -Werror -O -MMD

all: CFLAGS := $(CFLAGS) -O3
all: CXXFLAGS := $(CFLAGS)
debug: CFLAGS := $(CFLAGS) -g
debug: CXXFLAGS := $(CFLAGS)
test: CFLAGS := $(CFLAGS) -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=null -fsanitize=bounds-strict -fstack-protector-all
test: CXXFLAGS := $(CFLAGS)

CXXFLAGS := $(CFLAGS)

LDLIBS := -lm -lstdc++
test: LDFLAGS := -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=null -fsanitize=bounds-strict -fstack-protector-all

all: kursach
debug: kursach
test: kursach

kursach: $(CSOURCES:%.c=%.o) $(CPPSOURCES:%.cpp=%.o)

DEPS := $(shell find -name "*.d")
-include $(DEPS)

clean:
	rm -f kursach
	rm -f *.o
	rm -f *.d
