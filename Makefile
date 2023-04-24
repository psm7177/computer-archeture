CC = gcc-9

INCLUDE = -Iinclude/

SRC_DIR = ./src
OBJ_DIR = ./obj
DEBUG_OBJ_DIR = ./debug-obj
DIRS=$(OBJ_DIR)

$(shell mkdir -p $(DIRS))
$(shell mkdir -p $(DEBUG_OBJ_DIR))

TARGET = asm-emulator
DEBUG_TARGET = $(TARGET)-debug 

SRCS = $(notdir $(wildcard $(SRC_DIR)/*.c))

OBJS = $(SRCS:.c=.o)
DEBUG_OBJS = $(SRCS:.c=.o)

OBJECTS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))
DEBUG_OBJECTS = $(patsubst %.o,$(DEBUG_OBJ_DIR)/%.o,$(DEBUG_OBJS))

DEPS = $(OBJECTS:.o=.d)
DEBUG_DEPS = $(DEBUG_OBJECTS:.o=.d)

all: $(TARGET) $(DEBUG_TARGET)

$(TARGET) : $(OBJECTS)
	echo $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(INCLUDE) -c $< -o $@ -MD

$(DEBUG_TARGET) : $(DEBUG_OBJECTS)
	echo $(DEBUG_OBJECTS)
	$(CC) -DDEBUG $(DEBUG_OBJECTS) -o $(DEBUG_TARGET)

$(DEBUG_OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -DDEBUG $(INCLUDE) -c $< -o $@ -MD

.PHONY: clean all
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)
	rm -f $(DEBUG_OBJECTS) $(DEBUG_DEPS) $(TARGET)

-include $(DEPS)
-include $(DEBUG_DEPS)