
# Include all .c-files as source files
SRC:=$(wildcard src/*.c)

# Make target 'all' the default target
all:




# Local build directory that will hold a parallel structure
# identical to the files in SRC
BUILD_DIR:=build


# Associate object files for each library

lib/libcomponent.so: $(BUILD_DIR)/src/component.o

lib/libresistance.so: $(BUILD_DIR)/src/resistance.o

lib/libpower.so: $(BUILD_DIR)/src/power.o


LIB_FILES:=lib/libcomponent.so lib/libresistance.so lib/libpower.so



# Place the .o-files and .d-files in a parallel structure under BUILD_DIR

OBJ:=$(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
DEP_FILES:=$(OBJ:.o=.d)

$(foreach s, $(SRC), \
 $(eval $(BUILD_DIR)/$(basename $s).o: $s) \
)


# Create d-files without system files, with phony target for included files
CFLAGS+=-MMD -MP

# Turn on all compiler warnings
CFLAGS+=-Wall

# Generate position independent code
CFLAGS+=-shared -fPIC

# Search path for include<>
CFLAGS+=-Isrc


all: lib electrotest

lib: $(LIB_FILES)

.PHONY: all

# Include generated dependency files if they exist
include $(wildcard $(DEP_FILES))

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

lib/%.so:
	mkdir -p $(dir $@)
	$(CC) $^ -shared -o $@

electrotest: $(BUILD_DIR)/src/main.o
	gcc -Llib -Wall -Wl,-rpath,'$$ORIGIN/lib' $^ -o $@ -lresistance -lpower -lcomponent -lm 

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR) electrotest

install: $(LIB_FILES) electrotest
	install -C electrotest /usr/bin
	install -C $(LIB_FILES) /usr/lib
