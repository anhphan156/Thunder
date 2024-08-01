CC := g++
LDFLAGS := -lglm -lglfw -lvulkan -ldl -lpthread -lwayland-client -lwayland-cursor -lxkbcommon
CFLAGS := -Wall -g -std=c++17 -O2

SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:%.cpp=%.o)
EXECUTABLE = out

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) -o $@ $(addprefix $(BUILD_DIR)/,$(notdir $^)) $(LDFLAGS)

$(OBJS): %.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $(addprefix $(BUILD_DIR)/,$(notdir $@)) -I$(INCLUDE_DIR)

run:
	./out

debug:
	gdb ./out

leak-check:
	#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leak.txt ./build/app
	valgrind --leak-check=full --log-file=leak.txt ./out

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)
