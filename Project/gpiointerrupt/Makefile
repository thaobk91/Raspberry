
CC = gcc
CFLAGSS= -g -Wall

#build dir
BUILD_DIR = Build

#Source
SUBMODULE_DIR := 

SUBMODULE_INC := $(foreach dir, $(SUBMODULE_DIR), -I$(dir))
SUBMODULE_SRC := $(foreach dir, $(SUBMODULE_DIR), $(wildcard $(dir)/*.c))
SUBMODULE_OJB := $(SUBMODULE_SRC:.c=.o)
BUILD_OBJ = $(patsubst %, $(BUILD_DIR)/%, $(SUBMODULE_OJB))

TARGET= gpio_interrupt

all: $(TARGET)

$(TARGET): $(BUILD_DIR)/main.o $(BUILD_OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(BUILD_DIR)/main.o $(BUILD_OBJ) -lwiringPi
	
$(BUILD_DIR)/%.o: %.c
	@[ -d $(@D) ] || mkdir $(@D)
	$(CC) $(CFLAGS) -I./ $(SUBMODULE_INC) -lwiringPi -c $< -o $@ 

clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(TARGET)