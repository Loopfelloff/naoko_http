CC      := gcc
CFLAGS  := -std=c11 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Wpedantic -O2 -Iinclude
LDFLAGS :=

# ---- main program ----
SRC := $(shell find src -name '*.c')
OBJ := $(SRC:src/%.c=build/obj/%.o)
BIN := build/bin/webserver

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(OBJ:.o=.d)

# ---- tests ----
TEST_SRC := $(wildcard tests/test_*.c)
TEST_BIN := $(TEST_SRC:tests/%.c=build/tests/%)
# all objects except main.o, so each test can have its own main()
LIB_OBJ  := $(filter-out build/obj/main.o,$(OBJ))

build/tests/%: tests/%.c $(LIB_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< $(LIB_OBJ) -o $@ $(LDFLAGS)

test: $(TEST_BIN)
	@for t in $(TEST_BIN); do echo "Running $$t"; $$t || exit 1; done

# ---- extras ----
debug: CFLAGS += -g -O0 -fsanitize=address,undefined
debug: LDFLAGS += -fsanitize=address,undefined
debug: clean all

clean:
	rm -rf build

.PHONY: all test debug clean
