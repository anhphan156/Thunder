CC := g++
LDFLAGS := -lglm -lglfw -lvulkan -ldl -lpthread -lwayland-client -lwayland-cursor -lxkbcommon
CFLAGS := -Wall -g -std=c++17 -O2

SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
SHADER_DIR := shaders

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:%.cpp=%.o)
SHADERS := $(shell find $(SHADER_DIR) \( -name '*.frag' -o -name '*.vert' \))
VSPVS := $(SHADERS:%.vert=%v.spv)
FSPVS := $(SHADERS:%.frag=%f.spv)
EXECUTABLE = out

.PHONY: all clean

all: $(EXECUTABLE) $(VSPVS) $(FSPVS)

$(EXECUTABLE): $(OBJS)
	$(CC) -o $@ $(addprefix $(BUILD_DIR)/,$(notdir $^)) $(LDFLAGS)

$(OBJS): %.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $(addprefix $(BUILD_DIR)/,$(notdir $@)) -I$(INCLUDE_DIR)

%f.spv: %.frag
	glslc $< -o $(addprefix $(BUILD_DIR)/,$(notdir $@))
%v.spv: %.vert
	glslc $< -o $(addprefix $(BUILD_DIR)/,$(notdir $@))

run:
	./out

debug:
	gdb ./out

leak-check:
	#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leak.txt ./build/app
	valgrind --leak-check=full --log-file=leak.txt ./out

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)
